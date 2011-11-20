#include "dma.h"

#ifdef _DMA2IF

/*********************************************************************
* Function Name     : OpenDMA2
* Description       : Configures the DMA2. This includes :
                    · Data size			 // DMA2CON<14> SIZE bit
		    . Data transfer direction       // DMA2CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA2CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA2CON<11> NULLW bit
                    · DMA2 addressing mode select bit	//DMA2CON<5:4> AMODE<1:0> bits
                    . DMA2 operating mode select bit	//DMA2CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA2REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA2REQ<15> FORCE bit
		    . DMA2 start address for register A		//DMA2STA<7:0> STA<7:0> bits
		    . DMA2 start address for register B		//DMA2STB<7:0> STB<7:0> bits
		    . DMA2 peripheral address register		// DMA2PAD register
		    . DMA2 transfer count register		//DMA2CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if defined (__dsPIC33E__) || defined (__PIC24E__)

void OpenDMA2(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA2REQ = irq;

	/* set the start address for buffer A */
	DMA2STAL = sta_address & 0xFFFF;
	DMA2STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA2STBL = stb_address & 0xFFFF;
	DMA2STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA2PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA2CNT = count;
	
    /* configures the DMA2 CONTROL register */

    DMA2CON = config;
	/* enable the DMA2 */

	DMA2CONbits.CHEN = 1;


}
#else

void OpenDMA2(unsigned int config, unsigned int irq, unsigned int sta_address,
              unsigned int stb_address, unsigned int pad_address,
              unsigned int count)
{


    /* Set the peripheral IRQ number*/
    DMA2REQ = irq;

    /* set the start address for buffer A */
    DMA2STA = sta_address;

    /* set the start address for buffer B */
    DMA2STB = stb_address;

    /* set the peripheral address*/
    DMA2PAD = pad_address;

    /* set the number of bytes/words to be tranfered*/
    DMA2CNT = count;
	
    /* configures the DMA2 CONTROL register */
    DMA2CON = config;
    /* enable the DMA2 */
    DMA2CONbits.CHEN = 1;
}
#endif
#else
#warning "Does not build on this target"
#endif
