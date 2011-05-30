-- Oufffteam
-- Projet carte mère
-- Device: gpio_register_p

-- 17/04/2010			CBE			Création


library ieee;
use ieee.std_logic_1164.all;

library work;
use work.pmp_p.all;

package gpio_register_p is
 
	component gpio_register is
	generic ( nb_GPIO : natural := 1);
	port (
		PMP_in		: in PMP_SLV_IN_TYPE;
		PMP_out		: out PMP_SLV_OUT_TYPE;
		gpio_out	: out std_logic_vector (nb_GPIO - 1 downto 0);
		gpio_out_en	: out std_logic_vector (nb_GPIO - 1 downto 0);
		gpio_in		: in std_logic_vector (nb_GPIO - 1 downto 0)
	);
	end component gpio_register;
 
end gpio_register_p;
