-- Decodeur en quadrature

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity quadrature_counter is
	generic ( 	Nb_bits : natural := 16 ;              -- nombre de bits de sortie
				Nb_bascules : natural := 2            -- bascules d'antiparasites supplementaires si =2, sinon 1
			);
	port 	( 	Clock:		in std_logic; -- Horloge de référence
				Resetbar:	in std_logic; -- Reset actif bas du module
				A:	in std_logic; -- Canal A du codeur
				B:	in std_logic; -- Canal B du codeur
				Count_out:		out std_logic_vector (Nb_bits-1 downto 0);
				Count_latch:	in std_logic
			);
end entity quadrature_counter;

architecture behavioral of quadrature_counter is

signal A_temp : std_logic_vector (2 downto 0 ) := (others => '0');
signal B_temp : std_logic_vector (2 downto 0 ) := (others => '0');

signal tmp : unsigned (Nb_bits-1 downto 0) := (others => '0');

begin

	latch_channel : process ( Clock, Resetbar )
		begin
			if(Resetbar = '0') then
			
				A_temp <= ( others => A );
				B_temp <= ( others => B );
			
			elsif (Clock'event and Clock='1' ) then
				A_temp(0)<=A;
				B_temp(0)<=B;
				
				FOR i IN 1 TO 2 LOOP
					A_temp(i) <= A_temp(i-1);
					B_temp(i) <= B_temp(i-1);
				END LOOP;
				
			end if;		
	end process;
	
	decoding : process ( Clock, Resetbar )
	begin
	
		if(Resetbar = '0') then
		
			tmp <= ( others => '0' );
		
		elsif (Clock'event and Clock='1' ) then
			if 	( 	(A_temp(1) = '0' and B_temp(1) = '0' and A_temp(2) = '1' and B_temp(2) = '0')
				or	(A_temp(1) = '1' and B_temp(1) = '0' and A_temp(2) = '1' and B_temp(2) = '1')
				or	(A_temp(1) = '1' and B_temp(1) = '1' and A_temp(2) = '0' and B_temp(2) = '1')
				or	(A_temp(1) = '0' and B_temp(1) = '1' and A_temp(2) = '0' and B_temp(2) = '0') ) then tmp <= tmp - 1;

			elsif( 	(A_temp(1) = '1' and B_temp(1) = '0' and A_temp(2) = '0' and B_temp(2) = '0')
				or	(A_temp(1) = '1' and B_temp(1) = '1' and A_temp(2) = '1' and B_temp(2) = '0')
				or	(A_temp(1) = '0' and B_temp(1) = '1' and A_temp(2) = '1' and B_temp(2) = '1')
				or	(A_temp(1) = '0' and B_temp(1) = '0' and A_temp(2) = '0' and B_temp(2) = '1') ) then tmp <= tmp + 1;
	  
			end if;   
		end if;				
	end process;
	
	latch_counter : process ( Clock, Resetbar )
	begin
	
		if(Resetbar = '0') then
		
			Count_out <= ( others => '0' );
		
		elsif (Clock'event and Clock='1' ) then
			if 	( Count_latch = '0' ) then
				Count_out <= std_logic_vector(tmp);
			end if;   
		end if;				
	end process;

--	Count_out<=tmp;
	
end BEHAVIORAL;
