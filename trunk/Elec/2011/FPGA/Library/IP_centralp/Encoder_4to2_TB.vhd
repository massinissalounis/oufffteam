--------------------------------------------------------------------------------------------------------
-- Project :			Encoder 4 input to 2 bits Test bench
--
-- File:			Encoder_4to2_TB.vhd
--
-- Author:			C. BEGUET
--
-- Board:			all
--
-- Device:			all
--
-- Dependencies:		Encoder_4to2_c.vhd
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author		Comments
--				1.0	06/05/2009		C. BEGUET		Creation
--
--
--------------------------------------------------------------------------------------------------------
-- Purpose: Test bench for 4 to 2 encoder. Test all codes and priority.
--------------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity TB_encoder_4to2 is
	constant period : time := 100ns;
end TB_encoder_4to2;

architecture TB_ARCHITECTURE of TB_encoder_4to2 is

	component encoder_4to2
		port(
			signal_input : in STD_LOGIC_VECTOR(3 downto 0);
			coded_output : out STD_LOGIC_VECTOR(1 downto 0) );
	end component;

	signal signal_input : STD_LOGIC_VECTOR(3 downto 0);
	signal coded_output : STD_LOGIC_VECTOR(1 downto 0);

	begin
		-- Unit Under Test port map
		UUT : encoder_4to2
			port map (
				signal_input => signal_input,
				coded_output => coded_output
			);
		process		-- Change input state
			begin
				signal_input <= (others => '0');
				wait for 2*period;
				while true loop
					signal_input <= signal_input + 1;
					wait for 2*period;
				end loop;
		end process;

end TB_ARCHITECTURE;


