
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity BEACON_TB is
end entity BEACON_TB;

architecture testbench of BEACON_TB is

	constant period_PIC_TPB		: time := 12.5 ns; 	-- 80 MHz
	constant period_FPGA		: time := 50 ns;	-- 20.00 MHz
	
	constant period_BR		: time := 8.7 us;  	-- 115200 BPS
	
	constant period_ENCODER_edges	: time := 20*period_FPGA;
	constant period_COLOR		: time := 10 us;	-- 100kHz
	
	-- parametres du bus PMP reglables dans le microcontroleur (en nombre de fronts de fclk)
	constant WAITB	: integer := 3; -- 1 to 3
	constant WAITM	: integer := 9; -- 1 to 15
	constant WAITE	: integer := 3; -- 0 to 3

	
	-- Addresse des registres (Debut de la plage d'adressage) 
	constant Address_RESET			: std_logic_vector (15 downto 0)	:= X"0000";
	constant Address_LED			: std_logic_vector (15 downto 0)	:= X"0001";
	constant Address_ENCODER_LATCH		: std_logic_vector (15 downto 0)	:= X"0008";
	constant Address_ENCODER_R_LSB		: std_logic_vector (15 downto 0)	:= X"0009";
	constant Address_ENCODER_R_MSB		: std_logic_vector (15 downto 0)	:= X"000A";
	constant Address_ENCODER_L_LSB		: std_logic_vector (15 downto 0)	:= X"000B";
	constant Address_ENCODER_L_MSB		: std_logic_vector (15 downto 0)	:= X"000C";
	constant Address_AX12_1_STATUS		: std_logic_vector (15 downto 0)	:= X"0020";
	constant Address_AX12_1_IN		: std_logic_vector (15 downto 0)	:= X"0021";
	constant Address_AX12_1_OUT		: std_logic_vector (15 downto 0)	:= X"0022";
	constant Address_COLOR_SENSOR_1		: std_logic_vector (15 downto 0)	:= X"0030";
	constant Address_COLOR_SENSOR_2		: std_logic_vector (15 downto 0)	:= X"0031";
	constant Address_COLOR_SENSOR_3		: std_logic_vector (15 downto 0)	:= X"0032";
	constant Address_COLOR_SENSOR_4		: std_logic_vector (15 downto 0)	:= X"0033";
	constant Address_COLOR_CONTROL		: std_logic_vector (15 downto 0)	:= X"0040";
	constant Address_GPIO			: std_logic_vector (15 downto 0)	:= X"0060";	
	constant Address_SERVO_0		: std_logic_vector (15 downto 0)	:= X"0070";
	constant Address_SERVO_1		: std_logic_vector (15 downto 0)	:= X"0071";
	
	constant Address_BEACON_STATUS		: std_logic_vector (15 downto 0)	:= X"0100";
	constant Address_BEACON_0_LSB		: std_logic_vector (15 downto 0)	:= X"0101";
	constant Address_BEACON_0_MSB		: std_logic_vector (15 downto 0)	:= X"0102";
	constant Address_BEACON_1_LSB		: std_logic_vector (15 downto 0)	:= X"0103";
	constant Address_BEACON_1_MSB		: std_logic_vector (15 downto 0)	:= X"0104";
	constant Address_BEACON_2_LSB		: std_logic_vector (15 downto 0)	:= X"0105";
	constant Address_BEACON_2_MSB		: std_logic_vector (15 downto 0)	:= X"0106";
	constant Address_BEACON_3_LSB		: std_logic_vector (15 downto 0)	:= X"0107";
	constant Address_BEACON_3_MSB		: std_logic_vector (15 downto 0)	:= X"0108";
	constant Address_BEACON_4_LSB		: std_logic_vector (15 downto 0)	:= X"0109";
	constant Address_BEACON_4_MSB		: std_logic_vector (15 downto 0)	:= X"010A";
	constant Address_BEACON_5_LSB		: std_logic_vector (15 downto 0)	:= X"010B";
	constant Address_BEACON_5_MSB		: std_logic_vector (15 downto 0)	:= X"010C";
	constant Address_BEACON_6_LSB		: std_logic_vector (15 downto 0)	:= X"010D";
	constant Address_BEACON_6_MSB		: std_logic_vector (15 downto 0)	:= X"010E";
	constant Address_BEACON_7_LSB		: std_logic_vector (15 downto 0)	:= X"010F";
	constant Address_BEACON_7_MSB		: std_logic_vector (15 downto 0)	:= X"0110";
	constant Address_BEACON_ENCODER_LATCH	: std_logic_vector (15 downto 0)	:= X"0120";
	constant Address_BEACON_ENCODER_LSB	: std_logic_vector (15 downto 0)	:= X"0121";
	constant Address_BEACON_ENCODER_MSB	: std_logic_vector (15 downto 0)	:= X"0122";
	constant Address_BEACON_MOTOR_PERIOD	: std_logic_vector (15 downto 0)	:= X"0130";
	
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
		
		Beacon_EncoderTB_Forward: process
		begin
			loop
				FPGA_GPIO_2<='1'; FPGA_GPIO_4<='0';
				wait for period_ENCODER_edges/4;
				FPGA_GPIO_2<='1'; FPGA_GPIO_4<='1';
				wait for period_ENCODER_edges/4;
				FPGA_GPIO_2<='0'; FPGA_GPIO_4<='1';
				wait for period_ENCODER_edges/4;
				FPGA_GPIO_2<='0'; FPGA_GPIO_4<='0';
				wait for period_ENCODER_edges/4;
			end loop;
		end process;
		
		Beacon_Sensor_v1: process -- Start with 0 --> Need to look at the waits between the spots in order to make the story comaptible with the encoder speed !
		begin
			loop
			
				wait for 5 us;
				FPGA_GPIO_9 <= '0'; wait for 1 us;
				FPGA_GPIO_9 <= '1'; wait for 100 ns;
				FPGA_GPIO_9 <= '0'; wait for 200 ns;
				FPGA_GPIO_9 <= '1'; wait for 400 ns;
				FPGA_GPIO_9 <= '0'; wait for 100 ns;
				FPGA_GPIO_9 <= '1'; wait for 100 ns;
				wait for 200 us;
			end loop;
		end process;

--		Beacon_Sensor_v2: process -- Start with 1
--		begin
--			loop
--			
--				wait for 5 us;
--				FPGA_GPIO_9 <= '1'; wait for 1 us;
--				FPGA_GPIO_9 <= '0'; wait for 100 ns;
--				FPGA_GPIO_9 <= '1'; wait for 200 ns;
--				FPGA_GPIO_9 <= '0'; wait for 400 ns;
--				FPGA_GPIO_9 <= '1'; wait for 100 ns;
--				FPGA_GPIO_9 <= '0'; wait for 100 ns;
--				wait for 200 us;
--			end loop;
--		end process;

--		Beacon_Sensor_v3: process -- Test the error modes where there is too many sports
--		begin
--			loop
--				wait for 5 us;
--				FPGA_GPIO_9 <= '1'; wait for 1 us;
--				FPGA_GPIO_9 <= '0'; wait for 100 ns;
--				FPGA_GPIO_9 <= '1'; wait for 200 ns;
--				FPGA_GPIO_9 <= '0'; wait for 400 ns;
--				FPGA_GPIO_9 <= '1'; wait for 100 ns;
--				FPGA_GPIO_9 <= '0'; wait for 100 ns;
--				wait for 200 us;
--			end loop;
--		end process;

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

		---- Test SOFT RESET ----
			assert false report ("Test SOFT RESET") severity note;
			PIC_ADDR <= Address_RESET;
			PIC_PMDIN <=  X"FF"; -- LED1 On
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_PMDIN <=  X"00"; -- Look at the data back
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
		---- Test BEACON_ENCODER ----
			assert false report ("Test BEACON_ENCODER") severity note;
			-- Wait till the counters count after the soft reset !
			wait for 2.57 us;
			-- Latch the 2 counters
			PIC_ADDR <= Address_BEACON_ENCODER_LATCH;
			PIC_PMDIN <=  X"FF"; 
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			-- Read the data back
			PIC_ADDR <= Address_BEACON_ENCODER_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_BEACON_ENCODER_MSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
		---- Test BEACON_MOTOR ----
			assert false report ("Test BEACON_MOTOR") severity note;
			-- Wait till the counters count after the soft reset !
			wait for 2 us;
			-- Latch the 2 counters
			PIC_ADDR <= Address_BEACON_MOTOR;
			PIC_PMDIN <=  X"00"; 
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			wait for 2 us;
			PIC_PMDIN <=  X"AA"; 
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			wait for 2 us;
			PIC_PMDIN <=  X"FF"; 
			pmp_write_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			
		---- Test BEACONS ----
			wait for 2 us;
			assert false report ("Test BEACON") severity note;
			PIC_ADDR <= Address_BEACON_STATUS;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_BEACON_0_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);	
			PIC_ADDR <= Address_BEACON_0_MSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_BEACON_1_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);	
			PIC_ADDR <= Address_BEACON_1_MSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_BEACON_2_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);	
			PIC_ADDR <= Address_BEACON_2_MSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_BEACON_3_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);	
			PIC_ADDR <= Address_BEACON_3_MSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_BEACON_4_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);	
			PIC_ADDR <= Address_BEACON_4_MSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_BEACON_5_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);	
			PIC_ADDR <= Address_BEACON_5_MSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_BEACON_6_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);	
			PIC_ADDR <= Address_BEACON_6_MSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);
			PIC_ADDR <= Address_BEACON_7_LSB;
			pmp_read_access (PIC_PB_CLK, PIC_ADDR, PIC_PMDIN, PIC_PMP_PMD, PIC_PMP_PMALL, PIC_PMP_PMALH, PIC_PMP_PMRD, PIC_PMP_PMWR);	
			PIC_ADDR <= Address_BEACON_7_MSB;
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
