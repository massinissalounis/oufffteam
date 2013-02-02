-- Oufffteam
-- Projet carte mère
-- Device: Coder_interface_p

-- 13/02/2010			CBE			Création


library ieee;
use ieee.std_logic_1164.all;

library work;
use work.pmp_p.all;

package Coder_interface_p is
 
	component Coder_interface is
		port (
			clock			: in std_logic;
			reset_n			: in std_logic;
			debug_latch		: out std_logic;
			--pmp
			PMP_in			: in PMP_SLV_IN_TYPE;
			PMP_out			: out PMP_SLV_OUT_TYPE;
			-- coder
			coder_D_chanel_A	: in std_logic;
			coder_D_chanel_B	: in std_logic;
			coder_G_chanel_A	: in std_logic;
			coder_G_chanel_B	: in std_logic
		);
	end component Coder_interface;

end Coder_interface_p;
