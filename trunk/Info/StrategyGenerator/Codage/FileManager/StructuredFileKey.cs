using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator.FileManager
{
    class StructuredFileKey
    {
         // Constructeur ---------------------------------------------------------------------------
        /// <summary>
        /// GroupID : ID used to identify multi keys for one unique pattern line
        /// Name    : Name of the key to add
        /// Value   : Value of this key
        /// </summary>
        public StructuredFileKey(int GroupID, String Name, String Value)
        {
            // Assign current value
            _GID = GroupID;
            _Name = Name;
            _Value = Value;

        }

        // Private --------------------------------------------------------------------------------
        private int _GID;
        private String _Name;
        private String _Value;
    }
}
