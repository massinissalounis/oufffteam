-- Simulation de l'horloge de la clock

Library IEEE; -- Librairies
    use IEEE.STD_LOGIC_1164.all;
    
entity TB_BAUD_RATE_GENERATOR is
end TB_BAUD_RATE_GENERATOR;

architecture simulation of TB_BAUD_RATE_GENERATOR is

	constant period_FPGA		: time := 24.6 ns;  	-- 40.69 MHz

	component BAUD_RATE_GENERATOR is -- Vue externe
	generic (
		division_factor:integer:=41
	); -- Updated according to the AX12 freq
	port (
		clock: in  std_logic;
		reset: in  std_logic;
		baud_rate: out std_logic
	);
	end component;
	
	signal FPGA_CLK : std_logic;
	signal RESET : std_logic;
    
	begin
		
		FPGAclk: process
		begin
			loop
				FPGA_CLK <= '0';
				wait for period_FPGA/2;
				FPGA_CLK <= '1';
				wait for period_FPGA/2;
			end loop;
		end process;
		
		
		main_tb: process
		begin
			---- Test RESET ----
			assert false report (" HARD RESET") severity note;
			-- HARD RESET
			wait for 50 ns;
			RESET <= '1';
			wait for 50 ns;
			RESET <= '0';
			
			---- Test RESET ----
			assert false report ("Baud rate generator") severity note;
			
			---- Fin du Test----
			assert false report ("Fin Test") severity note;
			wait;
		end process;
        
        
        UUT : BAUD_RATE_GENERATOR 
		generic map (40690000/115200)
		port map (FPGA_CLK, RESET);
        
end architecture;
                
