#include <outcompare.h>

#ifdef _OC13IF

/********************************************************************
* Function Name :  CloseOC13                                        *
* Description   :  This routine disables the Output Compare and its *
*                  interrupt bits.                                  *
* Parameter     :  None                                             *
* Return Value  :  None                                             *
********************************************************************/

void CloseOC13()
{   
    _OC13IE = 0; /* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC13CON1bits.OCM = 0;  /* Turn off Output Compare8 */
#else
    OC13CONbits.OCM = 0;  /* Turn off Output Compare8*/
#endif
    _OC13IF = 0; /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
