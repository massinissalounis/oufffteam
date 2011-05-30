------------------------------------------------------------------------
-- 
-- Project:         LPC Bus Package
--
--
-- Module name:     lpc_p.vhd
--
-- Description:
--
-- History:
--     Project created  2009-02-25     d. faveyrial
--
------------------------------------------------------------------------
library IEEE;
  use IEEE.STD_LOGIC_1164.all;
library WORK;
  use WORK.APB.all;
  
    
package LPC is
  ----------------------------------------------------------------------
  -- exported type declarations
  ----------------------------------------------------------------------
  subtype nibble    is std_logic_vector (3 downto 0);
  subtype byte      is std_logic_vector (7 downto 0);
  subtype word      is std_logic_vector (15 downto 0);
  subtype dword     is std_logic_vector (31 downto 0);

  ----------------------------------------------------------------------
  -- exported constant declarations
  ----------------------------------------------------------------------
  -- === Start Type ===
  constant START_TARGET : std_logic_vector( 3 downto 0 ) := "0000";
  constant GNT_MASTER_0 : std_logic_vector( 3 downto 0 ) := "0010";
  constant GNT_MASTER_1 : std_logic_vector( 3 downto 0 ) := "0011";
  constant FIRMW_READ   : std_logic_vector( 3 downto 0 ) := "1101";
  constant FIRMW_WRITE  : std_logic_vector( 3 downto 0 ) := "1110";
  constant STOP_ABORT   : std_logic_vector( 3 downto 0 ) := "1111";

  -- === Cycle Type ===
  constant IO_CYCLE  : std_logic_vector( 1 downto 0 ) := "00";
  constant MEM_CYCLE : std_logic_vector( 1 downto 0 ) := "01";
  constant FWH_CYCLE : std_logic_vector( 1 downto 0 ) := "11";

  -- === Cycle Dir ===
  constant READ_CYCLE  : std_logic := '0';
  constant WRITE_CYCLE : std_logic := '1';

  -- === Cycle Size ===
  constant BYTE_SIZE  : std_logic_vector( 0 to 1 ) := "00";  -- 1 byte
  constant WORD_SIZE  : std_logic_vector( 0 to 1 ) := "01";  -- 2 bytes
  constant DWORD_SIZE : std_logic_vector( 0 to 1 ) := "11";  -- 4 bytes

  -- === Sync field ===
  -- Ready: SYNC achieved with no error.
  constant READY : nibble := "0000";
  -- Short Wait: Peripheral indicating normal wait states.
  constant SWAIT : nibble := "0101";
  -- Long Wait: Peripheral indicating abnormally long wait states.
  constant LWAIT : nibble := "0110";
  -- Error: Sync achieved with error.
  constant ERR   : nibble := "1010";
  
  ----------------------------------------------------------------------
  -- Component declarations
  ----------------------------------------------------------------------
	component LPC2APB is
	  port (
	    -- LPC interface
	    LCLK        : in  std_logic;
	    LRSTn       : in  std_logic;
	    LFRAMEn     : in  std_logic;
	    LADIN       : in  std_logic_vector( 3 downto 0 );
	    LADOUT      : out std_logic_vector( 3 downto 0 );
	    LADOE       : out std_logic;
	    -- APB interface
	    APBSlvToMst : in  APB_SLV_OUT_TYPE;
	    APBMstToSlv : out APB_SLV_IN_TYPE;
	    -- DECODE interface
	    MEM_IOn     : out std_logic;
	    ADD         : out std_logic_vector( 31 downto 0 );
	    SEL         : in  std_logic);
	end component LPC2APB;

	component LPC_BFM is
	  port (
	    LCLK       : in    std_logic;
	    LRSTn      : in    std_logic;
	    LFRAMEn    : out   std_logic;
	    LAD        : inout nibble);
	end component LPC_BFM;

	component LPC_ANALYSER is
	  port (
	    LCLK        : in  std_logic;
	    LRSTn       : in  std_logic;
	    LFRAMEn     : in  std_logic;
	    LADIN       : in  std_logic_vector( 3 downto 0 ));
	end component LPC_ANALYSER;

end package LPC;
------------------------------------------------------------------------
-- end of file  : lpc_p.vhd









