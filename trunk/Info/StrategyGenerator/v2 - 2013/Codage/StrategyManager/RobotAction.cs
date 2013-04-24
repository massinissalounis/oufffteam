using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using StrategyGenerator2.FileManager;

namespace StrategyGenerator2.StrategyManager
{
    public class RobotAction
    {
        // Public ---------------------------------------------------------------------------------
        public RobotAction()
        {
            _uID = 0;                                       // Identifiant unique pour l'action
            _cmd = EnumCmd.NotSet;                          // Commande
            _cmdType = EnumCmdType.CmdType_NotSet;                  // Type de l'action à réaliser
            _param1 = "";                                   // Param 1
            _param2 = "";                                   // Param 2
            _param3 = "";                                   // Param 3
            _param4 = "";                                   // Param 4
            _activeSensors = EnumActiveSensors.NotSet;      // Sensors actifs durant le mouvement
            _nextID = -1;                                   // Action suivante
            _timeoutID = -1;                                // Action à réaliser en cas de timeout
        }

        public RobotAction(int ID)
        {
            _uID = ID;                                      // Identifiant unique pour l'action
            _cmd = EnumCmd.NotSet;                          // Commande
            _cmdType = EnumCmdType.CmdType_NotSet;                  // Type de l'action à réaliser
            _param1 = "";                                   // Param 1
            _param2 = "";                                   // Param 2
            _param3 = "";                                   // Param 3
            _param4 = "";                                   // Param 4
            _activeSensors = EnumActiveSensors.NotSet;      // Sensors actifs durant le mouvement
            _nextID = -1;                                   // Action suivante
            _timeoutID = -1;                                // Action à réaliser en cas de timeout
        }

        /// <summary>
        /// Permet de mettre à jour les données de l'objet en cours à partir d'un autre objet passé en paramètre
        /// </summary>
        /// <param name="newValues">Objet contenant les nouvelles valeurs à assigner</param>
        public void UpdateValue(RobotAction newValues)
        {
            if (newValues != null)
            {
                this.ID = newValues.ID;
                this.cmd = newValues.cmd;
                this.cmdType = newValues.cmdType;
                this.param1 = newValues.param1;
                this.param2 = newValues.param2;
                this.param3 = newValues.param3;
                this.param4 = newValues.param4;
                this.activeSensors = newValues.activeSensors;
                this.nextID = newValues.nextID;
                this.timeoutID = newValues.timeoutID;
            }
        }

        /// <summary>
        /// Fonction pour verifier toutes les fonctions private du modules
        /// </summary>
        /// <returns>True si toutes les fonctions sont fonctionnelles, False sinon</returns>
        public bool CheckPrivateFunction()
        {
            bool Ret = true;

            if (CheckIntValue("AAAA", 0, 100, "NOK") != "NOK")
                Ret = false;

            if (CheckIntValue("0", 0, 100, "NOK") != "0")
                Ret = false;

            if (CheckIntValue("50", 0, 100, "NOK") != "50")
                Ret = false;

            if (CheckIntValue("150", 0, 100, "NOK") != "NOK")
                Ret = false;

            if (CheckStrategyFlagsValue("NotSet", "NOK") != "NotSet")
                Ret = false;

            if (CheckStrategyFlagsValue("Err", "NOK") != "NOK")
                Ret = false;

            if (CheckBooleanValue("OS_TRUE", "NOK") != "OS_TRUE")
                Ret = false;

            if (CheckBooleanValue("OS_FALSE", "NOK") != "OS_FALSE")
                Ret = false;

            if (CheckBooleanValue("true", "NOK") != "OS_TRUE")
                Ret = false;

            if (CheckBooleanValue("false", "NOK") != "OS_FALSE")
                Ret = false;

            if (CheckBooleanValue("Test", "NOK") != "NOK")
                Ret = false;

            if (CheckWheelValue("RIGHT_WHEEL", "NOK") != "RIGHT_WHEEL")
                Ret = false;

            if (CheckWheelValue("LEFT_WHEEL", "NOK") != "LEFT_WHEEL")
                Ret = false;

            if (CheckWheelValue("right_wheel", "NOK") != "RIGHT_WHEEL")
                Ret = false;

            if (CheckWheelValue("left_wheel", "NOK") != "LEFT_WHEEL")
                Ret = false;

            if (CheckWheelValue("Test", "NOK") != "NOK")
                Ret = false;

            if (CheckAngleValue("361", "NOK") != "1")
                Ret = false;

            if (CheckAngleValue("-270", "NOK") != "90")
                Ret = false;

            if (CheckAngleValue(null, "0") != "0")
                Ret = false;

            if (CheckAngleValue("ERR", "NOK") != "NOK")
                Ret = false;

            if (CheckEnumCmdValue("Mvt_UseMixedMode", EnumCmd.NotSet) != EnumCmd.Mvt_UseMixedMode)
                Ret = false;

            if (CheckEnumCmdValue("Err", EnumCmd.NotSet) != EnumCmd.NotSet)
                Ret = false;

            if (CheckEnumCmdTypeValue("CmdType_Blocking", EnumCmdType.CmdType_NotSet) != EnumCmdType.CmdType_Blocking)
                Ret = false;

            if (CheckEnumCmdTypeValue("CmdType_NonBlocking", EnumCmdType.CmdType_NotSet) != EnumCmdType.CmdType_NonBlocking)
                Ret = false;

            if (CheckEnumCmdTypeValue("ERR", EnumCmdType.CmdType_NotSet) != EnumCmdType.CmdType_NotSet)
                Ret = false;

            if (CheckEnumActiveSensorsValue("APP_PARAM_STRATEGYFLAG_COLLISION_FRONT", EnumActiveSensors.NotSet) != EnumActiveSensors.APP_PARAM_STRATEGYFLAG_COLLISION_FRONT)
                Ret = false;

            if (CheckEnumActiveSensorsValue("ERR", EnumActiveSensors.NotSet) != EnumActiveSensors.NotSet)
                Ret = false;

            return Ret;
        }

