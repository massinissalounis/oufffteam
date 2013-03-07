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
        public 


        // Private functions ----------------------------------------------------------------------
        /// <summary>
        /// Fontion charger les valeurs par défaut pour la commande actuelle
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
                    _param4 = null;                                     // Not Used
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
                case EnumCmd.App_SetStrategyFlags:
                    _param1 = EnumStrategyFlags.NotSet.ToString();      // Flag à modifier
                    _param2 = "OS_FALSE";                               // Nouvelle valeur du flag
                    _param3 = null;                                     // Not Set
                    _param4 = null;                                     // Not Set
                    _activeSensors = EnumActiveSensors.COLLISION_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.App_Wait:
                    _param1 = "0";                                      // Temps d'attente en heure
                    _param2 = "0";                                      // Temps d'attente en minute
                    _param3 = "5";                                      // Temps d'attente en sec
                    _param4 = "0";                                      // Temps d'attente en msec
                    _activeSensors = EnumActiveSensors.COLLISION_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.Mvt_Stop:
                    _param1 = null;                                     // Not Used
                    _param2 = null;                                     // Not Used
                    _param3 = null;                                     // Not Used
                    _param4 = null;                                     // Not Used
                    _activeSensors = EnumActiveSensors.COLLISION_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.Mvt_UseAngleOnly:
                case EnumCmd.MvtSimple_RotateInDeg:
                case EnumCmd.MvtSimple_RotateToAngleInDeg:
                    _param1 = "DEFAULT_SPEED";                          // Vitesse du déplacement
                    _param2 = null;                                     // Not Used
                    _param3 = null;                                     // Not Used
                    _param4 = "0";                                      // Angle
                    _activeSensors = EnumActiveSensors.COLLISION_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.Mvt_UseDistOnly:
                    _param1 = "DEFAULT_SPEED";                          // Vitesse du déplacement
                    _param2 = "1500";                                   // Position en x
                    _param3 = "1000";                                   // Position en y
                    _param4 = null;                                     // Not Used
                    _activeSensors = EnumActiveSensors.COLLISION_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.Mvt_UseMixedMode:
                case EnumCmd.Mvt_UseSpline:
                    _param1 = "DEFAULT_SPEED";                          // Vitesse du déplacement
                    _param2 = "1500";                                   // Position en x
                    _param3 = "1000";                                   // Position en y
                    _param4 = "0";                                      // Angle
                    _activeSensors = EnumActiveSensors.COLLISION_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.Mvt_UsePivotMode:
                    _param1 = "DEFAULT_SPEED";                          // Vitesse du déplacement
                    _param2 = "RIGHT_WHEEL";                            // Roue bloquée
                    _param3 = null;                                     // Not Used
                    _param4 = "0";                                      // Angle
                    _activeSensors = EnumActiveSensors.COLLISION_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.MvtSimple_MoveInMM:
                    _param1 = "DEFAULT_SPEED";                          // Vitesse du déplacement
                    _param2 = "100";                                    // Distance en mm
                    _param3 = null;                                     // Not Used
                    _param4 = null;                                     // Not Used
                    _activeSensors = EnumActiveSensors.COLLISION_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.NotSet:
                default:
                     _param1 = null;                                    // Not Used
                    _param2 = null;                                     // Not Used
                    _param3 = null;                                     // Not Used
                    _param4 = null;                                     // Not Used
                    _activeSensors = EnumActiveSensors.NotSet;          // Not Used
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
        private List<String> _information;
    }
}
