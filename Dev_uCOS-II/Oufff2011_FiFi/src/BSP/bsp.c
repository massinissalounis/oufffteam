/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                              (c) Copyright 2006, Micrium, Inc., Weston, FL
*                                           All Rights Reserved
*
*                                          Board Support Package
*                                               Oufff TEAM
*                                               O'CORE
*********************************************************************************************************
*/
// CBE	21/05/2011	Remplacement des PORTx ,BIT_n par un define dans bsp.h pour facilité les changements de brochage


#include "AppIncludes.h"
#include "osc.h"
#include "system.h"
#include "timer.h"
#include "uart.h"
#include "adc10.h"
#include "ports.h"
#include "pmp.h"
#include "outcompare.h"
#include "attribs.h"

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define  BSP_TMR_RELOAD          (BSP_CLK_FREQ / (2 * OS_TICKS_PER_SEC))
#define  BSP_DLY_CONST            BSP_CLK_FREQ / 1000000 

#define  PB0_MASK                 _PORTD_RD13_MASK
#define  PB0_TRIS                 TRISDbits.TRISD13
#define  PB0_IO                   LATDbits.LATD13
#define  PB0                      PORTDbits.RD13

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL FUNCTIONS
*********************************************************************************************************
*/

void	Tmr_Init    (void);

void	UART_Init   (void);

void	PB_IntInit  (void);
void	PB_Config   (void);
void	PB_Init     (void);

void	ADC_TmrInit (void);
void	ADC_IntInit (void);
void	ADC_Config  (void);

void	PMP_Init    (void);

#ifdef _TARGET_440H
void	LCD_Init	(void);
#endif

///////////////////////////////////////////////////////////
// GP2 FUNCTIONS
///////////////////////////////////////////////////////////

void GP2_Init (void)
{

}

void GP2_Read (void)
{

}

///////////////////////////////////////////////////////////
// SWITCH FUNCTIONS
///////////////////////////////////////////////////////////

void CLIC_Init (void)
{
#ifdef _TARGET_440H
	PORTSetPinsDigitalIn(IOPORT_B, BIT_3);
	PORTSetPinsDigitalIn(IOPORT_B, BIT_2);
	PORTSetPinsDigitalIn(IOPORT_B, BIT_4);
#else
	PORTSetPinsDigitalIn(IO_CLIC_1);
	PORTSetPinsDigitalIn(IO_CLIC_2);
	PORTSetPinsDigitalIn(IO_CLIC_3);
	PORTSetPinsDigitalIn(IO_CLIC_4);
#endif
}

CPU_INT08U CLIC_state (CPU_INT08U clic)
{
	CPU_INT08U state = 0;

    switch (clic) {
#ifdef _TARGET_440H
        case SW1:
			if(PORTReadBits(IOPORT_B, BIT_3)==0) state = 1;
			break;

        case SW2:
			if(PORTReadBits(IOPORT_B, BIT_2)==0) state = 1;
			break;

        case SW3:
			if(PORTReadBits(IOPORT_B, BIT_4)==0) state = 1;
			break;
#else
        case CLIC_1:
			if(PORTReadBits(IO_CLIC_1)==0) state = 1;
			break;

        case CLIC_2:
			if(PORTReadBits(IO_CLIC_2)==0) state = 1;
			break;

        case CLIC_3:
			if(PORTReadBits(IO_CLIC_3)==0) state = 1;
			break;

        case CLIC_4:
			if(PORTReadBits(IO_CLIC_4)==0) state = 1;
			break;
#endif
        default:
             break;
    }
	return state;
}

void START_Init (void)
{
#ifdef _TARGET_440H
#else
	PORTSetPinsDigitalIn(IO_START);
#endif
}

CPU_INT08U START_State (void)
{
#ifdef _TARGET_440H
	CLIC_state(SW2);
#else
	if(PORTReadBits(IO_START)!=0) 
		return 1;
	else
		return 0;
#endif
}	

