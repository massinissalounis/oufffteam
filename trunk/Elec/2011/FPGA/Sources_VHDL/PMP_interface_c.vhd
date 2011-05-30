-- Oufffteam
-- Projet carte mère
-- Device: PMP

-- 29/12/2009			CBE			Création

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

library work;
use work.pmp_p.all;


entity PMP_interface is
	generic ( slave_number : natural := 2);
	port (
		clock		: in std_logic;
		reset		: in std_logic;
		-- PMP
		PMP_PMALH	: in std_logic;
		PMP_PMALL	: in std_logic;
		PMP_PMCS	: in std_logic;
		PMP_PMD		: inout std_logic_vector (7 downto 0);
		PMP_PMRD	: in std_logic;
		PMP_PMWR	: in std_logic;
		
		-- external CS decode
		CS_input	: in std_logic_vector (slave_number - 1 downto 0);
		Address		: out std_logic_vector (15 downto 0);
		--internal PMP
		From_slave	: in PMP_SLV_OUT_VECTOR (slave_number - 1 downto 0);
		To_slave	: out PMP_SLV_IN_VECTOR (slave_number - 1 downto 0)		
		);
end entity PMP_interface;

architecture synchronous of PMP_interface is

	type DATA_VECTOR is array (natural range <> ) of std_logic_vector (7 downto 0);
	
	signal data_to_pmp	: DATA_VECTOR (slave_number - 1 downto 0);
	signal pmp_address	: std_logic_vector (15 downto 0);
	signal internal_CS	: std_logic_vector (slave_number - 1 downto 0);
	
	begin
		-- latch_address: process (reset, clock)
			-- begin
				-- if (reset = '1') then
					-- pmp_address	<= (others => '0');
				-- elsif (rising_edge (clock)) then
					-- if (PMP_PMALL = '1') then
						-- pmp_address (7 downto 0) <= PMP_PMD;
					-- elsif (PMP_PMALH = '1') then
						-- pmp_address (15 downto 8) <= PMP_PMD;
					-- end if;
				-- end if;
		-- end process latch_address;

		pmp_address (7 downto 0)	<= PMP_PMD when (PMP_PMALL = '1') else pmp_address (7 downto 0);
		pmp_address (15 downto 8)	<= PMP_PMD when (PMP_PMALH = '1') else pmp_address (15 downto 8);
		
		Address	<= pmp_address;
		internal_CS	<= CS_input;
	
		-- To_slave generation
		To_slave_gen: for N in 0 to slave_number - 1 generate
			begin
				To_slave(N).PMP_SEL		<= internal_CS(N) when PMP_PMCS = '1' else '0';
				To_slave(N).PMP_PMRD	<= PMP_PMRD;
				To_slave(N).PMP_PMWR	<= PMP_PMWR;
				To_slave(N).PMP_ADDR	<= pmp_address;
				To_slave(N).PMP_WDATA	<= PMP_PMD;
		end generate To_slave_gen;
	
	
		-- Gestion du bus de données
		data_to_pmp(0) <= From_slave(0).PMP_RDATA when internal_CS(0)='1' else (others => '1');
		output_mux: for N in 1 to slave_number - 1 generate
			begin
				data_to_pmp(N) <= From_slave(N).PMP_RDATA when internal_CS(N)='1' else data_to_pmp(N-1);
			end generate output_mux;
		-- Buffer de sortie
		PMP_PMD	<=	data_to_pmp(slave_number - 1)	when (PMP_PMRD = '1' and PMP_PMCS = '1') else
					(others => 'Z');
		
		
		
end architecture synchronous;
