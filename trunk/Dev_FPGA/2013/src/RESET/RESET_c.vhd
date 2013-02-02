-- Oufffteam
-- Projet carte mère
-- Device: Reset reg

-- 29/12/2009			CBE			Création
-- 27/01/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--library work;
--use work.RESET_p.all;

entity RESET is
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
end entity RESET;

architecture synchronous of RESET is
	
	signal RESET_register : std_logic_vector (7 downto 0);
	
	begin
		bus_interface: process (reset, clock)
		begin
			if (reset = '1') then
				BUS_D <= (others => 'Z');
				RESET_register <= (others => '0');
			elsif (clock'event and clock ='1') then
				if (BUS_CS = '1' and  BUS_WR ='1') then
					RESET_register <= BUS_D;
				elsif (BUS_CS = '1' and BUS_RD = '1') then
					BUS_D <= RESET_register;
				else
					BUS_D <= (others  => 'Z');
				end if;
			end if;
		end process bus_interface;
		
	SOFT_RESET	<= '1' when RESET_register = X"FF" else '0';
	SOFT_RESET_N	<= '0' when RESET_register = X"FF" else '1';

end architecture synchronous;