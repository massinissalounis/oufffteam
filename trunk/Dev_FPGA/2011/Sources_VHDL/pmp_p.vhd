-- Oufffteam
-- Projet carte mère
-- Device: pmp

-- 01/02/2010			CBE			Création


library ieee;
use ieee.std_logic_1164.all;

package PMP_P is
 
	constant PMP_DMAX  : positive range 8 to 32 := 8;      -- data width
	constant PMP_AMAX  : positive range 8 to 32 := 16;     -- address width
 
	-- PMP slave inputs (PCLK and PRESETn routed separately)
	type PMP_SLV_IN_TYPE is
		record
		PMP_SEL		: std_logic;                         	-- slave select
		PMP_PMRD	: std_logic;                         	-- read
		PMP_PMWR 	: std_logic;                         	-- write
		PMP_ADDR	: std_logic_vector(PMP_AMAX-1 downto 0);	-- address bus
		PMP_WDATA	: std_logic_vector(PMP_DMAX-1 downto 0);	-- write data bus
		end record;

	-- PMP slave outputs
	type PMP_SLV_OUT_TYPE is
		record
		PMP_RDATA  : std_logic_vector(PMP_DMAX-1 downto 0); -- read data bus
		end record;
  
	-- supporting array types
	type PMP_SLV_IN_VECTOR  is array (natural range <> ) of PMP_SLV_IN_TYPE;
	type PMP_SLV_OUT_VECTOR is array (natural range <> ) of PMP_SLV_OUT_TYPE;

	
	component PMP_interface is
		generic ( slave_number : natural := 2);
		port (
			clock		: in std_logic;
			reset		: in std_logic;
			-- PMP
			PMP_PMALH	: in std_logic;
			PMP_PMALL	: in std_logic;
			PMP_PMCS	: in std_logic;
			PMP_PMD		: inout std_logic_vector (7 downto 0);
			PMP_PMRD	: in std_logic;
			PMP_PMWR	: in std_logic;

			CS_input	: in std_logic_vector (slave_number - 1 downto 0);
			Address		: out std_logic_vector (15 downto 0);
			--internal PMP
			From_slave	: in PMP_SLV_OUT_VECTOR (slave_number - 1 downto 0);
			To_slave	: out PMP_SLV_IN_VECTOR (slave_number - 1 downto 0)		
		);
	end component PMP_interface;
  
  
end pmp_p;
-------------------------------------------------------------------------------
-- end of file