        /// <summary>
        /// Permet d'exporter l'action en cours dans un StructuredFileGroup
        /// </summary>
        /// <returns>Un objet StructuredFileGroup</returns>
        public StructuredFileGroup Export()
        {
            // Creation du groupe
            StructuredFileGroup Ret = new StructuredFileGroup(Convert.ToUInt32(_uID));

            // Ajout des données 
            Ret.AddKey(new StructuredFileKey(ExchangeTag.cmd, _cmd.ToString()));
            Ret.AddKey(new StructuredFileKey(ExchangeTag.cmdType, _cmdType.ToString()));
            Ret.AddKey(new StructuredFileKey(ExchangeTag.param1, _param1));
            Ret.AddKey(new StructuredFileKey(ExchangeTag.param2, _param2));
            Ret.AddKey(new StructuredFileKey(ExchangeTag.param3, _param3));
            Ret.AddKey(new StructuredFileKey(ExchangeTag.param4, _param4));
            Ret.AddKey(new StructuredFileKey(ExchangeTag.activeSensors, _activeSensors.ToString()));
            Ret.AddKey(new StructuredFileKey(ExchangeTag.nextID, _nextID));
            Ret.AddKey(new StructuredFileKey(ExchangeTag.timeoutID, _timeoutID));

            return Ret;
        }

