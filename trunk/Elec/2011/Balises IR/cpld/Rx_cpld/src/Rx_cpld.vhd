-- Auteur: P.P
-- Version: A
-- Date de création: 12/01/11

-- Description: Top level entity du CPLD de la balise Rx
-- la pin mode select permet de choisir deux modes de fonctionnements,
-- lorsque MODE_SELECT = 1: on travaille en mux sur les TSOP
-- lorsque MODE_SELECT = 0: on travaille en UART sur le module XBEE

LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;
	USE IEEE.NUMERIC_STD.ALL;

ENTITY RX_cpld IS
	PORT		(	-- I/O Génériques
					CLK		: IN STD_LOGIC;
					-- TSOPs
					TSOP1		: IN STD_LOGIC_VECTOR (15 DOWNTO 0);
					TSOP2		: IN STD_LOGIC_VECTOR (15 DOWNTO 0);
					-- Xbee
					Xbee_dout	: IN STD_LOGIC;	-- Xbee UART data out
					Xbee_din		: OUT STD_LOGIC;	-- Xbee UART data in
					Xbee_dtr_b	: OUT STD_LOGIC;	-- Xbee pin sleep control line or digital Input 8
					Xbee_cts_b	: IN STD_LOGIC;	-- Xbee clear to send flow control or digital I/O 7
					Xbee_rst_b	: OUT STD_LOGIC;	-- Xbee module reset
					Xbee_sleep_b: IN STD_LOGIC;	-- Xbee Module status indicator or digital I/O 9
					Xbee_rts_b	: OUT STD_LOGIC;	-- Xbee request to send flow control or digital I/O 6
					-- PIC
					PIC_Rx1		: OUT STD_LOGIC;
					PIC_Tx1		: IN STD_LOGIC;
					PIC_Rx2		: OUT STD_LOGIC;
					PIC_Tx2		: IN STD_LOGIC;
					MODE_SELECT	: IN STD_LOGIC; -- mode de fonctionnement (soit gestion des TSOP soit gestion de la RF)
					ADR			: IN STD_LOGIC_VECTOR (4 DOWNTO 0)); -- selection d'adresses pour les TSOP
END ENTITY RX_cpld;


ARCHITECTURE basic_mux_RX_cpld OF RX_cpld IS

BEGIN

END ARCHITECTURE;