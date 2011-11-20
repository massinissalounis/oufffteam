#include <adc.h>

#if (defined(_AD2IF) && defined(_PCFG0))
/*********************************************************************
* Function Name     : OpenADC2
* Description       : This function configures the ADC. This includes :
                    · Operating mode         // AD2CON1<15> ADON bit
                    · Data o/p format        // AD2CON1<9:8> FORM bits
                    · Sample Clk Source      // AD2CON1<7:5> SSRC<2:0>bits
                    · Vref source            // AD2CON2<15:13> VCFG<2:0> bits
                    · No of samples/int      // AD2CON2<4:2> SMPI<2:0>bits
                    · Buffer fill mode       // AD2CON2<1> BUFM bit
                    · Alternate i/p sample mode // AD2CON2<0> ALTS
                    · Conv clock source      //AD2CON3<15> ADRC
                    · Auto sample time       //AD2CON3<12:8> SAMC<4:0>bits
                    · Conv clock select bits //AD2CON3<5:0> ADCS<5:0>
                    · Port config control bits.
		    . Select number of DMA buffer locations per analog input // AD1CON4
* Parameters        : config1, config2, config3, configscan,configport
* Return Value      : None
*********************************************************************/

void OpenADC2(unsigned int config1, unsigned int config2, 
              unsigned int config3, unsigned int config4, 
              unsigned int configport_l, unsigned int configport_h, 
              unsigned int configscan_h, unsigned int configscan_l)
{
    /* digital/analog mode selection on the port bits */
    AD2PCFGL = configport_l;

    /* configures the input scan selection bits */
    AD2CSSL = configscan_l;

#ifdef _DMA0IF

    /* config AD1CON4 only if DMA is present on the device */
    AD2CON4 =  config4;	

#endif

    /* config AD1CON3 */
    AD2CON3 = config3;
    
    /* config AD1CON2 */
    AD2CON2 = config2;

    /* config AD1CON1 */
    AD2CON1 = config1;

    /* assign SAMP bit */
    AD2CON1bits.SAMP = config1 >> 1;
}

#elif (defined(_AD2IF) && defined(_ANSB0))
/*********************************************************************
* Function Name     : OpenADC2
* Description       : Configures the ADC. This includes :
                    · Operating mode      // AD2CON1<15> ADON bit
                    · Data o/p format     // AD2CON1<9:8> FORM bits
                    · Sample Clk Source   // AD2CON1<7:5> SSRC <2:0> bits SSRCG bit
                    · Vref source         // AD2CON2<15:13> VCFG<2:0> bits
                    · Channels utilized   // AD2CON2<9:8> CHPS<1:0>bits
                    · No of samples/int   // AD2CON2<6:2> SMPI<4:0>bits
                    · Buffer fill mode    // AD2CON2<1> BUFM bit
                    · Alternate i/p sample mode // AD2CON2<0> ALTS
                    · Conv clock source  //AD2CON3<15> ADRC
                    · Auto sample time   //AD2CON3<12:8> SAMC<4:0>bits
                    · Conv clock select bits //AD2CON3<7:0> ADCS<7:0>
		    		· Select number of DMA buffer locations per analog input // AD2CON4
                    · Port config control bits.  //AD2CSSL
					· Analog Input Configuration. // ANSELB

* Parameters        : config1, config2, config3, config4, configport_a, configport_b,
					  configport_c, configport_e, configscan_h and configscan_l
* Return Value      : None
*********************************************************************/

void OpenADC2(unsigned int config1, unsigned int config2, unsigned int config3,
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
    AD2CSSL = configscan_l;
	
#ifdef _DMA0IF

    /* config AD2CON4 only if DMA is present on the device */
    AD2CON4 =  config4;	

#endif

    /* config AD2CON3 */
    AD2CON3 = config3;
    
    /* config AD2CON2 */
    AD2CON2 = config2;

    /* config AD2CON1 */
    AD2CON1 = config1;

    /* assign SAMP bit */
    AD2CON1bits.SAMP = config1 >> 1;
}

#else
#warning "Does not build on this target"
#endif

