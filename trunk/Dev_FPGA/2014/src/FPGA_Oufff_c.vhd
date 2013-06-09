-- Oufffteam
-- Projet carte mere
-- Device: TOP

-- 29/12/2009			CBE			Creation
-- 20/01/2013			PEG			Refonte


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.FPGA_OUFFF_p.all;
use work.PMP_p.all;
use work.RESET_p.all;
use work.LED_p.all;
use work.ENCODER_p.all;
use work.HALF_DUPLEX_UART_p.all;
use work.TCS3200_p.all;
use work.GPIO_p.all;
use work.SERVO_CONTROL_p.all;

entity FPGA_Oufff is
	port (
		FPGA_CLK		: in std_logic;
		FPGA_RESET_n	: in std_logic;
		PIC_INT1		: out std_logic;
		-- GPIO
		FPGA_GPIO_0		: in std_logic;		-- CM_COLOR_1
		FPGA_GPIO_1		: inout std_logic;	-- CM_GPIO_3
		FPGA_GPIO_2		: in std_logic;		-- CM_BALISE_3
		FPGA_GPIO_3		: inout std_logic;	-- CM_GPIO_2
		FPGA_GPIO_4		: in std_logic;		-- CM_BALISE_4
		FPGA_GPIO_5		: inout std_logic;	-- NC
		FPGA_GPIO_6		: out std_logic;	-- CM_BALISE_1
		FPGA_GPIO_7		: inout std_logic;	-- CM_GPIO_1
		FPGA_GPIO_8		: inout std_logic;	-- CM_AX12_1_DATA
		FPGA_GPIO_9		: in std_logic;		-- CM_BALISE_2
		-- Codeurs
		FPGA_PHA1		: in std_logic;		-- RIGHT WHEEL
		FPGA_PHB1		: in std_logic;		-- RIGHT_WHEEL
		FPGA_PHA2		: in std_logic;		-- LEFT_WHEEL
		FPGA_PHB2		: in std_logic;		--  LEFT_WHEEL
		FPGA_PHA3		: in std_logic;		-- NC
		FPGA_PHB3		: in std_logic;		-- NC
		FPGA_PHA4		: in std_logic;		-- NC
		FPGA_PHB4		: in std_logic;		-- NC
		-- Servomoteurs
		FPGA_SERVO_0		: out std_logic;	-- NC
		FPGA_SERVO_1		: in std_logic;		-- CM_COLOR_4
		FPGA_SERVO_2		: in std_logic;		-- CM_COLOR_3
		FPGA_SERVO_3		: out std_logic;	-- CM_COLOR_S3
		FPGA_SERVO_4		: out std_logic;	-- NC
		FPGA_SERVO_5		: out std_logic;	-- CM_COLOR_S2
		FPGA_SERVO_6		: in std_logic;		-- CM_COLOR_2
		FPGA_SERVO_7		: out std_logic;	-- CM_SERVO_1
		FPGA_SERVO_8		: out std_logic;	-- NC
		FPGA_SERVO_9		: out std_logic;	-- CM_SERVO_0
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
end entity FPGA_Oufff;

architecture mapping of FPGA_Oufff is

	-- internal parallel bus
	signal BUS_D:			std_logic_vector (7 downto 0);
	signal BUS_A:			std_logic_vector (15 downto 0);
	signal BUS_RD:			std_logic;
	signal BUS_WR:			std_logic;
	
	signal BUS_CS_RESET:		std_logic;
	signal BUS_CS_LED:		std_logic;
	signal BUS_CS_ENCODER_1:	std_logic;
	signal BUS_CS_AX12_1:		std_logic;
	signal BUS_CS_COLOR_SENSOR_1:	std_logic;
	signal BUS_CS_COLOR_SENSOR_2:	std_logic;
	signal BUS_CS_COLOR_SENSOR_3:	std_logic;
	signal BUS_CS_COLOR_SENSOR_4:	std_logic;
	signal BUS_CS_COLOR_CONTROL:	std_logic;
	signal BUS_CS_GPIO:		std_logic;
	signal BUS_CS_SERVO_0:		std_logic;
	signal BUS_CS_SERVO_1:		std_logic;
	signal BUS_CS_BEACON:		std_logic;
	signal BUS_CS_BEACON_ENCODER:	std_logic;
	signal BUS_CS_BEACON_MOTOR:	std_logic;
	
	signal FPGA_RESET:	           std_logic;
	signal SOFT_RESET:	           std_logic;
	signal SOFT_RESET_N:               std_logic;
	signal HARD_SOFT_RESET:		    std_logic;
	
	signal COLOR_CONTROL_REG:		std_logic_vector (7 downto 0);
	signal GPIO_REG:		std_logic_vector (7 downto 0);
	signal BEACON_REG:		std_logic_vector (7 downto 0);
	signal tmp:		std_logic_vector (7 downto 0);
	signal tmp2 : std_logic;
	signal tmp_LED1 : std_logic;
	
	--Component configuration
	for PMP: PMP_interface
			use entity work.PMP_interface (semi_synchronous);
	
	begin
		
		FPGA_RESET <= not FPGA_RESET_n;
		
		-- Interface with the PIC PMP
		PMP: PMP_interface
			port map (
				clock		=> FPGA_CLK,
				reset		=> FPGA_RESET,
				-- in - PMP
				PMP_PMALH	=> PIC_PMP_PMALH,
				PMP_PMALL	=> PIC_PMP_PMALL,
				PMP_PMCS	=> PIC_PMP_PMCS2,
				PMP_PMD		=> PIC_PMP_PMD,
				PMP_PMRD	=> PIC_PMP_PMRD,
				PMP_PMWR	=> PIC_PMP_PMWR,
				-- out
				BUS_D		=> BUS_D,
				BUS_A		=> BUS_A,
				BUS_RD		=> BUS_RD,
				BUS_WR		=> BUS_WR
			);
			
		-- RESET Module
		-- Address decoding
		BUS_CS_RESET <= '1' when (BUS_A >= BUS_RESET_ADD_START and BUS_A <= BUS_RESET_ADD_STOP) else '0';
		
		RESET_software: RESET
			port map(
				clock		=> FPGA_CLK,
				reset		=> FPGA_RESET,
				-- Internal Bus
				BUS_D		=> BUS_D,
				BUS_RD		=> BUS_RD,
				BUS_WR		=> BUS_WR,
				BUS_CS		=> BUS_CS_RESET,
				-- Module Output
				SOFT_RESET	=> SOFT_RESET,
				SOFT_RESET_N	=> SOFT_RESET_N
			);
			
		HARD_SOFT_RESET <= FPGA_RESET or SOFT_RESET;
		
		-- LED Module
		-- Address decoding
		BUS_CS_LED <= '1' when (BUS_A >= BUS_LED_ADD_START and BUS_A <= BUS_LED_ADD_STOP) else '0';
		
		LED_interface: LED
			port map(
				clock		=> FPGA_CLK,
				reset		=> HARD_SOFT_RESET,
				-- Internal Bus
				BUS_D		=> BUS_D,
				BUS_RD		=> BUS_RD,
				BUS_WR		=> BUS_WR,
				BUS_CS		=> BUS_CS_LED,
				-- Module Output
				LED1		=> open, --LED1,
				LED2		=> open --LED2
			);

		--LED2 <= '1' when BUS_D = X"AA" else '0';
		--tmp_LED1 <= '1' when BUS_D = X"AA" and BUS_WR = '1' and BUS_CS_AX12_1 = '1' else 
--					'0' when BUS_D = X"55" and BUS_WR = '1' and BUS_CS_AX12_1 = '1' else tmp_LED1;
		LED1 <= tmp_LED1;
		
		-- ENCODER 1 Module
		-- Address decoding
		BUS_CS_ENCODER_1 <= '1' when (BUS_A >= BUS_ENCODER_1_ADD_START and BUS_A <= BUS_ENCODER_1_ADD_STOP) else '0';

		ENCODER1_interface: ENCODER
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- debug
				debug_latch		=> open,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_A			=> BUS_A(2 downto 0),
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_ENCODER_1,
				-- coders
				ENCODER_R_channel_A	=> FPGA_PHA1,
				ENCODER_R_channel_B	=> FPGA_PHB1,
				ENCODER_L_channel_A	=> FPGA_PHA2,
				ENCODER_L_channel_B	=> FPGA_PHB2
			);
			
		-- AX12_1 Module
		-- Frequency set to 115200 BPS -- TODO UPDATE at 117647 real objective in the DS
		BUS_CS_AX12_1 <= '1' when (BUS_A >= BUS_AX12_1_ADD_START and BUS_A <= BUS_AX12_1_ADD_STOP) else '0';

		AX12_1_interface: HALF_DUPLEX_UART
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_A			=> BUS_A(1 downto 0),
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_AX12_1,
				-- external pin
				RxTx			=> tmp2, --FPGA_GPIO_8
				tmp_LED1		=> tmp_LED1
			);
 
		FPGA_GPIO_8 <= tmp2;
		LED2 <= BUS_WR;
 
		-- TCS3200 Color Sensor 1
 		BUS_CS_COLOR_SENSOR_1 <= '1' when (BUS_A >= BUS_COLOR_SENSOR_1_ADD_START and BUS_A <= BUS_COLOR_SENSOR_1_ADD_STOP) else '0';
 		
		COLOR_SENSOR_1: TCS3200_INTERFACE
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_COLOR_SENSOR_1,
				-- coder
				IN_SIGNAL		=> FPGA_GPIO_0
			);
			
 		BUS_CS_COLOR_SENSOR_2 <= '1' when (BUS_A >= BUS_COLOR_SENSOR_2_ADD_START and BUS_A <= BUS_COLOR_SENSOR_2_ADD_STOP) else '0';
 		
		COLOR_SENSOR_2: TCS3200_INTERFACE
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_COLOR_SENSOR_2,
				-- coder
				IN_SIGNAL		=> FPGA_SERVO_6
			);
			
 		BUS_CS_COLOR_SENSOR_3 <= '1' when (BUS_A >= BUS_COLOR_SENSOR_3_ADD_START and BUS_A <= BUS_COLOR_SENSOR_3_ADD_STOP) else '0';
 		
		COLOR_SENSOR_3: TCS3200_INTERFACE
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_COLOR_SENSOR_3,
				-- coder
				IN_SIGNAL		=> FPGA_SERVO_2
			);
			
 		BUS_CS_COLOR_SENSOR_4 <= '1' when (BUS_A >= BUS_COLOR_SENSOR_4_ADD_START and BUS_A <= BUS_COLOR_SENSOR_4_ADD_STOP) else '0';
 		
		COLOR_SENSOR_4: TCS3200_INTERFACE
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_COLOR_SENSOR_4,
				-- coder
				IN_SIGNAL		=> FPGA_SERVO_1
			);
			
			
		BUS_CS_COLOR_CONTROL <= '1' when (BUS_A >= BUS_COLOR_CONTROL_ADD_START and BUS_A <= BUS_COLOR_CONTROL_ADD_STOP) else '0';
		
		FPGA_SERVO_5 <=	COLOR_CONTROL_REG(1); --S2 
		FPGA_SERVO_3 <=	COLOR_CONTROL_REG(0); -- S3
		
		-- Control signals of color sensors
		COLOR_CONTROL: GPIO_OUT
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_COLOR_CONTROL,
				-- GPIO
				GPIO_REG		=> COLOR_CONTROL_REG
			);
			
		-- GPIO
		BUS_CS_GPIO <= '1' when (BUS_A >= BUS_GPIO_ADD_START and BUS_A <= BUS_GPIO_ADD_STOP) else '0';
		
		FPGA_GPIO_1	<= GPIO_REG(2); -- GPIO3
		FPGA_GPIO_3 <= GPIO_REG(1); --GPIO2
		FPGA_GPIO_7 <= GPIO_REG(0); -- GPIO1

		GPIOs : GPIO_OUT
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_GPIO,
				-- GPIO
				GPIO_REG		=> GPIO_REG
			);
		
		-- SERVO CONTROLLER
		BUS_CS_SERVO_0 <= '1' when (BUS_A >= BUS_SERVO_0_ADD_START and BUS_A <= BUS_SERVO_0_ADD_STOP) else '0';
		
		SERVO_0: SERVO_CONTROL
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_SERVO_0,
				-- servo
				OUT_SIGNAL		=> FPGA_SERVO_9
			);
			
		BUS_CS_SERVO_1 <= '1' when (BUS_A >= BUS_SERVO_1_ADD_START and BUS_A <= BUS_SERVO_1_ADD_STOP) else '0';

		SERVO_1: SERVO_CONTROL
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_SERVO_1,
				-- servo
				OUT_SIGNAL		=> FPGA_SERVO_7
			);

		-- Beacon Control
		BUS_CS_BEACON <= '1' when (BUS_A >= BUS_BEACON_ADD_START and BUS_A <= BUS_BEACON_ADD_STOP) else '0';	
			
		BEACON : BEACON_CONTROL
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_BEACON,
				-- sensor
				SENSOR_in		=> FPGA_GPIO_9,
				-- coder
				ENCODER_channel_A	=> FPGA_GPIO_2,
				ENCODER_channel_B	=> FPGA_GPIO_4
				);
				
		BUS_CS_BEACON_ENCODER <= '1' when (BUS_A >= BUS_BEACON_ENCODER_ADD_START and BUS_A <= BUS_BEACON_ENCODER_ADD_STOP) else '0';	
				
		BEACON_ENCODER : SINGLE_ENCODER
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_A			=> BUS_A(1 downto 0),
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_BEACON_ENCODER,
				-- coders
				ENCODER_channel_A	=> FPGA_GPIO_2,
				ENCODER_channel_B	=> FPGA_GPIO_4
			);
		
		BUS_CS_BEACON_MOTOR <= '1' when (BUS_A >= BUS_BEACON_MOTOR_ADD_START and BUS_A <= BUS_BEACON_MOTOR_ADD_STOP) else '0';	
		
		BEACON_MOTOR : PWM
			port map (
				-- in
				clock			=> FPGA_CLK,
				reset			=> HARD_SOFT_RESET,
				-- in - Internal BUS			
				BUS_D			=> BUS_D,
				BUS_RD			=> BUS_RD,
				BUS_WR			=> BUS_WR,
				BUS_CS			=> BUS_CS_BEACON_MOTOR,
				OUT_PWM			=> FPGA_GPIO_6
			);

		
		-- Unassigned PINs
		PIC_INT1	<= 'Z';
		-- GPIO
		FPGA_GPIO_5	<= 'Z';
		-- Servomoteurs
		FPGA_SERVO_0	<= 'Z';
		FPGA_SERVO_4	<= 'Z';
		FPGA_SERVO_7	<= 'Z';
		FPGA_SERVO_8	<= 'Z';
		FPGA_SERVO_9	<= 'Z';

end architecture mapping;
