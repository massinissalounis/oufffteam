--------------------------------------------------------------------------------
-- 
-- Project:         APB Bus Component
--
--
-- Module name:     apb_bus_c.vhd
--
-- Description:
--
-- History:
--     Project created  18/04/2009   d. faveyrial
--
--------------------------------------------------------------------------------

library IEEE;
  use IEEE.STD_LOGIC_1164.all;
library WORK;
  use WORK.APB.all;

---------------------------------- E N T I T Y ---------------------------------
entity APB_BUS is
    generic (
            NB_SLAVES    : integer := 2
            );
    port (
            SEL_IN       : in  STD_LOGIC_VECTOR(NB_SLAVES-1 downto 0);
            SEL_OUT      : out STD_LOGIC;
            M2S_IN       : in  APB_SLV_IN_TYPE;
            S2M_IN       : in  APB_SLV_OUT_VECTOR(NB_SLAVES-1 downto 0);
            S2M_OUT      : out APB_SLV_OUT_TYPE;
            M2S_OUT      : out APB_SLV_IN_VECTOR(NB_SLAVES-1 downto 0)
        );
end entity APB_BUS;


----------------------------- A R C H I T E C T U R E --------------------------
architecture ARCH_APB_BUS of APB_BUS is

  ------------------------------------------------------------------------------
  -- constant declarations
    constant LAST_SLAVE : integer := NB_SLAVES-1;
    constant S2M_IDLE   : APB_SLV_OUT_TYPE := ((others => '0'), '1', '0');
	                                             -- data=0, ready, no errors
	                                           
  ------------------------------------------------------------------------------
  -- signal declarations
	signal sel : std_logic_vector(NB_SLAVES-1 downto 0);
	signal s2m : APB_SLV_OUT_VECTOR(NB_SLAVES-1 downto 0);

--------------------------------------------------------------------------------
-- ARCHITECTURE DEFINITION
begin

	------------------------------------------------------------------------------
	-- SEL generation
	sel(0) <= SEL_IN(0);
	
	SEL_GEN: 
	for i in 1 to LAST_SLAVE generate
	begin
		sel(i) <= sel(i-1) or SEL_IN(i);
	end generate;
	
	SEL_OUT <= sel(NB_SLAVES-1);
	
	------------------------------------------------------------------------------
	-- M2S_OUT generation
	M2S_OUT_GEN:
  for i in 0 to LAST_SLAVE generate
	begin
		M2S_OUT(i).PSEL    <= M2S_IN.PSEL and SEL_IN(i);
		M2S_OUT(i).PENABLE <= M2S_IN.PENABLE;
		M2S_OUT(i).PWRITE  <= M2S_IN.PWRITE;
		M2S_OUT(i).PADDR   <= M2S_IN.PADDR;
		M2S_OUT(i).PWDATA  <= M2S_IN.PWDATA;
	end generate;
	
	
	------------------------------------------------------------------------------
	-- S2M generation
	s2m(0) <= S2M_IN(0) when SEL_IN(0)='1' else S2M_IDLE;
	
	S2M_GEN:
	for i in 1 to LAST_SLAVE generate
	begin
		s2m(i) <= S2M_IN(i) when SEL_IN(i)='1' else s2m(i-1);
	end generate;

  S2M_OUT <= s2m(LAST_SLAVE);
  
end architecture ARCH_APB_BUS;
--------------------------------------------------------------------------------------
-- end of file  : apb_bus_c.vhd
