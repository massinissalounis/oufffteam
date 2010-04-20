/*******************************************************************************************
   File           :  Oufff_ConfigFile.h
   Authors        :  Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  Class to manage File Configuration
   History        :
      2008_05_02 (Fifi_one)   : Initial Version

   Dependencies   :
      None
/*******************************************************************************************/


#ifndef OUFFF_CONFIGFILE_H
#define OUFFF_CONFIGFILE_H


// Globale Include
#include <windows.h>
#include <stdio.h>

// Specific include
#include "Oufff_LibErrorCode.h"
#include "Oufff_LibConfig.h"

// Class definition ------------------------------------------------------------------------
class Oufff_ConfigFile
{
public:
	// ---------- CONSTRUCTOR ----------
	Oufff_ConfigFile();					// Constructor must have as parameter the filename to open
	~Oufff_ConfigFile();					// Destructor

	// --------- OPEN / CLOSE ----------
	int OpenFile(char *FileName);		// Function to open the config file pointed by FileName
	int CloseFile();						// Function to close previously openned config file

	// ----------- ACCESSOR ------------
	int GetValue(const char *ParamName, int *ReturnValue);		// Function to read an integer from file
	int GetValue(const char *ParamName, char *ReturnValue);		// Function to read one char from file 
	int GetValue(const char *ParamName, char *ReturnValue[]);	// Function to read a char string from file. 
																					// WARNING : returned string must be deleted by user.
																					// Be careful, you must delete string by using "delete []"
	int GetValue(const char *ParamName, float *ReturnValue);		// Function to read a float from file


private:
	FILE *fd;		// File descriptor


	// Functions
	char* SearchParam(const char *ParamName);		// Search ParamName in File pointed by fd.
																// If ParamName is found, string value is returned, NULL otherwise
																// WARNING : returned string must be deleted by user

};




#endif // OUFFF_CONFIGFILE_H