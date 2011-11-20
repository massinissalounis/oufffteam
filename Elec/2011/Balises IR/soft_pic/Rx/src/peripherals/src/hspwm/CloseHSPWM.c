#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : CloseHSPWM
* Description       : This function disables the Power Supply PWM module and clears the PWM, 
*                     Faults, Interrupt Enable and Flag bits. This function also clears the PTCON, 
*                     PWMCON1, PWMCON2, PWMCON3,  PWMCON4 ........PWMCON7..registers.                   
* Parameters        : void
* Return Value      : None 
**************************************************************************/

void CloseHSPWM(void)
{
    /* Clear the PWM Interrupt status Flags of PWMGEN #1, PWMGEN #2 PWMGEN #3, PWMGEN #4 */
	/*                                                    PWMGEN #5 PWMGEN #6, PWMGEN #7 */
#ifdef _PWM1IF
	ClearIntHSPWM1();
#endif 	
#ifdef _PWM2IF
	ClearIntHSPWM2();
#endif 	
#ifdef _PWM3IF       
	ClearIntHSPWM3();
#endif 	
#ifdef _PWM4IF	
	ClearIntHSPWM4();
#endif     
#ifdef _PWM5IF
	ClearIntHSPWM5();
#endif      
#ifdef _PWM6IF
	ClearIntHSPWM6();
#endif 	
#ifdef _PWM7IF       
	ClearIntHSPWM7();
#endif 	

	ClearIntHSPWMSevtMatch();

/* Clear the PWM Interrupt control registers of PWMGEN #1, PWMGEN #2 PWMGEN #3, PWMGEN #4 */
/*                                                         PWMGEN #5 PWMGEN #6, PWMGEN #7 */
#ifdef _PWM1IF
	SetIntHSPWM1(0);
#endif 
#ifdef _PWM2IF	
	SetIntHSPWM2(0) ;
#endif 
#ifdef _PWM3IF       
	SetIntHSPWM3(0) ;
#endif 	
#ifdef _PWM4IF
	SetIntHSPWM4(0) ; 
#endif      
#ifdef _PWM5IF	
	SetIntHSPWM5(0) ;
#endif 
#ifdef _PWM6IF       
	SetIntHSPWM6(0) ;
#endif 	
#ifdef _PWM7IF
	SetIntHSPWM7(0) ; 
#endif      
	SetIntHSPWMSevtMatch(0);

    /* Clear the PWM control registers */
	STCON     = STCON_VALUE;
	PTCON     = PTCON_VALUE;

#ifdef _PWM1IF	
	PWMCON1   = PWMCON1_VALUE;
#endif	
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
            
}
#else
#warning "Does not build on this target"
#endif
 
