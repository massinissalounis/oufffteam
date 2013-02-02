--------------------------------------------------------------------------------------------------------
-- Project :			Generic counter test bench
--
-- File:			Generic_Counter_TB.vhd
--
-- Author:			C. BEGUET
--
-- Board:			all
--
-- Device:			all
--
-- Dependencies:		Generic_Counter_c.vhd
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author		Comments
--				1.0	06/05/2009		C. BEGUET		Creation
--
--
--------------------------------------------------------------------------------------------------------
-- Purpose: Test bench for generic counter. Count alternatively up and down from "DATA" value to zero.
--------------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity TB_generic_counter is
	constant period : time:= 15ns;
	constant counter_width : natural:= 5;
end TB_generic_counter;

architecture bench of TB_generic_counter is
	
	component generic_counter is
		generic ( WIDTH : integer := 32);
		port (
			CLK	: in std_logic;		-- Counter clock
			RESET_n	: in std_logic;		-- Asynchronous reset
			ENABLE : in std_logic;		-- Active couting
			DOWN_n: in std_logic;		-- Count DOWN when LOW, count UP when HI
			LOAD	: in std_logic;		-- Synchronous parallel load
			ZERO	: out std_logic;	-- asynchrone zero detection
			DATA	: in  std_logic_vector (counter_width-1 downto 0);	-- Data to load
			Q		: out std_logic_vector (counter_width-1 downto 0));	-- Synchronous counter value output
	end component generic_counter;
	
	signal reset_n, clk_test, DOWN_n, LOAD, ZERO, ENABLE : std_logic;
	signal DATA	: std_logic_vector (counter_width-1 downto 0);	-- Data to load
	signal Q	: std_logic_vector (counter_width-1 downto 0);	-- Synchronous counter value output
	
	begin
		counter:  generic_counter 	generic map( counter_width )
									port map(
											clk_test, reset_n, ENABLE, DOWN_n,
											LOAD, ZERO, DATA, Q);
		horloge : process
			begin
		        clk_test <= '1';
		        wait for 0.5*period;
		        clk_test <= '0';
		        wait for 0.5*period;		
		end process horloge;

		test_counter: process
			begin
				reset_n <= '0';
				ENABLE <= '0';
				DOWN_n <= '0';
				LOAD <= '0';
				DATA <= ('1', '0', others => '1');	-- Reload value
		
				wait for 5*period;
				reset_n <= '1';
				wait for 5*period;
				ENABLE <= '1';				-- Reset and counter activation
				
				while TRUE loop				-- Infinite loop
					wait until ZERO = '1';	-- Zero detection
					wait for 0.1*period;
					LOAD <= '1';			-- Reload counter value
					DOWN_n <= not DOWN_n;	-- Change counter sens
					wait for 0.5*period;
					LOAD <= '0';
				end loop;
				
				wait;
		end process test_counter;

end bench;