-- Oufffteam
-- Projet carte mère
-- Device: LED

-- 29/12/2009			CBE			Création
-- 20/01/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--library work;

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
		pmp_write: process (PMP_in)
			begin
				if (PMP_in.PMP_SEL = '1' and PMP_in.PMP_PMWR = '1') then
				--if (PMP_in.PMP_PMWR = '1') then
					led_register <= PMP_in.PMP_WDATA;
				end if;
		end process pmp_write;
		
		
	
	LED1	<= led_register(0);
	LED2	<= led_register(1);
	PMP_out.PMP_RDATA <= led_register;
	
end architecture synchronous;