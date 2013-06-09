-- Oufffteam
-- Projet carte mère
-- Device: PMP

-- 29/12/2009			CBE			Création
-- 20/01/2013			PEG			Refonte


library ieee;
use ieee.std_logic_1164.all;

package PMP_P is

	component PMP_interface is
		port (
			-- in
			clock		: in std_logic;
			reset		: in std_logic;
			-- in - PMP
			PMP_PMALH	: in std_logic;
			PMP_PMALL	: in std_logic;
			PMP_PMCS	: in std_logic;
			PMP_PMD		: inout std_logic_vector (7 downto 0);
			PMP_PMRD	: in std_logic;
			PMP_PMWR	: in std_logic;
			-- out
			BUS_D		: inout std_logic_vector (7 downto 0);
			BUS_A		: out std_logic_vector (15 downto 0);
			BUS_RD		: out std_logic;
			BUS_WR		: out std_logic
		);
	end component PMP_interface;
  
end PMP_p;


