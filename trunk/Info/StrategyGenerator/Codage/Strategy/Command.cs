using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator.Strategy
{
    enum EnumCmd
    {
        NotSet                              = 0,	// Current Cmd is not set
        // Command MVT _________________________
        Mvt_UseAngleOnly                    = 10,	// Use Asser Mode 1
        Mvt_UseDistOnly                     = 11,	// Use Asser Mode 2
        Mvt_UseMixedMode                    = 12,	// Use Asser Mode 3
        Mvt_UsePivotMode                    = 13,	// Use Asser Mode 4
        MvtSimple_MoveInMM                  = 14,	// Use a simple mvt for moving in MM (don't divide this mvt)
        MvtSimple_RotateInDeg               = 15,	// Use a simple mvt for rotating in deg (don't divide this mvt)
        MvtSimple_RotateToAngleInDeg        = 16,	// Use a simple mvt for rotating to a specified angle in deg (don't divide this mvt)
        Mvt_Stop                            = 17,   // Used to stop current mvt
        // Command APP _________________________
        App_Wait                            = 20,	// Wait (if all params = 0, wait for ever)
        App_IfGoto_System                   = 21,	// Go to a specific step based on System Flags
        App_IfGoto_Strategy                 = 22,	// Go to a specific step based on Strategy Flags
        App_SetNewPos                       = 23,	// Msg used to define a new position
        App_SetStrategyFlags                = 24,	// Set the stratgey flags
        // Cmd Modif : Add new command here ____
        Sensors_ArmsOpenDown                = 30,	// Open arms (Use for grabbing objects on floor)
        Sensors_ArmsOpenUp                  = 31,	// Open arms (Use for grabbing objects on totem)
        Sensors_ArmsDeployment              = 32,	// Open arms with delay 
        Sensors_ArmsOpenTotem               = 33,	// Open arms (Use for the arrival on the totem) 
        Sensors_ArmsOpenOneCD               = 34,	// Open arms (Use for grabbing only one CD)
        Sensors_ArmsClose                   = 35,	// Close arms (Use for keeping objects into arms)
        Sensors_ArmsCloseTotem              = 36,	// Close arms (Use for keeping objects into arms on totem (elevator is up))
        Sensors_ArmsUngrab                  = 37,	// Open arms for putting down the objects
    }

    enum EnumCmdType
    {
        NotSet = 0,         // Undefined CmdType
	    Blocking,			// Command is a blocking action
	    NonBlocking,		// Command is a non-blocking action
    }

    enum EnumSensorsFlag
    {
        // APP_PARAM_
        APPFLAG_NONE            = 0,
        APPFLAG_SENSORS_FRONT   = 10,
        APPFLAG_SENSORS_BACK    = 11,
        APPFLAG_SENSORS_LEFT    = 12,
        APPFLAG_SENSORS_RIGHT   = 13,
        APPFLAG_ALL_GP2         = 20,
        APPFLAG_ALL_SW          = 21,
        APPFLAG_ALL_SENSORS     = 22
    }

    /// <summary>
    /// Command is an object that contains all data for doing an action
    /// </summary>
    class Command
    {
        // Constructeur ---------------------------------------------------------------------------
        /// <summary>
        /// Default constructor : Create an empty command
        /// </summary>
        public Command()
        {
            Update(EnumCmd.NotSet, EnumCmdType.NotSet, null, null, null, null, EnumSensorsFlag.APPFLAG_NONE);
            return;
        }

        /// <summary>
        /// Create a new 'Cmd' command
        /// Default values are used for CmdType and Params
        /// </summary>
        public Command(EnumCmd Cmd)
        {
            Update(Cmd, EnumCmdType.NotSet, null, null, null, null, EnumSensorsFlag.APPFLAG_NONE);
            return;
        }

        /// <summary>
        /// Create a new 'Cmd' command with the 'CmdType' type
        /// Default value is used Params
        /// </summary>
        public Command(EnumCmd Cmd, EnumCmdType CmdType)
        {
            Update(Cmd, CmdType, null, null, null, null, EnumSensorsFlag.APPFLAG_NONE);
            return;
        }

        /// <summary>
        /// Create a new 'Cmd' command with the 'CmdType' type and 'Params' parameters
        /// </summary>
        public Command(EnumCmd Cmd, EnumCmdType CmdType, String Param1, String Param2, String Param3, String Param4)
        {
            Update(Cmd, CmdType, Param1, Param2, Param3, Param4, EnumSensorsFlag.APPFLAG_NONE);
            return;
        }

        /// <summary>
        /// Create a new 'Cmd' command with the 'CmdType' type, 'Params' parameters and ActiveSensors parameters
        /// </summary>
        public Command(EnumCmd Cmd, EnumCmdType CmdType, String Param1, String Param2, String Param3, String Param4, EnumSensorsFlag ActiveSensors)
        {
            Update(Cmd, CmdType, Param1, Param2, Param3, Param4, ActiveSensors);
            return;
        }

        // Public ---------------------------------------------------------------------------------
        public EnumCmd Cmd
        {
            get { return _Cmd; }
        }
        
        public EnumCmdType CmdType
        {
            get { return _CmdType;}
            set { _CmdType = value;}
        }

        public String Param1                    { get { return _Param1; } }
        public String Param2                    { get { return _Param2; } }
        public String Param3                    { get { return _Param3; } }
        public String Param4                    { get { return _Param4; } }
        public EnumSensorsFlag ActiveSensors    { get { return _ActiveSensorsFlag; } }

        /// <summary>
        /// Update the current command with the given data
        /// </summary>
        /// <param name="Cmd">Command</param>
        /// <param name="CmdType">Command Type</param>
        /// <param name="Param1">Param 1</param>
        /// <param name="Param2">Param 2</param>
        /// <param name="Param3">Param 3</param>
        /// <param name="Param4">Param 4</param>
        /// <param name="ActiveSensors"></param>
        /// <returns></returns>
        public bool Update(EnumCmd Cmd, EnumCmdType CmdType, String Param1, String Param2, String Param3, String Param4, EnumSensorsFlag ActiveSensors)
        {
            bool Ret = false;

            // Init Cmd to the default value
            _Cmd = EnumCmd.NotSet;
            _CmdType = EnumCmdType.NotSet;
            _Param1 = null;
            _Param2 = null;
            _Param3 = null;
            _Param4 = null;

            if (ActiveSensors != EnumSensorsFlag.APPFLAG_NONE)
                _ActiveSensorsFlag = ActiveSensors;

            _Cmd = Cmd;
            _CmdType = CmdType;

            // Check Params for Cmd
            // Cmd Modif : Add new command here
            switch (Cmd)
            {
                // ________________________________________________________ Param1 / Param2
                case EnumCmd.MvtSimple_MoveInMM:
                case EnumCmd.App_SetStrategyFlags:
                    if ((Param1 != null) && (Param2 != null))
                    {
                        _Param1 = Param1;
                        _Param2 = Param2;
                        Ret = true;
                    }
                    else
                    {
                        LoadDefaultParamsValue();
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ Param1 / Param4
                case EnumCmd.Mvt_UseAngleOnly:
                case EnumCmd.MvtSimple_RotateInDeg:
                case EnumCmd.MvtSimple_RotateToAngleInDeg:
                    if ((Param1 != null) && (Param4 != null))
                    {
                        _Param1 = Param1;
                        _Param4 = Param4;
                        Ret = true;
                    }
                    else
                    {
                        LoadDefaultParamsValue();
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ Param1 / Param2 / Param3
                case EnumCmd.Mvt_UseDistOnly:
                case EnumCmd.App_IfGoto_System:
                case EnumCmd.App_IfGoto_Strategy:
                    if ((Param1 != null) && (Param2 != null) && (Param3 != null))
                    {
                        _Param1 = Param1;
                        _Param2 = Param2;
                        _Param3 = Param3;
                        Ret = true;
                    }
                    else
                    {
                        LoadDefaultParamsValue();
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ Param1 / Param2 / Param4
                case EnumCmd.Mvt_UsePivotMode:
                    if ((Param1 != null) && (Param2 != null) && (Param4 != null))
                    {
                        _Param1 = Param1;
                        _Param2 = Param2;
                        _Param4 = Param4;
                        Ret = true;
                    }
                    else
                    {
                        LoadDefaultParamsValue();
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ Param2 / Param3 / Param4
                case EnumCmd.App_SetNewPos:
                    if ((Param2 != null) && (Param3 != null) && (Param4 != null))
                    {
                        _Param2 = Param2;
                        _Param3 = Param3;
                        _Param4 = Param4;
                        Ret = true;
                    }
                    else
                    {
                        LoadDefaultParamsValue();
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ Param1 / Param2 / Param3 / Param4
                case EnumCmd.Mvt_UseMixedMode:
                case EnumCmd.App_Wait:
                    if ((Param1 != null) && (Param2 != null) && (Param3 != null) && (Param4 != null))
                    {
                        _Param1 = Param1;
                        _Param2 = Param2;
                        _Param3 = Param3;
                        _Param4 = Param4;
                        Ret = true;
                    }
                    else
                    {
                        LoadDefaultParamsValue();
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ None
                case EnumCmd.Mvt_Stop:
                case EnumCmd.Sensors_ArmsClose:
                case EnumCmd.Sensors_ArmsCloseTotem:
                case EnumCmd.Sensors_ArmsOpenDown:
                case EnumCmd.Sensors_ArmsOpenUp:
                case EnumCmd.Sensors_ArmsOpenOneCD:
                case EnumCmd.Sensors_ArmsOpenTotem:
                case EnumCmd.Sensors_ArmsUngrab:
                    Ret = true;
                    break;  

                // ________________________________________________________
                default:
                    break;
            }

            return Ret;

        }

        // Static functions ----------------------------------------------------------------------
        /// <summary>
        /// Get the Command from a string
        /// </summary>
        /// <param name="CmdString">String that contains the expected command</param>
        /// <returns>An EnumCmd object</returns>
        public static EnumCmd GetCmdFromString(String CmdString)
        {
            foreach (EnumCmd ECmd in Enum.GetValues(typeof(EnumCmd)))
            {
                if (ECmd.ToString().ToUpper() == CmdString.ToUpper())
                    return ECmd;
            }

            return EnumCmd.NotSet;
        }

        /// <summary>
        /// Get the Command into String
        /// </summary>
        /// <param name="Cmd">Command we have to export into a string</param>
        /// <returns>A string that contains the command into a string</returns>
        public static String GetCmdToString(EnumCmd Cmd)
        {
            foreach (EnumCmd ECmd in Enum.GetValues(typeof(EnumCmd)))
            {
                if (Cmd == ECmd)
                    return ECmd.ToString();
            }

            return EnumCmd.NotSet.ToString();
        }

        /// <summary>
        /// Get the Command Type from a string
        /// </summary>
        /// <param name="CmdTypeString">String that contains the expected command type</param>
        /// <returns>An EnumCmdType object</returns>
        public static EnumCmdType GetCmdTypeFromString(String CmdTypeString)
        {
            // App
            if ("CmdType_Blocking".ToUpper() == CmdTypeString.ToUpper()) { return EnumCmdType.Blocking; }
            if ("Blocking".ToUpper() == CmdTypeString.ToUpper()) { return EnumCmdType.Blocking; }
            if ("CmdType_NonBlocking".ToUpper() == CmdTypeString.ToUpper()) { return EnumCmdType.NonBlocking; }
            if ("NonBlocking".ToUpper() == CmdTypeString.ToUpper()) { return EnumCmdType.NonBlocking; }

            return EnumCmdType.NotSet;
        }

        /// <summary>
        /// Get the Command Type into a string
        /// </summary>
        /// <param name="CmdTypeString">String that contains the expected command type</param>
        /// <returns>An EnumCmdType object</returns>
        public static String GetCmdTypeToString(EnumCmdType CmdType)
        {
            // App
            if (EnumCmdType.Blocking == CmdType) { return "CmdType_Blocking"; }
            if (EnumCmdType.NonBlocking == CmdType) { return "CmdType_NonBlocking"; }

            return "CmdType_NotSet";
        }

        public static EnumSensorsFlag GetSensorsFlagFromString(String SensorsFlagString)
        {
            String SensorsStringToCheck = SensorsFlagString.Replace("APP_PARAM_", "");

            foreach (EnumSensorsFlag ESensorsFlag in Enum.GetValues(typeof(EnumSensorsFlag)))
            {
                if (SensorsStringToCheck == ESensorsFlag.ToString())
                    return ESensorsFlag;
            }

            return EnumSensorsFlag.APPFLAG_NONE;
        }

        public static String GetSensorsFlagToString(EnumSensorsFlag SensorsFlag)
        {
            return ("APP_PARAM_" + SensorsFlag.ToString());
        }

        /// <summary>
        /// Get the Params List from a string
        /// </summary>
        /// <param name="ParamsListString">String that contains the params list</param>
        /// <returns>A list of Params</returns>
        public static string [] GetParamsListFromString(String ParamsListString)
        {
            string [] ParamsList = new string[4];
            string [] ParsedString = null;

            if (ParamsListString != null)
            {
                // First parse the current string 
                ParsedString = ParamsListString.Replace(" ", "").Split(';', '>');

                // Analyse all items
                foreach (string s in ParsedString)
                {
                    // Search for "Param" string
                    if ((s.Length > 5) && (s.Substring(0,5) == "Param"))
                    {
                        int ParamID = int.Parse(s.Substring(5, 1)) - 1;
                        if (ParamID < 0) { ParamID = 0; };
                        
                        ParamsList[ParamID] = s.Substring(7);
                    }
                }

            }

            return ParamsList;
        }

        /// <summary>
        /// Export all params into a string
        /// </summary>
        /// <returns>A string that contains all params</returns>
        public String ExportParamsIntoString()
        {
            String Result = "";
            
            // Create the string that contains all data
            if (_Param1 != null)
                Result = Result + "p->Param1 = " + _Param1 + ";    ";

            if (_Param2 != null)
                Result = Result + "p->Param2 = " + _Param2 + ";    ";

            if (_Param3 != null)
                Result = Result + "p->Param3 = " + _Param3 + ";    ";

            if (_Param4 != null)
                Result = Result + "p->Param4 = " + _Param4 + ";    ";

            return Result;
        }

        private void LoadDefaultParamsValue()
        {
            // Check Params for Cmd
            switch (_Cmd)
            {
                default:
                    _Param1 = "0";
                    _Param2 = "0";
                    _Param3 = "0";
                    _Param4 = "0";
                    break;
            }
        }

        // Private --------------------------------------------------------------------------------
        private EnumCmdType _CmdType;
        private EnumSensorsFlag _ActiveSensorsFlag;
        private EnumCmd _Cmd;
        private String _Param1;
        private String _Param2;
        private String _Param3;
        private String _Param4;

    }
}
