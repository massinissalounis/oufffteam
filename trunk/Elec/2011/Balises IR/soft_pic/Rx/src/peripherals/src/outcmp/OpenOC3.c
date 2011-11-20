#include <outcompare.h>

#ifdef _OC3IF

/*****************************************************************************
*    Function Name:  OpenOC3                                                 *
*    Description:    This routine configures output compare module and loads *
*                    the compare registers                                   *
*    Parameters  :   unsigned int config1, unsigned int config2 (dsPIC33E/PIC24E only), * 
*					 unsigned int value1, unsigned int value2  *
*                                                                            *
*    Return Value:   None                                                    *
*    Notes           value1 is the compare value for the OCRS register       *
*                    value2 is the compare value for the OCR register        *
*****************************************************************************/

#if defined(__dsPIC33E__) || defined(__PIC24E__) 
void OpenOC3 (unsigned int config1, unsigned int config2, unsigned int value1, unsigned int value2)
{
    OC3CON1bits.OCM = 0; /* turn off OC before switching to new mode */
    OC3RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC3R = value2;      /* assign value2 to OCxR Main Register*/  
    OC3CON1 = config1;    /* assign config to OCxCON Register*/
    OC3CON2 = config2;
}
#else
void OpenOC3 (unsigned int config, unsigned int value1, unsigned int value2)
{
    OC3CONbits.OCM = 0; /* turn off OC before switching to new mode */ 
    OC3RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC3R = value2;      /* assign value2 to OCxR Main Register*/ 
    OC3CON = config;    /* assign config to OCxCON Register*/
}
#endif

#else
#warning "Does not build on this target"
#endif
