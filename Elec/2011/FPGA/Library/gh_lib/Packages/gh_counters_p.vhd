--------------------------------------------------------------------------------------------------------
-- Project :			gh Library
--
-- File:			gh_counters_p.vhd
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
-- Purpose: Package to define counter components in gh library
--------------------------------------------------------------------------------------------------------

library ieee ;
use ieee.std_logic_1164.all ;

package gh_counters_p is
	
	component gh_counter is
		generic (size: integer :=8);
		port(
			clk   : in	std_logic;
			rst   : in	std_logic;
			load  : in	std_logic;
			ce    : in	std_logic;
			up_d  : in  std_logic;
			d     : in  std_logic_vector(size-1 downto 0);
			q     : out std_logic_vector(size-1 downto 0);
			tc    : out std_logic
			);
	end component gh_counter;
	
	component gh_counter_down_ce_ld is
		generic (size: integer :=8);
		port(
			clk   : in	std_logic;
			rst   : in	std_logic;
			load  : in	std_logic;
			ce    : in	std_logic;
			d     : in  std_logic_vector(size-1 downto 0);
			q     : out std_logic_vector(size-1 downto 0)
			);
	end component gh_counter_down_ce_ld;
	
	component gh_counter_down_ce_ld_tc is
		generic (size: integer :=8);
		port(
			clk   : in	std_logic;
			rst   : in	std_logic;
			load  : in	std_logic;
			ce    : in	std_logic;
			d     : in  std_logic_vector(size-1 downto 0);
			q     : out std_logic_vector(size-1 downto 0);
			tc    : out std_logic
			);
	end component gh_counter_down_ce_ld_tc;
	
	component gh_counter_down_one is
		generic (size: integer :=8);
		port(
			clk   : in	std_logic;
			rst   : in	std_logic;
			load  : in	std_logic;
			ce    : in	std_logic;
			d     : in  std_logic_vector(size-1 downto 0);
			q     : out std_logic_vector(size-1 downto 0);
			tc    : out std_logic; -- added for flexibility
			one   : out std_logic
			);
	end component;
	
	component gh_counter_fr is
		generic (size: integer :=8);
		port(
			clk   : in	std_logic;
			rst   : in	std_logic;
			q     : out std_logic_vector(size-1 downto 0)
			);
	end component gh_counter_fr;
	
	component gh_counter_integer_down is	
		generic(max_count : integer := 8);
		port(	
			clk      : in std_logic;
			rst      : in std_logic; 
			load     : in std_logic; -- load d
			ce       : in std_logic; -- count enable
			d        : in integer range 0 to max_count;
			q        : out integer range 0 to max_count
			);
	end component gh_counter_integer_down;
	
	component gh_counter_integer_up is	
		generic(max_count : integer := 8);
		port(	
			clk      : in std_logic;
			rst      : in std_logic; 
			load     : in std_logic; -- load d
			ce       : in std_logic; -- count enable
			d        : in integer range 0 to max_count;
			q        : out integer range 0 to max_count
			);
	end component gh_counter_integer_up;
	
	component gh_counter_modulo is
		generic (size : integer :=7;
		         modulo :integer :=100 );
		port
		(
			clk   : in	std_logic;
			rst   : in	std_logic; -- active high reset
			ce    : in	std_logic; -- clock enable
			n     : in  std_logic_vector(size-1 downto 0); -- counter step size 
			q     : out std_logic_vector(size-1 downto 0);
			tc    : out std_logic
		);
	end component gh_counter_modulo;
	
	component gh_counter_up_ce is
		generic (size: integer :=8);
		port
		(
			clk   : in	std_logic;
			rst   : in	std_logic;
			ce    : in	std_logic;
			q     : out std_logic_vector(size-1 downto 0)
		);
	end component gh_counter_up_ce;
	
	component gh_counter_up_ce_ld is
		generic (size: integer :=8);
		port(
			clk   : in	std_logic;
			rst   : in	std_logic;
			load  : in	std_logic;
			ce    : in	std_logic;
			d     : in  std_logic_vector(size-1 downto 0);
			q     : out std_logic_vector(size-1 downto 0)
		);
	end component gh_counter_up_ce_ld;
	
	component gh_counter_up_ce_ld_tc is
		generic (size: integer :=8);
		port(
			clk   : in	std_logic;
			rst   : in	std_logic;
			load  : in	std_logic;
			ce    : in	std_logic;
			d     : in  std_logic_vector(size-1 downto 0);
			q     : out std_logic_vector(size-1 downto 0);
			tc    : out std_logic
			);
	end component gh_counter_up_ce_ld_tc;
	
	component gh_counter_up_ce_tc is
		generic (size: integer :=8);
		port(
			clk   : in	std_logic;
			rst   : in	std_logic;
			ce    : in	std_logic;
			q     : out std_logic_vector(size-1 downto 0);
			tc    : out std_logic
			);
	end component gh_counter_up_ce_tc;
	
	component gh_counter_up_sr_ce is
		generic (size: integer :=8);
		port
		(
		clk   : in	std_logic;
		rst   : in	std_logic;
		srst  : in	std_logic;
		ce    : in	std_logic;
		q     : out std_logic_vector(size-1 downto 0)
		);
	end component gh_counter_up_sr_ce;
	
end package gh_counters_p;