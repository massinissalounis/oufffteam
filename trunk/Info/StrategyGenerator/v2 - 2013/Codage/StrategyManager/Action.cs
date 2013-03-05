using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.StrategyManager
{
    class Action
    {
        // Public ---------------------------------------------------------------------------------


        // Properties -----------------------------------------------------------------------------


        // Private functions ----------------------------------------------------------------------
        /// <summary>
        /// Fontion charger les valeurs par défaut pour les commandes
        /// </summary>
        private void LoadDefaultValue()
        {
            switch (_cmd)
            {
                // _______________________________________________________
                case EnumCmd.App_IfGoto_Strategy:
                case EnumCmd.App_IfGoto_System:
                    _param1 = "(true == true)";                         // Test
                    _param2 = "-1";                                     // nextID si le test est vrai
                    _param3 = "-1";                                     // nextID si le test est faux
                    _param4 = null;                                     // Not Set
                    _activeSensors = EnumActiveSensors.COLLISION_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.App_SetNewPos:
                    _param1 = "1500";                                   // Position en x
                    _param2 = "1000";                                   // Position en y
                    _param3 = "-90";                                    // Angle
                    _param4 = null;                                     // Not Set
                    _activeSensors = EnumActiveSensors.COLLISION_NONE;  // Pas de sensors d'activé
                    break;
                    
                // _______________________________________________________
                case EnumCmd.

                // _______________________________________________________
                
                // _______________________________________________________
                
                // _______________________________________________________



                // _______________________________________________________
                case EnumCmd.NotSet:
                default:
                    break;
            }
        }

        // Private --------------------------------------------------------------------------------
        private int _uID;                               // Identifiant unique pour l'action
        private EnumCmd _cmd;                           // Commande
        private EnumCmdType _cmdType;                   // Type de l'action à réaliser
        private String _param1;                         // Param 1
        private String _param2;                         // Param 2
        private String _param3;                         // Param 3
        private String _param4;                         // Param 4
        private EnumActiveSensors _activeSensors;       // Sensors actifs durant le mouvement
        private int _nextActionID;                      // Action suivante
        private int _timeoutID;                         // Action à réaliser en cas de timeout
    }
}
