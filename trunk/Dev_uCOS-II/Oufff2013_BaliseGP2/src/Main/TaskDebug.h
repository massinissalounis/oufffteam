/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : TaskDebug.h
*********************************************************************************************************
*/

#ifndef TASKDEBUG_H
#define TASKDEBUG_H

#include "AppIncludes.h"

// fonctions publiques ----------------------------------------------------------------------------
void TaskDebug_RegisterNewData(int debugID, const char *debugDescription);
	// Fonction pour enregistrer une nouvelle variable pour le debug
	// int debugID						: ID pour le debug entre 0 et (TASKDEBUG_MAX_MSG - 1)
	// const char *debugDescription		: Message à afficher pour cette variable
	// Note : si jamais l'ID selectionné est déjà utilisé, la valeur de debugDescription n'est pas mis à jour

void TaskDebug_UnregisterData(int debugID);
	// Fonction pour desenregistrer la variable de debug
	// int debugID						: ID pour le debug qu'il faut libéré entre 0 et (TASKDEBUG_MAX_MSG - 1)

void TaskDebug_UpdateValueInt(int debugID, int value);
	// Fonction pour mettre à jour la valeur associée à debugID. Ne fait rien si debugID n'a pas été enregistrée.
	// int debugID						: ID qu'il faut mettre à jour
	// int value						: Valeur int à mettre à jour

void TaskDebug_UpdateValueFloat(int debugID, float value);
	// Fonction pour mettre à jour la valeur associée à debugID. Ne fait rien si debugID n'a pas été enregistrée.
	// int debugID						: ID qu'il faut mettre à jour
	// float value						: Valeur float à mettre à jour

void TaskDebug_UpdateValueAngle(int debugID, float value);
	// Fonction pour mettre à jour la valeur associée à debugID. Ne fait rien si debugID n'a pas été enregistrée.
	// int debugID						: ID qu'il faut mettre à jour
	// float value						: Valeur en radian à mettre à jour (conversion en degré au moment de l'affichage)

void TaskDebug_UpdateValueBool(int debugID, BOOLEAN value);
	// Fonction pour mettre à jour la valeur associée à debugID. Ne fait rien si debugID n'a pas été enregistrée.
	// int debugID						: ID qu'il faut mettre à jour
	// BOOLEAN value					: Valeur boolean à mettre à jour 

void TaskDebug_Main(void *p_arg);
	// Fonction principal du process de Debug
	// void *p_arg		: Arg for this task

#endif // TASKDEBUG_H
