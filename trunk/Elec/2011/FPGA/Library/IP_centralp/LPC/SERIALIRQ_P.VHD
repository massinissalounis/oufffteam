--------------------------------------------------------------------------------------------------
-- Project            : Pont PCI/ISA + Controle carte pour carte CBC
--
-- File               : SerialIRQ_p.vhd
--
-- Author             : L. Rabatel                                          Copyright Centralp, 2006
--
-- Board              : K190884  
-- Device             : Lattice XP6C
-- Part reference     : D10
-- Program Number     : pp1109
--
-- Revision History     Date            Author                  Comments
--                      23 janvier 2007    P. Copier               Creation
--
---------------------------------------------------------------------------------------------------
--  Purpose:
--    Implémentation du protocole SERIRQ (sérialisation des IRQ ISA)
---------------------------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

----------------------------- P A C K A G E  -----------------------------------
PACKAGE serialirq_p IS
    COMPONENT serialirq
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
        -- nIOCHK
        niochk  : IN    std_logic;
        -- SERIRQ
        serirq  : INOUT std_logic
    );
    END COMPONENT;
END PACKAGE serialirq_p;
