------------------------------------------------------------------------
-- 
-- Project:         LPC to APB bridge
--
--
-- Module name:     lpc2apb_c.vhd
--
-- Description:
--
-- History:
--     Project created  28/02/2009    d. faveyrial
--     Project updated  20/09/2009    d. faveyrial 
--         inversion poids forts poids faibles pour les données sur le bus LPC
--     Project updated  11/05/2010    d. faveyrial
--         insertion d'un registre sur LADOUT et LADOE 
--     Project updated  31/08/2010    d. faveyrial
--         remplacement de SWAIT par LWAIT (pas de limite en nombre de WAIT STATES) 
------------------------------------------------------------------------

library IEEE;
  use IEEE.STD_LOGIC_1164.all;
  use IEEE.STD_LOGIC_ARITH.all;
  use IEEE.STD_LOGIC_UNSIGNED.all;
library WORK;
  use WORK.LPC.all;
  use WORK.APB.all;

---------------------------------- E N T I T Y -------------------------
entity LPC2APB is
  port (
    -- LPC interface
    LCLK        : in  STD_LOGIC;
    LRSTn       : in  STD_LOGIC;
    LFRAMEn     : in  STD_LOGIC;
    LADIN       : in  STD_LOGIC_VECTOR( 3 downto 0 );
    LADOUT      : out STD_LOGIC_VECTOR( 3 downto 0 );
    LADOE       : out STD_LOGIC;
    -- APB interface
    APBSlvToMst : in  APB_SLV_OUT_TYPE;
    APBMstToSlv : out APB_SLV_IN_TYPE;
    -- DECODE interface
    MEM_IOn     : out STD_LOGIC;
    ADD         : out STD_LOGIC_VECTOR( 31 downto 0 );
    SEL         : in  STD_LOGIC
  );
end entity LPC2APB;


----------------------------- A R C H I T E C T U R E ------------------
architecture ARCH_LPC2APB of LPC2APB is

  ----------------------------------------------------------------------
  -- procedure and function declarations
  ----------------------------------------------------------------------

  ----------------------------------------------------------------------
  -- type declarations
  ----------------------------------------------------------------------
  type LPC_STATE_TYPE is (IDLE,
                          CTDIR,
                          ADDR,
                          DATA0, DATA1,
                          TURN0, TURN1,
                          SYNC,
                          TURN2, TURN3);

  type APB_STATE_TYPE is (IDLE,
                          SETUP,
                          ENABLE);
                          
  ----------------------------------------------------------------------
  -- constant declarations
  ----------------------------------------------------------------------

  ----------------------------------------------------------------------
  -- signal declarations
  ----------------------------------------------------------------------
  -- signals for lpc state machine
  signal lpc_state          : LPC_STATE_TYPE;
  signal next_lpc_state     : LPC_STATE_TYPE;
  -- signals for apb state machine
  signal apb_state          : APB_STATE_TYPE;
  signal next_apb_state     : APB_STATE_TYPE;
  --
  signal index              : STD_LOGIC_VECTOR(2 downto 0);
  signal next_ladoe         : STD_LOGIC;
  signal next_ladout        : STD_LOGIC_VECTOR(3 downto 0);
  signal apb_ready          : STD_LOGIC;
  signal next_apb_ready     : STD_LOGIC;
  signal cmd                : STD_LOGIC_VECTOR(3 downto 0);
  signal next_cmd           : STD_LOGIC_VECTOR(3 downto 0);
  signal wr                 : STD_LOGIC;
  signal io                 : STD_LOGIC;
  signal mem                : STD_LOGIC;
  signal address            : STD_LOGIC_VECTOR(31 downto 0);
  signal next_address       : STD_LOGIC_VECTOR(31 downto 0);
  signal data_lpc2apb       : STD_LOGIC_VECTOR(7 downto 0);
  signal next_data_lpc2apb  : STD_LOGIC_VECTOR(7 downto 0);
  signal data_apb2lpc       : STD_LOGIC_VECTOR(7 downto 0);
  signal next_data_apb2lpc  : STD_LOGIC_VECTOR(7 downto 0);
  signal apb_start          : STD_LOGIC;
  signal pready             : STD_LOGIC;
  
