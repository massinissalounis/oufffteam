-- Oufffteam
-- Projet carte mère
-- Device: quadrature_counter

-- 03/02/2010			CBE			Création


library ieee;
use ieee.std_logic_1164.all;

package quadrature_counter_p is
 
	component quadrature_counter is
		generic ( 	Nb_bits : natural := 16 ;              -- nombre de bits de sortie
					Nb_bascules : natural := 2            -- bascules d'antiparasites supplementaires si =2, sinon 1
				);
		port 	( 	Clock: in  std_logic; -- Horloge de référence
					Resetbar: in  std_logic; -- Reset actif bas du module

					A : in std_logic; -- Canal A du codeur
					B : in std_logic; -- Canal B du codeur

					Count_out : out  std_logic_vector (Nb_bits-1 downto 0);
					Count_latch : in std_logic
				);
	end component quadrature_counter;
  
end quadrature_counter_p;
-------------------------------------------------------------------------------
-- end of file

