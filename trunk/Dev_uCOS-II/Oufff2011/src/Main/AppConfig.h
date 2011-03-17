/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                       APPLICATION CONFIGURATION
*
*
* Filename      : AppConfig.h
* Version       : V1.00
* Programmer(s) : Hong Soong
*********************************************************************************************************
*/

#ifndef  APPCONFIG_H
#define  APPCONFIG_H

/*
*********************************************************************************************************
*                                            GLOBAL SETTINGS
*********************************************************************************************************
*/
#define APP_INIT_BLUE_POS_X					000.0		// Initial position for blue robot
#define APP_INIT_BLUE_POS_Y					000.0		// Initial position for blue robot
#define APP_INIT_BLUE_ANGLE					000.0		// Initial position for blue robot

#define APP_INIT_YELLOW_POS_X				000.0		// Initial position for blue robot
#define APP_INIT_YELLOW_POS_Y				000.0		// Initial position for blue robot
#define APP_INIT_YELLOW_ANGLE				000.0		// Initial position for blue robot

#define APP_INIT_ROBOT_SPEED				0.600		// Speed rate (0.0:No Move, 1.0: Full Speed)

#define APP_GP2D2_LIMIT_FRONT				300			// Object detection around 200 mm
#define APP_GP2D2_LIMIT_BACK				400			// Object detection around 200 mm

#define APP_NOT_USED						0			// Not Used value

/*
*********************************************************************************************************
*                                            TASK MANAGING
*********************************************************************************************************
*/
#define APP_TASK_MAIN_ENABLED				// Activate MainTask
#define APP_TASK_ODO_ENABLED				// Activate OdoTask
#define APP_TASK_ASSER_ENABLED				// Activate AsserTask
#define APP_TASK_CAPTEURS_ENABLED			// Activate CapteursTask
#define APP_TASK_TEMPO_ENABLED				// Activate TempoTask

/*
*********************************************************************************************************
*                                            APP PARAMETERS
*********************************************************************************************************
*/
#define	APP_PARAM_GAME_DURATION					90			//  in sec: Time until the end of the game				
#define APP_PARAM_TEMPO_RESOLUTION				500			//  in ms (0 to 999): Delay before 2 ticks check in TaskTempo		

#define APP_PARAM_APPFLAG_INITAL_VALUE			0x00000000	//  Initial value for AppFlags var 
// Value is defined as follow :								//	|Bit| Desctiption				| Value ON 			| Value OFF			| Connection	|	
#define APP_PARAM_APPFLAG_START_BUTTON			0x00000001	//	| 0	| Start Button				| Pressed			| Not Pressed		| S				|
#define APP_PARAM_APPFLAG_BIT1					0x00000002	//	| 1 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT2					0x00000004	//	| 2 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT3					0x00000008	//	| 3 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT4					0x00000010	//	| 4 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT5					0x00000020	//	| 5 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_BIT6					0x00000040	//	| 6 | Not Used					| -					| -					| -				|
#define APP_PARAM_APPFLAG_TIMER_STATUS			0x00000080	//	| 7 | Timer Status				| Time's Up			| Time's running	| NC			|	
#define APP_PARAM_APPFLAG_GP2D2_FRONT			0x00000100	//	| 8 | GP2D2 Front				| Active			| Inactive			| GP2D2_1		|
#define APP_PARAM_APPFLAG_GP2D2_BACK			0x00000200	//	| 9 | GP2D2 Back				| Active			| Inactive			| GP2D2_2		|
#define APP_PARAM_APPFLAG_GP2D2_3				0x00000400	//	|10 | Bumpers 2 Status			| Active			| Inactive			| NC			|
#define APP_PARAM_APPFLAG_GP2D2_4				0x00000800	//	|11 | Bumpers 3 Status			| Active			| Inactive			| NC			|	
#define APP_PARAM_APPFLAG_BUMPER_CLIC1			0x00001000	//	|12 | Front Left				| Active			| Inactive			| NC			|
#define APP_PARAM_APPFLAG_BUMPER_CLIC2			0x00002000	//	|13 | Front Right				| Active			| Inactive			| NC			|
#define APP_PARAM_APPFLAG_BUMPER_CLIC3			0x00004000	//	|14 | Front Center				| Active			| Inactive			| CLIC_3		|
#define APP_PARAM_APPFLAG_BUMPER_CLIC4			0x00008000	//	|15 | Rear Center				| Active			| Inactive			| CLIC_4		|
#define APP_PARAM_APPFLAG_NOT_USED				0xFFFF0000	//  |16 to 32 | Not used			| Not used			| Not used			| -				|	

// Flag to check all Flags
#define APP_PARAM_APPFLAG_ALL_BUMPERS			(APP_PARAM_APPFLAG_GP2D2_FRONT | APP_PARAM_APPFLAG_GP2D2_BACK | APP_PARAM_APPFLAG_GP2D2_3 | APP_PARAM_APPFLAG_GP2D2_4 | APP_PARAM_APPFLAG_BUMPER_CLIC1 | APP_PARAM_APPFLAG_BUMPER_CLIC2 | APP_PARAM_APPFLAG_BUMPER_CLIC3 | APP_PARAM_APPFLAG_BUMPER_CLIC4)

