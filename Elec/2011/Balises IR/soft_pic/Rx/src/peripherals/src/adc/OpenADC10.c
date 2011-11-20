#include "adc10.h"

#ifdef _ADC_10BIT

/*********************************************************************
* Function Name     : OpenADC10
* Description       : Configures the ADC. This includes :
                    · Operating mode      // ADCON1<15> ADON bit
                    · Data o/p format     // ADCON1<9:8> FORM bits
                    · Sample Clk Source   // ADCON1<7:5> SSRC<2:0>bits
                    · Vref source         // ADCON2<15:13> VCFG<2:0> bits
                    . Channels utilized   // ADCON2<9:8> CHPS<1:0>bits
                    · No of samples/int   // ADCON2<4:2> SMPI<2:0>bits
                    · Buffer fill mode    // ADCON2<1> BUFM bit
                    · Alternate i/p sample mode // ADCON2<0> ALTS
                    · Auto sample time   //ADCON3<12:8> SAMC<4:0>bits
                    · Conv clock source  //ADCON3<6> ADRC
                    · Conv clock select bits //ADCON3<5:0> ADCS<5:0>
                    · Port config control bits.

* Parameters        : config1, config2, config3, configscan,configport
* Return Value      : None
*********************************************************************/

void OpenADC10(unsigned int config1, unsigned int config2, unsigned int
               config3,unsigned int configport, unsigned int configscan)
{
    /* digital/analog mode selection on the port bits */
    ADPCFG = configport;

    /* configures the input scan selection bits */
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
