using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.FileManager
{
    public class StructuredFileGroup
    { 
        // Constructor ----------------------------------------------------------------------------
        public StructuredFileGroup(uint groupID)
        {
            _groupID = groupID;
            _keys = null;
        }

        public StructuredFileGroup(uint groupID, StructuredFileKey newKey)
        {
            // Verification des paramètres d'entrée
            if (newKey == null)
            {
                // En cas de paramètre non valide, on ne crée pas l'objet
                _groupID = 0;
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
        public uint groupID
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

        /// <summary>
        /// Permet d'ajouter une clé au groupe
        /// </summary>
        /// <param name="newKeyID">clé à ajouter</param>
        public void AddKey(StructuredFileKey newKeyID)
        {
            // Verification des paramètres
            if (newKeyID != null)
            {
                // Verification de la liste actuelle
                if (_keys == null)
                    _keys = new List<StructuredFileKey>();

                // Ajout de la clé
                _keys.Add(newKeyID);
            }                
        }

        /// <summary>
        /// Permet d'ajouter une liste de clé au groupe
        /// </summary>
        /// <param name="listNewKeyID">Liste de clé à ajouter</param>
        public void AddKey(List<StructuredFileKey> listNewKeyID)
        {
            // Verification des paramètres
            if ((listNewKeyID != null) && (listNewKeyID.Count() > 0))
            {
                // Verification de la liste actuelle
                if(_keys == null)
                    _keys = new List<StructuredFileKey>();

                // Ajout de toutes les clés
                foreach(StructuredFileKey currentKeyID in listNewKeyID)
                {
                    _keys.Add(currentKeyID);
                }
            }
            return;
        }

        /// <summary>
        /// Retourne le nombre de clé du groupe
        /// </summary>
        /// <returns>Nombre de clé</returns>
        public int Count()
        {
            int Ret = 0;

            // Verification de la liste actuelle
            if (_keys != null)
            {
                // Recupération de la valeur
                Ret = _keys.Count();
            }

            return Ret;
        }

        // Private --------------------------------------------------------------------------------
        private uint _groupID = 0;                              // ID du groupe
        private List<StructuredFileKey> _keys = null;           // Contient toutes les clées du groupe considéré
    }
}
