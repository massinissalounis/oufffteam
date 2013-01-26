-- Oufffteam
-- Projet carte mère
-- Device: LED

-- 29/12/2009			CBE			Création
-- 20/01/2013			PEG			Refonte


library ieee;
use ieee.std_logic_1164.all;

library work;

package LED_p is
 
	component LED is
		port (
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