        /// <summary>
        /// Importe les données de l'objet StructuredFileGroup dans l'objet en cours
        /// </summary>
        /// <param name="actionToImport">Données à importer dans l'objet</param>
        /// <returns>True si l'import est correct, false sinon</returns>
        public bool Import(StructuredFileGroup actionToImport)
        {
            bool Ret = false;
            StructuredFileKey currentKey = null;
            
            if (actionToImport != null)
            {
                try
                {
                    // Lecture du RobotAction ID
                    _uID = Convert.ToInt32(actionToImport.ID);

                    // Lecture de la commande
                    currentKey = actionToImport.GetFirstKey(ExchangeTag.cmd);
                    if (currentKey != null)
                    {
                        cmd = CheckEnumCmdValue(currentKey.valueString, EnumCmd.NotSet);
                    }

                    // Lecture de la variable CmdType
                    currentKey = actionToImport.GetFirstKey(ExchangeTag.cmdType);
                    if (currentKey != null)
                    {
                        cmdType = CheckEnumCmdTypeValue(currentKey.valueString, EnumCmdType.CmdType_NotSet);
                    }

                    // Lecture du Param1
                    currentKey = actionToImport.GetFirstKey(ExchangeTag.param1);
                    if (currentKey != null)
                    {
                        param1 = currentKey.valueString;
                    }

                    // Lecture du Param2
                    currentKey = actionToImport.GetFirstKey(ExchangeTag.param2);
                    if (currentKey != null)
                    {
                        param2 = currentKey.valueString;
                    }

                    // Lecture du Param3
                    currentKey = actionToImport.GetFirstKey(ExchangeTag.param3);
                    if (currentKey != null)
                    {
                        param3 = currentKey.valueString;
                    }

                    // Lecture du Param4
                    currentKey = actionToImport.GetFirstKey(ExchangeTag.param4);
                    if (currentKey != null)
                    {
                        param4 = currentKey.valueString;
                    }

                    // Lecture du param activeSensors
                    currentKey = actionToImport.GetFirstKey(ExchangeTag.activeSensors);
                    if (currentKey != null)
                    {
                        activeSensors = CheckEnumActiveSensorsValue(currentKey.valueString, EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE);
                    }

                    // Lecture du param nextID
                    currentKey = actionToImport.GetFirstKey(ExchangeTag.nextID);
                    if (currentKey != null)
                    {
                        nextID = currentKey.valueInt;
                    }

                    // Lecture du param timeoutID
                    currentKey = actionToImport.GetFirstKey(ExchangeTag.timeoutID);
                    if (currentKey != null)
                    {
                        timeoutID = currentKey.valueInt;
                    }

                    Ret = true;
                }
                catch (Exception)
                {
                    Ret = false;
                }
            }

            return Ret;
        }

        // Properties -----------------------------------------------------------------------------
        /// <summary>
        /// La modification de la commande implique un chargement par défaut des paramètres
        /// </summary>
        public EnumCmd cmd
        {
            get { return _cmd; }
            set
            {
                _cmd = value;
                LoadDefaultValue();
            }
        }

        /// <summary>
        /// Type de la commande 
        /// </summary>
        public EnumCmdType cmdType
        {
            get { return _cmdType; }
            set { _cmdType = value; }
        }

        /// <summary>
        /// L'ID est un entier > 0
        /// </summary>
        public int ID
        {
            get { return _uID; }
            set { if (value > 0) { _uID = value; } }
        }

        /// <summary>
        /// L'ID est un entier > 0
        /// (-1) permet de desactiver le timeout
        /// </summary>
        public int timeoutID
        {
            get { return _timeoutID; }
            set { _timeoutID = value; }
        }

        /// <summary>
        /// L'ID est un entier > 0
        /// (-1) permet de desactiver le nextID
        /// </summary>
        public int nextID
        {
            get { return _nextID; }
            set { _nextID = value; }
        }

        /// <summary>
        /// Accès au param 1 au format String
        /// </summary>
        public String param1
        {
            get{    return _param1; }
            set
            {
                switch (_cmd)
                {
                    // _______________________________________________________
                    case EnumCmd.App_IfGoto_Strategy:
                    case EnumCmd.App_IfGoto_System:
                        _param1 = value;                                    // Test
                        break;

                    // _______________________________________________________
                    case EnumCmd.App_SetStrategyFlags:
                        _param1 = EnumStrategyFlags.NotSet.ToString();      // Flag à modifier
                         break;

                    // _______________________________________________________
                    case EnumCmd.App_Wait:
                        _param1 = CheckIntValue(value, 0, 1, "0");          // Temps d'attente en heure
                        break;

                    // _______________________________________________________
                    case EnumCmd.Mvt_UseAngleOnly:
                    case EnumCmd.MvtSimple_RotateInDeg:
                    case EnumCmd.MvtSimple_RotateToAngleInDeg:
                    case EnumCmd.Mvt_UseDistOnly:
                    case EnumCmd.Mvt_UseMixedMode:
                    case EnumCmd.Mvt_UseSpline:
                    case EnumCmd.Mvt_UsePivotMode:
                    case EnumCmd.MvtSimple_MoveInMM:
                        _param1 = CheckIntValue(value, 1, 100, "DEFAULT_SPEED");    // Vitesse du déplacement
                        break;

                    // _______________________________________________________
                    case EnumCmd.Mvt_Stop:
                    case EnumCmd.NotSet:
                    case EnumCmd.App_SetNewPos:
                    default:
                        _param1 = "NotUsed";                                    // Not Used
                        break;
                }
            }
        }

