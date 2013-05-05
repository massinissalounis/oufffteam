/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskDebug.c
*
* Suivi de version :
* 2013-02-17 | PBE | Creation de la version de base pour la coupe 2013
*********************************************************************************************************
*/

#include "TaskDebug.h"
#include "AppGlobalVars.h"

// Structures internes au module ------------------------------------------------------------------
typedef enum 
{
	unused		= 0,	// Message non utilisé
	typeInt		= 1,	// Message de type intéger
	typeFloat	= 2,	// Message de type float
	typeAngle	= 3,	// Message de type angle
	typeBool	= 4		// Message de type boolean
}EnumMsgType;

typedef struct 
{
	EnumMsgType	msgType;			
	char		description[13];	// 12 char pour info + 1 char de fin de chaine
	float		value;				// Permet de stocker les valeurs à afficher
}StructDebug;

// Données internes au modules de débug -----------------------------------------------------------
StructDebug _debugInfo[TASKDEBUG_MAX_MSG];
BOOLEAN IsDebugTaskRunning = OS_FALSE;

// ------------------------------------------------------------------------------------------------
void TaskDebug_Init()
{
	INT8U i = 0;

	// Init de tous les valeurs de mon tableau
	for(i=0; i<TASKDEBUG_MAX_MSG; i++)
	{
		_debugInfo[i].msgType = unused;
		strcpy(_debugInfo[i].description, "Not Used\0");
		_debugInfo[i].value = 0;
	}

	IsDebugTaskRunning = OS_TRUE;

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskDebug_RegisterNewData(int debugID, const char *debugDescription)
{
	INT8U i = 0;
	char outputBuffer[255];
	memset(outputBuffer, 0, sizeof(char) * 255);

	// Wait for the taskDebug is ok
	while(OS_FALSE == IsDebugTaskRunning)
	{
		OSTimeDlyHMSM(0, 0, 1, 0);
	}

	// Verification de l'indice pour l'enregistrement
	if((debugID >=0) && (debugID < TASKDEBUG_MAX_MSG))
	{
		// Verification si l'ID selectionné est valid
		if(_debugInfo[debugID].msgType == unused)
		{
			strcpy(_debugInfo[debugID].description, "                \0");	// On efface les données si elles n'ont pas été effacées
			strncpy(_debugInfo[debugID].description, debugDescription, 16);	// On copie au max 16 caractères
			_debugInfo[debugID].value = 0;									// On définit la valeur par défaut
			_debugInfo[debugID].msgType = typeInt;							// On définit un type par défaut

			sprintf(outputBuffer, "TaskDebug : Register new debug ID n°%i (%s)\n", debugID, debugDescription);
			AppDebugMsg(outputBuffer);
		}
		else
		{
			sprintf(outputBuffer, "TaskDebug (ERROR) : Unable to register debug ID n°%i (%s)\n", debugID, debugDescription);
			AppDebugMsg(outputBuffer);
		}
	}
	else
	{
		AppDebugMsg("TaskDebug (ERROR) : Invalid ID\n");
	}

	
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskDebug_UnregisterData(int debugID)
{
	INT8U i = 0;
	char outputBuffer[255];
	memset(outputBuffer, 0, sizeof(char) * 255);

	if(IsDebugTaskRunning == OS_FALSE)
		return;

	// Verification de l'indice pour l'enregistrement
	if((debugID >=0) && (debugID < TASKDEBUG_MAX_MSG))
	{
		sprintf(outputBuffer, "TaskDebug : Unregister debug ID n°%i (%s)\n", debugID, _debugInfo[i].description);

		// Desenregistrement
		_debugInfo[i].msgType = unused;
		strcpy(_debugInfo[i].description, "Not Used\0");
		_debugInfo[i].value = 0;

		AppDebugMsg(outputBuffer);
	}
	else
	{
		AppDebugMsg("TaskDebug (ERROR) : Invalid ID\n");
	}

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskDebug_UpdateValueInt(int debugID, int value)
{
	if(IsDebugTaskRunning == OS_FALSE)
		return;

	// Verification de l'indice 
	if((debugID >=0) && (debugID < TASKDEBUG_MAX_MSG))
	{
		if(_debugInfo[debugID].msgType != unused)
		{
			// Mise à jour
			_debugInfo[debugID].msgType = typeInt;
			_debugInfo[debugID].value = value * 1.0;
		}
	}

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskDebug_UpdateValueFloat(int debugID, float value)
{
	if(IsDebugTaskRunning == OS_FALSE)
		return;

	// Verification de l'indice 
	if((debugID >=0) && (debugID < TASKDEBUG_MAX_MSG))
	{
		if(_debugInfo[debugID].msgType != unused)
		{
			// Mise à jour
			_debugInfo[debugID].msgType = typeFloat;
			_debugInfo[debugID].value = value;
		}
	}

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskDebug_UpdateValueAngle(int debugID, float value)
{
	if(IsDebugTaskRunning == OS_FALSE)
		return;

	// Verification de l'indice 
	if((debugID >=0) && (debugID < TASKDEBUG_MAX_MSG))
	{
		if(_debugInfo[debugID].msgType != unused)
		{
			// Mise à jour
			_debugInfo[debugID].msgType = typeAngle;
			_debugInfo[debugID].value = value * 180.0 / M_PI;
		}
	}

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskDebug_UpdateValueBool(int debugID, BOOLEAN value)
{
	if(IsDebugTaskRunning == OS_FALSE)
		return;

	// Verification de l'indice 
	if((debugID >=0) && (debugID < TASKDEBUG_MAX_MSG))
	{
		if(_debugInfo[debugID].msgType != unused)
		{
			// Mise à jour
			_debugInfo[debugID].msgType = typeBool;
			if(value == 0)
				_debugInfo[debugID].value = 0.0;
			else
				_debugInfo[debugID].value = 1.0;
		}
	}

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskDebug_Main(void *p_arg)
{
	char uart_buffer[8];
	char *buffer_ptr;
	INT8U err		= ERR__NO_ERROR;
	int i			= 0;

	AppDebugMsg("OUFFF TEAM 2013 : Debug online\n");

	// Task Initialisation
	TaskDebug_Init();
	
	// All TaskDebug_RegisterNewData() must be set into Task_Main

#ifdef ODO_CALIBRATION
	while(OS_TRUE)		
	{
		OSTimeDlyHMSM(1, 0, 0, 0);
	}
#endif

	// Main Loop
	while(OS_TRUE)
	{
		#ifdef TASKDEBUG_ENABLED
			AppDebugMsg("TaskDebug : ");
			for(i=0; i<TASKDEBUG_MAX_MSG; i++)
			{
				// Verification si le message doit être diffusé
				if(_debugInfo[i].msgType != unused)
				{
					// Description
					AppDebugMsg(_debugInfo[i].description);
					AppDebugMsg(" = ");

					// Value
					switch(_debugInfo[i].msgType)
					{
					// ________________________________________________________________________
					case typeInt: 
						buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) _debugInfo[i].value, (CPU_INT08U) 4, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
						AppDebugMsg(buffer_ptr);
						break;

					// ________________________________________________________________________
					case typeFloat:  
						buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) _debugInfo[i].value, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
						AppDebugMsg(buffer_ptr);
						break;

					// ________________________________________________________________________
					case typeAngle:	 
						buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) _debugInfo[i].value, (CPU_INT08U) 3, (CPU_INT08U) 2, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
						AppDebugMsg(buffer_ptr);
						break;

					// ________________________________________________________________________
					case typeBool:  
						if(_debugInfo[i].value == 0.0)
							AppDebugMsg("True");
						else
							AppDebugMsg("False");
						break;

					// ________________________________________________________________________
					default: 
						AppDebugMsg("NC");
						break;
					}

					// Fin de la valeur
					AppDebugMsg("\t");
				}
			}

			// Fin du message
			AppDebugMsg("\n");

			// Attente avant le prochain message de debug	
			OSTimeDlyHMSM(0, 0, 0, TASKDEBUG_REFRESH_MS);
		#else
			// Attente infinie	
			OSTimeDlyHMSM(1, 0, 0, 0);
		#endif
	}
}
