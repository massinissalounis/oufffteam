/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                              (c) Copyright 2006, Micrium, Inc., Weston, FL
*                                           All Rights Reserved
*
*                                          Board Support Package
*                                               Microchip
*                                              Explorer 16
*********************************************************************************************************
*/

#include "includes.h"
#include "osc.h"
#include "system.h"
#include "timer.h"
#include "uart.h"
#include "adc10.h"

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define  BSP_TMR_RELOAD          (BSP_CLK_FREQ / (2 * OS_TICKS_PER_SEC))
#define  BSP_DLY_CONST            BSP_CLK_FREQ / 1000000 

#if (BSP_UART == BSP_UART1)

#define  BSP_UART_PUTCHAR(x)      putcUART1(x)
#define  BSP_UART_DATARDY()       DataRdyUART1()
#define  BSP_UART_GETCHAR()       ReadUART1()
#define  BSP_UART_INTCONFIG(x)    ConfigIntUART1(x)
#define  BSP_UART_START(x, y, z)  OpenUART1(x, y, z)
#define  BSP_UART_INTENABLE(x)    EnIntUART1(x)
#define  BSP_UART_INTDISABLE(x)   DisIntUART1(x)
#define  BSP_UART_INTEN           IEC0
#define  BSP_UART_INTSTAT         IFS0
#define  BSP_UART_INTCLR          IFS0CLR
#define  BSP_UART_INTMASK         0x1C000000
#define  BSP_UART_INTTX           0x10000000
#define  BSP_UART_INTRX           0x08000000
#define  BSP_UART_INTERR          0x04000000

#elif (BSP_UART == BSP_UART2)

#define  BSP_UART_PUTCHAR(x)      putcUART2(x)
#define  BSP_UART_DATARDY()       DataRdyUART2()
#define  BSP_UART_GETCHAR()       ReadUART2()
#define  BSP_UART_INTCONFIG(x)    ConfigIntUART2(x)
#define  BSP_UART_START(x, y, z)  OpenUART2(x, y, z)
#define  BSP_UART_INTENABLE(x)    EnIntUART2(x)
#define  BSP_UART_INTDISABLE(x)   DisIntUART2(x)
#define  BSP_UART_INTEN           IEC1
#define  BSP_UART_INTSTAT         IFS1
#define  BSP_UART_INTCLR          IFS1CLR
#define  BSP_UART_INTMASK         0x00000700
#define  BSP_UART_INTTX           0x00000400
#define  BSP_UART_INTRX           0x00000200
#define  BSP_UART_INTERR          0x00000100

#endif

#define  LCD_DATA_TRIS            (*((volatile CPU_INT08U*)&TRISE))
#define  LCD_DATA_IO              (*((volatile CPU_INT08U*)&LATE))
#define  LCD_RD_WR_TRIS           TRISDbits.TRISD5
#define  LCD_RD_WR_IO             LATDbits.LATD5
#define  LCD_RS_TRIS              TRISBbits.TRISB15
#define  LCD_RS_IO                LATBbits.LATB15
#define  LCD_E_TRIS               TRISDbits.TRISD4
#define  LCD_E_IO                 LATDbits.LATD4

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

static  void  LED_Init      (void);

static  void  Tmr_Init      (void);

static  void  UART_Config   (CPU_INT32U baud_rate);
static  void  UART_IntEn    (void);

static  void  LCD_Init      (void);
static  void  LCD_Write     (CPU_INT08U w_type, CPU_CHAR val);

static  void  PB_IntInit    (void);
static  void  PB_Config     (void);
static  void  PB_Init       (void);

static  void  ADC_Init      (void);
static  void  ADC_TmrInit   (void);
static  void  ADC_IntInit   (void);
static  void  ADC_Config    (void) ;

