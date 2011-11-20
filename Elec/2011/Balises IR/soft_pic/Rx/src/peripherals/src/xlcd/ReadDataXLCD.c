#include <xlcd.h>
#include <delay.h>

#ifdef _RD10

/*******************************************************************
Function Name   :  ReadDataXLCD
Description     :  This function read the data byte from the 
                   LCD controller. The user must first check 
                   the busy status of the LCD controller by 
                   calling the BusyXLCD() function.The data 
                   read can be from DDRam or CGRam  depending 
                   on the previous SetXXRamAddr( char) that was
                   called.
Input parameters:  none
Return value    :  char data
********************************************************************/

char ReadDataXLCD(void)
{
    char data;
    char temp[8];

    /* init address */
    data = 0;
    /* Configure all pins as input */
    TRIS_DATA_PIN_7 = 1;
    TRIS_DATA_PIN_6 = 1;
    TRIS_DATA_PIN_5 = 1;
    TRIS_DATA_PIN_4 = 1;

#ifdef EIGHT_BIT_INTERFACE
    TRIS_DATA_PIN_3 = 1;
    TRIS_DATA_PIN_2 = 1;
    TRIS_DATA_PIN_1 = 1;
    TRIS_DATA_PIN_0 = 1;
#endif
    
    RW_PIN = 1;                 /* for read operation */
    RS_PIN = 1;                 /* for selecting AC for read */
    /* delay tSU - specified setup time RS/CSU */
    DelayRSSetupTime();
    E_PIN = 1;                  /* for enabling read/write */

    /* delay for data out */
    DelayDBOutput();

    temp[7] = (char) READ_PIN_7;
    temp[6] = (char) READ_PIN_6;
    temp[5] = (char) READ_PIN_5;
    temp[4] = (char) READ_PIN_4;

#ifdef EIGHT_BIT_INTERFACE
    temp[3] = (char) READ_PIN_3;
    temp[2] = (char) READ_PIN_2;
    temp[1] = (char) READ_PIN_1;
    temp[0] = (char) READ_PIN_0;
#else
    temp[3] = (char) READ_PIN_7;
    temp[2] = (char) READ_PIN_6;
    temp[1] = (char) READ_PIN_5;
    temp[0] = (char) READ_PIN_4;
#endif
    E_PIN = 0;                  /* disable read/write */
    /* minimum E pulse low */
    DelayEPulseWidthLow();
    RS_PIN = 0; 
    RW_PIN = 0; 
#ifdef EIGHT_BIT_INTERFACE
    data = (temp[7] << 7);
    data |= (temp[6] << 6);
    data |= (temp[5] << 5);
    data |= (temp[4] << 4);
#endif
    data |= (temp[3] << 3);
    data |= (temp[2] << 2);
    data |= (temp[1] << 1);
    data |= (temp[0]);

    return data;
} /* end of function */

#else
#warning "Does not build on this target"
#endif
