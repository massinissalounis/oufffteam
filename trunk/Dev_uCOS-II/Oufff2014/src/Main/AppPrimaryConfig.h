/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : AppPrimaryConfig.h
*********************************************************************************************************
*/

#ifndef  APPPRIMARYCONFIG_H
#define  APPPRIMARYCONFIG_H

#ifdef _PRIMARY_ROBOT
/*
*********************************************************************************************************
*                                            CALIBRATION
*********************************************************************************************************
*/
// ------------------------------------------------------------------------------------------------
// PID Coefficients 
// ------------------------------------------------------------------------------------------------
// Angle loop for theta-alpha
#define KP_ANGLE 				150000.0		// Oscillations de 2s environ
#define KI_ANGLE 				0.0
#define KD_ANGLE 				350000.0
#define IMAX_ANGLE 				1000.0

// Distance loop for theta-alpha
#define KP_DISTANCE 			350.0
#define KI_DISTANCE 			0.0
#define KD_DISTANCE 			1500.0
#define IMAX_DISTANCE 			1000.0

// Wheel loop for separated control
#define KP_WHEEL_L	 			75.0
#define KI_WHEEL_L	 			0.0
#define KD_WHEEL_L	 			500.0 //750.0
#define IMAX_WHEEL_L 			1000.0

#define KP_WHEEL_R	 			75.0
#define KI_WHEEL_R	 			0.0
#define KD_WHEEL_R	 			500.0 //750.0
#define IMAX_WHEEL_R 			1000.0

// Generic parameters
#define PID_SUM_NB_SAMPLES 		3		// 1000 à l'origine CBE
#define PID_D_PERIOD			1		// 100 à l'origine CBE

// ------------------------------------------------------------------------------------------------
// Speed control Coefficients 
// ------------------------------------------------------------------------------------------------
// Used in quadramp
#define DEFAULT_SPEED_DISTANCE	0.40	// n % of maximum speed
#define DEFAULT_ACC_DISTANCE	0.025	// n % of maximum speed per 10 ms

// Used in hold speed control
#define SPEED_ANGLE		1.0 //0.9 	// n % of maximum speed

//#define SPEED_PIVOT		0.40 //0.9

// ------------------------------------------------------------------------------------------------
// General Coefficients
// ------------------------------------------------------------------------------------------------
#define MAX_MOTOR_COMMAND 		        32000	                            // doit être < à 32768
#define PIVOT_APPROACH_PRECISION		2.00
#define ANGLE_VS_DISTANCE_RATIO			0.3									// n % used for angle on full scale
#define ASSER_SAMPLING					10									// in ms


/*
*********************************************************************************************************
*                                            PRIMARY SETTINGS
*********************************************************************************************************
*/
#define APP_USE_DEBUG								1			// If defined, debug msg are sent to UART2.

#define APP_ESCAPE_ROBOT_SPEED						40			// Speed rate for escape seq		(0:No Move, 100: Full Speed)
#define APP_INIT_USE_START_BUTTON					OS_TRUE		// Flag to indicate if we have to use start button or not
//#define APP_INIT_EXEC_STARTUP_SEQ					OS_TRUE		// Flag to indicate if we have to execute the start up sequence

#define APP_GP2_LIMIT_FRONT							150			// Threshold 
#define APP_GP2_LIMIT_FRONT_LEFT					200			// Threshold 
#define APP_GP2_LIMIT_FRONT_RIGHT					200			// Threshold 
#define APP_GP2_LIMIT_REAR_INTERNAL					150			// Threshold
#define APP_GP2_LIMIT_REAR_INTERNAL_LONG_DETECTION	80			// Threshold
#define APP_GP2_LIMIT_REAR_HOOP						250			// Threshold
#define APP_GP2_LIMIT_REAR_LEFT_HOOP				250			// Threshold
#define APP_GP2_LIMIT_REAR_RIGHT_HOOP				250			// Threshold

#define GP2_FILTER_THRESHOLD 4
#define GP2_FILTER_THRESHOLD_SHORT 2
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
#define APP_TASK_DEBUG_ENABLED							// Activate TaskDebug
#define APP_TASK_TEMPO_ENABLED							// Activate TaskTempo
//#define APP_TASK_TEST_ENABLED							// Activate TaskTest (Only for specific tests)
#define APP_TASK_DETECTION_ENABLED						// Activate TaskDetection

/*
*********************************************************************************************************
*											STRATEGY
*********************************************************************************************************
*/
#ifndef _TARGET_440H
//#define SENSORS_CALIBRATION				// Enable this option for testing sensors
//#define AX12_REG_PROGRAMMING				// Use this flag for programming the default values into AX12
//#define ODO_CALIBRATION					// Use this flag for testing the Odometry configuration

#define HOMOL_STRATEGY_ENABLED			// Enable this option to use the homol strategy

#else
#define DEV_CARD_STRATEGY_ENABLED
#endif

#endif // _PRIMARY_ROBOT

#endif // APPPRIMARYCONFIG_H