/*
*********************************************************************************************************
*                                                 LED ON
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to control
*                      0    indicates that you want ALL the LEDs to be ON
*                      1    turns ON LED D0 on the board
*                      .
*                      .
*                      8    turns on LED D9 on the board
*********************************************************************************************************
*/

void  LED_On (CPU_INT08U led)
{
    switch (led) {
        case 0:
             mPORTASetBits((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3 |
                            IOPORT_BIT_4 | IOPORT_BIT_5 | IOPORT_BIT_6 | IOPORT_BIT_7));
             break;
        case 1:
             mPORTASetBits(IOPORT_BIT_0);
             break;
        case 2:
             mPORTASetBits(IOPORT_BIT_1);
             break;
        case 3:
             mPORTASetBits(IOPORT_BIT_2);
             break;
        case 4:
             mPORTASetBits(IOPORT_BIT_3);
             break;
        case 5:
             mPORTASetBits(IOPORT_BIT_4);
             break;
        case 6:
             mPORTASetBits(IOPORT_BIT_5);
             break;
        case 7:
             mPORTASetBits(IOPORT_BIT_6);
             break;
        case 8:
             mPORTASetBits(IOPORT_BIT_7);
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
*                      1    turns OFF LED D0 on the board
*                      .
*                      .
*                      8    turns OFF LED D8 on the board
*********************************************************************************************************
*/

void  LED_Off (CPU_INT08U led)
{
    switch (led) {
        case 0:
             mPORTAClearBits((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3 |
                              IOPORT_BIT_4 | IOPORT_BIT_5 | IOPORT_BIT_6 | IOPORT_BIT_7));
             break;
        case 1:
             mPORTAClearBits(IOPORT_BIT_0);
             break;
        case 2:
             mPORTAClearBits(IOPORT_BIT_1);
             break;
        case 3:
             mPORTAClearBits(IOPORT_BIT_2);
             break;
        case 4:
             mPORTAClearBits(IOPORT_BIT_3);
             break;
        case 5:
             mPORTAClearBits(IOPORT_BIT_4);
             break;
        case 6:
             mPORTAClearBits(IOPORT_BIT_5);
             break;
        case 7:
             mPORTAClearBits(IOPORT_BIT_6);
             break;
        case 8:
             mPORTAClearBits(IOPORT_BIT_7);
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
*                      1    toggle LED D0 on the board
*                      .
*                      .
*                      8    toggle LED D8 on the board
*********************************************************************************************************
*/

void  LED_Toggle (CPU_INT08U led)
{
    switch (led) {
        case 0:
             mPORTAToggleBits((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3 |
                               IOPORT_BIT_4 | IOPORT_BIT_5 | IOPORT_BIT_6 | IOPORT_BIT_7));
             break;
        case 1:
             mPORTAToggleBits(IOPORT_BIT_0);
             break;
        case 2:
             mPORTAToggleBits(IOPORT_BIT_1);
             break;
        case 3:
             mPORTAToggleBits(IOPORT_BIT_2);
             break;
        case 4:
             mPORTAToggleBits(IOPORT_BIT_3);
             break;
        case 5:
             mPORTAToggleBits(IOPORT_BIT_4);
             break;
        case 6:
             mPORTAToggleBits(IOPORT_BIT_5);
             break;
        case 7:
             mPORTAToggleBits(IOPORT_BIT_6);
             break;
        case 8:
             mPORTAToggleBits(IOPORT_BIT_7);
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

static  void  BSP_IO_Init (void)
{                                                                             /* Each LED pin is set up as an output        */
    mPORTAOutputConfig((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3 | 
                        IOPORT_BIT_4 | IOPORT_BIT_5 | IOPORT_BIT_6 | IOPORT_BIT_7));
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
    OpenCoreTimer(BSP_TMR_RELOAD);                                            /* Initialize the Count and Compare registers */                                               
    mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_3));                        /* Enable the core timer's interrupt          */	    
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
    mCTClearIntFlag();                                                        /* Clear the core timer interrupt             */
    UpdateCoreTimer(BSP_TMR_RELOAD);                                          /* Prepare for the next core timer interrupt  */
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
*                                    OSProbe_TmrInit()
*
* Description: Initialize the timer used by uC/Probe.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  OSProbe_TmrInit (void)
{
    OpenTimer1(T1_ON | T1_PS_1_1 | T1_SOURCE_INT, 0);
}

/*
*********************************************************************************************************
*                                    OSProbe_TmrRd()
*
* Description: Read the value of the 32-bit timer used by uC/Probe
*
* Arguments  : None
*
* Returns    : The current 32-bit value of the timer
*********************************************************************************************************
*/

INT32U  OSProbe_TmrRd (void)
{
    return  (ReadTimer1());
}

/*
*********************************************************************************************************
*                                    BSP_UARTHandler()
*
* Description: This function handles interrupts from the UART.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_UARTHandler (void)
{
    CPU_INT32U  status;
    CPU_INT32U  int_en;
    
    
    status           = BSP_UART_INTSTAT;                                /* Read the interrupt status register               */
    int_en           = BSP_UART_INTEN;                                  /* Read the interrupt enabled register              */
    
    status          &= BSP_UART_INTMASK;                                /* Mask all other interrupts                        */
    BSP_UART_INTCLR  = status;                                          /* Clear all triggered interrupts                   */
    status          &= int_en;                                          /* Mask non-enabled interrupts                      */
    
    if (status & BSP_UART_INTRX) {                                      /* If a Rx interrupt has occured and is enabled...  */
        UART_TxByte(UART_RxByte());                                     /* Notify Probe and provide the incoming character  */
    }
}

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
    UART_Config(BSP_BAUD_RATE);
    UART_IntEn();   
}

/*
*********************************************************************************************************
*                                    UART_CalcBRG()
*
* Description: This function calculates the correct multiplier for the selected baud rate.
*
* Arguments  : baud_rate    The desired baud rate for the UART
*
* Returns    : The calcualted multiplier for the selected baud rate.
*********************************************************************************************************
*/

CPU_INT32U  UART_CalcBRG (CPU_INT32U baud_rate)
{
    CPU_INT32U  brg;
    
    
    brg = BSP_CLK_FREQ / (16 * baud_rate) - 1;
    
    return (brg);
}

/*
*********************************************************************************************************
*                                      UART_Config()
*
* Description: This function performs all necessary configurations on the UART.
*
* Arguments  : baud_rate    The desired baud rate for the UART
*
* Returns    : None
*********************************************************************************************************
*/

static  void  UART_Config (CPU_INT32U baud_rate)
{    
    CPU_INT32U  ubrg;
    CPU_INT32U  config1;
    CPU_INT32U  config2;
    
  
    mPORTAClearBits(DEF_BIT_07);                                        /* Turn off RA7 on startup.                         */
    mPORTASetPinsDigitalOut(DEF_BIT_07);                                /* Make RA7 as output.                              */
    
    ubrg    = UART_CalcBRG(baud_rate);                                  /* Calculate the correct multiplier                 */
    
    config1 = UART_EN                                                   /* UART module enabled                              */
            | UART_IDLE_CON                                             /* UART works in IDLE mode                          */
            | UART_RX_TX                                                /* Communication is done through the normal pins    */
            | UART_DIS_WAKE                                             /* Disable Wake-up on START bit detect during SLEEP */
            | UART_DIS_LOOPBACK                                         /* Disable loop back                                */
            | UART_DIS_ABAUD                                            /* Input to capture module from ICx pin             */
            | UART_NO_PAR_8BIT                                          /* 8 bits no parity                                 */
            | UART_1STOPBIT                                             /* 1 stop bit                                       */
            | UART_IRDA_DIS                                             /* IrDA disabled                                    */
            | UART_MODE_FLOWCTRL                                        /* UART pins in flow control mode                   */
            | UART_DIS_BCLK_CTS_RTS                                     /* Disable BCLK, CTS, and RTS pins                  */
            | UART_NORMAL_RX                                            /* UxRX idle stat is '1'                            */
            | UART_BRGH_SIXTEEN;                                        /* 16x baud clock                                   */
            
    config2 = UART_TX_PIN_LOW                                           /* IrDA encoded UxTx idle stat is '0'               */
            | UART_RX_ENABLE                                            /* Enable UxRx pin                                  */
            | UART_TX_ENABLE                                            /* Enable UxTx pin                                  */
            | UART_INT_TX                                               /* Interrupt on trasnfer of each character to TSR   */
            | UART_INT_RX_CHAR                                          /* Interrupt on every char received                 */
            | UART_ADR_DETECT_DIS                                       /* Disable 9-bit address detect                     */
            | UART_RX_OVERRUN_CLEAR;                                    /* Rx buffer overrun status bit clear               */
            
    BSP_UART_START(config1, config2, ubrg);                             /* Configure the settings                           */
}

/*
*********************************************************************************************************
*                                      UART_IntEn()
*
* Description: This function configures and enables interrupts for the UART.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

static  void  UART_IntEn (void)
{
    CPU_INT08U  config;
    
    
    config = UART_INT_PR3
           | UART_INT_SUB_PR0
           | UART_RX_INT;
           
    BSP_UART_INTCONFIG(config);
}

/*
*********************************************************************************************************
*                                      UART_RxByte()
*
* Description: This function receives a single character.
*
* Arguments  : None
*
* Returns    : The character that is read.
* 
* Note(s)    : This function calls OSTimeDly, it should not be used in ISRs.
*********************************************************************************************************
*/

CPU_CHAR  UART_RxByte (void)
{
    while (BSP_UART_DATARDY() == DEF_FALSE) {
        OSTimeDly(1);                                                   /* If there is no data to be read, delay            */
    }
        
    return (BSP_UART_GETCHAR());                                        /* Return a character                               */
}
 
/*
*********************************************************************************************************
*                                      UART_RxStr()
*
* Description: This function receives a string of num characters and stores it at a memory location
*              designated by the pointer str.
*
* Arguments  : str          A pointer to the location where the string will be stored.
*              num          The number of characters to receive.
*
* Returns    : The character that is read.
* 
* Note(s)    : This function calls OSTimeDly, it should not be used in ISRs.
*********************************************************************************************************
*/
 
void  UART_RxStr (CPU_CHAR *str, CPU_INT16U num)
{
    CPU_CHAR    b;
    CPU_INT16U  i;
    
    
    i      =  0;
    str[i] = ' ';
    
    while(num) {                                                        /* Check error flags                                */
        b = UART_RxByte();
        num--;            
        if (b == 13) {                                                  /* Null character                                   */
            str[i] = '\0';    
            break;
        } else if (b == 8) {                                            /* Backspace                                        */
            if(i) {
                i--;
                str[i] = ' ';
            }                                         
        } else {                                                        /* For any other character, read and store          */
            str[i] = b;
            i++;
        }
        
        OSTimeDly(1);
    }
    
    if (str[i] != '\0') {
        str[i]  = '\0';                                                 /* Ensure all strings are null terminated           */
    }
}            

/*
*********************************************************************************************************
*                                      UART_TxByte()
*
* Description: This function performs all necessary initializations on the UART.
*
* Arguments  : baud_rate    The desired baud rate for the UART
*
* Returns    : None
*********************************************************************************************************
*/
  
void  UART_TxByte (CPU_CHAR c)
{
    if (c == 8) {                                                       /* If a backspace character is to be printed        */
        BSP_UART_PUTCHAR(c);                                            /* Print backspace...                               */
        BSP_UART_PUTCHAR(' ');                                          /* Print space character to clear character         */
        BSP_UART_PUTCHAR(c);                                            /* Print backspace to reposition cursor             */
    } else {    
        BSP_UART_PUTCHAR(c);                                            /* Output the character                             */
    }
}    

/*
*********************************************************************************************************
*                                      UART_TxStr()
*
* Description: This function transmits a string using the UART.
*
* Arguments  : str          A pointer the the location of the string to be output.
*
* Returns    : None
*********************************************************************************************************
*/
 
void  UART_TxStr (CPU_CHAR  *str)
{
    while (*str) {
        UART_TxByte(*str++);              
    }
} 

/*
*********************************************************************************************************
*                                       LCD_Disp()
*
* Description: This function outputs a string to the debug LCD.
*
* Arguments  : pos          The position on the debug LCD to output to.
*                            LCD_LINE_1 - outputs to the first line of the debug LCD
*                            LCD_LINE_2 - outputs to the second line of the debug LCD
*              str          A pointer the the location of the string to be output.
*
* Returns    : None
*********************************************************************************************************
*/

void  LCD_Disp (CPU_INT08U pos, CPU_CHAR *str)
{
    LCD_Write(0, pos);                                                  /* Perform a control write setting the position     */
    BSP_Dly(5);
    
    if (*str) {
        do {
            LCD_Write(1, *str++);                                       /* Write the string, 1 character at at time         */
            BSP_Dly(5);
        } while (*str);     
    }    
}  

/*
*********************************************************************************************************
*                                       LCD_Write()
*
* Description: This function performs a control write or outputs a single character to the debug LCD.
*
* Arguments  : w_type       The type of write to perform.
*                            0 - control write
*                            1 - outputs to the debug LCD
*              val          The value to write.
*
* Returns    : None
*********************************************************************************************************
*/

static  void  LCD_Write (CPU_INT08U w_type, CPU_CHAR val)
{
    LCD_DATA_TRIS  =      0;
    LCD_RS_TRIS    =      0;
    LCD_RD_WR_TRIS =      0;
    LCD_RD_WR_IO   =      0;
    LCD_RS_IO      = w_type;
    LCD_DATA_IO    =    val;
    BSP_Dly(1);
    LCD_E_IO       =      1;
    BSP_Dly(1);
    LCD_E_IO       =      0;
    LCD_DATA_TRIS  =   0xFF;
    LCD_RS_TRIS    =      1;
    LCD_RD_WR_TRIS =      1;
}              

/*
*********************************************************************************************************
*                                       LCD_Init()
*
* Description: This function performs the initialization for the LCD.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

static  void  LCD_Init (void)
{
    LCD_E_IO       =    0;
    LCD_RD_WR_IO   =    0;
    LCD_DATA_TRIS  =    0;  
    LCD_RD_WR_TRIS =    0;
    LCD_RS_TRIS    =    0;
    LCD_E_TRIS     =    0;
    BSP_Dly(40000);
    LCD_RS_IO      =    0;
    LCD_DATA_IO    = 0x03;
    BSP_Dly(1);
    LCD_E_IO       =    1;
    BSP_Dly(1);
    LCD_E_IO       =    0;
    BSP_Dly(5);
    LCD_Write(0, 0x38);
    BSP_Dly(5);
    LCD_Write(0, 0x06);
    BSP_Dly(5);
    LCD_Write(0, 0x0C);
    BSP_Dly(5);
    LCD_Write(0, 0x01);
    BSP_Dly(2);
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

static  void  ADC_Init (void)
{
    ADC_Config();                                                       /* Configure ADC settings                           */
    ADC_IntInit();                                                      /* Configure the interrupt settings                 */
    ADC_TmrInit();                                                      /* Initialize the timer used for the ADC            */
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

static  void  ADC_Config (void) 
{
    CPU_INT32U  config;
    CPU_INT32U  config1;
    CPU_INT32U  config2;
    CPU_INT32U  config3;
    CPU_INT32U  config4;
    CPU_INT32U  config5;
    
    
    config  = ADC_CH0_NEG_SAMPLEA_NVREF
            | ADC_CH0_POS_SAMPLEA_AN5;
    
    config1 = ADC_MODULE_ON
            | ADC_IDLE_STOP
            | ADC_FORMAT_INTG
            | ADC_CLK_TMR
            | ADC_AUTO_SAMPLING_ON
            | ADC_SAMP_ON;
            
    config2 = ADC_VREF_AVDD_AVSS
            | ADC_OFFSET_CAL_DISABLE
            | ADC_SCAN_OFF
            | ADC_SAMPLES_PER_INT_16
            | ADC_ALT_BUF_ON
            | ADC_ALT_INPUT_ON;
    
    config3 = ADC_SAMPLE_TIME_0
            | ADC_CONV_CLK_INTERNAL_RC
            | ADC_CONV_CLK_Tcy2;
           
    config4 = SKIP_SCAN_ALL;
     
    config5 = ENABLE_AN5_ANA;
    
    SetChanADC10(config);        
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

static  void  ADC_IntInit (void)
{
    mAD1SetIntPriority(INT_PRIORITY_LEVEL_3);                           /* Set interrupt priority level to 3                        */
    mAD1ClearIntFlag();                                                 /* Clear interrupt flag, just in case                       */
    mAD1IntEnable(1);                                                   /* Enable interrupts                                        */
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
*                                     ADC_GetVal()
*
* Description: This function returns the ADC value.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

CPU_INT16U  ADC_GetVal (void)
{
    CPU_INT08U  buffer;
    
    
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

static  void  ADC_TmrInit (void)
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

static  void  PB_Init (void)
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

static  void  PB_Config (void)
{
    PB0_TRIS = 1;                                                       /* Set the pin corresponding to our push button as input    */
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

static  void  PB_IntInit (void)
{
    CPU_INT32U  dummy_read;
    CPU_INT16U  config;
    
    
    config = CHANGE_INT_ON
           | CHANGE_INT_PRI_3; 
    
    CNCON = 0x8000;                                                     /* Enable the change notice module                          */
        
    EnableCN19();                                                       /* Enable change notice pin 19, tied to our push button     */
    
    ConfigCNPullups(CN19_PULLUP_ENABLE);                                /* Enable a weak pull-up corresponding to the CN pin        */
    
    dummy_read = PORTD;                                                 /* Perform a dummy read to clear any mismatch conditions    */
            
    mCNClearIntFlag();                                                  /* Clear the int flag just in case it was triggered         */
    
    ConfigIntCN(config);                                                /* Enable CN interrupts at priority level 3                 */
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
    
    if ((reg_val & PB0_MASK) == 0) {
                                                                        /* Insert your application code here                        */                                                                  /* Insert your application code here                        */
    } 
    
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

static  void  BSP_InitIntCtrl (void) 
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
                                                                        /* Enable optimal performance                       */
    SYSTEMConfigPerformance(BSP_CLK_FREQ);
    mOSCSetPBDIV(0);                                                    /* Use 1:1 CPU Core:Peripheral clocks               */

#if JTAG_ENABLE	
	DDPCONbits.JTAGEN = 1;                                              /* Maintain the port pins for JTAG use              */
#else
    DDPCONbits.JTAGEN = 0;                                              /* Free the JTAG port pins for use as GPIO          */
#endif

    BSP_InitIntCtrl();                                                  /* Initialize the interrupt controller              */
    BSP_IO_Init();                                                      /* Initialize the board's I/Os                      */
    Tmr_Init();                                                         /* Initialize the timers                            */
    LED_Init();                                                         /* Initialize LEDs                                  */
    LCD_Init();                                                         /* Initialize the LCD                               */
    PB_Init();                                                          /* Initialize the push buttons                      */
    ADC_Init();
}
