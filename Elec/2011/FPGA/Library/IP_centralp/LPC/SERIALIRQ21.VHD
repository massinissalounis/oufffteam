--------------------------------------------------------------------------------------------------
-- Project            : NPU - eMenlow (miniBBCOM)
--
-- File               : SerialIRQ21.vhd
--
-- Author             : L. Rabatel                                          Copyright Centralp, 2006
--
-- Board              : K190960 (MiniBBCOM) - K190955 (NPU) 
-- Device             : Lattice MachXO1200C
-- Part reference     : 
-- Program Number     : ppxxxx
--
-- Revision History     Date            Author                  Comments
--                      23/01/2007      P. Copier               Creation
-- Add IT PCI           12/11/2009      P.L. Royer              Adaptation for NPU and MiniBBCOM. Add correction for correct simulation (l.176)
-- Correction           08/01/2010      P.L. Royer              Correction (l.95) to take into account interruptions during state machine
-- Correction           04/11/2010      P.L. Royer              The 08/01/2010 correction was misplaced => rewrite correction properly
---------------------------------------------------------------------------------------------------
--  Purpose:
--    Implémentation du protocole SERIRQ (sérialisation des IRQ ISA)
-- Référence : Norme Seialized IRQ Support for PCI Systems v6.0 (01/09/1995)
-- Corrrection : la correction du 08/11/2010 permet de prendre en compte toutes les interruptions car lors 
-- d'une transmission d'un SERIRQ si la broche INT passe de '0' à '1', elle n'est pas prise en compte, la 
-- détection du changement d'état ne se faisant que pendant l'état IDLE.
---------------------------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;
LIBRARY work;
    USE work.filtrage_p.ALL;


ENTITY serialirq21 IS
    PORT (
        -- Horloge
        pclk    : IN std_logic;
        -- Reset
        nreset  : IN std_logic;
        -- enable
        nvalirq : IN std_logic;
        --IRQs
        irq3    : IN std_logic;
        irq4    : IN std_logic;
        irq5    : IN std_logic;
        irq6    : IN std_logic;
        irq7    : IN std_logic;
        irq9    : IN std_logic;
        irq10   : IN std_logic;
        irq11   : IN std_logic;
        irq12   : IN std_logic;
        irq14   : IN std_logic; 
        irq15   : IN std_logic;
        --PCI IRQ
        irq17   : IN std_logic;
        irq18   : IN std_logic;
        irq19   : IN std_logic; 
        irq20   : IN std_logic;
        -- nIOCHK
        niochk  : IN std_logic;
        -- SERIRQ
        serirq  : INOUT std_logic
    );
END serialirq21;

ARCHITECTURE arch_serialirq21 OF serialirq21 IS
        
    ------------------------ DECLARATIONS --------------------------------
    -- IRQ : _i = input, latchées sur pclk,  _f = signaux filtres 
    SIGNAL irq_i, irq_i2, irq_f, ack : std_logic_vector(20 DOWNTO 0); -- PLR: Pour utilisation avec SERIRQ : 21 slots implementes (Avec les IT PCI) 

    TYPE serirq_states    IS (idle, start_initiated, start_detected, start_finished, broadcast_wait, broadcast_sample, broadcast_recovery_active,
                            broadcast_recovery_passive, broadcast_turn_around, stop_detection, stop_confirmation, stop_detected);
    SIGNAL serirq_state              : serirq_states;
    
    SIGNAL continuousnquiet          : std_logic; -- Continuous mode : 1, Quiet mode : 0. Default is Continuous Mode
    
    SIGNAL serirq_index              : natural RANGE 0 TO 20; -- max: idem Number of data frames implemented    PLR: change to 21
    SIGNAL serirq_wait_start         : natural RANGE 0 TO 5; -- max duration of start frame
    SIGNAL stop_counter              : natural RANGE 0 TO 3; -- duration of stop frame for mode selection
    --constant CONST_START_DURATION  : NATURAL := 2; -- start frame duration -2
    CONSTANT const_serirq_frames     : natural := 21; --Number of data frames implemented   PLR: change to 21
    
    SIGNAL debug_ser                 : std_logic_vector(7 DOWNTO 0);
    
    ----------------------DEFINITION DE L'ARCHITECTURE-----------------------------
