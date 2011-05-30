/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : App.h
*********************************************************************************************************
*/

#ifndef APP_H
#define APP_H 

#include "AppIncludes.h"

/***** Queue *****/
OS_EVENT		*AppQueueSensors;						// Queue for storing msg from TaskMain to TaskSensors

#if APP_QUEUE_SENSORS_SIZE > 0
void*			AppQSensorsStk[APP_QUEUE_SENSORS_SIZE];	// Stack to store pointer to msg for Sensors Queue
#endif

StructMsg		AppMsgStk[APP_QUEUES_TOTAL_SIZE];		// Stack to store msg for all Queues

//****** Global Vars ******/
StructCmd       App_CmdToTaskMvt;                       // Var to store next msg to TaskMvt (from TaskMain)
unsigned int    App_CmdToTaskMvtId;                     // Var to store MsgID of App_CmdToTaskMvt
StructCmd       App_CmdToTaskAsser;                     // Var to store next msg to TaskAsser (from TaskMvt)
unsigned int    App_CmdToTaskAsserId;                   // Var to store MsgID of App_CmdToTaskAsser

/***** MUTEX / SEMAPHORES *****/
OS_EVENT	    *App_MutexCmdToTaskMvt = NULL;		    // Mutex to limit access (RW) to Mvt Setpoint variable (from Main to TaskMvt)
OS_EVENT	    *App_MutexCmdToTaskAsser = NULL;		// Mutex to limit access (RW) to Asser Setpoint variable (from TaskMvt to TaskAsser)
OS_EVENT	    *App_MutexUART1 = NULL;					// Mutex to limit access (RW) to UART1 device
OS_EVENT	    *App_MutexUART2 = NULL;					// Mutex to limit access (RW) to UART2 device
OS_EVENT	    *App_MutexPMP = NULL;					// Mutex to limit access (RW) to UART2 device

/***** Enum *****/
EnumColor		AppCurrentColor;						// Contains current color (read from bsp)

/***** FLAGS *****/
OS_FLAG_GRP		*AppFlags;								// Contains all flags for this application							

#endif // APP_H
