#ifndef __PERIPHERALVERSION_H
#define __PERIPHERALVERSION_H
/******************************************************************************
 *
 *                  PERIPHERAL SELECT HEADER FILE
 *
 ******************************************************************************
 * FileName:        peripheralversion.h
 * Dependencies:    See include below
 * Processor:       dsPIC33F/30F/pic24H
 * Compiler:        MPLAB C30
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
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
 *****************************************************************************/


#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include <p24Hxxxx.h>
#elif defined(__PIC24E__)
#include <p24Exxxx.h>
#else
#error "Does not build on this target"
#endif

/*********************** Peripheral Inclusion Macros **************************/


#if defined(__dsPIC33FJ32MC302__) || defined(__dsPIC33FJ32MC304__) || defined(__dsPIC33FJ64MC202__) || defined(__dsPIC33FJ64MC204__) || defined(__dsPIC33FJ64MC802__) || defined(__dsPIC33FJ64MC804__) || defined(__dsPIC33FJ128MC202__) || defined(__dsPIC33FJ128MC204__) || defined(__dsPIC33FJ128MC802__) || defined(__dsPIC33FJ128MC804__) || defined(__dsPIC33FJ32GP302__) || defined(__dsPIC33FJ32GP304__) || defined(__dsPIC33FJ64GP202__) || defined(__dsPIC33FJ64GP204__) || defined(__dsPIC33FJ64GP802__) || defined(__dsPIC33FJ64GP804__) || defined(__dsPIC33FJ128GP202__) || defined(__dsPIC33FJ128GP204__) || defined(__dsPIC33FJ128GP802__) || defined(__dsPIC33FJ128GP804__) || defined(__PIC24HJ32GP302__) || defined(__PIC24HJ32GP304__) || defined(__PIC24HJ64GP202__) || defined(__PIC24HJ64GP204__) || defined(__PIC24HJ64GP502__) || defined(__PIC24HJ64GP504__) || defined(__PIC24HJ128GP202__) || defined(__PIC24HJ128GP204__) || defined(__PIC24HJ128GP502__) || defined(__PIC24HJ128GP504__)
           		   
#define _TMR_RTCC_V1       /* RTCC module*/

#define _CRC_PROG_V1       /* CRC module*/

#define _PPI_PMP_V1        /* PMP module*/

#define _COMPARATOR_V1     /* Comparator module*/

#endif

#if defined(__dsPIC33E__) || defined(__PIC24E__)

#define _TMR_RTCC_V1       /* RTCC module*/
    
#define _CRC_PROG_V2       /* CRC module*/

#define _PPI_PMP_V2        /* PMP module*/

#define _COMPARATOR_V2     /* Comparator module*/

#define _PPI_PPS_V2		   /* PPS module*/

#endif

#endif
