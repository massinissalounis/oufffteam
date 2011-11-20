#include <outcompare.h>

#ifdef _OC16IF

/*****************************************************************************
*    Function Name:  OpenOC16                                                *
*    Description:    This routine configures output compare module and loads *
*                    the compare registers                                   *
*    Parameters  :   unsigned int config1,unsigned int config1, unsigned int *
*					 value1, unsigned int value2                             *
*                                                                            *
*    Return Value:   None                                                    *
*    Notes           value1 is the compare value for the OCRS register       *
*                    value2 is the compare value for the OCR register        *
*****************************************************************************/

void OpenOC16(unsigned int config1,unsigned int config2, unsigned int value1, unsigned int value2)
{
   
#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    OC16CON1bits.OCM = 0; /* turn off OC before switching to new mode */
    OC16RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC16R = value2;      /* assign value2 to OCxR Main Register*/  
    OC16CON1 = config1;    /* assign config to OCxCON Register*/
    OC16CON2 = config2;

#else
    OC16CONbits.OCM = 0; /* turn off OC before switching to new mode */ 
    OC16RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC16R = value2;      /* assign value2 to OCxR Main Register*/ 
    OC16CON = config1;    /* assign config to OCxCON Register*/

#endif

}
#else
#warning "Does not build on this target"
#endif
