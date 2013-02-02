-- Oufffteam
-- Projet carte mere
-- Device: UART_Transmitter

-- 2007				PEG			Creation
-- 30/01/2013			PEG			Refonte

Library IEEE; -- Librairies
    use IEEE.STD_LOGIC_1164.all;
	use IEEE.STD_LOGIC_arith.all;

entity UART_TRANSMITTER is -- Vue externe
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
		
		Busy : out std_logic
	);
end UART_TRANSMITTER;

architecture synchronous of UART_TRANSMITTER is -- Vue interne
	-- Declaration de etats  
	type state_machine is (sleep, sync_clk, start, data, stop, interrupt);
	-- Declaration de signaux   
	signal current_state, next_state : state_machine;
	signal buffer_received : std_logic_vector (7 downto 0);
	signal clock_UART_old : std_logic;
	signal BR_edge: std_logic;

	signal Bit_To_Send : std_logic := '0';
	
	signal counter_data : natural range 8 downto 0;
	signal counter_int : natural range N_interrupt downto 0;

	begin
	
	state_update: process(clock, reset)
		begin
			if(reset='1') then
				current_state <= sleep;
			elsif (clock'event and clock='1') then
				current_state <= next_state; 
			end if;
	end process;

	BR_edge_detection: process(clock, reset)
		begin
			if(reset='1') then
				clock_UART_old <= clock_UART;
			elsif (clock'event and clock='1') then
				clock_UART_old <= clock_UART; 
			end if;
	end process;

	BR_edge <= (clock_UART xor clock_UART_old) and (clock_UART);

	next_state_prep: process(BR_edge, Send, counter_int)

		begin
			case current_state is
				when sleep =>		if(Send='1') then -- Start new transmission
								next_state<=sync_clk;
							end if;

				when sync_clk =>		if(BR_edge = '1') then  -- BR clock synchronization
								next_state<=start;
							end if;
					
				when start =>		if(BR_edge = '1') then
								next_state<=data;
							end if;
			
				when data =>		if(BR_edge = '1' and counter_data=7) then -- On a eu un front sur la clock de transfert
								next_state<=stop;
							end if;	
										
				when stop =>		if(BR_edge = '1') then -- On a eu un front sur la clock de transfert
								next_state<=interrupt;
							end if;
											
				when interrupt =>	if(counter_int=N_interrupt-1) then 
								next_state<=sleep;
							end if;

				when others =>		next_state<=sleep; --En cas d'etat inconnu, on passe dans l'etat de repos 
			end case;
	end process;

	data_counter: process (BR_edge, reset)
		begin
			if(reset='1' or current_state=sleep) then
				counter_data <= 0;
			elsif(current_state=data and BR_edge='1') then
				counter_data <= counter_data + 1;
			end if;
	end process;

	data_transmit: process(BR_edge)
		begin
			if (current_state=start) then
				Tx <= '0';
			elsif (current_state=data) then
				Tx<= Data_ToSend(counter_data);
			else
				Tx<='1';
			end if;
	end process;

	int_counter: process (clock, reset)
		begin
			if(reset='1' or current_state=sleep) then
				counter_int <= 0;
			elsif(clock'event and clock ='1' and current_state=interrupt) then
				counter_int <= counter_int + 1;
			end if;
	end process;

	int_signal: process(reset, current_state)
		begin
			if(reset='1') then
				Int_DataSent <= '0';
			elsif (current_state=interrupt) then
				Int_DataSent <= '1';
			else
				Int_DataSent <= '0';
			end if;
	end process;
	
	busy_update: process(current_state)
		begin
			if(current_state=sleep) then
		    Busy<='0';
		  else
		    Busy<='1';
		  end if;
	end process;
	
end synchronous;