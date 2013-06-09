-- Oufffteam
-- Projet carte m�re
-- Device: PMP

-- 29/12/2009			CBE			Cr�ation
-- 20/01/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

library work;
use work.PMP_p.all;

entity PMP_interface is
	port (
		-- in
		clock		: in std_logic;
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
	
	attribute TIG : string;
	attribute ASYNC_REG : string;
	
	attribute TIG of PMP_PMALH, PMP_PMALL, PMP_PMCS, PMP_PMD, PMP_PMRD, PMP_PMWR : signal is "TRUE";
	attribute ASYNC_REG of BUS_D, BUS_A_L, BUS_A_H, BUS_RD, BUS_WR : signal is "TRUE";
	
	begin
		latch: process (reset, clock)
			begin
				if (reset = '1') then
					BUS_A_L	<= (others => '1');
					BUS_A_H <= (others => '1');
					BUS_D <= (others => '0');
					PMP_PMD <= (others => 'Z');
				elsif (clock'event and clock='1') then
					if (PMP_PMALL = '1') then
						BUS_A_L <= PMP_PMD;
					  PMP_PMD <= (others => 'Z');
					elsif (PMP_PMALH = '1') then
						BUS_A_H <= PMP_PMD;
						PMP_PMD <= (others => 'Z');
					elsif (PMP_PMWR = '1') then
						BUS_D <= PMP_PMD;
						PMP_PMD <= (others => 'Z');
					elsif (PMP_PMRD = '1') then
						PMP_PMD <= BUS_D;
						BUS_D <= (others => 'Z');
					else
						PMP_PMD <= (others => 'Z');
						BUS_D <= (others => 'Z');					      
				  end if;
				end if;
		  end process latch;

		BUS_A (7 downto 0)	<= BUS_A_L;
		BUS_A (15 downto 8)	<= BUS_A_H;
		
		latch_control_sig: process (reset, clock)
			begin
				if (reset = '1') then
					BUS_RD	<= '0';
					BUS_WR <= '0';
				elsif (clock'event and clock='0') then
					BUS_RD <= PMP_PMRD;
					BUS_WR <= PMP_PMWR;
				end if;
		  end process latch_control_sig;
		
end architecture synchronous;

architecture semi_synchronous of PMP_interface is
	
	signal BUS_A_L	: std_logic_vector (7 downto 0);
	signal BUS_A_H	: std_logic_vector (7 downto 0);
	
	begin
		latch_data: process (reset, clock)
			begin
				if (reset = '1') then
					BUS_D <= (others => '0');
					PMP_PMD <= (others => 'Z');
				elsif (clock'event and clock='1') then
					if (PMP_PMWR = '1') then
						BUS_D <= PMP_PMD;
						PMP_PMD <= (others => 'Z');
					elsif (PMP_PMRD = '1') then
						PMP_PMD <= BUS_D;
						BUS_D <= (others => 'Z');
					else
						PMP_PMD <= (others => 'Z');
						BUS_D <= (others => 'Z');					      
				  end if;
				end if;
		  end process latch_data;
		  
		latch_address: process(reset, PMP_PMALH, PMP_PMALL)
			begin
				if (reset='1') then
					BUS_A_L <= (others =>'1');
					BUS_A_H <= (others =>'1');
				elsif (PMP_PMALL ='1') then
					BUS_A_L <= PMP_PMD;
				elsif (PMP_PMALH ='1') then
					BUS_A_H <= PMP_PMD;
				end if;
		end process latch_address;
		
		BUS_A (7 downto 0)	<= BUS_A_L;
		BUS_A (15 downto 8)	<= BUS_A_H;
		
		BUS_RD <= PMP_PMRD;
		BUS_WR <= PMP_PMWR;
end architecture semi_synchronous;
