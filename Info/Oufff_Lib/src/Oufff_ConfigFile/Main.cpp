/*******************************************************************************************
   File           :  Main.cpp
   Authors        :  Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  Main to test Oufff_ConfigFile class
   History        :
      2008_05_02 (Fifi_one)   : Initial Version

   Dependencies   :
      - None
/*******************************************************************************************/

#include <windows.h>
#include "Oufff_ConfigFile.h"

int main()
{
	int Value, sortie;
	char ValChar;
	char *temp;
	float tp1;

	Oufff_ConfigFile File;

	File.OpenFile("Test.txt");
	sortie = File.GetValue("Param", &Value);
	sortie = File.GetValue("Param2", &Value);
	sortie = File.GetValue("Para", &Value);

	sortie = File.GetValue("Param3", &ValChar);
	sortie = File.GetValue("char", &temp);
	sortie = File.GetValue("float", &tp1);

	return 0;
}