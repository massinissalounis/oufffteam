#include <incap.h>

#ifdef _IC4IF

/****************************************************************************************
     Function Name:  OpenCapture4                                  			  			*
     Description:    This function configures the Input Capture module.       			*
     Arguments       : config1 - This contains the parameters to be configured in the   *
                     ICxCON1/ICxCON register 							*
		config2 - This contains the parameters to be configured in the		*
                     ICxCON2 register as defined for 33E/24E						*
    Return Value:   None                                          					    *
*****************************************************************************************/

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
void OpenCapture4 (unsigned int config1, unsigned int config2)
{
    /* Config contains Clock source, number of Captures per interrupt and Capture Mode */
	IC4CON1 = config1;
	IC4CON2 = config2;
}
#else
void OpenCapture4 (unsigned int config)
{
	IC4CON = config; 
}
#endif

#else
#warning "Does not build on this target"
#endif
