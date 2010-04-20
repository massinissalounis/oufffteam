/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                             (c) Copyright 2006, Micrium, Inc., Weston, FL
*                                           All Rights Reserved
*
*                                          Board Support Package
*                                               Microchip
*                                              Explorer 16
*********************************************************************************************************
*/

#include  <app_cfg.h>
#include  <mini_libdef.h>

#if  uC_PROBE_COM_MODULE == DEF_ENABLED
#include  <probe_com_cfg.h>
#endif

/*
*********************************************************************************************************
*                                        PERIPHERAL DEFINITIONS
*********************************************************************************************************
*/   
                                                                        /* Define enabled peripherals                               */
#define  _TMR1
#define  _UART1                                                         /* UART1 is not connected on the Explorer 16                */
#define  _UART2                                                         /* The RS-232 connector on the Explorer 16 is tied to UART2 */

#define  BSP_UART1      1
#define  BSP_UART2      2

/*
*********************************************************************************************************
*                                       PERIPHERAL CONFIGURATIONS
*********************************************************************************************************
*/

#define  BSP_BAUD_RATE  57600

#if  PROBE_COM_METHOD_RS232 == DEF_TRUE
#define  BSP_UART       BSP_UART1
#else
#define  BSP_UART       BSP_UART2
#endif

