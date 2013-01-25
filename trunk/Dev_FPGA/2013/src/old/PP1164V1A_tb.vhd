--------------------------------------------------------------------------------------------------------
-- Project :		CPLD ESCORT A8
--
-- File:			PP1164V1A_tb.vhd
--
-- Author:			C. BEGUET
--
-- Board:			k191015
--
-- Device:			Lattice - MacXO - LCMXO2280C-4FT256I
-- Part number:		D2
--
-- Dependencies:	
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author			Comments
--						0.1		19/10/2011			C. BEGUET		Creation
--				
--
--------------------------------------------------------------------------------------------------------
-- Purpose: Testbench for top level of ESCORT A8's CPLD. The main fonctionnaly is:
--		*	
--------------------------------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library work;
use work.apb.all;

entity ESCORT_TB is
end entity ESCORT_TB;

architecture testbench of ESCORT_TB is

	-- paramètres des bus GPMC et APB
	constant GPMC_ad_width		: integer := 16;	-- Number of wire on Address/data multiplexed bus
	constant GPMC_data_width 	: integer := 16;	-- Number of bits used for data(must be less or equal to GPMC_ad_width and equal to APB data bus width)
	constant GPMC_add_width		: integer := 16;	-- Number of bits used for address(must be less or equal to GPMC_ad_width and equal to APB address bus width)
	constant APB_number_of_slaves: natural := 2;

	constant period_CPLD		: time := 38 ns; 		-- 26 MHz  --19 ns ; -- 56 MHz
	constant period_GPMC		: time := 6.25 ns ;  	-- 160 MHz
	
	-- paramètres du bus GPMC réglables dans le microcontrôleur (en nombre de fronts de fclk)
	constant CSWROFFTIME	: integer := 25 *2;
	constant CSRDOFFTIME	: integer := 25 *2;
	constant CSONTIME		: integer := 0 *2;
	constant ADVRDOFFTIME	: integer := 10 *2;
	constant ADVWROFFTIME	: integer := 10 *2;
	constant ADVONTIME		: integer := 0 *2;
	constant WEOFFTIME		: integer := 23 *2;
	constant WEONTIME		: integer := 0 *2;
	constant OEOFFTIME		: integer := 25 *2;
	constant OEONTIME		: integer := 15 *2;
	constant RDACCESSTIME	: integer := 20 *2;
	constant WRCYCLETIME	: integer := 26 *2;
	constant RDCYCLETIME	: integer := 26 *2;
	constant WRDATAONADMUXBUS	: integer := 15 *2;
	constant CYCLE2CYCLEDELAY : integer := 10 *2;
	
	--		nom de la fonction										adresse A16 A1		adresse A15 A0
	constant Address_ID_start	: std_logic_vector (PAMAX downto 1)		:= X"0000";		-- 0000			-- Début de la plage d'adressage de l'ID
	constant Address_LCD_start 	: std_logic_vector (PAMAX-1 downto 0)	:= X"0100";		-- 0100
	constant Address_DAC_start	: std_logic_vector (PAMAX-1 downto 0)	:= X"0200";		-- 0200
	constant Address_CLV_start 	: std_logic_vector (PAMAX-1 downto 0)	:= X"0300";		-- 0300
	constant Address_ETOR_start	: std_logic_vector (PAMAX-1 downto 0)	:= X"0400";		-- 0400
	constant Address_FLT0_start	: std_logic_vector (PAMAX-1 downto 0)	:= X"0500";		-- 0500
	constant Address_FLT1_start	: std_logic_vector (PAMAX-1 downto 0)	:= X"0600";		-- 0600
	constant Address_CPT0_start	: std_logic_vector (PAMAX-1 downto 0)	:= X"0700";		-- 0700
	constant Address_CPT1_start	: std_logic_vector (PAMAX-1 downto 0)	:= X"0800";		-- 0800
	constant Address_CPT2_start	: std_logic_vector (PAMAX-1 downto 0)	:= X"0900";		-- 0900
	constant Address_CPT3_start	: std_logic_vector (PAMAX-1 downto 0)	:= X"0A00";		-- 0A00
	constant Address_CPT4_start	: std_logic_vector (PAMAX-1 downto 0)	:= X"0B00";		-- 0B00
	constant Address_CPT5_start	: std_logic_vector (PAMAX-1 downto 0)	:= X"0C00";		-- 0C00
	constant Address_RS_start 	: std_logic_vector (PAMAX-1 downto 0)	:= X"0D00";		-- 0D00
	constant Address_PWR_start 	: std_logic_vector (PAMAX-1 downto 0)	:= X"0E00";		-- 0E00
	
	
	procedure gpmc_read_access (
		signal fclk			: in std_logic;
		signal address_to_read	: in std_logic_vector (GPMC_ad_width-1 downto 0);
		signal ad			: inout std_logic_vector (GPMC_ad_width-1 downto 0);
		signal nCS			: out std_logic;
		signal nADV			: out std_logic;
		signal nOE			: out std_logic;
		signal wait_signal	: in std_logic;
		signal read_data	: inout std_logic_vector (GPMC_ad_width-1 downto 0);
		signal counter_out	: out integer
		) is
		variable counter: integer;
		begin
			--assert false report ("Test lecture GPMC") severity note;
			ad		<= (others => 'Z');
			nCS		<= '1';
			nADV	<= '1';
			nOE		<= '1';
			counter	:= 0;
			counter_out <= counter;
			wait until rising_edge (fclk);
			while (counter <= RDCYCLETIME) loop
				counter_out <= counter;
				if (counter > CSONTIME and counter <= CSRDOFFTIME)		then nCS <= '0';	else nCS <= '1';	end if;
				if (counter > ADVONTIME and counter <= ADVRDOFFTIME)	then nADV <= '0';	else nADV <= '1';	end if;
				if (counter > OEONTIME and counter <= OEOFFTIME)		then 
					nOE <= '0';
					ad <= (others => 'Z');
				else
					nOE <= '1';
					ad <= '0' & address_to_read (address_to_read'length-1 downto 1);
				end if;
				
				if (counter = RDACCESSTIME) then read_data <= ad;			end if;
				if (wait_signal = '0') 		then counter := counter + 1; 	end if;
				
				wait until rising_edge (fclk);
			end loop;
			ad		<= read_data;
			nCS		<= '1';
			nADV	<= '1';
			nOE		<= '1';
			--assert false report ("Fin test lecture GPMC") severity note;
			wait for CYCLE2CYCLEDELAY * period_GPMC;
	end procedure gpmc_read_access;
	
	procedure gpmc_write_access (
		signal fclk			: in std_logic;
		signal address_to_write	: in std_logic_vector (GPMC_ad_width-1 downto 0);
		signal data_to_write	: in std_logic_vector (GPMC_ad_width-1 downto 0);
		signal ad			: inout std_logic_vector (GPMC_ad_width-1 downto 0);
		signal nCS			: out std_logic;
		signal nADV			: out std_logic;
		signal nOE			: out std_logic;
		signal nWE			: out std_logic;
		signal wait_signal	: in std_logic;
		signal counter_out	: out integer
		) is
		variable counter: integer;
		begin
			--assert false report ("Test ecriture GPMC") severity note;
			ad		<= (others => 'Z');
			nCS		<= '1';
			nADV	<= '1';
			nOE		<= '1';
			nWE		<= '1';
			counter	:= 0;
			counter_out <= counter;
			wait until rising_edge (fclk);
			while (counter <= WRCYCLETIME) loop
				counter_out <= counter;
				if (counter > CSONTIME and counter <= CSWROFFTIME)		then nCS <= '0';	else nCS <= '1';	end if;
				if (counter > ADVONTIME and counter <= ADVWROFFTIME)	then nADV <= '0';	else nADV <= '1';	end if;
				if (counter > WEONTIME and counter <= WEOFFTIME)		then nWE <= '0';	else nWE <= '1';	end if;
				if (counter > WRDATAONADMUXBUS)							then ad <= data_to_write; 
				else ad <= '0' & address_to_write (address_to_write'length-1 downto 1); end if;
				if (wait_signal = '0') 		then counter := counter + 1; 	end if;
				wait until rising_edge (fclk);
			end loop;
			
			nCS		<= '1';
			nADV	<= '1';
			nOE		<= '1';
			ad		<= (others => 'Z');
			--assert false report ("Fin test ecriture GPMC") severity note;
			wait for CYCLE2CYCLEDELAY * period_GPMC;
	end procedure gpmc_write_access;
	
	component PP1164 is
		port (	-- Power management signals			
			PWR_EN_VCCECRAN		: out std_logic;
			PWR_EN_15V			: out std_logic;
			PWR_OK_24VIN_n		: in std_logic;
			
			ARM_CPLD_CLK		: in std_logic;
			ARM_RESET_n			: in std_logic;
			
			-- ARM GPMC signals
			ARM_GPMC_OE_n		: in std_logic;
			ARM_GPMC_WE_n		: in std_logic;
			ARM_GPMC_ADV_n		: in std_logic;
			ARM_GPMC_D			: inout std_logic_vector (15 downto 0);
			ARM_CPLD_INT		: out std_logic;
			ARM_CPLD_CS_n		: in std_logic;
			ARM_CPLD_WAIT		: out std_logic;
						
			-- Entrées TOR
			CPLD_DIGIT_IN		: in std_logic_vector (23 downto 0);
			
			-- Sorties TOR
			CPLD_DIGIT_OUT_RST_n	: out std_logic;
			
			-- Ecran LCD
			CPLD_LCD_DB			: inout std_logic_vector (7 downto 0);
			CPLD_LCD_E1			: out std_logic;
			CPLD_LCD_E2			: out std_logic;
			CPLD_LCD_READ		: out std_logic;
			CPLD_LCD_REG_SEL		: out std_logic;
			
			-- Clavier
			CPLD_CLAVIER_RL		: in std_logic_vector (3 downto 0);
			CPLD_CLAVIER_S		: out std_logic_vector (5 downto 0);
			CPLD_CLAVIER_LED	: out std_logic_vector (3 downto 0);
			
			-- DAC
			CPLD_DAC_RESET_n 	: out std_logic;
			CPLD_DAC_CLK	 	: out std_logic;
			CPLD_DAC_CS1_n	 	: out std_logic;
			CPLD_DAC_CS2_n	 	: out std_logic;
			CPLD_DAC_LOADDACS_n	: out std_logic;
			CPLD_DAC_LOADREG_n	: out std_logic;
			CPLD_DAC_SDI1		: out std_logic;
			CPLD_DAC_SDI2		: out std_logic;
			
			-- UART signals
			ARM_UART1_TX		: in std_logic;
			CPLD_RS485_RXEN		: out std_logic;
			CPLD_RS485_TXEN		: out std_logic;
			
			-- CPLD spare signals
			CPLD_TP1			: out std_logic;
			CPLD_TP2			: out std_logic;
			CPLD_TP3			: out std_logic;
			CPLD_TP4			: out std_logic
		);
	end component PP1164;

-- Global signals
	signal main_clock		: std_logic;
	signal reset,reset_n	: std_logic;

-- GPMC interface
	signal address_to_read	: std_logic_vector (GPMC_ad_width-1 downto 0);
	signal address_to_write	: std_logic_vector (GPMC_ad_width-1 downto 0);
	signal data_to_write	: std_logic_vector (GPMC_ad_width-1 downto 0);
	signal read_data		: std_logic_vector (GPMC_ad_width-1 downto 0);
	signal counter_out		: integer;

-- DUT signals
	signal PWR_EN_VCCECRAN	: std_logic;
	signal PWR_EN_15V		: std_logic;
	signal PWR_OK_24VIN_n	: std_logic;
	signal ARM_CPLD_CLK		: std_logic;
	signal ARM_RESET_n		: std_logic;
	-- ARM GPMC signals
	signal ARM_GPMC_OE_n	: std_logic;
	signal ARM_GPMC_WE_n	: std_logic;
	signal ARM_GPMC_ADV_n	: std_logic;
	signal ARM_GPMC_D		: std_logic_vector (15 downto 0);
	signal ARM_CPLD_INT		: std_logic;
	signal ARM_CPLD_CS_n	: std_logic;
	signal ARM_CPLD_WAIT	: std_logic;
	-- Entrées TOR
	signal CPLD_DIGIT_IN	: std_logic_vector (23 downto 0);
	-- Sorties TOR
	signal CPLD_DIGIT_OUT_RST_n	: std_logic;
	-- Ecran LCD
	signal CPLD_LCD_DB		: std_logic_vector (7 downto 0);
	signal LCD_stratch_reg	: std_logic_vector (7 downto 0);
	signal CPLD_LCD_E1		: std_logic;
	signal CPLD_LCD_E2		: std_logic;
	signal CPLD_LCD_READ	: std_logic;
	signal CPLD_LCD_REG_SEL	: std_logic;
	-- Clavier
	signal CPLD_CLAVIER_RL	: std_logic_vector (3 downto 0);
	signal CPLD_CLAVIER_S	: std_logic_vector (5 downto 0);
	signal CPLD_CLAVIER_LED	: std_logic_vector (3 downto 0);
	-- DAC
	signal CPLD_DAC_RESET_n : std_logic;
	signal CPLD_DAC_CLK	 	: std_logic;
	signal CPLD_DAC_CS1_n	: std_logic;
	signal CPLD_DAC_CS2_n	: std_logic;
	signal CPLD_DAC_LOADDACS_n	: std_logic;
	signal CPLD_DAC_LOADREG_n	: std_logic;
	signal CPLD_DAC_SDI1	: std_logic;
	signal CPLD_DAC_SDI2	: std_logic;
	-- UART signals
	signal ARM_UART1_TX	: std_logic;
	signal CPLD_RS485_RXEN	: std_logic;
	signal CPLD_RS485_TXEN	: std_logic;
	-- CPLD spare signals
	signal CPLD_TP1		: std_logic;
	signal CPLD_TP2		: std_logic;
	signal CPLD_TP3		: std_logic;
	signal CPLD_TP4		: std_logic;

	begin	
		clk: process
		begin
			loop
				main_clock <= '0';
				wait for period_GPMC/2;
				main_clock <= '1';
				wait for period_GPMC/2;
			end loop;
		end process;
	
		gen_cpld_clk: process
		begin
			ARM_CPLD_CLK <= '0';
			wait for period_CPLD/2;
			loop
				ARM_CPLD_CLK <= '0';
				wait for period_CPLD/2;
				ARM_CPLD_CLK <= '1';
				wait for period_CPLD/2;
			end loop;
		end process;
		
		pseudo_LCD: process
		begin
			LCD_stratch_reg	<= (others => '0');
			CPLD_LCD_DB 	<= (others => 'Z');
			while 1=1 loop
				CPLD_LCD_DB <= (others => 'Z');
				wait until CPLD_LCD_E1 = '1' and CPLD_LCD_E2 = '1';
				if CPLD_LCD_READ = '1' then
					if CPLD_LCD_REG_SEL = '1' then
						CPLD_LCD_DB	<= X"BB";
					else
						CPLD_LCD_DB	<= X"22";
					end if;
				else
					LCD_stratch_reg <= CPLD_LCD_DB;
				end if;
				wait until CPLD_LCD_E1 = '0' or CPLD_LCD_E2 = '0';
			end loop;
		end process;
		
		reset_n		<= not reset;
		ARM_RESET_n	<= not reset;
		
		main_tb: process
		begin
			PWR_OK_24VIN_n	<= '0';
			CPLD_DIGIT_IN	<= (others => '0');
			reset 			<= '1';
			ARM_GPMC_WE_n 	<= '1';
			ARM_GPMC_OE_n	<= '1';
			ARM_GPMC_ADV_n	<= '1';
			ARM_GPMC_D		<= (others => 'Z');
			ARM_CPLD_CS_n	<= '1';
			ARM_UART1_TX 	<= '1';
		
		---- Test RESET ----
			assert false report ("Test RESET") severity note;
			wait for 1 us;
			reset <= '0';
			wait for 1 us;
			-- registre gestion PWR_OK_24VIN_n
			address_to_read <= Address_PWR_start;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			wait for 1 us;
			PWR_OK_24VIN_n <= '1';
			wait for 5 us;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			wait for 10 ns;
			address_to_write <= Address_PWR_start;
			data_to_write	<= X"0001";		-- activate reset on pwr_off
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			wait for 10 ns;
			reset <= '1';
			wait for 1 us;
			reset <= '0';
			wait for 1 us;
			PWR_OK_24VIN_n <= '0';
			wait for 5 us;
			reset <= '1';
			wait for 1 us;
			reset <= '0';
			wait for 5 us;

		---- Test APB ID ----
			assert false report ("Test APB ID") severity note;
			-- registre identifiant
			address_to_read <= Address_ID_start;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			-- registre scratch
			address_to_read	<= Address_ID_start+2;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			address_to_write <= Address_ID_start+2;
			data_to_write	<= X"AAAA";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_read	<= Address_ID_start+2;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
		---- Test RS485 ----
			assert false report ("Test RS485") severity note;
			-- test écriture
			address_to_write <= Address_RS_start;
			data_to_write	<= X"0007";	-- test avec 115200 bauds
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			-- test trame
			wait for 0.5 us;
			ARM_UART1_TX <= '0';
			wait for 8 us;
			ARM_UART1_TX <= '1';
			wait for 8 us;
			ARM_UART1_TX <= '0';
			wait for 8 us;
			ARM_UART1_TX <= '1';
			wait for 8 us;
			ARM_UART1_TX <= '0';
			wait for 8 us;
			ARM_UART1_TX <= '1';
			wait for 8 us;
			ARM_UART1_TX <= '0';
			wait for 8 us;
			ARM_UART1_TX <= '1';
			wait for 8 us;
			ARM_UART1_TX <= '0';
			wait for 8 us;
			ARM_UART1_TX <= '1';
			wait for 10 us;
			
		---- Test clavier ----
			assert false report ("Test CLAVIER") severity note;
			CPLD_CLAVIER_RL	<= "1010";
			-- test écriture
			address_to_write <= Address_CLV_start;
			data_to_write	<= X"ABCD";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_write <= Address_CLV_start+2;
			data_to_write	<= X"1234";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_write <= Address_CLV_start+4;
			data_to_write	<= X"6789";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			-- test lecture
			address_to_read <= Address_CLV_start;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			address_to_read <= Address_CLV_start+2;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			address_to_read <= Address_CLV_start+4;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
		
		---- Test Ecran LCD ----
			assert false report ("Test ECRAN LCD") severity note;
			-- test écriture
			address_to_write <= Address_LCD_start;
			data_to_write	<= X"1234";		-- 34 dans registre données
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_write <= Address_LCD_start+2;
			data_to_write	<= X"1283";		-- write dans registre 1
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_write <= Address_LCD_start+2;
			data_to_write	<= X"45B7";		-- enable 1 et 2
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_write <= Address_LCD_start+2;
			data_to_write	<= X"0000";		-- tous les bits de controle à 0
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_write <= Address_LCD_start+2;
			data_to_write	<= X"0040";		-- read dans registre 0
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_write <= Address_LCD_start+2;
			data_to_write	<= X"7777";		-- enable 1 et 2
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			-- test lecture
			address_to_read <= Address_LCD_start;		-- Lecture donnée sur bus
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			address_to_read <= Address_LCD_start+2;		-- Lecture registre controle
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			
		---- Test FILTRE ETOR ----
			assert false report ("Test Filtres E TOR") severity note;
			address_to_write <= Address_FLT0_start;
			data_to_write	<= X"0005";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			
			address_to_write <= Address_FLT1_start;
			data_to_write	<= X"000A";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			
		---- Test ETOR ----
			assert false report ("Test E TOR") severity note;
			CPLD_DIGIT_IN	<= X"AAAAAA";
			-- attente filtrage
			wait for 2 us;
			assert false report ("Lecture E TOR") severity note;
			address_to_read	<= Address_ETOR_start;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			
			address_to_write <= Address_ETOR_start;
			data_to_write	<= X"5678";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
		
			
		---- Test compteurs ETOR ----
			assert false report ("Test compteur 0 E TOR") severity note;
			address_to_write <= Address_CPT0_start;
			data_to_write	<= X"9ABF";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 2 us;
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 1 us;
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 5 us;
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 2 us;
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 1 us;
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 5 us;
			address_to_read	<= Address_CPT0_start;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			address_to_write <= Address_CPT0_start;
			data_to_write	<= X"FFFF";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 5 us;
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 5 us;
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 5 us;
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 5 us;
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 5 us;
			CPLD_DIGIT_IN	<= not CPLD_DIGIT_IN;	-- 1 front
			wait for 5 us;
			address_to_read	<= Address_CPT0_start;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			
		---- Test DAC ----
			assert false report ("Test DAC") severity note;
			address_to_write <= Address_DAC_start;
			data_to_write	<= X"8555";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_write <= Address_DAC_start+2;
			data_to_write	<= X"8AAA";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_write <= Address_DAC_start + X"A";
			data_to_write	<= X"8111";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			address_to_write <= Address_DAC_start + X"C";
			data_to_write	<= X"0888";
			gpmc_write_access (main_clock, address_to_write,data_to_write, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_GPMC_WE_n, ARM_CPLD_WAIT, counter_out);
			
			-- wait busy = 0
			address_to_read	<= Address_DAC_start;
			gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
			wait for 500 ns;
			read_data <= (others => '1');
			while (read_data(14) = '1') loop
				address_to_read	<= Address_DAC_start;
				gpmc_read_access (main_clock, address_to_read, ARM_GPMC_D, ARM_CPLD_CS_n, ARM_GPMC_ADV_n, ARM_GPMC_OE_n, ARM_CPLD_WAIT, read_data, counter_out);
				wait for 100 ns;
			end loop;
			
		---- Fin du Test----
			assert false report ("Fin Test") severity note;
			wait;
		end process;
			
		DUT: PP1164
			port map(	-- Power management signals			
				PWR_EN_VCCECRAN	=> PWR_EN_VCCECRAN,
				PWR_EN_15V		=> PWR_EN_15V,
				PWR_OK_24VIN_n	=> PWR_OK_24VIN_n,
				
				ARM_CPLD_CLK	=> ARM_CPLD_CLK,
				ARM_RESET_n		=> ARM_RESET_n,
				
				-- ARM GPMC signals
				ARM_GPMC_OE_n	=> ARM_GPMC_OE_n,
				ARM_GPMC_WE_n	=> ARM_GPMC_WE_n,
				ARM_GPMC_ADV_n	=> ARM_GPMC_ADV_n,
				ARM_GPMC_D		=> ARM_GPMC_D,
				ARM_CPLD_INT	=> ARM_CPLD_INT,
				ARM_CPLD_CS_n	=> ARM_CPLD_CS_n,
				ARM_CPLD_WAIT	=> ARM_CPLD_WAIT,
							
				-- Entrées TOR
				CPLD_DIGIT_IN	=> CPLD_DIGIT_IN,
				
				-- Sorties TOR
				CPLD_DIGIT_OUT_RST_n	=> CPLD_DIGIT_OUT_RST_n,
				
				-- Ecran LCD
				CPLD_LCD_DB		=> CPLD_LCD_DB,
				CPLD_LCD_E1		=> CPLD_LCD_E1,
				CPLD_LCD_E2		=> CPLD_LCD_E2,
				CPLD_LCD_READ	=> CPLD_LCD_READ,
				CPLD_LCD_REG_SEL	=> CPLD_LCD_REG_SEL,
				
				-- Clavier
				CPLD_CLAVIER_RL	=> CPLD_CLAVIER_RL,
				CPLD_CLAVIER_S	=> CPLD_CLAVIER_S,
				CPLD_CLAVIER_LED	=> CPLD_CLAVIER_LED,
				
				-- DAC
				CPLD_DAC_RESET_n	=> CPLD_DAC_RESET_n,
				CPLD_DAC_CLK	=> CPLD_DAC_CLK,
				CPLD_DAC_CS1_n	=> CPLD_DAC_CS1_n,
				CPLD_DAC_CS2_n	=> CPLD_DAC_CS2_n,
				CPLD_DAC_LOADDACS_n	=> CPLD_DAC_LOADDACS_n,
				CPLD_DAC_LOADREG_n	=> CPLD_DAC_LOADREG_n,
				CPLD_DAC_SDI1	=> CPLD_DAC_SDI1,
				CPLD_DAC_SDI2	=> CPLD_DAC_SDI2,
				
				-- UART signals
				ARM_UART1_TX	=> ARM_UART1_TX,
				CPLD_RS485_RXEN	=> CPLD_RS485_RXEN,
				CPLD_RS485_TXEN	=> CPLD_RS485_TXEN,
				
				-- CPLD spare signals
				CPLD_TP1		=> CPLD_TP1,
				CPLD_TP2		=> CPLD_TP2,
				CPLD_TP3		=> CPLD_TP3,
				CPLD_TP4		=> CPLD_TP4
			);
			
end architecture testbench;
