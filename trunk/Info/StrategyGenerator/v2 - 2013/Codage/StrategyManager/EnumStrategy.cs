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
        Sensors_SetHoopLevel = 40,                  // Function to move Rear Hoop
        Sensors_SetArmsStatus = 41,                 // Function to set Arms position
    }

    public enum EnumCmdType
    {
        CmdType_NotSet = 0,         // Undefined CmdType
        CmdType_Blocking,			// Command is a blocking action
        CmdType_NonBlocking,		// Command is a non-blocking action
    }

    public enum EnumAppParamStrategyFlags
    {
        NONE  = 0,
        // Actions Done ______________________________________________					
        BIT00 = 100,
        BIT01 = 101,
        BIT02 = 102,
        BIT03 = 103,
        BIT04 = 104,
        BIT05 = 105,
        BIT06 = 106,
        BIT07 = 107,
        BIT08 = 108,
        BIT09 = 109,
        BIT10 = 110,
        BIT11 = 111,
        BIT12 = 112,
        BIT13 = 113,
        BIT14 = 114,
        BIT15 = 115,
        // Valid Zone ______________________________________________					
        BIT16 = 116,
        BIT17 = 117,
        BIT18 = 118,
        BIT19 = 119,
        BIT20 = 120,
        BIT21 = 121,
        BIT22 = 122,
        BIT23 = 123,
        // State Flag ______________________________________________					
        // ReadOnly : COLLISION_FRONT = 124,
        // ReadOnly : COLLISION_REAR = 125,
        // ReadOnly : COLLISION_LEFT = 126,
        // ReadOnly : COLLISION_RIGHT = 127,
        // ReadOnly : COLLISION_REAR_LONG = 128,
        REAR_HOOPS_DOWN = 129,
        // ReadOnly : COLLISION_FRONT_LEFT = 130,
        // ReadOnly : COLLISION_FRONT_RIGHT = 131,
    }

    public enum EnumCollisionSensors
    {
        COLLISION_FRONT = 201,
        COLLISION_FRONT_LEFT = 202,
        COLLISION_FRONT_RIGHT = 203,
        COLLISION_LEFT = 204,
        COLLISION_RIGHT = 205,
        COLLISION_REAR = 206,
        COLLISION_LONG_REAR = 207,
    }

    public enum EnumSensorsHoopLevel
    {
        HOOP_LEVEL_UP = 20,
        HOOP_LEVEL_DOWN = 21,
    }

    public enum EnumSensorsArmStatus
    {
        ARM_OPEN = 30,
        ARM_CLOSED = 31,
        ARM_FRONT = 32,
    }

}
