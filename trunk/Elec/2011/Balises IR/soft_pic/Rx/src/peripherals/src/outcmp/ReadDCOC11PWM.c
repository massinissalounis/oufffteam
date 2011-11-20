#include <outcompare.h>

#ifdef _OC11IF

/********************************************************************
*    Function Name:  ReadDCOC11PWM                                  *
*    Description:    This routine reads duty cycle from Secondary   *
*                    register  in PWM mode                          *
*    Parameters:     None                                           *
*    Return Value:   unsigned int:duty cycle from Secondary register*
********************************************************************/

unsigned int ReadDCOC11PWM()
{
    /* check if OC is in PWM Mode */

#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    if((OC11CON1bits.OCM & 0x06) == 0x06)
    {       
        return OC11R;   /* Output Compare Secondary Register */
    }

#else

    if((OC11CONbits.OCM & 0x06) == 0x06)
    {       
        return OC11RS;   /* Output Compare Secondary Register */
    }

#endif

    else 
        return -1;
}

#else
#warning "Does not build on this target"
#endif
