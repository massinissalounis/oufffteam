/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : AppGlobalConfig.h
*********************************************************************************************************
*/

#ifndef  APPGLOBALCONFIG_H
#define  APPGLOBALCONFIG_H

/*
*********************************************************************************************************
*                                            GLOBAL SETTINGS
*********************************************************************************************************
*/
#define APP_USE_DEBUG						1			// If defined, debug msg are sent to UART2.

#define APP_ESCAPE_ROBOT_SPEED				40			// Speed rate for escape seq		(0:No Move, 100: Full Speed)
#define APP_INIT_USE_START_BUTTON			OS_TRUE		// Flag to indicate if we have to use start button or not
//#define APP_INIT_EXEC_STARTUP_SEQ			OS_TRUE		// Flag to indicate if we have to execute the start up sequence

#define APP_GP2_LIMIT_FRONT_CENTER			150			// Threshold 
#define APP_GP2_LIMIT_REAR_CENTER			200			// Threshold
#define APP_GP2_LIMIT_FRONT_LEFT_1			250			// Threshold
#define APP_GP2_LIMIT_FRONT_LEFT_2			200			// Threshold
#define APP_GP2_LIMIT_FRONT_LEFT_3			200			// Threshold
#define APP_GP2_LIMIT_FRONT_RIGHT_1			250			// Threshold
#define APP_GP2_LIMIT_FRONT_RIGHT_2			200			// Threshold
#define APP_GP2_LIMIT_FRONT_RIGHT_3			200			// Threshold

#define APP_NOT_USED						0			// Not Used value

/*
*********************************************************************************************************
*                                            TASK MANAGING
*********************************************************************************************************
*/
#define APP_TASK_MAIN_ENABLED							// Activate TaskMain
#define APP_TASK_ODO_ENABLED							// Activate TaskOdo
#define APP_TASK_ASSER_ENABLED							// Activate TaskAsser
#define APP_TASK_MVT_ENABLED							// Acvivate TaskMvt
#define APP_TASK_SENSORS_ENABLED						// Activate TaskSensors
#define APP_TASK_TEMPO_ENABLED							// Activate TaskTempo

#define APP_TASK_ODO_DISPLAY_POSITION					// Activate the position debug messages
//#define APP_TASK_ODO_DISPLAY_DEBUG						// Activate the other debug messages

/*
*********************************************************************************************************
*                                            APP PARAMETERS
*********************************************************************************************************
*/
#define	APP_PARAM_GAME_DURATION					90			//  in sec: Time until the end of the game				
#define APP_PARAM_TEMPO_RESOLUTION				500			//  in ms (0 to 999): Delay before 2 ticks check in TaskTempo		

#define APP_PARAM_APPFLAG_INITAL_VALUE			0x00000000	//  Initial value for AppFlags  
#define APP_PARAM_STRATEGYFLAG_INITAL_VALUE		0x00000000	//  Initial value for AppStrategyFlags 
#define APP_PARAM_APPFLAG_ALL					0xFFFFFFFF	//	Read all sensors
#define APP_PARAM_STRATEGYFLAG_ALL				0xFFFFFFFF	//	Read all flags
#define APP_PARAM_APPFLAG_NONE					0x00000000	//	Don't use sensor
#define APP_PARAM_STRATEGYFLAG_NONE				0x00000000	//	Don't use flags