BEGIN

    -- Synchronisation IRQs sur horloge PCI
    PROCESS(nreset, pclk, serirq_state) 
    BEGIN
        IF((nreset='0')) THEN 
            irq_i  <= (OTHERS => '1');
            irq_i2 <= (OTHERS => '1');
        ELSIF( pclk'event AND pclk='1') THEN 
            IF( serirq_state=idle ) THEN    --PLR: add correction : "AND serirq_state=idle"
                -- Affectation des IRQ
                irq_i(3)  <= irq3;
                irq_i(4)  <= irq4;
                irq_i(5)  <= irq5;
                irq_i(6)  <= irq6;
                irq_i(7)  <= irq7;
                irq_i(9)  <= irq9;
                irq_i(10) <= irq10;
                irq_i(11) <= irq11;
                irq_i(12) <= irq12;
                irq_i(14) <= irq14;
                irq_i(15) <= irq15;
                irq_i(16) <= niochk;
                irq_i(17) <= irq17;
                irq_i(18) <= irq18;
                irq_i(19) <= irq19;
                irq_i(20) <= irq20;

                -- Pour detection d'une transition
                irq_i2    <= irq_i;
            END IF;
        END IF;
    END PROCESS;
    
    ------------------------
    --    Filtrage IRQ --
    ------------------------
    boucle : FOR i IN 0 TO 20 GENERATE                              --PLR: modif for PCI IT supporting

    filtrage_irq:
        filtrage PORT MAP (
            entree_filtre   => irq_i(i),
            clock_filtre    => pclk,
            nreset_systeme  => nreset,
            ack             => ack(i),
            sortie_filtre   => irq_f(i)
            );
    END GENERATE;

    
    -- SERIRQ
    PROCESS(nreset, nvalirq, pclk)
    BEGIN
        IF(nreset='0') THEN 
            serirq_state      <= idle;
            serirq            <= 'Z';
            ack               <= (OTHERS => '1');
            serirq_index      <= 0;
            serirq_wait_start <= 0;
            stop_counter      <= 0;
            continuousnquiet  <= '1'; -- Default : Continuous
            debug_ser         <= X"30";

        ELSIF(pclk'event AND pclk='1') THEN
            IF(nvalirq='1') THEN        -- Reset si nvalirq='1'
                serirq_state      <= idle;
                serirq            <= 'Z';
                ack               <= (OTHERS => '1');
                serirq_index      <= 0;
                serirq_wait_start <= 0;
                stop_counter      <= 0;
                continuousnquiet  <= '1'; -- Default : Continuous
                debug_ser         <= X"30";
            ELSE
                CASE serirq_state IS

                    WHEN idle =>
                        stop_counter <= 0;
                        IF(serirq = '0') THEN ---- Start Frame detectee ?
                            serirq_state      <= start_detected;
                            serirq            <= 'Z';
                            serirq_wait_start <= 2;                      -- Waiting for 2 SERIRQ low for 2 periods minimum
                            debug_ser <= X"01";
                        ELSIF ((serirq = '1') AND (continuousnquiet = '0') AND (irq_i /= irq_i2)) THEN -- Quiet Mode : initiate Start Frame if any IRQ detected, bypassing filters
                            serirq_state      <= start_initiated;
                            serirq            <= '0';
                            serirq_wait_start <= 1;                      -- Waiting for 2 SERIRQ low for only 1 period minimum as we're loosing one period when tri-stating SERIRQ
                            debug_ser         <= X"02";
                        ELSE
                            serirq_state      <= idle;
                            serirq            <= 'Z';
                            debug_ser         <= X"03";
                        END IF;

                    WHEN start_initiated =>
                        serirq_state      <= start_detected;             -- Waiting for Host to complete Start Frame
                        serirq            <= 'Z';
                        debug_ser         <= X"04";

                    WHEN start_detected =>                               -- wait for 1 clock period at least
                        serirq_wait_start     <= serirq_wait_start - 1;
                        IF(serirq = '0') THEN 
                            IF(serirq_wait_start=1) THEN --Still '0' : it's a start frame       PLR: modif "serirq_wait_start=0" to "serirq_wait_start=1" for correct simulation
                                serirq_state  <= start_finished;
                                debug_ser     <= X"05";
                            ELSE  -- keep waiting
                                serirq_state  <= start_detected;
                                debug_ser     <= X"26";
                            END IF;
                        ELSE -- '1' seen : it's not a start frame : back to idle
                            serirq_state  <= idle;
                            debug_ser     <= X"06";
                        END IF;

                    WHEN start_finished => 
                        IF(serirq /= '0') THEN 
                            serirq_state  <= broadcast_sample; -- next clock period we must broadcast
                            debug_ser     <= X"07";
                        ELSE
                            serirq_state  <= start_finished;
                            debug_ser     <= X"08";
                        END IF;

                    WHEN broadcast_sample =>
                        IF(irq_f(serirq_index)='0') THEN
                            serirq            <= '0';
                            ack(serirq_index) <= '1'; -- '0' transmitted, release the low-level extender (as per SERIRQ specifications)
                            serirq_state      <= broadcast_recovery_active;
                            debug_ser         <= X"0A";
                        ELSE
                            serirq            <= 'Z';
                            serirq_state      <= broadcast_recovery_passive;
                            ack(serirq_index) <= '0'; -- '1' transmitted
                            debug_ser         <= X"0B";
                        END IF;

                    WHEN broadcast_recovery_active =>
                        serirq            <= '1';
                        serirq_state      <= broadcast_turn_around;
                        debug_ser         <= X"0C";

                    WHEN broadcast_recovery_passive =>    
                        serirq            <= 'Z';
                        serirq_state      <= broadcast_turn_around;
                        debug_ser         <= X"0D";

                    WHEN broadcast_turn_around =>
                        serirq            <= 'Z';
                        serirq_index      <= serirq_index + 1;
                        IF(serirq_index=const_serirq_frames-1) THEN -- All the slots managed by this component have been broadcasted
                            serirq_index  <= 0;
                            serirq_state  <= stop_detection;
                            debug_ser     <= X"09";
                        ELSE -- Keep broadcasting
                            serirq_state  <= broadcast_sample;
                            debug_ser     <= X"0E";
                        END IF;

                    WHEN stop_detection => 
                        IF (serirq = '0') THEN 
                            serirq_state  <= stop_confirmation;
                            debug_ser     <= X"11";
                        ELSE
                            serirq_state  <= stop_detection;
                            debug_ser     <= X"12";
                        END IF;

                    WHEN stop_confirmation => -- SERIRQ has already been low for one period
                        IF (serirq = '0') THEN -- SERIRQ has been low for 2 periods : it's definitely a Stop Frame
                            serirq_state  <= stop_detected;
                            debug_ser     <= X"13";
                        ELSE
                            serirq_state  <= stop_detection; -- it wasn't a Stop Frame
                            debug_ser     <= X"14";
                        END IF;

                    WHEN stop_detected => -- it's definitely a Stop frame
                        IF (serirq /= '0') THEN -- end of Stop Frame 
                            serirq_state  <= idle;
                            IF(stop_counter = 0) THEN  -- Stop Frame was only 2 periodes long : Quiet mode selected
                                continuousnquiet <= '0';
                                debug_ser        <= X"15";
                            ELSE
                                continuousnquiet <= '1'; -- Stop Frame was 3 periodes long : Continuous mode selected
                                debug_ser        <= X"16";
                            END IF;
                        ELSE
                            serirq_state <= stop_detected;
                            stop_counter <= stop_counter + 1;
                            debug_ser    <= X"17";
                            IF(stop_counter > 1) THEN -- It shouldn't happen, but just to be safe....
                                serirq_state <= idle;
                                debug_ser    <= X"18";
                            END IF;
                        END IF;

                    WHEN OTHERS =>
                        serirq_state <= idle;
                        debug_ser    <= X"20";

                END CASE;
            END IF;
        END IF;
    END PROCESS;
 
END arch_serialirq21;
