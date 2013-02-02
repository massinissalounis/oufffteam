-- Oufffteam
-- Projet carte mère
-- Device: Coder_interface_c.

-- 03/02/2010			CBE			Création

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.pmp_p.all;
use work.quadrature_counter_p.all;

entity Coder_interface is
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
end entity Coder_interface;

architecture wrapper of Coder_interface is
	
	constant Nb_bits_count : natural := 16;
	constant Nb_ff_filter : natural := 2;
	
	signal counter_D_value, counter_G_value : std_logic_vector ( Nb_bits_count-1 downto 0);
	signal counter_latch_sync1, counter_latch_sync2 : std_logic;
	signal latch_register : std_logic_vector ( PMP_DMAX-1 downto 0);
	signal reset_latch_reg : std_logic;
	signal dummy_reg : std_logic_vector ( PMP_DMAX-1 downto 0);
	
	begin

	counter_D: quadrature_counter
		generic map ( 	Nb_bits		=> Nb_bits_count,	-- nombre de bits de sortie
						Nb_bascules	=> Nb_ff_filter		-- bascules d'antiparasites supplementaires si =2, sinon 1
				)
		port map (	Clock 		=> clock,				-- Horloge de référence
					Resetbar	=> reset_n,				-- Reset actif bas du module
					A 			=> coder_D_chanel_A,	-- Canal A du codeur
					B			=> coder_D_chanel_B, 	-- Canal B du codeur
					Count_out 	=> counter_D_value,
					Count_latch	=> counter_latch_sync2
				);
				
	counter_G: quadrature_counter
		generic map ( 	Nb_bits => Nb_bits_count,		-- nombre de bits de sortie
						Nb_bascules => Nb_ff_filter		-- bascules d'antiparasites supplementaires si =2, sinon 1
				)
		port map (	Clock 		=> clock,				-- Horloge de référence
					Resetbar	=> reset_n,				-- Reset actif bas du module
					A 			=> coder_G_chanel_A,	-- Canal A du codeur
					B			=> coder_G_chanel_B, 	-- Canal B du codeur
					Count_out 	=> counter_G_value,
					Count_latch	=> counter_latch_sync2
				);

	-- gestion des latch
	synchro_latch: process (reset_n, clock, latch_register)
		begin
			if (reset_n = '0') then
				counter_latch_sync1	<= '0';
				counter_latch_sync2	<= '0';
				reset_latch_reg <= '0';
			elsif (rising_edge (clock)) then
				counter_latch_sync1	<= latch_register (0);
				counter_latch_sync2	<= counter_latch_sync1;
				if (latch_register(0) = '1') then
					reset_latch_reg <= '1';
				else
					reset_latch_reg <= '0';
				end if;
			end if;
	end process synchro_latch;
	debug_latch	<= counter_latch_sync2;
	
	pmp_write: process (reset_latch_reg, PMP_in)
		begin
			if (reset_latch_reg = '1') then
				latch_register <= (others => '0');
			elsif (PMP_in.PMP_SEL = '1' and PMP_in.PMP_PMWR = '1') then
				case PMP_in.PMP_ADDR (2 downto 0) is
					when "000"	=> latch_register <= PMP_in.PMP_WDATA;
					when "111"	=> latch_register <= dummy_reg;
					when others	=> latch_register <= dummy_reg;
				end case;
			end if;
	end process pmp_write;

	-- sortie PMP
	PMP_out.PMP_RDATA	<=	latch_register	when PMP_in.PMP_ADDR (2 downto 0) = "000" else
							counter_D_value (7 downto 0)		when PMP_in.PMP_ADDR (2 downto 0) = "001" else
							counter_D_value (15 downto 8)	when PMP_in.PMP_ADDR (2 downto 0) = "010" else
							counter_G_value (7 downto 0)		when PMP_in.PMP_ADDR (2 downto 0) = "011" else
							counter_G_value (15 downto 8)	when PMP_in.PMP_ADDR (2 downto 0) = "100" else
							dummy_reg		when PMP_in.PMP_ADDR (2 downto 0) = "101" else
							dummy_reg		when PMP_in.PMP_ADDR (2 downto 0) = "110" else
							dummy_reg		when PMP_in.PMP_ADDR (2 downto 0) = "111";

end architecture wrapper;