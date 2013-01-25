--------------------------------------------------------------------------------------------------------
-- Project :		CPLD ESCORT A8
--
-- File:			GPMC_to_APB_p.vhd
--
-- Author:			C. BEGUET
--
-- Board:			k191015
--
-- Device:			Lattice - MacXO - LCMXO2280C-4FT256I
-- Part number:		D2
--
-- Dependencies:	
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author			Comments
--						0.1		17/10/2011			C. BEGUET		Creation
--				
--
--------------------------------------------------------------------------------------------------------
-- Purpose: Interface beetwin a GPMC bus from TI ARM AM35xx and APB bus.
--		*	synchronisation of all the GPMC inputs
--		*	address and data bus width customaizable on GPMC and APB
--------------------------------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

library work;
use work.apb.all;

package GPMC2APB_p is
 	
	component GPMC2APB is
		generic (
			GPMC_ad_width		: integer := 16;	-- Number of wire on Address/data multiplexed bus
			GPMC_data_width 	: integer := 16;	-- Number of bits used for data(must be less or equal to GPMC_ad_width and equal to APB data bus width)
			GPMC_add_width		: integer := 16;	-- Number of bits used for address(must be less or equal to GPMC_ad_width and equal to APB address bus width)
			APB_number_of_slaves: natural := 2
			);
		port (
			-- Global signals
			main_clock	: in  std_logic;
			reset		: in std_logic;
			-- GPMC interface
			GPMC_AD		: inout  std_logic_vector (GPMC_ad_width-1 downto 0);
			GPMC_ADV_n	: in std_logic;
			GPMC_OE_n	: in std_logic;
			GPMC_WE_n	: in std_logic;
			GPMC_CS_n	: in std_logic;
			GPMC_WAIT	: out std_logic;
			-- APB interface
			APBSlvToMst : in  APB_SLV_OUT_TYPE;
			APBMstToSlv : out APB_SLV_IN_TYPE;
			-- DECODE interface
			address_out	: out std_logic_vector (GPMC_ad_width-1 downto 0)
		);
	end component GPMC2APB;

  
  
end GPMC2APB_p;
-------------------------------------------------------------------------------
-- end of file

