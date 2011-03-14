#include <p18cxxx.h>
#include <delays.h>

void pic_initialisation(void);


void main ( void )
{
   pic_initialisation();

   PORTAbits.RA0=1;	
   Delay10KTCYx(200); // Delay de 1 s avec horloge à 40MHz
//   Delay10KTCYx(200);
//   Delay10KTCYx(200);
//   Delay10KTCYx(200);
   PORTAbits.RA0=0;	
  
   while(1)
   {
   
   }
}


void pic_initialisation(void)
{
	// Configuration de l'oscillateur interne ( 4 MHz )
	OSCTUNE=0;
	OSCCON=0b01100010;

	// Configuration de l'oscillateur interne ( 32 MHz )
//	OSCCON=0b01110000;
	//OSCTUNEbits.PLLEN=1;
//	OSCTUNE=0b01000000;		
	// Configuration des ports d'E/S

	ADCON0 = 0x00; // On coupe la conversion analogique/numérique
  	ADCON1 = 0x0F; // On place toutes nos pattes en digitale
	// Ainsi on peut utiliser notre portA

	// 0 : ecriture 1 : lecture
	// RA7 : DATA7 - RA6 : DATA6 - RA5 : DATA5 - RA4 : DATA4 - RA3 : DATA3 - RA2 : DATA2 - RA1 : DATA1 - RA0 : DATA0
	TRISA=0b00000000;
	// RB7 : PGD - RB6 : PGC - RB5 : LED0  - RB4 : Current1 - RB3 : Current0 - RB1 : INT1 - RB1 : INT0 - RB0 : INT_EXT
//	TRISB=0b11011111;
	// RC7 : CS1 - RC6 : CS0 - RC5 : RST - RC4 : SDA - RC3 : SCL - RC2 : PS - RC1 : WR - RC0 : RD
//	TRISC=0b00011000;

//	LED0=_OFF; // On initialise les pattes du pics
}