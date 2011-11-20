#include "dma.h"

#ifdef _DMA7IF

/*********************************************************************
* Function Name     : OpenDMA7
* Description       : Configures the DMA7. This includes :
                    · Data size			 // DMA7CON<14> SIZE bit
		    . Data transfer direction       // DMA7CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA7CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA7CON<11> NULLW bit
                    · DMA7 addressing mode select bit	//DMA7CON<5:4> AMODE<1:0> bits
                    . DMA7 operating mode select bit	//DMA7CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA7REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA7REQ<15> FORCE bit
		    . DMA7 start address for register A		//DMA7STA<7:0> STA<7:0> bits
		    . DMA7 start address for register B		//DMA7STB<7:0> STB<7:0> bits
		    . DMA7 peripheral address register		// DMA7PAD register
		    . DMA7 transfer count register		//DMA7CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if defined (__dsPIC33E__) || defined (__PIC24E__)

void OpenDMA7(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA7REQ = irq;

	/* set the start address for buffer A */
	DMA7STAL = sta_address & 0xFFFF;
	DMA7STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA7STBL = stb_address & 0xFFFF;
	DMA7STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA7PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA7CNT = count;
	
    /* configures the DMA7 CONTROL register */

    DMA7CON = config;
	/* enable the DMA7 */

	DMA7CONbits.CHEN = 1;


}
#else

void OpenDMA7(unsigned int config, unsigned int irq, unsigned int sta_address,
              unsigned int stb_address, unsigned int pad_address,
              unsigned int count)
{

    /* Set the peripheral IRQ number*/
    DMA7REQ = irq;

    /* set the start address for buffer A */
    DMA7STA = sta_address;

    /* set the start address for buffer B */
    DMA7STB = stb_address;

    /* set the peripheral address*/
    DMA7PAD = pad_address;

    /* set the number of bytes/words to be tranfered*/
    DMA7CNT = count;
    
    /* configures the DMA7 CONTROL register */
    DMA7CON = config;
	
    /* enable the DMA0 */
    DMA7CONbits.CHEN = 1;
}
#endif
#else
#warning "Does not build on this target"
#endif
