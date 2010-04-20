/*******************************************************************************************
	File		:	Oufff_LibMatrice.h
	Authors		: 	Bashar		(baptiste.charmette@cpe.fr)
					Fifi_one	(philippe.bechet@cpe.fr)
	Team		: 	OUFFF TEAM
	Description	:	Dynamic Library to manage all OufffTeam generic errors
	History		:
		2008_03_04 (Fifi_one)	: DLL version 1.0
		2008_02_27 (Bashar)		: Initial version (C dev)
/*******************************************************************************************/

// Specific declarations

#ifdef WIN32		// Target = Windows
	//windows libraries
	#include <windows.h>

	// DLL Declaration
	#ifdef OUFFF_DLL_EXPORTS
	#define OUFFF_API_DLL __declspec(dllexport)
	#else
	#define OUFFF_API_DLL __declspec(dllimport)
	#endif
#else				// Target = Linux
	#define OUFFF_API_DLL 
#endif


// Common declarations
#ifndef OUFFF_LIBMATRICE_H
#define OUFFF_LIBMATRICE_H

//global libraries
#include <iostream>
#include <string>
#include <stdlib.h>

//personnal libraries
#include "error.h"


// Variables Declarations

OUFFF_API_DLL typedef double val_matrix;	//define the used type in matrix

using namespace std;

#endif // OUFFF_LIBMATRICE_H