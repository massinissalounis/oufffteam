#include <incap.h>

#ifdef _IC1IF

/****************************************************************************************
     Function Name:  OpenCapture1                                  			  			*
     Description:    This function configures the Input Capture module.       			*
     Arguments       : config1 - This contains the parameters to be configured in the   *
                     ICxCON1/ICxCON register 							*
		config2 - This contains the parameters to be configured in the		*
                     ICxCON2 register as defined for 33E/24E						*
*    Return Value:   None                                          					    *
*****************************************************************************************/

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
void OpenCapture1 (unsigned int config1, unsigned int config2)
{
    /* Config contains Clock source, number of Captures per interrupt and Capture Mode */
	IC1CON1 = config1;
	IC1CON2 = config2;
}
#else
void OpenCapture1 (unsigned int config)
{
	IC1CON = config; 
}
#endif

#else
#warning "Does not build on this target"
#endif

