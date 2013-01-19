using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.Tools
{
    class DebugTool
    {
        /// <summary>
        /// Enum pour lister tous les types de mode de debug supportés
        /// </summary>
        public enum EDebugToolType
        {
            Disabled = 0,
            Console = 1
        }

        // Constructor ----------------------------------------------------------------------------
        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="debugToolType">Mode de débug souhaité</param>
        public DebugTool(EDebugToolType debugToolType)
        {
            _debugToolType = debugToolType;
        }

        // Properties -----------------------------------------------------------------------------
        /// <summary>
        /// Type de débug utilisé 
        /// </summary>
        public EDebugToolType Type
        {
            get { return _debugToolType; }
            set { _debugToolType = value; }
        }

        // Public ---------------------------------------------------------------------------------
        /// <summary>
        /// Ecrire du texte dans le flux de debug choisi
        /// </summary>
        /// <param name="logMessage">Texte a écrire</param>
        public void Write(string logMessage)
        {
            switch (_debugToolType)
            {
                case EDebugToolType.Disabled:
                    break;

                case EDebugToolType.Console:
                    Console.Write(logMessage);
                    break;

                default:
                    break;
            }
        }

        /// <summary>
        /// Ecrire une ligne dans le flux de debug choisi
        /// </summary>
        /// <param name="logMessage">Ligne a écrire</param>
        public void WriteLine(string logMessage)
        {
            switch (_debugToolType)
            {
                case EDebugToolType.Disabled:
                    break;

                case EDebugToolType.Console:
                    Console.WriteLine("\n"+logMessage);
                    break;

                default:
                    break;
            }
        }

        // Private --------------------------------------------------------------------------------
        private EDebugToolType _debugToolType = EDebugToolType.Disabled;
    }
}
