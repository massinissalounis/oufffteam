/*****************************************************************************
 *  Module for Sure Electronics LCD Graphics Library
 *  1602D LCD controller driver  
 *****************************************************************************
 * FileName:        1602D.h
 * Dependencies:    p24Fxxxx.h
 * Processor:       PIC24
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 * Company:         Sure Electronics
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vivian Zhao  		12/01/09	Original
 *****************************************************************************/
#ifndef _1602D_LCD_H
#define _1602D_LCD_H

#if defined(__PIC24F__)
    #include <p24fxxxx.h>
#elif defined (__PIC32MX__)
    #include <p32xxxx.h>
#else
    #error No processor header file.
#endif
////////////////I/O Port Control Ports and Data Input and Output Port//////////
#define RS_PIN PORTBbits.RB15
#define RW_PIN PORTDbits.RD5
#define E_PIN PORTDbits.RD11	//Change Vivia,2010.01.18

#define DATA_PORT      PORTE  	//Data Container
#define TRIS_DATA_PORT TRISE	//Data Port Direction

/////////////////LCD Light////////////////////////////////////////////////
#define LCD_LIGHT PORTDbits.RD0
#define LCD_COMPARE	PORTDbits.RD1
#define LCD_POWER PORTBbits.RB5	//Change Vivia,2010.01.18

#define TRIS_LCD_LIGHT		TRISDbits.TRISD0
#define TRIS_LCD_COMPARE	TRISDbits.TRISD1
#define TRIS_LCD_POWER		TRISBbits.TRISB5

//////////////////////Functions///////////////////////////////////////////
void  DelayMs(int time);
void  Delay300Ns(int time);
void LightLCD(void);
void InitLCDPins(void);
void WriteAdress(unsigned char adr);
void InitByInstru(void);
void WriteCommand(unsigned char cmd);
void WriteData(unsigned char data);
unsigned char ReadCommand();
unsigned char ReadData();
void WriteStr(const char *string,int cnt);
void ReadStr(unsigned char *string,int cnt);
void LCD_check_busy(void);
int Set_Line_Information(int line,const char offset,const char *string,const int num);
//int Read_Line_Information(int line,char *string,int num);

//////////////////////////Varies//////////////////////////////////////////

#endif // _1602D_LCD_H
