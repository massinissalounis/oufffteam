-- Oufffteam
-- Projet carte mere
-- Device: Half Duplex UART

-- 30/01/2013			PEG			Creation

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity HALF_DUPLEX_UART is
  port (
		-- in
		clock		: in std_logic;
		reset		: in std_logic;
		-- in - Internal BUS			
		BUS_D		: inout std_logic_vector (7 downto 0);
		BUS_A		: in std_logic_vector (1 downto 0);
		BUS_RD		: in std_logic;
		BUS_WR		: in std_logic;
		BUS_CS		: in std_logic;
		-- output_signal
		RxTx		: inout std_logic;
		tmp_LED1 : out std_logic
		);
end entity HALF_DUPLEX_UART;

architecture wrapper of HALF_DUPLEX_UART is
  
	component FULL_DUPLEX_UART is -- Vue externe
		generic (
			N_interrupt: integer := 3; -- Duree du signal d'interruption (cycles)
			Speed: integer := 19200
		); -- Vitesse de fonctionnement de l'horloge en bauds
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

	signal status_reg	: std_logic_vector (7 downto 0); 	-- R	Address 00
	signal input_reg		: std_logic_vector (7 downto 0); -- W	Address 01
	signal output_reg	: std_logic_vector (7 downto 0); -- R	Address 10
	signal dummy_reg		: std_logic_vector (7 downto 0);	-- R/W 	Address others
	
	signal Rx : std_logic;
	signal Tx : std_logic;

	signal Int_DataReceived: std_logic;
	signal Int_DataSent: std_logic;

	signal BUS_WR_old, BUS_WR_old_2: std_logic;
	signal BUS_RD_old, BUS_RD_old_2: std_logic;
		
	signal WR_falling_edge: std_logic;
	signal RD_falling_edge: std_logic;
		
	signal received_flag: std_logic;
	signal send_flag: std_logic;
	
	signal busy: std_logic;
	
	signal tmp_LED: std_logic;

	begin
	
	tmp_LED1 <= tmp_LED;
	tmp_LED <= '1' when output_reg = X"AA" else
				'0';
--				when output_reg = X"55" else
--				tmp_LED;
	
	registers_interface: process (reset, clock)
		begin
			if (reset = '1') then
				BUS_D <= (others => 'Z');
				status_reg(7 downto 2) <= "000000";
				output_reg <= (others => '0');
				dummy_reg <= (others => '0');
			elsif (clock'event and clock ='1') then
				if (BUS_CS = '1' and  BUS_WR ='1' and busy='0') then
					case BUS_A is
						when "10"	=> output_reg <= BUS_D;
						when others	=> dummy_reg <= BUS_D;
					end case;
				elsif (BUS_CS = '1' and BUS_RD = '1') then
					case BUS_A is
						when "00"	=> BUS_D <= status_reg;
						when "01"	=> BUS_D <= input_reg;
						when others	=> BUS_D <= dummy_reg;
					end case;
				else
					BUS_D <= (others  => 'Z');
				end if;
			end if;
	end process registers_interface;

	falling_edges: process(clock, reset)
		begin
			if(reset='1') then
				BUS_WR_old <= BUS_WR;
				BUS_WR_old_2 <= BUS_WR_old;
				BUS_RD_old <= BUS_RD;
				BUS_RD_old_2 <= BUS_RD_old;
			elsif (clock'event and clock='1') then
				BUS_WR_old <= BUS_WR;
				BUS_WR_old_2 <= BUS_WR_old;
				BUS_RD_old <= BUS_RD;
				BUS_RD_old_2 <= BUS_RD_old;
			end if;
	end process;

	WR_falling_edge <= (BUS_WR xor BUS_WR_old_2) and (BUS_WR_old_2);
	RD_falling_edge <= (BUS_RD xor BUS_RD_old_2) and (BUS_RD_old_2);
	
	trig_send: process (reset, clock)
		begin
			if (reset = '1') then
				send_flag <= '0';
			elsif (clock'event and clock ='1') then
				if (BUS_CS = '1' and  WR_falling_edge ='1' and busy='0') then
					case BUS_A is
						when "10"	=> send_flag <= '1';
						when others	=> null;
					end case;
				elsif (Int_DataSent = '1') then
					send_flag <= '0';
				end if;
			end if;
	end process;
	
	trig_received: process (reset, clock)
		begin
			if (reset = '1') then
				received_flag <= '0';
			elsif (clock'event and clock ='1') then
				if(Int_DataReceived = '1') then
					received_flag <= '1';
				elsif (BUS_CS = '1' and  RD_falling_edge ='1') then
					case BUS_A is
						when "01"	=> received_flag <= '0';
						when others	=> null;
					end case;
				end if;
			end if;
	end process;
	
	-- Status reg filling
	status_reg(0) <= busy;
	status_reg(1) <= received_flag;
					
	UART: FULL_DUPLEX_UART 
		generic map (2,115200)
		port map (clock, reset, Rx, Tx, Int_DataReceived, Int_DataSent, send_flag, input_reg, output_reg, Busy);--output_reg


	RxTx <= Tx when send_flag='1' else 'Z';
	Rx <= RxTx when send_flag='0' else '1';
    
end architecture wrapper;