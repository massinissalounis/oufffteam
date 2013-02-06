
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library work;
use work.FPGA_OUFFF_p.all;

entity PMP_TB is
end entity PMP_TB;

architecture testbench of PMP_TB is

	constant period_PIC_TPB		: time := 12.5 ns; 	-- 80 MHz
	constant period_FPGA		: time := 1/FPGA_FREQUENCY;	-- 40.69 MHz
	
	constant period_BR		: time := 8.7 us;  	-- 115200 BPS
	
	constant period_ENCODER_edges	: time := 20*period_FPGA;
	constant period_COLOR		: time := 10 us;	-- 100kHz
	
	-- parametres du bus PMP reglables dans le microcontroleur (en nombre de fronts de fclk)
	constant WAITB	: integer := 3; -- 1 to 3
	constant WAITM	: integer := 7; -- 1 to 15
	constant WAITE	: integer := 3; -- 0 to 3

	
	-- Addresse des registres (Debut de la plage d'adressage) 
	constant Address_RESET		: std_logic_vector (15 downto 0)	:= X"0000";
	constant Address_LED		: std_logic_vector (15 downto 0)	:= X"0001";
	constant Address_ENCODER_LATCH	: std_logic_vector (15 downto 0)	:= X"0008";
	constant Address_ENCODER_R_LSB	: std_logic_vector (15 downto 0)	:= X"0009";
	constant Address_ENCODER_R_MSB	: std_logic_vector (15 downto 0)	:= X"000A";
	constant Address_ENCODER_L_LSB	: std_logic_vector (15 downto 0)	:= X"000B";
	constant Address_ENCODER_L_MSB	: std_logic_vector (15 downto 0)	:= X"000C";
	constant Address_AX12_1_STATUS	: std_logic_vector (15 downto 0)	:= X"0020";
	constant Address_AX12_1_IN	: std_logic_vector (15 downto 0)	:= X"0021";
	constant Address_AX12_1_OUT	: std_logic_vector (15 downto 0)	:= X"0022";
	constant Address_COLOR_SENSOR_1	: std_logic_vector (15 downto 0)	:= X"0030";
	constant Address_COLOR_SENSOR_2	: std_logic_vector (15 downto 0)	:= X"0031";
	constant Address_COLOR_SENSOR_3	: std_logic_vector (15 downto 0)	:= X"0032";
	constant Address_COLOR_SENSOR_4	: std_logic_vector (15 downto 0)	:= X"0033";
	constant Address_COLOR_CONTROL	: std_logic_vector (15 downto 0)	:= X"0040";
	constant Address_BEACON		: std_logic_vector (15 downto 0)	:= X"0050";
	constant Address_GPIO		: std_logic_vector (15 downto 0)	:= X"0060";	
	constant Address_SERVO_0	: std_logic_vector (15 downto 0)	:= X"0070";
	constant Address_SERVO_1	: std_logic_vector (15 downto 0)	:= X"0071";
	
	procedure pmp_wait_states (
		signal fPB			: in std_logic;
		constant wait_states	: in integer
		) is
		variable i: integer;
		begin
		  i := wait_states;
		  WHILE (i > 0) LOOP
				wait until rising_edge (fPB);
				i := i-1;
			END LOOP;
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
			PMD <= address(7 downto 0);
			wait until rising_edge (fPB);
			PMALL <= '1';
			pmp_wait_states(fPB, WAITB);
			PMALL <='0';
			wait until rising_edge (fPB);			
			PMD <= address(15 downto 8);
			wait until rising_edge (fPB);
			PMALH <= '1';
			pmp_wait_states(fPB, WAITB);
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
			PMD <= address(7 downto 0);
			wait until rising_edge (fPB);
			PMALL <= '1';
			pmp_wait_states(fPB, WAITB);
			PMALL <='0';
			wait until rising_edge (fPB);			
			PMD <= address(15 downto 8);
			wait until rising_edge (fPB);
			PMALH <= '1';
			pmp_wait_states(fPB, WAITB);
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
		FPGA_GPIO_0		: in std_logic;
		FPGA_GPIO_1		: inout std_logic;
		FPGA_GPIO_2		: in std_logic;
		FPGA_GPIO_3		: inout std_logic;
		FPGA_GPIO_4		: in std_logic;
		FPGA_GPIO_5		: inout std_logic;
		FPGA_GPIO_6		: in std_logic;
		FPGA_GPIO_7		: inout std_logic;
		FPGA_GPIO_8		: inout std_logic;
		FPGA_GPIO_9		: in std_logic;
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
		FPGA_SERVO_3		: out std_logic;
		FPGA_SERVO_4		: out std_logic;
		FPGA_SERVO_5		: out std_logic;
		FPGA_SERVO_6		: in std_logic;
		FPGA_SERVO_7		: out std_logic;
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
		LED2			: out std_logic
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
		
		EncoderTB_Forward: process
		begin
			loop
				FPGA_PHA1<='1'; FPGA_PHB1<='0';
				wait for period_ENCODER_edges/4;
				FPGA_PHA1<='1'; FPGA_PHB1<='1';
				wait for period_ENCODER_edges/4;
				FPGA_PHA1<='0'; FPGA_PHB1<='1';
				wait for period_ENCODER_edges/4;
				FPGA_PHA1<='0'; FPGA_PHB1<='0';
				wait for period_ENCODER_edges/4;
			end loop;
		end process;
		
		EncoderTB_Backward: process
		begin
			loop
				FPGA_PHA2<='0'; FPGA_PHB2<='1';
				wait for period_ENCODER_edges/4;
				FPGA_PHA2<='1'; FPGA_PHB2<='1';
				wait for period_ENCODER_edges/4;
				FPGA_PHA2<='1'; FPGA_PHB2<='0';
				wait for period_ENCODER_edges/4;
				FPGA_PHA2<='0'; FPGA_PHB2<='0';
				wait for period_ENCODER_edges/4;
			end loop;
		end process;
		
		Color_Sensor: process
		begin
			loop
				FPGA_GPIO_0 <= '0';
				wait for period_COLOR/2;
				FPGA_GPIO_0 <= '1';
				wait for period_COLOR/2;
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
			
			FPGA_PHA3	<= '0';
			FPGA_PHB3	<= '0';
			FPGA_PHA4	<= '0';
			FPGA_PHB4	<= '0';
			
			FPGA_GPIO_2	<= '0';
			FPGA_GPIO_4	<= '0';
			FPGA_GPIO_5	<= '0';
			FPGA_GPIO_6	<= '0';
			FPGA_GPIO_8	<= 'H'; -- AX12_1 link
			FPGA_GPIO_9	<= '0';

			FPGA_SERVO_1	<= '0';
			FPGA_SERVO_2	<= '0';
			FPGA_SERVO_6	<= '0';
		
		---- Test RESET ----
			assert false report ("Test HARD RESET") severity note;
			-- HARD RESET
			wait for 50 ns;
			RESET <= '1';
			wait for 50 ns;
			RESET <= '0';
			-- DO AN FPGA RESET

		---- Test LED ----
			assert false report ("Test LED") severity note;
			PIC_ADDR <= Address_LED;
			PIC_PMDIN <=  X"AA"; -- LED1 On
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_PMDIN <=  X"00"; -- Look at the data back
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
		---- Test SOFT RESET ----
			assert false report ("Test SOFT RESET") severity note;
			PIC_ADDR <= Address_RESET;
			PIC_PMDIN <=  X"FF"; -- LED1 On
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_PMDIN <=  X"00"; -- Look at the data back
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
		---- Test ENCODER_1 ----
			assert false report ("Test ENCODER_1") severity note;
			-- Wait till the counters count after the soft reset !
			wait for 2.57 us;
			-- Latch the 2 counters
			PIC_ADDR <= Address_ENCODER_LATCH;
			PIC_PMDIN <=  X"FF"; 
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			-- Read the data back
			PIC_ADDR <= Address_ENCODER_R_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_ENCODER_R_MSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_ENCODER_L_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_ENCODER_L_MSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
		---- Test AX12_1 ----
--			assert false report ("Test AX12_1") severity note;
			
			assert false report ("AX12_1 Write") severity note;
			PIC_ADDR <= Address_AX12_1_OUT;
			PIC_PMDIN <="11001100";
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			wait for 50 ns;
			PIC_ADDR <= Address_AX12_1_STATUS;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			wait for 50 ns;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			wait for 11*period_BR;
--			wait for 2*period_BR;
		
			assert false report ("AX12_1 Read") severity note;
			FPGA_GPIO_8<='H';			wait for period_BR;
			FPGA_GPIO_8<='0';			wait for period_BR; -- Start
			FPGA_GPIO_8<='H';			wait for period_BR;
			FPGA_GPIO_8<='H';			wait for period_BR;
			FPGA_GPIO_8<='0';			wait for period_BR;
			FPGA_GPIO_8<='0';			wait for period_BR;
			FPGA_GPIO_8<='H';			wait for period_BR;
			FPGA_GPIO_8<='H';			wait for period_BR;
			FPGA_GPIO_8<='0';			wait for period_BR;
			FPGA_GPIO_8<='0';			wait for period_BR;
			FPGA_GPIO_8<='H';			wait for 2*period_BR; -- Stop
			FPGA_GPIO_8<='H';				
			PIC_ADDR <= Address_AX12_1_STATUS;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_AX12_1_IN;
			wait for 50 ns;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);

		---- Test COLOR_SENSOR ----			
			assert false report ("Test COLOR_SENSOR_1") severity note;
			PIC_ADDR <= Address_COLOR_SENSOR_1;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
		---- Test COLOR_CONTROL ----
			assert false report ("Test COLOR_CONTROL") severity note;
			PIC_ADDR <= Address_COLOR_CONTROL;
			PIC_PMDIN <=  X"FF";
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_PMDIN <=  X"AA";
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
		---- Test BEACONS ----
			assert false report ("Test BEACON") severity note;
			PIC_ADDR <= Address_BEACON;
			FPGA_GPIO_4<='1'; FPGA_GPIO_2 <='0'; FPGA_GPIO_9 <='0'; FPGA_GPIO_6 <= '0';
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			FPGA_GPIO_4<='0'; FPGA_GPIO_2 <='0'; FPGA_GPIO_9 <='1'; FPGA_GPIO_6 <= '0';
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);	
			
		---- Test GPIO ----
			assert false report ("Test GPIO") severity note;
			PIC_ADDR <= Address_GPIO;
			PIC_PMDIN <=  X"FF";
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_PMDIN <=  X"00";
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
		---- Test SERVOs ----
			assert false report ("Test SERVOs") severity note;
			PIC_ADDR <= Address_SERVO_0;
			PIC_PMDIN <=  X"FF";
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_SERVO_1;
			PIC_PMDIN <=  X"80";
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
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
