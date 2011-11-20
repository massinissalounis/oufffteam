#include <outcompare.h>

#ifdef _OC8IF

/********************************************************************
* Function Name :  CloseOC8                                         *
* Description   :  This routine disables the Output Compare and its *
*                  interrupt bits.                                  *
* Parameter     :  None                                             *
* Return Value  :  None                                             *
********************************************************************/

void CloseOC8()
{   
    _OC8IE = 0; /* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC8CON1bits.OCM = 0;  /* Turn off Output Compare8 */
#else
    OC8CONbits.OCM = 0;  /* Turn off Output Compare8*/
#endif
    _OC8IF = 0; /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
