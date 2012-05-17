/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : App.c
*
* Suivi de version :
* 2009-03-26 | PBE | Creation de la version de base pour la coupe 2010
* 2009-04-01 | PBE | Mise à jour pour la coupe 2011
*********************************************************************************************************
*/

#include "App.h"		// Global Variables

// Task includes
#include "TaskOdo.h"
#include "TaskAsser.h"
#include "TaskSensors.h"
#include "TaskMain.h"
#include "TaskTempo.h"
#include "TaskMvt.h"

/***** Calling Stacks *****/
static OS_STK       AppTaskOdoStk[APP_TASK_ODO_STK_SIZE];
static OS_STK       AppTaskAsserStk[APP_TASK_ASSER_STK_SIZE];
static OS_STK       AppTaskSensorsStk[APP_TASK_SENSORS_STK_SIZE];
static OS_STK       AppTaskMainStk[APP_TASK_MAIN_STK_SIZE];
static OS_STK       AppTaskMvtStk[APP_TASK_MVT_STK_SIZE];
static OS_STK       AppTaskTempoStk[APP_TASK_TEMPO_STK_SIZE];

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void AppTaskStart();				/* Function to start all tasks		*/
void AppCreateIPCS();				/* Function to create IPCS			*/
void AppInitVar();					/* Function to initialize variables	*/

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.
* Arguments   : none
*********************************************************************************************************
*/

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF, FSOSCEN = OFF, POSCMOD = HS, FNOSC = FRCPLL, FPBDIV = DIV_1, ICESEL=ICS_PGx1 

int  main (void)
{
	unsigned char test_color = 1;
	char 		uart_buffer[13];
	char 		*buffer_ptr;
    CPU_INT08U  err;

    BSP_IntDisAll();			/* Disable all interrupts until we are ready to accept them */
	OSInit();                   /* Initialize "uC/OS-II, The Real-Time Kernel"              */


	AppInitVar();				/* Initialize globale vars									*/
	AppCreateIPCS();			/* Create IPCS objects										*/
	AppTaskStart();				/* Start all tasks											*/

	AppDebugMsg("-----------------------------------\r\n");
#ifdef _TARGET_440H
	Set_Line_Information( 1, 0, "    OUFFF TEAM   ", 16);
	Set_Line_Information( 2, 0, "    Coupe 2012   ", 16);
#endif

	OSStart();                  /* Start multitasking (i.e. give control to uC/OS-II)       */
	/* This part would be never executed */
}

/*
*********************************************************************************************************
*                                          AppTaskStart
*
* Description : This function starts all configured tasks
* Arguments   : None
*********************************************************************************************************
*/

