using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator.Strategy
{
    enum EnumCmd
    {
        NotSet                              = 0,	// Current Cmd is not set
        // Command MVT ______________________
        Mvt_UseAngleOnly                    = 10,	// Use Asser Mode 1
        Mvt_UseDistOnly                     = 11,	// Use Asser Mode 2
        Mvt_UseMixedMode                    = 12,	// Use Asser Mode 3
        Mvt_UsePivotMode                    = 13,	// Use Asser Mode 4
        MvtSimple_MoveInMM                  = 14,	// Use a simple mvt for moving in MM (don't divide this mvt)
        MvtSimple_RotateInDeg               = 15,	// Use a simple mvt for rotating in deg (don't divide this mvt)
        MvtSimple_RotateToAngleInDeg        = 16,	// Use a simple mvt for rotating to a specified angle in deg (don't divide this mvt)
        Mvt_Stop                            = 17,   // Used to stop current mvt
        // Command APP ______________________
        App_Wait                            = 20,	// Wait (if all params = 0, wait for ever)
        App_IfGoto                          = 21,	// Go to a specific step
        App_SetNewPos                       = 22,	// Msg used to define a new position
    }

    enum EnumCmdType
    {
        NotSet = 0,         // Undefined CmdType
	    Blocking,			// Command is a blocking action
	    NonBlocking,		// Command is a non-blocking action
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
            Update(EnumCmd.NotSet, EnumCmdType.NotSet, null, null, null, null);
            return;
        }

        /// <summary>
        /// Create a new 'Cmd' command
        /// Default values are used for CmdType and Params
        /// </summary>
        public Command(EnumCmd Cmd)
        {
            Update(Cmd, EnumCmdType.NotSet, null, null, null, null);
            return;
        }

        /// <summary>
        /// Create a new 'Cmd' command with the 'CmdType' type
        /// Default value is used Params
        /// </summary>
        public Command(EnumCmd Cmd, EnumCmdType CmdType)
        {
            Update(Cmd, CmdType, null, null, null, null);
            return;
        }

        /// <summary>
        /// Create a new 'Cmd' command with the 'CmdType' type and 'Params' parameters
        /// </summary>
        public Command(EnumCmd Cmd, EnumCmdType CmdType, String Param1, String Param2, String Param3, String Param4)
        {
            Update(Cmd, CmdType, Param1, Param2, Param3, Param4);
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
            set { _CmdType = CmdType;}
        }

        /// <summary>
        /// Update the current command with the given data
        /// </summary>
        public bool Update(EnumCmd Cmd, EnumCmdType CmdType, String Param1, String Param2, String Param3, String Param4)
        {
            bool Ret = false;

            // Init Cmd to the default value
            _Cmd = EnumCmd.NotSet;
            _CmdType = EnumCmdType.NotSet;
            _Param1 = null;
            _Param2 = null;
            _Param3 = null;
            _Param4 = null;
            
            // Check Params for Cmd
            switch (Cmd)
            {
                // ________________________________________________________ Param1 / Param2
                case EnumCmd.MvtSimple_MoveInMM:
                case EnumCmd.MvtSimple_RotateInDeg:
                    if ((Param1 != null) && (Param2 != null))
                    {
                        _Cmd = Cmd;
                        _CmdType = CmdType;
                        _Param1 = Param1;
                        _Param2 = Param2;
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ Param1 / Param4
                case EnumCmd.Mvt_UseAngleOnly:
                    if ((Param1 != null) && (Param4 != null))
                    {
                        _Cmd = Cmd;
                        _CmdType = CmdType;
                        _Param1 = Param1;
                        _Param4 = Param4;
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ Param1 / Param2 / Param3
                case EnumCmd.Mvt_UseDistOnly:
                case EnumCmd.App_IfGoto:
                    if ((Param1 != null) && (Param2 != null) && (Param3 != null))
                    {
                        _Cmd = Cmd;
                        _CmdType = CmdType;
                        _Param1 = Param1;
                        _Param2 = Param2;
                        _Param3 = Param3;
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ Param1 / Param2 / Param4
                case EnumCmd.Mvt_UsePivotMode:
                    if ((Param1 != null) && (Param2 != null) && (Param4 != null))
                    {
                        _Cmd = Cmd;
                        _CmdType = CmdType;
                        _Param1 = Param1;
                        _Param2 = Param2;
                        _Param4 = Param4;
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ Param2 / Param3 / Param4
                case EnumCmd.App_SetNewPos:
                    if ((Param2 != null) && (Param3 != null) && (Param4 != null))
                    {
                        _Cmd = Cmd;
                        _CmdType = CmdType;
                        _Param2 = Param2;
                        _Param3 = Param3;
                        _Param4 = Param4;
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ Param1 / Param2 / Param3 / Param4
                case EnumCmd.Mvt_UseMixedMode:
                case EnumCmd.App_Wait:
                    if ((Param1 != null) && (Param2 != null) && (Param3 != null) && (Param4 != null))
                    {
                        _Cmd = Cmd;
                        _CmdType = CmdType;
                        _Param1 = Param1;
                        _Param2 = Param2;
                        _Param3 = Param3;
                        _Param4 = Param4;
                        Ret = true;
                    }
                    break;

                // ________________________________________________________ None
                case EnumCmd.Mvt_Stop:
                    _Cmd = Cmd;
                    _CmdType = CmdType;
                    Ret = true;
                    break;  

                // ________________________________________________________
                default:
                    break;
            }

            return Ret;

        }

        // Private --------------------------------------------------------------------------------
        private EnumCmdType _CmdType;
        private CommandActiveSensorsFlag _ActiveSensorsFlag;
        private Int16 _NextActionID;
        private EnumCmd _Cmd;
        private String _Param1;
        private String _Param2;
        private String _Param3;
        private String _Param4;

    }
}
