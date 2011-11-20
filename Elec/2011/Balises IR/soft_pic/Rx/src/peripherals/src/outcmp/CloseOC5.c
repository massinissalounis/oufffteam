#include <outcompare.h>

#ifdef _OC5IF

/********************************************************************
* Function Name :  CloseOC5                                         *
* Description   :  This routine disables the Output Compare and its *
*                  interrupt bits.                                  *
* Parameter     :  None                                             *
* Return Value  :  None                                             *
********************************************************************/

void CloseOC5()
{   
    _OC5IE = 0;/* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC5CON1bits.OCM = 0;  /* Turn off Output Compare5 */
#else
    OC5CONbits.OCM = 0;  /* Turn off Output Compare5  */
#endif
    _OC5IF = 0;/* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
