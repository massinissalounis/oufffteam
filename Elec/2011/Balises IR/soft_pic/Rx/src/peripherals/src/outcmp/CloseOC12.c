#include <outcompare.h>

#ifdef _OC12IF

/********************************************************************
* Function Name :  CloseOC12                                        *
* Description   :  This routine disables the Output Compare and its *
*                  interrupt bits.                                  *
* Parameter     :  None                                             *
* Return Value  :  None                                             *
********************************************************************/

void CloseOC12()
{   
    _OC12IE = 0; /* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC12CON1bits.OCM = 0;  /* Turn off Output Compare8 */
#else
    OC12CONbits.OCM = 0;  /* Turn off Output Compare8*/
#endif
    _OC12IF = 0; /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
