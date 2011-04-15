/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : AppConfig.h
*********************************************************************************************************
*/

#ifndef  APPCONFIG_H
#define  APPCONFIG_H

/*
*********************************************************************************************************
*                                            GLOBAL SETTINGS
*********************************************************************************************************
*/
#define APP_INIT_ROBOT_SPEED				0.600		// Speed rate (0.0:No Move, 1.0: Full Speed)
#define APP_INIT_USE_START_BUTTON			OS_TRUE	// Flag to indicate if we have to use start button or not

#define APP_GP2D2_LIMIT_FRONT				300			// Object detection around 200 mm
#define APP_GP2D2_LIMIT_BACK				400			// Object detection around 200 mm

#define APP_NOT_USED						0			// Not Used value

/*
*********************************************************************************************************
*                                            TASK MANAGING
*********************************************************************************************************
*/
#define APP_TASK_MAIN_ENABLED							// Activate TaskMain
//#define APP_TASK_ODO_ENABLED							// Activate TaskOdo
//#define APP_TASK_ASSER_ENABLED						// Activate TaskAsser
#define APP_TASK_MVT_ENABLED							// Acvivate TaskMvt
//#define APP_TASK_SENSORS_ENABLED						// Activate TaskSensors
//#define APP_TASK_TEMPO_ENABLED						// Activate TaskTempo

/*
*********************************************************************************************************
*                                            APP PARAMETERS
*********************************************************************************************************
*/
#define	APP_PARAM_GAME_DURATION					90			//  in sec: Time until the end of the game				
#define APP_PARAM_TEMPO_RESOLUTION				500			//  in ms (0 to 999): Delay before 2 ticks check in TaskTempo		

#define APP_PARAM_APPFLAG_INITAL_VALUE			0x00000000	//  Initial value for AppFlags var 
#define APP_PARAM_APPFLAG_NONE					0x00000000	//	Don't use sensor

// Value is defined as follow :								//	|Bit| Desctiption				| Value ON 			| Value OFF			| Connection	|	
#define APP_PARAM_APPFLAG_START_BUTTON			0x00000001	//	| 0	| Start Button				| Pressed			| Not Pressed		| Hard			|
#define APP_PARAM_APPFLAG_BIT01					0x00000002	//	| 1 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT02					0x00000004	//	| 2 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT03					0x00000008	//	| 3 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT04					0x00000010	//	| 4 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_NEW_MVT_AVAILABLE		0x00000020	//	| 5 | New Mvt Flag				| New Mvt Available	| No Mvt Available  | Soft			|
#define APP_PARAM_APPFLAG_MVT_STATE				0x00000040	//	| 6 | Mouvement state			| Robot is moving	| Robot is stopped	| Soft			|
#define APP_PARAM_APPFLAG_TIMER_STATUS			0x00000080	//	| 7 | Timer Status				| Time's running	| Time's Up		 	| Soft			|	
#define APP_PARAM_APPFLAG_GP2_1					0x00000100	//	| 8 | GP2_1						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_2					0x00000200	//	| 9 | GP2_2						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_3					0x00000400	//	|10 | GP2_3						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_4					0x00000800	//	|11 | GP2_4						| Active			| Inactive			| Hard			|	
#define APP_PARAM_APPFLAG_GP2_5					0x00001000	//	|12 | GP2_5						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_6					0x00002000	//	|13 | GP2_6						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_7					0x00004000	//	|14 | GP2_7						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_GP2_8					0x00008000	//	|15 | GP2_8						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_1					0x00010000	//	|16 | SW_1						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_2					0x00020000	//	|17 | SW_2						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_3					0x00040000	//	|18 | SW_3						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_4					0x00080000	//	|19 | SW_4						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_5					0x00100000	//	|20 | SW_5						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_6					0x00200000	//	|21 | SW_6						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_7					0x00400000	//	|22 | SW_7						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_SW_8					0x00800000	//	|23 | SW_8						| Active			| Inactive			| Hard			|
#define APP_PARAM_APPFLAG_BIT24					0x01000000	//	|24 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT25					0x02000000	//	|25 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT26					0x04000000	//	|26 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT27					0x08000000	//	|27 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT28					0x10000000	//	|28 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT29					0x20000000	//	|29 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT30					0x40000000	//	|30 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT31					0x80000000	//	|31 | Not Used					| -					| -					| -				|

// Groups ------------------------------------------------------------------------------------------------
// Sensors Groups
#define APP_PARAM_APPFLAG_ALL_GP2				0x0000FF00	// All GP2 sensors
#define APP_PARAM_APPFLAG_ALL_SW				0x00FF0000	// All switches sensors
#define APP_PARAM_APPFLAG_ALL_SENSORS			0x00FFFF00	// All external sensors

// User defined groups
// - Front sensors
#define APP_PARAM_APPFLAG_FRONT_SENSORS			(APP_PARAM_APPFLAG_NONE)	
// - Back sensors
#define APP_PARAM_APPFLAG_BACK_SENSORS			(APP_PARAM_APPFLAG_NONE)	
// - Left sensors
#define APP_PARAM_APPFLAG_LEFT_SENSORS			(APP_PARAM_APPFLAG_NONE)	
// - Right sensors
#define APP_PARAM_APPFLAG_RIGHT_SENSORS			(APP_PARAM_APPFLAG_NONE)	

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define OS_TASK_TMR_PRIO						0
#define APP_TASK_HIGHER_PRIO					4
#define APP_TASK_ODO_PRIO						8
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

#define	APP_TASK_ODO_STK_SIZE					175
#define APP_TASK_ASSER_STK_SIZE	            	175
#define APP_TASK_SENSORS_STK_SIZE	            175
#define APP_TASK_MVT_STK_SIZE					175
#define APP_TASK_MAIN_STK_SIZE					175
#define APP_TASK_TEMPO_STK_SIZE	            	50

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

// POSITION MANAGER MODE
//#define ODO_CALIBRATION
#define APP_MOVING_SEQ_LEN						5			    // Length of moving sequence table (used for evoluate movment)

#define APP_MOVING_ASSER_INITIAL_MODE_CTRL		3			    // Initial Mode Controle

#define APP_MOVING_DIST_APPROCH_PRECISION       50.0            // Distance in mm to consider the change of control mode (arrival zone)  
#define APP_MOVING_ANGLE_APPROCH_PRECISION      2.0             // Angle in degree to consider the setpoint reached

/*
*********************************************************************************************************
*                                           LIB CONFIG
*********************************************************************************************************
*/

#define LIB_STR_CFG_FP_EN						DEF_ENABLED		// Activate printf option

/*
*********************************************************************************************************
*                                      CONSTANTS FOR DEV CARD
*********************************************************************************************************
*/
#ifdef _TARGET_440H
#define DELAY_MS_BETWEEN_NEXT_STATE				250				// Delay in ms before next state (TaskMvt)
#define DELAY_S_BETWEEN_NEXT_STATE				0				// Delay in ms before next state (TaskMvt)
#endif

#endif
