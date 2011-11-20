#include <outcompare.h>

#ifdef _OC10IF

/********************************************************************
*    Function Name:  ReadDCOC10PWM                                  *
*    Description:    This routine reads duty cycle from Secondary   *
*                    register  in PWM mode                          *
*    Parameters:     None                                           *
*    Return Value:   unsigned int:duty cycle from Secondary register*
********************************************************************/

unsigned int ReadDCOC10PWM()
{
    /* check if OC is in PWM Mode */

#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    if((OC10CON1bits.OCM & 0x06) == 0x06)
    {       
        return OC10R;   /* Output Compare Secondary Register */
    }

#else

    if((OC10CONbits.OCM & 0x06) == 0x06)
    {       
        return OC10RS;   /* Output Compare Secondary Register */
    }

#endif

    else 
        return -1;
}

#else
#warning "Does not build on this target"
#endif
