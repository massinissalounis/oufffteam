#include "dma.h"


/*********************************************************************
* Function Name     : OpenDMA11
* Description       : Configures the DMA11. This includes :
                    · Data size			 // DMA11CON<14> SIZE bit
		    . Data transfer direction       // DMA11CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA11CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA11CON<11> NULLW bit
                    · DMA11 addressing mode select bit	//DMA11CON<5:4> AMODE<1:0> bits
                    . DMA11 operating mode select bit	//DMA11CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA11REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA11REQ<15> FORCE bit
		    . DMA11 start address for register A		//DMA11STA<7:0> STA<7:0> bits
		    . DMA11 start address for register B		//DMA11STB<7:0> STB<7:0> bits
		    . DMA11 peripheral address register		// DMA11PAD register
		    . DMA11 transfer count register		//DMA11CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined _DMA11IF

void OpenDMA11(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA11REQ = irq;

	/* set the start address for buffer A */
	DMA11STAL = sta_address & 0xFFFF;
	DMA11STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA11STBL = stb_address & 0xFFFF;
	DMA11STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA11PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA11CNT = count;
    /* configures the DMA11 CONTROL register */

    DMA11CON = config;
	
	/* enable the DMA11 */

	DMA11CONbits.CHEN = 1;


}
#else
#warning "Does not build on this target"
#endif