void COLOR_Init (void)
{
#ifdef _TARGET_440H
#else
	PORTSetPinsDigitalIn(IO_COLOR);
#endif
}

CPU_INT08U COLOR_Read (void)
{
#ifdef _TARGET_440H
	CLIC_state(SW1);
#else
	if(PORTReadBits(IO_COLOR)!=0) 
		return 1;
	else
		return 0;
#endif
}

///////////////////////////////////////////////////////////
// PWM FUNCTIONS
///////////////////////////////////////////////////////////
void PWM_M1_SetDC(INT16U Duty)
{	
	SetDCOC2PWM((TMR3_RELOAD * Duty)/65536); 
}

void PWM_M0_SetDC(INT16U Duty)
{	
	SetDCOC1PWM((TMR3_RELOAD * Duty)/65536); 
}

void PWM_Init(void)
{
#ifdef _TARGET_440H
#else
	// Tmr1 Init
	// STEP 1. configure the Timer1
	OpenTimer3(T3_ON | T3_SOURCE_INT | T3_IDLE_CON | T3_PS_1_1, TMR3_RELOAD);

    // Enable OC | 16 bit Mode  | Timer1 is selected | Continuous O/P   | OC Pin High , S Compare value, Compare value
    OpenOC1( OC_ON | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE , 0, 0 );
    OpenOC2( OC_ON | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE , 0, 0 );
#endif
}



///////////////////////////////////////////////////////////
// TIMER2 FUNCTIONS
///////////////////////////////////////////////////////////

void TMR2_Init(void)
{
#ifdef _TARGET_440H
#else
	// STEP 1. configure the Timer2
	OpenTimer2(T2_ON | T2_SOURCE_INT | T2_IDLE_CON | T2_PS_1_256, TMR2_RELOAD);
	// STEP 2. set the timer interrupt to prioirty level 6
	ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_6);
	mT2ClearIntFlag();
#endif
}

// Timer 2 ISR
// Specify Interrupt Priority Level = 6

void __ISR(_TIMER_2_VECTOR, ipl6) TMR2_Handler(void)
{
	// clear the interrupt flag
	mT2ClearIntFlag();
	// QUAD LATCH
	position_manager_timer_handler();
}


///////////////////////////////////////////////////////////
// PMP FUNCTIONS
///////////////////////////////////////////////////////////

void  PMP_Init (void)
{
#ifdef _TARGET_440H
#else
	unsigned int control =  PMP_ON | PMP_IDLE_CON | PMP_MUX_DATA8_ALL | PMP_READ_WRITE_EN |\
                     		PMP_CS2_CS1_OFF | PMP_LATCH_POL_HI | PMP_CS2_POL_HI | PMP_CS1_POL_HI |\
                     		PMP_WRITE_POL_HI | PMP_READ_POL_HI;

	unsigned int mode = PMP_IRQ_OFF | PMP_AUTO_ADDR_OFF | PMP_DATA_BUS_8 | PMP_MODE_MASTER2 |\
                     	PMP_WAIT_BEG_3 | PMP_WAIT_MID_7 | PMP_WAIT_END_3;

	unsigned int port = PMP_PEN_OFF | PMP_PEN_0 | PMP_PEN_1;

	unsigned int interrupt = PMP_INT_OFF;

    mPMPOpen(control, mode, port, interrupt);
#endif
}

void PMP_Write(CPU_INT16U address, CPU_INT08U data)
{
#ifdef _TARGET_440H
#else
	PMPSetAddress(address);
    PMPMasterWrite(data);
#endif
}

CPU_INT08U PMP_Read(CPU_INT16U address)
{
#ifdef _TARGET_440H
#else
	CPU_INT08U value;
	PMPSetAddress(address);
	PMPMasterRead(); // Read the previous value and start a read operation onto PMP
    value = mPMPMasterReadByte(); // Read the actual latched value
	return value;
#endif
}