// APP FLAGS --------------------------------------------------------------------------------------------------------------------------------------------
// Value is defined as follow :								//	|Bit| Description				| Value ON 			| Value OFF			| Connection	|	
// State Flag ____________________________________________	//  |---|---------------------------|-------------------|-------------------|---------------|														
#define APP_PARAM_APPFLAG_START_BUTTON			0x00000001	//	| 0	| Start Button				| Pressed			| Not Pressed		| Hard			|
#define APP_PARAM_APPFLAG_BIT01					0x00000002	//	| 1 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT02					0x00000004	//	| 2 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT03					0x00000008	//	| 3 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT04					0x00000010	//	| 4 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_ACTION_TIMEOUT		0x00000020	//	| 5 | Timeout status			| Timeout reached	| Timeout unreached	| Soft			|
#define APP_PARAM_APPFLAG_ACTION_STATUS			0x00000040	//	| 6 | Action status				| Action is done	| Action is running	| Soft			|
#define APP_PARAM_APPFLAG_TIMER_STATUS			0x00000080	//	| 7 | Timer Status				| Time's Up			| Time's running 	| Soft			|	
// GP2 Flag ______________________________________________	//  |---|---------------------------|-------------------|-------------------|---------------|														
#define APP_PARAM_APPFLAG_GP2_FRONT_CENTER		0x00000100	//	| 8 | Front Sensor				| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_REAR_CENTER		0x00000200	//	| 9 | Rear sensor				| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_FRONT_LEFT_1		0x00000400	//	|10 | GP2 on left Arm (Front)	| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_FRONT_LEFT_2		0x00000800	//	|11 | GP2 on left Arm (Inside)	| Active			| Inactive			| Hard			|	
#define APP_PARAM_APPFLAG_GP2_FRONT_LEFT_3		0x00001000	//	|12 | GP2 on left Arm (Outside)	| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_1		0x00002000	//	|13 | GP2 on right Arm (Front)	| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_2		0x00004000	//	|14 | GP2 on right Arm (Inside)	| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_3		0x00008000	//	|15 | GP2 on right Arm (Outside)| Active			| Inactive			| Hard			|
// SW Flag _______________________________________________	//  |---|---------------------------|-------------------|-------------------|---------------|														
#define APP_PARAM_APPFLAG_SW_1					0x00010000	//	|16 | SW_1						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_2					0x00020000	//	|17 | SW_2						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_3					0x00040000	//	|18 | SW_3						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_4					0x00080000	//	|19 | SW_4						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_5					0x00100000	//	|20 | SW_5						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_6					0x00200000	//	|21 | SW_6						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_7					0x00400000	//	|22 | SW_7						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_8					0x00800000	//	|23 | SW_8						| Active			| Inactive			| Hard			|
// State Flag ____________________________________________	//  |---|---------------------------|-------------------|-------------------|---------------|														
#define APP_PARAM_APPFLAG_BIT24					0x01000000	//	|24 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT25					0x02000000	//	|25 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT26					0x04000000	//	|26 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT27					0x08000000	//	|27 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT28					0x10000000	//	|28 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT29					0x20000000	//	|29 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT30					0x40000000	//	|30 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT31					0x80000000	//	|31 | Not Used					| -					| -					| -				|

