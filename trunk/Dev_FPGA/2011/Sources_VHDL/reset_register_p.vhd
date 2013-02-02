-- Oufffteam
-- Projet carte mère
-- Device: reset_register_p

-- 13/02/2010			CBE			Création


library ieee;
use ieee.std_logic_1164.all;

library work;
use work.pmp_p.all;

package reset_register_p is
 
	component reset_register is
		port (
			PMP_in		: in PMP_SLV_IN_TYPE;
			PMP_out		: out PMP_SLV_OUT_TYPE;
			reset		: out std_logic;
			reset_n		: out std_logic
		);
	end component reset_register;
 
end reset_register_p;
