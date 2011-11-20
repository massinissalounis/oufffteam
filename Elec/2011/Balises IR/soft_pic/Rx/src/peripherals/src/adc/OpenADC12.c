#include "adc12.h"

#ifdef _ADC_12BIT

/*********************************************************************
* Function Name     : OpenADC12
* Description       : This function configures the ADC. This includes :
                    · Operating mode         // ADCON1<15> ADON bit
                    · Data o/p format        // ADCON1<9:8> FORM bits
                    · Sample Clk Source      // ADCON1<7:5> SSRC<2:0>bits
                    · Vref source            // ADCON2<15:13> VCFG<2:0> bits
                    · No of samples/int      // ADCON2<4:2> SMPI<2:0>bits
                    · Buffer fill mode       // ADCON2<1> BUFM bit
                    · Alternate i/p sample mode // ADCON2<0> ALTS
                    · Auto sample time       //ADCON3<12:8> SAMC<4:0>bits
                    · Conv clock source      //ADCON3<6> ADRC
                    · Conv clock select bits //ADCON3<5:0> ADCS<5:0>
                    · Port config control bits.

* Parameters        : config1, config2, config3, configscan,configport
* Return Value      : None
*********************************************************************/

void OpenADC12(unsigned int config1, unsigned int config2, unsigned int config3,
               unsigned int configport, unsigned int configscan)
{
    /* digital/analog mode selection on the port bits */
    ADPCFG = configport;

    /* configure the input scan selection bits */
    ADCSSL = configscan;

    /* config ADCON3 */
    ADCON3 = config3;
    
    /* config ADCON2 */
    ADCON2 = config2;

    /* config ADCON1 */
    ADCON1 = config1;

    /* assign SAMP bit */
    ADCON1bits.SAMP = config1 >> 1;
}

#else
#warning "Does not build on this target"
#endif
