-- Oufffteam
-- Projet carte mère
-- Device: GPIO_OUT

-- 01/02/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity GPIO_OUT is
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
end entity GPIO_OUT;

architecture synchronous of GPIO_OUT is
	
	signal GPIO_register : std_logic_vector (7 downto 0);
	
	begin
		bus_interface: process (reset, clock)
		begin
			if (reset = '1') then
				BUS_D <= (others => 'Z');
				GPIO_register <= (others => '0');
			elsif (clock'event and clock ='1') then
				if (BUS_CS = '1' and  BUS_WR ='1') then
					GPIO_register <= BUS_D;
				elsif (BUS_CS = '1' and BUS_RD = '1') then
					BUS_D <= GPIO_register;
				else
					BUS_D <= (others  => 'Z');
				end if;
			end if;
		end process bus_interface;
		
		output_latch: process (reset, clock)
		begin
			if (reset = '1') then
				GPIO_REG <= (others => '0');
			elsif (clock'event and clock ='1') then
				GPIO_REG <= GPIO_register;
			end if;
		end process output_latch;
	
end architecture synchronous;