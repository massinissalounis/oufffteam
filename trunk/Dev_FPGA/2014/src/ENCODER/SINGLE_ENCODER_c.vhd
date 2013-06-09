-- Oufffteam
-- Projet carte mère
-- Device: ENCODER

-- 29/12/2009			CBE			Création
-- 29/01/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SINGLE_ENCODER is
  port (
		-- in
		clock			: in std_logic;
		reset			: in std_logic;
		-- in - Internal BUS			
		BUS_D		: inout std_logic_vector (7 downto 0);
		BUS_A		: in std_logic_vector (2 downto 0);
		BUS_RD		: in std_logic;
		BUS_WR		: in std_logic;
		BUS_CS   : in std_logic;
		-- coder
		ENCODER_channel_A	: in std_logic;
		ENCODER_channel_B	: in std_logic
		);
end entity SINGLE_ENCODER;

architecture wrapper of SINGLE_ENCODER is
  
  component QUAD_COUNTER is
	port 	( 	clock:		in std_logic;
			reset:	in std_logic;
			A:	in std_logic;
			B:	in std_logic;
			count_out:		out std_logic_vector (15 downto 0);
			count_latch:	in std_logic
	);
  end component QUAD_COUNTER; 

	signal latch_reg		: std_logic_vector (7 downto 0); 	-- R/W	Address 00
	signal counter_reg		: std_logic_vector (15 downto 0); 	-- R	Address LSB: 01, MSB: 10
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
						when "00"	=> latch_reg <= BUS_D;
						when others	=> dummy_reg <= BUS_D;
					end case;
				elsif (BUS_CS = '1' and BUS_RD = '1') then
					case BUS_A is
						when "00"	=> BUS_D <= latch_reg;
						when "01"	=> BUS_D <= counter_reg (7 downto 0);
						when "10"	=> BUS_D <= counter_reg (15 downto 8);
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
			reset		=> reset,
			A 		=> ENCODER_channel_A,
			B		=> ENCODER_channel_B,
			count_out 	=> counter_reg,
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
end architecture wrapper;