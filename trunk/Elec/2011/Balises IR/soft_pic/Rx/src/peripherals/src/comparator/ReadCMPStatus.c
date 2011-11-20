#if defined(__dsPIC33F__) 
#include <p33Fxxxx.h>
#elif defined(__dsPIC24H__)
#include <p24Hxxxx.h>
#elif defined(__dsPIC33E__)
#include <p33Exxxx.h>
#endif

#include "comparator.h"
#if defined (_COMPARATOR_V2)

/**************************************************************************
* Function Name  :  ReadCMPStatus(void)			                  *
* Description    :  This routine returns the value of CMSTAT register.    *
* Parameter      :  None						  *
* Return Value   :  unsigned int                                          *
**************************************************************************/

unsigned int ReadCMPStatus(void)
{
   return CMSTAT;
}

#else
#warning "Does not build on this target"
#endif
