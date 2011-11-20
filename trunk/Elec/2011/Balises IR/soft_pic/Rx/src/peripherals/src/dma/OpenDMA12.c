#include "dma.h"


/*********************************************************************
* Function Name     : OpenDMA12
* Description       : Configures the DMA12. This includes :
                    · Data size			 // DMA12CON<14> SIZE bit
		    . Data transfer direction       // DMA12CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA12CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA12CON<11> NULLW bit
                    · DMA12 addressing mode select bit	//DMA12CON<5:4> AMODE<1:0> bits
                    . DMA12 operating mode select bit	//DMA12CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA12REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA12REQ<15> FORCE bit
		    . DMA12 start address for register A		//DMA12STA<7:0> STA<7:0> bits
		    . DMA12 start address for register B		//DMA12STB<7:0> STB<7:0> bits
		    . DMA12 peripheral address register		// DMA12PAD register
		    . DMA12 transfer count register		//DMA12CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined _DMA12IF

void OpenDMA12(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA12REQ = irq;

	/* set the start address for buffer A */
	DMA12STAL = sta_address & 0xFFFF;
	DMA12STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA12STBL = stb_address & 0xFFFF;
	DMA12STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA12PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA12CNT = count;
	
    /* configures the DMA12 CONTROL register */

    DMA12CON = config;
	/* enable the DMA12 */

	DMA12CONbits.CHEN = 1;


}
#else
#warning "Does not build on this target"
#endif
