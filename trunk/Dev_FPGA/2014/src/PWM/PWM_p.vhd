-- Oufffteam
-- Projet carte mère
-- Device: PWM

-- 04/06/2013			PEG			Creation

library ieee;
use ieee.std_logic_1164.all;

package PWM_P is
	
	component PWM is
		port (
				-- in
				clock			: in std_logic;
				reset			: in std_logic;
				-- in - Internal BUS			
				BUS_D		: inout std_logic_vector (7 downto 0);
				BUS_RD		: in std_logic;
				BUS_WR		: in std_logic;
				BUS_CS   : in std_logic;
				-- pwm
				OUT_PWM	: out std_logic
				);
	end component PWM;

end PWM_P;