///////////////////////////////////////////////////////////
// IO FUNCTIONS FUNCTIONS
///////////////////////////////////////////////////////////

void IO_M0_SetDirection(unsigned char dir)
{
#ifdef _TARGET_440H
#else
	if(dir==0)
	{
		PORTClearBits(IO_Motor_dir_0);
	}
	else
	{
		PORTSetBits(IO_Motor_dir_0);
	}
#endif
}

void IO_M1_SetDirection(unsigned char dir)
{
#ifdef _TARGET_440H
#else
	if(dir==0)
	{
		PORTClearBits(IO_Motor_dir_1);
	}
	else
	{
		PORTSetBits(IO_Motor_dir_1);
	}
#endif
}

/*
*********************************************************************************************************
*                                                 LED ON
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to control
*                      0    indicates that you want ALL the LEDs to be ON
*                      1    turns ON LED1
*                      2    turns ON LED2
*                      3    turns ON LED3
*                      4	turns ON LED4
*                      5	turns ON LED5
*********************************************************************************************************
*/

void  LED_On (CPU_INT08U led)
{
    switch (led) {
		case 0:
			#ifdef _TARGET_440H
        	 PORTClearBits(IOPORT_D, BIT_6 | BIT_7);
        	 PORTClearBits(IOPORT_F, BIT_0 | BIT_1);
			#else
			 //PORTSetBits(IO_LED1);
			 //PORTSetBits(IO_LED2);
			 PORTSetBits(IO_LED3);
			 PORTSetBits(IO_LED4);
			 PORTSetBits(IO_LED5);
   			#endif
			break;
		case 1:
			#ifdef _TARGET_440H
        	 PORTClearBits(IOPORT_D, BIT_7);
			 #else
			 //PORTSetBits(IO_LED1);
			#endif
			break;

		case 2:
			#ifdef _TARGET_440H
        	#else
			 //PORTSetBits(IO_LED2);
			#endif
			break;

        case 3:
            #ifdef _TARGET_440H
        	 PORTClearBits(IOPORT_F, BIT_0);
			#else
			 PORTSetBits(IO_LED3);
			#endif
			break;
        case 4:
            #ifdef _TARGET_440H
        	 PORTClearBits(IOPORT_F, BIT_1);
			#else
             PORTSetBits(IO_LED4);
			#endif
			break;
        case 5:
            #ifdef _TARGET_440H
			#else
             PORTSetBits(IO_LED5);
			#endif
			break;
        default:
             break;
    }
}

/*
*********************************************************************************************************
*                                                LED OFF
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to turn OFF
*                      0    indicates that you want ALL the LEDs to be OFF
*                      1    turns OFF LED1
*                      2    turns OFF LED2
*                      3    turns OFF LED3
*                      4	turns OFF LED4
*                      5	turns OFF LED5
*********************************************************************************************************
*/

void  LED_Off (CPU_INT08U led)
{
    switch (led) {
        case 0:
            #ifdef _TARGET_440H
			 PORTSetBits(IOPORT_D, BIT_6 | BIT_7);
			 PORTSetBits(IOPORT_F, BIT_0 | BIT_1);
			#else
			 //PORTClearBits(IO_LED1);
			 //PORTClearBits(IO_LED2);
			 PORTClearBits(IO_LED3);
			 PORTClearBits(IO_LED4);
			 PORTClearBits(IO_LED5);
			#endif
            break;
        case 1:
            #ifdef _TARGET_440H
			 PORTSetBits(IOPORT_D, BIT_7);
			#else
			//PORTClearBits(IO_LED1);
			#endif
            break;
        case 2:
            #ifdef _TARGET_440H
			 PORTSetBits(IOPORT_D, BIT_6);
			#else
			//PORTClearBits(IO_LED2);
			#endif
            break;
        case 3:
            #ifdef _TARGET_440H
			 PORTSetBits(IOPORT_F, BIT_0);
			#else
             PORTClearBits(IO_LED3);
			#endif
            break;
        case 4:
            #ifdef _TARGET_440H
			 PORTSetBits(IOPORT_F, BIT_1);
			#else
             PORTClearBits(IO_LED4);
			#endif
            break;
        case 5:
            #ifdef _TARGET_440H
			#else
             PORTClearBits(IO_LED5);
			#endif
            break;
		default:
             break;
    }
}

