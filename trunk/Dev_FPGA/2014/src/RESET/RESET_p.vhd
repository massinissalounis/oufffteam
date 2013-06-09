-- Oufffteam
-- Projet carte mère
-- Device: Reset reg

-- 29/12/2009			CBE			Création
-- 27/01/2013			PEG			Refonte


library ieee;
use ieee.std_logic_1164.all;


package RESET_p is
 
	component RESET is
		port (
			clock		: in std_logic;
			reset		: in std_logic;
			-- Internal Bus inputs
			BUS_D		: inout std_logic_vector (7 downto 0);
			BUS_RD		: in std_logic;
			BUS_WR		: in std_logic;
			BUS_CS		: in std_logic;
			-- Module out
			SOFT_RESET	: out std_logic;
			SOFT_RESET_N	: out std_logic
		);
	end component RESET;
 
end RESET_p;
