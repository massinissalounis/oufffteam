-- Oufffteam
-- Projet carte mère
-- Device: BEACON CONTROL

-- 04/06/2013			PEG			Creation

library ieee;
use ieee.std_logic_1164.all;

package BEACON_CONTROL_P is
	
	component BEACON_CONTROL is
		port (
				-- in
				clock			: in std_logic;
				reset			: in std_logic;
				-- in - Internal BUS			
				BUS_D		: inout std_logic_vector (7 downto 0);
				BUS_RD		: in std_logic;
				BUS_WR		: in std_logic;
				BUS_CS   	: in std_logic;
				-- sensor
				SENSOR_in	: in std_logic;
				-- coder
				ENCODER_channel_A	: in std_logic;
				ENCODER_channel_B	: in std_logic
				);
	end component BEACON_CONTROL;

end BEACON_CONTROL_P;