#include <xlcd.h>
#include <delay.h>

#ifdef _RD10

/* definition of typical duration of loop containg clear watchdog */
/* given in TCYs */
#define TCY_CNT_PER_LOOP 4

/******************************************************************************
    This file provides the delay routines required XLCD operation.

The following are the delay routines provided: 
    1. DelayEPulseWidth - Delay for min cycle of the E pulse 
    2. DelayXLCD    - Delay for atleast 5msec general purpose
    3. Delay600nsXLCD - Delay for 600ns
    4. DelayPORXLCD - Delay for atleast 15msec - Power On Reset
    5. DelayRSSetupTime - Delay btw RS/RW pulse to E pulse
    6. DelayDBOutput - Data Output delay from E pulse rise
    7. DelayEPulseWidthLow - min E pulse low width
    8. DelayEPulseWidthLow - min E pulse high width
    9. Delay200usXLCD - 200us delay

The loop counts used in these routines needs to be changed based on the 
exact clock frequency.
******************************************************************************/

void DelayRSSetupTime(void)   	/* provides delay for RS Setup Time */
{
	/* This is E pulse delay from RS/CSU		*/
	/* required by the LCD controlller			*/
	/* for TM162JCAWG1 it is min 60ns worst case */
	
	int i;
	for(i=0;i<DelayRSSetupTime_Cnt;i+=TCY_CNT_PER_LOOP)
		asm("clrwdt");
}
void DelayDBOutput(void) /* provides delay for Data Output */
{
	/* This is DB Output time from E High		*/
	/* required by the LCD controlller read 	*/
	/* for TM162JCAWG1 it is min 360ns worst case */
	
	int i;
	for(i=0;i<DelayDBOutput_Cnt;i+=TCY_CNT_PER_LOOP)
		asm("clrwdt");
}

void DelayEPulseWidthLow(void)   	/* provides delay for E Pulse Width Low */
{
	/* This is the width of the E signal		*/
	/* required by the LCD controlller read & write  */
	/* for TM162JCAWG1 it is min 150ns worst case */
	int i;
	for(i=0;i<DelayEPulseWidthLow_Cnt;i+=TCY_CNT_PER_LOOP)
		asm("clrwdt");
}

void DelayEPulseWidthHigh(void)   	/* provides delay for E Pulse Width High */
{
	/* This is the width of the E signal		*/
	/* required by the LCD controlller write  */
	/* for TM162JCAWG1 it is min 450ns worst case */
	int i;
	for(i=0;i<DelayEPulseWidthHigh_Cnt;i+=TCY_CNT_PER_LOOP)
		asm("clrwdt");
}
void DelayEPulseWidth(void)   	/* provides delay for E Pulse Width Generic */
{
	/* This is the width of the E signal		*/
	/* required by the LCD controlller read & write  */
	/* for TM162JCAWG1 it is min 150ns worst case */
	int i;
	for(i=0;i<DelayEPulseWidth_Cnt;i+=TCY_CNT_PER_LOOP)
		asm("clrwdt");
}

void DelayPORXLCD(void) 	/* provides delay for atleast 15msec */
{
    /* Give a delay of atleast 15 msec after power up	*/
    /* POR Power On Reset */
    
   long i;
    for(i=0;i < DelayPORXLCD_Cnt;i+=TCY_CNT_PER_LOOP)
        asm("clrwdt");
}

void DelayXLCD(void)  		/* provides delay for atleast 5msec */
{
  long i;
    for(i=0;i < DelayXLCD_Cnt;i+=TCY_CNT_PER_LOOP)
        asm("clrwdt");
        }

void Delay600nsXLCD(void)		/* provides delay for 600ns */
{
	/* This delay is required during the read operation	*/
	
    int i;
    for(i=0;i<Delay_600nS_Cnt;i+=TCY_CNT_PER_LOOP)
        asm("clrwdt");
}

//For 33F and 24H devices

void Delay200usXLCD(void)	/* provides delay for 200uS */
{
    int i;
    for(i=0;i<Delay200uS_count;i+=TCY_CNT_PER_LOOP)
        asm("clrwdt");
}



#else
#warning "Does not build on this target"
#endif
