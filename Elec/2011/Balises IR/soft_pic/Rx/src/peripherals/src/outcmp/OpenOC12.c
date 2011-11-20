#include <outcompare.h>

#ifdef _OC12IF

/*****************************************************************************
*    Function Name:  OpenOC12                                                *
*    Description:    This routine configures output compare module and loads *
*                    the compare registers                                   *
*    Parameters  :   unsigned int config1,unsigned int config1, unsigned int *
*					 value1, unsigned int value2                             *
*                                                                            *
*    Return Value:   None                                                    *
*    Notes           value1 is the compare value for the OCRS register       *
*                    value2 is the compare value for the OCR register        *
*****************************************************************************/

void OpenOC12(unsigned int config1,unsigned int config2, unsigned int value1, unsigned int value2)
{
   
#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    OC12CON1bits.OCM = 0; /* turn off OC before switching to new mode */
    OC12RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC12R = value2;      /* assign value2 to OCxR Main Register*/  
    OC12CON1 = config1;    /* assign config to OCxCON Register*/
    OC12CON2 = config2;

#else
    OC12CONbits.OCM = 0; /* turn off OC before switching to new mode */ 
    OC12RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC12R = value2;      /* assign value2 to OCxR Main Register*/ 
    OC12CON = config1;    /* assign config to OCxCON Register*/

#endif

}
#else
#warning "Does not build on this target"
#endif
