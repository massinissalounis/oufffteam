------------------------------------------------------------------------
--
-- Project:         LPC 
--
--
-- Module name:     lpc_analyser_c.vhd
--
-- Description:
--
-- History:
--     Project created  2009/03/06    d. faveyrial
--
------------------------------------------------------------------------

library IEEE;
  use IEEE.STD_LOGIC_1164.all;
  use IEEE.STD_LOGIC_ARITH.all;
  use IEEE.STD_LOGIC_UNSIGNED.all;
  use IEEE.STD_LOGIC_TEXTIO.all;
library STD;
  use STD.TEXTIO.all;
library WORK;
  use WORK.LPC.all;

---------------------------------- E N T I T Y -------------------------
entity LPC_ANALYSER is
  port (
    LCLK        : in  std_logic;
    LRSTn       : in  std_logic;
    LFRAMEn     : in  std_logic;
    LADIN       : in  std_logic_vector( 3 downto 0 )
  );
end entity LPC_ANALYSER;


----------------------------- A R C H I T E C T U R E ------------------
architecture ARCH_LPC_ANALYSER of LPC_ANALYSER is

  ----------------------------------------------------------------------
  -- type declarations
  ----------------------------------------------------------------------
  type LPC_STATE_TYPE is (IDLE,
                          CTDIR,
                          ADDR,
                          DATA0, DATA1,
                          TURN0, TURN1,
                          SYNC,
                          TURN2, TURN3,
                          ERRO);

  ----------------------------------------------------------------------
  -- constant declarations
  ----------------------------------------------------------------------
  constant TIMEOUT  : std_logic_vector(3 downto 0) := "0001";
  constant SYNC_ERR : std_logic_vector(3 downto 0) := "0010";
  
  ----------------------------------------------------------------------
  -- signal declarations
  ----------------------------------------------------------------------
  -- signals for lpc state machine
  signal lpc_state          : LPC_STATE_TYPE;
  signal next_lpc_state     : LPC_STATE_TYPE;
  --
  signal index              : std_logic_vector(2 downto 0);
  signal cmd                : std_logic_vector(3 downto 0);
  signal next_cmd           : std_logic_vector(3 downto 0);
  signal wr                 : std_logic;
  signal io                 : std_logic;
  signal mem                : std_logic;
  signal address            : std_logic_vector(31 downto 0);
  signal next_address       : std_logic_vector(31 downto 0);
  signal data               : std_logic_vector(7 downto 0);
  signal next_data          : std_logic_vector(7 downto 0);
  signal timeout_counter    : std_logic_vector(2 downto 0);
  signal err                : std_logic_vector(3 downto 0);
  signal next_err           : std_logic_vector(3 downto 0);
  
  signal log_start          : std_logic;
  signal log_access         : std_logic;
  file   log_file           : text open WRITE_MODE is "log.out";


  ----------------------------------------------------------------------
  -- procedure and function declarations
  ----------------------------------------------------------------------

------------------------------------------------------------------------
-- ARCHITECTURE DEFINITION
------------------------------------------------------------------------
begin
  -- 
  next_cmd <= LADIN when lpc_state=CTDIR           else cmd;
  wr       <= '1'   when cmd(1)=WRITE_CYCLE        else '0';
  io       <= '1'   when cmd(3 downto 2)=IO_CYCLE  else '0';
  mem      <= '1'   when cmd(3 downto 2)=MEM_CYCLE else '0';

  next_address <= address(27 downto 0) & LADIN when lpc_state=ADDR else
                  (others=>'0')                when lpc_state=CTDIR else 
                  next_address;

  next_data <= 
   data(3 downto 0) & LADIN when lpc_state=DATA1 or lpc_state=DATA0 else 
   (others=>'0')            when lpc_state=CTDIR else 
   next_data;
  
  next_err <=  (others => '0') when lpc_state=IDLE else
               err or TIMEOUT  when lpc_state=SYNC and LADIN=SWAIT and
                                    timeout_counter="000" else
               err or SYNC_ERR when lpc_state=SYNC and (LADIN/=READY and  
                                           LADIN/=SWAIT and LADIN/=LWAIT) else
               err;

  log_start  <= '1' when lpc_state=CTDIR and LFRAMEn='1' else '0';
  
  log_access <= '1' when lpc_state=TURN3 or 
                         (lpc_state=ERRO and LADIN=STOP_ABORT) else
                '0';
  ----------------------------------------------------------------------
  -- LPC State Machine
  LPC:
  process (lpc_state, LFRAMEn, LADIN, index, wr)
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
      elsif  LADIN=START_TARGET then
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
      next_lpc_state <= TURN1;
    ------------------
    when TURN1 =>
      next_lpc_state <= SYNC;
    ------------------
    when SYNC =>
      if LADIN = READY then
        if wr='1' then
          next_lpc_state <= TURN2;
        else
          next_lpc_state <= DATA0;
        end if;
      else
        if LFRAMEn='0' then
          next_lpc_state <= ERRO;
        else
          next_lpc_state <= SYNC;
        end if;
      end if;
      ------------------
    when TURN2 =>
      next_lpc_state <= TURN3;
    ------------------
    when TURN3 =>
      next_lpc_state <= IDLE;
    ------------------
    when ERRO =>
      if LADIN=STOP_ABORT then
        next_lpc_state <= IDLE;
      else
        next_lpc_state <= ERRO;
      end if;
    ------------------
    when others =>
      next_lpc_state <= IDLE;
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
  -- Data Register
  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      data <= (others => '0');
    elsif rising_edge(LCLK) then
      data <= next_data;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- Timeout Counter
  process (LCLK, lpc_state)
  begin
    if rising_edge(LCLK) then
      if lpc_state=TURN1 then
        timeout_counter  <= "100";
      else
        timeout_counter <= timeout_counter-1;
      end if;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- Error Register
  process (LCLK, LRSTn)
  begin
    if LRSTn='0' then
      err <= (others => '0');
    elsif rising_edge(LCLK) then
      err <= next_err;
    end if;
  end process;

  ----------------------------------------------------------------------
  -- LOG process
  LPC_LOG:
  process (LCLK)
  
    variable start : time;
    
    procedure log_s   is
    begin
      start := now;
    end procedure log_s ;

    procedure log_a  is
    variable l           : line;
    variable access_time : time;
    begin
      if mem='1' then 
        write(l, string'("mem"));
      else
        write(l, string'("i/o"));
      end if;
      if wr='1' then
        write(l, string'(" write"));
      else
        write(l, string'(" read "));
      end if;
      write(l, string'(", address = "));
      --hwrite(l, address);
      write(l, string'(",  data= "));
      hwrite(l, data);
      write(l, string'(", duration : "));
      access_time := now-start;
      write(l, access_time);
      if err /= "0000" then
        write(l, string'(", error :"));
        hwrite(l, err);
      end if;
      writeline(log_file, l);
    end procedure log_a ;

  begin
    if rising_edge(LCLK) then
      if log_start = '1' then
      	log_s;
	      end if;
      if log_access = '1' then
	      log_a;
      end if;
    end if;
  end process LPC_LOG;

end architecture ARCH_LPC_ANALYSER;
------------------------------------------------------------------------
-- end of file  : lpc_analyser_c.vhd





