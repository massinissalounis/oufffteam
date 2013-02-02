------------------------------------------------------------------------
--
-- Project:         LPC
--
--
-- Module name:     lpc_tb.vhd
--
-- Description:     Test bench 
--
-- History:
--     Project created  25/02/2009    d. faveyrial
--
------------------------------------------------------------------------

library IEEE;
  use IEEE.STD_LOGIC_1164.all;
  use IEEE.STD_LOGIC_ARITH.all;
  use IEEE.STD_LOGIC_UNSIGNED.all;
library WORK;
  use WORK.LPC.all;
  use WORK.APB.all;

---------------------------------- E N T I T Y -------------------------
entity LPC_TB is
end entity LPC_TB;


----------------------------- A R C H I T E C T U R E ------------------
architecture ARCH_LPC_TB of LPC_TB is

	component LPC_BFM is
		port (
			LCLK       : in    std_logic;
			LRSTn      : in    std_logic;
			LFRAMEn    : out   std_logic;
			LAD        : inout nibble);
	end component LPC_BFM;
	
	component LPC_ANALYSER is
		port (
			LCLK       : in std_logic;
			LRSTn      : in std_logic;
			LFRAMEn    : in std_logic;
			LADIN      : in nibble);
	end component LPC_ANALYSER;
	
	component SIMPLE_LPC     
	  port (
	    LCLK       : in    std_logic;
	    LRSTn      : in    std_logic;
	    LFRAMEn    : in    std_logic;
	    LAD        : inout nibble;
	    ----
	    WD_CLK     : in  	 std_logic;
	    WDT        : out 	 std_logic;
	    WD_INT     : out   std_logic;
	    WD_RST     : out   std_logic);
	end component SIMPLE_LPC;
  
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
  signal LCLK    : std_logic;
  signal LRSTn   : std_logic;
  signal LFRAMEn : std_logic;
  signal LAD     : nibble;
  
------------------------------------------------------------------------
-- ARCHITECTURE DEFINITION
------------------------------------------------------------------------
begin

	LAD <= "HHHH";
	
  ----------------------------------------------------------------------
  -- Clk stimulus
  ----------------------------------------------------------------------
  process
  begin
    loop
      LCLK <= '0';
      wait for 15 ns;
      LCLK <= '1';
      wait for 15 ns;
    end loop;
  end process;

  ----------------------------------------------------------------------
  -- Reset stimulus
  ----------------------------------------------------------------------
  process
  begin
    LRSTn <= '0' after 0 ns,
             '1' after 80 ns;
    wait;
  end process;

  ----------------------------------------------------------------------
  -- LPC Bus Fonctiunnal Model
  ----------------------------------------------------------------------
  BFM: LPC_BFM
        port map(
          LCLK        => LCLK,
          LRSTn       => LRSTn,
          LFRAMEn     => LFRAMEn,
          LAD         => LAD);

  ----------------------------------------------------------------------
  -- LPCanalyser
  ----------------------------------------------------------------------
  ANA: LPC_ANALYSER
        port map(
          LCLK        => LCLK,
		      LRSTn       => LRSTn,
          LFRAMEn     => LFRAMEn,
          LADIN       => LAD);
 
  ----------------------------------------------------------------------
  -- LPC Unit under test
  ----------------------------------------------------------------------
  UUT: SIMPLE_LPC
        port map(
          LCLK        => LCLK,
          LRSTn       => LRSTn,
          LFRAMEn     => LFRAMEn,
          LAD         => LAD,
		      WD_CLK      => LCLK,
		      WDT         => open,
		      WD_INT      => open,
		      WD_RST      => open);
  
 end architecture ARCH_LPC_TB;
------------------------------------------------------------------------
-- end of file  : lpc_tb.vhd














