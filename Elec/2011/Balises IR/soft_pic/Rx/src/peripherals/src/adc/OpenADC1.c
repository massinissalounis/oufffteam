#include <adc.h>

#if (defined(_AD1IF) && defined(_PCFG0))
/*********************************************************************
* Function Name     : OpenADC1
* Description       : Configures the ADC. This includes :
                    · Operating mode      // AD1CON1<15> ADON bit
                    · Data o/p format     // AD1CON1<9:8> FORM bits
                    · Sample Clk Source   // AD1CON1<7:5> SSRC<2:0>bits
                    · Vref source         // AD1CON2<15:13> VCFG<2:0> bits
                    . Channels utilized   // AD1CON2<9:8> CHPS<1:0>bits
                    · No of samples/int   // AD1CON2<4:2> SMPI<2:0>bits
                    · Buffer fill mode    // AD1CON2<1> BUFM bit
                    · Alternate i/p sample mode // AD1CON2<0> ALTS
                    · Conv clock source  //AD1CON3<15> ADRC
                    · Auto sample time   //AD1CON3<12:8> SAMC<4:0>bits
                    · Conv clock select bits //AD1CON3<5:0> ADCS<5:0>
		    . Select number of DMA buffer locations per analog input // AD1CON4
                    · Port config control bits.  //AD1CSSH and AD1CSSL

* Parameters        : config1, config2, config3, configscan,configport
* Return Value      : None
*********************************************************************/

void OpenADC1(unsigned int config1, unsigned int config2, unsigned int config3,
              unsigned int config4, unsigned int configport_l, 
              unsigned int configport_h, unsigned int configscan_h,
              unsigned int configscan_l)
{
    /* digital/analog mode selection on the port bits */
    /* configures the input scan selection bits */
#if defined(__dsPIC33FJ64GP206__) || defined(__dsPIC33FJ64GP306__) || \
    defined(__dsPIC33FJ64GP310__) || defined(__dsPIC33FJ64GP706__) || \
    defined(__dsPIC33FJ64GP708__) || defined(__dsPIC33FJ64GP710__) || \
    defined(__dsPIC33FJ128GP206__) || defined(__dsPIC33FJ128GP306__) || \
    defined(__dsPIC33FJ128GP310__) || defined(__dsPIC33FJ128GP706__) || \
    defined(__dsPIC33FJ128GP708__) || defined(__dsPIC33FJ128GP710__) || \
    defined(__dsPIC33FJ256GP506__) || defined(__dsPIC33FJ256GP510__) || \
    defined(__dsPIC33FJ256GP710__) || defined(__dsPIC24HJ64GP206__) || \
    defined(__dsPIC24HJ64GP210__) || defined(__dsPIC24HJ64GP506__) || \
    defined(__dsPIC24HJ64GP510__) || defined(__dsPIC24HJ128GP206__) || \
    defined(__dsPIC24HJ128GP210__) || defined(__dsPIC24HJ128GP506__) || \
    defined(__dsPIC24HJ128GP510__) || defined(__dsPIC24HJ128GP306__) || \
    defined(__dsPIC24HJ128GP310__) || defined(__dsPIC24HJ256GP206__) || \
    defined(__dsPIC24HJ256GP210__) || defined(__dsPIC24HJ256GP610__)    
    


    AD1PCFGH = configport_h;
    AD1CSSH = configscan_h;
    AD1PCFGL = configport_l;
    AD1CSSL = configscan_l;
	
#else

    AD1PCFGL = configport_l;
    AD1CSSL = configscan_l;

#endif

#ifdef _DMA0IF

    /* config AD1CON4 only if DMA is present on the device */
    AD1CON4 =  config4;	

#endif

    /* config AD1CON3 */
    AD1CON3 = config3;
    
    /* config AD1CON2 */
    AD1CON2 = config2;

    /* config AD1CON1 */
    AD1CON1 = config1;

    /* assign SAMP bit */
    AD1CON1bits.SAMP = config1 >> 1;
}

#elif (defined(_AD1IF) && defined(_ANSB0))
/*********************************************************************
* Function Name     : OpenADC1
* Description       : Configures the ADC. This includes :
                    · Operating mode      // AD1CON1<15> ADON bit
                    · Data o/p format     // AD1CON1<9:8> FORM bits
                    · Sample Clk Source   // AD1CON1<7:5> SSRC <2:0> bits SSRCG bit
                    · Vref source         // AD1CON2<15:13> VCFG<2:0> bits
                    · Channels utilized   // AD1CON2<9:8> CHPS<1:0>bits
                    · No of samples/int   // AD1CON2<6:2> SMPI<4:0>bits
                    · Buffer fill mode    // AD1CON2<1> BUFM bit
                    · Alternate i/p sample mode // AD1CON2<0> ALTS
                    · Conv clock source  //AD1CON3<15> ADRC
                    · Auto sample time   //AD1CON3<12:8> SAMC<4:0>bits
                    · Conv clock select bits //AD1CON3<7:0> ADCS<7:0>
		    		· Select number of DMA buffer locations per analog input // AD1CON4
                    · Port config control bits.  //AD1CSSH and AD1CSSL
					· Analog Input Configuration. //ANSELA, ANSELB, ANSELC and ANSELE

* Parameters        : config1, config2, config3, config4, configport_a, configport_b,
					  configport_c, configport_e, configscan_h and configscan_l
* Return Value      : None
*********************************************************************/

void OpenADC1(unsigned int config1, unsigned int config2, unsigned int config3,
              unsigned int config4, unsigned int configport_a, unsigned int configport_b,
              unsigned int configport_c, unsigned int configport_e, 
              unsigned int configscan_h, unsigned int configscan_l)
{
    /* digital/analog mode selection on the port bits */
#ifdef _ANSELA6	
    ANSELA = configport_a;
#endif
    ANSELB = configport_b;
    ANSELC = configport_c;
    ANSELE = configport_e;

    /* configures the input scan selection bits */
    AD1CSSH = configscan_h;
    AD1CSSL = configscan_l;
	
#ifdef _DMA0IF

    /* config AD1CON4 only if DMA is present on the device */
    AD1CON4 =  config4;	

#endif

    /* config AD1CON3 */
    AD1CON3 = config3;
    
    /* config AD1CON2 */
    AD1CON2 = config2;

    /* config AD1CON1 */
    AD1CON1 = config1;

    /* assign SAMP bit */
    AD1CON1bits.SAMP = config1 >> 1;
}

#else
#warning "Does not build on this target"
#endif