------------------------------------------------------------------------
-- ARCHITECTURE DEFINITION
------------------------------------------------------------------------
begin
  -- Interface to decode logic (out of bridge)
  MEM_IOn <= mem;
  ADD     <= address;
  -- 
  next_cmd <= LADIN when lpc_state=CTDIR           else cmd;
  wr       <= '1'   when cmd(1)=WRITE_CYCLE        else '0';
  io       <= '1'   when cmd(3 downto 2)=IO_CYCLE  else '0';
  mem      <= '1'   when cmd(3 downto 2)=MEM_CYCLE else '0';
  
  next_address <= address(27 downto 0) & LADIN when lpc_state=ADDR else
                  (others=>'0')                when lpc_state=CTDIR else 
                  address;

  next_data_lpc2apb <= 
   data_lpc2apb(7 downto 4) & LADIN when lpc_state=DATA0 else 
   LADIN & data_lpc2apb(3 downto 0) when lpc_state=DATA1 else 
   data_lpc2apb;

  next_ladout <=  data_apb2lpc(3 downto 0) when next_lpc_state=DATA0 else
                  data_apb2lpc(7 downto 4) when next_lpc_state=DATA1 else
                  "1111"                   when next_lpc_state=TURN2 else 
                  READY                    when next_lpc_state=SYNC and next_apb_ready='1' else 
                  LWAIT;

  next_ladoe  <=  '1' when  (next_lpc_state=DATA0 and wr='0') or
                            (next_lpc_state=DATA1 and wr='0') or
                            next_lpc_state=TURN2 or
                            next_lpc_state=SYNC
                  else '0';

  apb_start <= '1' when lpc_state=TURN0 and SEL='1' else '0';

  next_apb_ready <= '1' when apb_state=ENABLE and pready='1' else
                    '0' when apb_state=IDLE  else
                    apb_ready;
  
  APBMstToSlv.psel <= '1' when (apb_state = SETUP) or (apb_state = ENABLE) else
                      '0';
  APBMstToSlv.penable   <= '1' when apb_state = ENABLE else '0';
  APBMstToSlv.pwrite    <= wr;
  APBMstToSlv.paddr     <= address;
  APBMstToSlv.pwdata    <= data_lpc2apb;
  next_data_apb2lpc     <= APBSlvToMst.prdata when apb_state=ENABLE else
                           data_apb2lpc;

  pready                <= APBSlvToMst.pready;

  ----------------------------------------------------------------------
  -- LADOUT Register
  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      LADOUT <= (others => '0');
    elsif rising_edge(LCLK) then
      LADOUT <= next_ladout;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- LADOE Register
  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      LADOE <= '0';
    elsif rising_edge(LCLK) then
      LADOE <= next_ladoe;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- LPC State Machine
  LPC:
  process (lpc_state, LFRAMEn, LADIN, index, wr, SEL, apb_ready)
  begin
    case lpc_state is
    ------------------
    when IDLE =>
      if LFRAMEn='0' and LADIN=START_TARGET then
        next_lpc_state <= CTDIR;
      else
        next_lpc_state <= IDLE;
      end if;
    ------------------
    when CTDIR =>
      if LFRAMEn='1' then
        next_lpc_state <= ADDR;
      elsif LADIN=START_TARGET then
        next_lpc_state <= CTDIR;
      else
        next_lpc_state <= IDLE;
      end if;
    ------------------
    when ADDR =>
      if index="000" then
        if wr='1' then
          next_lpc_state <= DATA0;
        else
          next_lpc_state <= TURN0;
        end if;
      else
        next_lpc_state <= ADDR;
      end if;
    ------------------
    when DATA0 =>
      next_lpc_state <= DATA1;
    ------------------
    when DATA1 =>
      if wr='1' then
        next_lpc_state <= TURN0;
      else
        next_lpc_state <= TURN2;
      end if;
    ------------------
    when TURN0 =>
      if SEL='1' then 
        next_lpc_state <= TURN1;
      else
        next_lpc_state <= IDLE;
      end if;
    ------------------
    when TURN1 =>
      next_lpc_state <= SYNC;
    ------------------
    when SYNC =>
      if apb_ready='1' then
        if wr='1' then
          next_lpc_state <= TURN2;
        else
          next_lpc_state <= DATA0;
        end if;
      else
        next_lpc_state <= SYNC;
      end if;
    ------------------
    when TURN2 =>
      next_lpc_state <= TURN3;
    ------------------
    when TURN3 =>
      next_lpc_state <= IDLE;
    ------------------
    -- when others =>
    --  next_lpc_state <= IDLE;
    end case;
  end process LPC;

  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      lpc_state <= IDLE;
    elsif rising_edge(LCLK) then
      lpc_state <= next_lpc_state;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- Address Index counter
  process (LCLK)
  begin
    if rising_edge(LCLK) then
      if lpc_state=CTDIR then
        if LADIN(2)='1' then
          index <= "111";
        else
          index <= "011";
        end if;
      else
        index <= index-1;
      end if;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- Command Register
  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      cmd <= (others => '0');
    elsif rising_edge(LCLK) then
      cmd <= next_cmd;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- Address Register
  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      address <= (others => '0');
    elsif rising_edge(LCLK) then
      address <= next_address;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- "Data to APB" Register
  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      data_lpc2apb <= (others => '0');
    elsif rising_edge(LCLK) then
      data_lpc2apb <= next_data_lpc2apb;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- APB state machine
  --
  -- Signals between LPC State machine and APB State machine
  -- apb_start      lpc --> apb
  -- wr             lpc --> apb
  -- address        lpc --> apb
  -- data_lpc2apb   lpc --> apb
  -- apb_ready      lpc <-- apb
  -- data_apb2lpc   lpc <-- apb

  APB:
  process (apb_state, apb_start, pready)
  begin
    case apb_state is
    when IDLE =>
      if apb_start = '1' then
        next_apb_state <= SETUP;
      else
        next_apb_state <= IDLE;
      end if;
    when SETUP =>
      next_apb_state <=ENABLE;
    when ENABLE =>
      if pready = '1' then
        next_apb_state <= IDLE;
      else
        next_apb_state <=ENABLE;
      end if;  
    --when others =>
    --  next_apb_state <= IDLE;
    end case;
  end process;

  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      apb_state <= IDLE;
    elsif rising_edge(LCLK) then
      apb_state <= next_apb_state;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- "Data from APB" Register
  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      data_apb2lpc <= (others => '0');
    elsif rising_edge(LCLK) then
      data_apb2lpc <= next_data_apb2lpc;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- "pready from APB" Register
  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      apb_ready <= '0';
    elsif rising_edge(LCLK) then
      apb_ready <= next_apb_ready;
    end if;
  end process;

end architecture ARCH_LPC2APB;
------------------------------------------------------------------------
-- end of file  : lpc2apb_c.vhd