/*
*********************************************************************************************************
*                                              LED TOGGLE
*
* Description : This function is used to alternate the state of an LED
*
* Arguments   : led    is the number of the LED to control
*                      0    indicates that you want ALL the LEDs to toggle
*                      1	toggle LED1
*                      2	toggle LED2
*                      3	toggle LED3
*                      4	toggle LED4
*                      5    toggle LED5
*********************************************************************************************************
*/

void  LED_Toggle (CPU_INT08U led)
{
    switch (led) {
        case 0:
            #ifdef _TARGET_440H
        	 PORTToggleBits(IOPORT_D, BIT_6 | BIT_7);
        	 PORTToggleBits(IOPORT_F, BIT_0 | BIT_1);
			#else
			 //PORTToggleBits(IO_LED1);
			 //PORTToggleBits(IO_LED2);
        	 PORTToggleBits(IO_LED3);
        	 PORTToggleBits(IO_LED4);
        	 PORTToggleBits(IO_LED5);
			#endif
            break;
        case 1:
            #ifdef _TARGET_440H
        	 PORTToggleBits(IOPORT_D, BIT_7);
			#else
			//PORTToggleBits(IO_LED1);
			#endif
            break;
        case 2:
            #ifdef _TARGET_440H
        	 PORTToggleBits(IOPORT_D, BIT_6);
			#else
			//PORTToggleBits(IO_LED2);
			#endif
            break;
        case 3:
            #ifdef _TARGET_440H
        	 PORTToggleBits(IOPORT_F, BIT_0);
			#else
             PORTToggleBits(IO_LED3);
			#endif
            break;
        case 4:
            #ifdef _TARGET_440H
        	 PORTToggleBits(IOPORT_F, BIT_1);
			#else
             PORTToggleBits(IO_LED4);
			#endif
            break;
        case 5:
            #ifdef _TARGET_440H
			#else
             PORTToggleBits(IO_LED5);
			#endif
            break;
        default:
             break;
    }
}

/*
*********************************************************************************************************
*                                       LED_Init()
*
* Description: This function initializes all of the board's leds
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  LED_Init (void) 
{
    LED_Off(0);                                                               /* Turn off all of the LEDs                   */
}

/*
*********************************************************************************************************
*                                          INITIALIZE I/Os
*
* Description : This function initializes the GPIO pins.  All the I/O pins are initialized in this function
*               so you don't have to look at multiple places for I/O initialization.
*
* Arguments   : None
*
*********************************************************************************************************
*/

void  BSP_IO_Init (void)
{
#ifdef _TARGET_440H
	// Each LED pin is set up as an output
	PORTSetPinsDigitalOut(IOPORT_D, BIT_6 | BIT_7);
	PORTSetPinsDigitalOut(IOPORT_F, BIT_0 | BIT_1);
	DisableCN0;
#else
	// Each LED pin is set up as an output
	
	//PORTSetPinsDigitalOut(IO_LED1);
	//PORTSetPinsDigitalOut(IO_LED2);
	PORTSetPinsDigitalOut(IO_LED3);
	PORTSetPinsDigitalOut(IO_LED4);
	DisableCN0;
	PORTSetPinsDigitalOut(IO_LED5);

	// Motor direction
	PORTSetPinsDigitalOut(IO_Motor_dir_0);
	PORTSetPinsDigitalOut(IO_Motor_dir_1);
	
	START_Init();
	COLOR_Init();
#endif

	CLIC_Init();
	
}

