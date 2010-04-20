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
*                                            APP PARAMETERS
*********************************************************************************************************
*/
#define	APP_PARAM_GAME_DURATION				10			/* in sec: Time until the end of the game				*/
#define APP_PARAM_TEMPO_RESOLUTION			500			/* in ms (0 to 999): Delay before 2 ticks check in TaskTempo		*/

#define APP_PARAM_APPFLAG_INITAL_VALUE		0x00000000	/* Initial value for AppFlags var */
/* Value is defined as follow :							/*	|Bit| Desctiption				| Value ON 			| Value OFF			|	*/
#define APP_PARAM_APPFLAG_START_BUTTON		0x00000001	/*	| 0	| Start Button				| Pressed			| Not Pressed		|	*/
#define APP_PARAM_APPFLAG_BIT1				0x00000002	/*	| 1 | Not Used					| -					| -					|	*/
#define APP_PARAM_APPFLAG_BIT2				0x00000004	/*	| 2 | Not Used					| -					| -					|	*/
#define APP_PARAM_APPFLAG_BIT3				0x00000008	/*	| 3 | Not Used					| -					| -					|	*/
#define APP_PARAM_APPFLAG_BIT4				0x00000010	/*	| 4 | Not Used					| -					| -					|	*/
#define APP_PARAM_APPFLAG_BIT5				0x00000020	/*	| 5 | Not Used					| -					| -					|	*/
#define APP_PARAM_APPFLAG_BIT6				0x00000040	/*	| 6 | Not Used					| -					| -					|	*/
#define APP_PARAM_APPFLAG_TIMER_STATUS		0x00000080	/*	| 7 | Timer Status				| Time's Up			| Time's running	|	*/
#define APP_PARAM_APPFLAG_BUMPER0			0x00000100	/*	| 8 | Bumpers 0 Status			| Active			| Inactive			|	*/
#define APP_PARAM_APPFLAG_BUMPER1			0x00000200	/*	| 9 | Bumpers 1 Status			| Active			| Inactive			|	*/
#define APP_PARAM_APPFLAG_BUMPER2			0x00000400	/*	|10 | Bumpers 2 Status			| Active			| Inactive			|	*/
#define APP_PARAM_APPFLAG_BUMPER3			0x00000800	/*	|11 | Bumpers 3 Status			| Active			| Inactive			|	*/
#define APP_PARAM_APPFLAG_BUMPER4			0x00001000	/*	|12 | Bumpers 4 Status			| Active			| Inactive			|	*/
#define APP_PARAM_APPFLAG_BUMPER5			0x00002000	/*	|13 | Bumpers 5 Status			| Active			| Inactive			|	*/
#define APP_PARAM_APPFLAG_BUMPER6			0x00004000	/*	|14 | Bumpers 6 Status			| Active			| Inactive			|	*/
#define APP_PARAM_APPFLAG_BUMPER7			0x00008000	/*	|15 | Bumpers 7 Status			| Active			| Inactive			|	*/
#define APP_PARAM_APPFLAG_NOT_USED			0xFFFF0000	/*  |16 to 32 | Not used			| Not used			| Not used			|	*/				

// Flag to check all Flags
#define APP_PARAM_APPFLAG_ALL_BUMPERS		APP_PARAM_APPFLAG_BUMPER0 | APP_PARAM_APPFLAG_BUMPER1 | APP_PARAM_APPFLAG_BUMPER2 | APP_PARAM_APPFLAG_BUMPER3 | APP_PARAM_APPFLAG_BUMPER4 | APP_PARAM_APPFLAG_BUMPER5 | APP_PARAM_APPFLAG_BUMPER6 | APP_PARAM_APPFLAG_BUMPER7 

#define APP_PARAM_ERR_ON_POS				1.00		// Error in mm for x and y for considering setpoint is reached
#define APP_PARAM_ERR_ON_ANGLE				1.00		// Error in degree for angle for considering setpoint is reached
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
#define APP_QUEUES_TOTAL_SIZE					APP_QUEUE_MAIN_SIZE + APP_QUEUE_ASSER_SIZE

/*
*********************************************************************************************************
*                                           MOVING METHOD
*********************************************************************************************************
*/

// POSITION MANAGER MODE
//#define ODO_CALIBRATION
#define APP_MOVING_SEQ_LEN						5			// Length of moving sequence table (used for evoluate movment)

#define APP_MOVING_ASSER_IN_POS_ENABLED			OS_TRUE		// Indicate if we use asser in pos
#define APP_MOVING_ASSER_IN_ANGLE_ENABLED		OS_TRUE		// Indicate if we use asser in angle
#define APP_MOVING_ASSER_IN_SPEED_ENABLED		OS_FALSE	// Indicate if we use asser in speed (Not used)
/*
*********************************************************************************************************
*                                           LIB CONFIG
*********************************************************************************************************
*/

#define LIB_STR_CFG_FP_EN						DEF_ENABLED		// Activate printf option

#endif
