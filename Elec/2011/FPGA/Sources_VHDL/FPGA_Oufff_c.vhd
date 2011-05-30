-- Oufffteam
-- Projet carte mère
-- Device: Top

-- 28/12/2009			CBE			Création

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.pmp_p.all;
use work.reset_register_p.all;
use work.led_register_p.all;
use work.gpio_register_p.all;
use work.Coder_interface_p.all;
use work.gh_uart_16550_p.all;
use work.gh_registers_gates_p.all;

entity FPGA_Oufff is
	port (
		FPGA_CLK		: in std_logic;
		FPGA_RESET		: in std_logic;
		PIC_INT1		: out std_logic;
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
		FPGA_SERVO_0	: out std_logic;
		FPGA_SERVO_1	: out std_logic;
		FPGA_SERVO_2	: out std_logic;
		FPGA_SERVO_3	: out std_logic;
		FPGA_SERVO_4	: out std_logic;
		FPGA_SERVO_5	: out std_logic;
		FPGA_SERVO_6	: out std_logic;
		FPGA_SERVO_7	: out std_logic;
		FPGA_SERVO_8	: out std_logic;
		FPGA_SERVO_9	: out std_logic;
		-- PMP
		PIC_PMP_PMALH	: in std_logic;
		PIC_PMP_PMALL	: in std_logic;
		PIC_PMP_PMCS2	: in std_logic;
		PIC_PMP_PMD		: inout std_logic_vector (7 downto 0);
		PIC_PMP_PMRD	: in std_logic;
		PIC_PMP_PMWR	: in std_logic;
		-- Led
		LED1			: out std_logic;
		LED2			: out std_logic
		);
end entity FPGA_Oufff;