        /// <summary>
        /// Accès au param 2 au format String
        /// </summary>
        public String param2
        {
            get { return _param2; }
            set
            {
                switch (_cmd)
                {
                    // _______________________________________________________
                    case EnumCmd.App_IfGoto_Strategy:
                    case EnumCmd.App_IfGoto_System:
                        _param2 = value;                                    // Action ID si vrai
                        break;

                    // _______________________________________________________
                    case EnumCmd.App_SetNewPos:
                    case EnumCmd.Mvt_UseDistOnly:
                    case EnumCmd.Mvt_UseMixedMode:
                    case EnumCmd.Mvt_UseSpline:
                        _param2 = CheckIntValue(value, 0, 3000, "1500");    // Position en x
                        break;

                    // _______________________________________________________
                    case EnumCmd.Mvt_UsePivotMode:
                        _param2 = CheckWheelValue(value, "RIGHT_WHEEL");
                        break;

                    // _______________________________________________________
                    case EnumCmd.App_Wait:
                        _param2 = CheckIntValue(value, 0, 59, "0");          // Temps d'attente en minutes
                        break;

                    // _______________________________________________________
                    case EnumCmd.MvtSimple_MoveInMM:
                        _param2 = CheckIntValue(value, -5000, 5000, "0");    // Distance 
                        break;

                    // _______________________________________________________
                    case EnumCmd.App_SetStrategyFlags:
                        _param2 = CheckBooleanValue(value, "OS_FALSE");     // Valeur du flag
                        break;

                    // _______________________________________________________
                    case EnumCmd.Mvt_Stop:
                    case EnumCmd.NotSet:
                    case EnumCmd.Mvt_UseAngleOnly:
                    case EnumCmd.MvtSimple_RotateInDeg:
                    case EnumCmd.MvtSimple_RotateToAngleInDeg:
                    default:
                        _param2 = "NotUsed";
                        break;
                }
            }
        }

        /// <summary>
        /// Accès au param 3 au format String
        /// </summary>
        public String param3
        {
            get { return _param3; }
            set
            {
                switch (_cmd)
                {
                    // _______________________________________________________
                    case EnumCmd.Mvt_UseDistOnly:
                    case EnumCmd.Mvt_UseMixedMode:
                    case EnumCmd.Mvt_UseSpline:
                    case EnumCmd.App_SetNewPos:
                        _param3 = CheckIntValue(value, 0, 2000, "1000");        // Position en y
                        break;

                    // _______________________________________________________
                    case EnumCmd.App_Wait:
                        _param3 = CheckIntValue(value, 0, 59, "0");             // Temps d'attente en sec
                        break;

                    // _______________________________________________________
                    case EnumCmd.App_IfGoto_Strategy:
                    case EnumCmd.App_IfGoto_System:
                        _param3 = value;                                        // Action ID si faux
                        break;

                    // _______________________________________________________
                    case EnumCmd.Mvt_UsePivotMode:
                    case EnumCmd.MvtSimple_MoveInMM:
                    case EnumCmd.App_SetStrategyFlags:
                    case EnumCmd.Mvt_Stop:
                    case EnumCmd.NotSet:
                    case EnumCmd.Mvt_UseAngleOnly:
                    case EnumCmd.MvtSimple_RotateInDeg:
                    case EnumCmd.MvtSimple_RotateToAngleInDeg:
                    default:
                        _param3 = "NotUsed";
                        break;
                }
            }
        }

        /// <summary>
        /// Accès au param 4 au format String
        /// </summary>
        public String param4
        {
            get { return _param4; }
            set
            {
                switch (_cmd)
                {
                    // _______________________________________________________
                    case EnumCmd.Mvt_UseAngleOnly:
                    case EnumCmd.Mvt_UseMixedMode:
                    case EnumCmd.Mvt_UsePivotMode:
                    case EnumCmd.Mvt_UseSpline:
                    case EnumCmd.MvtSimple_RotateInDeg:
                    case EnumCmd.MvtSimple_RotateToAngleInDeg:
                    case EnumCmd.App_SetNewPos:
                        _param4 = CheckAngleValue(value, "0.0");                // Verification de la valeur de l'angle
                        break;

                    // _______________________________________________________
                    case EnumCmd.App_Wait:
                        _param4 = CheckIntValue(value, 0, 99, "0");             // Temps d'attente en msec
                        break;

                    // _______________________________________________________
                    case EnumCmd.Mvt_UseDistOnly:
                    case EnumCmd.App_IfGoto_Strategy:
                    case EnumCmd.App_IfGoto_System:
                    case EnumCmd.MvtSimple_MoveInMM:
                    case EnumCmd.App_SetStrategyFlags:
                    case EnumCmd.Mvt_Stop:
                    case EnumCmd.NotSet:
                    default:
                        _param4 = "NotUsed";
                        break;
                }
            }
        }