// STRATEGY FLAGS -----------------------------------------------------------------------------------------------------------------------
// Value is defined as follow :								//	|Bit| Desctiption				| Value ON 			| Value OFF			|	
// Actions Done __________________________________________	//  |---|---------------------------|-------------------|-------------------|											
#define APP_PARAM_STRATEGYFLAG_BIT00			0x00000001	//	| 0	| Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT01			0x00000002	//	| 1 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT02			0x00000004	//	| 2 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT03			0x00000008	//	| 3 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT04			0x00000010	//	| 4 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT05			0x00000020	//	| 5 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT06			0x00000040	//	| 6 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT07			0x00000080	//	| 7 | Not Used					| -					| -				 	| 	
// Forbbiden Zone ________________________________________	//  |---|---------------------------|-------------------|-------------------|														
#define APP_PARAM_STRATEGYFLAG_BIT08			0x00000100	//	| 8 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT09			0x00000200	//	| 9 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT10			0x00000400	//	|10 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT11			0x00000800	//	|11 | Not Used					| -					| -					| 	
#define APP_PARAM_STRATEGYFLAG_BIT12			0x00001000	//	|12 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT13			0x00002000	//	|13 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT14			0x00004000	//	|14 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT15			0x00008000	//	|15 | Not Used					| -					| -					| 
// SW Flag _______________________________________________	//  |---|---------------------------|-------------------|-------------------|														
#define APP_PARAM_STRATEGYFLAG_BIT16			0x00010000	//	|16 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT17			0x00020000	//	|17 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT18			0x00040000	//	|18 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT19			0x00080000	//	|19 | Not Used					| -					| -					| 
#define APP_PARAM_STRATEGYFLAG_BIT20			0x00100000	//	|20 | Not Used					| -					| -					| 	
#define APP_PARAM_STRATEGYFLAG_BIT21			0x00200000	//	|21 | Not Used					| -					| -					| 		
#define APP_PARAM_STRATEGYFLAG_BIT22			0x00400000	//	|22 | Not Used					| -					| -					| 	
#define APP_PARAM_STRATEGYFLAG_BIT23			0x00800000	//	|23 | Not Used					| -					| -					| 		
// State Flag ____________________________________________	//  |---|---------------------------|-------------------|-------------------|													
#define APP_PARAM_STRATEGYFLAG_ARMS_IS_INIT		0x01000000	//	|24 | Init postion for arms		| In init Pos		| Not in init pos	| 
#define APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED	0x02000000	//	|25 | Arms is opened			| Arms opened		| Arms not opened	| 
#define APP_PARAM_STRATEGYFLAG_ARMS_IS_CLOSED	0x04000000	//	|26 | Arms is closed			| Arms closed		| Arms not closed	| 
#define APP_PARAM_STRATEGYFLAG_COLLISION_FRONT	0x08000000	//	|27 | Collision state (front)	| Collision active  | Collision inactive|
#define APP_PARAM_STRATEGYFLAG_COLLISION_REAR	0x10000000	//	|28 | Collision state (rear)	| Collision active  | Collision inactive|
#define APP_PARAM_STRATEGYFLAG_COLLISION_LEFT	0x20000000	//	|29 | Collision state (left)	| Collision active  | Collision inactive|
#define APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT	0x40000000	//	|30 | Collision state (right)	| Collision active  | Collision inactive| 
#define APP_PARAM_STRATEGYFLAG_BIT31			0x80000000	//	|31 | Not Used					| -					| -					| 

// Groups ------------------------------------------------------------------------------------------------
// Sensors Groups
//#define APP_PARAM_DISABLE_ALL_SENSORS						// Use this flag for disabling all sensors (SW + GP2)
//#define APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE				// Use this flag for disabling sensors during an escape sequence
//#define APP_PARAM_DISABLE_SENSORS_DURING_TIMEOUT				// Use this flag for disabling sensors during a timeout sequence

#define APP_PARAM_APPFLAG_ALL_GP2				0x0000FF00	// All GP2 sensors
#define APP_PARAM_APPFLAG_ALL_SW				0x00FF0000	// All switches sensors
#define APP_PARAM_APPFLAG_ALL_SENSORS			0x00FFFF00	// All external sensors
#define APP_PARAM_APPFLAG_ALL_STATE				0xFF0000FF	// All state flags

// For storing the arms status
#define APP_PARAM_STRATEGYFLAG_ARMS_STATUS		(APP_PARAM_STRATEGYFLAG_ARMS_IS_INIT + APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED + APP_PARAM_STRATEGYFLAG_ARMS_IS_CLOSED)

// User defined groups
#ifdef APP_PARAM_DISABLE_ALL_SENSORS
	// Don't change this part !!!!
	#define APP_PARAM_STRATEGYFLAG_COLLISION_FRONT			(APP_PARAM_STRATEGYFLAG_NONE)	// Don't change this value !!!!
	#define APP_PARAM_STRATEGYFLAG_COLLISION_REAR			(APP_PARAM_STRATEGYFLAG_NONE)	// Don't change this value !!!!
	#define APP_PARAM_STRATEGYFLAG_COLLISION_LEFT			(APP_PARAM_STRATEGYFLAG_NONE)	// Don't change this value !!!!	
	#define APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT			(APP_PARAM_STRATEGYFLAG_NONE)	// Don't change this value !!!!
