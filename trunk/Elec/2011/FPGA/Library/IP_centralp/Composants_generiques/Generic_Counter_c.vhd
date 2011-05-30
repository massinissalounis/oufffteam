--------------------------------------------------------------------------------------------------------
-- Project :			Generic counter
--
-- File:			Generic_Counter_c.vhd
--
-- Author:			C. BEGUET
--
-- Board:			all
--
-- Device:			all
--
-- Dependencies:		none
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author		Comments
--				1.0	06/05/2009		C. BEGUET		Creation
--
--
--------------------------------------------------------------------------------------------------------
-- Purpose: Counter with variable width (generic input), count up or down, asynchronous  reset, asynchronous zero detection, asynchronous parallel loading.
--------------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
 
entity generic_counter is
	generic ( WIDTH : natural := 32);
	port (
		CLK			: in std_logic;		-- Counter clock
		aRESET_n	: in std_logic;		-- Asynchronous reset
		ENABLE 		: in std_logic;		-- Active couting
		DOWN_n		: in std_logic;		-- Count DOWN when LOW, count UP when HI
		LOAD		: in std_logic;		-- Asynchronous parallel load when HI
		ZERO		: out std_logic;	-- Asynchronous zero detection
		DATA		: in  std_logic_vector (WIDTH-1 downto 0);	-- Data to load
		Q			: out std_logic_vector (WIDTH-1 downto 0)	-- Synchronous counter value output
		);
end generic_counter;
 
architecture asynchronous_reset_load of generic_counter is
	
	signal cnt : std_logic_vector (WIDTH-1 downto 0);	-- Counter value
	
	begin
	process(aRESET_n, LOAD, CLK)
		begin
		if (aRESET_n = '0') then
			cnt <= (others => '0');	-- Reset
		elsif (LOAD = '1') then
			cnt <= DATA;			-- Parallel load
		elsif rising_edge(CLK) then
			if (ENABLE = '1' and DOWN_n = '1') then
				cnt <= cnt - 1;			-- Count DOWN
			elsif (ENABLE = '1' and DOWN_n = '0') then
				cnt <= cnt + 1;			-- Count UP
			end if;
		end if;
	end process;

	ZERO <= '1' when (cnt = 0) else '0'; -- Zero detection
	Q <= cnt;			-- Output
end architecture asynchronous_reset_load;
