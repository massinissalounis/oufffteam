#include <outcompare.h>

#ifdef _OC15IF

/********************************************************************
* Function Name :  CloseOC15                                        *
* Description   :  This routine disables the Output Compare and its *
*                  interrupt bits.                                  *
* Parameter     :  None                                             *
* Return Value  :  None                                             *
********************************************************************/

void CloseOC15()
{   
    _OC15IE = 0; /* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC15CON1bits.OCM = 0;  /* Turn off Output Compare8 */
#else
    OC15CONbits.OCM = 0;  /* Turn off Output Compare8*/
#endif
    _OC15IF = 0; /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
