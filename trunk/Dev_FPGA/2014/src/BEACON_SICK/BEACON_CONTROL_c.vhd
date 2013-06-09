-- Oufffteam
-- Projet carte mere
-- Device: BEACON CONTROL

-- overflow value for the motor:
  -- 16 lines per revolution
  -- 2 channels --> 16*2*2 = 64 inc. per revolution
  -- Gear = 22:1 --> 64*22 = 1408 inc. per motor revolution

-- 05/06/2013			PEG			Creation

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.FPGA_OUFFF_p.all;
	
entity BEACON_CONTROL is
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
end entity BEACON_CONTROL;


architecture wrapper of BEACON_CONTROL is

	component QUAD_COUNTER is
		port (
			clock:		in std_logic;
			reset:		in std_logic;
			A:		in std_logic;
			B:		in std_logic;
			count_out:	out std_logic_vector (15 downto 0);
			count_latch:	in std_logic
		);
	end component;
  
 	-- Declaration de etats  
	type state_machine is (sleep, sync0, sync1, sync2, sync3, sync4, sync5, sync6, sync7, latch);
	-- Declaration de signaux   
	signal current_state, next_state : state_machine;
	
	signal counter_reg		: std_logic_vector (15 downto 0); 
	
	signal sensor_sync, sensor_sync_old : std_logic;
	signal SENSOR_edge: std_logic;
	
	
	signal status_reg		: std_logic_vector (7 downto 0); 	-- R	Address 00000
	signal counter_reg_0		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 00001, MSB: 00010
	signal counter_reg_1		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 00011, MSB: 00100
	signal counter_reg_2		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 00101, MSB: 00110
	signal counter_reg_3		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 00111, MSB: 01000
	signal counter_reg_4		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 01001, MSB: 01010
	signal counter_reg_5		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 01011, MSB: 01100
	signal counter_reg_6		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 01101, MSB: 01110
	signal counter_reg_7		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 01111, MSB: 10000
	signal dummy_reg		: std_logic_vector (7 downto 0);	-- R/W 	Address others
	
	signal counter_reg_0_int	: std_logic_vector (15 downto 0);
	signal counter_reg_1_int	: std_logic_vector (15 downto 0);
	signal counter_reg_2_int	: std_logic_vector (15 downto 0);
	signal counter_reg_3_int	: std_logic_vector (15 downto 0);
	signal counter_reg_4_int	: std_logic_vector (15 downto 0);
	signal counter_reg_5_int	: std_logic_vector (15 downto 0);
	signal counter_reg_6_int	: std_logic_vector (15 downto 0); 
	signal counter_reg_7_int	: std_logic_vector (15 downto 0);
	
	signal reset_latch_reg : std_logic;

	signal counter_latch_sync1, counter_latch_sync2 : std_logic;
	
	begin
	
	registers_interface: process (reset, clock, reset_latch_reg)
		begin
			if (reset = '1') then
				BUS_D <= (others => 'Z');
				status_reg <= (others => '0');
				counter_reg_0 <= (others => '0'); counter_reg_0_int <= (others => '0');
				counter_reg_1 <= (others => '0'); counter_reg_1_int <= (others => '0');
				counter_reg_2 <= (others => '0'); counter_reg_2_int <= (others => '0');
				counter_reg_3 <= (others => '0'); counter_reg_3_int <= (others => '0');
				counter_reg_4 <= (others => '0'); counter_reg_4_int <= (others => '0');
				counter_reg_5 <= (others => '0'); counter_reg_5_int <= (others => '0');
				counter_reg_6 <= (others => '0'); counter_reg_6_int <= (others => '0');
				counter_reg_7 <= (others => '0'); counter_reg_7_int <= (others => '0');
				dummy_reg <= (others => '0');
			elsif (clock'event and clock ='1') then
				if (BUS_CS = '1' and BUS_RD = '1') then
					case BUS_A is
						when "00000"	=> BUS_D <= status_reg;
						when "00001"	=> BUS_D <= counter_reg_0 (7 downto 0);
						when "00010"	=> BUS_D <= counter_reg_0 (15 downto 8);
						when "00011"	=> BUS_D <= counter_reg_1 (7 downto 0);
						when "00100"	=> BUS_D <= counter_reg_1 (15 downto 8);
						when "00101"	=> BUS_D <= counter_reg_2 (7 downto 0);
						when "00110"	=> BUS_D <= counter_reg_2 (15 downto 8);
						when "00111"	=> BUS_D <= counter_reg_3 (7 downto 0);
						when "01000"	=> BUS_D <= counter_reg_3 (15 downto 8);
						when "01001"	=> BUS_D <= counter_reg_4 (7 downto 0);
						when "01010"	=> BUS_D <= counter_reg_4 (15 downto 8);
						when "01011"	=> BUS_D <= counter_reg_5 (7 downto 0);
						when "01100"	=> BUS_D <= counter_reg_5 (15 downto 8);
						when "01101"	=> BUS_D <= counter_reg_6 (7 downto 0);
						when "01110"	=> BUS_D <= counter_reg_6 (15 downto 8);
						when "01111"	=> BUS_D <= counter_reg_7 (7 downto 0);
						when "10000"	=> BUS_D <= counter_reg_7 (15 downto 8);
						when others	=> BUS_D <= dummy_reg;
					end case;
				else
					BUS_D <= (others  => 'Z');
				end if;
			end if;
	end process registers_interface;
	
	counter: QUAD_COUNTER
		port map (
			clock		=> clock,
			reset		=> reset or counter_reset,
			A 		=> ENCODER_channel_A,
			B		=> ENCODER_channel_B,
			count_out 	=> counter_reg,
			count_latch	=> '1'
	);
	
	counter_reset: process(clock, reset)
		begin
			if(reset='1') then
				counter_reset <= '0';
			elsif (clock'event and clock = '1') then
				if(counter_reg = 1408) then
					counter_reset <= '1';
				else
					counter_reset <= '0';
				end if;
			end if;
	end process;
	
	synchro_sensor: process(clock, reset)
		begin
			if(reset='1') then
				sensor_sync <= '0';
			elsif (clock'event and clock = '1') then
				sensor_sync <= not SENSOR_in;
			end if;
	end process;
		
		
	SENSOR_edge_detection: process(clock, reset)
		begin
			if(reset='1') then
				sensor_sync_old <= synsor_sync;
			elsif (clock'event and clock='1') then
				sensor_sync_old <= synsor_sync;
			end if;
	end process;

	SENSOR_edge <= (synsor_sync xor sensor_sync_old); -- and (sensor_sync_old);
	
	state_update: process(clock, reset)
		begin
			if(reset='1') then
				current_state <= sleep;
			elsif (clock'event and clock='1') then
				current_state <= next_state; 
			end if;
	end process;

	next_state_proc: process(SENSOR_edge, period_counter, sig_counter)

		begin
		
			if(counter_reset='1') then
				next_state <= latch;
			else
				case current_state is
					when sleep =>		next_state <= sync0;
					
					when sync0 =>		if(SENSOR_edge='1') then next_state<=sync1;
								else next_state<=sync0; end if;
	
					when sync1 =>		if(SENSOR_edge='1') then next_state<=sync2;
								else next_state<=sync1; end if;
							
					when sync2 =>		if(SENSOR_edge='1') then next_state<=sync3;
								else next_state<=sync2; end if;
							
					when sync3 =>		if(SENSOR_edge='1') then next_state<=sync4;
								else next_state<=sync3; end if;
							
					when sync4 =>		if(SENSOR_edge='1') then next_state<=sync5;
								else next_state<=sync4; end if;
							
					when sync5 =>		if(SENSOR_edge='1') then next_state<=sync6;
								else next_state<=sync5; end if;
							
					when sync6 =>		if(SENSOR_edge='1') then next_state<=sync7;
								else next_state<=sync6; end if;
							
					when sync7 =>		if(SENSOR_edge='1') then next_state<=err;
								else next_state<=sync7; end if;
							
					when err =>		next_state <= latch;
					when latch =>		next_state <= sleep;
					when others =>		next_state<=sleep;
				end case;
			end if;
	end process;
	
	state_proc: process(current_state)
		begin
			case current_state is
				when sleep =>		next_state <= sync0;
						
				when sync0 =>		counter_reg_0_int <= counter_reg;
							status_reg_int(0) <= sensor_sync;
							
				when sync1 =>		counter_reg_1_int <= counter_reg;
							status_reg_int(1) <= sensor_sync;
							
				when sync2 =>		counter_reg_2_int <= counter_reg;
							status_reg_int(2) <= sensor_sync;
							
				when sync3 =>		counter_reg_3_int <= counter_reg;
							status_reg_int(3) <= sensor_sync;
							
				when sync4 =>		counter_reg_4_int <= counter_reg;
							status_reg_int(4) <= sensor_sync;
							
				when sync5 =>		counter_reg_5_int <= counter_reg;
							status_reg_int(5) <= sensor_sync;
							
				when sync6 =>		counter_reg_6_int <= counter_reg;
							status_reg_int(6) <= sensor_sync;
		
				when sync7 =>		counter_reg_7_int <= counter_reg;
							status_reg_int(7) <= sensor_sync;
							
				when err =>		status_reg_int <= X"FF";
				
				when latch =>		if (not (BUS_CS = '1' and BUS_RD = '1')) then
								status_reg <= status_reg_int;
								counter_reg_0 <= counter_reg_0_int;
								counter_reg_1 <= counter_reg_1_int;
								counter_reg_2 <= counter_reg_2_int;
								counter_reg_3 <= counter_reg_3_int;
								counter_reg_4 <= counter_reg_4_int;
								counter_reg_5 <= counter_reg_5_int;
								counter_reg_6 <= counter_reg_6_int;
								counter_reg_7 <= counter_reg_7_int;
							end if;

				when others =>		status_reg_int <= X"FF";
			end case;
	end process;
	
end architecture wrapper;