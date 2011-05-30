--**************************************************************************************************************************
--Project                      : GENERIC IP
--
--File                            : TB_Power_sequencer.vhd
--
--Author                       : C. BEGUET  23/02/09                                                                                   Copyight Centralp, 2009
--
--Board                         : GENERIC IP
--Device                       : GENERIC IP
--Part refence             :
--Program Number      :
--
--Revision History        Date          Author                          Comments
--
--**************************************************************************************************************************
--Purpose:
-- Séquenceur d'alimentation generique
-- Ordonne les alimentations de 1 à Nb_Voltages, 1 étant l'alimentation à mettre sous tension en 1er
-- Test Bench
--
--**************************************************************************************************************************

-- Library declaration
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;


entity TB_power_sequencer is
	constant period : time:= 15 ns;
	constant tb_Nb_Voltages : natural := 8;
	constant voltage_up_time : time := 200 us;	-- temps de montée des alimentations(power_good)
	constant voltage_down_time : time := 50 us;	-- temps de déscente des alimentations (power_good)
	constant pwr_on_time : time := 5 ms;			-- temps de fonctionnement de l'alimentation
	constant pause_time : time := 1 ms;			--temps de pause entre les tests
	
end TB_power_sequencer;

architecture TB of TB_power_sequencer is

	-- déclaration des composants
	component power_sequencer is
		generic ( Nb_Voltages : natural := 3 ); --Nombre de tensions à séquancer, de 1 à Nb_Voltages, 1 étant mise sous tension en 1er
		port (	-- interface de controle
				reset :				in std_logic;		-- Signal de reset
				clock :				in	std_logic;		-- horloge de synchronisation
				PWR_ENABLE : 		in  std_logic;		--Active l'alimentation
				PWR_OK :			out std_logic;		--Indique que l'alimentation est ON et OK
				PWR_OFF :			out	std_logic;		--Indique que l'alimentation est OFF
				ERROR :				out std_logic;		--Indique une erreur sur les alimentations
				-- interface avec les régulateurs
				Voltage_good :		in	std_logic_vector (Nb_Voltages downto 1);
				Voltage_enable :	out	std_logic_vector (Nb_Voltages downto 1)
				);
	end component power_sequencer;

	-- déclaration des signaux
	signal reset, clk_test, gene_error : std_logic;
	signal pwr_on, pwr_good, pwr_off, error_detect : std_logic;
	signal tb_Voltage_good :	std_logic_vector (tb_Nb_Voltages downto 1);
	signal tb_Voltage_enable :	std_logic_vector (tb_Nb_Voltages downto 1);
	
	signal rail_error : integer;	

begin

	-- intensiation des composants et mappage
	to_test: power_sequencer	generic map (tb_Nb_Voltages)
								port map (reset, clk_test, pwr_on, pwr_good, pwr_off, error_detect, tb_Voltage_good, tb_Voltage_enable);

	-- génération de l'horloge
	horloge : PROCESS
	BEGIN
        clk_test <= '1';
        wait for period;
        clk_test <= '0';
        wait for period;
	END PROCESS horloge;

	-- début du test
	test: process
	begin
		reset <= '1';
		pwr_on <= '0';
		rail_error <= 0;
		wait for 100 ns;
		reset <= '0';
		wait for 100 ns;
		gene_error <= '0';			--pas d'erreur pour ce démarrage
		pwr_on <= '1';				--marche
		wait until pwr_good = '1';	--attendre démarrage
		wait for pwr_on_time;		--attendre le temps de fonctionnement
		pwr_on <= '0';				--arret
		wait until pwr_off = '1';	--attendre arret
		wait for pause_time;		-- pause
		gene_error <= '1';			--generation d'une erreur pour ce démarrage
		rail_error <= 2;			--apres le power good du rail 2
		pwr_on <= '1';				--marche
		wait until pwr_off = '1';	--attendre arret car erreur
		wait for pause_time;		-- pause
		pwr_on <= '0';				--arret
		wait for pause_time;		-- pause
		gene_error <= '1';			--generation d'une erreur pour ce démarrage
		rail_error <= tb_Nb_Voltages; --apres un temps de fonctionnement
		pwr_on <= '1';				--marche
		wait until pwr_off = '1';	--attendre arret car erreur
		wait for pause_time;		-- pause
		pwr_on <= '0';				--arret
		
		wait;						--fin
	end process test;
	
	regul: process		  
	variable I : integer;
	begin					  
		wait for 10 ns;
		I:=1;
		regulateurs: while I<=tb_Nb_Voltages loop
			if (tb_Voltage_enable(I) = '1') then
				wait for voltage_up_time;		-- activation du power good après le temps de montée
				tb_Voltage_good(I) <= '1';
				if (gene_error = '1' and I = rail_error) then	--génération d'une erreur pendant le démarrage
					wait for voltage_up_time*2;
					tb_Voltage_good(I) <= '0';	--désactivation du power good pour simuler une erreur
				end if;				
			else
				wait for voltage_down_time;		-- désactivation du power good après le temps de déscente
				tb_Voltage_good(I) <= '0';
			end if;
			I := I+1;
		end loop regulateurs;
		
	end process regul;

end TB;