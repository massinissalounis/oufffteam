--------------------------------------------------------------------------------------------------------
-- Project :			Centralp Package
--
-- File:			Centralp_pkg_p.vhd
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
-- Purpose: Package with usefull functions for Centralp Automatismes
-- Content:	* functions
--	number_of_bit_from_max_count
--
--		* types
--	...
--------------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

package centralp_pkg is

	-- Fonction qui retourne le nombre de bit qu'un compteur doit avoir pour compter jusqu'à max_count
	function number_of_bit_from_max_count (max_count : integer) return integer;

end centralp_pkg;

package body centralp_pkg is
	
	-- Fonction qui retourne le nombre de bit qu'un compteur doit avoir pour compter jusqu'à max_count
	function number_of_bit_from_max_count (max_count : integer) return integer is
		variable number_of_bit : integer range 1 to integer'high;
		begin
			for i in 1 to integer'high loop
				if ( (2 ** i) >= max_count ) then
					number_of_bit := i;
					exit;
				end if;
			end loop;
		return number_of_bit;
	end number_of_bit_from_max_count;
	
end centralp_pkg;