#endif	

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define OS_TASK_TMR_PRIO						0
#define APP_TASK_HIGHER_PRIO					2
#define APP_MUTEX_UART1_PRIO					4
#define APP_MUTEX_UART2_PRIO					5
#define APP_MUTEX_ODO_PRIO						6
#define APP_MUTEX_ASSER_PRIO					7
#define APP_MUTEX_MVT_PRIO						10
#define APP_TASK_ODO_PRIO						12
#define APP_TASK_ASSER_PRIO						16
#define APP_TASK_SENSORS_PRIO					24
#define APP_TASK_MVT_PRIO						28
#define APP_TASK_MAIN_PRIO						32
#define APP_TASK_TEMPO_PRIO						40

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define	APP_TASK_ODO_STK_SIZE					300
#define APP_TASK_ASSER_STK_SIZE	            	300
#define APP_TASK_SENSORS_STK_SIZE	            300
#define APP_TASK_MVT_STK_SIZE					300
#define APP_TASK_MAIN_STK_SIZE					300
#define APP_TASK_TEMPO_STK_SIZE	            	300

/*
*********************************************************************************************************
*                                            QUEUE SIZES
*********************************************************************************************************
*/

#define APP_QUEUE_SENSORS_SIZE					8	/* Nb max of msg from TaskMain to TaskSensors	(0=Not Used)	*/
#define APP_QUEUES_TOTAL_SIZE					(APP_QUEUE_SENSORS_SIZE)

/*
*********************************************************************************************************
*                                           MOVING METHOD
*********************************************************************************************************
*/

// SENSORS
//#define SENSORS_CALIBRATION

// Program AX12
//#define AX12_REG_PROGRAMMING											// Use this flag for programming the default values into AX12

// POSITION MANAGER MODE
//#define ODO_CALIBRATION

#define APP_MOVING_SEQ_LEN						5			    		// Length of moving sequence table (used for evoluate movment)
																		// WARNING : Minimal value is 3

#define APP_MOVING_ESCAPE_SEQ_RIGHT				1						// Create escape sequence by going on the right 
#define APP_MOVING_ESCAPE_SEQ_LEFT				2						// Create escape sequence by going on the left 
#define APP_MOVING_ESCAPE_SEQ_BACK				3						// Create escape sequence by going back
#define APP_MOVING_ESCAPE_SEQ_FRONT				4						// Create escape sequence by going forward

#define APP_MOVING_TIMEOUT_SEQ_BACK				3						// Create timeout sequence by going back
#define APP_MOVING_TIMEOUT_SEQ_FRONT			4						// Create timeout sequence by going forward


#define APP_MOVING_ASSER_INITIAL_MODE_CTRL		3					    // Initial Mode Control

#define APP_MOVING_DIST_APPROACH_PRECISION      50.0       			    // Distance in mm to consider the change of control mode (arrival zone)  
#define APP_MOVING_ANGLE_APPROACH_PRECISION     (2.0 * M_PI / 180.0)    // Angle in degree to consider the setpoint reached
#define APP_MOVING_APPROACH_PRECISION_COEF		1.1						// Coef to use to consider the setpoint reached (use by TaskMain)

#define APP_MOVING_MINIMAL_DIST_FOR_MIXED_MODE	50.0					// Minimal value necessary for TaskMvt to send order (in mixed mode) to TaskAsser
																		// If dist is under this value, command is not sent 
																		// This limitation is made to prevent small moves (big angle and small length)

#define APP_MVT_TIMEOUT							50						// Nb of iteration before considering position is unreachable
#define APP_COLLISION_TIMEOUT					10						// Nb of iteration before considering position is unreachable due to obstacle			

/*
*********************************************************************************************************
*                                           LIB CONFIG
*********************************************************************************************************
*/

#define LIB_STR_CFG_FP_EN						DEF_ENABLED		// Activate printf option

/*
*********************************************************************************************************
*											STRATEGY
*********************************************************************************************************
*/
// Only 1 option can be set bellow.

#define HOMOL_STRATEGY_ENABLED				// Enable this option to use the homol strategy

/*
*********************************************************************************************************
*                                      CONSTANTS FOR DEV CARD
*********************************************************************************************************
*/
#ifdef _TARGET_440H
	#define DELAY_MS_BETWEEN_NEXT_STATE				250				// Delay in ms before next state (TaskMvt)
	#define DELAY_S_BETWEEN_NEXT_STATE				0				// Delay in ms before next state (TaskMvt)
#endif

#endif // APPGLOBALCONFIG_H
