-- Oufffteam
-- Projet carte mère
-- Device: PMP

-- 29/12/2009			CBE			Création

library ieee;
use ieee.std_logic_1164.all;

package PMP_decode_p is
	component PMP_decode is
		generic ( cs_number : natural := 2);
		port (
			clock		: in std_logic;
			reset		: in std_logic;
			-- PMP
			PMP_PMALH	: in std_logic;
			PMP_PMALL	: in std_logic;
			PMP_PMCS	: in std_logic;
			PMP_PMD		: inout std_logic_vector (7 downto 0);
			internal_CS	: out std_logic_vector (cs_number - 1 downto 0)
			);
	end component PMP_decode;

end package PMP_decode_p;

package body PMP_decode_p is

end package body PMP_decode_p;