-- Simulation de la reception serie

Library IEEE; -- Librairies
    use IEEE.STD_LOGIC_1164.all;
    
entity TB_FULL_DUPLEX_UART is
end TB_FULL_DUPLEX_UART;

architecture simulation of TB_FULL_DUPLEX_UART is

	constant period_FPGA		: time := 24.6 ns;  	-- 40.69 MHz
	constant period_BR		: time := 1 us;  	-- 1 MHz

	component FULL_DUPLEX_UART is -- Vue externe
		generic (
			N_interrupt: integer := 3; -- Duree du signal d'interruption (cycles)
			Speed: integer := 115200 -- Vitesse de fonctionnement de l'horloge en bauds
		);
		port (
			clock:in std_logic;
			reset:in std_logic;

			Rx: in  std_logic; -- Entree asynchrone de la liasion
			Tx: out std_logic; -- Sortie asynchrone de la liaison
		
			Int_DataReceived: out std_logic; -- Signal d'IT lors de la reception d'une donnee
			Int_DataSent: out std_logic; -- Signal d'IT lorsque la donnee a ete transmise
				
			Send: in std_logic; -- Demarrage d'une emission
				
			Data_Received : out std_logic_vector (7 downto 0); -- Donnee recue
			Data_ToSend : in std_logic_vector (7 downto 0);
			
			Busy : out std_logic
	  ); -- Donnee a transmettre
	end component;

	signal FPGA_CLK, RESET: std_logic;
	signal Rx, Tx: std_logic;
	signal Int_DataReceived, Int_DataSent, Send: std_logic;
	signal Data_Received, Data_ToSend : std_logic_vector ( 7 downto 0 );
    
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
			Rx<='Z';

			---- Test RESET ----
			assert false report (" HARD RESET") severity note;
			-- HARD RESET
			wait for 50 ns;
			RESET <= '1';
			wait for 50 ns;
			RESET <= '0';
			
			---- Test RESET ----
			assert false report ("Send") severity note;
			Data_ToSend<="01010101";
			Send<='1';
			wait for 20 ns;
			Send <= '0';		   
			wait for 11*period_BR;
		
			---- Test RESET ----
			assert false report ("Read") severity note;
			Rx<='0';			wait for period_BR; -- Start
			Rx<='1';			wait for period_BR;
			Rx<='1';			wait for period_BR;
			Rx<='0';			wait for period_BR;
			Rx<='0';			wait for period_BR;
			Rx<='1';			wait for period_BR;
			Rx<='1';			wait for period_BR;
			Rx<='0';			wait for period_BR;
			Rx<='0';			wait for period_BR;
			Rx<='1';			wait for period_BR; -- Stop
      Rx<='Z';

			---- Fin du Test----
			assert false report ("Fin Test") severity note;
			wait;
			
		end process;
		
        UUT : FULL_DUPLEX_UART
		generic map(4,1000000)
		port map ( FPGA_CLK, RESET, Rx, Tx, Int_DataReceived, Int_DataSent, Send, Data_Received, Data_ToSend);

end architecture;