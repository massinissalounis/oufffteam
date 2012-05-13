/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : AppGlobalVars.h
*********************************************************************************************************
*/

#ifndef APPGLOBALVARS_H
#define APPGLOBALVARS_H 

/***** Queue *****/
extern OS_EVENT			*AppQueueSensors;						// Queue for storing msg from TaskMain to TaskSensors

#if APP_QUEUE_SENSORS_SIZE > 0
extern void*			AppQSensorsStk[APP_QUEUE_SENSORS_SIZE];	// Stack to store pointer to msg for SENSORS Queue
#endif

extern StructMsg		AppMsgStk[APP_QUEUES_TOTAL_SIZE];		// Stack to store msg for all Queues

//****** Global Vars ******/
extern StructCmd        App_CmdToTaskMvt;                       // Var to store next msg to TaskMvt (from TaskMain)
extern unsigned int     App_CmdToTaskMvtId;                     // Var to store MsgID of App_CmdToTaskMvt
extern StructCmd		App_CmdToTaskAsser;                     // Var to store next msg to TaskAsser (from TaskMvt)
extern unsigned int     App_CmdToTaskAsserId;                   // Var to store MsgID of App_CmdToTaskAsser

/***** MUTEX / SEMAPHORES *****/
extern OS_EVENT	        *App_MutexCmdToTaskMvt;		            // Mutex to limit access (RW) to Mvt Setpoint variable (from Main to TaskMvt)
extern OS_EVENT	        *App_MutexCmdToTaskAsser;	            // Mutex to limit access (RW) to Asser Setpoint variable (from TaskMvt to TaskAsser)
extern OS_EVENT			*App_MutexUART1;						// Mutex to limit access (RW) to UART1 device
extern OS_EVENT			*App_MutexUART2;						// Mutex to limit access (RW) to UART2 device

/***** Enum *****/
extern EnumColor		AppCurrentColor;						// Contains current color (read from bsp)

/***** FLAGS *****/
extern OS_FLAG_GRP		*AppFlags;								// Contains all flags for this application							
extern OS_FLAG_GRP		*AppStrategyFlags;						// Contains all flags for the Strategy							

#endif // APPGLOBALVARS_H
