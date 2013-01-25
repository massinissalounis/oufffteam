-- Oufffteam
-- Projet carte mère
-- Device: led_register_p

-- 02/02/2010			CBE			Création


library ieee;
use ieee.std_logic_1164.all;

library work;
use work.pmp_p.all;

package led_register_p is
 
	component led_register is
		port (
			PMP_in		: in PMP_SLV_IN_TYPE;
			PMP_out		: out PMP_SLV_OUT_TYPE;
			LED1		: out std_logic;
			LED2		: out std_logic
		);
	end component led_register;
 
end led_register_p;
