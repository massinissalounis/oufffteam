--------------------------------------------------------------------------------------------------------
-- Project :			gh Library
--
-- File:			gh_uart_16550_p.vhd
--
-- Author:			C. BEGUET
--
--
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author		Comments
--				0.1	24/09/2009		C. BEGUET		Creation
--
--
--------------------------------------------------------------------------------------------------------
-- Purpose: Package to define component for gh_UART_16550
--------------------------------------------------------------------------------------------------------

library ieee ;
use ieee.std_logic_1164.all ;

library work;
use work.pmp_p.all;

package gh_UART_16550_p is

	component gh_uart_16550 is
		port(
			clk     : in std_logic;
			BR_clk  : in std_logic;
			rst     : in std_logic;
			CS      : in std_logic;
			WR      : in std_logic;
			ADD     : in std_logic_vector(2 downto 0);
			D       : in std_logic_vector(7 downto 0);
			
			sRX	    : in std_logic;
			CTSn    : in std_logic := '1';
			DSRn    : in std_logic := '1';
			RIn     : in std_logic := '1';
			DCDn    : in std_logic := '1';
			
			sTX     : out std_logic;
			DTRn    : out std_logic;
			RTSn    : out std_logic;
			OUT1n   : out std_logic;
			OUT2n   : out std_logic;
			TXRDYn  : out std_logic;
			RXRDYn  : out std_logic;
			
			IRQ     : out std_logic;
			B_CLK   : out std_logic;
			RD      : out std_logic_vector(7 downto 0)
			);
	end component;

	component gh_uart_16550_pmp_wrapper is
		port(	  
			-------- pmp signals ------------
			PMP_in		: in PMP_SLV_IN_TYPE;
			PMP_out		: out PMP_SLV_OUT_TYPE;
			
			------ other I/O ----------------
			main_clk	: in std_logic;
			main_reset	: in std_logic;
			BR_clk  : in std_logic;
			sRX	    : in std_logic;
			CTSn    : in std_logic := '1';
			DSRn    : in std_logic := '1';
			RIn     : in std_logic := '1';
			DCDn    : in std_logic := '1';
			
			sTX     : out std_logic;
			TX_EN	: out std_logic;
			DTRn    : out std_logic;
			RTSn    : out std_logic;
			OUT1n   : out std_logic;
			OUT2n   : out std_logic;
			TXRDYn  : out std_logic;
			RXRDYn  : out std_logic;
			
			IRQ     : out std_logic;
			B_CLK   : out std_logic		
		);
	end component;

	component gh_uart_16550_AMBA_APB_wrapper is
		port(	  
		-------- AMBA_APB signals ------------
			PCLK      : in std_logic;
			PRESETn   : in std_logic;
			PSEL      : in std_logic;
			PENABLE   : in std_logic;
			PWRITE    : in std_logic;
			PADDR     : in std_logic_vector(2 downto 0);
			PWDATA    : in std_logic_vector(7 downto 0);
			
			PRDATA    : out std_logic_vector(7 downto 0);
			PREADY	  : out std_logic;			-- Ajout CBE pour gestion du PREADY
		----------------------------------------------------
		------ other I/O -----------------------------------	
			BR_clk  : in std_logic;
			sRX	    : in std_logic;
			CTSn    : in std_logic := '1';
			DSRn    : in std_logic := '1';
			RIn     : in std_logic := '1';
			DCDn    : in std_logic := '1';
			
			sTX     : out std_logic;
			DTRn    : out std_logic;
			RTSn    : out std_logic;
			OUT1n   : out std_logic;
			OUT2n   : out std_logic;
			TXRDYn  : out std_logic;
			RXRDYn  : out std_logic;
			
			IRQ     : out std_logic;
			B_CLK   : out std_logic		
			);
	end component;

	component gh_uart_16550_wb_wrapper is
		port(	  
		-------- wishbone signals ------------
			wb_clk_i  : in std_logic;
			wb_rst_i  : in std_logic;
			wb_stb_i  : in std_logic;
			wb_cyc_i  : in std_logic;
			wb_we_i   : in std_logic;
			wb_adr_i  : in std_logic_vector(2 downto 0);
			wb_dat_i  : in std_logic_vector(7 downto 0);
			
			wb_ack_o  : out std_logic;
			wb_dat_o  : out std_logic_vector(7 downto 0);
		----------------------------------------------------
		------ other I/O -----------------------------------	
			BR_clk  : in std_logic;
			sRX	    : in std_logic;
			CTSn    : in std_logic := '1';
			DSRn    : in std_logic := '1';
			RIn     : in std_logic := '1';
			DCDn    : in std_logic := '1';
			
			sTX     : out std_logic;
			DTRn    : out std_logic;
			RTSn    : out std_logic;
			OUT1n   : out std_logic;
			OUT2n   : out std_logic;
			TXRDYn  : out std_logic;
			RXRDYn  : out std_logic;
			
			IRQ     : out std_logic;
			B_CLK   : out std_logic		
			);
	end component;

	component gh_uart_Rx_8bit is 
		port(
			clk       : in std_logic; -- clock
			rst       : in std_logic;
			BRCx16    : in std_logic; -- 16x clock enable
			sRX       : in std_logic; 
			num_bits  : in integer;
			Parity_EN : in std_logic;
			Parity_EV : in std_logic;
			Parity_ER : out std_logic;
			Frame_ER  : out std_logic;
			Break_ITR : out std_logic;
			D_RDY     : out std_logic;
			D         : out std_logic_vector(7 downto 0)
			);
	end component;

	component gh_uart_Tx_8bit is 
		port(
			clk       : in std_logic; --  clock
			rst       : in std_logic;
			xBRC      : in std_logic; -- x clock enable
			D_RYn     : in std_logic; -- data ready 
			D         : in std_logic_vector(7 downto 0);
			num_bits  : in integer:= 8; -- number of bits in transfer
			Break_CB  : in std_logic;
			stopB     : in std_logic;
			Parity_EN : in std_logic;
			Parity_EV : in std_logic;
			sTX       : out std_logic;
			BUSYn     : out std_logic;
			read      : out std_logic -- data read
			);
	end component;

	component gh_fifo_async16_sr is
		GENERIC (data_width: INTEGER :=8 ); -- size of data bus
		port (					
			clk_WR : in STD_LOGIC; -- write clock
			clk_RD : in STD_LOGIC; -- read clock
			rst    : in STD_LOGIC; -- resets counters
			srst   : in STD_LOGIC:='0'; -- resets counters (sync with clk_WR)
			WR     : in STD_LOGIC; -- write control 
			RD     : in STD_LOGIC; -- read control
			D      : in STD_LOGIC_VECTOR (data_width-1 downto 0);
			Q      : out STD_LOGIC_VECTOR (data_width-1 downto 0);
			empty  : out STD_LOGIC; 
			full   : out STD_LOGIC);
	end component;

	component gh_fifo_async16_rcsr_wf is
		GENERIC (data_width: INTEGER :=8 ); -- size of data bus
		port (					
			clk_WR  : in STD_LOGIC; -- write clock
			clk_RD  : in STD_LOGIC; -- read clock
			rst     : in STD_LOGIC; -- resets counters
			rc_srst : in STD_LOGIC:='0'; -- resets counters (sync with clk_RD!!!)
			WR      : in STD_LOGIC; -- write control 
			RD      : in STD_LOGIC; -- read control
			D       : in STD_LOGIC_VECTOR (data_width-1 downto 0);
			Q       : out STD_LOGIC_VECTOR (data_width-1 downto 0);
			empty   : out STD_LOGIC; -- sync with clk_RD!!!
			q_full  : out STD_LOGIC; -- sync with clk_RD!!!
			h_full  : out STD_LOGIC; -- sync with clk_RD!!!
			a_full  : out STD_LOGIC; -- sync with clk_RD!!!
			full    : out STD_LOGIC);
	end component;

end package gh_UART_16550_p;
