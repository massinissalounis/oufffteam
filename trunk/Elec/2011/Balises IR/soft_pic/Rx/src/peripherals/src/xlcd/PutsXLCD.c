#include <xlcd.h>
#include <delay.h>

#ifdef _RD10

/*******************************************************************
Function Name:          PutsXLCD
Description:            This function writes a string of characters 
                        into the LCD controller.it stops transmission
                        before the null character.(which is not sent).
Input parameters:       char  *buffer 
Return value:           void
********************************************************************/
void PutsXLCD(char *buffer)
{

    while(*buffer != '\0')
    {
        /* wait for command completion */
        while(BusyXLCD());
        
        WriteDataXLCD(*buffer); /* calling another function */
                                /* to write each char to the lcd module */
        /* check next char */
        buffer++;
    }
    /* wait for command completion */
    while(BusyXLCD());

} /* end of function */

#else
#warning "Does not build on this target"
#endif
