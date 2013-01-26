-- Oufffteam
-- Projet carte mère
-- Device: PMP

-- 29/12/2009			CBE			Création
-- 20/01/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

library work;
use work.PMP_p.all;

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
		BUS_WR		: out std_logic
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
				elsif (clock'event and clock='1') then
					if (PMP_PMALL = '1') then
						BUS_A_L <= PMP_PMD;
					elsif (PMP_PMALH = '1') then
						BUS_A_H <= PMP_PMD;
					elsif (PMP_PMWR = '1') then
						BUS_D <= PMP_PMD;
					elsif (PMP_PMRD = '1') then
						PMP_PMD <= BUS_D;
					end if;
				end if;
		end process latch;

		BUS_A (7 downto 0)	<= BUS_A_L;
		BUS_A (15 downto 8)	<= BUS_A_H;
		
		BUS_RD <= PMP_PMRD;
		BUS_WR <= PMP_PMWR;
end architecture synchronous;
