#include <outcompare.h>

#ifdef _OC11IF

/********************************************************************
* Function Name :  CloseOC11                                        *
* Description   :  This routine disables the Output Compare and its *
*                  interrupt bits.                                  *
* Parameter     :  None                                             *
* Return Value  :  None                                             *
********************************************************************/

void CloseOC11()
{   
    _OC11IE = 0; /* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC11CON1bits.OCM = 0;  /* Turn off Output Compare8 */
#else
    OC11CONbits.OCM = 0;  /* Turn off Output Compare8*/
#endif
    _OC11IF = 0; /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
