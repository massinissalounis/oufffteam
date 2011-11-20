#include <outcompare.h>

#ifdef _OC1IF

/**********************************************************************
*    Function Name:  ReadDCOC1PWM                                     *
*    Description:    This routine reads duty cycle from Secondary     *
*                    register  in PWM mode                            *
*    Parameters:     None                                             *
*    Return Value:   unsigned int: duty cycle from Secondary register *
**********************************************************************/

unsigned int ReadDCOC1PWM()
{
    /* check if OC is in PWM Mode */

#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    if((OC1CON1bits.OCM & 0x06) == 0x06)
    {       
        return OC1R;   /* Output Compare primary Register */
    }

#else

    if((OC1CONbits.OCM & 0x06) == 0x06)
    {       
        return OC1RS;   /* Output Compare Secondary Register */
    }

#endif

    else 
        return -1;
}

#else
#warning "Does not build on this target"
#endif

