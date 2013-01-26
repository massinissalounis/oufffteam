-- Oufffteam
-- Projet carte mère
-- Device: TOP

-- 29/12/2009			CBE			Création
-- 20/01/2013			PEG			Refonte


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.PMP_p.all;
use work.LED_register_p.all;

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
		FPGA_SERVO_0		: out std_logic;
		FPGA_SERVO_1		: in std_logic;
		FPGA_SERVO_2		: in std_logic;
		FPGA_SERVO_3		: in std_logic;
		FPGA_SERVO_4		: out std_logic;
		FPGA_SERVO_5		: out std_logic;
		FPGA_SERVO_6		: out std_logic;
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
end entity FPGA_Oufff;

architecture mapping of FPGA_Oufff is
	
	constant BUS_LED_ADD_START:		std_logic_vector (15 downto 0) := X"0000";
	constant BUS_LED_ADD_STOP:		std_logic_vector (15 downto 0) := X"0000";
	
	-- internal parallel bus
	signal BUS_D		std_logic_vector (7 downto 0);
	signal BUS_A		std_logic_vector (15 downto 0);
	signal BUS_RD		std_logic;
	signal BUS_WR		std_logic;
	
	signal BUS_CS_LED	std_logic;
	
	begin
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
		
		-- LED Module
		-- Address decoding
		BUS_CS_LED <= '1' when (BUS_A >= BUS_LED_ADD_START and BUS_A <= BUS_LED_ADD_STOP) else '0';
		
		LED_interface: LED
			port map(
				clock		=> FPGA_CLK,
				reset		=> FPGA_RESET,
				-- Internal Bus
				BUS_D		=> BUS_D,
				BUS_RD		=> BUS_RD,
				BUS_WR		=> BUS_WR,
				BUS_CS		=> BUS_CS_LED,
				-- Module Output
				LED1		=> LED1, --open,
				LED2		=> LED2 --open
			);
			
--		reset_from_pic: reset_register
--			port map(
--				PMP_in		=> To_slave(reset_slave_number),
--				PMP_out		=> From_slave(reset_slave_number),
--				reset		=> global_reset,
--				reset_n		=> global_reset_n
--			);

		-- Unassigned PINs
		PIC_INT1		<= 'Z';
		-- GPIO
		FPGA_GPIO_0		<= 'Z';
		FPGA_GPIO_1		<= 'Z';
		FPGA_GPIO_2		<= 'Z';
		FPGA_GPIO_3		<= 'Z';
		FPGA_GPIO_4		<= 'Z';
		FPGA_GPIO_5		<= 'Z';
		FPGA_GPIO_6		<= 'Z';
		FPGA_GPIO_7		<= 'Z';	-- à 1 pour lecture couleur avec GPIO 9 check previous code !!!
		FPGA_GPIO_8		<= 'Z';
		FPGA_GPIO_9		<= 'Z';
		
		-- Servomoteurs
		FPGA_SERVO_0	<= 'Z';
		--FPGA_SERVO_1	<= 'Z'; -- Input ports !
		--FPGA_SERVO_2	<= 'Z';
		--FPGA_SERVO_3	<= 'Z';
		FPGA_SERVO_4	<= 'Z';
		FPGA_SERVO_5	<= 'Z';
		FPGA_SERVO_6	<= 'Z';
		FPGA_SERVO_7	<= 'Z';
		FPGA_SERVO_8	<= 'Z';
		FPGA_SERVO_9	<= 'Z';

end architecture mapping;
