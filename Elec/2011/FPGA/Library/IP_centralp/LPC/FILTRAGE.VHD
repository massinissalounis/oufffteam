-- ---------------------------------------------------
-- fichier: filtrage.vhd
--
-- Revisions:
-- ----------
-- Revision 1.0    Auteur: M. RAHMANI    Date: 11/05/2001
--
-- Commentaire:
-- ------------ 
-- Ce composant genere un filtre compose de 3 bascules D. sortie_filtre
-- vaut entree_filtre si entree_filtre reste stable pendant au moins
-- 3 coups de horloge_filtre.
-- Le niveau 0 est maintenu jusqu'à ce que le SIGNAL ack passe à 1
--
-- l'Horloge des bascules est l'entree clock_filtre.
--
-- nRESET_systeme est une entree reset asynchrone.
-- ---------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY filtrage IS
    PORT(
        entree_filtre   : IN  std_logic;
        clock_filtre    : IN  std_logic;
        nreset_systeme  : IN  std_logic;
        ack             : IN  std_logic;
        sortie_filtre   : OUT std_logic
    );
END filtrage;

ARCHITECTURE arch_filtrage OF filtrage IS
    SIGNAL entree_retardee : std_logic_vector(3 DOWNTO 1);
BEGIN
    PROCESS (clock_filtre,nreset_systeme)
    BEGIN
        IF (nreset_systeme='0')    THEN     
            entree_retardee <= (OTHERS=>'1');
            sortie_filtre   <= '1';
        ELSIF (clock_filtre'event AND clock_filtre='1') THEN
            entree_retardee(1) <= entree_filtre;
            entree_retardee(2) <= entree_retardee(1);
            entree_retardee(3) <= entree_retardee(2);
            IF ((entree_retardee(1) AND entree_retardee(2) AND 
                entree_retardee(3) AND ack)='1')THEN              -- ack IS '1' if a '0' has been transmitted
                sortie_filtre  <= '1';
            ELSIF((entree_retardee(1) OR entree_retardee(2) OR
                   entree_retardee(3))='0')THEN
                sortie_filtre  <= '0';
            END IF;
        END IF;
    END PROCESS;
END arch_filtrage;
