#include <outcompare.h>

#ifdef _OC12IF

/********************************************************************
*    Function Name:  ReadRegOC12		                            *
*    Description:    In Non PWM Mode, this function reads the OCRS  *
*                    reg or OCR reg based on input parameter        *
*    Parameters:     char reg                                       *
*    Return Value:   unsigned int OCRS (if reg is 0)                *
*                    or OCR (if reg is 1)                           *
********************************************************************/

unsigned int ReadRegOC12(char reg)
{   
    
#if defined(__dsPIC33E__) || defined(__PIC24E__) 
    /* check if OC is in NON_PWM Mode */
    if((OC12CON1bits.OCM & 0x06) != 0x06) 
    {                                                    
        if(reg)
        {       
            return OC12R; /* Output Compare main Register */
            
        }     
        return OC12RS;    /* Output Compare Secondary Register */
    }  

#else    
    /* check if OC is in NON_PWM Mode */
    if((OC12CONbits.OCM & 0x06) != 0x06) 
    {                                                    
        if(reg)
        {       
            return OC12R; /* Output Compare main Register */
            
        }     
        return OC12RS;    /* Output Compare Secondary Register */
    }  

#endif
    return -1;  
}

#else
#warning "Does not build on this target"
#endif
