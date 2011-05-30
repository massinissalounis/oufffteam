--------------------------------------------------------------------------------------------------------
-- Project :			Generic demultiplexor
--
-- File:			Generic_Deux_c.vhd
--
-- Author:			C. BEGUET
--
-- Board:			all
--
-- Device:			all
--
-- Dependencies:		centralp_pkg_p.vhd
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author		Comments
--				1.0	06/05/2009		C. BEGUET		Creation
--
--
--------------------------------------------------------------------------------------------------------
-- Purpose: Demultiplexor with variable input width (generic input), and default value for unselected output.
--------------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;
use work.centralp_pkg.all;

entity generic_demux is
	generic ( output_length : natural := 2 );
	port ( 	muxin  :  in  std_logic;										-- 1 input
			muxout :  out std_logic_vector(output_length - 1  downto 0);	-- n output
			default_out : in std_logic;										-- default output value if output not selected
			sel    :  in  std_logic_vector(number_of_bit_from_max_count(output_length)-1 downto 0)	-- input selection
			);
end generic_demux;

architecture asynchrone_switching of generic_demux is
	begin
		output_control: for I in 0 to output_length-1 generate -- Generate automaticaly n output control
			begin
				muxout (I) <=
					muxin when (conv_integer(sel) = I) else		-- Output = input when selected
					default_out;								-- Output = default output when not selected
		end generate output_control;
end asynchrone_switching;
