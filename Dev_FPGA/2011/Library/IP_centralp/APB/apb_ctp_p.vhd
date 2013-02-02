------------------------------------------------------------------------
-- 
-- Project:         CENTRALP APB Components Package
--
--
-- Module name:     apb_ctp_p.vhd
--
-- Description:
--
-- History:
--     Project created  2010-07-05     d. faveyrial
--     Modified         2010-08-30     d. faveyrial
--     Add apb_i2c      2010-11-19     d. faveyrial
------------------------------------------------------------------------
library IEEE;
  use IEEE.STD_LOGIC_1164.all;
library WORK;
  use WORK.APB.all;
  
    
package APB_CTP is

  ----------------------------------------------------------------------
  -- Component declarations
  ----------------------------------------------------------------------
  -- component APB_BUS is
    -- generic (
      -- NB_SLAVES    : INTEGER := 2);
    -- port (
      -- SEL_IN       : in  STD_LOGIC_VECTOR(NB_SLAVES-1 downto 0);
      -- SEL_OUT      : out STD_LOGIC;
      -- M2S_IN       : in  APB_SLV_IN_TYPE;
      -- S2M_IN       : in  APB_SLV_OUT_VECTOR(NB_SLAVES-1 downto 0);
      -- S2M_OUT      : out APB_SLV_OUT_TYPE;
      -- M2S_OUT      : out APB_SLV_IN_VECTOR(NB_SLAVES-1 downto 0));
  -- end component APB_BUS;

  component APB_SLAVE is
    port (
      PCLK        : in  STD_ULOGIC;
      PRESETn     : in  STD_ULOGIC;
      APBSlaveIn  : in  APB_SLV_IN_TYPE;
      APBSlaveOut : out APB_SLV_OUT_TYPE);
  end component APB_SLAVE;

  -- component APB_ID is
    -- generic (
      -- PROG_NUMBER : INTEGER   range 1061 to 9999 := 1139;
      -- REVISION    : CHARACTER range 'A' to 'O' := 'A');
    -- port (
      -- PCLK        : in  STD_ULOGIC;
      -- PRESETn     : in  STD_ULOGIC;
      -- APBSlaveIn  : in  APB_SLV_IN_TYPE;
      -- APBSlaveOut : out APB_SLV_OUT_TYPE);
  -- end component APB_ID;

  component APB_PORT80 is
    port (
      PCLK        : in  STD_ULOGIC;
      PRESETn     : in  STD_ULOGIC;
      APBSlaveIn  : in  APB_SLV_IN_TYPE;
      APBSlaveOut : out APB_SLV_OUT_TYPE;
      PORT80      : out STD_ULOGIC;
      TxOUTPUT    : out STD_ULOGIC);
  end component APB_PORT80;

  component APB_PS2 is
    port (
      PCLK        : in  STD_ULOGIC;
      PRESETn     : in  STD_ULOGIC;
      APBSlaveIn  : in  APB_SLV_IN_TYPE;
      APBSlaveOut : out APB_SLV_OUT_TYPE;
  
      -- IRQ output
      ps2KIRQ     : out STD_LOGIC;
      ps2MIRQ     : out STD_LOGIC;
  
      -- PS2 signals
      PS2KCLKIN   : in  STD_LOGIC;
      PS2KCLKOUT  : out STD_LOGIC;
      ps2KDATIN   : in  STD_LOGIC;
      ps2KDATOUT  : out STD_LOGIC;
      ps2MCLKIN   : in  STD_LOGIC;
      ps2MCLKOUT  : out STD_LOGIC;
      ps2MDATIN   : in  STD_LOGIC;
      ps2MDATOUT  : out STD_LOGIC;
      ps2GATEA20  : out STD_LOGIC;
      ps2KRESET   : out STD_LOGIC);
  end component APB_PS2;

  -- component APB_UART is
    -- port (
      -- PCLK        : in  STD_ULOGIC;
      -- PRESETn     : in  STD_ULOGIC;
      -- APBSlaveIn  : in  APB_SLV_IN_TYPE;
      -- APBSlaveOut : out APB_SLV_OUT_TYPE;
  
      -- INTR        : out STD_LOGIC; -- Interrupt
  
      ---- Receiver interface
      -- SIN         : in  STD_LOGIC; -- Receiver serial input
      -- RxRDYn      : out STD_LOGIC; -- Receiver ready
  
      ---- Transmitter interface
      -- SOUT        : out STD_LOGIC; -- Transmitter serial output
      -- TxRDYn      : out STD_LOGIC; -- Transmitter ready
  
      ---- Modem interface
      -- DCDn        : in  STD_LOGIC; -- Data Carrier Detect
      -- CTSn        : in  STD_LOGIC; -- Clear To Send
      -- DSRn        : in  STD_LOGIC; -- Data Set Ready
      -- RIn         : in  STD_LOGIC; -- Ring Indicator
      -- DTRn        : out STD_LOGIC; -- Data Terminal Ready
      -- RTSn        : out STD_LOGIC);-- Request To Send component
  -- end component APB_UART;

  component APB_I2C     
    port (
      PCLK          : in  STD_ULOGIC;
      PRESETn       : in  STD_ULOGIC;
      APBSlaveIn    : in  APB_SLV_IN_TYPE;
      APBSlaveOut   : out APB_SLV_OUT_TYPE;
      INTR          : out STD_LOGIC;          -- Interrupt
        -- i2c lines
      SCL_PAD_I     : in  STD_LOGIC;          -- i2c clock line input
      SCL_PAD_O     : out STD_LOGIC;          -- i2c clock line output
      SCL_PADOEN_O  : out STD_LOGIC;          -- i2c clock line output enable, active low
      SDA_PAD_I     : in  STD_LOGIC;          -- i2c data line input
      SDA_PAD_O     : out STD_LOGIC;          -- i2c data line output
      SDA_PADOEN_O  : out STD_LOGIC           -- i2c data line output enable, active low
      );
  end component APB_I2C;
  
  component APB_WD is
    generic (
      WD_INIT1    : INTEGER   range 1 to 6000 := 600; -- en centaine de millisecondes
      WD_INIT2    : INTEGER   range 1 to 6000 := 60   -- en centaine de millisecondes
      );
    port (
      PCLK        : in  STD_ULOGIC;
      PRESETn     : in  STD_ULOGIC;
      APBSlaveIn  : in  APB_SLV_IN_TYPE;
      APBSlaveOut : out APB_SLV_OUT_TYPE;
      ----
      WD_CLK      : in  STD_ULOGIC;
      WDT         : out STD_ULOGIC;
      WD_INT      : out STD_ULOGIC;
      WD_RST      : out STD_ULOGIC
      );
  end component APB_WD;
  
  component APB_ISA is
    port (
      PCLK        : in  STD_LOGIC;
      PRESETn     : in  STD_LOGIC;
      APBSlaveIn  : in  APB_SLV_IN_TYPE;
      APBSlaveOut : out APB_SLV_OUT_TYPE;
      -- DECODE interface
      MEM_IOn     : in  STD_LOGIC;
      ADD         : in  STD_LOGIC_VECTOR( 31 downto 0 );
      SEL         : out STD_LOGIC;
      -- ISA interface
      ISA_RESET   : out STD_LOGIC;
      ISA_BCLK    : out STD_LOGIC;
      ISA_SMEMRn  : out STD_LOGIC;
      ISA_SMEMWn  : out STD_LOGIC;
      ISA_IORn    : out STD_LOGIC;
      ISA_IOWn    : out STD_LOGIC;
      ISA_IOCHRDY : in  STD_LOGIC;
      ISA_SA      : out STD_LOGIC_VECTOR(19 downto 0);
      ISA_SDO     : out STD_LOGIC_VECTOR(7 downto 0);
      ISA_SDI     : in  STD_LOGIC_VECTOR(7 downto 0);
      ISA_SDEN    : out STD_LOGIC );
  end component APB_ISA;

  component APB2WB     
    port (
      -- Global reset and clock
      PCLK        : in  STD_ULOGIC;
      PRESETn     : in  STD_ULOGIC;
      -- APB interface
      APBSlaveIn  : in  APB_SLV_IN_TYPE;
      APBSlaveOut : out APB_SLV_OUT_TYPE;
      -- wishbone interface
      CLK_O       : out STD_LOGIC;
      RST_O       : out STD_LOGIC;
      ADR_O       : out STD_LOGIC_VECTOR(PAMAX-1 downto 0);
      DAT_O       : out STD_LOGIC_VECTOR(PDMAX-1 downto 0);
      DAT_I       : in  STD_LOGIC_VECTOR(PDMAX-1 downto 0);
      STB_O       : out STD_LOGIC;
      CYC_O       : out STD_LOGIC;
      SEL_O       : out STD_LOGIC;
      WE_O        : out STD_LOGIC;
      ACK_I       : in  STD_LOGIC);
  end component APB2WB;
  
end package APB_CTP;
------------------------------------------------------------------------
-- end of file  : apb_ctp_p.vhd











