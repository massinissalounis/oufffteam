-- Oufffteam
-- Projet carte mère
-- Device: GPIO

-- 01/02/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;

package GPIO_p is
 
	component GPIO_IN is
		port (
			clock		: in std_logic;
			reset		: in std_logic;
			-- Internal Bus inputs
			BUS_D		: inout std_logic_vector (7 downto 0);
			BUS_RD		: in std_logic;
			BUS_WR		: in std_logic;
			BUS_CS		: in std_logic;
			-- Module out
			GPIO_REG	: in std_logic_vector (7 downto 0)
		);
	end component GPIO_IN;
 
	component GPIO_OUT is
		port (
			clock		: in std_logic;
			reset		: in std_logic;
			-- Internal Bus inputs
			BUS_D		: inout std_logic_vector (7 downto 0);
			BUS_RD		: in std_logic;
			BUS_WR		: in std_logic;
			BUS_CS		: in std_logic;
			-- Module out
			GPIO_REG	: out std_logic_vector (7 downto 0)
		);
	end component GPIO_OUT;
end GPIO_p;
