--------------------------------------------------------------------------------------------------------
-- Project :			gh Library
--
-- File:			gh_memory_p.vhd
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
-- Purpose: Package to define memory components in gh library
--------------------------------------------------------------------------------------------------------

library ieee ;
use ieee.std_logic_1164.all ;

package gh_memory_p is

	component gh_sram_1wp_2rp_sc is
		generic (size_add: integer :=8 ;
		         size_data: integer :=8 );
		port (					
			a_clk  : in std_logic;
			b_clk  : in std_logic;
			we     : in std_logic;
			a_add  : in std_logic_vector(size_add-1 downto 0);
			b_add  : in std_logic_vector(size_add-1 downto 0);
			d      : in std_logic_vector (size_data-1 downto 0);
			a_q    : out std_logic_vector (size_data-1 downto 0);
			b_q    : out std_logic_vector (size_data-1 downto 0));
	end component;

	component gh_sram_1wp_2rp is
		generic (size_add: integer :=8 ;
		         size_data: integer :=8 );
		port (					
			a_clk  : in std_logic;
			b_clk  : in std_logic;
			we     : in std_logic;
			a_add  : in std_logic_vector(size_add-1 downto 0);
			b_add  : in std_logic_vector(size_add-1 downto 0);
			d      : in std_logic_vector (size_data-1 downto 0);
			a_q    : out std_logic_vector (size_data-1 downto 0);
			b_q    : out std_logic_vector (size_data-1 downto 0));
	end component;

	component gh_sram is
		generic (size_add: integer :=10 ;
		         size_data: integer :=32 );
		port (					
			clk  : in std_logic;
			we     : in std_logic;
			add  : in std_logic_vector(size_add-1 downto 0);
			d      : in std_logic_vector (size_data-1 downto 0);
			q    : out std_logic_vector (size_data-1 downto 0));
	end component;

	component gh_fifo_sync_sr is
		generic (add_width: integer :=3; -- min value is 1 (2 memory locations)
		         data_width: integer :=8 ); -- size of data bus
		port (					
			clk : in std_logic; -- clock
			rst    : in std_logic; -- resets counters
			srst   : in std_logic:='0'; -- resets counters
			wr     : in std_logic; -- write control 
			rd     : in std_logic; -- read control
			d      : in std_logic_vector (data_width-1 downto 0);
			q      : out std_logic_vector (data_width-1 downto 0);
			empty  : out std_logic; 
			full   : out std_logic);
	end component;

	component gh_fifo_sync_rrd_sr is
		generic (add_width: integer :=8; -- min value is 1 (2 memory locations)
		         data_width: integer :=8 ); -- size of data bus
		port (					
			clk : in std_logic; -- clock
			rst    : in std_logic; -- resets counters
			srst   : in std_logic:='0'; -- resets counters
			wr     : in std_logic; -- write control 
			rd     : in std_logic; -- read control
			d      : in std_logic_vector (data_width-1 downto 0);
			q      : out std_logic_vector (data_width-1 downto 0);
			empty  : out std_logic; 
			full   : out std_logic);
	end component;

	component gh_fifo_async_uswf is
		generic (add_width: integer :=4;
		         data_width: integer :=8 ); -- size of data bus
		port (					
			clk_wr : in std_logic; -- write clock
			clk_rd : in std_logic; -- read clock
			rst    : in std_logic; -- resets counters
			srst   : in std_logic:='0'; -- resets counters (sync with clk_wr)
			wr     : in std_logic; -- write control 
			rd     : in std_logic; -- read control
			d      : in std_logic_vector (data_width-1 downto 0);
			q      : out std_logic_vector (data_width-1 downto 0);
			empty  : out std_logic; 
			full   : out std_logic);
	end component;

	component gh_fifo_async_usrf is
		generic (add_width: integer :=4;
		         data_width: integer :=8 ); -- size of data bus
		port (					
			clk_wr  : in std_logic; -- write clock
			clk_rd  : in std_logic; -- read clock
			rst     : in std_logic; -- resets counters
			rc_srst : in std_logic:='0'; -- resets counters (sync with clk_rd!!!)
			wr      : in std_logic; -- write control 
			rd      : in std_logic; -- read control
			d       : in std_logic_vector (data_width-1 downto 0);
			q       : out std_logic_vector (data_width-1 downto 0);
			empty   : out std_logic; -- sync with clk_rd!!!
			q_full  : out std_logic; -- sync with clk_rd!!!
			h_full  : out std_logic; -- sync with clk_rd!!!
			a_full  : out std_logic; -- sync with clk_rd!!!
			full    : out std_logic);
	end component;

	component gh_fifo_async_sr_wf is
		generic (add_width: integer :=4; -- min value is 2 (4 memory locations)
		         data_width: integer :=8 ); -- size of data bus
		port (					
			clk_wr  : in std_logic; -- write clock
			clk_rd  : in std_logic; -- read clock
			rst     : in std_logic; -- resets counters
			srst    : in std_logic:='0'; -- resets counters (sync with clk_wr)
			wr      : in std_logic; -- write control 
			rd      : in std_logic; -- read control
			d       : in std_logic_vector (data_width-1 downto 0);
			q       : out std_logic_vector (data_width-1 downto 0);
			empty   : out std_logic; 
			qfull   : out std_logic;
			hfull   : out std_logic;
			qqqfull : out std_logic;
			full    : out std_logic);
	end component;

	component gh_fifo_async_sr is
		generic (add_width: integer :=4; -- min value is 2 (4 memory locations)
		         data_width: integer :=8 ); -- size of data bus
		port (					
			clk_wr : in std_logic; -- write clock
			clk_rd : in std_logic; -- read clock
			rst    : in std_logic; -- resets counters
			srst   : in std_logic:='0'; -- resets counters (sync with clk_wr)
			wr     : in std_logic; -- write control 
			rd     : in std_logic; -- read control
			d      : in std_logic_vector (data_width-1 downto 0);
			q      : out std_logic_vector (data_width-1 downto 0);
			empty  : out std_logic; 
			full   : out std_logic);
	end component;

	component gh_fifo_async_rrd_sr_wf is
		generic (add_width: integer :=8; -- min value is 2 (4 memory locations)
		         data_width: integer :=8 ); -- size of data bus
		port (					
			clk_wr  : in std_logic; -- write clock
			clk_rd  : in std_logic; -- read clock
			rst     : in std_logic; -- resets counters
			srst    : in std_logic:='0'; -- resets counters (sync with clk_wr)
			wr      : in std_logic; -- write control 
			rd      : in std_logic; -- read control
			d       : in std_logic_vector (data_width-1 downto 0);
			q       : out std_logic_vector (data_width-1 downto 0);
			empty   : out std_logic;
			qfull   : out std_logic;
			hfull   : out std_logic;
			qqqfull : out std_logic;
			full    : out std_logic);
	end component;

	component gh_fifo_async_rrd_sr is
		generic (add_width: integer :=8; -- min value is 2 (4 memory locations)
		         data_width: integer :=8 ); -- size of data bus
		port (					
			clk_wr : in std_logic; -- write clock
			clk_rd : in std_logic; -- read clock
			rst    : in std_logic; -- resets counters
			srst   : in std_logic:='0'; -- resets counters (sync with clk_wr)
			wr     : in std_logic; -- write control 
			rd     : in std_logic; -- read control
			d      : in std_logic_vector (data_width-1 downto 0);
			q      : out std_logic_vector (data_width-1 downto 0);
			empty  : out std_logic; 
			full   : out std_logic);
	end component;

	component gh_fasm_1wp_2rp_r is
		generic (size_add: integer :=8 ;
		         size_data: integer :=8 );
		port (					
			clk   : in std_logic;
			rst   : in std_logic;
			we    : in std_logic;
			a_add : in std_logic_vector(size_add-1 downto 0);
			b_add : in std_logic_vector(size_add-1 downto 0);
			d     : in std_logic_vector (size_data-1 downto 0);
			a_q   : out std_logic_vector (size_data-1 downto 0);
			b_q   : out std_logic_vector (size_data-1 downto 0));
	end component;

	component gh_fasm_1wp_2rp is
		generic (size_add: integer :=8 ;
		         size_data: integer :=8 );
		port (					
			clk   : in std_logic;
			we    : in std_logic;
			a_add : in std_logic_vector(size_add-1 downto 0);
			b_add : in std_logic_vector(size_add-1 downto 0);
			d     : in std_logic_vector (size_data-1 downto 0);
			a_q   : out std_logic_vector (size_data-1 downto 0);
			b_q   : out std_logic_vector (size_data-1 downto 0));
	end component;

	component gh_fasm is
		generic (size_add: integer :=10 ;
		         size_data: integer :=32 );
		port (					
			clk  : in std_logic;
			we   : in std_logic;
			add  : in std_logic_vector(size_add-1 downto 0);
			d    : in std_logic_vector (size_data-1 downto 0);
			q    : out std_logic_vector (size_data-1 downto 0));
	end component;

	component gh_4byte_dpram_x32 is
		generic (size_add: integer :=8); -- size of 2nd port read address bus
		port (					
			a_clk  : in std_logic;
			b_clk  : in std_logic;
			csn	   : in std_logic;
			we     : in std_logic;
			be     : in std_logic_vector(3 downto 0);
			a_add  : in std_logic_vector(size_add-1 downto 0);
			b_add  : in std_logic_vector(size_add-1 downto 0);
			d      : in std_logic_vector(31 downto 0);
			a_q    : out std_logic_vector(31 downto 0);
			b_q    : out std_logic_vector(31 downto 0));
	end component;

	component gh_4byte_dpram_x16_le is
		generic (size_add: integer :=8); -- size of 2nd port read address bus
		port (					
			a_clk  : in std_logic;
			b_clk  : in std_logic;
			csn	   : in std_logic;
			we     : in std_logic;
			be     : in std_logic_vector(3 downto 0);
			a_add  : in std_logic_vector(size_add-2 downto 0);
			b_add  : in std_logic_vector(size_add-1 downto 0);
			d      : in std_logic_vector(31 downto 0);
			a_q    : out std_logic_vector(31 downto 0);
			b_q    : out std_logic_vector(15 downto 0));
	end component;

	component gh_4byte_dpram_x16_be is
		generic (size_add: integer :=8); -- size of 2nd port read address bus
		port (					
			a_clk  : in std_logic;
			b_clk  : in std_logic;
			csn	   : in std_logic;
			we     : in std_logic;
			be     : in std_logic_vector(3 downto 0);
			a_add  : in std_logic_vector(size_add-2 downto 0);
			b_add  : in std_logic_vector(size_add-1 downto 0);
			d      : in std_logic_vector(31 downto 0);
			a_q    : out std_logic_vector(31 downto 0);
			b_q    : out std_logic_vector(15 downto 0));
	end component;

	component gh_4byte_dpram_x8_le is
		generic (size_add: integer :=8); -- size of 2nd port read address bus
		port (					
			a_clk  : in std_logic;
			b_clk  : in std_logic;
			csn	   : in std_logic;
			we     : in std_logic;
			be     : in std_logic_vector(3 downto 0); -- 
			a_add  : in std_logic_vector(size_add-3 downto 0);
			b_add  : in std_logic_vector(size_add-1 downto 0);
			d      : in std_logic_vector(31 downto 0);
			a_q    : out std_logic_vector(31 downto 0);
			b_q    : out std_logic_vector(7 downto 0));
	end component;

	component gh_4byte_dpram_x8_be is
		generic (size_add: integer :=8); -- size of 2nd port read address bus
		port (					
			a_clk  : in std_logic;
			b_clk  : in std_logic;
			csn	   : in std_logic;
			we     : in std_logic;
			be     : in std_logic_vector(3 downto 0); -- 
			a_add  : in std_logic_vector(size_add-3 downto 0);
			b_add  : in std_logic_vector(size_add-1 downto 0);
			d      : in std_logic_vector(31 downto 0);
			a_q    : out std_logic_vector(31 downto 0);
			b_q    : out std_logic_vector(7 downto 0));
	end component;

end package gh_memory_p;