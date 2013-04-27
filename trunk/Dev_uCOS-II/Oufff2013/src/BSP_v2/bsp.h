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
// CBE	21/05/2011	Remplacement des PORTx ,BIT_n par un define dans bsp.h pour facilité les changements de brochage


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

#define  UART1_BAUDRATE				115200
#define  UART2_BAUDRATE				115200

// **** Affectation des périphériques sur les IO du PIC ****
// ****** Carte debug ******
#ifdef _TARGET_440H
	#define SW1							10		// Switch 1
	#define SW2							11		// Switch 2
	#define SW3							12		// Switch 3
	#define LED_USB						1		// Led USB
	#define LED_SD						2		// Led SD
	#define LED_FLASH					3		// Led Flash
	#define LED_ERR						4		// Led Error

#else
// ****** Carte mère ******
	#define CLIC_1						0		// connecteur 1
	#define CLIC_2						1		// connecteur 2
	#define CLIC_3						2		// connecteur 3
	#define CLIC_4						3		// connecteur 4

	// correspondance pin PIC_ADC_xx de la carte mère avec l'entrée analogique du PIC ANx
	#define PIC_ADC_AN0					2
	#define PIC_ADC_AN1					3
	#define PIC_ADC_AN2					4
	//#define PIC_ADC_AN3					NON CONNECTE
	#define PIC_ADC_AN4					6
	#define PIC_ADC_AN5					7
	#define PIC_ADC_AN6					8
	#define PIC_ADC_AN7					9
	#define PIC_ADC_AN8					10
	#define PIC_ADC_AN9					11
	
	// correspondance GP2_x avec la pin PIC_ADC_xx de la carte mère
	
	#define GP2_1						PIC_ADC_AN0
	#define GP2_2						PIC_ADC_AN2
	#define GP2_3						PIC_ADC_AN4
	#define GP2_4						PIC_ADC_AN6
	#define GP2_5						PIC_ADC_AN8
	#define GP2_6						PIC_ADC_AN9
	#define GP2_7						PIC_ADC_AN7
	#define GP2_8						PIC_ADC_AN5
	//#define GP2_9						PIC_ADC_AN3 //AN3 NON CONNECTE NE PAS UTILISER
	#define GP2_10						PIC_ADC_AN1

	#define GP2_REAR_INTERNAL				GP2_3
	#define GP2_REAR_HOOP					GP2_8
	#define GP2_FRONT					GP2_7
	
	#define IO_CLIC_1					IOPORT_G, BIT_0
	#define IO_CLIC_2					IOPORT_A, BIT_7
	#define IO_CLIC_3					IOPORT_F, BIT_0
	#define IO_CLIC_4					IOPORT_C, BIT_4
	
	#define IO_START					IOPORT_F, BIT_1
	#define IO_COLOR					IOPORT_D, BIT_2
	
	#define IO_LED1						LED_NON_DEFINIE
	#define IO_LED2						LED_NON_DEFINIE
	#define IO_LED3						IOPORT_D, BIT_11
	#define IO_LED4						IOPORT_C, BIT_14
	#define IO_LED5						IOPORT_D, BIT_13
	
	#define IO_Motor_dir_0				IOPORT_C, BIT_1
	#define IO_Motor_dir_1				IOPORT_C, BIT_2
	
#endif

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/    

void        LED_Toggle          (CPU_INT08U led);
void        LED_Off             (CPU_INT08U led);
void        LED_On              (CPU_INT08U led);
void        LED_Init            (void);

void        BSP_ADCHandler      (void);
void        BSP_UARTHandler     (void);
void        BSP_CNHandler       (void);
void        BSP_TickISR_Handler (void);
void        BSP_Except_Handler  (void);

void        BSP_InitIO          (void);
void        BSP_IntDisableALL   (void);

void 		PWM_M0_SetDC(INT16U Duty);
void 		PWM_M1_SetDC(INT16U Duty);

void        BSP_Dly             (CPU_INT32U  us);

void PMP_Write(CPU_INT16U address, CPU_INT08U data);
CPU_INT08U PMP_Read(CPU_INT16U address);


void TMR2_Init(void);

void  ADC_Init (void);
CPU_INT16U  ADC_GetVal (CPU_INT08U channel_to_convert);

CPU_INT08U START_State (void);
CPU_INT08U COLOR_Read (void);
