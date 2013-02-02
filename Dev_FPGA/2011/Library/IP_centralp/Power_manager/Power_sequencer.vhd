--**************************************************************************************************************************
--Project                      : GENERIC IP
--
--File                            : Power_sequencer.vhd
--
--Author                       : C. BEGUET  23/02/09                                                                                   Copyight Centralp, 2009
--
--Board                         : GENERIC IP
--Device                       : GENERIC IP
--Part refence             :
--Program Number      :
--
-- Dependencies:		gh_DFF.vhd
--
--Revision History        Date          Author                          Comments
--
--**************************************************************************************************************************
--Purpose: 
-- Séquenceur d'alimentation generique
-- Ordonne les alimentations de 1 à Nb_Voltages, 1 étant l'alimentation à mettre sous tension en 1er
-- TOP Level du séquenceur: instantiation automatique des voltage_manager en fonction du nombre de tensions à séquencer
--
--**************************************************************************************************************************

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;


entity power_sequencer is
	generic ( Nb_Voltages : natural := 3 ); --Nombre de tensions à séquancer, de 1 à Nb_Voltages, 1 étant mise sous tension en 1er
	port (	-- interface de controle
			reset :				in std_logic;		-- Signal de reset
			clock :				in	std_logic;		-- horloge de synchronisation
			PWR_ENABLE : 		in  std_logic;		--Active l'alimentation
			PWR_OK :			out std_logic;		--Indique que l'alimentation est ON et OK
			PWR_OFF :			out	std_logic;		--Indique que l'alimentation est OFF
			ERROR :				out std_logic;		--Indique une erreur sur les alimentations
			-- interface avec les régulateurs
			Voltage_good :		in	std_logic_vector (Nb_Voltages downto 1);
			Voltage_enable :	out	std_logic_vector (Nb_Voltages downto 1)
			);
end entity power_sequencer;

architecture auto_generate of power_sequencer is

	--Déclaration des composants
	component voltage_manager is
	port (
		reset :				in std_logic;	-- Signal de reset
		--horlage de cadencement
		clock :				in	std_logic;	-- fréquence à définir
		--Interface avec manager amont
		enable_input :		in	std_logic;	-- mise sous/hors tension (ON à l'état haut)
		power_off_output :	out	std_logic;	-- indique que la tension est à 0V ou presque
		error_output:		out std_logic;	-- indique une erreur à la mise sous tension ou en cours de fonctionnement
		--Interface avec manager aval
		power_good_output : out	std_logic;	-- indique que la tension est ok et stable
		power_off_input :	in	std_logic;	-- Autorise la mise hors tension (quand les alims plus basses sont OFF)	
		error_input :		in	std_logic;	-- entrée pour la transmission des erreurs
		--Interface avec le régulateur de tension
		voltage_good :		in	std_logic;	--entrée du power good du régulateur (actif haut)
		voltage_enable :	out std_logic	--sortie d'activation du régulateur (actif haut)
	);

	end component voltage_manager;
	
	component gh_DFF is
		 port(
			 D    : in STD_LOGIC;
			 CLK  : in STD_LOGIC;
			 rst  : in STD_LOGIC;
			 Q    : out STD_LOGIC
		     );
	end component gh_DFF;

	--Déclaration des signaux
	--signal clock_sequence : std_logic;
	signal enable_interne, power_off_interne, error_interne : std_logic_vector (Nb_Voltages downto 0);
	signal error_reg : std_logic;			-- erreur mémorisée jusqu'au passage à 0 de PWR_ENABLE
	signal pwr_enable_sync_temp, pwr_enable_sync : std_logic;	-- Power enable synchronisé
	signal voltage_good_sync_temp, voltage_good_sync : std_logic_vector (Nb_Voltages downto 1);	-- Signaux voltage_good synchronisés
	
	begin
		-- Synchronisation de l'entrée PWR_ENABLE
		enable_sync1: gh_DFF port map(
									 D	 => PWR_ENABLE,
									 CLK => clock,
									 rst => reset,
									 Q   => pwr_enable_sync_temp
									 );
		enable_sync2: gh_DFF port map(
									 D	 => pwr_enable_sync_temp,
									 CLK => clock,
									 rst => reset,
									 Q   => pwr_enable_sync
									 );
		-- Synchronisation des entrées VOLTAGE_GOOD
		Sync_voltage_good: for I in 1 to Nb_Voltages generate
			Voltage_good_sync1: gh_DFF port map(
									 D	 => Voltage_good (I),
									 CLK => clock,
									 rst => reset,
									 Q   => voltage_good_sync_temp (I)
									 );
			Voltage_good_sync2: gh_DFF port map(
										 D	 => voltage_good_sync_temp (I),
										 CLK => clock,
										 rst => reset,
										 Q   => voltage_good_sync (I)
									     );
		end generate Sync_voltage_good;
		
		-- Sorites du sequenceur
		PWR_OFF <= power_off_interne(0);		--Sortie power off global reliée à la sortie du manager 1
		PWR_OK <= enable_interne(Nb_Voltages);	--Sortie power ok global reliée à la sortie du dernier nanager
		ERROR <= error_reg;						--Sortie erreur reliée au signal d'erreur registred
		
		-- controle du 1er manager
		enable_interne(0) <= pwr_enable_sync and not error_reg;		--Entrée enable du manager 1 reliée au power enable global si pas d'erreur
		-- controle du dernier manager
		power_off_interne(Nb_Voltages) <= '1';	--entrée power off du dernier manager forcée à 1 pour autoriser l'arrer
		error_interne(Nb_Voltages) <= '0';		--entrée erreur du dernier manager forcée à 0 pour ne pas signaler d'erreur
		
		-- Instentiation des modules de management et iterconnexions internes
		Sequenceur: for I in 1 to Nb_Voltages generate
			manager: voltage_manager port map (	
												reset,
												--horlage de cadencement
												clock,
												--Interface avec manager amont, les signaux provenants de l'amont sont I-1
												enable_interne (I-1),
												power_off_interne (I-1),
												error_interne (I-1),
												--Interface avec manager aval
												enable_interne (I),
												power_off_interne (I),
												error_interne (I),
												--Interface avec le régulateur de tension
												voltage_good_sync (I),
												Voltage_enable (I)
												);
		end generate Sequenceur;

		error_memory: process (error_interne(0), pwr_enable_sync, error_reg)
		begin
				if (pwr_enable_sync = '0') then
					error_reg <= '0';
				elsif (error_interne(0) = '1') then
					error_reg <= '1';
				else error_reg <= error_reg;
				end if;
		end process error_memory;
		
end architecture auto_generate;


