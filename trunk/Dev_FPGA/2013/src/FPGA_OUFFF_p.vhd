-- Oufffteam
-- Projet carte mère
-- Device: FPGA OUFFF CONSTANT

-- 29/12/2009			CBE			Création
-- 20/01/2013			PEG			Refonte


library ieee;
use ieee.std_logic_1164.all;

--library work;

package FPGA_OUFFF_p is
 
	constant FPGA_FREQUENCY:		integer := 20000000;

	constant BUS_RESET_ADD_START:		    std_logic_vector (15 downto 0) := X"0000";
	constant BUS_RESET_ADD_STOP:		     std_logic_vector (15 downto 0) := X"0000";
	constant BUS_LED_ADD_START:		      std_logic_vector (15 downto 0) := X"0001";
	constant BUS_LED_ADD_STOP:		       std_logic_vector (15 downto 0) := X"0001";
	constant BUS_ENCODER_1_ADD_START:	 std_logic_vector (15 downto 0) := X"0008";
	constant BUS_ENCODER_1_ADD_STOP:	  std_logic_vector (15 downto 0) := X"000F";
	constant BUS_AX12_1_ADD_START:		   std_logic_vector (15 downto 0) := X"0020";
	constant BUS_AX12_1_ADD_STOP:      std_logic_vector (15 downto 0) := X"0027";
	constant BUS_COLOR_SENSOR_1_ADD_START:		   std_logic_vector (15 downto 0) := X"0030";
	constant BUS_COLOR_SENSOR_1_ADD_STOP:      std_logic_vector (15 downto 0) := X"0030";
	constant BUS_COLOR_SENSOR_2_ADD_START:		   std_logic_vector (15 downto 0) := X"0031";
	constant BUS_COLOR_SENSOR_2_ADD_STOP:      std_logic_vector (15 downto 0) := X"0031";
	constant BUS_COLOR_SENSOR_3_ADD_START:		   std_logic_vector (15 downto 0) := X"0032";
	constant BUS_COLOR_SENSOR_3_ADD_STOP:      std_logic_vector (15 downto 0) := X"0032";
	constant BUS_COLOR_SENSOR_4_ADD_START:		   std_logic_vector (15 downto 0) := X"0033";
	constant BUS_COLOR_SENSOR_4_ADD_STOP:      std_logic_vector (15 downto 0) := X"0033";
	constant BUS_COLOR_CONTROL_ADD_START:		   std_logic_vector (15 downto 0) := X"0040";
	constant BUS_COLOR_CONTROL_ADD_STOP:      std_logic_vector (15 downto 0) := X"0040";
	constant BUS_BEACON_ADD_START:		   std_logic_vector (15 downto 0) := X"0050";
	constant BUS_BEACON_ADD_STOP:      std_logic_vector (15 downto 0) := X"0050";
	constant BUS_GPIO_ADD_START:		   std_logic_vector (15 downto 0) := X"0060";
	constant BUS_GPIO_ADD_STOP:      std_logic_vector (15 downto 0) := X"0060";	
	constant BUS_SERVO_0_ADD_START:		   std_logic_vector (15 downto 0) := X"0070";
	constant BUS_SERVO_0_ADD_STOP:      std_logic_vector (15 downto 0) := X"0070";	
	constant BUS_SERVO_1_ADD_START:		   std_logic_vector (15 downto 0) := X"0071";
	constant BUS_SERVO_1_ADD_STOP:      std_logic_vector (15 downto 0) := X"0071";
 
end FPGA_OUFFF_p;
