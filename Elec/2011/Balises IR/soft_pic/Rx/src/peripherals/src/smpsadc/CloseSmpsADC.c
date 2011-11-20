#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP0IF


/*************************************************************************
* Function Name     : CloseSmpsADC
* Description       : This function disables the SMPS ADC module and clears the ADC 
*                     Interrupt Flag bits. This function also clears the ADCON register.                 
* Parameters        : void
* Return Value      : None 
**************************************************************************/

void CloseSmpsADC(void)
                    
{
    
    /* Clear the all ADC Interrupt status Flags  */
#if defined(__dsPIC30F__)
    #ifdef _ADCP0IF
	IFS2bits.ADCP0IF = 0;
    #endif	
    #ifdef _ADCP1IF	
	IFS2bits.ADCP1IF = 0;
    #endif	
    #ifdef _ADCP2IF	
	IFS2bits.ADCP2IF = 0;
    #endif	
    #ifdef _ADCP3IF
	IFS2bits.ADCP3IF = 0;
    #endif
    #ifdef _ADCP4IF
	IFS2bits.ADCP4IF = 0;
    #endif
    #ifdef _ADCP5IF	
	IFS2bits.ADCP5IF = 0;
    #endif
	IFS0bits.ADIF    = 0;

   /* Clear the ADC Interrupt control registers */
    #ifdef _ADCP0IF
	IEC2bits.ADCP0IE = 0;
    #endif	
    #ifdef _ADCP1IF    
	IEC2bits.ADCP1IE = 0;
    #endif	
    #ifdef _ADCP2IF    
	IEC2bits.ADCP2IE = 0;
    #endif	
    #ifdef _ADCP3IF
	IEC2bits.ADCP3IE = 0;
    #endif
    #ifdef _ADCP4IF
	IEC2bits.ADCP4IE = 0;
    #endif
    #ifdef _ADCP5IF
	IEC2bits.ADCP5IE = 0;
    #endif
	IEC0bits.ADIE    = 0;


#elif defined(__dsPIC33F__)
    #ifdef _ADCP0IF
	IFS6bits.ADCP0IF = 0;
    #endif	
    #ifdef _ADCP1IF	
	IFS6bits.ADCP1IF = 0;
    #endif	
    #ifdef _ADCP2IF	
	IFS7bits.ADCP2IF = 0;
    #endif	
    #ifdef _ADCP3IF
	IFS7bits.ADCP3IF = 0;
    #endif
    #ifdef _ADCP4IF
	IFS7bits.ADCP4IF = 0;
    #endif
    #ifdef _ADCP5IF
	IFS7bits.ADCP5IF = 0;
    #endif
    #ifdef _ADCP6IF
	IFS7bits.ADCP6IF = 0;
    #endif

 #ifdef _ADCP7IF
	IFS7bits.ADCP7IF = 0;
    #endif	
    #ifdef _ADCP8IF	
	IFS5bits.ADCP8IF = 0;
    #endif	
    #ifdef _ADCP9IF	
	IFS5bits.ADCP9IF = 0;
    #endif	
    #ifdef _ADCP10IF
	IFS5bits.ADCP10IF = 0;
    #endif
    #ifdef _ADCP11IF
	IFS5bits.ADCP11IF = 0;
    #endif

    #ifdef _ADCP12IF
	IFS5bits.ADCP12IF = 0;
    #endif






	IFS0bits.ADIF    = 0;

   /* Clear the ADC Interrupt control registers */
    #ifdef _ADCP0IF
	IEC6bits.ADCP0IE = 0;
    #endif	
    #ifdef _ADCP1IF	
	IEC6bits.ADCP1IE = 0;
    #endif	
    #ifdef _ADCP2IF	
	IEC7bits.ADCP2IE = 0;
    #endif	
    #ifdef _ADCP3IF
	IEC7bits.ADCP3IE = 0;
    #endif
    #ifdef _ADCP4IF
	IEC7bits.ADCP4IE = 0;
    #endif
    #ifdef _ADCP5IF
	IEC7bits.ADCP5IE = 0;
    #endif
    #ifdef _ADCP6IF
	IEC7bits.ADCP6IE = 0;
    #endif

  #ifdef _ADCP7IF
	IEC7bits.ADCP7IE = 0;
    #endif	
    #ifdef _ADCP8IF	
	IEC5bits.ADCP8IE = 0;
    #endif	
    #ifdef _ADCP9IF	
	IEC5bits.ADCP9IE = 0;
    #endif	
    #ifdef _ADCP9IF
	IEC5bits.ADCP9IE = 0;
    #endif
    #ifdef _ADCP10IF
	IEC5bits.ADCP10IE = 0;
    #endif
    #ifdef _ADCP11IF
	IEC5bits.ADCP11IE = 0;
    #endif
    #ifdef _ADCP12IF
	IEC5bits.ADCP12IE = 0;
    #endif


	IEC0bits.ADIE    = 0;
#endif


    /* Clear the ADC control registers */
	ADCON   = 0;
	
            
}
#else
#warning "Does not build on this target"
#endif
 
