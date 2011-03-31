/*****************************************************************************
 *  Module for the LEDs of Sure Electronics Storage Project
 *****************************************************************************
 * FileName:        LED.h
 * Dependencies: 	None
 * Processor:       PIC24
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 * Company:         Sure Electronics
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vivian Zhao  		02/25/10	Original
 *****************************************************************************/
#ifndef _LED_H
#define _LED_H

////////////////////////////////LED Pins///////////////////////////////
#define TRIS_SD_LED TRISDbits.TRISD6
#define TRIS_FLASH_LED TRISFbits.TRISF0
#define TRIS_USB_LED TRISDbits.TRISD7
#define TRIS_ERROR_LED TRISFbits.TRISF1

#define SD_LED _RD6
#define FLASH_LED _RF0
#define USB_LED _RD7
#define ERROR_LED _RF1

//////////////////////////////Turn On/OFF///////////////////////////////
#define INPUT   1
#define OUTPUT  0

#define LED_TURN_ON		0
#define LED_TURN_OFF	1

//////////////////////Functions///////////////////////////////////////////
void LEDInit( void );

#endif
