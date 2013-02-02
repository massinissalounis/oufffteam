--------------------------------------------------------------------------------------------------------
-- Project :			gh Library
--
-- File:			gh_registers_gates_p.vhd
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
-- Purpose: Package to define registers gates components in gh library
--------------------------------------------------------------------------------------------------------

library ieee ;
use ieee.std_logic_1164.all ;

package gh_registers_gates_p is

	component gh_shift_reg_sr is
		generic (size: integer := 16;
		         make_reset_preset: boolean := false); 
		port(
			clk      : in std_logic;
			rst      : in std_logic;
			srst     : in std_logic;
			d        : in std_logic;
			q        : out std_logic_vector(size-1 downto 0)
			);
	end component gh_shift_reg_sr ;

	component gh_shift_reg_se_sl is
		generic (size: integer := 16); 
		port(
			clk      : in std_logic;
			rst      : in std_logic;
			srst     : in std_logic:='0';
			se       : in std_logic; -- shift enable
			d        : in std_logic;
			q        : out std_logic_vector(size-1 downto 0)
			);
	end component ;

	component gh_shift_reg_pl_slr is
		generic (size: integer := 16);
		port(
			clk      : in std_logic;
			rst      : in std_logic;
			mode     : in std_logic_vector(1 downto 0); 
			            --  00  hold, do nothing
			            --  01  shift right
			            --  10  shift left
			            --  11  parallel load
			dsl      : in std_logic := '0'; -- data in for shift left
			dsr      : in std_logic := '0'; -- data in for shift right
			d        : in std_logic_vector(size-1 downto 0) := (others => '0');
			q        : out std_logic_vector(size-1 downto 0)
			);
	end component gh_shift_reg_pl_slr;

	component gh_shift_reg_pl_sl is
		generic (size: integer := 16);
		port(
			clk      : in std_logic;
			rst      : in std_logic;
			load     : in std_logic;  -- load data
			se       : in std_logic;  -- shift enable
			d        : in std_logic_vector(size-1 downto 0);
			q        : out std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_shift_reg_pl is
		generic (size: integer := 16);
		port(
			clk      : in std_logic;
			rst      : in std_logic;
			load     : in std_logic;  -- load data
			se       : in std_logic;  -- shift enable
			d        : in std_logic_vector(size-1 downto 0);
			q        : out std_logic_vector(size-1 downto 0)
			);
	end component gh_shift_reg_pl;

	component gh_shift_reg is
		generic (size: integer := 16); 
		port(
			clk      : in std_logic;
			rst      : in std_logic;
			d        : in std_logic;
			q        : out std_logic_vector(size-1 downto 0)
			);
	end component gh_shift_reg ;

	component gh_register_ce is
		generic (size: integer := 8);
		port(	
			clk : in		std_logic;
			rst : in		std_logic; 
			ce  : in		std_logic; -- clock enable
			d   : in		std_logic_vector(size-1 downto 0);
			q   : out		std_logic_vector(size-1 downto 0)
			);
	end component gh_register_ce;

	component gh_register is
		generic (size: integer := 8);
		port(	
			clk : in		std_logic;
			rst : in		std_logic; 
			d   : in		std_logic_vector(size-1 downto 0);
			q   : out		std_logic_vector(size-1 downto 0)
			);
	end component gh_register;

	component gh_mux_16to1_bus is	
		generic (size: integer := 8);
		port(	
			sel : in  std_logic_vector(3 downto 0); -- select control
			a   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			b   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			c   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			d   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			e   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			f   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			g   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			h   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			
			i   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			j   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			k   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			l   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			m   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			n   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			o   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			p   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			y   : out std_logic_vector(size-1 downto 0)	:= (others => '0')
			);
	end component;

	component gh_mux_8to1_bus is	
		generic (size: integer := 8);
		port(	
			sel : in  std_logic_vector(2 downto 0); -- select control
			a   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			b   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			c   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			d   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			e   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			f   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			g   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			h   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			y   : out std_logic_vector(size-1 downto 0) := (others => '0')
			);
	end component;

	component gh_mux_4to1_bus is	
		generic (size: integer := 8);
		port(	
			sel : in  std_logic_vector(1 downto 0); -- select control
			a   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			b   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			c   : in  std_logic_vector(size-1 downto 0) := (others => '0'); 
			d   : in  std_logic_vector(size-1 downto 0) := (others => '0');
			y   : out std_logic_vector(size-1 downto 0)
			);
	end component gh_mux_4to1_bus;

	component gh_mux_4to1 is	
		generic (size: integer := 8);
		port(	
			sel : in  std_logic_vector(1 downto 0); -- select control
			a   : in  std_logic := '0'; 
			b   : in  std_logic := '0';
			c   : in  std_logic := '0'; 
			d   : in  std_logic := '0';
			y   : out std_logic
			);
	end component gh_mux_4to1;

	component gh_mux_2to1_bus is	
		generic (size: integer := 8);
		port(	
			sel : in  std_logic; -- select control
			a   : in  std_logic_vector(size-1 downto 0); 
			b   : in  std_logic_vector(size-1 downto 0);
			y   : out std_logic_vector(size-1 downto 0)
			);
	end component gh_mux_2to1_bus;

	component gh_mux_2to1 is	
		generic (size: integer := 8);
		port(	
			sel : in  std_logic; -- select control
			a   : in  std_logic; 
			b   : in  std_logic;
			y   : out std_logic
			);
	end component gh_mux_2to1;

	component gh_latch is
		generic (size: integer := 8);
		port(	
			le  : in std_logic; 
			d   : in std_logic_vector(size-1 downto 0);
			q   : out std_logic_vector(size-1 downto 0)
			);
	end component;

	component gh_jkff is
		port(
			clk  : in std_logic;
			rst : in std_logic;
			j,k  : in std_logic;
			q    : out std_logic
			);
	end component gh_jkff;

	component gh_dff is
		 port(
			 d    : in std_logic;
			 clk  : in std_logic;
			 rst  : in std_logic;
			 q    : out std_logic
		     );
	end component gh_dff;

	component gh_decode_4to16 is
		port(	
			a   : in  std_logic_vector(3 downto 0); -- address
			g1  : in  std_logic; -- enable positive
			g2n : in  std_logic; -- enable negative
			g3n : in  std_logic; -- enable negative
			y   : out std_logic_vector(15 downto 0)
			);
	end component gh_decode_4to16 ;

	component gh_decode_3to8 is
		port(	
			a   : in  std_logic_vector(2 downto 0); -- address
			g1  : in  std_logic; -- enable positive
			g2n : in  std_logic; -- enable negative
			g3n : in  std_logic; -- enable negative
			y   : out std_logic_vector(7 downto 0)
			);
	end component gh_decode_3to8 ;

	component gh_decode_2to4 is
		port(	
			a   : in  std_logic_vector(1 downto 0); -- address
			g1  : in  std_logic; -- enable positive
			g2n : in  std_logic; -- enable negative
			g3n : in  std_logic; -- enable negative
			y   : out std_logic_vector(3 downto 0)
			);
	end component gh_decode_2to4 ;

	component gh_compare_bmm_s is
		generic (size: integer := 8);
		port(	
				min : in std_logic_vector(size-1 downto 0);
				max : in std_logic_vector(size-1 downto 0); 
				d   : in std_logic_vector(size-1 downto 0);
				y   : out std_logic
			);
	end component;

	component gh_compare_bmm is
		generic (size: integer := 8);
		port(	
				min : in std_logic_vector(size-1 downto 0);
				max : in std_logic_vector(size-1 downto 0); 
				d   : in std_logic_vector(size-1 downto 0);
				y   : out std_logic
			);
	end component;

	component gh_compare_abs_reg is
		generic (size: integer := 16);
		port(	
			clk    : in  std_logic;
			rst    : in  std_logic;
			a      : in  std_logic_vector(size-1 downto 0);
			b      : in  std_logic_vector(size-1 downto 0);
			agb    : out std_logic;
			aeb    : out std_logic;
			alb    : out std_logic;
			as     : out std_logic; -- a sign bit
			bs     : out std_logic; -- b sign bit
			abs_a  : out std_logic_vector(size-1 downto 0);
			abs_b  : out std_logic_vector(size-1 downto 0)
			);
	end component ;

	component gh_compare_abs is
		generic (size: integer := 16);
		port(	
			a      : in  std_logic_vector(size-1 downto 0);
			b      : in  std_logic_vector(size-1 downto 0);
			agb    : out std_logic;
			aeb    : out std_logic;
			alb    : out std_logic;
			as     : out std_logic; -- a sign bit
			bs     : out std_logic; -- b sign bit
			abs_a  : out std_logic_vector(size-1 downto 0);
			abs_b  : out std_logic_vector(size-1 downto 0)
			);
	end component gh_compare_abs ;

	component gh_compare is
		generic (size: integer := 8);
		port(	
			a     : in std_logic_vector(size-1 downto 0);
			b     : in std_logic_vector(size-1 downto 0); 
			agb   : out std_logic;
			aeb   : out std_logic;
			alb   : out std_logic
			);
	end component gh_compare;

	component gh_4byte_reg_4096 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			a    : in std_logic_vector(6 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(4095 downto 0)
			);
	end component;

	component gh_4byte_reg_3072 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			a    : in std_logic_vector(6 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(3071 downto 0)
			);
	end component;

	component gh_4byte_reg_2048 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			a    : in std_logic_vector(5 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(2047 downto 0)
			);
	end component;

	component gh_4byte_reg_1536 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			a    : in std_logic_vector(5 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(1535 downto 0)
			);
	end component;

	component gh_4byte_reg_1024 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			a    : in std_logic_vector(4 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(1023 downto 0)
			);
	end component gh_4byte_reg_1024;

	component gh_4byte_reg_768 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			a    : in std_logic_vector(4 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(767 downto 0)
			);
	end component gh_4byte_reg_768;

	component gh_4byte_reg_512 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			a    : in std_logic_vector(3 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(511 downto 0)
			);
	end component gh_4byte_reg_512;

	component gh_4byte_reg_256 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			a    : in std_logic_vector(2 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(255 downto 0)
			);
	end component gh_4byte_reg_256;

	component gh_4byte_reg_128 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			a    : in std_logic_vector(1 downto 0); -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(127 downto 0)
			);
	end component gh_4byte_reg_128;

	component gh_4byte_reg_64 is 
		port(
			clk  : in std_logic; -- sample clock
			rst  : in std_logic;
			csn  : in std_logic; -- chip select
			wr   : in std_logic; -- write signal
			be   : in std_logic_vector(3 downto 0); -- byte enables
			a    : in std_logic; -- address bus
			d    : in std_logic_vector(31 downto 0);-- data bus in
			rd   : out std_logic_vector(31 downto 0); -- read data
			q    : out std_logic_vector(63 downto 0)
			);
	end component gh_4byte_reg_64;

	component gh_4byte_reg_32 is 
		port(
			clk       :  in std_logic;	-- sample clock
			rst       :  in std_logic;
			wr        :  in std_logic; -- write signal
			be        :  in std_logic_vector(3 downto 0); -- byte enable
			d         :  in std_logic_vector(31 downto 0);-- data bus in
			q         :  out std_logic_vector(31 downto 0)
			);
	end component gh_4byte_reg_32;

	component gh_xor_bus is
		generic(size: integer := 8);
		port(
			a : in std_logic_vector(size downto 1);
			b : in std_logic_vector(size downto 1);
			q : out std_logic_vector(size downto 1)
			);
	end component gh_xor_bus;

end package gh_registers_gates_p;