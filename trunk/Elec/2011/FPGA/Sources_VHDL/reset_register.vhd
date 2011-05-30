-- Oufffteam
-- Projet carte mère
-- Device: reset_register

-- 13/02/2010			CBE			Création

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.pmp_p.all;

entity reset_register is
	port (
		PMP_in		: in PMP_SLV_IN_TYPE;
		PMP_out		: out PMP_SLV_OUT_TYPE;
		reset		: out std_logic;
		reset_n		: out std_logic
	);
end entity reset_register;

architecture parallel_IO of reset_register is
	
	signal reset_register : std_logic_vector (7 downto 0);
	
	begin
		pmp_write: process (PMP_in)
			begin
				if (PMP_in.PMP_SEL = '1' and PMP_in.PMP_PMWR = '1') then
				--if (PMP_in.PMP_PMWR = '1') then
					reset_register <= PMP_in.PMP_WDATA;
				end if;
		end process pmp_write;
	
	reset	<= '1' when reset_register = X"FF" else '0';
	reset_n	<= '0' when reset_register = X"FF" else '1';
	PMP_out.PMP_RDATA <= reset_register;

end architecture parallel_IO;