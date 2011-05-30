------------------------------------------------------------------------
-- 
-- Project:         APB 
--
--
-- File name:       apb_p.vhd
--
-- Description:     This package declares types to be used with the APB bus
--                  of the Advanced Microcontroller Bus Architecture (AMBA 3).
--
-- History:
--     Project created  2009/03/06    d. faveyrial
--
------------------------------------------------------------------------

library IEEE;
  use IEEE.STD_LOGIC_1164.all;

package APB is
  -----------------------------------------------------------------------------
  -- Definitions for AMBA(TM) 3  Advanced Peripheral Bus (APB)
  -----------------------------------------------------------------------------
  -- Records are defined for the input and output of an APB Slave. These
  -- records are grouped in arrays, for scalability, and new records using
  -- these arrays are defined for the input and output of an APB Bridge.
  --
  -- The routing of the clock and reset signals defined in the AMBA(TM)
  -- Specification is not covered in this package, since being dependent on
  -- the clock and reset conventions defined at system level.
  --
  -- The PCLK and PRESETn signals are routed separately:
  --    pclk:       STD_ULOGIC;                         -- rising edge
  --    presetn:    STD_ULOGIC;                         -- active low reset
  --
  --
  -- When implementing modules with this package, it is recommended that the
  -- information on the address bus PADDR is interpreted as byte addresses.
  --
  -----------------------------------------------------------------------------
  -- Constant definitions for AMBA(TM) APB
  -----------------------------------------------------------------------------
  constant PDMAX  : POSITIVE range 8 to 32 := 8;      -- data width
  constant PAMAX  : POSITIVE range 8 to 32 := 32;     -- address width
  
  -----------------------------------------------------------------------------
  -- Definitions for AMBA(TM) APB Slaves  
  -----------------------------------------------------------------------------
  -- APB slave inputs (PCLK and PRESETn routed separately)
  type APB_SLV_IN_TYPE is
    record
      PSEL    : STD_ULOGIC;                         -- slave select
      PENABLE : STD_ULOGIC;                         -- strobe
      PADDR   : STD_LOGIC_VECTOR(PAMAX-1 downto 0); -- address bus (byte)
      PWRITE  : STD_ULOGIC;                         -- write
      PWDATA  : STD_LOGIC_VECTOR(PDMAX-1 downto 0); -- write data bus
    end record;

  -- APB slave outputs
  type APB_SLV_OUT_TYPE is
    record
      PRDATA  : STD_LOGIC_VECTOR(PDMAX-1 downto 0); -- read data bus
      PREADY  : std_ulogic;                         -- ready
      PSLVERR : std_ulogic;                         -- transfert failure
    end record;
  
  -----------------------------------------------------------------------------
  -- Definitions for AMBA(TM) APB Master or APB Bridge 
  -----------------------------------------------------------------------------
  -- supporting array types
  type APB_SLV_IN_VECTOR  is array (NATURAL range <> ) of APB_SLV_IN_TYPE;
  type APB_SLV_OUT_VECTOR is array (NATURAL range <> ) of APB_SLV_OUT_TYPE;
  
  
  
  -----------------------------------------------------------------------------
  -- APB Components 
  -----------------------------------------------------------------------------
  component APB_BUS is
	  generic (
	    NB_SLAVES    : INTEGER := 2);
	  port (
      SEL_IN       : in  STD_LOGIC_VECTOR(NB_SLAVES-1 downto 0);
      SEL_OUT      : out STD_LOGIC;
      M2S_IN       : in  APB_SLV_IN_TYPE;
      S2M_IN       : in  APB_SLV_OUT_VECTOR(NB_SLAVES-1 downto 0);
      S2M_OUT			 : out APB_SLV_OUT_TYPE;
      M2S_OUT      : out APB_SLV_IN_VECTOR(NB_SLAVES-1 downto 0));
	end component APB_BUS;


	component APB_ID is
	  generic (
	    PROG_NUMBER : INTEGER   range 1061 to 9999 := 1139;
	    REVISION    : CHARACTER range 'A' to 'O' := 'A');
	  port (
	    PCLK        : in  STD_ULOGIC;
	    PRESETn     : in  STD_ULOGIC;
	    APBSlaveIn  : in  APB_SLV_IN_TYPE;
	    APBSlaveOut : out APB_SLV_OUT_TYPE);
	end component APB_ID;

	component APB_WD is
	  generic (
	    WD_INIT1    : INTEGER   range 1 to 6000 := 600; -- en centaine de millisecondes
	    WD_INIT2    : INTEGER   range 1 to 6000 := 60   -- en centaine de millisecondes
	    );
	  port (
	    PCLK        : in  std_logic;
	    PRESETn     : in  std_logic;
	    APBSlaveIn  : in  APB_SLV_IN_TYPE;
	    APBSlaveOut : out APB_SLV_OUT_TYPE;
	    ----
	    WD_CLK      : in  std_logic;
	    WDT         : out std_logic;
	    WD_INT      : out std_logic;
	    WD_RST      : out std_logic
	    );
	end component APB_WD;

end APB;
-------------------------------------------------------------------------------
-- end of file

