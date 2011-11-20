#include <outcompare.h>

#ifdef _OC10IF

/********************************************************************
* Function Name :  CloseOC10                                        *
* Description   :  This routine disables the Output Compare and its *
*                  interrupt bits.                                  *
* Parameter     :  None                                             *
* Return Value  :  None                                             *
********************************************************************/

void CloseOC10()
{   
    _OC10IE = 0; /* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC10CON1bits.OCM = 0;  /* Turn off Output Compare8 */
#else
    OC10CONbits.OCM = 0;  /* Turn off Output Compare8*/
#endif
    _OC10IF = 0; /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
