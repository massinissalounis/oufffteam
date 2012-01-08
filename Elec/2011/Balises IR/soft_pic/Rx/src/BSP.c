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
	// CROSSBAR configuration
	//-----------------------------------------------------------------
	
	// Unlock Registers
	__builtin_write_OSCCONL(OSCCON & ~(1<<6));

	// ********** Configure Input Functions **********
	//UART1 (IR serial) Input config
	RPINR18bits.U1CTSR = 0b11111; //31 -> tied at VSS
	RPINR18bits.U1RXR = 0b10011; //PIN 19
	//UART2 (Xbee serial) Input config
	RPINR19bits.U2CTSR = 15; //PIN15 -> RP15
	RPINR19bits.U2RXR = 10; // PIN8 -> RP10
	// CAN SERIAL
	RPINR26bits.C1RXR = 3; // CAN receive on RP3 pin (PIN24)


	// ********** Configure Output Functions **********
	RPOR0bits.RP0R = 0b00000 ;// RP0 output - PGD
	RPOR0bits.RP1R = 0b00000 ;// RP1 output - PGC
	RPOR1bits.RP2R = 0b10000 ;// RP2 output - CAN TXD
	//RPOR1bits.RP3R = 0b00000 ;// RP3 output

	RPOR2bits.RP4R = 0b00000 ;// RP4 output - Unused
	RPOR2bits.RP5R = 0b00000 ;// RP5 output - PIC-CPLD PORT6 - Output
	RPOR3bits.RP6R = 0b00000 ;// RP6 output - PIC-CPLD PORT5 - Output
	RPOR3bits.RP7R = 0b00000 ;// RP7 output - PIC-CPLD OIRT4 - Output

	//RPOR4bits.RP8R = 0b00000 ;// RP8 output - I2C
	//RPOR4bits.RP9R = 0b00000 ;// RP9 output - I2C
	//RPOR5bits.RP10R = 0b00000 ;// RP10 output - Xbee UART DIN
	RPOR5bits.RP11R = 0b00101 ;// RP11 output - Xbee UART2 DOUT

	RPOR6bits.RP12R = 0b00000 ;// RP12 output - Xbee Reset - Output
	RPOR6bits.RP13R = 0b00000 ;// RP13 output - Xbee DTR - Output
	RPOR7bits.RP14R = 0b00110 ;// RP14 output - Xbee CTS
	//RPOR7bits.RP15R = 0b00000 ;// RP15 output - Xbee RTS

	RPOR8bits.RP16R = 0b00000 ;// RP16 output - Unused
	RPOR8bits.RP17R = 0b00000 ;// RP17 output - Unused
	RPOR9bits.RP18R = 0b00000 ;// RP18 output - Unused
	//RPOR9bits.RP19R = 0b00000 ;// RP19 output - PIC-CPLD PORT9 - RS232 input

	RPOR10bits.RP20R = 0b00000 ;// RP20 output - PIC-CPLD PORT8 - Output
	RPOR10bits.RP21R = 0b00000 ;// RP21 output - PIC-CPLD PORT7 - Output
	RPOR11bits.RP22R = 0b00000 ;// RP22 output - PIC-CPLD PORT3 - Output
	RPOR11bits.RP23R = 0b00000 ;// RP23 output - PIC-CPLD PORT2 - Output
	RPOR12bits.RP24R = 0b00000 ;// RP24 output - PIC-CPLD PORT1 - Output
	RPOR12bits.RP25R = 0b00000 ;// RP25 output - PIC-CPLD PORT0 - Output
	// Lock Registers
	__builtin_write_OSCCONL(OSCCON | (1<<6));


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
