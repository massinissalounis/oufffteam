using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.FileManager
{
    class StructuredFileKey
    {
        // Constructor ----------------------------------------------------------------------------
        public StructuredFileKey()
        {
            // Initialisation des valeurs par défaut
            _groupID = -1;
            _key = null;
            _value = null;
        }

        public StructuredFileKey(int groupID, String key, String value)
        {
            // Initialisation des valeurs par défaut
            _groupID = -1;
            _key = null;
            _value = null;
        }


        // Properties -----------------------------------------------------------------------------

        // Public ---------------------------------------------------------------------------------

        // Private --------------------------------------------------------------------------------
        private int _groupID;           // Pour stocker les ID des groupes de commandes
        private String _key;            // Clé permettant d'identifier la donnée 
        private String _value;          // Valeur de la clé
    }
}
