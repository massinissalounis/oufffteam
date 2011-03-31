/*****************************************************************************
 *  Module for the buttons of Sure Electronics Storage Project
 *****************************************************************************
 * FileName:        Button.h
 * Dependencies: None
 * Processor:       PIC24
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 * Company:         Sure Electronics
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vivian Zhao  		12/08/09	Original
 *****************************************************************************/
 #ifndef _BUTTON_H
#define _BUTTON_H

////////////////////////////////Button Pins///////////////////////////////
#define TRIS_L_BUTTON TRISBbits.TRISB3
#define TRIS_R_BUTTON TRISBbits.TRISB4
#define TRIS_M_BUTTON TRISBbits.TRISB2

///////////////////////////////Constant///////////////////////////////////
#define NUM_TOUCHPADS	3
#define STARTING_ADC_CHANNEL 2			//RB2(AN2),RB3(AN3),RB4(AN4)

///////////////////////////////Varies/////////////////////////////////////
extern int buttonPress;

//////////////////////Functions///////////////////////////////////////////
void ButtonInit( void );
void ReadButton();
void ButtonsMsg();

#endif
