-- Oufffteam
-- Projet carte mère
-- Device: SERVO CONTROL

-- 02/02/2013			PEG			Creation

library ieee;
use ieee.std_logic_1164.all;

package SERVO_CONTROL_P is
	
	component SERVO_CONTROL is
		port (
				-- in
				clock			: in std_logic;
				reset			: in std_logic;
				-- in - Internal BUS			
				BUS_D		: inout std_logic_vector (7 downto 0);
				BUS_RD		: in std_logic;
				BUS_WR		: in std_logic;
				BUS_CS   : in std_logic;
				-- coder
				OUT_SIGNAL	: out std_logic
				);
	end component SERVO_CONTROL;

end SERVO_CONTROL_P;