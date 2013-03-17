using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.StrategyManager
{
    public enum EnumCmd
    {
        NotSet = 0,	// Current Cmd is not set
        // Command MVT _________________________
        Mvt_UseAngleOnly = 10,	                    // Use Asser Mode 1
        Mvt_UseDistOnly = 11,	                    // Use Asser Mode 2
        Mvt_UseMixedMode = 12,	                    // Use Asser Mode 3
        Mvt_UsePivotMode = 13,	                    // Use Asser Mode 4
        Mvt_UseSpline = 14,	                        // Send the expected point directly to the task asser (without computation)
        MvtSimple_MoveInMM = 15,	                // Use a simple mvt for moving in MM (don't divide this mvt)
        MvtSimple_RotateInDeg = 16,	                // Use a simple mvt for rotating in deg (don't divide this mvt)
        MvtSimple_RotateToAngleInDeg = 17,	        // Use a simple mvt for rotating to a specified angle in deg (don't divide this mvt)
        Mvt_Stop = 18,                              // Used to stop current mvt

        // Command APP _________________________
        App_Wait = 30,	                            // Wait (if all params = 0, wait for ever)
        App_IfGoto_System = 31,	                    // Go to a specific step based on System Flags
        App_IfGoto_Strategy = 32,	                // Go to a specific step based on Strategy Flags
        App_SetNewPos = 33,	                        // Msg used to define a new position
        App_SetStrategyFlags = 34,	                // Set the stratgey flags
        
        // Cmd SENSORS __________________________

    }

    public enum EnumCmdType
    {
        NotSet = 0,         // Undefined CmdType
        Blocking,			// Command is a blocking action
        NonBlocking,		// Command is a non-blocking action
    }

    public enum EnumActiveSensors
    {
        NotSet = 0,
        // Sensors COLLISION ____________________
        COLLISION_NONE = 10,
        COLLISION_FRONT = 11,
        COLLISION_REAR = 12,
        COLLISION_LEFT = 13,
        COLLISION_RIGHT = 14,
    }

    public enum EnumStrategyFlags
    {
        NotSet = 0,
    }

}
