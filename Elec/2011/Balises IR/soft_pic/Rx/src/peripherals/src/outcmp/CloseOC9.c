#include <outcompare.h>

#ifdef _OC9IF

/********************************************************************
* Function Name :  CloseOC9                                         *
* Description   :  This routine disables the Output Compare and its *
*                  interrupt bits.                                  *
* Parameter     :  None                                             *
* Return Value  :  None                                             *
********************************************************************/

void CloseOC9()
{   
    _OC9IE = 0; /* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC9CON1bits.OCM = 0;  /* Turn off Output Compare9 */
#else
    OC9CONbits.OCM = 0;  /* Turn off Output Compare9  */
#endif
    _OC9IF = 0; /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
