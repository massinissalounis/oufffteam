/*******************************************************************************************
   File           :  OpenGL_Object.h
   Authors        :  Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  Class to read and store objects in order to display its on screen  
   History        :
      2008_04_23 (Fifi_one)     : Initial version (C++ dev)

   Dependencies   :
      - OpenGL 
/*******************************************************************************************/

#ifndef OPENGL_OBJECT_H
#define OPENGL_OBJECT_H

// included files
#include <windows.h>
#include <glut.h>
#include <stdio.h>
#include <math.h>

#include "IHM_GLUT_Error.h"
#include "IHM_BALISES_Config.h"

// Structure definition ------------------------------------------------------------------------
typedef struct
{   
   int x;      
   int y;      
   int z;
}Coord3D;

typedef struct
{   
   float x;      
   float y;      
   float z;
}CoordVect;

typedef struct
{   
   int a;      
   int b;      
   int c;
}Rot3D;

typedef struct
{
   double R;
   double G;
   double B;
   double A;
}ColorRGB;

// Class definition ----------------------------------------------------------------------------
class OpenGL_Object
{
public:
   // Data :
   short Type;          // Store object type (None, line, triangle, square, cylinder, circle...)
   ColorRGB Color;      

   Coord3D Pt1;            // used by line, triangle, square, cylinder, circle
   Coord3D Pt2;            // used by line, triangle, square
   Coord3D Pt3;            // used by triangle, square
   Coord3D Pt4;            // used by triangle, square
   CoordVect NormalVect;   // Normal vector for surface
   int Radius;             // used by cylinder and circle
   int Height;             // used by cylinder

   OpenGL_Object *Next; // Pointer to the next object

   // Constructor
   OpenGL_Object();																															// Constructor : Empty object
   OpenGL_Object(short _Type, Coord3D *_Pt1);											
   OpenGL_Object(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, ColorRGB *_Color);											// Line Constructor
   OpenGL_Object(short _Type, Coord3D *_Pt1, int *_Radius, int *_Height, ColorRGB *_Color);							// Line Constructor
   OpenGL_Object(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, ColorRGB *_Color);						// Triangle Constructor
   OpenGL_Object(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, Coord3D *_Pt4, ColorRGB *_Color);   // Square Constructor

   // Destructor
   ~OpenGL_Object();    // Constructor : Delete all objects

   // Functions
   int LoadObjFromFile(char *FileName);																								// Allow to get objects from a specific file
	int AddObject(short _Type, Coord3D *_Pt1);											                                 // Add New object (object info) to the list
	int AddObject(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, ColorRGB *_Color);											// Add New object (Line) to the list
	int AddObject(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, ColorRGB *_Color);						// Add New object (Triangle) to the list
	int AddObject(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, Coord3D *_Pt4, ColorRGB *_Color);	// Add New object (Square) to the list

   int ComputeNormalVect();   // Compute Normal Vector if surf has been modifed
private:

   // Functions
   int SetObject(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, Coord3D *_Pt4, int *_Radius, int *_Height, ColorRGB *_Color);
      // Fill all fields of OpenGL object

   int AddObject(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, Coord3D *_Pt4, int *_Radius, int *_Height, ColorRGB *_Color);
		// Add object with all properties

	int InitObject();	// Function to init all data

   int VectProduct(CoordVect VectA, CoordVect VectB, CoordVect *VectOut);  // Compute vectorial product VectOut = VectA ^ VectB
};

#endif // OPENGL_OBJECT_H