architecture mapping of FPGA_Oufff is
		
	constant pmp_slave_number: 	natural := 5;

	constant reset_slave_number:	natural := 0;
	constant led_slave_number:		natural := 1;
	constant codeur_slave_number:	natural := 2;
	constant gpio_slave_number: 	natural := 3;
	constant AX12_1_slave_number: 	natural := 4;
	
	constant pmp_cs_0_add_start:	std_logic_vector (15 downto 0) := X"0000";
	constant pmp_cs_0_add_stop:		std_logic_vector (15 downto 0) := X"0000";
	constant pmp_cs_1_add_start:	std_logic_vector (15 downto 0) := X"0001";
	constant pmp_cs_1_add_stop:		std_logic_vector (15 downto 0) := X"0001";
	constant pmp_cs_2_add_start:	std_logic_vector (15 downto 0) := X"0008";
	constant pmp_cs_2_add_stop:		std_logic_vector (15 downto 0) := X"000F";
	constant pmp_cs_3_add_start:	std_logic_vector (15 downto 0) := X"0010";
	constant pmp_cs_3_add_stop:		std_logic_vector (15 downto 0) := X"0010";
	constant pmp_cs_4_add_start:	std_logic_vector (15 downto 0) := X"0020";
	constant pmp_cs_4_add_stop:		std_logic_vector (15 downto 0) := X"0027";

	signal global_reset, global_reset_n:	std_logic;
	signal coder_clock:			std_logic;
	signal coder_reset_n:		std_logic;
	
	signal gpio_out:	std_logic_vector (0 downto 0);
	signal gpio_out_en:	std_logic_vector (0 downto 0);
	signal gpio_in:		std_logic_vector (0 downto 0);
	
	signal uart_reset : std_logic;
	signal uart_main_clock, uart_BR_clock : std_logic;
	signal AX12_1_RX, AX12_1_TX, AX12_1_TXEN : std_logic;
	signal AX12_2_RX, AX12_2_TX, AX12_2_TXEN : std_logic;
	signal AX12_1_DATA, AX12_2_DATA : std_logic;
	
	signal pmp_CS:				std_logic_vector (pmp_slave_number - 1 downto 0);
	signal pmp_address:			std_logic_vector (15 downto 0);
	signal From_slave:			PMP_SLV_OUT_VECTOR (pmp_slave_number - 1 downto 0);
	signal To_slave	:			PMP_SLV_IN_VECTOR (pmp_slave_number - 1 downto 0);
	
	signal toto1, toto1_n : std_logic;
	signal toto2, toto2_n : std_logic;
	signal toto3, toto3_n : std_logic;
	signal toto4, toto4_n : std_logic;
	
	
	begin

		coder_clock		<= FPGA_CLK;
		coder_reset_n	<= global_reset_n;
		uart_main_clock	<= FPGA_CLK;
		uart_BR_clock	<= FPGA_CLK;
		uart_reset		<= global_reset;
		
		pmp_bus: PMP_interface
			generic map ( slave_number => pmp_slave_number)
			port map (
				clock		=> FPGA_CLK,
				reset		=> '0',
				-- PMP
				PMP_PMALH	=> PIC_PMP_PMALH,
				PMP_PMALL	=> PIC_PMP_PMALL,
				PMP_PMCS	=> '1', --PIC_PMP_PMCS2,  -- pin CS2 non utilisée !!
				PMP_PMD		=> PIC_PMP_PMD,
				PMP_PMRD	=> PIC_PMP_PMRD,
				PMP_PMWR	=> PIC_PMP_PMWR,

				CS_input	=> pmp_CS,
				Address		=> pmp_address,
				--internal PMP
				From_slave	=> From_slave, 
				To_slave	=> To_slave
			);
		
		PIC_PMP_PMD	<= (others => 'Z');
		pmp_CS(0) <= '1' when (pmp_address >= pmp_cs_0_add_start and pmp_address <= pmp_cs_0_add_stop) else '0';
		pmp_CS(1) <= '1' when (pmp_address >= pmp_cs_1_add_start and pmp_address <= pmp_cs_1_add_stop) else '0';
		pmp_CS(2) <= '1' when (pmp_address >= pmp_cs_2_add_start and pmp_address <= pmp_cs_2_add_stop) else '0';
		pmp_CS(3) <= '1' when (pmp_address >= pmp_cs_3_add_start and pmp_address <= pmp_cs_3_add_stop) else '0';
		pmp_CS(4) <= '1' when (pmp_address >= pmp_cs_4_add_start and pmp_address <= pmp_cs_4_add_stop) else '0';
		LED2 <= pmp_CS(4);
		--LED2 <= '1' when pmp_address = pmp_cs_4_add_start else '0';
		
		PIC_INT1		<= 'Z';
		-- GPIO
		FPGA_GPIO_0		<= 'Z';
		FPGA_GPIO_1		<= 'Z';
		FPGA_GPIO_2		<= 'Z';
		FPGA_GPIO_3		<= 'Z';
		FPGA_GPIO_4		<= 'Z';
		FPGA_GPIO_5		<= 'Z';
		--FPGA_GPIO_6		<= 'Z';
		FPGA_GPIO_7		<= '1';	-- à 1 pour lecture couleur
		--FPGA_GPIO_8		<= 'Z';
		FPGA_GPIO_9		<= gpio_out(0) when gpio_out_en(0) = '1' else 'Z'; -- lecture couleur
		gpio_in (0)		<= FPGA_GPIO_9;
		
		-- Servomoteurs
		FPGA_SERVO_0	<= 'Z';
		FPGA_SERVO_1	<= 'Z';
		FPGA_SERVO_2	<= 'Z';
		FPGA_SERVO_3	<= 'Z';
		FPGA_SERVO_4	<= 'Z';
		FPGA_SERVO_5	<= 'Z';
		FPGA_SERVO_6	<= 'Z';
		FPGA_SERVO_7	<= 'Z';
		FPGA_SERVO_8	<= 'Z';
		FPGA_SERVO_9	<= 'Z';

		reset_from_pic: reset_register
			port map(
				PMP_in		=> To_slave(reset_slave_number),
				PMP_out		=> From_slave(reset_slave_number),
				reset		=> global_reset,
				reset_n		=> global_reset_n
			);
		
		LED_interface: led_register
			port map(
				PMP_in		=> To_slave(led_slave_number),
				PMP_out		=> From_slave(led_slave_number),
				LED1		=> open, --LED1,
				LED2		=> open	--LED2
			);

			
		codeurs: Coder_interface	
			port map (
				clock			=> coder_clock,
				reset_n			=> coder_reset_n,
				debug_latch		=> open,
				--pmp
				PMP_in			=> To_slave(codeur_slave_number),
				PMP_out			=> From_slave(codeur_slave_number),
				-- coders
				coder_D_chanel_A	=> FPGA_PHA1,
				coder_D_chanel_B	=> FPGA_PHB1,
				coder_G_chanel_A	=> FPGA_PHA2,
				coder_G_chanel_B	=> FPGA_PHB2
			);
			
		GPIO: gpio_register
			generic map ( nb_GPIO => 1)
			port map (
				PMP_in		=> To_slave(gpio_slave_number),
				PMP_out		=> From_slave(gpio_slave_number),
				gpio_out	=> gpio_out,
				gpio_out_en	=> gpio_out_en,
				gpio_in		=> gpio_in
			);
		
		AX12_1: gh_uart_16550_pmp_wrapper
			port map(	  
				--------- pmp signals ------------
				PMP_in		=> To_slave(AX12_1_slave_number),
				PMP_out		=> From_slave(AX12_1_slave_number),
				--------- other I/O --------------
				main_clk	=> uart_main_clock,
				main_reset	=> uart_reset,
				BR_clk		=> uart_BR_clock,
				-------- Serial I/O --------------
				sRX			=> AX12_1_RX,
				sTX			=> AX12_1_TX,
				TX_EN		=> AX12_1_TXEN,
				
				CTSn		=> '0',
				DSRn		=> '1',
				RIn			=> '1',
				DCDn		=> '1',
				DTRn		=> open,
				RTSn		=> open,
				OUT1n		=> open,
				OUT2n		=> open,
				TXRDYn		=> open,
				RXRDYn		=> open,
				IRQ			=> open,
				B_CLK		=> open
				);
		
		FPGA_GPIO_8 <= AX12_1_TX when AX12_1_TXEN = '1' else 'Z';
		AX12_1_RX	<= FPGA_GPIO_8 when AX12_1_TXEN = '0' else '1';
		--FPGA_GPIO_8	<= AX12_1_DATA;
		LED1 <= AX12_1_TXEN;
		--FPGA_GPIO_8 <= '1';
		
		AX12_2_DATA <= AX12_2_TX when AX12_2_TXEN = '1' else 'Z';
		AX12_2_RX	<= AX12_2_DATA;
		AX12_2_TX	<= '0';
		AX12_2_TXEN	<= '0';

		-- Singaux uart sur sorties servo (modifiée en inout)
		FPGA_GPIO_6	<= '0'; --AX12_1_DATA;
		
		
		sync1_cs: gh_dff port map (toto1_n,FPGA_CLK,global_reset,toto1);
		toto1_n <= not toto1;
		toto2_n <= not toto2;
		toto3_n <= not toto3;
		toto4_n <= not toto4;
		sync2_cs: gh_dff port map (toto2_n,toto1,global_reset,toto2);
		sync3_cs: gh_dff port map (toto3_n,toto2,global_reset,toto3);
		sync4_cs: gh_dff port map (toto4_n,toto3,global_reset,toto4);
		
		
		
end architecture mapping;
