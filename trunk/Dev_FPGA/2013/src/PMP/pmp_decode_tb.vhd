-- Oufffteam
-- Projet carte mère
-- Device: pmp testbench

-- 29/12/2009			CBE			Création

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;


entity tb_pmp is
	begin
end entity tb_pmp;

architecture arch_tb_pmp of tb_pmp is

	component PMP_interface is
		generic ( cs_number : natural);
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
			internal_CS	: out std_logic_vector (cs_number - 1 downto 0)
			);
	end component PMP_interface;
	
	constant period: time := 50 ns;
	constant cs_number: integer := 10;
	signal clock:		std_logic;
	signal reset:		std_logic;
				-- PMP
	signal PMP_PMALH:	std_logic;
	signal PMP_PMALL:	std_logic;
	signal PMP_PMCS:	std_logic;
	signal PMP_PMD:		std_logic_vector (7 downto 0);
	signal PMP_PMRD:	std_logic;
	signal PMP_PMWR:	std_logic;
	signal internal_CS: std_logic_vector (cs_number - 1 downto 0);
	signal counter:		std_logic_vector (15 downto 0);
	
	begin
	
		main_clock: process
			begin
				clock <= '0';
				wait for period / 2;
				clock <= '1';
				wait for period / 2;
		end process main_clock;
		
		test: process
			begin
				reset <= '1';
				PMP_PMALH	<= '0';
				PMP_PMALL	<= '0';
				PMP_PMCS	<= '0';
				PMP_PMD		<= X"00";
				PMP_PMRD	<= '0';
				PMP_PMWR	<= '0';
				counter		<= (others => '0');
				wait for 2*period;
				reset <= '0';
				wait for 2*period;
				--set address
				PMP_PMD		<= X"00";
				wait for 10*period;
				PMP_PMALL	<= '1';
				wait for 10*period;
				PMP_PMALL	<= '0';
				wait for 10*period;
				PMP_PMALH	<= '1';
				wait for 10*period;
				PMP_PMALH	<= '0';
				
				loop1: FOR a IN 1 TO 15 LOOP -- la variable de boucle est a de 1 à 10
					PMP_PMD		<= counter (7 downto 0);
					wait for 1*period;
					PMP_PMALL	<= '1';
					wait for 10*period;
					PMP_PMALL	<= '0';
					wait for 10*period;
					PMP_PMD		<= counter (15 downto 8);
					wait for 1*period;
					PMP_PMALH	<= '1';
					wait for 10*period;
					PMP_PMALH	<= '0';
					wait for 10*period;
					counter		<= counter + 1;
				end loop;
				
				wait;
		end process test;
	
		dut: PMP_interface
			generic map ( cs_number => cs_number)
			port map (
				clock			=> clock,
				reset			=> reset,
				-- PMP
				PMP_PMALH		=> PMP_PMALH,
				PMP_PMALL		=> PMP_PMALL,
				PMP_PMCS		=> PMP_PMCS,
				PMP_PMD			=> PMP_PMD,
				PMP_PMRD		=> PMP_PMRD,
				PMP_PMWR		=> PMP_PMWR,
				internal_CS		=> internal_CS
				);
	
end architecture arch_tb_pmp;
