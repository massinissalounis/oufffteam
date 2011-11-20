#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF


/*************************************************************************
* Function Name     : CloseSmpsPWM
* Description       : This function disables the Power Supply PWM module and clears the PWM, 
*                     Faults, Interrupt Enable and Flag bits. This function also clears the PTCON, 
*                     PWMCON1, PWMCON2, PWMCON3,  PWMCON4 ........PWMCON9..registers.                   
* Parameters        : void
* Return Value      : None 
**************************************************************************/

void CloseSmpsPWM(void)
                    
{
    
    /* Clear the PWM Interrupt status Flags of PWMGEN #1, PWMGEN #2 PWMGEN #3, PWMGEN #4 */
	ClearIntSmpsPWM1() ;        
#ifdef _PWM2IF
	ClearIntSmpsPWM2() ;
#endif 	
#ifdef _PWM3IF       
	ClearIntSmpsPWM3() ;
#endif 	
#ifdef _PWM4IF	
	ClearIntSmpsPWM4() ;   
#endif     
#ifdef _PWM5IF
	ClearIntSmpsPWM5() ;
#endif        
#ifdef _PWM6IF
	ClearIntSmpsPWM6() ;
#endif 	
#ifdef _PWM7IF       
	ClearIntSmpsPWM7() ;
#endif 	
#ifdef _PWM8IF	
	ClearIntSmpsPWM8() ;   
#endif     
#ifdef _PWM9IF	
	ClearIntSmpsPWM9() ;   
#endif     

	ClearIntSmpsPWMSevtMatch();
   

/* Clear the PWM Interrupt control registers of PWMGEN #1, PWMGEN #2 PWMGEN #3, PWMGEN #4 */
	SetIntSmpsPWM1(0) ; 
#ifdef _PWM2IF	
	SetIntSmpsPWM2(0) ;
#endif 
#ifdef _PWM3IF       
	SetIntSmpsPWM3(0) ;
#endif 	
#ifdef _PWM4IF
	SetIntSmpsPWM4(0) ; 
#endif      
#ifdef _PWM5IF	
	SetIntSmpsPWM5(0) ;
#endif 
#ifdef _PWM6IF       
	SetIntSmpsPWM6(0) ;
#endif 	
#ifdef _PWM7IF
	SetIntSmpsPWM7(0) ; 
#endif      
#ifdef _PWM8IF       
	SetIntSmpsPWM8(0) ;
#endif 	
#ifdef _PWM9IF
	SetIntSmpsPWM9(0) ; 
	STCON     = STCON_VALUE;
#endif      

	SetIntSmpsPWMSevtMatch(0);

    /* Clear the PWM control registers */
	PTCON     = PTCON_VALUE;

	PWMCON1   = PWMCON1_VALUE;
#ifdef _PWM2IF	
	PWMCON2   = PWMCON2_VALUE;
#endif	
#ifdef _PWM3IF
	PWMCON3   = PWMCON3_VALUE;
#endif	
#ifdef _PWM4IF 
   	PWMCON4   = PWMCON4_VALUE;
#endif	
#ifdef _PWM5IF	
	PWMCON5   = PWMCON5_VALUE;
#endif	
#ifdef _PWM6IF
	PWMCON6   = PWMCON6_VALUE;
#endif	
#ifdef _PWM7IF 
   	PWMCON7   = PWMCON7_VALUE;
#endif            
#ifdef _PWM8IF
	PWMCON8   = PWMCON8_VALUE;
#endif	
#ifdef _PWM9IF 
   	PWMCON9   = PWMCON9_VALUE;
#endif
       
}
#else
#warning "Does not build on this target"
#endif
 
