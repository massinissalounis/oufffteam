-- Oufffteam
-- Projet carte mère
-- Device: LED

-- 29/12/2009			CBE			Création
-- 20/01/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.LED_p.all;

entity LED is
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
end entity LED;

architecture synchronous of LED is
	
	signal LED_register : std_logic_vector (7 downto 0);
	
	begin
		bus_interface: process (reset, clock)
		begin
			if (reset = '1') then
				BUS_D <= (others => 'Z');
				LED_register <= (others => '0');
			elsif (clock'event and clock ='1') then
				if (BUS_CS = '1' and  BUS_WR ='1') then
					LED_register <= BUS_D;
				elsif (BUS_CS = '1' and BUS_RD = '1') then
					BUS_D <= LED_register;
				else
					BUS_D <= (others  => 'Z');
				end if;
			endif;
		end process bus_interface;
		
	LED1	<= LED_register(0);
	LED2	<= LED_register(1);
	
end architecture synchronous;