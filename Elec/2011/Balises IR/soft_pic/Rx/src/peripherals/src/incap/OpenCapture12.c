#include <incap.h>

#ifdef _IC12IF

/****************************************************************************************
     Function Name:  OpenCapture12                                  			  			*
     Description:    This function configures the Input Capture module.       			*
                     			 														*
     Arguments       : config1 - This contains the parameters to be configured in the   *
                     ICxCON1/ICxCON register as defined below							*
					 Idle mode operation												*
					   *IC_IDLE_CON														*
					   *IC_IDLE_STOP													*	
					 Clock select for 33E/24E					    					*
					   *IC_SYSCLK_SRC 													*
					   *IC_TIMER1_SRC													*					
					   *IC_TIMER2_SRC													*					
					   *IC_TIMER3_SRC													*
					   *IC_TIMER4_SRC													*
					   *IC_TIMER5_SRC													*
					 Clock select for 33E/24E											*
					   *IC_TIMER2_SRC													*					
					   *IC_TIMER3_SRC							 						*							                                                        	*					
					 Captures per interrupt												*	
					   *IC_INT_4CAPTURE													*
					   *IC_INT_3CAPTURE													*
					   *IC_INT_2CAPTURE													*
					   *IC_INT_1CAPTURE													*
					   *IC_INTERRUPT   													*
					 IC mode select														*
					   *IC_INTERRUPT													*				
					   *IC_EVERY_16_RISE_EDGE											*
					   *IC_EVERY_4_RISE_EDGE											*
					   *IC_EVERY_RISE_EDGE												*
					   *IC_EVERY_FALL_EDGE												*
					   *IC_EVERY_EDGE													*
					   *IC_INPUTCAP_OFF													*	
					   																	*
					 config2 - This contains the parameters to be configured in the		*
                     ICxCON2 register as defined below for 33E/24E						*
                     Cascade Module operation enable\disable							*
                       *IC_CASCADE_ENABLE												*
                       *IC_CASCADE_DISABLE 												*			
                     Trigger Operation Select bit										*
                       *IC_TRIGGER_ENABLE 												*
                       *IC_SYNC_ENABLE													*
                     Timer Trigger bit													*
                       *IC_TRIGGER_TIMER												*
                       *IC_UNTRIGGER_TIMER 												*
                     Source selection for synchronisation and trigger operation 	    *
                       *IC_SYNC_TRIG_IN_DISABLE											*
                       *IC_SYNC_TRIG_IN_OC1												*
                       *IC_SYNC_TRIG_IN_OC2												*
                       *IC_SYNC_TRIG_IN_OC3												*
                       *IC_SYNC_TRIG_IN_OC4												*
                       *IC_SYNC_TRIG_IN_OC5												*
                       *IC_SYNC_TRIG_IN_OC6												*
                       *IC_SYNC_TRIG_IN_OC7												*
                       *IC_SYNC_TRIG_IN_OC8												*
                       *IC_SYNC_TRIG_IN_OC9												*
                       *IC_SYNC_TRIG_IN_IC5												*
                       *IC_SYNC_TRIG_IN_TMR1											*
                       *IC_SYNC_TRIG_IN_TMR2											*
                       *IC_SYNC_TRIG_IN_TMR3											*
					   *IC_SYNC_TRIG_IN_TMR4											*
					   *IC_SYNC_TRIG_IN_TMR5											*
					   *IC_SYNC_TRIG_IN_IC7												*	
					   *IC_SYNC_TRIG_IN_IC8												*	
					   *IC_SYNC_TRIG_IN_IC1												*	
					   *IC_SYNC_TRIG_IN_IC2												*
					   *IC_SYNC_TRIG_IN_IC3												*
					   *IC_SYNC_TRIG_IN_IC4												*
					   *IC_SYNC_TRIG_IN_CMP1											*
					   *IC_SYNC_TRIG_IN_CMP2											*
					   *IC_SYNC_TRIG_IN_CMP3											*
					   *IC_SYNC_TRIG_IN_AD												*
					   *IC_SYNC_TRIG_IN_CTMU                          			      	*
					   *IC_SYNC_TRIG_IN_IC6	                        		            *	
					   *IC_SYNC_TRIG_IN_IC9                         		            *
					 		                			            		            *
    Return Value:   None                                          					    *
*****************************************************************************************/

void OpenCapture12(unsigned int config1, unsigned int config2)
{
    /* Config contains Clock source, number of Captures per interuppt
                                    and Capture Mode */
     
#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	
	IC12CON1 = config1;
	IC12CON2 = config2;

#else

	IC12CON = config1; 

#endif

}

#else
#warning "Does not build on this target"
#endif
