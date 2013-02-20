using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.FileManager
{
    public class StructuredFileKey
    { 
        // Constructor ----------------------------------------------------------------------------
        public StructuredFileKey()
        {
            // Initialisation des valeurs par défaut
            _ID = null;
            _value = null;
        }

        public StructuredFileKey(String keyID, String newValue)
        {
            // Initialisation des valeurs par défaut
            ID = keyID;
            valueString = newValue;
        }

        public StructuredFileKey(String keyID, int newValue)
        {
            // Initialisation des valeurs par défaut
            ID = keyID;
            valueInt = newValue;
        }

        public StructuredFileKey(String keyID, double newValue)
        {
            // Initialisation des valeurs par défaut
            ID = keyID;
            valueDouble = newValue;
        }

        // Properties -----------------------------------------------------------------------------
        public String ID 
        {
            get { return _ID; }
            set { _ID = value; }
        }
        
        public String valueString
        {
            get { return _value; }
            set { _value = value; }
        }

        public int valueInt
        {
            get
            {
                try
                {
                    return Convert.ToInt32(_value);
                }
                catch(Exception)
                {
                    return 0;
                }
            }
            set { _value = value.ToString(); }
        }

        public double valueDouble
        {
            get
            {
                try
                {
                    return Convert.ToDouble(_value);
                }
                catch (Exception)
                {
                    return 0.0;
                }
            }
            set { _value = value.ToString(); }
        }

        // Public ---------------------------------------------------------------------------------

        // Private --------------------------------------------------------------------------------
        private String _ID;            // Clé permettant d'identifier la donnée 
        private String _value;          // Valeur de la clé
    }
}
