-- Oufffteam
-- Projet carte mere
-- Device: FIFO

-- 30/01/2013			PEG			Creation


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity FIFO is
	generic (
		depth: integer := 2 -- FIFO depth
	);
	port (
		clock: in std_logic;
		reset: in std_logic;
	
		enr : in std_logic;   --enable read,should be '0' when not in use.
		enw : in std_logic;    --enable write,should be '0' when not in use.

		in_port: in std_logic_vector (7 downto 0);
		out_port: out std_logic_vector (7 downto 0);

		empty : out std_logic;     --set as '1' when the queue is empty
		full : out std_logic     --set as '1' when the queue is full
	);
end FIFO;


architecture behavioral of FIFO is

	type memory_type is array ((depth-1) downto 0) of std_logic_vector(7 downto 0);
	signal memory : memory_type :=(others => (others => '0'));   --memory for queue.

	signal readptr : natural range depth-1 downto 0;
	signal writeptr : natural range depth-1 downto 0;

begin
	
	process(clock, reset)
	begin
		if(reset='1') then
			memory <= (others => (others => '0'));
			readptr <= 0;
			writeptr <= 0;
		elsif(clock'event and clock='1') then
			if(enr ='1') then
				out_port <= memory(readptr);
				readptr <= readptr + 1;      --points to next address.
			elsif(enw ='1') then
				memory(writeptr) <= in_port;
				writeptr <= writeptr + 1;  --points to next address.
			end if;
		end if;

		if(readptr = (depth-1)) then      --resetting read pointer.
			readptr <= 0;
		end if;

		if(writeptr = (depth-1)) then        --checking whether queue is full or not
			full <='1';
			writeptr <= 0;
		else
			full <='0';
		end if;

		if(writeptr = 0) then   --checking whether queue is empty or not
			empty <='1';
		else
			empty <='0';
		end if;
	end process;

end behavioral;