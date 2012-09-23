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
        /// LoopID  : ID used to indicate in which loop the kay must be used
        ///           (LoopID = -1 means that this data is not included in a loop)
        /// GroupID : ID used to identify multi keys for one unique pattern line
        /// Name    : Name of the key to add
        /// Value   : Value of this key
        /// </summary>
        public StructuredFileKey(int LoopID, int GroupID, String Name, String Value)
        {
            // Assign current value
            _LoopID = LoopID;
            _GID = GroupID;
            _Name = Name;
            _Value = Value;

            return;
        }

        public int GetLoopID()
        {
            return _LoopID;
        }

        public int GetGID()
        {
            return _GID;
        }

        public String GetName()
        {
            return _Name;
        }

        public String GetValue()
        {
            return _Value;
        }

        public String Debug()
        {
            return ("[" + _LoopID.ToString() + "/" + _GID.ToString() + "] " + _Name + " = " + _Value);
        }

        // Private --------------------------------------------------------------------------------
        private int _LoopID;
        private int _GID;
        private String _Name;
        private String _Value;
    }
}
