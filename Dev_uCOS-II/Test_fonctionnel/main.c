/*********************************************************************
 *
 *      PIC32MX Parallel Master Port (PMP) API Example Code
 *
 *********************************************************************
 * FileName:        pmp_master_mode2_16bit.c
 * Dependencies:	plib.h
 *
 * Processor:       PIC32MX
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32MX Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *********************************************************************
 * $Id: pmp_master_mode2_16bit.c 9390 2008-06-16 23:43:04Z rajbhartin $
 *
 * $Name:  $
 *********************************************************************
 * The purpose of this example code is to demonstrate the use of
 * peripheral library macros and functions supporting the PIC32MX
 * Enhanced Parallel Master Port.
 *
 * Features demonstrated:
 *      - PMP master mode 2
 *      - 16-bit interface configurations
 *
 * Description:
 *	This example demonstrates PMP peripheral Master mode 2 configuration
 * 	and read/write operations to an external device.
 *
 * Oscillator Configuration Bit Settings:
 * 		- Oscillator Selection Bits = 	Primary Osc w/PLL (XT+HS+EC+PLL)
 *		- Primary Oscillator Config = 	HS osc mode
 *		- PLL Input Divider			=	2x Divider
 *		- PLL Multiplier			=	18x Multiplier
 *
 * Notes:
 *
 *
 ********************************************************************/
#include <plib.h>

// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 40 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
//
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF, FSOSCEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

#define SYS_FREQ 			(80000000L)

// Pre-defined bit masks are located in the PIC32MX PMP peripheral library header file
// pmp.h
#define CONTROL     (PMP_ON | PMP_IDLE_CON | PMP_MUX_OFF | PMP_READ_WRITE_EN |\
                     PMP_CS2_CS1_EN | PMP_LATCH_POL_HI | PMP_CS2_POL_LO | PMP_CS1_POL_LO |\
                     PMP_WRITE_POL_LO | PMP_READ_POL_LO)

#define MODE        (PMP_IRQ_OFF | PMP_AUTO_ADDR_OFF | PMP_DATA_BUS_16 | PMP_MODE_MASTER2 |\
                     PMP_WAIT_BEG_3 | PMP_WAIT_MID_7 | PMP_WAIT_END_3 )

#define PORT        (PMP_PEN_ALL)

#define INTERRUPT   (PMP_INT_OFF)

int main(void)
{

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //STEP 1. Configure cache, wait states and peripheral bus clock
	// Configure the device for maximum performance but do not change the PBDIV
	// Given the options, this function will change the flash wait states, RAM
	// wait state and enable prefetch cache but will not change the PBDIV.
	// The PBDIV value is already set via the pragma FPBDIV option above..
	SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

	PORTSetPinsDigitalOut(IOPORT_D, BIT_13 | BIT_11);

	DisableCN0;

	PORTSetPinsDigitalOut(IOPORT_C, BIT_14);

    mPORTCClearBits(BIT_14);


	PORTSetBits(IOPORT_C, BIT_14);
	PORTSetBits(IOPORT_D, BIT_13 | BIT_11);

    while(1);

}
