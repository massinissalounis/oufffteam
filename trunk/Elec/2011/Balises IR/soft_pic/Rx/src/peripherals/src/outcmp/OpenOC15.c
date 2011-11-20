#include <outcompare.h>

#ifdef _OC15IF

/*****************************************************************************
*    Function Name:  OpenOC15                                                *
*    Description:    This routine configures output compare module and loads *
*                    the compare registers                                   *
*    Parameters  :   unsigned int config1,unsigned int config1, unsigned int *
*					 value1, unsigned int value2                             *
*                                                                            *
*    Return Value:   None                                                    *
*    Notes           value1 is the compare value for the OCRS register       *
*                    value2 is the compare value for the OCR register        *
*****************************************************************************/

void OpenOC15(unsigned int config1,unsigned int config2, unsigned int value1, unsigned int value2)
{
   
#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    OC15CON1bits.OCM = 0; /* turn off OC before switching to new mode */
    OC15RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC15R = value2;      /* assign value2 to OCxR Main Register*/  
    OC15CON1 = config1;    /* assign config to OCxCON Register*/
    OC15CON2 = config2;

#else
    OC15CONbits.OCM = 0; /* turn off OC before switching to new mode */ 
    OC15RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC15R = value2;      /* assign value2 to OCxR Main Register*/ 
    OC15CON = config1;    /* assign config to OCxCON Register*/

#endif

}
#else
#warning "Does not build on this target"
#endif
