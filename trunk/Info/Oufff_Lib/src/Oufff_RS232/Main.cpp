/*******************************************************************************************
   File           :  Main.cpp
   Authors        :  Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  Main to test Oufff_RS232 class
   History        :
      2008_05_02 (Fifi_one)   : Initial Version

   Dependencies   :
      - Oufff_RS232
/*******************************************************************************************/

#include <windows.h>
#include "Oufff_RS232.h"

int main()
{
	char Buf[] = "@1234,4321,123#";
	int Nb = strlen(Buf);

	Oufff_RS232 TestPort;

	TestPort.OpenPort(1,PORT_SPEED_19200);
	Sleep(1000);
	TestPort.Send("@100,1000,123#", &Nb);
	Sleep(1000);
	TestPort.Send("@200,1000,123#", &Nb);
	Sleep(1000);
	TestPort.Send("@300,1000,123#", &Nb);
	Sleep(1000);
	TestPort.Send("@400,1000,123#", &Nb);
	Sleep(1000);
	TestPort.Send("@500,1000,123#", &Nb);
	Sleep(1000);
	TestPort.Send("@600,1000,123#", &Nb);
	Sleep(1000);
	TestPort.Send("@700,1000,123#", &Nb);
	Sleep(1000);
	TestPort.Send("@800,1000,123#", &Nb);
	Sleep(1000);
	TestPort.Send("@900,1000,123#", &Nb);


	return 0;
}