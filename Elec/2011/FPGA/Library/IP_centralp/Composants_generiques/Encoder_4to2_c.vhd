--------------------------------------------------------------------------------------------------------
-- Project :			Encoder 4 input to 2 bits
--
-- File:			Encoder_4to2_c.vhd
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
-- Purpose: 4 input to 2 bits binary encoder. Encode the number of the active input line (from 0 to 3) on the output binary word.
-- When more than one input is active, output indicate the highest input number(in the std_logic_vector).
-- Default output value (when no input is active) is "00".
--------------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;   

entity Encoder_4to2 is
	port (
		signal_input : in std_logic_vector ( 3 downto 0);
		coded_output : out std_logic_vector ( 1 downto 0)
		);
end Encoder_4to2;

architecture asynchronous of Encoder_4to2 is

	begin
	process (signal_input)
		begin
			if 	  (signal_input(3) = '1') then coded_output <= "11";
			elsif (signal_input(2) = '1') then coded_output <= "10";
			elsif (signal_input(1) = '1') then coded_output <= "01";
			elsif (signal_input(0) = '1') then coded_output <= "00";
			else coded_output <= "00";
			end if;
	end process;
end asynchronous;