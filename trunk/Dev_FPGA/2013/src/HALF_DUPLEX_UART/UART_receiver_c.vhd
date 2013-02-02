-- Oufffteam
-- Projet carte mere
-- Device: UART_Receiver

-- 2007				PEG			Creation
-- 30/01/2013			PEG			Refonte

-- Recepteur serie : on gere une reception asynchrone avec 1 bit de start, 8 bits de donnees et 1 bit de stop

-- Notre controleur serie sera synchrone a l'horloge du FPGA mais fonctionnera a la frequence clk_UART generee separement

-- La donnee presente en sortie sera la donnee precedente tant que la nouvelle donnee n'est pas completement arrivee
-- Le recepteur serie indiquera l'arrivee d'une nouvelle donnee en levant son signal int_RS232 pendant N_interrupt coup de clock

Library IEEE; -- Librairies
    use IEEE.STD_LOGIC_1164.all;
	use IEEE.STD_LOGIC_arith.all;

entity UART_RECEIVER is
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
end UART_RECEIVER;

architecture synchronous of UART_RECEIVER is -- Vue interne
	-- Declaration de etats  
	type state_machine is (sleep, start, syn_clk, data, stop, interrupt);
	-- Declaration de signaux   
	signal current_state, next_state : state_machine;
	signal buffer_received : std_logic_vector (7 downto 0);
	signal clock_UART_old : std_logic;
	signal BR_edge: std_logic;
	
	signal counter_data : natural range 9 downto 0;
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

	BR_edge <= (clock_UART xor clock_UART_old) and (clock_UART_old);

	next_state_prep: process(BR_edge, Rx, counter_int)

		begin
			case current_state is
				when sleep =>		if(Rx='0') then  -- Detection d'un bit de start
								next_state<=syn_clk;
							end if;
							
				when syn_clk => if(BR_edge = '1') then -- Syncho clock
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
											
				when interrupt =>	if(Counter_int=N_interrupt-1) then 
								next_state<=sleep;
							end if;

				when others =>		next_state<=sleep; --En cas d'etat inconnu, on passe dans l'etat de repos 
			end case;
	end process;

	storage_counter: process (BR_edge, reset)
		begin
			if(reset='1' or current_state=sleep) then
				counter_data <= 0;
			elsif(current_state=data and BR_edge='1') then
				counter_data <= counter_data + 1;
			end if;
	end process;

	data_latch: process(reset, counter_data, current_state)
		begin
		  if(reset='1') then
		    buffer_received <= (others => '0');
			elsif(current_state=data and counter_data<=7) then
				buffer_received(counter_data)<=Rx;
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

	output_update: process(reset, current_state)
		begin
			if(reset='1') then
				Data_Received <= (others => '0');
				Int_DataReceived <= '0';
			elsif (current_state=stop) then
				Data_Received <= buffer_received;
			elsif (current_state=interrupt) then
				Int_DataReceived <= '1';
			else
				Int_DataReceived <= '0';
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