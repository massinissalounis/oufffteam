#include <outcompare.h>

#ifdef _OC3IF

/************************************************************************
* Function Name  : CloseOC3                                             *
* Description    : This routine disables the Output Compare and its     *
*                  interrupt bits.                                      *
* Parameter      : None                                                 *
* Return Value   : None                                                 *
************************************************************************/

void CloseOC3()
{   
    _OC3IE = 0;/* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC3CON1bits.OCM = 0;  /* Turn off Output Compare3 */
#else
    OC3CONbits.OCM = 0;  /* Turn off Output Compare3  */
#endif
    _OC3IF = 0;/* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
