--------------------------------------------------------------------------------------------------------
-- Project :			gh Library
--
-- File:			gh_custom_MSI_p.vhd
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
-- Purpose: Package to define custom MSI components in gh library
--------------------------------------------------------------------------------------------------------

library ieee ;
use ieee.std_logic_1164.all ;

package gh_custom_MSI_p is
	
	component gh_4byte_control_reg_32 is 
		port(
			clk  :  in std_logic; -- sample clock
			rst  :  in std_logic;
			wr   :  in std_logic; -- write signal
			be   :  in std_logic_vector(3 downto 0); -- byte enable
			mode :  in std_logic_vector(1 downto 0);
			d    :  in std_logic_vector(31 downto 0);-- data bus in
			q    :  out std_logic_vector(31 downto 0)
			);
	end component;

	component gh_4byte_control_reg_64 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			mode : in std_logic_vector(1 downto 0);
			a    : in std_logic; -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(63 downto 0)
			);
	end component;

	component gh_4byte_control_reg_128 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			mode : in std_logic_vector(1 downto 0);
			a    : in std_logic_vector(1 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(127 downto 0)
			);
	end component;

	component gh_4byte_control_reg_256 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			mode : in std_logic_vector(1 downto 0);
			a    : in std_logic_vector(2 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(255 downto 0)
			);
	end component;

	component gh_4byte_gpio_32 is 
		port(
			clk   : in std_logic; -- sample clock
			rst   : in std_logic;
			csn   : in std_logic; -- chip select
			wr    : in std_logic; -- write signal
			be    : in std_logic_vector(3 downto 0); -- byte enable
			drive : in std_logic_vector(3 downto 0);
			mode  : in std_logic_vector(1 downto 0);
			d     : in std_logic_vector(31 downto 0); -- data bus in
			rd    : out std_logic_vector(31 downto 0); -- read back bus
			io    : inout std_logic_vector(31 downto 0)
			);
	end component;

	component gh_baud_rate_gen is
		port(
			clk     : in std_logic;	
			br_clk  : in std_logic;
			rst     : in std_logic;
			wr      : in std_logic;
			be      : in std_logic_vector (1 downto 0); -- byte enable
			d       : in std_logic_vector (15 downto 0);
			rd      : out std_logic_vector (15 downto 0);
			rce     : out std_logic;
			rclk    : out std_logic
			);
	end component;

	component gh_binary2gray is
		generic (size: integer := 8);
		port(	
			b   : in std_logic_vector(size-1 downto 0);	-- binary value in
			g   : out std_logic_vector(size-1 downto 0) -- gray code out
			);
	end component;

	component gh_burst_generator is
		generic(size_period: integer := 16;
				size_pcount: integer := 8); 
		port(
			clk         : in std_logic; 
			rst         : in std_logic;
			period      : in std_logic_vector (size_period-1 downto 0);
			pulse_width : in std_logic_vector (size_period-1 downto 0);
			p_count     : in std_logic_vector (size_pcount-1 downto 0);
			trigger     : in std_logic;
			pulse       : out std_logic;
			busy        : out std_logic 
			);
	end component;

	component gh_clk_ce_div is 
		generic (divide_ratio : integer :=8);
		 port(
			 clk : in std_logic;
			 rst : in std_logic;
			 q : out std_logic
			 );
	end component gh_clk_ce_div;

	component gh_clk_mirror is 
		port(
			clk_2x    : in std_logic;
			clk_1x    : in std_logic;
			rst       : in std_logic;
			mirror    : out std_logic		
			);
	end component;

	component gh_data_demux is 
		generic (size: integer := 16);
		port(
			clk_2x    : in std_logic;
			clk_1x    : in std_logic;
			rst       : in std_logic;
			mux_cnt   : in std_logic;
			d         : in  std_logic_vector(size-1 downto 0);
			qa        : out std_logic_vector(size-1 downto 0);		
			qb        : out std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_data_mux is 
		generic (size: integer := 16);
		port(
			clk_2x    : in std_logic;
			rst       : in std_logic;
			mux_cnt   : in std_logic;
			da        : in  std_logic_vector(size-1 downto 0);
			db        : in  std_logic_vector(size-1 downto 0);		
			q         : out std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_debounce is 
		generic (min_pw: integer :=1;
				 hold: integer :=10); -- 2 is min useful value
		port(
			clk : in std_logic;
			rst : in std_logic;
			d   : in std_logic;
			q   : out std_logic
			);
	end component;

	component gh_delay is
		generic (clock_delays : integer := 16); 
		port(
			clk  : in std_logic;
			rst  : in std_logic;
			srst : in std_logic := '0';
			d    : in std_logic;
			q    : out std_logic
			);
	end component;

	component gh_delay_bus is
		generic (clock_delays : integer := 16;
				 size : integer := 8); 
		port(
			clk  : in std_logic;
			rst  : in std_logic;
			srst : in std_logic := '0';
			d    : in std_logic_vector(size-1 downto 0);
			q    : out std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_delay_programmable_15 is
	  port(
			clk   : in std_logic;
			rst   : in std_logic;
			srst  : in std_logic := '0';
			d     : in std_logic;
			delay : in std_logic_vector(3 downto 0);
			q     : out std_logic
			);
	end component;

	component gh_delay_programmable_31 is
	  port(
			clk   : in std_logic;
			rst   : in std_logic;
			srst  : in std_logic := '0';
			d     : in std_logic;
			delay : in std_logic_vector(4 downto 0);
			q     : out std_logic
			);
	end component;

	component gh_delay_programmable_63 is
	  port(
			clk   : in std_logic;
			rst   : in std_logic;
			srst  : in std_logic := '0';
			d     : in std_logic;
			delay : in std_logic_vector(5 downto 0);
			q     : out std_logic
			);
	end component;

	component gh_delay_programmable_127 is
	  port(
			clk   : in std_logic;
			rst   : in std_logic;
			srst  : in std_logic := '0';
			d     : in std_logic;
			delay : in std_logic_vector(6 downto 0);
			q     : out std_logic
			);
	end component;

	component gh_delay_programmable_255 is
	  port(
			clk   : in std_logic;
			rst   : in std_logic;
			srst  : in std_logic := '0';
			d     : in std_logic;
			delay : in std_logic_vector(7 downto 0);
			q     : out std_logic
			);
	end component;

	component gh_delay_programmable_255_bus is
		generic (size : integer := 8);
		port(
			clk   : in std_logic;
			rst   : in std_logic;
			srst  : in std_logic := '0';
			d     : in std_logic_vector(size-1 downto 0);
			delay : in std_logic_vector(7 downto 0);
			q     : out std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_delay_programmable_bus is
		generic (size_data : integer := 8;
				 size_add : integer := 8);
		port(
			clk   : in std_logic;
			rst   : in std_logic;
			d     : in std_logic_vector(size_data-1 downto 0);
			delay : in std_logic_vector(size_add-1 downto 0);
			q     : out std_logic_vector(size_data-1 downto 0)
			);
	end component;

	component gh_edge_det is
		port(
			clk : in std_logic;
			rst : in std_logic;
			d   : in std_logic;
			re  : out std_logic; -- rising edge (need sync source at d)
			fe  : out std_logic; -- falling edge (need sync source at d)
			sre : out std_logic; -- sync'd rising edge
			sfe : out std_logic  -- sync'd falling edge
			);
	end component gh_edge_det;

	component gh_edge_det_xcd is
		port(
			iclk : in std_logic;  -- clock for input data signal
			oclk : in std_logic;  -- clock for output data pulse
			rst  : in std_logic;
			d    : in std_logic;
			re   : out std_logic; -- rising edge 
			fe   : out std_logic  -- falling edge 
			);
	end component;

	component gh_gray2binary is
		generic (size: integer := 8);
		port(	
			g   : in std_logic_vector(size-1 downto 0);	-- gray code in
			b   : out std_logic_vector(size-1 downto 0) -- binary value out
			);
	end component;

	component gh_parity_gen_serial is
		port(	
			clk      : in std_logic;
			rst      : in std_logic; 
			srst     : in std_logic;
			sd       : in std_logic; -- sample data pulse
			d        : in std_logic; -- data
			q        : out std_logic -- parity 
			);
	end component gh_parity_gen_serial;

	component gh_pulse_generator is
		generic(size_period: integer := 16); 
		port(
			clk         : in std_logic; 
			rst         : in std_logic;
			period      : in std_logic_vector (size_period-1 downto 0);
			pulse_width : in std_logic_vector (size_period-1 downto 0);
			enable      : in std_logic;
			pulse       : out std_logic 
			);
	end component;

	component gh_pw_wtoa is
		generic (pw_size: integer :=7;
				 t_size: integer :=7); -- t_size must be >= pw_size
		port(
			clk       : in std_logic;
			rst       : in std_logic;
			pulse     : in std_logic;
			new_pulse : out std_logic;
			pw        : out std_logic_vector(pw_size-1 downto 0);
			toa       : out std_logic_vector(t_size-1 downto 0);
			ttime     : out std_logic_vector(t_size-1 downto 0); -- output of free 
																 -- running counter
			active    : out std_logic -- high with pulse, low with no new 
		);                            -- pulse for ttime wrap around
	end component;

	component gh_pwm is
		generic(size : integer := 8);
		port(
			clk      : in std_logic;
			rst      : in std_logic;
			d_format : in std_logic:='0'; -- '0' = two's comp   '1' = offset binary
			data     : in std_logic_vector(size-1 downto 0);
			pwmo     : out std_logic;
			nd       : out std_logic -- new data sample strobe
			);
	end component;

	component gh_register_control_ce is
		generic (size: integer := 8);
		port(	
			clk  : in		std_logic;
			rst  : in		std_logic; 
			ce   : in		std_logic; -- clock enable
			mode : in		std_logic_vector(1 downto 0);
			d    : in		std_logic_vector(size-1 downto 0);
			q    : out		std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_stretch is 
		generic (stretch_count: integer :=1023);
		 port(
			 clk : in std_logic;
			 rst : in std_logic;
			 d : in std_logic;
			 q : out std_logic
			 );
	end component gh_stretch;

	component gh_stretch_low is 
		generic (stretch_count: integer :=10);
		port(
			clk : in std_logic;
			rst : in std_logic;
			dn  : in std_logic;
			qn  : out std_logic
			);
	end component;

	component gh_stretch_programmable is
		generic (size : integer := 8);
		port(
			clk     : in std_logic;
			rst     : in std_logic;
			d       : in std_logic;
			stretch : in std_logic_vector(size-1 downto 0);
			q       : out std_logic
			);
	end component;

	component gh_stretch_programmable_low is
		generic (size : integer := 8);
		port(
			clk     : in std_logic;
			rst     : in std_logic;
			dn      : in std_logic;
			stretch : in std_logic_vector(size-1 downto 0);
			qn      : out std_logic
			);
	end component;

	component gh_wdt is 
		generic (ticks : integer :=1023); -- number of clock ticks q <= '1'
		 port(
			 clk  : in std_logic;
			 rst  : in std_logic;
			 t_en : in std_logic:='1';
			 t    : in std_logic; -- either edge will reset count
			 q    : out std_logic
			 );
	end component;

	component gh_wdt_programmable is 
		generic (size : integer :=8); 
		 port(
			 clk      : in std_logic;
			 rst      : in std_logic;
			 t_en     : in std_logic; -- high will enable counting, low will load
			 t_time   : in std_logic_vector(size-1 downto 0);  -- timer time
			 q        : out std_logic  -- high with time out
			 );
	end component;

end package gh_custom_MSI_p;