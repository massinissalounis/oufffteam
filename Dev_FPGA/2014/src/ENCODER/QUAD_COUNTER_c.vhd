-- Oufffteam
-- Projet carte mère
-- Device: ENCODER

-- 2008				PEG			Création
-- 29/01/2013			PEG			Refonte

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity QUAD_COUNTER is
	port (
		clock:		in std_logic;
		reset:		in std_logic;
		A:		in std_logic;
		B:		in std_logic;
		count_out:	out std_logic_vector (15 downto 0);
		count_latch:	in std_logic
			);
end entity QUAD_COUNTER;

architecture behavioral of QUAD_COUNTER is

signal A_temp : std_logic_vector (2 downto 0 ) := (others => '0'); -- interference suppression
signal B_temp : std_logic_vector (2 downto 0 ) := (others => '0'); -- interference supprssion

signal tmp : unsigned (15 downto 0) := (others => '0');

	attribute TIG : string;
	attribute ASYNC_REG : string;
	
	attribute TIG of A,B : signal is "TRUE";
	attribute ASYNC_REG of A_temp, B_temp : signal is "TRUE";

begin

	latch_channel : process ( clock, reset )
		begin
			if(reset = '1') then
				A_temp <= ( others => A );
				B_temp <= ( others => B );
			elsif (clock'event and clock='1' ) then
				A_temp(0)<=A; A_temp(1) <= A_temp(0);	A_temp(2) <= A_temp(1);
				B_temp(0)<=B; B_temp(1) <= B_temp(0); B_temp(2) <= B_temp(1);			
			end if;		
	end process;
	
	decoding : process ( clock, reset )
	begin
	
		if(reset = '1') then
			tmp <= ( others => '0' );
		elsif (clock'event and clock='0' ) then
			if 	((A_temp(1) = '0' and B_temp(1) = '0' and A_temp(2) = '1' and B_temp(2) = '0')
				or	(A_temp(1) = '1' and B_temp(1) = '0' and A_temp(2) = '1' and B_temp(2) = '1')
				or	(A_temp(1) = '1' and B_temp(1) = '1' and A_temp(2) = '0' and B_temp(2) = '1')
				or	(A_temp(1) = '0' and B_temp(1) = '1' and A_temp(2) = '0' and B_temp(2) = '0') ) then tmp <= tmp - 1;
			elsif((A_temp(1) = '1' and B_temp(1) = '0' and A_temp(2) = '0' and B_temp(2) = '0')
				or	 (A_temp(1) = '1' and B_temp(1) = '1' and A_temp(2) = '1' and B_temp(2) = '0')
				or	 (A_temp(1) = '0' and B_temp(1) = '1' and A_temp(2) = '1' and B_temp(2) = '1')
				or	 (A_temp(1) = '0' and B_temp(1) = '0' and A_temp(2) = '0' and B_temp(2) = '1') ) then tmp <= tmp + 1;
			end if;   
		end if;				
	end process;
	
	latch_counter : process (clock,reset)
	begin
		if(reset = '1') then
			count_out <= ( others => '0' );
		elsif (clock'event and clock='1' ) then
			if 	( count_latch = '1' ) then
				count_out <= std_logic_vector(tmp);
			end if;   
		end if;				
	end process;
	
end behavioral;
