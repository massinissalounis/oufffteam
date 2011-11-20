#include <outcompare.h>

#ifdef _OC1IF

/**************************************************************************
* Function Name  :  CloseOC1                                              *
* Description    :  This routine disables the Output Compare and its      *
*                   interrupt bits.                                       *
* Parameter      :  None                                                  *
* Return Value   :  None                                                  *
**************************************************************************/

void CloseOC1()
{   
    _OC1IE = 0;  /* Disable the Interrupt bit in IEC Register */

#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC1CON1bits.OCM = 0;  /* Turn off Output Compare1 */
#else
    OC1CONbits.OCM = 0;  /* Turn off Output Compare1 */
#endif

    _OC1IF = 0;  /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
