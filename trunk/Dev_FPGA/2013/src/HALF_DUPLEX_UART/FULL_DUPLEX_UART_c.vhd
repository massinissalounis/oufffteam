-- RS232_Controller.vhd

Library IEEE; -- Librairies
    use IEEE.STD_LOGIC_1164.all;
    
library work;
use work.FPGA_OUFFF_p.all;

entity FULL_DUPLEX_UART is -- Vue externe
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
		Data_ToSend : in std_logic_vector (7 downto 0); -- Donnee a transmettre
		
		Busy: out std_logic
	);
end FULL_DUPLEX_UART;

architecture wrapper of FULL_DUPLEX_UART is

	component BAUD_RATE_GENERATOR is
		generic (
			division_factor:integer:=41
		);
		port (
			clock: in  std_logic;
			reset: in  std_logic;
			baud_rate: out std_logic
		);
	end component;
	
	component UART_TRANSMITTER is
		generic (
			N_interrupt: integer := 3 -- Duree du signal d'interruption (en cycles Max 15)
		);
		port (
			clock: in std_logic;
			reset: in std_logic;
			
			clock_UART: in std_logic; -- Baud Rate

			Tx: out  std_logic; -- Entree asynchrone de la liaison
			Data_ToSend: in std_logic_vector (7 downto 0); -- Donnee a transmettre
			Send: in std_logic; -- Demarrage d'une emission

			Int_DataSent: out std_logic; -- Signal d'IT lorsqu'une donnee a ete envoyee
			
			Busy: out std_logic
		);
	end component;
	
	component UART_RECEIVER is
		generic (
			N_interrupt: integer := 3 -- Duree du signal d'interruption (en cycles Max 15)
		);
		port (
			clock: in std_logic;
			reset: in std_logic;

			clock_UART: in std_logic; -- Baud Rate
			Rx: in  std_logic; -- Entree asynchrone de la liaison

			Data_Received : out std_logic_vector (7 downto 0); -- Donnee recue
			Int_DataReceived: out std_logic; -- Signal d'IT lorsqu'une donnee a ete recue
			
			Busy: out std_logic
		);
	end component;
	
	signal BAUD_RATE : std_logic;
	
	signal Busy_receiver : std_logic;
	signal Busy_transmitter : std_logic;
	
	begin
		--Intensiation des composants
		Baud_Rate_Gen: BAUD_RATE_GENERATOR 
			generic map (FPGA_FREQUENCY/Speed) -- Rapport de division
			port map (clock, reset, BAUD_RATE);

		Transmitter: UART_TRANSMITTER 
			generic map (N_Interrupt)
			port map (clock, reset, BAUD_RATE, Tx, Data_ToSend, Send, Int_DataSent, Busy_transmitter);
		
		Receiver: UART_RECEIVER 
			generic map (N_interrupt)
			port map (clock, reset, BAUD_RATE, Rx, Data_Received, Int_DataReceived, Busy_receiver);
			
		Busy <= Busy_receiver or Busy_transmitter;
--		Busy <= Busy_transmitter;
--		Int_DataReceived <= '0';
end wrapper;