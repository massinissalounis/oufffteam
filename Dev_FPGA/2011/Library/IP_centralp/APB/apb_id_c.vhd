-------------------------------------------------------------------------------
-- 
-- Module name:     apb_id_c.vhd
--
-- Description:
--      Composant avec interface APB :
--      Il comporte 2 registres 16 bits
--        - adresse 0 (en lecture seulement)
--            numero de programme FPGA
--            LES 12 BITS DE POIDS FORT REPRESENTENT LE NUMERO DU PROGRAMME
--            LES 4 BITS DE POIDS FAIBLES REPRESENTENT LA REVISION DU PROGRAMME
--            LE PROGRAMME 1061V1A est pris en reference
--            1061V(1)A   => 0100 0010 0101 0000
--            1061V(1)B   => 0100 0010 0101 0001
--            1070V(1)C   => 0100 0010 0101 0010
--            le programme XXXXV2Y n'est pas autorise
--        - adresse 4 (lecture/ecriture)
--            registre 16 bits pour tester l'acces au FPGA.
--
--
-- History:
--
-- Revision 1.0  Auteur : Denis Faveyrial        Date: 30/10/02
--   Creation
-- Revision 1.1  Auteur : Denis Faveyrial        Date: 30/10/02
--   Passage parametres sous forme PROG_NUMBER et REVISION
-- Revision 1.2	

-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author		Comments
--				1.0	30/10/02			Denis Faveyrial	Creation
--				1.1 	30/10/02			Denis Faveyrial	Passage parametres sous forme PROG_NUMBER et REVISION
--				1.2	19/07/2010		C. BEGUET		Modification: asynchronous reset

-------------------------------------------------------------------------------
library IEEE;
  use IEEE.STD_LOGIC_1164.all;
library WORK;
  use WORK.APB.all;

----------------------------- E N T I T Y -------------------------------------
entity APB_ID is
  generic (
    PROG_NUMBER : INTEGER   range 1061 to 9999 := 1139;
    REVISION    : CHARACTER range 'A' to 'O' := 'A');
  port (
    pclk        : in  STD_ULOGIC;
    presetn     : in  STD_ULOGIC;
    APBSlaveIn  : in  APB_SLV_IN_TYPE;
    APBSlaveOut : out APB_SLV_OUT_TYPE);
end APB_ID;

------------------------- A R C H I T E C T U R E -----------------------------
architecture ARCH_APB_ID of APB_ID is

  -----------------------------------------------------------------------------
  -- conversion Integer to Std_logic_vector 
  -----------------------------------------------------------------------------
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

  -----------------------------------------------------------------------------
  -- calcul de ID a partir de PROG_NUMBER et REVISION
  -----------------------------------------------------------------------------
  function ID(
        PROG_NUMBER : in INTEGER;
        REVISION    : in CHARACTER)
    return STD_LOGIC_VECTOR is
    
    variable ident : STD_LOGIC_VECTOR(15 downto 0);
  begin
    ident(15 downto 4):= int_2_slv(PROG_NUMBER, 12);
    ident(3 downto 0):= int_2_slv((CHARACTER'pos(REVISION) - CHARACTER'pos('A')), 4);
    return ident;
  end function ID;            
  
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

  -- definition des registres -------------------------------------------------
  signal id_reg       : STD_LOGIC_VECTOR(15 downto 0);
  signal scratch_reg  : STD_LOGIC_VECTOR(15 downto 0);
  
----------------------DEFINITION DE L'ARCHITECTURE-----------------------------
begin

  APBSlaveOut.PREADY  <= '1'; -- No wait states
  APBSlaveOut.PSLVERR <= '0'; -- No error
  
  -------------------------------------------------------------
  --            Registre ID                                  --
  -------------------------------------------------------------
  id_reg <= ID(PROG_NUMBER, REVISION);
   
  -------------------------------------------------------------
  --            Ecriture du registre de test                 --
  -------------------------------------------------------------

	process (pclk)
	begin
		if (presetn = '0') then
			scratch_reg <= (others => '0');	-- mise a zero du registre au reset
		elsif (pclk'event and pclk='1') then
			if ( psel='1' and paddr(1)='1' and penable='1' and pwrite='1' ) then
			-- ecriture du registre
				if paddr(0) = '0' then
					scratch_reg(7 downto 0) <= pwdata;
				else
					scratch_reg(15 downto 8) <= pwdata;
				end if;
			else 
				scratch_reg <= scratch_reg;
			end if;
		end if;
	end process;


  -------------------------------------------------------------
  --                   Lecture des registres                 --
  -------------------------------------------------------------

  with paddr(1 downto 0) select
    APBSlaveOut.prdata <=  id_reg(7 downto 0)       when "00",
                           id_reg(15 downto 8)      when "01",
                           scratch_reg(7 downto 0)  when "10",
                           scratch_reg(15 downto 8) when others;

end ARCH_APB_ID;
-------------------------------------------------------------------------------
-- end of file