/*
*********************************************************************************************************
*                                       Tmr_Init()
*
* Description: This function should intialize the timers used by your application
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  Tmr_Init (void)
{
    OpenCoreTimer(BSP_TMR_RELOAD);                                            // Initialize the Count and Compare registers                                              
    mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_3));                        // Enable the core timer's interrupt
}

/*
*********************************************************************************************************
*                                  BSP_TickISR_Handler()
*
* Description : 
*
* Arguments   : None
*********************************************************************************************************
*/

void  BSP_TickISR_Handler (void)
{
    mCTClearIntFlag();                                                        // Clear the core timer interrupt             
    UpdateCoreTimer(BSP_TMR_RELOAD);                                          // Prepare for the next core timer interrupt  
}

/*
*********************************************************************************************************
*                                    BSP_Except_Handler()
*
* Description: This function offers a means of servicing exceptions that are not triggered by interrupts
*              or the syscall instruction.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_Except_Handler (void)
{
}

/*
*********************************************************************************************************
*                                    UART_Handler()
*
* Description: This function handles interrupts from the UART.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

//void __ISR(_UART_2_VECTOR, ipl2) UART_Handler (void)
//{
//    CPU_INT32U  status;
//    CPU_INT32U  int_en;

//#define  BSP_UART_PUTCHAR(x)      putcUART2(x)
//#define  BSP_UART_DATARDY()       DataRdyUART2()
//#define  BSP_UART_GETCHAR()       ReadUART2()
//#define  BSP_UART_INTCONFIG(x)    ConfigIntUART2(x)
//#define  BSP_UART_START(x, y, z)  OpenUART2(x, y, z)
//#define  BSP_UART_INTENABLE(x)    EnIntUART2(x)
//#define  BSP_UART_INTDISABLE(x)   DisIntUART2(x)
//#define  BSP_UART_INTEN           IEC1
//#define  BSP_UART_INTSTAT         IFS1
//#define  BSP_UART_INTCLR          IFS1CLR
//#define  BSP_UART_INTMASK         0x00000700
//#define  BSP_UART_INTTX           0x00000400
//#define  BSP_UART_INTRX           0x00000200
//#define  BSP_UART_INTERR          0x00000100

    
    
//    status           = BSP_UART_INTSTAT;                                /* Read the interrupt status register               */
//    int_en           = BSP_UART_INTEN;                                  /* Read the interrupt enabled register              */
    
//    status          &= BSP_UART_INTMASK;                                /* Mask all other interrupts                        */
//    BSP_UART_INTCLR  = status;                                          /* Clear all triggered interrupts                   */
//    status          &= int_en;                                          /* Mask non-enabled interrupts                      */
    
//    if (status & BSP_UART_INTRX) {                                      /* If a Rx interrupt has occured and is enabled...  */
//        UART_TxByte(UART_RxByte());                                     /* Notify Probe and provide the incoming character  */
//    }
//}

/*
*********************************************************************************************************
*                                      UART_Init()
*
* Description: This function performs all necessary initializations on the UART.
*
* Arguments  : baud_rate    The desired baud rate for the UART
*
* Returns    : None
*********************************************************************************************************
*/

