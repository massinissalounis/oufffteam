-- Oufffteam
-- Projet carte mère
-- Device: TCS3200 COLOR SENSOR

-- Input Freq range 100KHz
-- Output [0-203]

-- 31/01/2013			PEG			Creation

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity TCS3200_INTERFACE is
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
end entity TCS3200_INTERFACE;

architecture wrapper of TCS3200_INTERFACE is
  
	signal period_reg		: std_logic_vector (7 downto 0); 
	
	signal IN_SIGNAL_old	: std_logic;
	signal IN_SIGNAL_RISING_EDGE : std_logic;
	signal IN_SIGNAL_FALLING_EDGE : std_logic;
	
	signal half_period_counter : unsigned (7 downto 0) := (others => '0');
	
	begin
	registers_interface: process (reset, clock)
		begin
			if (reset = '1') then
				BUS_D <= (others => 'Z');
			elsif (clock'event and clock ='1') then
				if (BUS_CS = '1' and BUS_RD = '1') then
					BUS_D <= period_reg;
				else
				  BUS_D <= (others => 'Z');
				end if;
			end if;
	end process registers_interface;
	
	input_signal_latch: process (reset, clock)
		begin
			if(reset='1') then
				IN_SIGNAL_old <= IN_SIGNAL;
			elsif (clock'event and clock ='1') then
				IN_SIGNAL_old <= IN_SIGNAL;
			end if;
	end process;
	
	IN_SIGNAL_RISING_EDGE <= (IN_SIGNAL xor IN_SIGNAL_old) and (not IN_SIGNAL_old);
	IN_SIGNAL_FALLING_EDGE <= (IN_SIGNAL xor IN_SIGNAL_old) and (IN_SIGNAL_old);
		
	freq_measurement: process (reset, clock, IN_SIGNAL_RISING_EDGE, IN_SIGNAL_FALLING_EDGE)
		begin
			if (reset='1') then
			  period_reg <= (others => '0');
				half_period_counter <= (others => '0');
			elsif (IN_SIGNAL_RISING_EDGE='1') then
				half_period_counter <= (others => '0');
			elsif (IN_SIGNAL_FALLING_EDGE = '1' and BUS_CS = '0') then
				period_reg <= std_logic_vector(half_period_counter);
			elsif (clock'event and clock='1') then
				half_period_counter <= half_period_counter + 1;
			end if;
	end process;

end architecture wrapper;