-- Simulation de décodeur de quadrature

Library IEEE; -- Librairies
    use IEEE.STD_LOGIC_1164.all;
    use ieee.numeric_std.all;
    
entity TB_QUADRATURE_COUNTER is
end TB_QUADRATURE_COUNTER;

architecture simulation of TB_QUADRATURE_COUNTER is
    
	component QUADRATURE_COUNTER is -- Vue externe
	GENERIC ( 	Nb_bits : natural := 16 ;              -- nombre de bits de sortie
				Nb_bascules : natural := 2            -- bascules d'antiparasites supplementaires si =2, sinon 1
			);
	PORT 	( 	Clock: in  std_logic; -- Horloge de référence
				Resetbar: in  std_logic; -- Reset actif bas du module

				A : in std_logic; -- Canal A du codeur
				B : in std_logic; -- Canal B du codeur

				Count_out : OUT  unsigned(Nb_bits-1 DOWNTO 0);
				Count_latch : in std_logic
			);
	end component;
	
	signal Clock : std_logic;
	signal resetbar : std_logic;
	signal A,B : std_logic;
	signal count_latch : std_logic;
    
    begin
		
        process
        begin
            clock<='1';
            wait for 10 ns;
            
            clock<='0';
            wait for 10 ns;
        end process;
        
        process
        begin
           Resetbar<='0';
		   Count_latch <= '0';
           wait for 10 ns;
           Resetbar<='1';
		   wait for 20 us;
		   Count_latch <= '1';
           wait for 30 ns;
		   Count_latch <= '0';
           wait for 10000 us;
       end process;
	   
	    -- process -- Test en marche arriere
        -- begin
            -- A<='0';
			-- B<='1';
            -- wait for 250 ns;
			-- A<='1';
			-- B<='1';
            -- wait for 250 ns;
			-- A<='1';
			-- B<='0';
			-- wait for 250 ns;
			-- A<='0';
			-- B<='0';
            -- wait for 250 ns;
        -- end process;
			    
		process -- Test en marche avant
        begin
            B<='0';
			A<='1';
            wait for 250 ns;
			B<='1';
			A<='1';
            wait for 250 ns;
			B<='1';
			A<='0';
			wait for 250 ns;
			B<='0';
			A<='0';
            wait for 250 ns;
        end process;
        
        UUT : QUADRATURE_COUNTER 	port map (Clock => clock, resetbar => resetbar, A => A, B => B, Count_latch => Count_latch);
        
end architecture;
                
