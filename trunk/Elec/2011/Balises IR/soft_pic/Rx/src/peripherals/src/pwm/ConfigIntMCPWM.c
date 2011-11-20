#include <pwm.h>

#ifdef _PWMIF

/**********************************************************************
* Function Name     :ConfigIntMCPWM
* Description       :This function Enable/Disable interrupts and 
*                    sets Interrupt priority for period match, 
*                    FaultA and FaultB.  
* Parameters        :unsigned int Config
* Return Value      :None 
**********************************************************************/

void ConfigIntMCPWM(unsigned int config)
{

    /* clear the Interrupt flags */
    _PWMIF = 0;	
    _FLTAIF = 0;	

    /* Set priority for the period match */
    _PWMIP      = (0x0007 & config);

    /* Set priority for the Fault A */
    _FLTAIP    = (0x0070 & config)>> 4;

    /* enable /disable of interrupt Period match */
    _PWMIE      = (0x0008 & config) >> 3;

    /* enable /disable of interrupt Fault A.*/
    _FLTAIE     = (0x0080 & config) >> 7;

#ifdef _FLTBIF
    /* clear the Interrupt flags */
    _FLTBIF = 0;	

    /* Set priority for the Fault B */
    _FLTBIP    = (0x0700 & config)>>8;

    /* enable /disable of interrupt Fault B.*/
    _FLTBIE     = (0x0800 & config) >> 11;
#endif

}

#else
#warning "Does not build on this target"
#endif
