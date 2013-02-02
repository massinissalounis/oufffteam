-- Oufffteam
-- Projet carte mere
-- Device: Baud Rate Generator : permet de creer une horloge de transfer a 1 MHz a partir d'un horloge de 40.69 MHz

-- 2007				PEG			Creation
-- 30/01/2013			PEG			Refonte


Library IEEE; -- Librairies
    use IEEE.STD_LOGIC_1164.all;

entity BAUD_RATE_GENERATOR is -- Vue externe
	generic (
		division_factor:integer:=41
	); -- Updated according to the AX12 freq
	port (
		clock: in  std_logic;
		reset: in  std_logic;
		baud_rate: out std_logic
	);
end BAUD_RATE_GENERATOR;

architecture synchronous of BAUD_RATE_GENERATOR is -- Vue interne
   signal internal_clk : std_logic;
   
   signal count : integer range 1 to division_factor+1;
   
   begin
    
      transition : process(clock,reset)

      begin
         if(reset='1') then
            internal_clk<='0';
            count<=1;
         elsif (clock'event) then
            if(division_factor=1) then -- Rising and Falling edges
               internal_clk <= not internal_clk; 
            elsif(clock='1') then -- Rising edge
              if(count=division_factor/2) then
                count<=1;
              else
                count<=count+1;
              end if;  
                        
              if(count=division_factor/2) then
               internal_clk <= not internal_clk;
              end if;  
            end if;
            
 
          end if;
      end process;   
      
      baud_rate<= internal_clk;      
end synchronous;


