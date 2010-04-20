/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                             (c) Copyright 1998-2006, Micrium, Weston, FL
*                                          All Rights Reserved
*
*
*                                            MIPS Sample code
*
* File : APP.C
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

static  OS_STK       AppTaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_STK       AppTask1Stk[APP_TASK1_STK_SIZE];
static  OS_STK       AppTask2Stk[APP_TASK2_STK_SIZE];

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void        AppTaskStart(void *p_arg);
static  void        AppTask1(void *p_arg);
static  void        AppTask2(void *p_arg);
static  void        AppTaskCreate(void);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.
*
* Arguments   : none
*********************************************************************************************************
*/

#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_18, FPLLIDIV = DIV_2, FWDTEN = OFF, FPBDIV = DIV_1, POSCMOD = XT, FNOSC = PRIPLL, CP = OFF

int  main (void)
{
    CPU_INT08U  err;


    BSP_IntDisAll();                                                    /* Disable all interrupts until we are ready to accept them */

    OSInit();                                                           /* Initialize "uC/OS-II, The Real-Time Kernel"              */

    OSTaskCreateExt(AppTaskStart,                                       /* Create the start task                                    */
                    (void *)0,
                    (OS_STK *)&AppTaskStartStk[APP_TASK_START_STK_SIZE - 1],
                    APP_TASK_START_PRIO,
                    APP_TASK_START_PRIO,
                    (OS_STK *)&AppTaskStartStk[0],
                    APP_TASK_START_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 13
    OSTaskNameSet(APP_TASK_START_PRIO, "Startup", &err);
#endif

    OSStart();                                                          /* Start multitasking (i.e. give control to uC/OS-II)       */
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
#if CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL
    CPU_SR  cpu_sr;
#endif
    CPU_INT08U  i;
    CPU_INT08U  j;

    (void)p_arg;

    BSP_InitIO();                                                       /* Initialize BSP functions                                 */

#if PROBE_COM_METHOD_RS232 == DEF_FALSE
    UART_Init();                                                        /* Initialize serial port                                   */
#endif

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                                       /* Determine CPU capacity                                   */
#endif

#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
    AppProbeInit();                                                     /* Initialize uC/Probe modules                              */
#endif
    
    AppTaskCreate();                                                    /* Create application tasks                                 */
    
    while (OS_TRUE) {                                                   /* Task body, always written as an infinite loop.            */
        for (j = 0; j < 2; j++) {
            for (i = 1; i < 9; i++) {
                LED_Toggle(i);
                OSTimeDlyHMSM(0, 0, 0, ADC_GetVal() + 10);
            }
            
            for (i = 0; i < 8; i++) {
                LED_Toggle(0);
                OSTimeDlyHMSM(0, 0, 0, ADC_GetVal() + 10);
            }
        }
        
        for ( ; j > 0; j--) {        
            for (i = 9; i > 0; --i) {        
                LED_Toggle(i);
                OSTimeDlyHMSM(0, 0, 0, ADC_GetVal() + 10);
            }    
            
            for (i = 0; i < 8; i++) {
                LED_Toggle(0);
                OSTimeDlyHMSM(0, 0, 0, ADC_GetVal() + 10);
            }
        }
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                        CREATE APPLICATION TASKS
*
* Description: This function creates the application tasks.
*
* Arguments  : none.
*
* Note(s)    : none.
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
    CPU_INT08U  err;
    
    
    OSTaskCreateExt(AppTask1,                                           /* Create start task 1                                      */
                   (void *)0,
                   (OS_STK *)&AppTask1Stk[APP_TASK1_STK_SIZE - 1],
                    APP_START_TASK1_PRIO,
                    APP_START_TASK1_PRIO,
                   (OS_STK *)&AppTask1Stk[0],
                    APP_TASK1_STK_SIZE,
                   (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
                    
#if OS_TASK_NAME_SIZE > 7
    OSTaskNameSet(APP_START_TASK1_PRIO, (CPU_CHAR *)"Task 1", &err);
#endif

    OSTaskCreateExt(AppTask2,                                           /* Create start task 1                                      */
                   (void *)0,
                   (OS_STK *)&AppTask2Stk[APP_TASK2_STK_SIZE - 1],
                    APP_START_TASK2_PRIO,
                    APP_START_TASK2_PRIO,
                   (OS_STK *)&AppTask2Stk[0],
                    APP_TASK2_STK_SIZE,
                   (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
                    
#if OS_TASK_NAME_SIZE > 7
    OSTaskNameSet(APP_START_TASK1_PRIO, (CPU_CHAR *)"Task 2", &err);
#endif
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                          STARTUP TASK 1
*
* Description : This is an example of a startup task. This task initializes the call back function for
*               uC Probe and displays the number of transmits through Probe.
*
* Arguments   : p_arg   is the argument passed to 'AppTask1()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

void  AppTask1 (void *p_arg)
{
    CPU_INT32U  i;
    CPU_CHAR    tx_num[16];
    
    
    i         =  0;
    tx_num[0] = 'T';
    tx_num[1] = 'x';
    tx_num[2] = ' ';
    tx_num[3] = '#';
    
    while (1) {
        i++;
        tx_num[4]  =  i / 1000000000  + '0';
        tx_num[5]  = (i % 100000000)  / 10000000 + '0';
        tx_num[6]  = (i % 10000000)   / 1000000  + '0';
        tx_num[7]  = (i % 1000000)    / 100000   + '0';
        tx_num[8]  = (i % 100000)     / 10000    + '0';
        tx_num[9]  = (i % 10000)      / 1000     + '0';
        tx_num[10] = (i % 1000)       / 100      + '0';
        tx_num[11] = (i % 100)        / 10       + '0';
        tx_num[12] =  i % 10          + '0';
        tx_num[13] = '\r';
        tx_num[14] = '\n';
        tx_num[15] = '\0';     
        
#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
        ProbeCom_TxStr((CPU_CHAR *)&tx_num, 100);
#else
        UART_TxStr((CPU_CHAR *)&tx_num);
#endif
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                          STARTUP TASK 2
*
* Description : This is an example of a startup task. This task displays a message on the debug LCD.
*
* Arguments   : p_arg   is the argument passed to 'AppTask2()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

void  AppTask2(void *p_arg)
{
    CPU_INT08U   i;
    CPU_INT08U   j;
    CPU_INT08U   dir1;
    CPU_INT08U   dir2;
    CPU_CHAR     str1[26];
    CPU_CHAR     str2[25];
    CPU_CHAR    *tmp_str;
     
    i       = 0;
    j       = 0;
    dir1    = 0;
    dir2    = 0;
    tmp_str = (CPU_CHAR *)"         Micrium         ";
    
    while (*tmp_str) {
        str1[i++] = *tmp_str++;
    }
    
    i       = 0;
        
    tmp_str = (CPU_CHAR *)"        uC/OS-II        ";    
    
    while (*tmp_str) {
        str2[i++] = *tmp_str++;
    }
    
    i        = 0;
    
    while (1) {
        if (str1[i] != ' ') {
            dir1 = 1;
        }
        
        str1[i + 16] = '\0'; 
        LCD_Disp(LCD_LINE_1, &str1[i]);
        str1[i + 16] = ' ';
        
        if (dir1 == 0) {
            i++;
        } else {
            i--;
            
            if (i == 0) {
                dir1 = 0;
            }    
        }      
        
        if (str2[j] != ' ') {
            dir2 = 1;
        }      
        
        str2[j + 16] = '\0';
        LCD_Disp(LCD_LINE_2, &str2[j]);
        str2[j + 16] = ' ';
    
        if (dir2 == 0) {
            j++;
        } else {
            j--;
            
            if (j == 0) {
                dir2 = 0;
            }
        }
        
        OSTimeDlyHMSM(0, 0, 0, 300);
    }
}    
