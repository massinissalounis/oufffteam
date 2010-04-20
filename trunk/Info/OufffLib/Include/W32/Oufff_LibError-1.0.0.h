/*******************************************************************************************
   File           :  Oufff_LibError.h
   Authors        :  Bashar         (baptiste.charmette@cpe.fr)
                     Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  Dynamic Library to manage all OufffTeam generic errors
   History        :
      2008_03_04 (Fifi_one)   : DLL version 1.0
      2008_02_27 (Bashar)     : Initial version (C++ dev)

   Dependencies   :
      None
/*******************************************************************************************/

// Specific declarations


#ifdef WIN32   // Target = Windows
   //windows libraries
   #include <windows.h>
   
   // DLL Declaration
   #ifdef OUFFF_DLL_EXPORTS
      #define OUFFF_API_DLL __declspec(dllexport)
   #else
      #define OUFFF_API_DLL __declspec(dllimport)
   #endif // OUFFF_DLL_EXPORTS
#else // Target = Linux
   #define OUFFF_API_DLL
#endif


// Common declarations
#ifndef OUFFF_LIBERROR_H
#define OUFFF_LIBERROR_H

//global libraries
#include <iostream>
#include <string>
#include <stdlib.h>

//personnal libraries



// ********** Constants Definitions ********** //
// General Errors
#define OUFFF_ERROR_UNKNOWN            -1    //error unknown (default value)
#define OUFFF_ERROR_OUTOFTABLE         1     //try to access out of a table (segmentation fault)
#define OUFFF_ERROR_ALLOCATION         2     //error in allocation (new return NULL)
#define OUFFF_ERROR_INVALIDVALUE       3     //value is invalid


// LibMatrix Errors
#define OUFFF_ERROR_DIMENSIONDISAGREE     100   //try to use matrix operator with bad dimension
#define OUFFF_ERROR_MATHS                 101   //mathematical error such as division by 0
#define OUFFF_ERROR_MATRIXNOTSQUARE       102   //matrix is not square 

// ********** End of Definitions ********** //


// *********** Class Definition *********** //
class OUFFF_API_DLL error
{
public:
   error(int _code=-1, const char* _context=NULL, const char* _message=NULL);
   error(const error& err);
   ~error();

public:
   int code;
   char* message;
   char* context;
};

#endif

