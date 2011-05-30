--------------------------------------------------------------------------------------------------------
-- Project :			Generic multiplexor
--
-- File:			Generic_Mux_c.vhd
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
-- Purpose: Multiplexor with variable input width (generic input).
--------------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;
use work.centralp_pkg.all;

entity generic_mux is
	generic ( input_length : natural := 2 );
	port ( 	muxin  :  in  std_logic_vector(input_length - 1  downto 0);		-- n input
			muxout :  out std_logic;										-- 1 output
			sel    :  in  std_logic_vector(number_of_bit_from_max_count(input_length)-1 downto 0)	-- input selection
			);
end generic_mux;

architecture asynchrone_switching of generic_mux is
	begin
		muxout <= muxin(conv_integer(sel));
end asynchrone_switching;