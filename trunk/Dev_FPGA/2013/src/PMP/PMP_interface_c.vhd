-- Oufffteam
-- Projet carte mère
-- Device: PMP

-- 29/12/2009			CBE			Création
-- 20/01/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

library work;
use work.pmp_p.all;

entity PMP_interface is
	port (
		-- in
		clock		: in std_logic
		reset		: in std_logic;
		-- in - PMP
		PMP_PMALH	: in std_logic;
		PMP_PMALL	: in std_logic;
		PMP_PMCS	: in std_logic;
		PMP_PMD		: inout std_logic_vector (7 downto 0);
		PMP_PMRD	: in std_logic;
		PMP_PMWR	: in std_logic;
		-- out
		BUS_D		: inout std_logic_vector (7 downto 0);
		BUS_A		: out std_logic_vector (15 downto 0);
		BUS_RD		: out std_logic;
		BUS_WR		: out std_logic;
		);
end entity PMP_interface;

architecture synchronous of PMP_interface is
	
	signal BUS_A_L	: std_logic_vector (7 downto 0);
	signal BUS_A_H	: std_logic_vector (7 downto 0);
	
	begin
		latch: process (reset, clock)
			begin
				if (reset = '1') then
					BUS_A_L	<= (others => '0');
					BUS_A_H <= (others => '0');
					BUS_D <= (others => '0');
					BUS_RD <= '0';
					BUS_WR <= '0';
					data
				elsif (Clock'event and Clock='1') then
					if (PMP_PMALL = '1') then
						pmp_address (7 downto 0) <= PMP_PMD;
					elsif (PMP_PMALH = '1') then
						pmp_address (15 downto 8) <= PMP_PMD;
					end if;
				end if;
		end process latch_address;

		BUS_A (7 downto 0)	<= BUS_A_L;
		BUS_A (15 downto 8)	<= BUS_A_H;
		
		
		
		
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
		BUS_RD <= PMP_PMRD;
		BUS_
		
		
end architecture synchronous;