#define APP_PARAM_ERR_ON_POS					55.0						// Error in mm for x and y for considering setpoint is reached
#define APP_PARAM_ERR_ON_ANGLE					(2.00 * M_PI / 180.0)		// Error in rad for angle for considering setpoint is reached
/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define OS_TASK_TMR_PRIO						0
#define APP_TASK_HIGHER_PRIO					4
#define APP_TASK_ODO_PRIO						8
#define APP_TASK_ASSER_PRIO						16
#define APP_TASK_CAPTEURS_PRIO					24
#define APP_TASK_MAIN_PRIO						32
#define APP_TASK_TEMPO_PRIO						40

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define	APP_TASK_ODO_STK_SIZE					175
#define APP_TASK_ASSER_STK_SIZE	            	175
#define APP_TASK_CAPTEURS_STK_SIZE	            175
#define APP_TASK_MAIN_STK_SIZE					175
#define APP_TASK_TEMPO_STK_SIZE	            	175

/*
*********************************************************************************************************
*                                            QUEUE SIZES
*********************************************************************************************************
*/

#define APP_QUEUE_MAIN_SIZE						0	/* Nb max of msg into MainQueue		(0=Not Used)	*/
#define APP_QUEUE_ASSER_SIZE					8	/* Nb max of msg into AsserQueue	(0=Not Used)	*/
#define APP_QUEUES_TOTAL_SIZE					(APP_QUEUE_MAIN_SIZE + APP_QUEUE_ASSER_SIZE)

/*
*********************************************************************************************************
*                                           MOVING METHOD
*********************************************************************************************************
*/

// POSITION MANAGER MODE
//#define ODO_CALIBRATION
#define APP_MOVING_SEQ_LEN						5			// Length of moving sequence table (used for evoluate movment)

// Moving Algo : The first option set to OS_TRUE would be used
#define APP_MOVING_ALGO_1_SIMPLE				OS_TRUE		// Activate Simple Moving Algo (without anticipation)

#define APP_MOVING_ASSER_INITIAL_MODE_CTRL		3			// Initial Mode Controle

#define APP_MOVING_ESCAPE_SEQ_STOP				0			// No escape sequence. In case of collision, do nothing and stay in pos
#define APP_MOVING_ESCAPE_SEQ_FRONT_RIGHT		1			// Escape sequence by the right (to the front)
#define APP_MOVING_ESCAPE_SEQ_FRONT_LEFT		2			// Escape sequence by the left (to the front)
#define APP_MOVING_ESCAPE_SEQ_FRONT_BACK		3			// Escape sequence by the back (to the front)
#define APP_MOVING_ESCAPE_SEQ_CHECK_CORN		4			// Escape sequence by the back (to the front)

// Choose the default escape sequence to use
#define APP_MOVING_ESCAPE_SEQ_FRONT_DEFAULT		APP_MOVING_ESCAPE_SEQ_STOP

/*
*********************************************************************************************************
*                                           MOVING FLAGS
*********************************************************************************************************
*/
#define APP_FLAG_POS__NO_FLAG					0x00		// No flag has been set
#define APP_FLAG_POS__LOCK_IN_POS				0x01		// Robot stay in pos when it arrives to expected pos
#define APP_FLAG_POS__SIMPLE_MOVE				0x02		// There is no decomposition if this flag is set
#define APP_FLAG_POS__CHECK_CORN				0x04		// Flag to indicate next order checks for corn (low speed)

/*
*********************************************************************************************************
*                                           SENSORS FLAGS
*********************************************************************************************************
*/
#define SENSORS_GPD2D_1						0x00				// GPD2D2_1 : Front sensor
#define SENSORS_GPD2D_2						0x01				// GPD2D2_2 : Back sensor
#define SENSORS_GPD2D_3						0x02				// GPD2D2_3 : Not Used
#define SENSORS_GPD2D_4						0x03				// GPD2D2_4 : Not Used
#define SENSORS_CLICCLIC_1					0x04				// CLICCLIC_1 : Not Used
#define SENSORS_CLICCLIC_2					0x05				// CLICCLIC_2 : Not Used
#define SENSORS_CLICCLIC_3					0x06				// CLICCLIC_3 : Front Sensor
#define SENSORS_CLICCLIC_4					0x07				// CLICCLIC_4 : Back Sensor
#define SENSORS_ALL							0x08				// Must be the highest value for block SENSORS_...

#define SENSORS_NONE_ID						0x0000											// None
#define SENSORS_GPD2D_1_ID					0x0001											// GPD2D2_1 : Front sensor
#define SENSORS_GPD2D_2_ID					0x0002											// GPD2D2_2 : Back sensor
#define SENSORS_GPD2D_3_ID					0x0004											// GPD2D2_3 : Not Used
#define SENSORS_GPD2D_4_ID					0x0008											// GPD2D2_4 : Not Used
#define SENSORS_CLICCLIC_1_ID				0x0010											// CLICCLIC_1 : Not Used
#define SENSORS_CLICCLIC_2_ID				0x0020											// CLICCLIC_2 : Not Used
#define SENSORS_CLICCLIC_3_ID				0x0040											// CLICCLIC_3 : Front Sensor
#define SENSORS_CLICCLIC_4_ID				0x0080											// CLICCLIC_4 : Back Sensor
#define SENSORS_BACK_ID						(SENSORS_GPD2D_2_ID + SENSORS_CLICCLIC_4_ID)	// Back Sensors (GPD2D2_2 + CLICCLIC_4)
#define SENSORS_FRONT_ID					(SENSORS_GPD2D_1_ID + SENSORS_CLICCLIC_3_ID)	// Front Sensors (GPD2D2_1 + CLICCLIC_3)
#define SENSORS_ALL_ID						0xFFFF
/*
*********************************************************************************************************
*                                           LIB CONFIG
*********************************************************************************************************
*/

#define LIB_STR_CFG_FP_EN						DEF_ENABLED		// Activate printf option

#endif
