-- Oufffteam
-- Projet carte mère
-- Device: color_register_p

-- 17/04/2010			CBE			Création


library ieee;
use ieee.std_logic_1164.all;

library work;
use work.pmp_p.all;

package color_register_p is
	component color_register is
		port (
			PMP_in		: in PMP_SLV_IN_TYPE;
			PMP_out		: out PMP_SLV_OUT_TYPE;
			color_1		: in std_logic;
			color_2		: in std_logic;
			color_3		: in std_logic
		);
	end component color_register;
 
end color_register_p;