        /// <summary>
        /// Accès au paramètre activeSensors
        /// </summary>
        public EnumActiveSensors activeSensors
        {
            get { return _activeSensors; }
            set
            {
                switch (_cmd)
                {
                    // _______________________________________________________
                    case EnumCmd.Mvt_UseAngleOnly:
                    case EnumCmd.Mvt_UseMixedMode:
                    case EnumCmd.Mvt_UsePivotMode:
                    case EnumCmd.Mvt_UseSpline:
                    case EnumCmd.MvtSimple_RotateInDeg:
                    case EnumCmd.MvtSimple_RotateToAngleInDeg:
                    case EnumCmd.Mvt_UseDistOnly:
                    case EnumCmd.MvtSimple_MoveInMM:
                    case EnumCmd.Mvt_Stop:
                        _activeSensors = value;
                        break;

                    // _______________________________________________________
                    case EnumCmd.App_Wait:
                    case EnumCmd.App_SetNewPos:
                    case EnumCmd.App_IfGoto_Strategy:
                    case EnumCmd.App_IfGoto_System:
                    case EnumCmd.App_SetStrategyFlags:
                    case EnumCmd.NotSet:
                    default:
                        _activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;
                        break;
                }
            }
        }

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
                    param1 = "(true == true)";                         // Test
                    param2 = "-1";                                     // nextID si le test est vrai
                    param3 = "-1";                                     // nextID si le test est faux
                    param4 = null;                                     // Not Used
                    activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.App_SetNewPos:
                    param1 = "1500";                                   // Position en x
                    param2 = "1000";                                   // Position en y
                    param3 = "-90";                                    // Angle
                    param4 = null;                                     // Not Set
                    activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;  // Pas de sensors d'activé
                    break;
                    
                // _______________________________________________________
                case EnumCmd.App_SetStrategyFlags:
                    param1 = EnumStrategyFlags.NotSet.ToString();      // Flag à modifier
                    param2 = "OS_FALSE";                               // Nouvelle valeur du flag
                    param3 = null;                                     // Not Set
                    param4 = null;                                     // Not Set
                    activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.App_Wait:
                    param1 = "0";                                      // Temps d'attente en heure
                    param2 = "0";                                      // Temps d'attente en minute
                    param3 = "5";                                      // Temps d'attente en sec
                    param4 = "0";                                      // Temps d'attente en msec
                    activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.Mvt_Stop:
                    param1 = null;                                     // Not Used
                    param2 = null;                                     // Not Used
                    param3 = null;                                     // Not Used
                    param4 = null;                                     // Not Used
                    activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.Mvt_UseAngleOnly:
                case EnumCmd.MvtSimple_RotateInDeg:
                case EnumCmd.MvtSimple_RotateToAngleInDeg:
                    param1 = "DEFAULT_SPEED";                          // Vitesse du déplacement
                    param2 = null;                                     // Not Used
                    param3 = null;                                     // Not Used
                    param4 = "0";                                      // Angle
                    activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.Mvt_UseDistOnly:
                    param1 = "DEFAULT_SPEED";                          // Vitesse du déplacement
                    param2 = "1500";                                   // Position en x
                    param3 = "1000";                                   // Position en y
                    param4 = null;                                     // Not Used
                    activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.Mvt_UseMixedMode:
                case EnumCmd.Mvt_UseSpline:
                    param1 = "DEFAULT_SPEED";                          // Vitesse du déplacement
                    param2 = "1500";                                   // Position en x
                    param3 = "1000";                                   // Position en y
                    param4 = "0";                                      // Angle
                    activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.Mvt_UsePivotMode:
                    param1 = "DEFAULT_SPEED";                          // Vitesse du déplacement
                    param2 = "RIGHT_WHEEL";                            // Roue bloquée
                    param3 = null;                                     // Not Used
                    param4 = "0";                                      // Angle
                    activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.MvtSimple_MoveInMM:
                    param1 = "DEFAULT_SPEED";                          // Vitesse du déplacement
                    param2 = "100";                                    // Distance en mm
                    param3 = null;                                     // Not Used
                    param4 = null;                                     // Not Used
                    activeSensors = EnumActiveSensors.APP_PARAM_STRATEGYFLAG_NONE;  // Pas de sensors d'activé
                    break;

