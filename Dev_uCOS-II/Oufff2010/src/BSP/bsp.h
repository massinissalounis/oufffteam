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


/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define  BSP_CLK_FREQ               80E6

// TMR2 --> Odometer
#define  TMR2_TICK					10E-3
#define  TMR2_PRESCALER				256
#define  TMR2_RELOAD				TMR2_TICK*BSP_CLK_FREQ/TMR2_PRESCALER

// TMR3 --> PWM generation
#define  TMR3_FREQUENCY				30E3
#define  TMR3_TICK					1/TMR3_FREQUENCY
#define  TMR3_PRESCALER				1
#define  TMR3_RELOAD				TMR3_TICK*BSP_CLK_FREQ/TMR3_PRESCALER

#define  UART2_BAUDRATE				115200

#define CLIC_FRONT_LEFT				0
#define CLIC_FRONT_RIGHT			1
#define CLIC_REAR_LEFT				2
#define CLIC_REAR_RIGHT				3

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

void        BSP_InitIO          (void);
void        BSP_IntDisableALL   (void);

void PWM_M0_SetDC(INT16U Duty);
void PWM_M1_SetDC(INT16U Duty);

void        BSP_Dly             (CPU_INT32U  us);

CPU_INT16U  ADC_GetVal          (void);

void PMP_Write(CPU_INT16U address, CPU_INT08U data);
CPU_INT08U PMP_Read(CPU_INT16U address);


void TMR2_Init(void);

