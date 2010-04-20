/*******************************************************************************************
      File           :  Oufff_LibError.cpp
      See details on :  Oufff_LibError.h
      Authors        :  Bashar      (baptiste.charmette@cpe.fr)
                        Fifi_one    (philippe.bechet@cpe.fr)
      Team           :  OUFFF TEAM
/*******************************************************************************************/

#include "Oufff_LibError.h"


#ifdef WIN32
// DLL Entry Point (Necessary for windows but not used here) 
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
   return TRUE;
}
#endif // WIN32


// Class Functions
error::error(int _code, const char* _context, const char* _message)
:code(_code)
{

   if(_context != NULL)
   {
      context = new char[strlen(_context)+1];
      strcpy(context, _context);
   }
   else
   {
      context=NULL;
   }
   if(_message != NULL)
   {
      message = new char[strlen(_message)+1];
      strcpy(message, _message);
   }
   else
   {
      message=NULL;
   }
}

error::error(const error &err)
:code(err.code)
{
   if(err.context != NULL)
   {
      context = new char[strlen(err.context)+1];
      strcpy(context, err.context);
   }
   else
   {
      context=NULL;
   }
   if(err.message != NULL)
   {
      message = new char[strlen(err.message)+1];
      strcpy(message, err.message);
   }
   else
   {
      message=NULL;
   }
}

error::~error()
{
   if(context != NULL)
      delete context;

   if(message != NULL)
      delete message;
}

