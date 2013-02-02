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
-- Add IT PCI           12/11/2009      P.L. Royer              Adaptation for NPU and MiniBBCOM. Add correction for correct simulation (l.172)
---------------------------------------------------------------------------------------------------
--  Purpose:
--    Implémentation du protocole SERIRQ (sérialisation des IRQ ISA)
---------------------------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

----------------------------- P A C K A G E  -----------------------------------
PACKAGE serialirq21_p IS
    COMPONENT serialirq21
    PORT (
        -- Horloge
        pclk    : IN    std_logic;
        -- Reset  
        nreset  : IN    std_logic;
        -- enable
        nvalirq : IN    std_logic;
        --IRQs
        irq3    : IN    std_logic;
        irq4    : IN    std_logic;
        irq5    : IN    std_logic;
        irq6    : IN    std_logic;
        irq7    : IN    std_logic;
        irq9    : IN    std_logic;
        irq10   : IN    std_logic;
        irq11   : IN    std_logic;
        irq12   : IN    std_logic;
        irq14   : IN    std_logic; 
        irq15   : IN    std_logic;
        --PCI IRQ
        irq17   : IN    std_logic;
        irq18   : IN    std_logic;
        irq19   : IN    std_logic; 
        irq20   : IN    std_logic;

        -- nIOCHK
        niochk  : IN    std_logic;
        -- SERIRQ
        serirq  : INOUT std_logic
    );
    END COMPONENT;
END PACKAGE serialirq21_p;
