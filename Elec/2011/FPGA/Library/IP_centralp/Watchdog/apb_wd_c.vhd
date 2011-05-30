------------------------------------------------------------------------
-- 
-- Project:         Watchdog
--
--
-- Module name:     apb_wd_c.vhd
--
-- Description:
--
-- History:
--     Project created  28/02/2009    d. faveyrial
--
------------------------------------------------------------------------

library IEEE;
  use IEEE.STD_LOGIC_1164.all;
  use IEEE.STD_LOGIC_ARITH.all;
  use IEEE.STD_LOGIC_UNSIGNED.all;
library WORK;
  use WORK.APB.all;

-------------------------- E N T I T Y -----------------------
entity APB_WD is
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
end APB_WD;

---------------------- A R C H I T E C T U R E ---------------
architecture ARCH_APB_WD of APB_WD is

  ------------------------------------------------------------
  -- conversion Integer to Std_logic_vector 
  function int_2_slv (val, SIZE : INTEGER) return STD_LOGIC_VECTOR is

    variable result : std_logic_vector(SIZE-1 downto 0);
    variable l_val   : integer := val;

  begin

    assert SIZE > 1
      report "Error : function missuse : in_2_slv(val, negative size)"
      severity FAILURE;

    for i in 0 to result'length-1 loop
      if (l_val mod 2) = 0 then
        result(i) := '0';
      else
        result(i) := '1';
      end if;
      l_val := l_val/2;
    end loop;
    return result;

  end int_2_slv;

  ------------------------------------------------------------
  -- alias declarations
  
  -- slave select
  alias psel    : STD_ULOGIC is APBSlaveIn.psel;
  -- strobe         
  alias penable : STD_ULOGIC is APBSlaveIn.penable; 
  -- write      
  alias pwrite  : STD_ULOGIC is APBSlaveIn.pwrite;
  -- address bus (byte)        
  alias paddr   : STD_LOGIC_VECTOR(PAMAX-1 downto 0)  is APBSlaveIn.paddr; 
  -- write data bus
  alias pwdata  : STD_LOGIC_VECTOR(7 downto 0) is APBSlaveIn.pwdata;
  -- read data bus
  alias prdata  : STD_LOGIC_VECTOR(7 downto 0) is APBSlaveOut.prdata;

  ------------------------------------------------------------
  -- type declarations
  type WD_REFRESH_STATE_TYPE is (IDLE, STEP1, REFRESH);
  
  ------------------------------------------------------------
  -- constant declarations
  constant PRESCALER_LENGTH : integer := 8;
  constant WD_PRESCALER_INIT : std_logic_vector(PRESCALER_LENGTH-1 downto 0) := X"55";
  constant WD_PRESCALER_ZERO : std_logic_vector(PRESCALER_LENGTH-1 downto 0) := (others => '0');
  constant WD_COUNTER_ZERO   : std_logic_vector(PRESCALER_LENGTH-1 downto 0) := (others => '0');
   
  ------------------------------------------------------------
  -- signal declarations
	signal refresh1 					: std_logic;
	signal refresh2 					: std_logic;
  signal refresh_ok 				: std_logic;
  signal wd_refresh					: std_logic;
  
  signal wd_refresh_state 			: WD_REFRESH_STATE_TYPE;
  signal next_wd_refresh_state 	: WD_REFRESH_STATE_TYPE;
  --signal refresh_cmd_timer 			: std_logic;
  
  signal wd_prescaler : std_logic_vector(PRESCALER_LENGTH-1 downto 0);
	signal wd_clk_en 		: std_logic;
  signal wd_counter 	: std_logic_vector(15 downto 0);
  signal wd_timeout 	: std_logic;

  -- definition des registres 
  signal wd_reg       : STD_LOGIC_VECTOR(15 downto 0);
  --signal refresh_reg  : STD_LOGIC_VECTOR(15 downto 0);
  
