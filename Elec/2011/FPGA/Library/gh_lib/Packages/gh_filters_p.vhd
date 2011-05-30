--------------------------------------------------------------------------------------------------------
-- Project :			gh Library
--
-- File:			gh_filters_p.vhd
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
-- Purpose: Package to define filters components in gh library
--------------------------------------------------------------------------------------------------------

library ieee ;
use ieee.std_logic_1164.all ;

package gh_filters_p is
	
	component gh_tvfd_filter_w is  
		generic(
			modulo_bits : integer := 7; -- must have bits to hold modulo_count
			modulo_count : integer := 100;
			x : integer := 3; -- filter order = 2^x
			d_size : integer := 16;	-- size of data path
			c_size : integer := 16	-- size of filter coeff 
			);
		port(
			clk : in std_logic;
			rst : in std_logic;
			start : in std_logic;
			rate : in std_logic_vector(modulo_bits downto 0);
			l_in : in std_logic_vector(d_size-1 downto 0);
			r_in : in std_logic_vector(d_size-1 downto 0);
			coef_data : in std_logic_vector(c_size-1 downto 0);
			nd : out std_logic;
			rom_add : out std_logic_vector((modulo_bits + x -1) downto 0); 
			l_out : out std_logic_vector(d_size-1 downto 0);
			r_out : out std_logic_vector(d_size-1 downto 0)
			);
	end component;

	component gh_cic_decimation_m1 is
		generic (data_in_size : integer := 16; --
		         data_out_size : integer := 37; --
		         stages : integer := 4; -- listed as n in formula's
		         m : integer := 1);	 -- eather 1 or 2
		port(	
			clk      : in  std_logic;
			rst      : in  std_logic; 
			d        : in  std_logic_vector(data_in_size-1 downto 0);
			nd       : in  std_logic; -- new data strobe, 1 clock wide 
			              -- r in formula's is (period of nd)/(period of clk)
			q        : out std_logic_vector(data_out_size-1 downto 0)
			);
	end component;

	component gh_cic_decimation_m2 is
		generic (data_in_size : integer := 16; --
		         data_out_size : integer := 37; --
		         stages : integer := 4; -- listed as n in formula's
		         m : integer := 1);	 -- eather 1 or 2
		port(	
			clk      : in  std_logic;
			rst      : in  std_logic; 
			d        : in  std_logic_vector(data_in_size-1 downto 0);
			nd       : in  std_logic; -- new data strobe, 1 clock wide 
			              -- r in formula's is (period of nd)/(period of clk)
			q        : out std_logic_vector(data_out_size-1 downto 0)
			);
	end component;

	component gh_cic_filter is
		generic (data_in_size : integer := 16; --
		         data_out_size : integer := 37; --
		         mode : integer := 0; -- mode 0 is decimation
		                              -- mode 1 is interpolation
		         stages : integer := 4; -- listed as n in formula's
		         m : integer := 1);	 -- eather 1 or 2
		port(	
			clk      : in  std_logic;
			rst     : in  std_logic; 
			din      : in  std_logic_vector(data_in_size-1 downto 0);
			nd       : in  std_logic; -- new data strobe, 1 clock wide 
			              -- r in formula's is (period of nd)/(period of clk)
			q        : out std_logic_vector(data_out_size-1 downto 0)
			);
	end component;

	component gh_cic_interpolation is
		generic (data_in_size : integer := 16; --
		         data_out_size : integer := 37; --
		         stages : integer := 4; -- listed as n in formula's
		         m : integer := 1);	 -- eather 1 or 2
		port(	
			clk      : in  std_logic;
			rst      : in  std_logic; 
			din      : in  std_logic_vector(data_in_size-1 downto 0);
			nd       : in  std_logic; -- new data strobe, 1 clock wide 
			              -- r in formula's is (period of nd)/(period of clk)
			q        : out std_logic_vector(data_out_size-1 downto 0)
			);
	end component;

	component gh_cic_interpolation_m1 is
		generic (data_in_size : integer := 16; --
		         data_out_size : integer := 37; --
		         stages : integer := 4 -- listed as n in formula's
		         );	 
		port(	
			clk      : in  std_logic;
			rst      : in  std_logic; 
			d        : in  std_logic_vector(data_in_size-1 downto 0);
			nd       : in  std_logic; -- new data strobe, 1 clock wide 
			              -- r in formula's is (period of nd)/(period of clk)
			q        : out std_logic_vector(data_out_size-1 downto 0)
			);
	end component;

	component gh_cic_interpolation_m2 is
		generic (data_in_size : integer := 16; --
		         data_out_size : integer := 37; --
		         stages : integer := 4 -- listed as n in formula's
		         );
		port(	
			clk      : in  std_logic;
			rst      : in  std_logic; 
			din      : in  std_logic_vector(data_in_size-1 downto 0);
			nd       : in  std_logic; -- new data strobe, 1 clock wide 
			              -- r in formula's is (period of nd)/(period of clk)
			q        : out std_logic_vector(data_out_size-1 downto 0)
			);
	end component;

	component gh_filter_ab_interpolation is
		generic (size: integer :=16);
		port(
			clk : in std_logic;
			rst : in std_logic;
			ce  : in std_logic:='1';
			d   : in std_logic_vector(size-1 downto 0);
			qa  : out std_logic_vector(size-1 downto 0);
			qb  : out std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_filter_compensation_2db is
		generic (size: integer :=16);
		port(
			clk : in std_logic;
			rst : in std_logic;
			ce  : in std_logic:='1';
			d   : in std_logic_vector(size-1 downto 0);
			q   : out std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_filter_compensation_4db is
		generic (size: integer :=16);
		port(
			clk : in std_logic;
			rst : in std_logic;
			ce  : in std_logic:='1';
			d   : in std_logic_vector(size-1 downto 0);
			q   : out std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_filter_compensation_6db is
		generic (size: integer :=16);
		port(
			clk : in std_logic;
			rst : in std_logic;
			ce  : in std_logic:='1';
			d   : in std_logic_vector(size-1 downto 0);
			q   : out std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_fir_coef_prom is
		port (
			clk : in std_logic;
			add : in std_logic_vector(3 downto 0);
			q : out std_logic_vector(15 downto 0)
		);
	end component;

	component gh_fir_filter is  
		generic(x : integer := 3); -- filter order = 2^x
		port(
			clk       : in std_logic;
			rst       : in std_logic;
			sample    : in std_logic;
			d_in      : in std_logic_vector(15 downto 0);
			coef_data : in std_logic_vector(15 downto 0);
			rom_add   : out std_logic_vector(x-1 downto 0);
			d_out     : out std_logic_vector(15 downto 0)
			);
	end component;

	component gh_fir_filter_fg is  
		generic(
			x : integer :=3; -- filter order = 2^x
			d_size: integer :=16; -- data size
			c_size: integer :=16; -- coef size
			xbits : integer :=0);  -- extra bits, needed if gain > 1.0
		port(
			clk       : in std_logic;
			rst       : in std_logic;
			sample    : in std_logic;
			d_in      : in std_logic_vector(d_size-1 downto 0);
			coef_data : in std_logic_vector(c_size-1 downto 0);
			rom_add   : out std_logic_vector(x-1 downto 0);
			d_out     : out std_logic_vector(d_size+xbits-1 downto 0)
			);
	end component;

	component gh_fir_pcoef_prom is
		port (
			q : out std_logic_vector(127 downto 0)
		);
	end component;

	component gh_fir_pfilter is  
		generic(
			d_size: integer := 16;
			coef_size: integer := 16;
			fract_bits: integer := 4;
			half_tap_size: integer := 8);
		port(
			clk  : in  std_logic;
			rst  : in std_logic:='0';
			ce   : in std_logic:='1';
			d    : in  std_logic_vector (d_size-1 downto 0);
			coef : in  std_logic_vector (coef_size * half_tap_size -1 downto 0);
			q    : out std_logic_vector (d_size-1 downto 0)
			);
	end component;

	component gh_fir_pfilter_ns is  
		generic(
			d_size: integer := 16;
			coef_size: integer := 16;
			fract_bits: integer := 4;
			half_tap_size: integer := 8);
		port(
			clk  : in  std_logic;
			rst  : in std_logic:='0';
			ce   : in std_logic:='1';
			d    : in  std_logic_vector (d_size-1 downto 0);
			coef : in  std_logic_vector (coef_size * half_tap_size -1 downto 0);
			q    : out std_logic_vector (d_size-1 downto 0)
			);
	end component;

	component gh_fir_pfilter_nsc is  
		generic(
			d_size: integer := 16;
			coef_size: integer := 16;
			fract_bits: integer := 4;
			tap_size: integer := 8);
		port(
			clk  : in  std_logic;
			rst  : in std_logic:='0';
			ce   : in std_logic:='1';
			d    : in  std_logic_vector (d_size-1 downto 0);
			coef : in  std_logic_vector (coef_size * tap_size -1 downto 0);
			q    : out std_logic_vector (d_size-1 downto 0)
			);
	end component;

	component gh_fir_pfilter_ot is  
		generic(
			d_size: integer := 16;
			coef_size: integer := 16;
			fract_bits: integer := 4;
			half_tap_size: integer := 8);
		port(
			clk  : in  std_logic;
			rst  : in std_logic:='0';
			ce   : in std_logic:='1';
			d    : in  std_logic_vector (d_size-1 downto 0);
			coef : in  std_logic_vector (coef_size * (half_tap_size +1) -1 downto 0);
			q    : out std_logic_vector (d_size-1 downto 0)
			);
	end component;

	component gh_fir_pfilter_ot_ns is  
		generic(
			d_size: integer := 16;
			coef_size: integer := 16;
			fract_bits: integer := 4;
			half_tap_size: integer := 8);
		port(
			clk  : in  std_logic;
			rst  : in std_logic:='0';
			ce   : in std_logic:='1';
			d    : in  std_logic_vector (d_size-1 downto 0);
			coef : in  std_logic_vector (coef_size * half_tap_size -1 downto 0);
			q    : out std_logic_vector (d_size-1 downto 0)
			);
	end component;

	component gh_tvfd_coef_prom is
		port (
			clk : in std_logic;
			add : in std_logic_vector(9 downto 0);
			q : out std_logic_vector(15 downto 0)
		);
	end component;

	component gh_tvfd_filter is  
		generic(
			modulo_bits : integer := 7; -- must have bits to hold modulo_count
			modulo_count : integer := 100;
			x : integer := 3 -- filter order = 2^x
			);
		port(
			clk : in std_logic;
			rst : in std_logic;
			start : in std_logic;
			rate : in std_logic_vector(modulo_bits-1 downto 0);
			l_in : in std_logic_vector(15 downto 0);
			r_in : in std_logic_vector(15 downto 0);
			coef_data : in std_logic_vector(15 downto 0); -- 02/16/06
			nd : out std_logic;
			rom_add : out std_logic_vector((modulo_bits + x -1) downto 0); -- 02/16/06
			l_out : out std_logic_vector(15 downto 0);
			r_out : out std_logic_vector(15 downto 0)
			);
	end component gh_tvfd_filter;

end package gh_filters_p;