#include <xlcd.h>
#include <delay.h>

#ifdef _RD10

/*******************************************************************
Function Name:            WriteDataXLCD
Description:              This function writes a data byte into the 
                          DDRam/CGRam of the LCD controller.The user
                          must first check the busy  status of the 
                          LCD controller  by calling the BusyXLCD()
                          function.The data written can go to the 
                          DDRam or CGRam depending on the previous
                          SetXXRamAddr( char) that was  called.
Input parameters:         char data
Return value:             void
********************************************************************/
void WriteDataXLCD( char data)
{
    RW_PIN = 0;  /* enable write */
    RS_PIN = 1;  /* select Data Reg */
                     
    /* configure the common data pins as output */
    TRIS_DATA_PIN_7 = 0;
    TRIS_DATA_PIN_6 = 0;
    TRIS_DATA_PIN_5 = 0;
    TRIS_DATA_PIN_4 = 0;

	# ifdef EIGHT_BIT_INTERFACE
		/* configure the other pins as output */
		TRIS_DATA_PIN_3 = 0;
		TRIS_DATA_PIN_2 = 0;
		TRIS_DATA_PIN_1 = 0;
		TRIS_DATA_PIN_0 = 0;
    	DATA_PIN_7 = (unsigned int)((data & 0x80)>>7);
     	DATA_PIN_6 = (unsigned int)((data & 0x40)>>6);
	    DATA_PIN_5 = (unsigned int)((data & 0x20)>>5);
	    DATA_PIN_4 = (unsigned int)((data & 0x10)>>4);		
		DATA_PIN_3 = (unsigned int)((data & 0x08)>>3);
		DATA_PIN_2 = (unsigned int)((data & 0x04)>>2);
		DATA_PIN_1 = (unsigned int)((data & 0x02)>>1);
		DATA_PIN_0 = (unsigned int)((data & 0x01)>>0);
	#else
		DATA_PIN_7 = (unsigned int)((data & 0x08)>>3);
		DATA_PIN_6 = (unsigned int)((data & 0x04)>>2);
		DATA_PIN_5 = (unsigned int)((data & 0x02)>>1);
		DATA_PIN_4 = (unsigned int)((data & 0x01)>>0);
	#endif
	
    E_PIN = 1;
    DelayEPulseWidthHigh();
    E_PIN = 0;
    DelayEPulseWidthLow();

    RS_PIN = 0; 
    RW_PIN = 0; 
    /*configure all pins to input mode*/
    TRIS_DATA_PIN_7 = 1;
    TRIS_DATA_PIN_6 = 1;
    TRIS_DATA_PIN_5 = 1;
    TRIS_DATA_PIN_4 = 1;
# ifdef EIGHT_BIT_INTERFACE
    TRIS_DATA_PIN_3 = 1;
    TRIS_DATA_PIN_2 = 1;
    TRIS_DATA_PIN_1 = 1;
    TRIS_DATA_PIN_0 = 1;
#endif
 

}  /* end of function */

#else
#warning "Does not build on this target"
#endif
