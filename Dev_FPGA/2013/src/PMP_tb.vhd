
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library work;

entity PMP_TB is
end entity PMP_TB;

architecture testbench of PMP_TB is

	constant period_PIC_TPB		: time := 12.5 ns; 	-- 80 MHz //TO update !!!
	constant period_FPGA		: time := 20 ns ;  	-- 50 MHz
	
	-- paramètres du bus PMP réglables dans le microcontrôleur (en nombre de fronts de fclk)
	constant WAITB	: integer := 2; -- 1 to 3
	constant WAITM	: integer := 2; -- 1 to 15
	constant WAITE	: integer := 2; -- 0 to 3

	
	-- Addresse des IP esclaves (Début de la plage d'adressage) 
	constant Address_LED		: std_logic_vector (15 downto 0)	:= X"0000";
	
	procedure pmp_wait_states (
		signal fPB			: in std_logic;
		signal wait_states	: in integer
		) is
		begin
			loop1: FOR i IN wait_states DONWTO 0 LOOP
				wait until rising_edge (fPB);
			END LOOP loop1;
	end procedure pmp_wait_states;
	
	procedure pmp_read_access (
		signal fPB			: in std_logic;
		signal address	 		: in std_logic_vector (15 downto 0);
		signal PMDIN			: inout std_logic_vector (7 downto 0);
		signal PMD			: inout std_logic_vector (7 downto 0);
		signal PMALL			: out std_logic;
		signal PMALH			: out std_logic;
		signal PMRD			: out std_logic;
		signal PMWR			: out std_logic
		) is
		variable counter: integer;
		begin
			PMALL <= '0'; PMALH <= '0'; PMRD <= '0'; PMWR <= '0';
			wait until rising_edge (fPB);
			PMD <= address(7:0);
			wait until rising_edge (fPB);
			PMALL <= '1';
			pmp_wait_states(fPB, WAITB);
			PMALL <='0';
			wait until rising_edge (fPB);			
			PMD <= address(15:8);
			pmp_wait_states(fPB, WAITB);
			PMALH <= '1';
			wait until rising_edge (fPB);
			PMALH <='0';			
			wait until rising_edge (fPB);
			PMD <= (others => 'Z');
			pmp_wait_states(fPB, WAITB);
			PMRD <= '1';
			pmp_wait_states(fPB, WAITM);
			PMRD <= '0';
			PMDIN <= PMD;
			pmp_wait_states(fPB, WAITE);			
	end procedure pmp_read_access;
	
	procedure pmp_write_access (
		signal fPB			: in std_logic;
		signal address	 		: in std_logic_vector (15 downto 0);
		signal PMDIN			: inout std_logic_vector (7 downto 0);
		signal PMD			: inout std_logic_vector (7 downto 0);
		signal PMALL			: out std_logic;
		signal PMALH			: out std_logic;
		signal PMRD			: out std_logic;
		signal PMWR			: out std_logic
		) is
		variable counter: integer;
		begin
			PMALL <= '0'; PMALH <= '0'; PMRD <= '0'; PMWR <= '0';
			wait until rising_edge (fPB);
			PMD <= address(7:0);
			wait until rising_edge (fPB);
			PMALL <= '1';
			pmp_wait_states(fPB, WAITB);
			PMALL <='0';
			wait until rising_edge (fPB);			
			PMD <= address(15:8);
			pmp_wait_states(fPB, WAITB);
			PMALH <= '1';
			wait until rising_edge (fPB);
			PMALH <='0';			
			wait until rising_edge (fPB);
			PMD <= PMDIN;
			pmp_wait_states(fPB, WAITB);
			PMWR <= '1';
			pmp_wait_states(fPB, WAITM);
			PMWR <= '0';
			pmp_wait_states(fPB, WAITE);			
	end procedure pmp_write_access;
	
	component FPGA_Oufff is
	port (
		FPGA_CLK			: in std_logic;
		FPGA_RESET		: in std_logic;
		PIC_INT1			: out std_logic;
		-- GPIO
		FPGA_GPIO_0		: inout std_logic;
		FPGA_GPIO_1		: inout std_logic;
		FPGA_GPIO_2		: inout std_logic;
		FPGA_GPIO_3		: inout std_logic;
		FPGA_GPIO_4		: inout std_logic;
		FPGA_GPIO_5		: inout std_logic;
		FPGA_GPIO_6		: inout std_logic;
		FPGA_GPIO_7		: inout std_logic;
		FPGA_GPIO_8		: inout std_logic;
		FPGA_GPIO_9		: inout std_logic;
		-- Codeurs
		FPGA_PHA1		: in std_logic;
		FPGA_PHB1		: in std_logic;
		FPGA_PHA2		: in std_logic;
		FPGA_PHB2		: in std_logic;
		FPGA_PHA3		: in std_logic;
		FPGA_PHB3		: in std_logic;
		FPGA_PHA4		: in std_logic;
		FPGA_PHB4		: in std_logic;
		-- Servomoteurs
		FPGA_SERVO_0		: out std_logic;
		FPGA_SERVO_1		: in std_logic;
		FPGA_SERVO_2		: in std_logic;
		FPGA_SERVO_3		: in std_logic;
		FPGA_SERVO_4		: out std_logic;
		FPGA_SERVO_5		: out std_logic;
		FPGA_SERVO_6		: out std_logic;
		FPGA_SERVO_7		: out std_logic;;
		FPGA_SERVO_8		: out std_logic;
		FPGA_SERVO_9		: out std_logic;
		-- PMP
		PIC_PMP_PMALH		: in std_logic;
		PIC_PMP_PMALL		: in std_logic;
		PIC_PMP_PMCS2		: in std_logic;
		PIC_PMP_PMD		: inout std_logic_vector (7 downto 0);
		PIC_PMP_PMRD		: in std_logic;
		PIC_PMP_PMWR		: in std_logic;
		-- Led
		LED1			: out std_logic;
		LED2			: out std_logic;
                );
end component FPGA_Oufff;
	

-- Global signals
	signal FPGA_CLK		: std_logic;
	signal PIC_PB_CLK	: std_logic;
	signal RESET		: std_logic;

-- PIC signals
	signal PIC_ADDR		: std_logic_vector (15 downto 0);
	signal PIC_PMDIN		: std_logic_vector (7 downto 0);

-- PMP interface
	signal PIC_PMP_PMALH	: std_logic;
	signal PIC_PMP_PMALL	: std_logic;
	signal PIC_PMP_PMCS2	: std_logic;
	signal PIC_PMP_PMD	: std_logic_vector (7 downto 0);
	signal PIC_PMP_PMRD	: std_logic;
	signal PIC_PMP_PMWR	: std_logic;
	signal PIC_INT1		: std_logic;

-- FPGA signals
	-- GPIO
	signal FPGA_GPIO_0	: std_logic;
	signal FPGA_GPIO_1	: std_logic;
	signal FPGA_GPIO_2	: std_logic;
	signal FPGA_GPIO_3	: std_logic;
	signal FPGA_GPIO_4	: std_logic;
	signal FPGA_GPIO_5	: std_logic;
	signal FPGA_GPIO_6	: std_logic;
	signal FPGA_GPIO_7	: std_logic;
	signal FPGA_GPIO_8	: std_logic;
	signal FPGA_GPIO_9	: std_logic;

	-- Codeurs
	signal FPGA_PHA1		: std_logic;
	signal FPGA_PHB1		: std_logic;
	signal FPGA_PHA2		: std_logic;
	signal FPGA_PHB2		: std_logic;
	signal FPGA_PHA3		: std_logic;
	signal FPGA_PHB3		: std_logic;
	signal FPGA_PHA4		: std_logic;
	signal FPGA_PHB4		: std_logic;

	-- Servomoteurs
	signal FPGA_SERVO_0	: std_logic;
	signal FPGA_SERVO_1	: std_logic;
	signal FPGA_SERVO_2	: std_logic;
	signal FPGA_SERVO_3	: std_logic;
	signal FPGA_SERVO_4	: std_logic;
	signal FPGA_SERVO_5	: std_logic;
	signal FPGA_SERVO_6	: std_logic;
	signal FPGA_SERVO_7	: std_logic;
	signal FPGA_SERVO_8	: std_logic;
	signal FPGA_SERVO_9	: std_logic;

	-- Led
	signal LED1		: std_logic;
	signal LED2		: std_logic;

	begin	
		PICclk: process
		begin
			loop
				PIC_PB_CLK <= '0';
				wait for period_PIC_TPB/2;
				PIC_PB_CLK <= '1';
				wait for period_PIC_TPB/2;
			end loop;
		end process;
	
		FPGAclk: process
		begin
			loop
				FPGA_CLK <= '0';
				wait for period_FPGA/2;
				FPGA_CLK <= '1';
				wait for period_FPGA/2;
			end loop;
		end process;
		
		main_tb: process
		begin
			RESET 		<= '1';
			
			PIC_PMP_PMALH	<= '0';
			PIC_PMP_PMALL	<= '0';
			PIC_PMP_PMCS2	<= '0';
			PIC_PMP_PMRD	<= '0';
			PIC_PMP_PMWR	<= '0';
			PIC_PMP_PMD	<= (others => 'Z');
			
			FPGA_PHA1	<= '0';
			FPGA_PHB1	<= '0';
			FPGA_PHA2	<= '0';
			FPGA_PHB2	<= '0';
			FPGA_PHA3	<= '0';
			FPGA_PHB3	<= '0';
			FPGA_PHA4	<= '0';
			FPGA_PHB4	<= '0';
			
			FPGA_GPIO_0	<= '0';
			FPGA_GPIO_1	<= '0';
			FPGA_GPIO_2	<= '0';
			FPGA_GPIO_3	<= '0';
			FPGA_GPIO_4	<= '0';
			FPGA_GPIO_5	<= '0';
			FPGA_GPIO_6	<= '0';
			FPGA_GPIO_7	<= '0';
			FPGA_GPIO_8	<= '0';
			FPGA_GPIO_9	<= '0';

			FPGA_SERVO_1	<= '0';
			FPGA_SERVO_2	<= '0';
			FPGA_SERVO_3	<= '0';
		
		---- Test RESET ----
			assert false report ("Test RESET") severity note;
			wait for 1 us;
			RESET <= '1';
			wait for 1 us;
			RESET <= '0';
			-- DO AN FPGA RESET

		---- Test LED ----
			assert false report ("Test LED") severity note;
			
			PIC_ADDR <= Adress_LED;
			PIC_PMDIN <=  X"01"; -- LED1 On
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_PMDIN <=  X"00"; -- Look at the data back
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
		---- Fin du Test----
			assert false report ("Fin Test") severity note;
			wait;
		end process;
			
		DUT: FPGA_Oufff
			port map(
				FPGA_CLK		=> FPGA_CLK,
				FPGA_RESET	=> RESET,
				PIC_INT1		=> PIC_INT1,
				
				FPGA_GPIO_0	=> FPGA_GPIO_0,
				FPGA_GPIO_1	=> FPGA_GPIO_1,
				FPGA_GPIO_2	=> FPGA_GPIO_2,
				FPGA_GPIO_3	=> FPGA_GPIO_3,
				FPGA_GPIO_4	=> FPGA_GPIO_4,
				FPGA_GPIO_5	=> FPGA_GPIO_5,
				FPGA_GPIO_6	=> FPGA_GPIO_6,
				FPGA_GPIO_7	=> FPGA_GPIO_7,
				FPGA_GPIO_8	=> FPGA_GPIO_8,
				FPGA_GPIO_9	=> FPGA_GPIO_9,
				
				FPGA_PHA1	=> FPGA_PHA1,
				FPGA_PHB1	=> FPGA_PHB1,
				FPGA_PHA2	=> FPGA_PHA2,
				FPGA_PHB2	=> FPGA_PHB2,
				FPGA_PHA3	=> FPGA_PHA3,
				FPGA_PHB3	=> FPGA_PHB3,
				FPGA_PHA4	=> FPGA_PHA4,
				FPGA_PHB4	=> FPGA_PHB4,

				FPGA_SERVO_0	=> FPGA_SERVO_0,
				FPGA_SERVO_1	=> FPGA_SERVO_1,
				FPGA_SERVO_2	=> FPGA_SERVO_2,
				FPGA_SERVO_3	=> FPGA_SERVO_3,
				FPGA_SERVO_4	=> FPGA_SERVO_4,
				FPGA_SERVO_5	=> FPGA_SERVO_5,
				FPGA_SERVO_6	=> FPGA_SERVO_6,
				FPGA_SERVO_7	=> FPGA_SERVO_7,
				FPGA_SERVO_8	=> FPGA_SERVO_8,
				FPGA_SERVO_9	=> FPGA_SERVO_9,

				PIC_PMP_PMALH	=> PIC_PMP_PMALH,
				PIC_PMP_PMALL	=> PIC_PMP_PMALL,
				PIC_PMP_PMCS2	=> PIC_PMP_PMCS2,
				PIC_PMP_PMD	=> PIC_PMP_PMD,
				PIC_PMP_PMRD	=> PIC_PMP_PMRD,
				PIC_PMP_PMWR	=> PIC_PMP_PMWR,

				LED1		=> LED1,
				LED2		=> LED2
			);

end architecture testbench;
