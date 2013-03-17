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
            _keyName = null;
            _value = null;
        }

        public StructuredFileKey(String keyID, String newValue)
        {
            // Initialisation des valeurs par défaut
            keyName = keyID;
            valueString = newValue;
        }

        public StructuredFileKey(String keyID, int newValue)
        {
            // Initialisation des valeurs par défaut
            keyName = keyID;
            valueInt = newValue;
        }

        public StructuredFileKey(String keyID, double newValue)
        {
            // Initialisation des valeurs par défaut
            keyName = keyID;
            valueDouble = newValue;
        }

        // Properties -----------------------------------------------------------------------------
        public String keyName 
        {
            get { return _keyName; }
            set { _keyName = value; }
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
        private String _keyName;        // Clé permettant d'identifier la donnée 
        private String _value;          // Valeur de la clé
    }
}
