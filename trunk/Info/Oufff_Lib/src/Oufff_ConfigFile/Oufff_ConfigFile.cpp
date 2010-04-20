/*******************************************************************************************
      File           :  Oufff_ConfigFile.cpp
      See details on :  Oufff_ConfigFile.h
      Authors        :  Fifi_one    (philippe.bechet@cpe.fr)
      Team           :  OUFFF TEAM
/*******************************************************************************************/

#include "Oufff_ConfigFile.h"

// -----------------------------------------------------------------------------------------
Oufff_ConfigFile::Oufff_ConfigFile()
{
	// Initialisation 
	fd = NULL;
}


// -----------------------------------------------------------------------------------------
Oufff_ConfigFile::~Oufff_ConfigFile()
{
	CloseFile();
}

// -----------------------------------------------------------------------------------------
int Oufff_ConfigFile::OpenFile(char *FileName)
{
	if(NULL == FileName)
	{
		return OUFFF_LIB_CONFIGFILE_INVALID_PARAM;
	}

	// Step 1 : Open given file
	fd = fopen(FileName, "r");

	if(NULL == fd)
	{
		return OUFFF_LIB_CONFIGFILE_UNABLE_OPEN_FILE;
	}

	return OUFFF_LIB_NOERR;
}

// -----------------------------------------------------------------------------------------
int Oufff_ConfigFile::CloseFile()
{
	if(NULL != fd)
	{
		if(0 != fclose(fd))
		{
			return OUFFF_LIB_CONFIGFILE_UNABLE_CLOSE_FILE;
		}
		fd = NULL;
	}

	return OUFFF_LIB_NOERR;
}

// -----------------------------------------------------------------------------------------
int Oufff_ConfigFile::GetValue(const char *ParamName, int *ReturnValue)
{
	char *ReadLine = NULL;
	char *PatternString = new char[1024];
	int ReadValue = 0;

	// Search line into file
	ReadLine = SearchParam(ParamName);

	// ParamName has not been found in config file
	if(NULL == ReadLine)
	{
		return OUFFF_LIB_CONFIGFILE_PARAM_NOT_FOUND;
	}

	// Pattern string creation
	memset(PatternString, '\0', 1024);
	memcpy(PatternString, ParamName, strlen(ParamName));
	PatternString = strcat(PatternString, " = %d\0");

	// ParamName has been found in file
	if(1 != sscanf(ReadLine, PatternString, &ReadValue))
	{
		if(NULL != PatternString)		{		delete [] PatternString;	PatternString = NULL;	}
		if(NULL != ReadLine)				{		delete ReadLine;				ReadLine = NULL;			}
		return OUFFF_LIB_CONFIGFILE_PARAM_NOT_FOUND;
	}

	*ReturnValue = ReadValue;

	if(NULL != PatternString)			{		delete [] PatternString;	PatternString = NULL;	}
	if(NULL != ReadLine)					{		delete ReadLine;				ReadLine = NULL;			}

	return OUFFF_LIB_NOERR;
}


// -----------------------------------------------------------------------------------------
int Oufff_ConfigFile::GetValue(const char *ParamName, char *ReturnValue)
{
	char *ReadLine = NULL;
	char *PatternString = new char[1024];
	char ReadValue;

	ReturnValue = '\0';

	if((NULL == ParamName) || (NULL == ReturnValue))
	{
		return OUFFF_LIB_CONFIGFILE_INVALID_PARAM;
	}

	// Search line into file
	ReadLine = SearchParam(ParamName);
	
	// ParamName has not been found in config file
	if(NULL == ReadLine)
	{
		return OUFFF_LIB_CONFIGFILE_PARAM_NOT_FOUND;
	}

	// Pattern string creation
	memset(PatternString, '\0', 1024);
	memcpy(PatternString, ParamName, strlen(ParamName));
	PatternString = strcat(PatternString, " = %c\0");

	// ParamName has been found in file
	if(1 != sscanf(ReadLine, PatternString, &ReadValue))
	{
		if(NULL != PatternString)		{		delete [] PatternString;	PatternString = NULL;	}
		if(NULL != ReadLine)				{		delete ReadLine;				ReadLine = NULL;			}
		return OUFFF_LIB_CONFIGFILE_PARAM_NOT_FOUND;
	}

	*ReturnValue = ReadValue;

	if(NULL != PatternString)			{		delete [] PatternString;	PatternString = NULL;	}
	if(NULL != ReadLine)					{		delete ReadLine;				ReadLine = NULL;			}

	return OUFFF_LIB_NOERR;
}

