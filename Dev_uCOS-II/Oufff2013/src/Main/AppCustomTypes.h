/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : AppCustomTypes.h
*********************************************************************************************************
*/

#ifndef APPCUSTOMTYPES_H
#define APPCUSTOMTYPES_H

// DEFINE ################################################################
#define	WAIT_FOREVER							0		// Define for Timeout

#define RIGHT_WHEEL								1		// Used for pivot mode
#define LEFT_WHEEL								-1		// Used for pivot mode

#define HOOP_UP									1		// Hoop position 
#define HOOP_DOWN								2		// Hoop position

#define USE_CURRENT_VALUE						-9999	// Used into Cmd msg to indicate we want to keep current value 
														// (Thus no computation is needed for this param)

#define CURRENT_STATE__MOVING					0		// Current Odo state is moving
#define CURRENT_STATE__STOP    					1       // Current Odo state is set to "STOP"

// ERROR CODES ###########################################################
// Global ---------------------------------------
#define ERR__NO_ERROR							0				// No error
#define ERR__INVALID_PARAM						1				// Parameter given is not valid
#define ERR__NO_MORE_DATA_AVAILABLE				2				// There is no more data


// ENUM ##################################################################
// Color ----------------------------------------
typedef enum
{
	c_NotSet = -1,
	c_ColorA,					// Red
	c_ColorB,					// Purple
}EnumColor;

// Mvt Mode -------------------------------------
typedef enum
{
	NotSet							= 0,	// Current Cmd is not set
	// Command MVT ______________________
	Mvt_UseAngleOnly				= 10,	// Use Asser Mode 1
	Mvt_UseDistOnly					= 11,	// Use Asser Mode 2
	Mvt_UseMixedMode				= 12,	// Use Asser Mode 3
	Mvt_UsePivotMode				= 13,	// Use Asser Mode 4
	Mvt_UseSpline					= 14,	// Send the expected point directly to the task asser (without computation)
	MvtSimple_MoveInMM				= 15,	// Use a simple mvt for moving in MM (don't divide this mvt)
	MvtSimple_RotateInDeg			= 16,	// Use a simple mvt for rotating in deg (don't divide this mvt)
	MvtSimple_RotateToAngleInDeg	= 17,	// Use a simple mvt for rotating to a specified angle in deg (don't divide this mvt)
	Mvt_Stop						= 18,   // Used to stop current mvt
	// Command APP ______________________
	App_Wait						= 30,	// Wait (if all params = 0, wait for ever)
	App_IfGoto_System				= 31,	// Go to a specific step based on System Flags
	App_IfGoto_Strategy				= 32,	// Go to a specific step based on Strategy Flags
	App_SetNewPos					= 33,	// Msg used to define a new position
	App_SetStrategyFlags			= 34,	// Set the stratgey flags
	// Command SENSORS __________________
	// TODO : A reprendre suivant DSL
	Sensors_SetHoopLevel			= 40,	// Change 
}EnumCmd;

typedef enum
{
	CmdType_NotSet = 0,	        // Command type is not set
	CmdType_Blocking,			// Command is a blocking action
	CmdType_NonBlocking,		// Command is a non-blocking action
}EnumCmdType;

// STRUCT ################################################################
// Position -------------------------------------
typedef struct
{
	float 			x;					// Pos en x
	float 			y;					// Pos en y
	float 			angle;				// Angle
	CPU_INT16U		right_encoder;		// Right wheel position for mode 4
	CPU_INT16U		left_encoder;		// Left wheel position for mode 4
	unsigned char	CurrentState;		// Flag for storing current mvt state
}StructPos;

typedef struct
{
	EnumCmd			Cmd;			        // Mode used to go to next major point
	int 			Param1;				
	float 			Param2;				
	float 			Param3;				
	float			Param4;				
	unsigned int 	ActiveSensorsFlag;		// Define which sensors we have to use for this movement (if not set, use all external sensors)
	EnumCmdType		CmdType;				// Var to define if the current action is a blocking action or not
}StructCmd;

typedef struct
{
    BOOLEAN		IsRead;				// Read Flag
    EnumCmd		Cmd;				// Command for the current Msg
	EnumCmdType	CmdType;			// Var to define if the current action is a blocking action or not
}StructMsg;

#endif // APPCUSTOMTYPES_H