void  UART_Init (void)
{
    CPU_INT08U  config;
    CPU_INT32U  config1;
    CPU_INT32U  config2;
       
    config1 = UART_EN                                                   // UART module enabled                              
            | UART_IDLE_CON                                             // UART works in IDLE mode                          
            | UART_RX_TX                                                // Communication is done through the normal pins    
            | UART_DIS_WAKE                                             // Disable Wake-up on START bit detect during SLEEP
            | UART_DIS_LOOPBACK                                         // Disable loop back                               
            | UART_DIS_ABAUD                                            // Input to capture module from ICx pin           
            | UART_NO_PAR_8BIT                                          // 8 bits no parity                               
            | UART_1STOPBIT                                             // 1 stop bit                                      
            | UART_IRDA_DIS                                             // IrDA disabled                                    
            | UART_MODE_FLOWCTRL                                        // UART pins in flow control mode                   
            | UART_DIS_BCLK_CTS_RTS                                     // Disable BCLK, CTS, and RTS pins                  
            | UART_NORMAL_RX                                            // UxRX idle stat is '1'                            
            | UART_BRGH_SIXTEEN;                                        // 16x baud clock                                   
//            
    config2 = UART_TX_PIN_LOW                                           // IrDA encoded UxTx idle stat is '0'               
 //           | UART_RX_ENABLE                                            // Enable UxRx pin                                  
            | UART_TX_ENABLE                                            // Enable UxTx pin                                  
 //           | UART_INT_TX                                               // Interrupt on trasnfer of each character to TSR   
 //           | UART_INT_RX_CHAR                                          // Interrupt on every char received                 
            | UART_ADR_DETECT_DIS                                       // Disable 9-bit address detect                     
            | UART_RX_OVERRUN_CLEAR;                                    // Rx buffer overrun status bit clear               
            
//    config1 = UART_EN;                                                   // UART module enabled                              
                                   
//    config2 = UART_TX_ENABLE;                                            // Enable UxTx pin 
                                 
    OpenUART2(config1, config2, BSP_CLK_FREQ / (16 * UART2_BAUDRATE) - 1);  // Configure the settings                           

//    config = UART_INT_PR3
//           | UART_INT_SUB_PR0
//           | UART_RX_INT;
           
//	ConfigIntUART2(config);
 
}

/*
*********************************************************************************************************
*                                     BSP_ADCHandler()
*
* Description: This function handles ADC interrupts.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_ADCHandler (void)
{
                                                                        /* Insert application code here                             */
    mAD1ClearIntFlag();                                                 /* Clear the interrupt before exiting ISR                   */
}

/*
*********************************************************************************************************
*                                       ADC_Init()
*
* Description: This function performs the initialization for the ADC.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  ADC_Init (void)
{
	//!!!!!!!! PORTB BIT_2 --> GP2_6 ne fonctionne pas !!!!!!!!!! CBE 29/04/2010
	//Disable all comparators
	DisableCN2;
	DisableCN4;
	DisableCN6;
	DisableCN8;
	DisableCN10;
	DisableCN11;
	PORTSetPinsAnalogIn(IOPORT_B, BIT_2 | BIT_4 | BIT_6 | BIT_8 | BIT_10 | BIT_11);	// Set AN pin as analog input.
	CloseADC10();														// ensure the ADC is off before setting the configuration
    ADC_Config();                                                       /* Configure ADC settings                           */
    EnableADC10();                                                      /* Enable the ADC                                   */
}

/*
*********************************************************************************************************
*                                     ADC_Config()
*
* Description: This function performs the configuration of the ADC.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  ADC_Config (void) 
{
    CPU_INT32U  config1;
    CPU_INT32U  config2;
    CPU_INT32U  config3;
    CPU_INT32U  config4;
    CPU_INT32U  config5;
      
    config1 = ADC_IDLE_STOP
            | ADC_FORMAT_INTG
            | ADC_CLK_AUTO
            | ADC_AUTO_SAMPLING_ON
            | ADC_SAMP_ON;
            
    config2 = ADC_VREF_AVDD_AVSS
            | ADC_OFFSET_CAL_DISABLE
            | ADC_SCAN_OFF
            | ADC_SAMPLES_PER_INT_1
            | ADC_ALT_BUF_ON
            | ADC_ALT_INPUT_OFF;
    
    config3 = ADC_SAMPLE_TIME_0
            | ADC_CONV_CLK_INTERNAL_RC
            | ADC_CONV_CLK_Tcy2;
           
    config4 = ENABLE_AN2_ANA | ENABLE_AN4_ANA | ENABLE_AN6_ANA | ENABLE_AN8_ANA | ENABLE_AN10_ANA | ENABLE_AN11_ANA;
    
	config5 = SKIP_SCAN_ALL;

	// configure to sample AN4
	SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN1 ); //|  ADC_CH0_NEG_SAMPLEB_NVREF | ADC_CH0_POS_SAMPLEB_AN5); // configure to sample AN4 & AN5
    OpenADC10(config1, config2, config3, config4, config5);
}

/*
*********************************************************************************************************
*                                     ADC_IntInit()
*
* Description: This function intializes the ADC interrupt.
*
	* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  ADC_IntInit (void)
{
//    mAD1SetIntPriority(INT_PRIORITY_LEVEL_3);                           /* Set interrupt priority level to 3                        */
//    mAD1ClearIntFlag();                                                 /* Clear interrupt flag, just in case                       */
//    mAD1IntEnable(1);                                                   /* Enable interrupts                                        */
}
        

