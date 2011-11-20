#include <outcompare.h>

#ifdef _OC10IF

/*************************************************************************
*    Function Name:  SetPulseOC10                                        *
*    Description:    This routine writes the pulse_start to Main register*
*                    and pulse_stop to Secondary register                *
*    Parameters:     unsigned int pulse_start,unsigned int pulse_stop    *
*    Return Value:   None                                                *
*************************************************************************/

void SetPulseOC10(unsigned int pulse_start, unsigned int pulse_stop)
{   
  #if defined(__dsPIC33E__) || defined(__PIC24E__) 

    /* check if OC is in NON PWM Mode */
    if( (OC10CON1bits.OCM & 0x06) != 0x06) 
    {
        OC10R = pulse_start; /* assign pulse_start to Main Register */
        OC10RS = pulse_stop; /* assign pulse_stop to Secondary Register */
    }

#else

    /* check if OC is in NON PWM Mode */
    if( (OC10CONbits.OCM & 0x06) != 0x06) 
    {
        OC10R = pulse_start; /* assign pulse_start to Main Register */
        OC10RS = pulse_stop; /* assign pulse_stop to Secondary Register */
    }

#endif
}

#else
#warning "Does not build on this target"
#endif
