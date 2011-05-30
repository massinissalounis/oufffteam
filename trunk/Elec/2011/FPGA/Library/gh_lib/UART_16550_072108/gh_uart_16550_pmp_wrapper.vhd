-----------------------------------------------------------------------------
--	Filename:	gh_uart_16550_wb_wrapper.vhd
--
--	Description:
--		This is (ment to be) a wishbone interface 
--		wrapper for a 16550 compatible UART 
--
--	Copyright (c) 2006 by H LeFevre 
--		A VHDL 16550 UART core
--		an OpenCores.org Project
--		free to use, but see documentation for conditions 
--
--	Revision 	History:
--	Revision 	Date       	Author    	Comment
--	-------- 	---------- 	---------	-----------
--	1.0      	02/25/06  	H LeFevre	Initial revision
--
-----------------------------------------------------------------------------
library ieee ;
use ieee.std_logic_1164.all ;

library work;
use work.pmp_p.all;
use work.gh_registers_gates_p.all;

entity gh_uart_16550_pmp_wrapper is
	port(	  
	-------- pmp signals ------------
		PMP_in		: in PMP_SLV_IN_TYPE;
		PMP_out		: out PMP_SLV_OUT_TYPE;
		
	------ other I/O -----------------------------------	
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
end entity;

architecture a of gh_uart_16550_pmp_wrapper is

COMPONENT gh_edge_det is
	PORT(	
		clk : in STD_LOGIC;
		rst : in STD_LOGIC;
		D   : in STD_LOGIC;
		re  : out STD_LOGIC; -- rising edge (need sync source at D)
		fe  : out STD_LOGIC; -- falling edge (need sync source at D)
		sre : out STD_LOGIC; -- sync'd rising edge
		sfe : out STD_LOGIC  -- sync'd falling edge
		);
END COMPONENT;

COMPONENT gh_register_ce is
	GENERIC (size: INTEGER := 8);
	PORT(	
		clk : IN		STD_LOGIC;
		rst : IN		STD_LOGIC; 
		CE  : IN		STD_LOGIC; -- clock enable
		D   : IN		STD_LOGIC_VECTOR(size-1 DOWNTO 0);
		Q   : OUT		STD_LOGIC_VECTOR(size-1 DOWNTO 0)
		);
END COMPONENT;

COMPONENT gh_uart_16550 is
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
		TX_EN	: out std_logic;
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
END COMPONENT;

	
	signal iRD    : std_logic_vector(7 downto 0);
	signal CS     : std_logic;
	
	signal iCS    : std_logic;

	signal pmp_psel_sync,pmp_psel_sync_temp		: std_logic;
	signal pmp_write_sync, pmp_write_sync_temp	: std_logic;
	signal pmp_read_sync, pmp_read_sync_temp	: std_logic;
	signal pmp_add_sync, pmp_add_sync_temp		: std_logic_vector (PMP_AMAX-1 downto 0);
	signal pmp_data_sync, pmp_data_sync_temp	: std_logic_vector (PMP_DMAX-1 downto 0);
	
begin

-- Synchronisation des signaux PMP entrants
	sync1_cs: gh_dff port map (PMP_In.PMP_SEL,main_clk,main_reset,pmp_psel_sync_temp);
	sync2_cs: gh_dff port map (pmp_psel_sync_temp,main_clk,main_reset,pmp_psel_sync);

	sync1_write: gh_dff port map (PMP_In.PMP_PMWR,main_clk,main_reset,pmp_write_sync_temp);
	sync2_write: gh_dff port map (pmp_write_sync_temp,main_clk,main_reset,pmp_write_sync);

	sync1_read: gh_dff port map (PMP_In.PMP_PMRD,main_clk,main_reset,pmp_read_sync_temp);
	sync2_read: gh_dff port map (pmp_read_sync_temp,main_clk,main_reset,pmp_read_sync);

	sync_data : for j in 0 to PMP_DMAX-1 generate
		sync1_data: gh_dff port map (PMP_In.PMP_WDATA(j),main_clk,main_reset,pmp_data_sync_temp(j));
		sync2_data: gh_dff port map (pmp_data_sync_temp(j),main_clk,main_reset,pmp_data_sync(j));
	end generate sync_data;
	
	sync_add : for k in 0 to PMP_AMAX-1 generate
		sync1_add: gh_dff port map (PMP_In.PMP_ADDR(k),main_clk,main_reset,pmp_add_sync_temp(k));
		sync2_add: gh_dff port map (pmp_add_sync_temp(k),main_clk,main_reset,pmp_add_sync(k));
	end generate sync_add;


U1 : gh_uart_16550 
	PORT MAP (
		clk    => main_clk,
		BR_clk => BR_clk,
		rst    => main_reset,
		CS     => iCS,
		WR     => pmp_write_sync,
		ADD    => pmp_add_sync (2 downto 0),
		D      => pmp_data_sync,
		sRX	   => sRX,
		CTSn   => CTSn,
		DSRn   => DSRn,
		RIn    => RIn,
		DCDn   => DCDn,
		
		sTX    => sTX,
		TX_EN  => TX_EN,
		DTRn   => DTRn,
		RTSn   => RTSn,
		OUT1n  => OUT1n,
		OUT2n  => OUT2n,
		TXRDYn => TXRDYn,
		RXRDYn => RXRDYn,
		
		IRQ    => IRQ,
		B_CLK  => B_CLK,
		RD     => PMP_out.PMP_RDATA
		);

		CS <= '1' when ((pmp_psel_sync = '1') and ( pmp_read_sync = '1' or pmp_write_sync = '1')) else
	      '0';
		
U3 : gh_edge_det -- génération d'un chip select d'une période d'hologe
	PORT MAP (
		clk => main_clk,
		rst => main_reset,
		d => CS,
		re => iCS);
		
		
end a;
