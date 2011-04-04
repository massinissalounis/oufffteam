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
#define	WAIT_FOREVER			0		// Define for Timeout

#define RIGHT_WHEEL				1		// Used for pivot mode
#define LEFT_WHEEL				-1		// Used for pivot mode

// ENUM ##################################################################
// Color ----------------------------------------
typedef enum
{
	c_NotSet = -1,
	c_ColorA,
	c_ColorB,
}EnumColor;

// Mvt Mode -------------------------------------
typedef enum
{
	MvtMode_Simple = -1,		// Used a simple mvt (don't divide this mvt)
	MvtMode_DontMove = 0,		// Don't move for this mvt
	MvtMode_AngleOnly = 1,		// Use Asser Mode 1
	MvtMode_DistOnly,			// Use Asser Mode 2
	MvtMode_MixedMode,			// Use Asser Mode 3
	MvtMode_PivotMode,			// Use Asser Mode 4
}EnumMvtMode;

// Msg Type -------------------------------------
typedef enum
{								// Dest		| Details																
	Msg_NoMsg = 0,				// None		| To send a NULL msg (not used)											
	Msg_Asser_MsgType = 100,	// None		| Asser Msg																
	Msg_Asser_MoveMode1,		// Asser	| Go to specified angle (Mode 1 = Angle only)
	Msg_Asser_MoveMode2,		// Asser	| Go to specified (x,y) position (Mode 2 = Dist only)							
	Msg_Asser_MoveMode3,		// Asser	| Go to specified (x,y,a) position (Mode 3 = Mixed Mode)
	Msg_Asser_MoveMode4,		// Asser	| Rotate around specified wheel (Mode 4 = Pivot Mode)
}EnumMsgType;

// STRUCT ################################################################
// Position -------------------------------------
typedef struct
{
	float 		x;					// Pos en x
	float 		y;					// Pos en y
	float 		angle;				// Angle
	CPU_INT16U	right_encoder;		// Right wheel position for mode 4
	CPU_INT16U	left_encoder;		// Left wheel position for mode 4
	char		CurrentState;		// Flag for storing current mvt state
}StructOdoPos;

typedef struct
{
	int MvtMode;				// Mode used to go to next major point
	// MvtMode Type				   Simple			| DontMove	| AngleOnly		| DistOnly		| MixedMode		| PivotMode		|
	short 	Param1;				// Speed(1-100)		| Not Used	| Speed(1-100)	| Speed(1-100)	| Speed(1-100)	| Speed(1-100)	|
	float 	Param2;				// x				| Not Used	| Not Used		| x				| x				| Wheel to lock	|
	float 	Param3;				// y				| Not Used	| Not Used		| y				| y				| Not Used		|
	float	Param4;				// angle			| Not Used	| angle			| Not Used		| angle			| angle			|
	int 	ActiveSensorsFlag;	// Define which sensors we have to use for this movement (if not set, use all external sensors)
}StructMvtPos;

// Msg ------------------------------------------
typedef struct 
{
	EnumMsgType MsgType;	// Msg Type (Msg_NoMsg: Invalid Msg)																					
	BOOLEAN IsRead;		// Flag to indicate if current msg has been read or not																	
	// Msg Parameters	:	Msg_Asser_MoveMode1 | Msg_Asser_MoveMode2	| Msg_Asser_MoveMode3	| Msg_Asser_MoveMode4	|
	short Param1;		//	Speed (1-100)		| Speed (1-100)			| Speed (1-100)			| Speed (1-100)			|
	float Param2;		//	Not Used			| x						| x						| Wheel to lock			| 
	float Param3;		//	Not Used			| y						| y						| Not Used				|
	float Param4;		//	Angle In Rad		| Not Used				| Angle In Rad			| Angle In Rad			|
}StructMsg;

#endif // APPCUSTOMTYPES_H