// -----------------------------------------------------------------------------------------
int Oufff_ConfigFile::GetValue(const char *ParamName, char *ReturnValue[])
{
	char *ReadLine = NULL;
	char *PatternString = new char[1024];
	char ReadValue[1024];
	int StringLen = 0;

	if((NULL == ParamName) || (NULL == ReturnValue))
	{
		*ReturnValue = NULL;
		return OUFFF_LIB_CONFIGFILE_INVALID_PARAM;
	}

	// Search line into file
	ReadLine = SearchParam(ParamName);
	
	// ParamName has not been found in config file
	if(NULL == ReadLine)
	{
		*ReturnValue = NULL;
		return OUFFF_LIB_CONFIGFILE_PARAM_NOT_FOUND;
	}

	// Pattern string creation
	memset(PatternString, '\0', 1024);
	memcpy(PatternString, ParamName, strlen(ParamName));
	PatternString = strcat(PatternString, " = %s\0");

	// ParamName has been found in file
	if(1 != sscanf(ReadLine, PatternString, &ReadValue))
	{
		*ReturnValue = NULL;
		if(NULL != PatternString)		{		delete [] PatternString;	PatternString = NULL;	}
		if(NULL != ReadLine)				{		delete ReadLine;				ReadLine = NULL;			}
		return OUFFF_LIB_CONFIGFILE_PARAM_NOT_FOUND;
	}

	// Value found is correct, I copy it into ReturnValue[]
	StringLen = strlen(ReadValue);
	*ReturnValue = new char[StringLen+1];
	memset(*ReturnValue, '\0', StringLen+1);
	memcpy(*ReturnValue, ReadValue, StringLen);

	// Delete temp variables
	if(NULL != PatternString)			{		delete [] PatternString;	PatternString = NULL;	}
	if(NULL != ReadLine)					{		delete ReadLine;				ReadLine = NULL;			}

	return OUFFF_LIB_NOERR;
}

// -----------------------------------------------------------------------------------------
int Oufff_ConfigFile::GetValue(const char *ParamName, float *ReturnValue)
{
	char *ReadLine = NULL;
	char *PatternString = new char[1024];
	float ReadValue;

	if((NULL == ParamName) || (NULL == ReturnValue))
	{
		return OUFFF_LIB_CONFIGFILE_INVALID_PARAM;
	}

	// Search line into file
	ReadLine = SearchParam(ParamName);
	
	// ParamName has not been found in config file
	if(NULL == ReadLine)
	{
		return OUFFF_LIB_CONFIGFILE_PARAM_NOT_FOUND;
	}

	// Pattern string creation
	memset(PatternString, '\0', 1024);
	memcpy(PatternString, ParamName, strlen(ParamName));
	PatternString = strcat(PatternString, " = %f\0");

	// ParamName has been found in file
	if(1 != sscanf(ReadLine, PatternString, &ReadValue))
	{
		if(NULL != PatternString)		{		delete [] PatternString;	PatternString = NULL;	}
		if(NULL != ReadLine)				{		delete ReadLine;				ReadLine = NULL;			}
		return OUFFF_LIB_CONFIGFILE_PARAM_NOT_FOUND;
	}

	*ReturnValue = ReadValue;
	
	// Delete temp variables
	if(NULL != PatternString)			{		delete [] PatternString;	PatternString = NULL;	}
	if(NULL != ReadLine)					{		delete ReadLine;				ReadLine = NULL;			}

	return OUFFF_LIB_NOERR;
}


// ##########################################################################################
// Private functions
// ##########################################################################################

char* Oufff_ConfigFile::SearchParam(const char *ParamName)
{
	char Buff[1024];
	char *SearchString1 = new char[512];
	char *SearchString2 = new char[512];
	char *ReturnValue = NULL;

	// Check input params
	if((NULL == fd) || (NULL == ParamName))
	{
		return NULL;
	}

	// Make pattern strings
	memset(SearchString1, 0, 512);
	memcpy(SearchString1, ParamName, strlen(ParamName));
	SearchString1 = strcat(SearchString1, " =");

	memset(SearchString2, 0, 512);
	memcpy(SearchString2, ParamName, strlen(ParamName));
	SearchString2 = strcat(SearchString2, "=");

	// Place file cursor to the beginning of the config file
	fseek(fd, 0, SEEK_SET);

	// Read each line
   while(NULL != fgets(Buff, 256, fd))
	{
		// Looking for ParamName
		if((NULL != strstr(Buff, SearchString1)) || (NULL != strstr(Buff, SearchString2)))
		{
			// ParamName has been found
			// I create string which will be returned
			if(NULL != ReturnValue)
			{
				delete ReturnValue;
				ReturnValue = NULL;
			}

			ReturnValue = new char[1024];
			strcpy(ReturnValue, Buff);
		}
	}


	return ReturnValue;
}