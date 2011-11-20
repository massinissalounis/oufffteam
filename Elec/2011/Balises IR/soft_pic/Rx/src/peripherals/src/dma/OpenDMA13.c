#include "dma.h"


/*********************************************************************
* Function Name     : OpenDMA13
* Description       : Configures the DMA13. This includes :
                    · Data size			 // DMA13CON<14> SIZE bit
		    . Data transfer direction       // DMA13CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA13CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA13CON<11> NULLW bit
                    · DMA13 addressing mode select bit	//DMA13CON<5:4> AMODE<1:0> bits
                    . DMA13 operating mode select bit	//DMA13CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA13REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA13REQ<15> FORCE bit
		    . DMA13 start address for register A		//DMA13STA<7:0> STA<7:0> bits
		    . DMA13 start address for register B		//DMA13STB<7:0> STB<7:0> bits
		    . DMA13 peripheral address register		// DMA13PAD register
		    . DMA13 transfer count register		//DMA13CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined _DMA13IF

void OpenDMA13(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA13REQ = irq;

	/* set the start address for buffer A */
	DMA13STAL = sta_address & 0xFFFF;
	DMA13STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA13STBL = stb_address & 0xFFFF;
	DMA13STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA13PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA13CNT = count;
    /* configures the DMA13 CONTROL register */

    DMA13CON = config;
	
	/* enable the DMA13 */

	DMA13CONbits.CHEN = 1;


}
#else
#warning "Does not build on this target"
#endif
