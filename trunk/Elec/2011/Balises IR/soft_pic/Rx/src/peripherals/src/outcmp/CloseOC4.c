#include <outcompare.h>

#ifdef _OC4IF

/*********************************************************************
* Function Name  :  CloseOC4                                         *
* Description    :  This routine disables the Output Compare and its *
*                   interrupt bits.                                  *
* Parameters     :  None                                             *
* Return Value   :  None                                             *
*********************************************************************/

void CloseOC4()
{   
    _OC4IE = 0;/* Disable the Interrupt bit in IEC Register */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
	OC4CON1bits.OCM = 0;  /* Turn off Output Compare4 */
#else
    OC4CONbits.OCM = 0;  /* Turn off Output Compare4  */
#endif
    _OC4IF = 0;/* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
