#if defined(__dsPIC33F__) 
#include <p33Fxxxx.h>
#elif defined(__dsPIC24H__)
#include <p24Hxxxx.h>
#elif defined(__dsPIC33E__)
#include <p33Exxxx.h>
#endif

#include "comparator.h"
#ifdef _COMPARATOR_V1
/**************************************************************************
* Function Name  :  ConfigCMP(unsigned int  config1)                      *
* Description    :  This routine configures the Comparator module.        *
* Parameter      :  config1 This contains the parameters to be configured *
*                           in the CMCON Register                         *                  
* Return Value   :  None                                                  *
**************************************************************************/


void ConfigCMP(unsigned int config1)
{
   CMCON = config1 ;
}

#elif defined _COMPARATOR_V2
/**************************************************************************
* Function Name  :  ConfigCMP(unsigned int  config1, unsigned int config2,*
*							  unsigned int config3, unsigned int config4) *
* Description    :  This routine configures the Comparator module.        *
* Parameter      :  config1 This contains the parameters to be configured *
*                           in the CMSTAT Register, config2 for CMMSKSRC  *
*							config3 for CMMSKCON, config4 for CMFLTR      *
*							config5 for CMSTAT							  *		
* Return Value   :  None                                                  *
**************************************************************************/
#ifdef _C1EVT
void ConfigCMP1(unsigned int config1, unsigned int config2, unsigned int config3, unsigned int config4, unsigned int config5)
{
   CM1CON = config1 ;
   CM1MSKSRC = config2;
   CM1MSKCON = config3;
   CM1FLTR = config4;
   CMSTAT = config5;
}
#endif

#ifdef _C2EVT
void ConfigCMP2(unsigned int config1, unsigned int config2, unsigned int config3, unsigned int config4, unsigned int config5)
{
   CM2CON = config1 ;
   CM2MSKSRC = config2;
   CM2MSKCON = config3;
   CM2FLTR = config4;
   CMSTAT = config5;
}
#endif

#ifdef _C3EVT
void ConfigCMP3(unsigned int config1, unsigned int config2, unsigned int config3, unsigned int config4, unsigned int config5)
{
   CM3CON = config1 ;
   CM3MSKSRC = config2;
   CM3MSKCON = config3;
   CM3FLTR = config4;
   CMSTAT = config5;
}
#endif

#else
#warning "Does not build on this target"
#endif
