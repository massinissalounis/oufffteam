------------------------------------------------------------------------
--
-- Project:         LPC Bus Functionnal Model
--
--
-- Module name:     lpc_bfm.vhd
--
-- Description:
--
-- History:
--     Project created  25/02/2009    d. faveyrial
--
------------------------------------------------------------------------

library IEEE;
  use IEEE.STD_LOGIC_1164.all;
  use IEEE.STD_LOGIC_ARITH.all;
  use IEEE.STD_LOGIC_UNSIGNED.all;
  use WORK.LPC.all;

---------------------------------- E N T I T Y -------------------------
entity LPC_BFM is
  port (
    LCLK       : in    std_logic;
    LRSTn      : in    std_logic;
    LFRAMEn    : out   std_logic;
    LAD        : inout nibble
  );
end entity LPC_BFM;


----------------------------- A R C H I T E C T U R E ------------------
architecture ARCH_LPC_BFM of LPC_BFM is

	constant Test_LPC_ID	: std_logic := '1';	-- Test de l'ID APB
	constant Test_LPC_autre : std_logic := '0'; -- Test hote LPC non présent
	constant Test_LPC_UART	: std_logic := '1';	-- Test du bus LPC et de l'UART
	constant TEST_FWH	: std_logic := '0';	-- Test du bus LPC en mode FWH
	constant Msg_debug_LPC_n : boolean := false;	-- Affiche les messages de debug du LPC (false pour afficher, true pour ne pas afficher)
    constant delay_clk_to_data : time := 2 ns;  -- Temps entre le front de l'horloge et la validité des données. Varie de 2 à 11 ns
	constant TEST_WD	: std_logic := '0';	-- Test du WD
	
	signal read_data, UART_status : byte;
  ----------------------------------------------------------------------
  -- procedure and function declarations
  ----------------------------------------------------------------------
  ----------------------------------------------------------------------
  -- lpc init                                                         --
  ----------------------------------------------------------------------
  procedure lpc_init( signal rst_n   : in    std_logic;
                      signal frame_n : out   std_logic;
                      signal ad      : inout nibble)       is

  begin
    wait until rst_n = '0';
    frame_n <= '1';
    ad      <= "1111";
    wait until rising_edge(rst_n);

  end procedure lpc_init;

  ----------------------------------------------------------------------
  -- lpc access                                                       --
  ----------------------------------------------------------------------
  procedure lpc_access(        ctdir   : in    nibble;
                               address : in    dword;
                               wdata   : in    byte;
                               rdata   : out   byte;
                        signal clk     : in    std_logic;
                        signal frame_n : out   std_logic;
                        signal ad      : inout nibble)    
	is

  variable i, l    : integer;

  begin
	assert Msg_debug_LPC_n report ("--- LPC: Transaction start ---") severity note;
    -- Mem or I/O Start Cycle
    wait until rising_edge(clk);
    wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
    frame_n <= '0';
    ad      <= "0000";

    -- Ctdir Cycle
    wait until rising_edge(clk);
    wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
	assert Msg_debug_LPC_n report ("--- LPC: CT/dir ---") severity note;
    frame_n <= '1';
    ad      <= ctdir;

    -- Address Cycles
    if ctdir(3 downto 2) = MEM_CYCLE then
      l := 7; -- memory address  : 32 bits
    else
      l := 3; -- i/o address     : 16 bits
    end if;
	
	for i in l downto 0 loop
      wait until rising_edge(clk);
      wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
	  assert Msg_debug_LPC_n report ("--- LPC: Adresse ---") severity note;
      ad <= address( 4*i+3 downto 4*i );
    end loop;

    if ctdir(1) = WRITE_CYCLE then
      -- Write transaction
      for i in 0 to 1 loop
        wait until rising_edge(clk);
        wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
		assert Msg_debug_LPC_n report ("--- LPC: Write data ---") severity note;
        ad <= wdata( 4*i+3 downto 4*i );
      end loop;
    end if;

    -- 2 Tournaround Cycles
    wait until rising_edge(clk);
    wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
	assert Msg_debug_LPC_n report ("--- LPC: turn 0 ---") severity note;
    ad <= "1111";
    wait until rising_edge(clk);
    wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
	assert Msg_debug_LPC_n report ("--- LPC: turn 1 ---") severity note;
    ad <= "ZZZZ";
    wait until rising_edge(clk);

    -- Sync Cycles
	assert Msg_debug_LPC_n report ("--- LPC: sync ---") severity note;
    wait until rising_edge(clk);
    case ad is
		when SWAIT  =>
	        i := 0;
	        swaitLoop : loop
	          wait until rising_edge(clk);
	          exit swaitLoop when ad/=SWAIT or i=5;--TIMEOUT;
	          i := i+1;
	        end loop swaitLoop;
			assert Msg_debug_LPC_n report ("--- LPC: sync fin short wait ---") severity note;
		when LWAIT  =>
	        lwaitLoop : loop
	          wait until rising_edge(clk);
	          exit lwaitLoop when ad/=LWAIT;
	        end loop lwaitLoop;
			assert Msg_debug_LPC_n report ("--- LPC: sync fin long wait ---") severity note;
		when READY =>
			assert Msg_debug_LPC_n report ("--- LPC: sync - pas de wait ---") severity note;
		when others =>	-- No SYNCH answer
			assert false report ("--- LPC: Error or no answer --> Transaction aboard ---") severity warning;
			-- Wait 3 clock cycles before aboard transaction (normaly SYNCH signal can arrive before the 3 clocks and transaction in not aboarded) 
			wait until rising_edge(clk);
			wait until rising_edge(clk);
			wait until rising_edge(clk);
			-- End of transaction on error, Aboard machanism Assert Frame_n  and LAD for 4 clocks
			frame_n <= '0';
			ad <= "1111";
			wait until rising_edge(clk);
			wait until rising_edge(clk);
			wait until rising_edge(clk);
			wait until rising_edge(clk);
			-- Release bus
			frame_n <= '1';
			ad <= "ZZZZ";
			wait until rising_edge(clk);
    end case;
	if (ad = READY) then
		if ctdir(1) = READ_CYCLE then
			-- Read Data if read transaction
			rdata := (others => '0');
			for i in 0 to 1 loop
			  wait until rising_edge(clk);
			  assert Msg_debug_LPC_n report ("--- LPC: read data ---") severity note;
			  rdata( 4*i+3 downto 4*i ) := ad;
			end loop;
		end if;
		-- no error, 2 Tournaround Cycles
		assert Msg_debug_LPC_n report ("--- LPC: turn 2 ---") severity note;
		wait until rising_edge(clk);
		assert Msg_debug_LPC_n report ("--- LPC: turn 3 ---") severity note;
		-- drive "1111" on second Turnaround cycle
		ad <= "1111";
		wait until rising_edge(clk);
	end if;
	assert Msg_debug_LPC_n report ("--- LPC: End of transaction ---") severity note;
  end procedure lpc_access;

  ----------------------------------------------------------------------
  -- fwh access                                                       --
  ----------------------------------------------------------------------
  procedure fwh_access(        start   : in    nibble;
                               address : in    dword;
                               wdata   : in    byte;
                               rdata   : out   byte;
                        signal clk     : in    std_logic;
                        signal frame_n : out   std_logic;
                        signal ad      : inout nibble)    
	is

  variable i, l    : integer;

  begin
	assert Msg_debug_LPC_n report ("--- LPC: Transaction start ---") severity note;
    -- firmware start Cycle: while frame_n = '0' the value should not be sampled because "ad" can change
     frame_n <= '0';
     ad      <= start;
    wait until rising_edge(clk);
    wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
     frame_n <= '0';
     ad      <= "0100";
    wait until rising_edge(clk);
    wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset


     frame_n <= '0';
     ad      <= start;
	assert Msg_debug_LPC_n report ("--- LPC: Start ---") severity note;
    -- start Cycle
    wait until rising_edge(clk);
    wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
    frame_n <= '1';
    ad      <= "0000"; -- we consider there is only one device which number is "0000"
	assert Msg_debug_LPC_n report ("--- LPC: IDSEL ---") severity note;


    -- Address Cycles
      l := 6; -- memory address  : 28 bits
	
	for i in l downto 0 loop
      wait until rising_edge(clk);
      wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
	  assert Msg_debug_LPC_n report ("--- LPC: Adresse ---") severity note;
      ad <= address( 4*i+3 downto 4*i );
    end loop;

    -- Msize cycle
    wait until rising_edge(clk);
    wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
    ad      <= "0000";

    if start = FIRMW_WRITE then
      -- Write transaction
      for i in 0 to 1 loop
        wait until rising_edge(clk);
        wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
		assert Msg_debug_LPC_n report ("--- LPC: Write data ---") severity note;
        ad <= wdata( 4*i+3 downto 4*i );
      end loop;
    end if;

    -- 2 Tournaround Cycles
    wait until rising_edge(clk);
    wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
    assert Msg_debug_LPC_n report ("--- LPC: turn 0 ---") severity note;
    ad <= "ZZZZ";
    wait until rising_edge(clk);
    wait for delay_clk_to_data;  -- Min Delay between clock and valid data from chipset
    assert Msg_debug_LPC_n report ("--- LPC: turn 1 ---") severity note;
    ad <= "ZZZZ";
    wait until rising_edge(clk);

    -- Sync Cycles
    wait until rising_edge(clk);

	assert Msg_debug_LPC_n report ("--- LPC: sync ---") severity note;
    case ad is
		when SWAIT  =>
	        i := 0;
	        swaitLoop : loop
	          wait until rising_edge(clk);
	          exit swaitLoop when ad/=SWAIT or i=5;--TIMEOUT;
	          i := i+1;
	        end loop swaitLoop;
			assert Msg_debug_LPC_n report ("--- LPC: sync fin short wait ---") severity note;
		when LWAIT  =>
	        lwaitLoop : loop
	          wait until rising_edge(clk);
	          exit lwaitLoop when ad/=LWAIT;
	        end loop lwaitLoop;
			assert Msg_debug_LPC_n report ("--- LPC: sync fin long wait ---") severity note;
		when READY =>
			assert Msg_debug_LPC_n report ("--- LPC: sync - pas de wait ---") severity note;
		when others =>	-- No SYNCH answer
			assert false report ("--- LPC: Error or no answer --> Transaction aboard ---") severity warning;
			-- Wait 3 clock cycles before aboard transaction (normaly SYNCH signal can arrive before the 3 clocks and transaction in not aboarded) 
			wait until rising_edge(clk);
			wait until rising_edge(clk);
			wait until rising_edge(clk);
			-- End of transaction on error, Aboard machanism Assert Frame_n  and LAD for 4 clocks
			frame_n <= '0';
			ad <= "1111";
			wait until rising_edge(clk);
			wait until rising_edge(clk);
			wait until rising_edge(clk);
			wait until rising_edge(clk);
			-- Release bus
			frame_n <= '1';
			ad <= "ZZZZ";
			wait until rising_edge(clk);
    end case;
	if (ad = READY) then
		if start(1) = READ_CYCLE then
			-- Read Data if read transaction
			rdata := (others => '0');
			for i in 1 downto 0 loop
			  wait until rising_edge(clk);
			  assert Msg_debug_LPC_n report ("--- LPC: read data ---") severity note;
			  rdata( 4*i+3 downto 4*i ) := ad;
			end loop;
		end if;
		-- no error, 2 Tournaround Cycles
		assert Msg_debug_LPC_n report ("--- LPC: turn 2 ---") severity note;
		wait until rising_edge(clk);
		assert Msg_debug_LPC_n report ("--- LPC: turn 3 ---") severity note;
		-- drive "1111" on second Turnaround cycle
		ad <= "ZZZZ";
		wait until rising_edge(clk);
	end if;
	assert Msg_debug_LPC_n report ("--- LPC: End of transaction ---") severity note;
  end procedure fwh_access;


  ----------------------------------------------------------------------
  -- memory write                                                     --
  ----------------------------------------------------------------------
  procedure lpc_mem_write(        address : in    dword;
                                  data    : in    byte;
                           signal clk     : in    std_logic;
                           signal frame_n : out   std_logic;
                           signal ad      : inout nibble)      is

  variable dummy : byte;

  begin
    lpc_access( MEM_CYCLE & WRITE_CYCLE & '0',
                address, data, dummy, clk, frame_n, ad);
  end procedure lpc_mem_write;

  ----------------------------------------------------------------------
  -- memory read                                                      --
  ----------------------------------------------------------------------
  procedure lpc_mem_read(        address : in    dword;
                                 data    : out   byte;
                          signal clk     : in    std_logic;
                          signal frame_n : out   std_logic;
                          signal ad      : inout nibble)      is

  begin
    lpc_access( MEM_CYCLE & READ_CYCLE & '0',
                address, (others => '0'), data, clk, frame_n, ad);
  end procedure lpc_mem_read;

  ----------------------------------------------------------------------
  -- i/o write                                                        --
  ----------------------------------------------------------------------
  procedure lpc_io_write(         address : in    word;
                                  data    : in    byte;
                           signal clk     : in    std_logic;
                           signal frame_n : out   std_logic;
                           signal ad      : inout nibble)      is

  variable dummy : byte;

  begin
    lpc_access( IO_CYCLE & WRITE_CYCLE & '0',
                X"0000" & address, data, dummy, clk, frame_n, ad);
  end procedure lpc_io_write;

  ----------------------------------------------------------------------
  -- i/o read                                                         --
  ----------------------------------------------------------------------
  procedure lpc_io_read(         address : in    word;
                                 data    : out   byte;
                          signal clk     : in    std_logic;
                          signal frame_n : out   std_logic;
                          signal ad      : inout nibble)      is

  begin
    lpc_access( IO_CYCLE & READ_CYCLE & '0', X"0000" & address,
                (others => '0'), data, clk, frame_n, ad);
  end procedure lpc_io_read;

  ----------------------------------------------------------------------
  -- FWH read                                                         --
  ----------------------------------------------------------------------
  procedure lpc_fwh_read(         address : in    dword;
                                 data    : out   byte;
                          signal clk     : in    std_logic;
                          signal frame_n : out   std_logic;
                          signal ad      : inout nibble)      is

  begin
    fwh_access( FIRMW_READ, address,
                (others => '0'), data, clk, frame_n, ad);
  end procedure lpc_fwh_read;

  ----------------------------------------------------------------------
  -- FWH write                                                    --
  ----------------------------------------------------------------------
  procedure lpc_fwh_write(         address : in    dword;
                                  data    : in    byte;
                           signal clk     : in    std_logic;
                           signal frame_n : out   std_logic;
                           signal ad      : inout nibble)      is

  variable dummy : byte;

  begin
    fwh_access( FIRMW_WRITE, address, data, dummy, clk, frame_n, ad);
  end procedure lpc_fwh_write;

  ----------------------------------------------------------------------
  -- Procedure implements a temporisation                             --
  ----------------------------------------------------------------------
  procedure tempo(value : TIME) is
  begin
    wait for value;
  end tempo;

  ----------------------------------------------------------------------
  -- Procedure implements instruction ABRT                            --
  ----------------------------------------------------------------------
  procedure abrt is
  begin
    assert ( 1=0 )
      report "######## END OF TEST ##########"
      severity FAILURE;
  end abrt;
  
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
  process

	variable rdata 			: byte;

  --//////////////////////////////////////////////////////////////////--
  --//////////////////////////////////////////////////////////////////--
  begin
	
    lpc_init(LRSTn, LFRAMEn, LAD);
	read_data <= (others => '0');
    assert false report ("Initialisation Simulo OK") severity note;

    --test FWH
    if (TEST_FWH = '1') then
		assert false report ("Test LPC en mode FWH") severity note;

        lpc_fwh_read(X"2FEFFBA9", rdata, LCLK, LFRAMEn, LAD); 
        wait for 3 us;
        lpc_fwh_write(X"2FEDCBA9", X"50", LCLK, LFRAMEn, LAD); 
        wait for 3 us;
        lpc_fwh_write(X"2FEDCBA9", X"06", LCLK, LFRAMEn, LAD); 
        wait for 3 us;
        lpc_fwh_write(X"2FEDCBA9", X"04", LCLK, LFRAMEn, LAD); 
        wait for 3 us;

        lpc_fwh_write(X"2FEDCBA9", X"01", LCLK, LFRAMEn, LAD); 
        wait for 3 us;

        lpc_fwh_write(X"2FEDCBA9", X"AA", LCLK, LFRAMEn, LAD); 
        wait for 1 us;
        lpc_fwh_read(X"2FEDCBA9", rdata, LCLK, LFRAMEn, LAD); 
    end if;

	
	if (Test_LPC_ID = '1') then
        wait for 6 us;
		assert false report ("Test lecture ID") severity note;
		lpc_io_read(X"0010", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur ID
		read_data <= rdata;	-- pour visualisation
        wait for 3 us;
		lpc_io_read(X"0011", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur ID
		read_data <= rdata;	-- pour visualisation
        wait for 3 us;
		lpc_io_write(X"0012", X"34", LCLK, LFRAMEn, LAD);		-- Ecriture sur ID registre de test
        wait for 3 us;
		lpc_io_write(X"0013", X"12", LCLK, LFRAMEn, LAD);		-- Ecriture sur ID registre de test
        wait for 3 us;
		
		lpc_io_read(X"0012", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur ID registre de test
		read_data <= rdata;	-- pour visualisation
		assert (rdata = X"34") report ("ERREUR TEST ID: echec écriture - lecture registre 0") severity error;
		lpc_io_read(X"0013", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur ID registre de test
		read_data <= rdata;	-- pour visualisation
		assert (rdata = X"12") report ("ERREUR TEST ID: echec écriture - lecture registre 1") severity error;
	end if;
	
	if (Test_LPC_autre = '1') then
		assert false report ("Test ecriture LPC non mappe") severity note;
		lpc_io_write(X"0FF8", X"AB", LCLK, LFRAMEn, LAD);		-- Ecriture sur RIEN (adresse non mappée)
	end if;	
	
	if (Test_LPC_UART = '1') then
		wait for 10 us;
		assert false report ("Test UART") severity note;
        UART_status <= (others => '0');
		-- Initialisation de l'UART
        -- lpc_io_write(X"03FB", b"10000011", LCLK, LFRAMEn, LAD); -- Registre LCR
		-- lpc_io_write(X"03F8", X"00", LCLK, LFRAMEn, LAD);		-- Registre DLL car LCR(7) = 1
		-- lpc_io_write(X"03F9", X"01", LCLK, LFRAMEn, LAD);		-- Registre DLM car LCR(7) = 1
		-- lpc_io_write(X"03FB", b"00000011", LCLK, LFRAMEn, LAD);	-- Registre LCR => remise à 0 de LCR(7)
		-- lpc_io_write(X"03F9", b"00000001", LCLK, LFRAMEn, LAD);	-- Registre IER => activation de l'interruption en reception
		-- lpc_io_write(X"03FA", b"00000110", LCLK, LFRAMEn, LAD);	-- Registre FRC => Reset des FIFO
		-- lpc_io_write(X"03FA", b"00000000", LCLK, LFRAMEn, LAD);	-- Registre FRC => retour normal
        --

        --Test de ce qu'envoi l'UART
		lpc_io_write(X"03FB", X"80", LCLK, LFRAMEn, LAD);       -- Registre LCR
		lpc_io_write(X"03F8", X"01", LCLK, LFRAMEn, LAD);		-- Registre DLL car LCR(7) = 1
		lpc_io_write(X"03F9", X"00", LCLK, LFRAMEn, LAD);		-- Registre DLM car LCR(7) = 1
		lpc_io_write(X"03FB", X"03", LCLK, LFRAMEn, LAD);	    -- Registre LCR => remise à 0 de LCR(7)
        lpc_io_write(X"03FC", X"03", LCLK, LFRAMEn, LAD);       -- Registre MCR = 03h
        	

        --lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        --read_data <= rdata;	-- pour visualisation
        --lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        --read_data <= rdata;	-- pour visualisation
        --lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        --read_data <= rdata;	-- pour visualisation

       -- lpc_io_write(X"03F9", X"01", LCLK, LFRAMEn, LAD);       -- Registre IER = 01h validation de l'interuption
        lpc_io_write(X"03F8", X"41", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        lpc_io_write(X"03F8", X"52", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        lpc_io_write(X"03F8", X"1B", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
		
		--lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART

        WAIT FOR 400 us;
        
		while UART_status(0) = '0' loop
			lpc_io_read (X"03FD", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
			UART_status <= rdata;	-- pour visualisation	 
			WAIT FOR 10 ns;
		end loop;
		lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        read_data <= rdata;	-- pour visualisation

		UART_status <= (others => '0');
		WAIT FOR 10 ps;
		while UART_status(0) = '0' loop
			lpc_io_read (X"03FD", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
			UART_status <= rdata;	-- pour visualisation	 
			WAIT FOR 10 ns;
		end loop;
        lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        read_data <= rdata;	-- pour visualisation

		UART_status <= (others => '0');
		WAIT FOR 10 ps;
		while UART_status(0) = '0' loop
			lpc_io_read (X"03FD", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
			UART_status <= rdata;	-- pour visualisation	 
			WAIT FOR 10 ns;
		end loop;
        lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        read_data <= rdata;	-- pour visualisation
        -- WAIT FOR 400 us;

        -- lpc_io_write(X"03F8", X"01", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"02", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"03", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"04", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"05", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"06", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"07", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"08", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"09", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"10", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"11", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"12", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"13", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"14", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"15", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"16", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"17", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"18", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"19", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"20", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"21", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"22", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"23", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
        -- lpc_io_write(X"03F8", X"24", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART

        -- WAIT FOR 400 us;
		
		-- lpc_io_read (X"03FD", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
		-- while read_data(0) = '0' loop
			-- lpc_io_read (X"03FD", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
			-- read_data <= rdata;	-- pour visualisation
		-- end loop;
		
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- lpc_io_read (X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- WAIT FOR 400 us;

       
		-- lpc_io_read (X"03FD", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- wait for 2 us;
		-- lpc_io_read (X"03FD", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- wait for 2 us;
		-- lpc_io_read (X"03FD", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
        -- read_data <= rdata;	-- pour visualisation
        -- wait for 2 us;

		-- lpc_io_write(X"03F8", X"AB", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
		-- lpc_io_write(X"03F8", X"FF", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
		-- lpc_io_write(X"03F8", X"00", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
		-- lpc_io_write(X"03F8", X"55", LCLK, LFRAMEn, LAD);		-- Ecriture sur UART
		
		-- wait for 5 ms;
		-- assert false report ("Test lecture UART") severity note;
		-- lpc_io_read(X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
		-- read_data <= rdata;	-- pour visualisation
		-- wait for 5 ms;
		-- assert false report ("Test lecture UART") severity note;
		-- lpc_io_read(X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
		-- read_data <= rdata;	-- pour visualisation
		-- wait for 5 ms;
		-- assert false report ("Test lecture UART") severity note;
		-- lpc_io_read(X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
		-- read_data <= rdata;	-- pour visualisation
		-- wait for 5 ms;
		-- assert false report ("Test lecture UART") severity note;
		-- lpc_io_read(X"03F8", rdata, LCLK, LFRAMEn, LAD);		-- Lecture sur UART
		-- read_data <= rdata;	-- pour visualisation

	end if;


    if (TEST_WD = '1') then
        -- TEST WATCHDOG
        --ecriture dans WD_REG
        lpc_io_write(X"0C02", X"10", LCLK, LFRAMEn, LAD);
        lpc_io_write(X"0C03", X"00", LCLK, LFRAMEn, LAD);
        wait for 1000 ns;
        --lecture pour verifier que l'ecriture a fonctionnée
        lpc_io_read(X"0C02", rdata, LCLK, LFRAMEn, LAD);
        read_data <= rdata;	-- pour visualisation
        lpc_io_read(X"0C03", rdata, LCLK, LFRAMEn, LAD);
        read_data <= rdata;	-- pour visualisation
        wait for 1000 ns;
        --ecriture dans WD_REG et vérifier que l'on ne peut pas ecrire une valeur supérieure à celle deja en place
        lpc_io_write(X"0C02", X"95", LCLK, LFRAMEn, LAD);
        lpc_io_write(X"0C03", X"DC", LCLK, LFRAMEn, LAD);
        wait for 1000 ns;
        --ecriture dans WD_REG et vérifier que l'on peut ecrire une valeur inferieure à celle deja en place
        lpc_io_write(X"0C02", X"08", LCLK, LFRAMEn, LAD);
        lpc_io_write(X"0C03", X"00", LCLK, LFRAMEn, LAD);
        wait for 1000 ns;

        --Ecriture pour faire un refresh du watchdog
        lpc_io_write(X"0C00", X"55", LCLK, LFRAMEn, LAD);
        lpc_io_write(X"0C01", X"AA", LCLK, LFRAMEn, LAD);
        --Ecriture dans le registre WD_REG pour voir si pb de syncro entre le refresh et l'ecriture du registre
        lpc_io_write(X"0C02", X"01", LCLK, LFRAMEn, LAD);
        wait for 1000 ns;
    end if;



  end process;
  --//////////////////////////////////////////////////////////////////--
  --//////////////////////////////////////////////////////////////////--

end architecture ARCH_LPC_BFM;
------------------------------------------------------------------------
-- end of file  : lpc_bfm.vhd





