#include "p24Hxxxx.h"
#include "define.h"
#include "BSP.h"
#include "uart.h"

//Select Internal FRC at POR
_FOSCSEL(FNOSC_FRC);
//Enable Clocl Switching and configure
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF);

unsigned char current_state = TSOP33_1;
unsigned char current_TRANSMITTER;
unsigned char COMPUTE_FLAG = OFF;
unsigned char receive_flag[32] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char polar_response[32] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char TSOP33_REG[16];
unsigned char TSOP40_REG[16];


//-----------------------------------------------------------------
// Computing subfunctions
//-----------------------------------------------------------------
void state_machine()
{
	if (current_state >= TSOP40_16)
	{
		current_state = TSOP33_1;
	}
	else
	{
		current_state++;
	}
	CPLD_MUX_ADDRESS(current_state);
}

void measure_dispatch()
{
	TSOP33_REG[0]=polar_response[0];
	TSOP33_REG[1]=polar_response[2];
	TSOP33_REG[2]=polar_response[4];
	TSOP33_REG[3]=polar_response[6];
	TSOP33_REG[4]=polar_response[8];
	TSOP33_REG[5]=polar_response[10];
	TSOP33_REG[6]=polar_response[12];
	TSOP33_REG[7]=polar_response[14];
	TSOP33_REG[8]=polar_response[16];
	TSOP33_REG[9]=polar_response[18];
	TSOP33_REG[10]=polar_response[20];
	TSOP33_REG[11]=polar_response[22];
	TSOP33_REG[12]=polar_response[24];
	TSOP33_REG[13]=polar_response[26];
	TSOP33_REG[14]=polar_response[28];
	TSOP33_REG[15]=polar_response[30];

	TSOP40_REG[0]=polar_response[1];
	TSOP40_REG[1]=polar_response[3];
	TSOP40_REG[2]=polar_response[5];
	TSOP40_REG[3]=polar_response[7];
	TSOP40_REG[4]=polar_response[9];
	TSOP40_REG[5]=polar_response[11];
	TSOP40_REG[6]=polar_response[13];
	TSOP40_REG[7]=polar_response[15];
	TSOP40_REG[8]=polar_response[17];
	TSOP40_REG[9]=polar_response[19];
	TSOP40_REG[10]=polar_response[21];
	TSOP40_REG[11]=polar_response[23];
	TSOP40_REG[12]=polar_response[25];
	TSOP40_REG[13]=polar_response[27];
	TSOP40_REG[14]=polar_response[29];
	TSOP40_REG[15]=polar_response[31];
}

//-----------------------------------------------------------------
// Interrupts
//-----------------------------------------------------------------
// UART1 -> IR signal
void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
	unsigned char buffer;
	IFS0bits.U1RXIF = 0;
	while( DataRdyUART1() )
	{
		buffer=ReadUART1();
	}
	if (buffer == current_TRANSMITTER) //check if the received signal is the current slave's adress
	{
		receive_flag[current_state]=buffer;
	}
}

// Timer interrupt => sample time
void __attribute__((__interrupt__)) _T1Interrupt(void)
{
	unsigned char i;
	WriteTimer1(0);		//reset timer's value
	IFS0bits.T1IF = 0; 	//clear the interrupt flag
	if (current_state == TSOP40_16) // end of read turn
	{
		for (i=0 ; i<16 ; i++)
		{
			polar_response[i]=receive_flag[i];
			receive_flag[i]=0;
		}
		COMPUTE_FLAG = ON;
	}
	state_machine();
}

//-----------------------------------------------------------------
// Main: 1 slave tracking only
//-----------------------------------------------------------------	
int main(void)
{
	configure_pic();
	LED1 = ON; //

	//track TRANSMITTER 1
	current_TRANSMITTER=B1_ADDRESS;
	

	while (1)
	{
		if (COMPUTE_FLAG == ON) // sampling phase done -> compute slave position
		{
			measure_dispatch();

			COMPUTE_FLAG = OFF;
		}
	}
	return(0);
}

