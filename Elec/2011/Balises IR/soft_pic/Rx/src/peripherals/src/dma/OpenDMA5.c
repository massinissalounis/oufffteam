#include "dma.h"

#ifdef _DMA5IF

/*********************************************************************
* Function Name     : OpenDMA5
* Description       : Configures the DMA5. This includes :
                    · Data size			 // DMA5CON<14> SIZE bit
		    . Data transfer direction       // DMA5CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA5CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA5CON<11> NULLW bit
                    · DMA5 addressing mode select bit	//DMA5CON<5:4> AMODE<1:0> bits
                    . DMA5 operating mode select bit	//DMA5CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA5REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA5REQ<15> FORCE bit
		    . DMA5 start address for register A		//DMA5STA<7:0> STA<7:0> bits
		    . DMA5 start address for register B		//DMA5STB<7:0> STB<7:0> bits
		    . DMA5 peripheral address register		// DMA5PAD register
		    . DMA5 transfer count register		//DMA5CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if defined (__dsPIC33E__) || defined (__PIC24E__)

void OpenDMA5(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA5REQ = irq;

	/* set the start address for buffer A */
	DMA5STAL = sta_address & 0xFFFF;
	DMA5STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA5STBL = stb_address & 0xFFFF;
	DMA5STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA5PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA5CNT = count;
	
    /* configures the DMA5 CONTROL register */

    DMA5CON = config;
	/* enable the DMA5 */

	DMA5CONbits.CHEN = 1;


}
#else

void OpenDMA5(unsigned int config, unsigned int irq, unsigned int sta_address,
              unsigned int stb_address, unsigned int pad_address,
              unsigned int count)
{
    

    /* Set the peripheral IRQ number*/
    DMA5REQ = irq;

    /* set the start address for buffer A */
    DMA5STA = sta_address;

    /* set the start address for buffer B */
    DMA5STB = stb_address;

    /* set the peripheral address*/
    DMA5PAD = pad_address;

    /* set the number of bytes/words to be tranfered*/
    DMA5CNT = count;
	
    /* configures the DMA5 CONTROL register */
    DMA5CON = config;
    /* enable the DMA5 */
    DMA5CONbits.CHEN = 1;
}
#endif
#else
#warning "Does not build on this target"
#endif
