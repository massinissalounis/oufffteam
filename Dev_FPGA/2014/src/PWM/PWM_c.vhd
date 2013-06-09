-- Oufffteam
-- Projet carte mere
-- Device: PWM

-- Fixed 30kHZ frequency
-- 256 PWM values

-- Need for a base clk at 256*30kHz = 7680kHz --> Time base = 130ns
-- FPGA CLK = 40.69 MHz --> freq_div by 5.29 = 5

-- 04/06/2013			PEG			Creation

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.FPGA_OUFFF_p.all;

entity PWM is
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
end entity PWM;

architecture wrapper of PWM is

	component BAUD_RATE_GENERATOR is
		generic (
			division_factor:integer:=5
		);
		port (
			clock: in  std_logic;
			reset: in  std_logic;
			baud_rate: out std_logic
		);
	end component;
  
 	-- Declaration de etats  
	type state_machine is (sleep, high, low);
	-- Declaration de signaux   
	signal current_state, next_state : state_machine;
	
	signal period_reg: std_logic_vector (7 downto 0); 
	
	signal base_clk, base_clk_old : std_logic;
	signal BC_edge: std_logic;
	

	signal sig_counter : natural range 256 downto 0;
	
	
	begin
	registers_interface: process (reset, clock)
		begin
			if (reset = '1') then
				BUS_D <= (others => 'Z');
				period_reg <= (others => '0');
			elsif (clock'event and clock ='1') then
				if (BUS_CS = '1' and BUS_WR = '1') then
					period_reg <= BUS_D;
				end if;
			end if;
	end process registers_interface;
	
	Base_clk_gen: BAUD_RATE_GENERATOR 
		generic map ((130*(FPGA_FREQUENCY/1000000))/1000)
		port map (clock, reset, base_clk);
		
	BC_edge_detection: process(clock, reset)
		begin
			if(reset='1') then
				base_clk_old <= base_clk;
			elsif (clock'event and clock='1') then
				base_clk_old <= base_clk; 
			end if;
	end process;

	BC_edge <= (base_clk xor base_clk_old) and (base_clk_old);
	
	state_update: process(clock, reset)
		begin
			if(reset='1') then
				current_state <= sleep;
			elsif (clock'event and clock='1') then
				current_state <= next_state; 
			end if;
	end process;

	next_state_proc: process(BC_edge, period_counter, sig_counter)

		begin
			case current_state is
			
				when sleep =>		next_state <= high;
							
				when high =>		if(sig_counter = to_integer(unsigned(period_reg))) then -- Syncho clock
								next_state<=low;
									else
								next_state<=sig;
							end if;  
					
				when low =>		if(sig_counter = 255) then
								next_state<=sleep;
									else
								next_state<=low;
							end if;
							
				when others =>		next_state<=sleep;
			end case;
	end process;
	
	sig_counter_proc: process (BC_edge, reset, clock)
		begin
			if(reset='1' or current_state=sleep) then
				sig_counter <= 0;
			elsif(clock'event and clock='1' and BC_edge='1' and current_state=high) then
				sig_counter <= sig_counter + 1;
			end if;
	end process;
	
	OUT_PWM <= '0' when (current_state=low) else '1';
	
end architecture wrapper;