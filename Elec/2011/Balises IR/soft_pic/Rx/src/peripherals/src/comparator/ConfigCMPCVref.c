#if defined(__dsPIC33F__) 
#include <p33Fxxxx.h>
#elif defined(__dsPIC24H__)
#include <p24Hxxxx.h>
#elif defined(__dsPIC33E__)
#include <p33Exxxx.h>
#endif

#include "comparator.h"
#if defined (_COMPARATOR_V1) || defined (_COMPARATOR_V2)

/**************************************************************************
* Function Name  :  ConfigCMPCVref(unsigned int  config1)                 *
* Description    :  This routine configures Reference Voltage level of the
					Comparator module.									  *
* Parameter      :  config1 This contains the parameters to be configured *
                    in the CVRCON Register                                *
* Return Value   :  None                                                  *
**************************************************************************/

void ConfigCMPCVref(unsigned int config1)
{
   CVRCON = config1 ;
}

#else
#warning "Does not build on this target"
#endif
