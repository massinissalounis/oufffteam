#include "p24Hxxxx.h"
#include "define.h"
#include "uart.h"
#include "i2c.h"
#include "timer.h"

//---------------------------------------------
// Global Terms definition
//---------------------------------------------
#define ON	1
#define OFF	0

#define BAUD_RATE 9600


//---------------------------------------------
// I/O definition
//---------------------------------------------
#define CPLD_A0	PORTCbits.RC9
#define CPLD_A1	PORTCbits.RC8
#define	CPLD_A2	PORTCbits.RC7
#define CPLD_A3	PORTCbits.RC6
#define	CPLD_A4	PORTBbits.RB7
#define CPLD_A5 PORTBbits.RB6
#define CPLD_A6 PORTBbits.RB5
#define CPLD_A7	PORTCbits.RC5
#define CPLD_A8	PORTCbits.RC4
#define CPLD_UART PORTCbits.RC3

#define LED1 PORTAbits.RA0
#define LED2 PORTAbits.RA1

#define VISION_ENABLE PORTAbits.RA4

#define Xbee_ON_SLEEP PORTAbits.RA10


//---------------------------------------------
// Functions definition
//---------------------------------------------
void configure_pic();
void CPLD_MUX_ADRESS(char ADRESS);
void Xbee_ON_OFF_CONTROL(char STATE);
