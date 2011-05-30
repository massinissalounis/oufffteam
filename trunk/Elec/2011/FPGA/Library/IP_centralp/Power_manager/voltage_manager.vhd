--**************************************************************************************************************************
--Project                      : GENERIC IP
--
--File                            : voltage_manager.vhd
--
--Author                       : C. BEGUET  23/02/09                                                                                   Copyight Centralp, 2009
--
--Board                         : GENERIC IP
--Device                       : GENERIC IP
--Part refence             :
--Program Number      :
--
-- Dependencies:		??
--				??
--				??
--
-- Revision history:	Rev.	Date (dd/mm/yyyy)	Author		Comments
--				
--
--**************************************************************************************************************************
--Purpose: 
-- Séquenceur d'alimentation generique
-- Ordonne les alimentations de 1 à Nb_Voltages, 1 étant l'alimentation à mettre sous tension en 1er
-- Entité voltage_manager qui gère une tention
--
--**************************************************************************************************************************

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity voltage_manager is
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
end entity voltage_manager;

architecture state_machine of voltage_manager is

	type power_states is (voltage_off, starting, voltage_ok, wait_stopping, stopping);	--états
	signal next_state, monitoring_state : power_states;	--déclaration de la machine d'états
	signal enable_intern, error_interne : std_logic;

begin

	enable_intern <= enable_input and not (error_interne or error_input);	--activation uniquement si aucune erreur
	error_output <= error_interne or error_input;							--transmission de l'erreur

	state_machine: process (monitoring_state, enable_intern, power_off_input, voltage_good)
		begin
			case monitoring_state is
				when voltage_off =>
					-- affectation des sorties
					power_off_output <= '1';	-- L'alimentation est OFF
					power_good_output <= '0';	-- power NOT good
					VOLTAGE_ENABLE <= '0';		-- régulateur activé
					error_interne <= '0';		-- on reset l'erreur interne
					-- transisions
					if (enable_intern = '1') then next_state <= starting;
					else next_state <= voltage_off;
					end if;
				
				when starting =>
					-- affectation des sorties
					power_off_output <= '0';	-- L'alimentation n'est pas OFF
					power_good_output <= '0';	-- power NOT good
					VOLTAGE_ENABLE <= '1';		-- régulateur activé
					-- transisions
					if (enable_intern = '0') then next_state <= wait_stopping;
					elsif (voltage_good = '1') then next_state <= voltage_ok;
					else next_state <= starting;
					end if;
				
				when voltage_ok =>
					-- affectation des sorties
					power_off_output <= '0';	-- L'alimentation n'est pas OFF
					power_good_output <= '1';	-- power good
					VOLTAGE_ENABLE <= '1';		-- régulateur activé

					-- transisions
					if (enable_intern = '0' or voltage_good = '0') then
						next_state <= wait_stopping;	-- Erreur ou demande d'arret
						if (voltage_good = '0') then	-- Détection d'erreur
							error_interne <= '1';		-- Erreur détectée
						end if;
					else next_state <= voltage_ok;
					end if;
				
				when wait_stopping =>			-- Arret demandé, attend que les alims plus basses soient OFF
					-- affectation des sorties
					power_off_output <= '0';	-- L'alimentation n'est pas OFF
					power_good_output <= '0';	-- power NOT good
					VOLTAGE_ENABLE <= '1';		-- régulateur activé
					-- transisions
					if (power_off_input = '1') then next_state <= stopping;
					else next_state <= wait_stopping;
					end if;
					
				when stopping =>
					-- affectation des sorties
					power_off_output <= '0';	-- L'alimentation n'est pas OFF
					power_good_output <= '0';	-- power NOT good
					VOLTAGE_ENABLE <= '0';		-- régulateur désactivé
					-- transisions
					if (voltage_good = '0') then next_state <= voltage_off;
					else next_state <= stopping;
					end if;
				
				when others => next_state <= voltage_off;
			end case;
	end process state_machine;
	
	sequence: process (clock, reset)
		begin
			if (reset = '1') then
				monitoring_state <= voltage_off;
			elsif (rising_edge (clock)) then
				monitoring_state <= next_state;
			else
				monitoring_state <= monitoring_state;
			end if;
	end process sequence;


end state_machine;
	
	