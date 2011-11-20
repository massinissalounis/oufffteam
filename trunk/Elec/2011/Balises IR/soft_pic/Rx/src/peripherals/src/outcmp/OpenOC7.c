#include <outcompare.h>

#ifdef _OC7IF

/*****************************************************************************
*    Function Name:  OpenOC7                                                 *
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
void OpenOC7 (unsigned int config1, unsigned int config2, unsigned int value1, unsigned int value2)
{
    OC7CON1bits.OCM = 0; /* turn off OC before switching to new mode */
    OC7RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC7R = value2;      /* assign value2 to OCxR Main Register*/  
    OC7CON1 = config1;    /* assign config to OCxCON Register*/
    OC7CON2 = config2;
}
#else
void OpenOC7 (unsigned int config, unsigned int value1, unsigned int value2)
{
    OC7CONbits.OCM = 0; /* turn off OC before switching to new mode */ 
    OC7RS = value1;     /* assign value1 to OCxRS Secondary Register */
    OC7R = value2;      /* assign value2 to OCxR Main Register*/ 
    OC7CON = config;    /* assign config to OCxCON Register*/
}
#endif

#else
#warning "Does not build on this target"
#endif