/*
*********************************************************************************************************
*                                     ADC_GetVal()
*
* Description: This function returns the ADC value.
*
* Arguments  : GP2 chanel to convert
*
* Returns    : converted value
*********************************************************************************************************
*/

CPU_INT16U  ADC_GetVal (CPU_INT08U channel_to_convert)
{
    CPU_INT08U  buffer;
    CPU_INT32U  config;   

	switch (channel_to_convert)
		{
		case 0: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN0; break;
		case 1: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN1; break;
		case 2: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN2; break;
		case 3: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN3; break;
		case 4: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN4; break;
		case 5: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN5; break;
		case 6: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN6; break;
		case 7: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN7; break;
		case 8: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN8; break;
		case 9: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN9; break;
		case 10: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN10; break;
		case 11: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN11; break;
		case 12: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN12; break;
		case 13: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN13; break;
		case 14: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN14; break;
		case 15: config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN15; break;
		config  = ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN0;
		}

	SetChanADC10(config);
	//pour le changement de voie en entrée de l'adc, il faudra prévoir un temps pour que la tension se
	//stabilise entre la comutation et l'échantillonnage. Le top se serait de changer de voie à la fin de la conversion précédente. 
	//Ce qui laisse du temps avant la conversion suivante.    CBE
	OSTimeDlyHMSM(0, 0, 0, 5);
	
	ConvertADC10(); 
    while (!BusyADC10());	// timeaout ?? !!
    buffer = 8 * (~ReadActiveBufferADC10() & 0x1);                      /* Select non active buffer                                 */
    
    return (ReadADC10(buffer));                                         /* Return ADC reading                                       */
}

/*
*********************************************************************************************************
*                                    ADC_TmrInit()
*
* Description: Initialize the timer used by the ADC.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  ADC_TmrInit (void)
{
    OpenTimer3(T3_ON | T3_PS_1_8 | T3_SOURCE_INT, 0);                  /* Timer 3 enabled with 1:8 prescaler                        */
}    

/* 
*********************************************************************************************************
*                                        PB_Init()
*
* Description: This function performs the initialization for the push buttons. On the Explorer 16, the push
*              buttons are all multiplexed except for push button 0. Therefore push button 0 is the only
*              one that is configured to be interrupt driven using the change notice interrupt.
*     
*                                   +----+      +----+      +----+      +----+         
*                                   | [] |      | [] |      | [] |      | [] |      
*              Push Button # :    3 +----+    2 +----+    1 +----+    0 +----+      
*                                       
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  PB_Init (void)
{
    PB_Config();                                                        /* Configure the port pins                                  */
    PB_IntInit();                                                       /* Configure interrupt settings                             */
}    

/*
*********************************************************************************************************
*                                        PB_Config()
*
* Description: This function configures the port pins for the push button.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  PB_Config (void)
{
//    PB0_TRIS = 1;                                                       /* Set the pin corresponding to our push button as input    */
}    
    
