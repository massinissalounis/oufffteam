-- Oufffteam
-- Projet carte mère
-- Device: Led register

-- 02/02/2010			CBE			Création

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.pmp_p.all;

entity led_register is
	port (
		PMP_in		: in PMP_SLV_IN_TYPE;
		PMP_out		: out PMP_SLV_OUT_TYPE;
		LED1		: out std_logic;
		LED2		: out std_logic
	);
end entity led_register;

architecture parallel_IO of led_register is
	
	signal led_register : std_logic_vector (7 downto 0);
	
	begin
		pmp_write: process (PMP_in)
			begin
				if (PMP_in.PMP_SEL = '1' and PMP_in.PMP_PMWR = '1') then
				--if (PMP_in.PMP_PMWR = '1') then
					led_register <= PMP_in.PMP_WDATA;
				end if;
		end process pmp_write;
	
	LED1	<= led_register(0);
	LED2	<= led_register(1);
	PMP_out.PMP_RDATA <= led_register;
	
end architecture parallel_IO;