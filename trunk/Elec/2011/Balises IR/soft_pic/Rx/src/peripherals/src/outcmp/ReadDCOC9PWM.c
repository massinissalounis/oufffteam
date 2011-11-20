#include <outcompare.h>

#ifdef _OC9IF

/********************************************************************
*    Function Name:  ReadDCOC9PWM                                   *
*    Description:    This routine reads duty cycle from Secondary   *
*                    register  in PWM mode                          *
*    Parameters:     None                                           *
*    Return Value:   unsigned int:duty cycle from Secondary register*
********************************************************************/

unsigned int ReadDCOC9PWM()
{
    /* check if OC is in PWM Mode */

#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    if((OC9CON1bits.OCM & 0x06) == 0x06)
    {       
        return OC9R;   /* Output Compare Secondary Register */
    }

#else

    if((OC9CONbits.OCM & 0x06) == 0x06)
    {       
        return OC9RS;   /* Output Compare Secondary Register */
    }

#endif

    else 
        return -1;
}

#else
#warning "Does not build on this target"
#endif
