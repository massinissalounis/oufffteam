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
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : Hong Soong
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/
                                                                        /* DEF_ENABLED = Present, DEF_DISABLED = Not Present        */
#define  uC_PROBE_OS_PLUGIN              DEF_DISABLED                 
#define  uC_PROBE_COM_MODULE             DEF_DISABLED

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  OS_TASK_TMR_PRIO                      0
#define  APP_TASK_START_PRIO                   4
#define  APP_START_TASK1_PRIO                  5
#define  APP_START_TASK2_PRIO                  6

#if  uC_PROBE_OS_PLUGIN == DEF_ENABLED

#define  OS_PROBE_TASK_PRIO                    7

#endif

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE            175
#define  APP_TASK1_STK_SIZE                 175
#define  APP_TASK2_STK_SIZE                 175

#if  uC_PROBE_OS_PLUGIN == DEF_ENABLED

#define  OS_PROBE_TASK_STK_SIZE             175

#endif

/*
*********************************************************************************************************
*                               uC/Probe plug-in for uC/OS-II CONFIGURATION
*********************************************************************************************************
*/

#if  uC_PROBE_OS_PLUGIN == DEF_ENABLED

#define  OS_PROBE_TASK                         1                /* Task will be created for uC/Probe OS Plug-In.            */
#define  OS_PROBE_TMR_32_BITS                  1                /* uC/Probe OS Plug-In timer is a 16-bit timer.             */
#define  OS_PROBE_HOOKS_EN                     1                /* Hooks to update OS_TCB profiling members are included.   */
#define  OS_PROBE_TASK_ID     OS_PROBE_TASK_PRIO
#define  OS_PROBE_USE_FP                       0                /* Use floating point for uC/Probe                          */ 
#define  PROBE_BAUD_RATE                   57600

#endif

#endif
