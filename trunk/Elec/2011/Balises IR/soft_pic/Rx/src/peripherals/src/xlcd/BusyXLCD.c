#include <xlcd.h>
#include <delay.h>

#ifdef _RD10

/*********************************************************************
Function Name:             BusyXLCD
Description:               This function returns the busy status
                           of the LCD Controller.The Busy flag is
                           is MS bit when the Instruction Reg is read
Input parameters:          none
Return value:              char- returns 1 if Busy flag is set, else 0
*********************************************************************/

char BusyXLCD(void)
{
    char status;
    /* Configure all pins as input */
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


    RS_PIN = 0;           /* for selecting AC for read */
    RW_PIN = 1;           /* for read operation */
    /* delay tSU - specified setup time RS/CSU */
    DelayRSSetupTime();
     
    E_PIN = 1;            /* for enabling read/write */
     
    /* delay for data out */
    DelayDBOutput();

    /* read the busy bit */
    if(READ_PIN_7)        /* busy flag */
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    E_PIN = 0;
    
    /* minimum E pulse low */
    DelayEPulseWidthLow();
    RS_PIN = 0; 
    RW_PIN = 0; 
    return status;
} /* end of function */

#else
#warning "Does not build on this target"
#endif