void  AppTaskStart()
{
    CPU_INT08U  err;

	// --------------------------------------------------------------------------------------------
	// Init BSP and FPGA module
	BSP_Dly(10000);			// to wait FPGA to be loaded (time in us)
	BSP_InitIO();           // Initialize BSP functions
	BSPFPGA_Reset();

#ifdef AX12_REG_PROGRAMMING
	ARMS_InitReg(); // Register configuration - Comment for match
	AppDebugMsg("AX12_REG_PROGRAMMING ok\n");
	while(1)
	{
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
#endif

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                                       // Determine CPU capacity
#endif

#ifdef APP_TASK_ODO_ENABLED
	// --------------------------------------------------------------------------------------------
	// Starts TaskOdo
    OSTaskCreateExt( TaskOdo_Main,                                      
				    (void *)0,
                    (OS_STK *)&AppTaskOdoStk[APP_TASK_ODO_STK_SIZE - 1],
                    APP_TASK_ODO_PRIO,
                    APP_TASK_ODO_PRIO,
                    (OS_STK *)&AppTaskOdoStk[0],
                    APP_TASK_ODO_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 13
    OSTaskNameSet(APP_TASK_ODO_PRIO, "TaskOdo", &err);
#endif
#endif

#ifdef APP_TASK_ASSER_ENABLED
	// --------------------------------------------------------------------------------------------
	// Starts TaskAsser
    OSTaskCreateExt( TaskAsser_Main,                                      
				    (void *)0,
                    (OS_STK *)&AppTaskAsserStk[APP_TASK_ASSER_STK_SIZE - 1],
                    APP_TASK_ASSER_PRIO,
                    APP_TASK_ASSER_PRIO,
                    (OS_STK *)&AppTaskAsserStk[0],
                    APP_TASK_ASSER_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 13
    OSTaskNameSet(APP_TASK_ASSER_PRIO, "TaskAsser", &err);
#endif
#endif

#ifdef APP_TASK_MVT_ENABLED
	// --------------------------------------------------------------------------------------------
	// Starts Mvt
    OSTaskCreateExt( TaskMvt_Main,                                      
				    (void *)0,
                    (OS_STK *)&AppTaskMvtStk[APP_TASK_MVT_STK_SIZE - 1],
                    APP_TASK_MVT_PRIO,
                    APP_TASK_MVT_PRIO,
                    (OS_STK *)&AppTaskMvtStk[0],
					APP_TASK_MVT_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 13
    OSTaskNameSet(APP_TASK_ASSER_PRIO, "TaskMvt", &err);
#endif

#endif


#ifdef APP_TASK_SENSORS_ENABLED
	// --------------------------------------------------------------------------------------------
	// Starts TaskSensors
    OSTaskCreateExt( TaskSensors_Main,                                       
				    (void *)0,
                    (OS_STK *)&AppTaskSensorsStk[APP_TASK_SENSORS_STK_SIZE - 1],
                    APP_TASK_SENSORS_PRIO,
                    APP_TASK_SENSORS_PRIO,
                    (OS_STK *)&AppTaskSensorsStk[0],
                    APP_TASK_SENSORS_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 13
    OSTaskNameSet(APP_TASK_SENSORS_PRIO, "TaskSensors", &err);
#endif
#endif

#ifdef APP_TASK_MAIN_ENABLED
	// --------------------------------------------------------------------------------------------
	// Starts TaskMain
    OSTaskCreateExt( TaskMain_Main,                                       
				    (void *)0,
                    (OS_STK *)&AppTaskMainStk[APP_TASK_MAIN_STK_SIZE - 1],
                    APP_TASK_MAIN_PRIO,
                    APP_TASK_MAIN_PRIO,
                    (OS_STK *)&AppTaskMainStk[0],
                    APP_TASK_MAIN_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 13
    OSTaskNameSet(APP_TASK_MAIN_PRIO, "TaskMain", &err);
#endif
#endif

#ifdef APP_TASK_TEMPO_ENABLED
	// --------------------------------------------------------------------------------------------
	// Starts TaskTempo
    OSTaskCreateExt( TaskTempo_Main,                                       
				    (void *)0,
                    (OS_STK *)&AppTaskTempoStk[APP_TASK_TEMPO_STK_SIZE - 1],
                    APP_TASK_TEMPO_PRIO,
                    APP_TASK_TEMPO_PRIO,
                    (OS_STK *)&AppTaskTempoStk[0],
                    APP_TASK_TEMPO_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
					
#if OS_TASK_NAME_SIZE > 13
    OSTaskNameSet(APP_TASK_MAIN_PRIO, "TaskTempo", &err);
#endif
#endif

	// All tasks are started
	return;
}

/*
*********************************************************************************************************
*                                          AppCreateIPCS
*
* Description : This function creates all IPCS objects
* Arguments   : None
*********************************************************************************************************
*/
void AppCreateIPCS()
{
	INT8U perr;

    // Mutex
   	App_MutexCmdToTaskMvt = OSMutexCreate(APP_MUTEX_MVT_PRIO, &perr);
	App_MutexCmdToTaskAsser = OSMutexCreate(APP_MUTEX_ASSER_PRIO, &perr);
	if((NULL == App_MutexCmdToTaskMvt) || (NULL == App_MutexCmdToTaskAsser))
	{
		AppDebugMsg("DEBUG (App.c) : Error -> Unable to create Semaphore or Mutex\n");
		AppDebugMsg("DEBUG (App.c) : Entering in sleeping mode...\n");	
		while(OS_TRUE)		// Infinite Loop
			OSTimeDlyHMSM(1, 0, 0, 0);		
	}

#if APP_USE_DEBUG > 0
   	App_MutexUART1 = OSMutexCreate(APP_MUTEX_UART1_PRIO, &perr);
	App_MutexUART2 = OSMutexCreate(APP_MUTEX_UART2_PRIO, &perr);
#else
   	App_MutexCmdToTaskMvt = NULL;
	App_MutexCmdToTaskAsser = NULL;

#endif

#if APP_QUEUE_SENSORS_SIZE > 0
	// Create an empty queue for asser process
	AppQueueSensors = OSQCreate(AppQSensorsStk, APP_QUEUE_SENSORS_SIZE);
	if(NULL == AppQueueSensors)		// Check if Queue is well created
	{
		AppDebugMsg("DEBUG (App.c) : Error -> Unable to create AsserQueue\n");
		AppDebugMsg("DEBUG (App.c) : Entering in sleeping mode...\n");	

        while(OS_TRUE)		// Infinite Loop
			OSTimeDlyHMSM(1, 0, 0, 0);		
	}
#endif

	// Flags
	AppFlags = OSFlagCreate(APP_PARAM_APPFLAG_INITAL_VALUE, &perr);
	if(NULL == AppFlags)
	{
		AppDebugMsg("DEBUG (App.c) : Error -> Unable to create Appliction Flag\n");
		AppDebugMsg("DEBUG (App.c) : Entering in sleeping mode...\n");	

        while(OS_TRUE)		// Infinite Loop
			OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	// Strategy Flags
	AppStrategyFlags = OSFlagCreate(APP_PARAM_STRATEGYFLAG_INITAL_VALUE, &perr);
	if(NULL == AppStrategyFlags)
	{
		AppDebugMsg("DEBUG (App.c) : Error -> Unable to create Strategy Flag\n");
		AppDebugMsg("DEBUG (App.c) : Entering in sleeping mode...\n");	

        while(OS_TRUE)		// Infinite Loop
			OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	return;
}

/*
*********************************************************************************************************
*                                          AppInitVar
*
* Description : This function initializes globale variables
* Arguments   : None
*********************************************************************************************************
*/
void AppInitVar()
{
	int i;

	// Vars
    AppQueueSensors = NULL;
	AppFlags = NULL;														/* Application Flags							*/
	AppStrategyFlags = NULL;												/* Strategy Flags								*/
	AppCurrentColor = c_NotSet;												/* Set CurrentColor to NotSet					*/
    App_CmdToTaskMvtId = 0;                                               // Var to store MsgID of App_CmdToTaskMvt
    App_CmdToTaskAsserId = 0;                                             // Var to store MsgID of App_CmdToTaskAsser

	// Arrays
#if APP_QUEUE_SENSORS_SIZE > 0
	memset(AppQSensorsStk, 0, sizeof(void*) * APP_QUEUE_SENSORS_SIZE);		/* Set Sensors Queue to NULL					*/
#endif

    memset(AppMsgStk,				0, sizeof(StructMsg) * APP_QUEUES_TOTAL_SIZE);
    memset(&App_CmdToTaskMvt,		0, sizeof(StructCmd) * 1);
    memset(&App_CmdToTaskAsser,		0, sizeof(App_CmdToTaskAsser) * 1);

	// Clear Msg
	for(i=0; i<APP_QUEUES_TOTAL_SIZE; i++)
		AppMsgStk[i].IsRead = OS_TRUE;
	
	return;
}

