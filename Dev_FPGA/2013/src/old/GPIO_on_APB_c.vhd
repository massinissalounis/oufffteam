--------------------------------------------------------------------------------------------------------
-- Project :		GENERIQUE
--
-- File:			GPIO_on_APB_c.vhd
--
-- Author:			C. BEGUET
--
-- Dependencies:	
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author			Comments
--						0.1		18/10/2011			C. BEGUET		Creation
--				
--
--------------------------------------------------------------------------------------------------------
-- Purpose: GPIO port on APB bus
--		*generics: 		nb_GPIO:		number of total of pin in input ou output
--		*inputs:		MODE:			vector to define i/o mode for each pin. 0 = input, on read: pin state, out_en = 0
--																				1 = output, on read: output register, out_en = 1
--						pclk:			APB clock
--						presetn			reset, active low
--						APBSlaveIn		APB input bus
--						gpio_in			logical inputs
--		*outputs:		APBSlaveOut		APB output bus
--						gpio_out		logical outputs
--						gpio_out_en		output enable for buffers
--------------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;


library work;
use work.apb.all;
use work.byte_bit_count_p.all;

entity GPIO_on_APB_c is
	generic (	nb_GPIO : natural := 1	);
	port (
		MODE 		: in std_logic_vector (nb_GPIO-1 downto 0);
		pclk        : in  std_logic;
		presetn     : in  std_logic;
		APBSlaveIn  : in  APB_SLV_IN_TYPE;
		APBSlaveOut : out APB_SLV_OUT_TYPE;
		gpio_out	: out std_logic_vector (nb_GPIO - 1 downto 0);
		gpio_out_en	: out std_logic_vector (nb_GPIO - 1 downto 0);
		gpio_in		: in  std_logic_vector (nb_GPIO - 1 downto 0)
	);
end entity GPIO_on_APB_c;

architecture parallel_IO of GPIO_on_APB_c is
	
	constant nb_regsiters 	: integer := nb_regsiters_for_n_bits (nb_GPIO, PDMAX);
	
	signal output_register	: std_logic_vector ((nb_regsiters*PDMAX)-1 downto 0);
	signal input_register	: std_logic_vector ((nb_regsiters*PDMAX)-1 downto 0);
	signal mode_register	: std_logic_vector ((nb_regsiters*PDMAX)-1 downto 0);
	
	signal address_int		: natural;
	
	-- slave select
	alias psel    : STD_ULOGIC is APBSlaveIn.psel;
	-- strobe         
	alias penable : STD_ULOGIC is APBSlaveIn.penable; 
	-- write      
	alias pwrite  : STD_ULOGIC is APBSlaveIn.pwrite;
	-- address bus (byte)        
	alias paddr   : STD_LOGIC_VECTOR(PAMAX-1 downto 0)  is APBSlaveIn.paddr; 
	-- write data bus
	alias pwdata  : STD_LOGIC_VECTOR(PDMAX-1 downto 0) is APBSlaveIn.pwdata;
	-- read data bus
	alias prdata  : STD_LOGIC_VECTOR(PDMAX-1 downto 0) is APBSlaveOut.prdata;

	
	begin
	
		-- Décodage des adresses (adaptation automatique en fonction du nombre de registres)
		address_int <= CONV_INTEGER ( paddr(number_of_bit_from_max_count(nb_regsiters)-1 downto 0));
		
		-------------------------------------------------------------
		--            Ecriture dans les registres                  --
		-------------------------------------------------------------
		generate_write_registers: for I in 0 to nb_regsiters-1 generate
			process (presetn, pclk)
			begin
				if (presetn = '0') then
					output_register(((I+1)*PDMAX)-1 downto (I*PDMAX)) <= (others => '0');	-- mise a zero du registre au reset
				elsif (pclk'event and pclk='1') then
					if ( psel='1' and penable='1' and pwrite='1' and address_int=I) then
						output_register(((I+1)*PDMAX)-1 downto (I*PDMAX)) <= pwdata and mode_register(((I+1)*PDMAX)-1 downto (I*PDMAX));	
						-- ecriture du registre des sorties avec masquage des bits en lecture seule
					end if;
				end if;
			end process;
		end generate generate_write_registers;
		
		-- Registre de mode pour masquage des registres d'entrée et de sortie
		mode_register(nb_GPIO-1 downto 0) <= MODE;
		
		-- S'il y a plus de bits dans le regsitre que de sorties, on complète par des '0'
		output_reg_completion: if ((nb_regsiters*PDMAX) > nb_GPIO) generate
			output_register ((nb_regsiters*PDMAX)-1 downto nb_GPIO) <= (others => '0');
			mode_register	((nb_regsiters*PDMAX)-1 downto nb_GPIO) <= (others => '0');
		end generate output_reg_completion;
		
		gpio_out			<= output_register (nb_GPIO - 1 downto 0);
		gpio_out_en			<= MODE;	-- sortie activée si mode=1
		APBSlaveOut.pready	<= '1';		-- toujours ok
		APBSlaveOut.pslverr	<= '0';		-- toujours ok
		
		-------------------------------------------------------------
		--                   Lecture des registres                 --
		-------------------------------------------------------------
		-- Choix de la donnée lu : On lit l'entrée (mode='0') ou le registre de sortie (mode='1')
		input_register (nb_GPIO - 1 downto 0) 	<= (gpio_in and not MODE) or (output_register (nb_GPIO - 1 downto 0) and MODE);
		-- S'il y a plus de bits dans le regsitre que d'entrées, on complète par des '0'
		input_reg_completion: if ((nb_regsiters*PDMAX) > nb_GPIO) generate
			input_register ((nb_regsiters*PDMAX)-1 downto nb_GPIO) <= (others => '0');
		end generate input_reg_completion;
		
		generate_read_registers: for I in 0 to nb_regsiters-1 generate
				prdata <= input_register(((I+1)*PDMAX)-1 downto (I*PDMAX))	when address_int=I else (others => 'Z');
		end generate generate_read_registers;

end architecture parallel_IO;