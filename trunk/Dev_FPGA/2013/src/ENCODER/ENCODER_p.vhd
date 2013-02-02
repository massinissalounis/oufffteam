-- Oufffteam
-- Projet carte mère
-- Device: ENCODER

-- 29/12/2009			CBE			Création
-- 29/01/2013			PEG			Refonte


library ieee;
use ieee.std_logic_1164.all;

package ENCODER_P is
 
	component ENCODER is
		port (
      -- in
			clock			: in std_logic;
			reset			: in std_logic;
      -- debug
			debug_latch		: out std_logic;
      -- in - Internal BUS			
			BUS_D		: inout std_logic_vector (7 downto 0);
			BUS_A		: in std_logic_vector (2 downto 0);
			BUS_RD		: in std_logic;
			BUS_WR		: in std_logic;
			BUS_CS   : in std_logic;
			-- coder
			ENCODER_R_channel_A	: in std_logic;
			ENCODER_R_channel_B	: in std_logic;
			ENCODER_L_channel_A	: in std_logic;
			ENCODER_L_channel_B	: in std_logic
		);
	end component ENCODER;

end ENCODER_P;