#include <outcompare.h>

#ifdef _OC2IF

/***********************************************************************
* Function Name :  CloseOC2                                            *
* Description   :  This routine disables the Output Compare and its    *
*                  interrupt bits.                                     *
* Parameter     :  None                                                *
* Return Value  :  None                                                *
***********************************************************************/

void CloseOC2()
{   
    _OC2IE = 0; /* Disable the Interrupt bit in IEC Register */

#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC2CON1bits.OCM = 0;  /* Turn off Output Compare2 */
#else
    OC2CONbits.OCM = 0;  /* Turn off Output Compare2  */
#endif
    _OC2IF = 0; /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
