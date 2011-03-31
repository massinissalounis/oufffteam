/******************************************************************************
 *
 *                Microchip Memory Disk Drive File System
 *
 ******************************************************************************
 * FileName:        HardwareProfile.h
 * Dependencies:    None
 * Processor:       PIC18/PIC24/dsPIC30/dsPIC33/PIC32
 * Compiler:        C18/C30/C32
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company? for its PICmicro?Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS?CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
*****************************************************************************/


#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_

#include "usb_config.h"	

// Define your clock speed here

// Sample clock speed for PIC18
#if defined (__C30__)

    #define GetSystemClock()        32000000
    #define GetPeripheralClock()    GetSystemClock()
    #define GetInstructionClock()   (GetSystemClock() / 2)

    // Clock values
    #define MILLISECONDS_PER_TICK       10                      // Definition for use with a tick timer
    #define TIMER_PRESCALER             TIMER_PRESCALER_8       // Definition for use with a tick timer
    #define TIMER_PERIOD                20000                   // Definition for use with a tick timer

// Sample clock speed for a 32-bit processor
#elif defined (__PIC32MX__)

    // Indicates that the PIC32 clock is running at 48 MHz
    //#define RUN_AT_48MHZ
    // Indicates that the PIC32 clock is running at 24 MHz
    //#define RUN_AT_24MHZ
    // Indicates that the PIC32 clock is running at 80 MHz
    #define RUN_AT_60MHZ

    // Various clock values

    #if defined(RUN_AT_48MHZ)
        #define GetSystemClock()            48000000UL              // System clock frequency (Hz)
        #define GetPeripheralClock()        48000000UL              // Peripheral clock frequency
        #define GetInstructionClock()       (GetSystemClock())      // Instruction clock frequency
    #elif defined(RUN_AT_24MHZ)
        #define GetSystemClock()            24000000UL
        #define GetPeripheralClock()        24000000UL
        #define GetInstructionClock()       (GetSystemClock())
    #elif defined(RUN_AT_60MHZ)    
        #define GetSystemClock()            (60000000ul)
        #define GetPeripheralClock()        (GetSystemClock()/2) 
        #define GetInstructionClock()       (GetSystemClock())
    #else
        #error Choose a speed
    #endif

    // Clock values

    #define MILLISECONDS_PER_TICK       10                  // Definition for use with a tick timer
    #define TIMER_PRESCALER             TIMER_PRESCALER_8   // Definition for use with a tick timer
    #define TIMER_PERIOD                37500               // Definition for use with a tick timer
#endif
    


// Define the baud rate constants
#if defined(__C30__)
    #define BAUDRATE2       57600UL         // Desired baud rate
    #define BRG_DIV2        16              // BRG baud rate divider
    #define BRGH2           0               // BRGH bit value
#elif defined (__PIC32MX__)
    #define BAUDRATE2       57600UL
    #define BRG_DIV2        16 
    #define BRGH2           0 
#endif

// Description: Macro used to enable the SD-SPI physical layer (SD-SPI.c and .h)
#define USE_SD_INTERFACE_WITH_SPI		//Support Function "1.SD Card" and "3.SD To UART"

// Description: Macro used to enable the USB Host physical layer (USB host MSD library)
//#define USE_USB_INTERFACE				//Support Function "4.USB To UART"

// Description: Macro used to enable the Internal Flash physical layer (InternalFlash.c and .h)
//#define USE_INTERNAL_FLASH				//Support Function "2.In Flash"

#if defined (USE_SD_INTERFACE_WITH_SPI) || defined (USE_USB_INTERFACE) || defined (USE_INTERNAL_FLASH)
	#if defined (USE_SD_INTERFACE_WITH_SPI)
		#if defined (USE_USB_INTERFACE) || defined (USE_INTERNAL_FLASH)
			#error ONLY ONE HARDWARE MODULE
		#endif
	#elif defined (USE_USB_INTERFACE)
		#if defined (USE_SD_INTERFACE_WITH_SPI) || defined (USE_INTERNAL_FLASH)
			#error ONLY ONE HARDWARE MODULE
		#endif
	#else
		#if defined (USE_SD_INTERFACE_WITH_SPI) || defined (USE_USB_INTERFACE)
			#error ONLY ONE HARDWARE MODULE
		#endif
	#endif
#else
	#error PLEASE CHOOSE ONE HARDWARE MODULE
#endif

    /*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #define self_power          1

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
    #define USB_BUS_SENSE       1 
   
    //Uncomment this to make the output HEX of this project 
    //   to be able to be bootloaded using the HID bootloader
    //#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER	

    //If the application is going to be used with the HID bootloader
    //  then this will provide a function for the application to 
    //  enter the bootloader from the application (optional)
    #if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
        #define EnterBootloader() __asm__("goto 0x400")
    #endif  

    //I/O pin definitions 
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

    #define ERASE_BLOCK_SIZE        1024
    #define WRITE_BLOCK_SIZE        128  

#include "uart2.h"

#endif
