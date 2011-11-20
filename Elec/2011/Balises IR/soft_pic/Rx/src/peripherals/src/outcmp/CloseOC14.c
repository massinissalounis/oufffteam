#include <outcompare.h>

#ifdef _OC14IF

/********************************************************************
* Function Name :  CloseOC14                                        *
* Description   :  This routine disables the Output Compare and its *
*                  interrupt bits.                                  *
* Parameter     :  None                                             *
* Return Value  :  None                                             *
********************************************************************/

void CloseOC14()
{   
    _OC14IE = 0; /* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC14CON1bits.OCM = 0;  /* Turn off Output Compare8 */
#else
    OC14CONbits.OCM = 0;  /* Turn off Output Compare8*/
#endif
    _OC14IF = 0; /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
