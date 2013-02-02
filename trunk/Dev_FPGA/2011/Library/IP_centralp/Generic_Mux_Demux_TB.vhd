--------------------------------------------------------------------------------------------------------
-- Project :			Generic multiplexor Test bench
--
-- File:			Generic_Mux_Demux_TB.vhd
--
-- Author:			C. BEGUET
--
-- Board:			all
--
-- Device:			all
--
-- Dependencies:		centralp_pkg_p.vhd
--				Generic_Mux_c.vhd
--				Generic_Demux_c.vhd
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author		Comments
--				1.0	06/05/2009		C. BEGUET		Creation
--
--
--------------------------------------------------------------------------------------------------------
-- Purpose: Test bench for generic multiplexor and demultiplexor.
--------------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;
use work.centralp_pkg.all;

entity test_generic_mux is
    constant period : time:= 15ns;
	constant nombre_signaux_mux : natural := 3;
	constant temps_entre_switch : time := 100ns;
end test_generic_mux;

architecture bench of test_generic_mux is 

	component generic_mux is
		generic ( input_length : integer := 2 );
		port ( 	muxin  :  in  std_logic_vector(input_length - 1  downto 0);		-- n input
				muxout :  out std_logic;										-- 1 output
				sel    :  in  std_logic_vector(number_of_bit_from_max_count(input_length) downto 0)	-- input selection
				);
	end component generic_mux;

	component generic_demux is
		generic ( output_length : integer := 2 );
		port ( 	muxin  :  in  std_logic;										-- 1 input
				muxout :  out std_logic_vector(output_length - 1  downto 0);	-- n output
				default_out : in std_logic;										-- default output value if output not selected
				sel    :  in  std_logic_vector(number_of_bit_from_max_count(output_length) downto 0)	-- input selection
				);
	end component generic_demux;
		
	signal clk_test : std_logic;
	signal output_test: std_logic;
	signal inter_mux : std_logic_vector(nombre_signaux_mux - 1  downto 0 );
	signal selection : std_logic_vector(number_of_bit_from_max_count(nombre_signaux_mux) downto 0);
	
	begin
		-- instentiation composants
		demux: generic_mux	generic map ( nombre_signaux_mux )
							port map ( inter_mux, output_test, selection);
								
		mux: generic_demux 	generic map ( nombre_signaux_mux )
							port map ( clk_test, inter_mux, '0', selection);
		
		horloge : process
			begin
		        clk_test <= '1';
		        wait for period;
		        clk_test <= '0';
		        wait for period;		
			end process horloge;

		test: process
			begin
				selection <= (others => '0');
				for n in 0 to nombre_signaux_mux - 1 loop
					wait for temps_entre_switch;
					selection <= selection + 1;
					if (conv_integer (selection) > nombre_signaux_mux) then
						selection <= (others => '0');
					end if;
				end loop;
		end process test;
end bench;