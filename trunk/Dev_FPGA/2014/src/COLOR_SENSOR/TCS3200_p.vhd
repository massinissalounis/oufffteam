-- Oufffteam
-- Projet carte mère
-- Device: TCS3200 COLOR SENSOR

-- 31/01/2013			PEG			Creation

library ieee;
use ieee.std_logic_1164.all;

package TCS3200_P is
	
	component TCS3200_INTERFACE is
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
				IN_SIGNAL	: in std_logic
				);
	end component TCS3200_INTERFACE;

end TCS3200_P;