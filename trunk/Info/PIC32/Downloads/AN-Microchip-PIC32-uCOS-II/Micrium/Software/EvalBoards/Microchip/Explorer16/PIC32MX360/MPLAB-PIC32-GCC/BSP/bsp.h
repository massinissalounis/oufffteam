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

#include "bsp_peripherals.h"

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define  BSP_CLK_FREQ               72000000
#define  JTAG_ENABLE                DEF_DISABLED
#define  LCD_LINE_1                 0x02
#define  LCD_LINE_2                 0xC0

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/    

void        LED_Toggle          (CPU_INT08U led);
void        LED_Off             (CPU_INT08U led);
void        LED_On              (CPU_INT08U led);


void        BSP_ADCHandler      (void);
void        BSP_UARTHandler     (void);
void        BSP_CNHandler       (void);
void        BSP_TickISR_Handler (void);
void        BSP_Except_Handler  (void);

void        UART_Init           (void);
void        UART_RxStr          (CPU_CHAR *str, CPU_INT16U num);    
void        UART_TxByte         (CPU_CHAR c);
void        UART_TxStr          (CPU_CHAR  *str);
CPU_INT32U  UART_CalcBRG        (CPU_INT32U baud_rate);
CPU_CHAR    UART_RxByte         (void);

void        BSP_InitIO          (void);
void        BSP_IntDisableALL   (void);

void        LCD_Disp            (CPU_INT08U pos, CPU_CHAR *str);

void        BSP_Dly             (CPU_INT32U  us);

CPU_INT16U  ADC_GetVal          (void);
