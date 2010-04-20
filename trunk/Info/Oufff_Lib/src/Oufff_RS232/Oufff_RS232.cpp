/*******************************************************************************************
      File           :  Oufff_RS232.cpp
      See details on :  Oufff_RS232.h
      Authors        :  Fifi_one    (philippe.bechet@cpe.fr)
      Team           :  OUFFF TEAM
/*******************************************************************************************/

#include "Oufff_RS232.h"

// -----------------------------------------------------------------------------------------
Oufff_RS232::Oufff_RS232()
{
	// Initialisation 
	hCom = NULL;
}


// -----------------------------------------------------------------------------------------
Oufff_RS232::~Oufff_RS232()
{
	ClosePort();
}

// -----------------------------------------------------------------------------------------
int Oufff_RS232::OpenPort(int NumPort, int SpeedPort)
{
	char Buffer[5];

	if((NumPort < 1) || (NumPort > 100))
	{
		return OUFFF_LIB_RS232_INVALID_PARAM;
	}


	if(	(PORT_SPEED_9600 != SpeedPort)
		&&	(PORT_SPEED_19200 != SpeedPort)
		&&	(PORT_SPEED_38400 != SpeedPort)
		&&	(PORT_SPEED_57600 != SpeedPort)
		&&	(PORT_SPEED_115200 != SpeedPort))
	{
		return OUFFF_LIB_RS232_INVALID_PARAM;
	}

	// Name port creation
	sprintf(Buffer, "COM%d\0", NumPort);

	// Openning port
	hCom = CreateFile(Buffer, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING , FILE_FLAG_NO_BUFFERING, 0);

   // Flush Buffer
   FlushFileBuffers(hCom);

	if((NULL == hCom) || (INVALID_HANDLE_VALUE == hCom))
	{
		return OUFFF_LIB_RS232_UNABLE_OPEN_PORT;
	}

	// Set Port Timeout
	SetPortTimeOut(100);
	SetPortSpeed(SpeedPort);

	//Set Port Buffer Size
	if ( !SetupComm(hCom, 8192, 8192) ) 
	{
	    return OUFFF_LIB_RS232_UNABLE_SET_CONFIG;
	}

	// Read Port Config
   if( !GetCommState(hCom, &dcb))
	{
	    return OUFFF_LIB_RS232_UNABLE_READ_CONFIG;
	}

	// Set port config
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;

	if (!SetCommState(hCom, &dcb))
	{
		return OUFFF_LIB_RS232_UNABLE_SET_CONFIG;
	}

	return OUFFF_LIB_NOERR;
}

// -----------------------------------------------------------------------------------------
int Oufff_RS232::SetPortTimeOut(DWORD Delay)
{
	if(Delay<0)
		return false;

	TimeOut.ReadIntervalTimeout = 0;
	TimeOut.ReadTotalTimeoutMultiplier = 0;
	TimeOut.ReadTotalTimeoutConstant = Delay;
	TimeOut.WriteTotalTimeoutMultiplier = 0;
	TimeOut.WriteTotalTimeoutConstant = Delay;
	if(false == SetCommTimeouts(hCom, &TimeOut) )      // TimeOut config
	{
		return OUFFF_LIB_RS232_UNABLE_SET_CONFIG;
	}

	return OUFFF_LIB_NOERR;
}


// -----------------------------------------------------------------------------------------
int Oufff_RS232::SetPortSpeed(DWORD SpeedPort)
{
	if(	(PORT_SPEED_9600 != SpeedPort)
		&&	(PORT_SPEED_19200 != SpeedPort)
		&&	(PORT_SPEED_38400 != SpeedPort)
		&&	(PORT_SPEED_57600 != SpeedPort)
		&&	(PORT_SPEED_115200 != SpeedPort))
	{
		return OUFFF_LIB_RS232_INVALID_PARAM;
	}


	if (!GetCommState(hCom, &dcb))
	{
		return OUFFF_LIB_RS232_UNABLE_READ_CONFIG;
	}

	dcb.BaudRate = SpeedPort;

	if (!SetCommState(hCom, &dcb))
	{
		return OUFFF_LIB_RS232_UNABLE_SET_CONFIG;
	}

	return OUFFF_LIB_NOERR;
}

// -----------------------------------------------------------------------------------------
int Oufff_RS232::ClosePort()
{
	if(0 == CloseHandle(hCom))
	{
		return OUFFF_LIB_RS232_UNABLE_CLOSE_PORT;
	}

	hCom = NULL;
	
	return OUFFF_LIB_NOERR;
}

// -----------------------------------------------------------------------------------------
int Oufff_RS232::Send(char* Data, int *DataSent)
{

	int LenghtToSend = 0;
	DWORD LenghtSent = 0;

	// Checking input param
	if((NULL == Data) || (NULL == DataSent) || (NULL == hCom))
	{
		return OUFFF_LIB_RS232_INVALID_PARAM;
	}

	// Checking string length
	if((int)strlen(Data) < *DataSent)
	{
		LenghtToSend = strlen(Data);
	}
	else
	{
		LenghtToSend = *DataSent;
	}

	if(LenghtToSend < 1)
	{
		return OUFFF_LIB_RS232_INVALID_PARAM;
	}
	
	// Send Data
	if (WriteFile(hCom, Data, LenghtToSend, &LenghtSent, 0) == false)
	{
		return OUFFF_LIB_RS232_ERR_SEND;
	}
	else
	{
		*DataSent = (int)(LenghtSent);
	}

	return OUFFF_LIB_NOERR;
}

// -----------------------------------------------------------------------------------------
int Oufff_RS232::Receive(char* Data, int *DataReceived)
{
	DWORD LenghtRead = 0;
	*DataReceived = 0;

	// Checking param
	if((NULL == Data) || (NULL == DataReceived))
	{
		return OUFFF_LIB_RS232_INVALID_PARAM;
	}

	// Clear Data string
	memset(Data, '\0', strlen(Data));

	do
	{
		if (ReadFile(hCom, Data, 1024, &LenghtRead, 0) == false)
		{
			return OUFFF_LIB_RS232_ERR_RCV;
		}

		*DataReceived += (int)LenghtRead;
	}while(0 != (int)LenghtRead);

	return OUFFF_LIB_NOERR;
}