--------------------DEFINITION DE L'ARCHITECTURE--------------
begin

  APBSlaveOut.PREADY  <= '1'; -- No wait states
  APBSlaveOut.PSLVERR <= '0'; -- No error
  WD_RST              <= '0'; -- not yet implemented
  WD_INT              <= '0'; -- not yet implemented
  ------------------------------------------------------------
  -- Raffraichissement
  
  refresh1   <= '1' when psel='1' and penable='1' and pwrite='1' and
                       paddr(1 downto 0)="00"
                else '0' ;
              
  refresh2   <= '1' when psel='1' and penable='1' and pwrite='1' and
                       paddr(1 downto 0)="01"
                else '0' ;
 
  wd_refresh <= '1' when wd_refresh_state= REFRESH else '0';
  
  refresh_ok <= '1'; --DFA temporairement when refresh_cmd_timer=(others=>'0') else '0';            

  WD_REFRESH_PROCESS:
  process (wd_refresh_state, refresh1, refresh2, refresh_ok)
  begin
    case wd_refresh_state is
    when IDLE =>
      if refresh1 = '1' and pwdata=X"55" then
        next_wd_refresh_state <= STEP1;
      else
        next_wd_refresh_state <= IDLE;
      end if;
    when STEP1 =>
      if refresh2 = '1' and pwdata=X"AA" then
        next_wd_refresh_state <= REFRESH;
      elsif refresh1 = '1' or refresh2 = '1' then
        next_wd_refresh_state <= IDLE;
      else
        next_wd_refresh_state <= STEP1;
      end if;
    when REFRESH =>
      if refresh_ok='1' then
        next_wd_refresh_state <= IDLE;
      else
        next_wd_refresh_state <= REFRESH;
      end if;
    end case;
  end process;

  process (PCLK, PRESETn)
  begin
    if PRESETn='0' then
      wd_refresh_state <= IDLE;
    elsif rising_edge(PCLK) then
      wd_refresh_state <= next_wd_refresh_state;
    end if;
  end process;

 -------------------------------------------------------------
  -- Ecriture du registre de rechargement
 
  process (PCLK, PRESETn)
  begin
    if (PRESETn = '0') then
      -- valeur initiale au reset
      wd_reg <= int_2_slv(WD_INIT2, wd_reg'length);
    elsif (PCLK'event and PCLK='1') then
      if ( psel='1' and paddr(1)='1' and penable='1' and pwrite='1' ) then
        -- ecriture du registre
        if paddr(0)='0' then
          wd_reg(7 downto 0)   <= wd_reg(7 downto 0)   and pwdata ;
        else
          wd_reg(15 downto 8)  <= wd_reg(15 downto 8)  and pwdata ;
        end if;
      end if;
    end if;
  end process;


  ------------------------------------------------------------
  -- Lecture des registres
  with paddr(1 downto 0) select
    APBSlaveOut.prdata <=  --wd_xxx(7 downto 0)       when "00", --reserve pour les fonctions supplementaires
                           --wd_xxx(15 downto 8)      when "01",
                           wd_reg(7 downto 0)       when "10",
                           wd_reg(15 downto 8)      when others;

  --================= W A T C H D O G ======================--

  -- Watchdog output
  process (WD_CLK, PRESETn)
  begin
    if (PRESETn = '0') then
      WDT <= '0';
    elsif rising_edge(WD_CLK) then
      WDT <= wd_timeout ;
   end if;
  end process;

  ------------------------------------------------------------
  -- Watchdog prescaler
 
  process (WD_CLK, PRESETn)
  begin
    if (PRESETn = '0') then
      wd_prescaler <= WD_PRESCALER_INIT;
    elsif rising_edge(WD_CLK) then
        if (wd_refresh = '1') then
          wd_prescaler <= WD_PRESCALER_INIT;
        else
          wd_prescaler <= wd_prescaler-1 ;
        end if;
    end if;
  end process;

  wd_clk_en <= '1' when wd_prescaler= WD_PRESCALER_ZERO else '0';
  
  ------------------------------------------------------------
  -- Watchdog counter
 
  process (WD_CLK, PRESETn)
  begin
    if (PRESETn = '0') then
      -- valeur initiale au reset
      wd_counter <= int_2_slv(WD_INIT1, wd_reg'length);
    elsif rising_edge(WD_CLK) then
      if (wd_clk_en = '1') then
        if (wd_refresh = '1') then
          wd_counter <= wd_reg ;
        elsif (wd_timeout = '0') then
          wd_counter <= wd_counter-1 ;
        else
          wd_counter <= wd_counter ;
        end if;
      end if;
    end if;
  end process;
 
  wd_timeout <= '1' when wd_counter = WD_COUNTER_ZERO else '0' ;

end ARCH_APB_WD;
--------------------------------------------------------------
-- end of file  : apb_wd_c.vhd

