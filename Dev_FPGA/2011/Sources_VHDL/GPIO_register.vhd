-- Oufffteam
-- Projet carte mère
-- Device: GPIO_register

-- 13/02/2010			CBE			Création

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.pmp_p.all;

entity gpio_register is
	generic ( nb_GPIO : natural := 1);
	port (
		PMP_in		: in PMP_SLV_IN_TYPE;
		PMP_out		: out PMP_SLV_OUT_TYPE;
		gpio_out	: out std_logic_vector (nb_GPIO - 1 downto 0);
		gpio_out_en	: out std_logic_vector (nb_GPIO - 1 downto 0);
		gpio_in		: in std_logic_vector (nb_GPIO - 1 downto 0)
	);
end entity gpio_register;

architecture parallel_IO of gpio_register is
	
	signal gpio_register : std_logic_vector (7 downto 0);
	
	begin
		
		-- Mappage pour lecture de la couleur.
		PMP_out.PMP_RDATA (nb_GPIO - 1 downto 0)	<= gpio_in (nb_GPIO - 1 downto 0);
		PMP_out.PMP_RDATA (7 downto nb_GPIO) 		<= (others => '0');
		gpio_out_en	<=	"0";
		gpio_out	<=	"0";
		
end architecture parallel_IO;