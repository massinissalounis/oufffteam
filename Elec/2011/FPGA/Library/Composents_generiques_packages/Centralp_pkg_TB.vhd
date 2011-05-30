--------------------------------------------------------------------------------------------------------
-- Project :			Centralp Package Test bench
--
-- File:			Centralp_pkg_TB.vhd
--
-- Author:			C. BEGUET
--
-- Board:			all
--
-- Device:			all
--
-- Dependencies:		Centralp_pkg_p.vhd
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author		Comments
--				1.0	06/05/2009		C. BEGUET		Creation
--
--
--------------------------------------------------------------------------------------------------------
-- Purpose: Test bench for Centralp package. Test fonctions included in the package
--------------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use work.centralp_pkg.all;

entity TB_centralp_pkg is
	constant factor: integer := 10000000;
end TB_centralp_pkg;

architecture bench of TB_centralp_pkg is

	signal vector : std_logic_vector (number_of_bit_from_max_count (factor) downto 1); -- Test for number_of_bit_from_max_count function

	begin
		process
			begin
			vector <= (others => '1');
			wait for 10ns;
			vector <= (others => '0');
			wait;
		end process;
end bench;