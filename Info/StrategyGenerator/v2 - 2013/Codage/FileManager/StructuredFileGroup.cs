using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.FileManager
{
    public class StructuredFileGroup
    { 
        // Constructor ----------------------------------------------------------------------------
        public StructuredFileGroup()
        {
            _groupID = -1;
            _keys = null;
        }

        public StructuredFileGroup(int groupID, StructuredFileKey newKey)
        {
            // Verification des paramètres d'entrée
            if ((groupID < 0) || (newKey == null))
            {
                // En cas de paramètre non valide, on ne crée pas l'objet
                _groupID = -1;
                _keys = null;
            }
            else
            {
                // Creation de l'objet
                _groupID = groupID;

                // Ajout des données 
                if (_keys == null)
                    _keys = new List<StructuredFileKey>();

                _keys.Add(newKey);
            }
        }
        
        // Properties -----------------------------------------------------------------------------
        public int groupID
        {
            get { return _groupID; }
            internal set { return; }
        }

        // Public ---------------------------------------------------------------------------------
        /// <summary>
        /// Permet de retourner toutes les clés contenues dans ce groupID
        /// </summary>
        /// <returns>La liste de toutes les clés (null si la liste est vide)</returns>
        public List<StructuredFileKey> GetAllKeys()
        {
            return _keys;
        }

        /// <summary>
        /// Permet de retourner toutes les clés contenues dans ce groupID pour un ID spécifique
        /// </summary>
        /// <param name="keyID"></param>
        /// <returns>La liste de toutes les clés trouvées (null si la liste est vide)</returns>
        public List<StructuredFileKey> GetKeys(String keyID)
        {
            List<StructuredFileKey> retKeys = null;

            // Verification des paramètres
            if (_keys == null)
                retKeys = null;
            else
            {
                // On parcourt la liste complète
                foreach (StructuredFileKey tmpKey in _keys)
                {
                    // Si la clé attendue est trouvée
                    if (tmpKey.ID == keyID)
                    {
                        // Ajout de la clé dans l'objet de retour 
                        // (si la structure de retour est vide, on commence par la créer)
                        if (retKeys == null)
                            retKeys = new List<StructuredFileKey>();

                        retKeys.Add(tmpKey);
                    }
                }
            }

            return retKeys;
        }

        // Private --------------------------------------------------------------------------------
        private int _groupID = -1;                              // ID du groupe
        private List<StructuredFileKey> _keys = null;           // Contient toutes les clées du groupe considéré
    }
}
