-- Oufffteam
-- Projet carte mère
-- Device: GPIO_IN

-- 01/02/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity GPIO_IN is
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
end entity GPIO_IN;

architecture synchronous of GPIO_IN is
	
	signal GPIO_register : std_logic_vector (7 downto 0);
	
	begin
		bus_interface: process (reset, clock)
		begin
			if (reset = '1') then
				BUS_D <= (others => 'Z');
			elsif (clock'event and clock ='1') then
				if (BUS_CS = '1' and BUS_RD = '1') then
					BUS_D <= GPIO_register;
				else
					BUS_D <= (others  => 'Z');
				end if;
			end if;
		end process bus_interface;
		
	GPIO_register <= GPIO_REG;
	
end architecture synchronous;