                // _______________________________________________________
                case EnumCmd.NotSet:
                default:
                    param1 = null;                                    // Not Used
                    param2 = null;                                     // Not Used
                    param3 = null;                                     // Not Used
                    param4 = null;                                     // Not Used
                    activeSensors = EnumActiveSensors.NotSet;          // Not Used
                    break;
             }
        }

        /// <summary>
        /// Fonction pour verifier la valeur du paramètre Int
        /// </summary>
        /// <param name="valueToCheck">Valeur à tester</param>
        /// <param name="valueMin">Valeur minimale</param>
        /// <param name="valueMax">Valeur maximale</param>
        /// <param name="defaultValue">Valeur à utiliser en cas de valeur non valide</param>
        /// <returns>La valeur verifiée ou la valeur par défaut</returns>
        private String CheckIntValue(String valueToCheck, int valueMin, int valueMax, String defaultValue)
        {
            int valueToCheckInt = 0;
            String Ret = defaultValue;
 
            try
            {
                // On essaye de convertir la valeur String en Int
                valueToCheckInt = Convert.ToInt32(valueToCheck);

                // On verifie la valeur en fonction des seuils
                if ((valueToCheckInt >= valueMin) && (valueToCheckInt <= valueMax))
                {
                    Ret = valueToCheckInt.ToString();
                }
                else
                {
                    // La valeur n'est pas valable, on retourne la valeur par défaut
                    Ret = defaultValue;
                }
            }
            catch (Exception)
            {
                // En cas d'erreur lors de la conversion
                Ret = defaultValue;
            }

            return Ret;
        }

        /// <summary>
        /// Fonction pour verifier la valeur du paramètre StrategyFlags
        /// </summary>
        /// <param name="valueToCheck">Valeur à tester</param>
        /// <param name="defaultValue">Valeur à utiliser en cas de valeur non valide</param>
        /// <returns>La valeur verifiée ou la valeur par défaut</returns>
        private String CheckStrategyFlagsValue(String valueToCheck, String defaultValue)
        {
            String Ret = defaultValue;
 
            try
            {
                foreach(EnumStrategyFlags currentValue in Enum.GetValues(typeof(EnumStrategyFlags)))
                {
                    if(currentValue.ToString() == valueToCheck)
                        Ret = currentValue.ToString();
                }
            }
            catch (Exception)
            {
                Ret = defaultValue;
            }

            return Ret;
        }

        /// <summary>
        /// Fonction pour verifier la valeur du paramètre Boolean
        /// </summary>
        /// <param name="valueToCheck">Valeur à tester</param>
        /// <param name="defaultValue">Valeur à utiliser en cas de valeur non valide</param>
        /// <returns>La valeur verifiée ou la valeur par défaut</returns>
        private String CheckBooleanValue(String valueToCheck, String defaultValue)
        {
            String Ret = defaultValue;

            try
            {
                if ((valueToCheck.ToUpper() == "OS_TRUE") || (valueToCheck.ToUpper() == "TRUE"))
                    Ret = "OS_TRUE";

                if ((valueToCheck.ToUpper() == "OS_FALSE") || (valueToCheck.ToUpper() == "FALSE"))
                    Ret = "OS_FALSE";
            }
            catch (Exception)
            {
                Ret = defaultValue;
            }

            return Ret;
        }

        /// <summary>
        /// Fonction pour verifier la valeur de la roue de pivot
        /// </summary>
        /// <param name="valueToCheck">Valeur à tester</param>
        /// <param name="defaultValue">Valeur à utiliser en cas de valeur non valide</param>
        /// <returns>La valeur verifiée ou la valeur par défaut</returns>
        private String CheckWheelValue(String valueToCheck, String defaultValue)
        {
            String Ret = defaultValue;

            try
            {
                if ((valueToCheck.ToUpper() == "LEFT_WHEEL") || (valueToCheck.ToUpper() == "RIGHT_WHEEL"))
                    Ret = valueToCheck.ToUpper();
            }
            catch
            {
                Ret = defaultValue;
            }

            return Ret;
        }

        /// <summary>
        /// Fonction pour verifier la valeur de l'angle en paramètre
        /// </summary>
        /// <param name="valueToCheck">Valeur à tester</param>
        /// <param name="defaultValue">Valeur à utiliser en cas de valeur non valide</param>
        /// <returns>Retourne une valeur entre -180° et +180°</returns>
        private String CheckAngleValue(String valueToCheck, String defaultValue)
        {
            String ret = defaultValue;
            int retInt = 0;

            try
            {

                retInt = Convert.ToInt32(valueToCheck);

                // Verification des valeurs > 360°
                while (retInt > 180)
                    retInt = retInt - 360;

                // Verification des valeurs <= 360°
                while (retInt <= -180)
                    retInt = retInt + 360;

                // Création de la chaine de retour
                ret = retInt.ToString();

               }
            catch
            {
                ret = defaultValue;
            }

            return ret;

        }

        /// <summary>
        /// Fonction pour verifier la valeur de la commande passée en paramètre
        /// </summary>
        /// <param name="valueToCheck">Valeur à tester</param>
        /// <param name="defaultValue">Valeur à utiliser en cas de valeur non valide</param>
        /// <returns>La commande verifiée</returns>
        private EnumCmd CheckEnumCmdValue(String valueToCheck, EnumCmd defaultValue)
        {
            EnumCmd Ret = defaultValue;

            try
            {
                foreach (EnumCmd currentValue in Enum.GetValues(typeof(EnumCmd)))
                {
                    if (currentValue.ToString() == valueToCheck)
                        Ret = currentValue;
                }
            }
            catch (Exception)
            {
                Ret = defaultValue;
            }

            return Ret;
        }

        /// <summary>
        /// Fonction pour verifier la valeur du type de commande passé en paramètre
        /// </summary>
        /// <param name="valueToCheck">Valeur à tester</param>
        /// <param name="defaultValue">Valeur à utiliser en cas de valeur non valide</param>
        /// <returns>Le type de commande verifié</returns>
        private EnumCmdType CheckEnumCmdTypeValue(String valueToCheck, EnumCmdType defaultValue)
        {
            EnumCmdType Ret = defaultValue;

            try
            {
                foreach (EnumCmdType currentValue in Enum.GetValues(typeof(EnumCmdType)))
                {
                    if (currentValue.ToString() == valueToCheck)
                        Ret = currentValue;
                }
            }
            catch (Exception)
            {
                Ret = defaultValue;
            }

            return Ret;
        }

        /// <summary>
        /// Fonction pour verifier la valeur l'active sensors passé en paramètre
        /// </summary>
        /// <param name="valueToCheck">Valeur à tester</param>
        /// <param name="defaultValue">Valeur à utiliser en cas de valeur non valide</param>
        /// <returns>ActiveSensors</returns>
        private EnumActiveSensors CheckEnumActiveSensorsValue(String valueToCheck, EnumActiveSensors defaultValue)
        {
            EnumActiveSensors Ret = defaultValue;
            
            try
            {
                foreach (EnumActiveSensors currentValue in Enum.GetValues(typeof(EnumActiveSensors)))
                {
                    if (currentValue.ToString() == valueToCheck)
                        Ret = currentValue;
                }
            }
            catch (Exception)
            {
                Ret = defaultValue;
            }

            return Ret;
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
        private int _nextID;                            // Action suivante
        private int _timeoutID;                         // Action à réaliser en cas de timeout

        private struct ExchangeTag
        {
            public const String uID = "UID";
            public const String cmd = "Cmd";
            public const String cmdType = "CmdType";
            public const String param1 = "Param1";
            public const String param2 = "Param2";
            public const String param3 = "Param3";
            public const String param4 = "Param4";
            public const String activeSensors = "ActiveSensors";
            public const String nextID = "nextID";
            public const String timeoutID = "timeoutID";
        }

    }
}
