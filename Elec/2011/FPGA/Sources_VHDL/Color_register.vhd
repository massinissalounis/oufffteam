-- Oufffteam
-- Projet carte mère
-- Device: color_register

-- 31/05/2011			CBE			Création

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.pmp_p.all;

entity color_register is
	port (
		PMP_in		: in PMP_SLV_IN_TYPE;
		PMP_out		: out PMP_SLV_OUT_TYPE;
		color_1		: in std_logic;
		color_2		: in std_logic;
		color_3		: in std_logic
	);
end entity color_register;

architecture parallel_I of color_register is

	begin		
		-- Mappage pour lecture de la couleur.
		PMP_out.PMP_RDATA (0)	<= color_1;
		PMP_out.PMP_RDATA (1)	<= color_2;
		PMP_out.PMP_RDATA (2)	<= color_3;
		PMP_out.PMP_RDATA (7 downto 3) 	<= (others => '0');
		
end architecture parallel_I;