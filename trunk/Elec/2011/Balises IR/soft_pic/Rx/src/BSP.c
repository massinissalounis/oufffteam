#include "p24Hxxxx.h"
#include "define.h"
#include "BSP.h"
#include "uart.h"
#include "i2c.h"
#include "timer.h"

float Fcy; // sys clk frequency

void configure_pic()
{
	unsigned int U1BRG,I2CBRG;
	//-----------------------------------------------------------------
	// Oscillator and PLL (code example from datasheet) ->79MHz(ou 80?)
	//-----------------------------------------------------------------
	// Configure PLL prescaler, PLL postscaler, PLL divisor
	PLLFBD = 41;				// M=43
	CLKDIVbits.PLLPOST = 0;		// N2=2
	CLKDIVbits.PLLPRE =0;		// N1=2
	// Initiate Clock switching to Internal FRC with PLL (NOSC = 0b001)
	__builtin_write_OSCCONH(0x01);
	__builtin_write_OSCCONL(0x01);

	// Wait for Clock switch to occur
	while (OSCCONbits.COSC != 0b001);
	// Wait for PLL to lock
	while(OSCCONbits.LOCK != 1) {};
	Fcy=7.37*43/(2*2*2); //Fcy=Fosc/2=Fin*M/(N1*N2*2) -- fréquence système en MHz!!

	//-----------------------------------------------------------------
	// GPIO configuration
	//-----------------------------------------------------------------	
	TRISA = 0b1111110001100000;
	TRISB = 0b1100011100001011;
	TRISC = 0b0000000000001000;

	//-----------------------------------------------------------------
	// UARTS configuration
	//-----------------------------------------------------------------		
	
	// UART1 -> IR protocol
	U1BRG=520;			//(Fcy/(16*BAUD_RATE)-1)
	// UART1 protocol
	OpenUART1(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW & UART_UEN_10 & UART_EN_WAKE & UART_DIS_LOOPBACK & UART_DIS_ABAUD & UART_NO_PAR_8BIT & UART_BRGH_SIXTEEN & UART_1STOPBIT, UART_INT_TX & UART_IrDA_POL_INV_ZERO & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_INT_RX_CHAR & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR , U1BRG); // Should be wrong

	// UART1 interrupt config
	ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR6 & UART_TX_INT_DIS & UART_TX_INT_PR5); // check interrupt priority

	// UART2 -> Xbee protocol
	U1BRG=260;			//(Fcy/(16*BAUD_RATE)-1)
	// UART2 protocol
	OpenUART2(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW & UART_UEN_10 & UART_EN_WAKE & UART_DIS_LOOPBACK & UART_DIS_ABAUD & UART_NO_PAR_8BIT & UART_BRGH_SIXTEEN & UART_1STOPBIT, UART_INT_TX & UART_IrDA_POL_INV_ZERO & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_INT_RX_CHAR & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR , U1BRG); // Should be wrong

	// UART2 interrupt config
	ConfigIntUART2(UART_RX_INT_DIS & UART_RX_INT_PR6 & UART_TX_INT_DIS & UART_TX_INT_PR5); // check interrupt priority


	//-----------------------------------------------------------------
	// I2C configuration
	//-----------------------------------------------------------------	
	I2CBRG=0; //unused

	// I2C init
	OpenI2C1(I2C1_ON & I2C1_IDLE_STOP & I2C1_CLK_REL & I2C1_IPMI_EN & I2C1_7BIT_ADD & I2C1_SLW_DIS & I2C1_SM_DIS & I2C1_GCALL_DIS & I2C1_STR_DIS & I2C1_ACK & I2C1_ACK_EN & I2C1_RCV_EN & I2C1_STOP_EN & I2C1_RESTART_DIS & I2C1_START_EN , I2CBRG); // Should be wrong

	// I2C interrupt
	ConfigIntI2C1(MI2C1_INT_OFF & SI2C1_INT_ON & MI2C1_INT_PRI_0 & SI2C1_INT_PRI_7); // slave interrupts at highest priority


	//-----------------------------------------------------------------
	// TIMER CONFIGURATION
	//-----------------------------------------------------------------
	OpenTimer1(T1_ON & T1_IDLE_STOP & T1_GATE_OFF & T1_PS_1_64 & T1_SYNC_EXT_OFF & T1_SOURCE_INT,625); // for 10ms sample time
	// Timer period:
	// fcy=fosc/2=39.61MHz
	// Tcy = 25ns
	// Ttimer = Tcy * T1_PS_1_64 = 25ns * 64 = 1.6 us
	// Tperiod = N * Ttimer => N = Tperiod / Ttimer = 10 000us / 1.6us = 6250
	WriteTimer1(0);
	ConfigIntTimer1(T1_INT_PRIOR_3 & T1_INT_ON); // Sampling is now active -> last configuration fonction!!


	//-----------------------------------------------------------------
	// INTERRUPT PRIORITY TABLE
	//-----------------------------------------------------------------	
	// I2C		7	Master orders
	// UART		5	TX/RX communications
	// TIMER	3	Sample clock (angular hearing speed)


}





//-----------------------------------------------------------------
// Board peripheral functions
//-----------------------------------------------------------------		


void CPLD_MUX_ADDRESS(char ADRESS)
{
	if( (ADRESS & 1)   != 0){CPLD_A0 = 1;}else{CPLD_A0 = 0;}
	if( (ADRESS & 2)   != 0){CPLD_A1 = 1;}else{CPLD_A1 = 0;}
	if( (ADRESS & 4)   != 0){CPLD_A2 = 1;}else{CPLD_A2 = 0;}
	if( (ADRESS & 8)   != 0){CPLD_A3 = 1;}else{CPLD_A3 = 0;}
	if( (ADRESS & 16)  != 0){CPLD_A4 = 1;}else{CPLD_A4 = 0;}
	if( (ADRESS & 32)  != 0){CPLD_A5 = 1;}else{CPLD_A5 = 0;}
	if( (ADRESS & 64)  != 0){CPLD_A6 = 1;}else{CPLD_A6 = 0;}
	if( (ADRESS & 128) != 0){CPLD_A7 = 1;}else{CPLD_A7 = 0;}
	if( (ADRESS & 256) != 0){CPLD_A8 = 1;}else{CPLD_A8 = 0;}
}


void Xbee_ON_OFF_CONTROL (char STATE)
{
	if (STATE == ON || STATE == OFF)
	{
		Xbee_ON_SLEEP = STATE;
	}
}

void LED_DRIVER (char STATE)
{
	if (STATE == ON || STATE == OFF)
	{
		VISION_ENABLE = STATE;
	}
}
