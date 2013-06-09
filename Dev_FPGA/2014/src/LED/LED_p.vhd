-- Oufffteam
-- Projet carte m�re
-- Device: LED

-- 29/12/2009			CBE			Cr�ation
-- 20/01/2013			PEG			Refonte


library ieee;
use ieee.std_logic_1164.all;

--library work;

package LED_p is
 
	component LED is
		port (
			clock		: in std_logic;
			reset		: in std_logic;
			-- Internal Bus inputs
			BUS_D		: inout std_logic_vector (7 downto 0);
			BUS_RD		: in std_logic;
			BUS_WR		: in std_logic;
			BUS_CS		: in std_logic;
			-- Module out
			LED1		: out std_logic;
			LED2		: out std_logic
		);
	end component LED;
 
end LED_p;
