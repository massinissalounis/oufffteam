/*******************************************************************************************
   File           :  Oufff_RS232.h
   Authors        :  Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  Class to use RS232 Port
   History        :
      2008_05_02 (Fifi_one)   : Initial Version

   Dependencies   :
      None
/*******************************************************************************************/


#ifndef OUFFF_RS232_H
#define OUFFF_RS232_H


// Globale Include
#include <windows.h>
#include <stdio.h>

// Specific include
#include "Oufff_LibErrorCode.h"
#include "Oufff_LibConfig.h"

// Class definition ------------------------------------------------------------------------
class Oufff_RS232
{
public:
	// ---------- CONSTRUCTOR ----------
	Oufff_RS232();			// Constructor
	~Oufff_RS232();		// Destructor

	// -- OPEN / CONFIG / CLOSE PORT ---
	int OpenPort(int NumPort, int SpeedPort);	// Open port with settings (8 bits, 1 stop bit, no parity)
	int SetPortTimeOut(DWORD Delay);				// Set time-out in ms for receive data.
	int SetPortSpeed(DWORD SpeedPort);			// Set speed in bauds.
	int ClosePort();									// Close serial port.

	//------ SEND AND RECEIVE DATA ------
	int Send(char* Data, int *DataSent);			// Send string Data and store into DataSent how many bits are sent.
																// DataSend must contain Data string lenght
																// Data and DataSent must be allocated by user
	int Receive(char* Data, int *DataReceived);	// Receive string Data and store into DataReceived how many bits are received
																// Data and DataReceived must be allocated by user
																// If Data is not large enought, only message begining are stored into Data.
																// The last charactere are lost and Receive returns error code associated
private:
	HANDLE			hCom;			// Handle on file that permits to access on RS232 Port
	_COMMTIMEOUTS	TimeOut;		// This variable contain the delay of the time-out. 
	DCB				dcb;			// This object is use in order to configure the serial port.


};
// -----------------------------------------------------------------------------------------

// Constants definition
// Com Port Speed supported 
#define PORT_SPEED_9600				9600
#define PORT_SPEED_19200			19200
#define PORT_SPEED_38400			38400
#define PORT_SPEED_57600			57600
#define PORT_SPEED_115200			115200



#endif // OUFFF_RS232_H