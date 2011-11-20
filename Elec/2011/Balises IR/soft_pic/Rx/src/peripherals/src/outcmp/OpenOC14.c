#include <outcompare.h>

#ifdef _OC14IF

/*****************************************************************************
*    Function Name:  OpenOC14                                                *
*    Description:    This routine configures output compare module and loads *
*                    the compare registers                                   *
*    Parameters  :   unsigned int config1,unsigned int config1, unsigned int *
*					 value1, unsigned int value2                             *
*                                                                            *
*    Return Value:   None                                                    *
*    Notes           value1 is the compare value for the OCRS register       *
*                    value2 is the compare value for the OCR register        *
*****************************************************************************/

void OpenOC14(unsigned int config1,unsigned int config2, unsigned int value1, unsigned int value2)
{
   
#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    OC14CON1bits.OCM = 0; /* turn off OC before switching to new mode */
    OC14RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC14R = value2;      /* assign value2 to OCxR Main Register*/  
    OC14CON1 = config1;    /* assign config to OCxCON Register*/
    OC14CON2 = config2;

#else
    OC14CONbits.OCM = 0; /* turn off OC before switching to new mode */ 
    OC14RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC14R = value2;      /* assign value2 to OCxR Main Register*/ 
    OC14CON = config1;    /* assign config to OCxCON Register*/

#endif

}
#else
#warning "Does not build on this target"
#endif
