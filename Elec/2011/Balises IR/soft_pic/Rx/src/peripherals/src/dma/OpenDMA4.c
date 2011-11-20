#include "dma.h"

#ifdef _DMA4IF

/*********************************************************************
* Function Name     : OpenDMA4
* Description       : Configures the DMA4. This includes :
                    · Data size			 // DMA4CON<14> SIZE bit
		    . Data transfer direction       // DMA4CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA4CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA4CON<11> NULLW bit
                    · DMA4 addressing mode select bit	//DMA4CON<5:4> AMODE<1:0> bits
                    . DMA4 operating mode select bit	//DMA4CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA4REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA4REQ<15> FORCE bit
		    . DMA4 start address for register A		//DMA4STA<7:0> STA<7:0> bits
		    . DMA4 start address for register B		//DMA4STB<7:0> STB<7:0> bits
		    . DMA4 peripheral address register		// DMA4PAD register
		    . DMA4 transfer count register		//DMA4CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if defined (__dsPIC33E__) || defined (__PIC24E__)

void OpenDMA4(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA4REQ = irq;

	/* set the start address for buffer A */
	DMA4STAL = sta_address & 0xFFFF;
	DMA4STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA4STBL = stb_address & 0xFFFF;
	DMA4STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA4PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA4CNT = count;
	
    /* configures the DMA4 CONTROL register */

    DMA4CON = config;
	/* enable the DMA4 */

	DMA4CONbits.CHEN = 1;


}
#else

void OpenDMA4(unsigned int config, unsigned int irq, unsigned int sta_address,
              unsigned int stb_address, unsigned int pad_address,
              unsigned int count )
{


    /* Set the peripheral IRQ number*/
    DMA4REQ = irq;

    /* set the start address for buffer A */
    DMA4STA = sta_address;

    /* set the start address for buffer B */
    DMA4STB = stb_address;

    /* set the peripheral address*/
    DMA4PAD = pad_address;

    /* set the number of bytes/words to be tranfered*/
    DMA4CNT = count;
	
    /* configures the DMA4 CONTROL register */
    DMA4CON = config;
    /* enable the DMA4 */
    DMA4CONbits.CHEN = 1;
}
#endif
#else
#warning "Does not build on this target"
#endif
