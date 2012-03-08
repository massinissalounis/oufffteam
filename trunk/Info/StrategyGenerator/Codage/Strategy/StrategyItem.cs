using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator.Strategy
{
    class StrategyItem
    {
        public StrategyItem(Command Action, int ActionID, int NextActionID)
        {
            if ((Action == null) || (_ActionID < 0))
            {
                throw (new Exception("Invalid params"));
            }

            // Création de l'objet
            _Cmd = Action;
            _ActionID = ActionID;
            _NextActionID = NextActionID;
        }

        public Command Cmd { get { return _Cmd; } }
        public int ActionID { get { return _ActionID; } }
        public int NextActionID { get { return _NextActionID; } }

        public int LoopID
        {
            get
            {
                int Res = _ActionID % 100;
                return ((_ActionID - Res) / 100);
            }
        }

        public int GID
        {
            get
            {
                return (_ActionID % 100);
            }
        }

        public int NextLoopID
        {
            get
            {
                int Res = _NextActionID % 100;
                return ((_NextActionID - Res) / 100);
            }
        }

        public int NextGID
        {
            get
            {
                return (_NextActionID % 100);
            }
        }

        // Private --------------------------------------------------------------------------------
        private Command _Cmd;               // Contient la commande associée à cet item
        private int _ActionID;              // Contient l'ID de l'action                                                
        private int _NextActionID;          // Contient l'ID de la prochaine action

    }
}
