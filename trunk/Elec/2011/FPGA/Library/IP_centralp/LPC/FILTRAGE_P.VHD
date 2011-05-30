-------------------------------------------------------------------------------
--
-- fichier: filtrage_p.vhd
--
-- PACKAGE Filtrage 3 périodes d'horloge
-------------------------------------------------------------------------------
-- Revisions :
-- ----------
--
-- Revision 1.0  Auteur : Laurent Rabatel           Date: 18 janvier 2007
-- Creation
-------------------------------------------------------------------------------

LIBRARY ieee;
  USE ieee.std_logic_1164.ALL;
  USE ieee.std_logic_arith.ALL;
  USE ieee.std_logic_unsigned.ALL;

----------------------------- P A C K A G E  -----------------------------------
PACKAGE filtrage_p IS

  COMPONENT filtrage
    PORT (
      entree_filtre   : IN  std_logic;
      clock_filtre    : IN  std_logic;
      nreset_systeme  : IN  std_logic;
      ack             : IN  std_logic;
      sortie_filtre   : OUT std_logic);
  END COMPONENT;

END PACKAGE filtrage_p;
-------------------------------------------------------------------------------
-- END OF file
