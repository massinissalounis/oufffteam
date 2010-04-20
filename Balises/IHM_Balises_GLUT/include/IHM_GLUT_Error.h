/*******************************************************************************************
   File           :  IHM_GLUT_Error.h
   Authors        :  Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  Errors used in project "IHM_BALISES_GLUT" 
   History        :
      2008_04_23 (Fifi_one)     : Initial version (C++ dev)

   Dependencies   :
      None
/*******************************************************************************************/

#ifndef IHM_GLUT_ERROR_H
#define IHM_GLUT_ERROR_H


#define	IHM_GLUT_NoError							   0		// No Errors

// During file decoding 
#define	IHM_GLUT_ERR_PATHNAME						10		// PathName is not correct
#define	IHM_GLUT_ERR_OPEN_FILE						11		// Unable to open file
#define	IHM_GLUT_ERR_ADD_OBJ_FROM_FILE			12		// Unable to read file



// OpenGL_Object Class --------------------------------------------------------------------- 
#define IHM_GLUT_ERR_NOTENOUGHTPARAM            100   // Function was called without all arguments


// RS232 Management ------------------------------------------------------------------------
#define IHM_GLUT_THREAD_INIT							200	// Thread is in a creating mode
#define IHM_GLUT_THREAD_RUNNING						201	// Thread is runnning
#define IHM_GLUT_THREAD_UNEXPECTED_ERR				202	// Thread has been terminated by unexpected error
#define IHM_GLUT_THREAD_TERMINATE					203	// Thread is in a terminating mode
#define IHM_GLUT_THREAD_ERR_RS232					203	// Unable to use RS232 port in thread

#endif // IHM_GLUT_ERROR_H