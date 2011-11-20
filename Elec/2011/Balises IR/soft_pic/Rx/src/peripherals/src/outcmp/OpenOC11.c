#include <outcompare.h>

#ifdef _OC11IF

/*****************************************************************************
*    Function Name:  OpenOC11                                                *
*    Description:    This routine configures output compare module and loads *
*                    the compare registers                                   *
*    Parameters  :   unsigned int config1,unsigned int config1, unsigned int *
*					 value1, unsigned int value2                             *
*                                                                            *
*    Return Value:   None                                                    *
*    Notes           value1 is the compare value for the OCRS register       *
*                    value2 is the compare value for the OCR register        *
*****************************************************************************/

void OpenOC11(unsigned int config1,unsigned int config2, unsigned int value1, unsigned int value2)
{
   
#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    OC11CON1bits.OCM = 0; /* turn off OC before switching to new mode */
    OC11RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC11R = value2;      /* assign value2 to OCxR Main Register*/  
    OC11CON1 = config1;    /* assign config to OCxCON Register*/
    OC11CON2 = config2;

#else
    OC11CONbits.OCM = 0; /* turn off OC before switching to new mode */ 
    OC11RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC11R = value2;      /* assign value2 to OCxR Main Register*/ 
    OC11CON = config1;    /* assign config to OCxCON Register*/

#endif

}
#else
#warning "Does not build on this target"
#endif
