-- Oufffteam
-- Projet carte mère
-- Device: ENCODER

-- 29/12/2009			CBE			Création
-- 29/01/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ENCODER is
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
end entity ENCODER;

architecture wrapper of ENCODER is
  
  component QUAD_COUNTER is
	port 	( 	clock:		in std_logic;
			reset:	in std_logic;
			A:	in std_logic;
			B:	in std_logic;
			count_out:		out std_logic_vector (15 downto 0);
			count_latch:	in std_logic
	);
  end component QUAD_COUNTER; 

	signal latch_reg		: std_logic_vector (7 downto 0); 	-- R/W	Address 000
	signal counter_R_reg		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 001, MSB: 010
	signal counter_L_reg		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 011, MSB: 100
	signal dummy_reg		: std_logic_vector (7 downto 0);	-- R/W 	Address others
	
	signal reset_latch_reg : std_logic;

	signal counter_latch_sync1, counter_latch_sync2 : std_logic;
	
	begin
	
	registers_interface: process (reset, clock, reset_latch_reg)
		begin
			if (reset = '1') then
				BUS_D <= (others => 'Z');
				latch_reg <= (others => '0');
				dummy_reg <= (others => '0');
			elsif (reset_latch_reg = '1') then
				latch_reg <= (others => '0');
			elsif (clock'event and clock ='1') then
				if (BUS_CS = '1' and  BUS_WR ='1') then
					case BUS_A is
						when "000"	=> latch_reg <= BUS_D;
						when others	=> dummy_reg <= BUS_D;
					end case;
				elsif (BUS_CS = '1' and BUS_RD = '1') then
					case BUS_A is
						when "000"	=> BUS_D <= latch_reg;
						when "001"	=> BUS_D <= counter_R_reg (7 downto 0);
						when "010"	=> BUS_D <= counter_R_reg (15 downto 8);
						when "011"	=> BUS_D <= counter_L_reg (7 downto 0);
						when "100"	=> BUS_D <= counter_L_reg (15 downto 8);
						when others	=> BUS_D <= dummy_reg;
					end case;
				else
					BUS_D <= (others  => 'Z');
				end if;
			end if;
	end process registers_interface;

	counter_R: QUAD_COUNTER
		port map (
			clock		=> clock,
			reset		=> reset,
			A 		=> ENCODER_R_channel_A,
			B		=> ENCODER_R_channel_B,
			count_out 	=> counter_R_reg,
			count_latch	=> counter_latch_sync2
		);
					
	counter_L: QUAD_COUNTER
		port map (
			clock 		=> clock,
			reset		=> reset,
			A 		=> ENCODER_L_channel_A,
			B		=> ENCODER_L_channel_B,
			count_out 	=> counter_L_reg,
			count_latch	=> counter_latch_sync2
		);

	-- gestion des latch
	synchro_latch: process (reset, clock, latch_reg)
		begin
			if (reset = '1') then
				counter_latch_sync1	<= '0';
				counter_latch_sync2	<= '0';
				reset_latch_reg		<= '0';
			elsif (clock'event and clock='1') then
				counter_latch_sync1	<= latch_reg (0);
				counter_latch_sync2	<= counter_latch_sync1;
				if (latch_reg(0) = '1' and BUS_WR ='0') then -- The second condition inhibits the reset while write operation is not finished
					reset_latch_reg <= '1';
				else
					reset_latch_reg <= '0';
				end if;
			end if;
	end process synchro_latch;
	
	debug_latch	<= counter_latch_sync2;
end architecture wrapper;