#include <outcompare.h>

#ifdef _OC16IF

/********************************************************************
* Function Name :  CloseOC16                                        *
* Description   :  This routine disables the Output Compare and its *
*                  interrupt bits.                                  *
* Parameter     :  None                                             *
* Return Value  :  None                                             *
********************************************************************/

void CloseOC16()
{   
    _OC16IE = 0; /* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC16CON1bits.OCM = 0;  /* Turn off Output Compare8 */
#else
    OC16CONbits.OCM = 0;  /* Turn off Output Compare8*/
#endif
    _OC16IF = 0; /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
