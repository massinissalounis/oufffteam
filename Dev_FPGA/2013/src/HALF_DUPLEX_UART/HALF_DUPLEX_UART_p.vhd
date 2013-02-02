-- Oufffteam
-- Projet carte mere
-- Device: Half Duplex UART

-- 30/01/2013			PEG			Creation

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package HALF_DUPLEX_UART_P is

	component HALF_DUPLEX_UART is
		port (
			-- in
			clock			: in std_logic;
			reset			: in std_logic;
			-- in - Internal BUS			
			BUS_D		: inout std_logic_vector (7 downto 0);
			BUS_A		: in std_logic_vector (1 downto 0);
			BUS_RD		: in std_logic;
			BUS_WR		: in std_logic;
			BUS_CS		: in std_logic;
			-- coder
			RxTx	: inout std_logic
		);
	end component HALF_DUPLEX_UART;
 
end HALF_DUPLEX_UART_P;