/*
*********************************************************************************************************
*                                        PB_IntInit()
*
* Description: This function performs the interrupt initialization for the push button.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  PB_IntInit (void)
{
/*    CPU_INT32U  dummy_read;
    CPU_INT16U  config;
    
    
    config = CHANGE_INT_ON
           | CHANGE_INT_PRI_3; 
    
    CNCON = 0x8000;                                                     // Enable the change notice module                          
        
    EnableCN19; 
                                                      // Enable change notice pin 19, tied to our push button   
    
    ConfigCNPullups(CN19_PULLUP_ENABLE);                                // Enable a weak pull-up corresponding to the CN pin        
    
    dummy_read = PORTD;                                                 // Perform a dummy read to clear any mismatch conditions    
            
    mCNClearIntFlag();                                                  // Clear the int flag just in case it was triggered         
    
    ConfigIntCN(config);                                                // Enable CN interrupts at priority level 3                 */
}    

/*
*********************************************************************************************************
*                                     BSP_CNHandler()
*
* Description: This function handles change notice interrupts.
*
* Arguments  : None
*
* Returns    : None
* 
* Notes      : Each push of the user push button will actually generate 2 interrupts, as there will actually be
*              two changes of state with the IO pin. However, since the second generation occurs as the pin returns
*              to its original state there is no simple way to reliably detect which pin generated this interrupt.
*              In this implementation only the initial change notice interrupt is serviced.
*********************************************************************************************************
*/

void  BSP_CNHandler (void)
{    
    CPU_INT32U  reg_val;
   

    reg_val = PORTD;                                                    /* Read register to clear change notice mismatch condition  */ 
    
//    if ((reg_val & PB0_MASK) == 0) {
                                                                        /* Insert your application code here                        */                                                                  /* Insert your application code here                        */
//    } 
    
    mCNClearIntFlag();
}

/*
*********************************************************************************************************
*                                                BSP_Dly()
* 
* Description: Perform a short delay (~1uS) by performing multiple NOP.
*
* Arguments  : us           The number of uS to delay (approximate).
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_Dly (CPU_INT32U  us)
{
    CPU_INT32U  dly;
    
    
    dly = us * BSP_DLY_CONST;
    
    while (dly--) {
        asm("NOP");
    }    
}    
    
/*
*********************************************************************************************************
*                                             BSP_IntDisAll()
* 
* Description: Disable all interrupts at the interrupt controller.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{
    INTDisableInterrupts();
}

/*
*********************************************************************************************************
*                                      BSP_InitIntCtrl()
*
* Description: This function intializes the external interrupt controller.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void BSP_InitIntCtrl  (void) 
{
    INTCONSET = 0x1000;	
    INTEnableSystemMultiVectoredInt();
}

/*
*********************************************************************************************************
*                                             BSP_InitIO()
* 
* Description: Initialize all the I/O devices.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_InitIO (void)    
{
#ifdef _TARGET_440H
	BSP_IO_Init();
	LCD_Init();
	Tmr_Init();
    LED_Init();                                                         /* Initialize LEDs                                  */
	UART_Init();
#else
	SYSTEMConfig(BSP_CLK_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
	
    BSP_IO_Init();                                                      // Initialize the board's I/Os
    Tmr_Init();                                                         // Initialize the timers
    BSP_InitIntCtrl();                                                  // Initialize the interrupt controller

    LED_Init();                                                         /* Initialize LEDs                                  */
//    PB_Init();                                                          /* Initialize the push buttons                      */
    ADC_Init();
	PMP_Init();
	UART_Init();
	PWM_Init();
#endif
}


#ifdef _TARGET_440H
/*
*********************************************************************************************************
*                                             LCD_Init()
* 
* Description: Initialize the LCD device
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/


void		LCD_Init(void)
{
	LightLCD();
	InitLCDPins();
	InitByInstru();
}
#endif

