------------------------------------------------------------------------
-- 
-- Project:         APB to WISHBONE bridge
--
--
-- Module name:     apb2wb_c.vhd
--
-- Description:
--
-- History:
--     Project created  08/07/2010    d. faveyrial
------------------------------------------------------------------------

library IEEE;
  use IEEE.STD_LOGIC_1164.all;
  use IEEE.STD_LOGIC_ARITH.all;
  use IEEE.STD_LOGIC_UNSIGNED.all;
library WORK;
  use WORK.APB.all;

---------------------------------- E N T I T Y -------------------------
entity APB2WB is
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
end entity APB2WB;


----------------------------- A R C H I T E C T U R E ------------------
architecture ARCH_APB2WB of APB2WB is

  ----------------------------------------------------------------------
  -- procedure and function declarations
  ----------------------------------------------------------------------

  ----------------------------------------------------------------------
  -- type declarations
  ----------------------------------------------------------------------
                          
  ----------------------------------------------------------------------
  -- constant declarations
  ----------------------------------------------------------------------

  ----------------------------------------------------------------------
  -- signal declarations
  ----------------------------------------------------------------------
  
------------------------------------------------------------------------
-- ARCHITECTURE DEFINITION
------------------------------------------------------------------------
begin
  CLK_O <= PCLK;
  RST_O <= not PRESETn;
  ADR_O <= APBSlaveIn.PADDR;
  DAT_O <= APBSlaveIn.PWDATA;
  STB_O <= APBSlaveIn.PENABLE;
  CYC_O <= APBSlaveIn.PSEL and APBSlaveIn.PENABLE;
  SEL_O <= APBSlaveIn.PSEL;
  WE_O  <= APBSlaveIn.PWRITE;
  APBSlaveOut.PRDATA  <= DAT_I;
  APBSlaveOut.PREADY  <= ACK_I;
  APBSlaveOut.PSLVERR <= '0';
end architecture ARCH_APB2WB;
------------------------------------------------------------------------
-- end of file  : apb2wb_c.vhd
