#include "dma.h"

#ifdef _DMA6IF

/*********************************************************************
* Function Name     : OpenDMA0
* Description       : Configures the DMA0. This includes :
                    · Data size			 // DMA6CON<14> SIZE bit
		    . Data transfer direction       // DMA6CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA6CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA6CON<11> NULLW bit
                    · DMA6 addressing mode select bit	//DMA6CON<5:4> AMODE<1:0> bits
                    . DMA6 operating mode select bit	//DMA6CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA6REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA6REQ<15> FORCE bit
		    . DMA6 start address for register A		//DMA6STA<7:0> STA<7:0> bits
		    . DMA6 start address for register B		//DMA6STB<7:0> STB<7:0> bits
		    . DMA6 peripheral address register		// DMA6PAD register
		    . DMA6 transfer count register		//DMA6CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if defined (__dsPIC33E__) || defined (__PIC24E__)

void OpenDMA6(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA6REQ = irq;

	/* set the start address for buffer A */
	DMA6STAL = sta_address & 0xFFFF;
	DMA6STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA6STBL = stb_address & 0xFFFF;
	DMA6STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA6PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA6CNT = count;
	
    /* configures the DMA6 CONTROL register */

    DMA6CON = config;
	/* enable the DMA6 */

	DMA6CONbits.CHEN = 1;


}
#else

void OpenDMA6(unsigned int config, unsigned int irq, unsigned int sta_address,
              unsigned int stb_address, unsigned int pad_address,
              unsigned int count)
{
    

    /* Set the peripheral IRQ number*/
    DMA6REQ = irq;

    /* set the start address for buffer A */
    DMA6STA = sta_address;

    /* set the start address for buffer B */
    DMA6STB = stb_address;

    /* set the peripheral address*/
    DMA6PAD = pad_address;

    /* set the number of bytes/words to be tranfered*/
    DMA6CNT = count;
	
    /* configures the DMA6 CONTROL register */
    DMA6CON = config;
    /* enable the DMA6 */
    DMA6CONbits.CHEN = 1;
}
#endif
#else
#warning "Does not build on this target"
#endif
