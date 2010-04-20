/*******************************************************************************************
      File           :  OpenGL_Object.cpp
      See details on :  OpenGL_Object.h
      Authors        :  Fifi_one    (philippe.bechet@cpe.fr)
      Team           :  OUFFF TEAM
/*******************************************************************************************/

#include "OpenGL_Object.h"

// ------------------------------------------------------------------------------------------
OpenGL_Object::OpenGL_Object()
{
	InitObject();

   // Object Init (Empty object)
   SetObject(OPENGL_OBJECT_NONE, NULL, NULL, NULL, NULL, NULL, NULL,NULL);
   Next = NULL;
}

// ------------------------------------------------------------------------------------------
OpenGL_Object::OpenGL_Object(short _Type, Coord3D *_Pt1)
{
	InitObject();

   // It is necessary to check if all param are set. If not, we do not create object
   if(	(OPENGL_OBJECT_NONE != _Type)
      && (NULL != _Pt1)
      )
   {
      SetObject(_Type, _Pt1, NULL, NULL, NULL, NULL, NULL, NULL);
   }
   else
   {
      SetObject(OPENGL_OBJECT_NONE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   }
}


// ------------------------------------------------------------------------------------------
OpenGL_Object::OpenGL_Object(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, ColorRGB *_Color)
{
	InitObject();

   // It is necessary to check if all param are set. If not, we do not create object
   if(	(OPENGL_OBJECT_LINE == _Type)
      && (NULL != _Pt1)
      && (NULL != _Pt2)
      && (NULL != _Color)
      )
   {
      SetObject(_Type, _Pt1, _Pt2, NULL, NULL, NULL, NULL, _Color);
   }
   else
   {
      SetObject(OPENGL_OBJECT_NONE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   }
}

// ------------------------------------------------------------------------------------------
OpenGL_Object::OpenGL_Object(short _Type, Coord3D *_Pt1, int *_Radius, int *_Height, ColorRGB *_Color)
{
	InitObject();

   // It is necessary to check if all param are set. If not, we do not create object
   if(	(OPENGL_OBJECT_CYLINDER == _Type)
      && (NULL != _Pt1)
      && (NULL != _Radius)
      && (NULL != _Height)
      && (NULL != _Color)
      )
   {
      SetObject(_Type, _Pt1, NULL, NULL, NULL, _Radius, _Height, _Color);
   }
   else
   {
      SetObject(OPENGL_OBJECT_NONE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   }

}

// ------------------------------------------------------------------------------------------
OpenGL_Object::OpenGL_Object(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, ColorRGB *_Color)
{

	InitObject();

   // It is necessary to check if all param are set. If not, we do not create object
   if(   (OPENGL_OBJECT_TRIANGLE == _Type)
      && (NULL != _Pt1)
      && (NULL != _Pt2)
      && (NULL != _Pt3)
      && (NULL != _Color)
      )
   {
      SetObject(_Type, _Pt1, _Pt2, _Pt3, NULL, NULL, NULL, _Color);
      ComputeNormalVect();
   }
   else
   {
      SetObject(OPENGL_OBJECT_NONE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   }

}

// ------------------------------------------------------------------------------------------
OpenGL_Object::OpenGL_Object(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, Coord3D *_Pt4, ColorRGB *_Color)
{

   InitObject();

   // It is necessary to check if all param are set. If not, we do not create object
   if(   (OPENGL_OBJECT_SQUARE == _Type)
      && (NULL != _Pt1)
      && (NULL != _Pt2)
      && (NULL != _Pt3)
      && (NULL != _Pt4)
      && (NULL != _Color)
      )
   {
      SetObject(_Type, _Pt1, _Pt2, _Pt3, _Pt4, NULL, NULL, _Color);
      ComputeNormalVect();
   }
   else
   {
      SetObject(OPENGL_OBJECT_NONE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   }

}

// ------------------------------------------------------------------------------------------
OpenGL_Object::~OpenGL_Object()
{
   // It's necessary to delete current object
   if(NULL != Next)
   {
      delete Next;   // The next object is delete
      Next = NULL;
   }

   // Nothing more must be done
}

// ------------------------------------------------------------------------------------------
int OpenGL_Object::LoadObjFromFile(char *FileName)
{
   FILE *FilePtr = NULL;
   char buf[256];
   bool Done = FALSE;
   short CurrentPoint = 0;
   short ObjType = OPENGL_OBJECT_NONE;
   int ReadValue1, ReadValue2, ReadValue3;	   // Var to get informations from file
	int *PtrRadius = NULL;							   // Var to store temp informations
	int *PtrHeight = NULL;							   // Var to store temp informations
   int ObjectHeight = 0;                        // Height of object (only for 3D object)
   int TmpRadius, TmpHeight;
   Coord3D TmpPt1, TmpPt2, TmpPt3, TmpPt4;	   // Var to store temp informations 
   Coord3D TmpPt5, TmpPt6, TmpPt7, TmpPt8;	   // Var to store temp informations (for 3D object) 
   Coord3D *PtrPt1 = NULL;		   				   // Pointer used to send or not data so SetObject function
   Coord3D *PtrPt2 = NULL;							   // Pointer used to send or not data so SetObject function
	Coord3D *PtrPt3 = NULL;							   // Pointer used to send or not data so SetObject function
	Coord3D *PtrPt4 = NULL;							   // Pointer used to send or not data so SetObject function
   ColorRGB TmpColor;

   if(NULL == FileName)
   {
      // Pathname is not valid
      return IHM_GLUT_ERR_PATHNAME;
   }

   // First I open the file pointed by FileName
   FilePtr = fopen(FileName, "r");
   if(NULL == FilePtr)
   {
      // Unable to open file
      return IHM_GLUT_ERR_OPEN_FILE;
   }


   // I read all the file
   while(NULL != fgets(buf, 256, FilePtr))
   {
      if(NULL == strstr(buf, "//")) // I don't read comment lines
      {
			// Pointer Init
			ObjType = OPENGL_OBJECT_NONE;
			TmpRadius = NULL;
			TmpHeight = NULL;							
			PtrPt1 = NULL;
			PtrPt2 = NULL;
			PtrPt3 = NULL;
			PtrPt4 = NULL;
         ObjectHeight = 0;


         // Case LINE *************************************************************************
         if(NULL != strstr(buf, "LINE"))
         {
            // I save object type before reading other data
            ObjType = OPENGL_OBJECT_LINE;

            // The object found is a LINE or a SQUARE, I read object color:
            if(sscanf(buf, "LINE %d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) == 3) 
            {
               // I save obj color found
               TmpColor.R = (double)ReadValue1/255;      TmpColor.G = (double)ReadValue2/255;   TmpColor.B = (double)ReadValue3/255;
            }
            else
            {
               // I have not found a correct object color, I use the default one...
               TmpColor.R = 1.0;             TmpColor.G = 1.0;          TmpColor.B = 1.0;
            }

            // Then I read point coord
            CurrentPoint = 0;
            Done = FALSE;
            PtrPt1 = NULL;		PtrPt2 = NULL;		PtrPt3 = NULL;    PtrPt4 = NULL;  

            do
            {
               if(NULL != fgets(buf, 256, FilePtr))   // I read a line from the opened file
               {
                  if(sscanf(buf, "%d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) == 3)   // I get data
                  {
                     switch(CurrentPoint) // I store data into temporary object structure
                     {
                     case 0:  TmpPt1.x = ReadValue1;    TmpPt1.y = ReadValue2;    TmpPt1.z = ReadValue3;    PtrPt1 = &TmpPt1;		break;
                     case 1:  TmpPt2.x = ReadValue1;    TmpPt2.y = ReadValue2;    TmpPt2.z = ReadValue3;    PtrPt2 = &TmpPt2;		Done = TRUE;   break;
                     default: break;
                     }

                     CurrentPoint++;
                  }

               }
            }while(FALSE == Done);
         }

         // Case TRIANGLE *************************************************************
         if(NULL != strstr(buf, "TRIANGLE")) 
         {
            // I save object type before reading other data
            if(NULL != strstr(buf, "TRIANGLE")) { ObjType = OPENGL_OBJECT_TRIANGLE; }

            // The object found is a TRIANGLE, I read object color:
            if(sscanf(buf, "TRIANGLE %d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) == 3)
            {
               // I save color found
               TmpColor.R = (double)ReadValue1/255;      TmpColor.G = (double)ReadValue2/255;      TmpColor.B = (double)ReadValue3/255;
            }
            else
            {
               // I have not found a correct object color, I use the default one...
               TmpColor.R = 1.0;             TmpColor.G = 1.0;             TmpColor.B = 1.0;
            }

            // Then I read point coord
            CurrentPoint = 0;
            Done = FALSE;
            PtrPt1 = NULL;		PtrPt2 = NULL;		PtrPt3 = NULL;    PtrPt4 = NULL;     

            do
            {
               if(NULL != fgets(buf, 256, FilePtr))   // I read a line from the opened file
               {
                  if(sscanf(buf, "%d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) == 3)   // I get data
                  {
                     switch(CurrentPoint) // I store data into object structure
                     {
                     case 0:  TmpPt1.x = ReadValue1;    TmpPt1.y = ReadValue2;    TmpPt1.z = ReadValue3;    PtrPt1 = &TmpPt1;    break;
                     case 1:  TmpPt2.x = ReadValue1;    TmpPt2.y = ReadValue2;    TmpPt2.z = ReadValue3;    PtrPt2 = &TmpPt2;    break;
                     case 2:  TmpPt3.x = ReadValue1;    TmpPt3.y = ReadValue2;    TmpPt3.z = ReadValue3;    PtrPt3 = &TmpPt3;    Done = TRUE;   break;
                     default: break;
                     }

                     CurrentPoint++;
                  }

               }
            }while(FALSE == Done);
			}

         
			// Case SQUARE_2D  *************************************************************
         if(NULL != strstr(buf, "SQUARE_2D")) 
         {
            // I save object type before reading other data
            ObjType = OPENGL_OBJECT_SQUARE;

            // The object found is a TRIANGLE, I read object color:
            if(sscanf(buf, "SQUARE_2D %d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) == 3)
            {
               // I save color found
               TmpColor.R = (double)ReadValue1/255;      TmpColor.G = (double)ReadValue2/255;      TmpColor.B = (double)ReadValue3/255;
            }
            else
            {
               // I have not found a correct object color, I use the default one...
               TmpColor.R = 1.0;             TmpColor.G = 1.0;             TmpColor.B = 1.0;
            }

            // Then I read point coord
            CurrentPoint = 0;
            Done = FALSE;
            PtrPt1 = NULL;		PtrPt2 = NULL;		PtrPt3 = NULL;    PtrPt4 = NULL;    

            do
            {
               if(NULL != fgets(buf, 256, FilePtr))   // I read a line from the opened file
               {
                  if(sscanf(buf, "%d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) == 3)   // I get data
                  {
                     switch(CurrentPoint) // I store data into object structure
                     {
                     case 0:  TmpPt1.x = ReadValue1;    TmpPt1.y = ReadValue2;    TmpPt1.z = ReadValue3;    PtrPt1 = &TmpPt1;    break;
                     case 1:  TmpPt2.x = ReadValue1;    TmpPt2.y = ReadValue2;    TmpPt2.z = ReadValue3;    PtrPt2 = &TmpPt2;    break;
                     case 2:  TmpPt3.x = ReadValue1;    TmpPt3.y = ReadValue2;    TmpPt3.z = ReadValue3;    PtrPt3 = &TmpPt3;    break;
                     case 3:  TmpPt4.x = ReadValue1;    TmpPt4.y = ReadValue2;    TmpPt4.z = ReadValue3;    PtrPt4 = &TmpPt4;    Done = TRUE;   break;
                     default: break;
                     }

                     CurrentPoint++;
                  }

               }
            }while(FALSE == Done);
			}

			// Case SQUARE_3D  *************************************************************
         if(NULL != strstr(buf, "SQUARE_3D")) 
         {
            // I save object type before reading other data
            ObjType = OPENGL_OBJECT_SQUARE;

            // The object found is a TRIANGLE, I read object color:
            if(sscanf(buf, "SQUARE_3D %d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) == 3)
            {
               // I save color found
               TmpColor.R = (double)ReadValue1/255;      TmpColor.G = (double)ReadValue2/255;      TmpColor.B = (double)ReadValue3/255;
            }
            else
            {
               // I have not found a correct object color, I use the default one...
               TmpColor.R = 1.0;             TmpColor.G = 1.0;             TmpColor.B = 1.0;
            }

            // Then I read point coord
            CurrentPoint = 0;
            Done = FALSE;
            PtrPt1 = NULL;		PtrPt2 = NULL;		PtrPt3 = NULL;    PtrPt4 = NULL;     

            do
            {
               if(NULL != fgets(buf, 256, FilePtr))   // I read a line from the opened file
               {
                  if(sscanf(buf, "%d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) == 3)   // I get data
                  {
                     switch(CurrentPoint) // I store data into object structure
                     {
                     case 0:  TmpPt1.x = ReadValue1;    TmpPt1.y = ReadValue2;    TmpPt1.z = ReadValue3;    PtrPt1 = &TmpPt1;    break;
                     case 1:  TmpPt2.x = ReadValue1;    TmpPt2.y = ReadValue2;    TmpPt2.z = ReadValue3;    PtrPt2 = &TmpPt2;    break;
                     case 2:  TmpPt3.x = ReadValue1;    TmpPt3.y = ReadValue2;    TmpPt3.z = ReadValue3;    PtrPt3 = &TmpPt3;    break;
                     case 3:  TmpPt4.x = ReadValue1;    TmpPt4.y = ReadValue2;    TmpPt4.z = ReadValue3;    PtrPt4 = &TmpPt4;    Done = TRUE;   break;
                     default: break;
                     }

                     CurrentPoint++;
                  }
               }
            }while(FALSE == Done);

            // Read 3D object Height
            if(NULL != fgets(buf, 256, FilePtr))   // I read a line from the opened file
            {
               if(sscanf(buf, "%d", &ObjectHeight) < 1) 
               {
                  ObjectHeight = 0;
               }
            }
			}

			// Case CYLINDER  *************************************************************
         if(NULL != strstr(buf, "CYLINDER")) 
         {
            // I save object type before reading other data
            ObjType = OPENGL_OBJECT_CYLINDER;

            // The object found is a TRIANGLE, I read object color:
            if(sscanf(buf, "CYLINDER %d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) == 3)
            {
               // I save color found
               TmpColor.R = (double)ReadValue1/255;      TmpColor.G = (double)ReadValue2/255;      TmpColor.B = (double)ReadValue3/255;
            }
            else
            {
               // I have not found a correct object color, I use the default one...
               TmpColor.R = 1.0;             TmpColor.G = 1.0;             TmpColor.B = 1.0;
            }

            // Then I read point coord
            CurrentPoint = 0;
            Done = FALSE;
            PtrPt1 = NULL;		PtrPt2 = NULL;		PtrPt3 = NULL;    PtrPt4 = NULL;     

            do
            {
               if(NULL != fgets(buf, 256, FilePtr))   // I read a line from the opened file
               {
                  if(sscanf(buf, "%d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) == 3)   // I get data
                  {
                     TmpPt1.x = ReadValue1;    TmpPt1.y = ReadValue2;    TmpPt1.z = ReadValue3;    PtrPt1 = &TmpPt1;
                  }

                  else if(sscanf(buf, "%d", &ReadValue1) == 1)   // I get data
                  {
                     switch(CurrentPoint) // I store data into object structure
                     {
                     case 0:  TmpRadius = ReadValue1;    PtrRadius = &TmpRadius;    break;
                     case 1:  TmpHeight = ReadValue1;    PtrHeight = &TmpHeight;    Done = TRUE;   break;
                     default: break;
                     }

                     CurrentPoint++;
                  }
               }
            }while(FALSE == Done);

			}

			// Case BEACON_BLUE  *************************************************************
         if(NULL != strstr(buf, "BEACON_BLUE")) 
         {
            // I save object type before reading other data
            ObjType = OPENGL_OBJECT_INFO_BEACON;

            TmpColor.R = 0;             TmpColor.G = 0;             TmpColor.B = 0;

            // Then I read point coord
            CurrentPoint = 0;
            Done = FALSE;
            PtrPt1 = NULL;		PtrPt2 = NULL;		PtrPt3 = NULL;    PtrPt4 = NULL;     

            do
            {
               if(NULL != fgets(buf, 256, FilePtr))   // I read a line from the opened file
               {
                  if(sscanf(buf, "%d%d%d%d", &ReadValue1, &ReadValue2, &ReadValue3, &TmpRadius) == 4)   // I get data
                  {
                     PtrRadius = &TmpRadius;
                     switch(CurrentPoint) // I store data into object structure
                     {
                     case 0:  TmpPt1.x = ReadValue1;    TmpPt1.y = ReadValue2;    TmpPt1.z = ReadValue3;    PtrPt1 = &TmpPt1;    break;
                     case 1:  TmpPt2.x = ReadValue1;    TmpPt2.y = ReadValue2;    TmpPt2.z = ReadValue3;    PtrPt2 = &TmpPt2;    break;
                     case 2:  TmpPt3.x = ReadValue1;    TmpPt3.y = ReadValue2;    TmpPt3.z = ReadValue3;    PtrPt3 = &TmpPt3;    Done = true;   break;
                     default: break;
                     }

                     CurrentPoint++;
                  }
               }
            }while(FALSE == Done);
			}

         // Case Object Info : MapSize  *************************************************************
         if(NULL != strstr(buf, "MAP_SIZE")) 
         {
            // I save object type before reading other data
            ObjType = OPENGL_OBJECT_INFO_MAPSIZE;

            Done = FALSE;
            PtrPt1 = NULL;		PtrPt2 = NULL;		PtrPt3 = NULL;    PtrPt4 = NULL;     

            if(sscanf(buf, "MAP_SIZE %d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) != 3)
            {
               ReadValue1 = 0;             ReadValue2 = 0;             ReadValue3 = 0;
            }

            TmpPt1.x = ReadValue1;    TmpPt1.y = ReadValue2;    TmpPt1.z = ReadValue3;    PtrPt1 = &TmpPt1;
			}

         // Case Object Info : AXIS  *************************************************************
         if(NULL != strstr(buf, "AXIS")) 
         {
            // I save object type before reading other data
            ObjType = OPENGL_OBJECT_AXIS;

            Done = FALSE;
            PtrPt1 = NULL;		PtrPt2 = NULL;		PtrPt3 = NULL;    PtrPt4 = NULL;     

            if(sscanf(buf, "AXIS %d%d%d%d", &ReadValue1, &ReadValue2, &TmpHeight, &TmpRadius) == 4)
            {
               TmpPt1.x = ReadValue1;    TmpPt1.y = ReadValue1;    TmpPt1.z = ReadValue1;    PtrPt1 = &TmpPt1;
               TmpPt2.x = ReadValue2;    TmpPt2.y = ReadValue2;    TmpPt2.z = ReadValue2;    PtrPt2 = &TmpPt2;
               PtrRadius = &TmpRadius;
               PtrHeight = &TmpHeight;
            }
         }

         // Case Object Info : AXIS  *************************************************************
         if(NULL != strstr(buf, "CAMERA_POS")) 
         {
            // I save object type before reading other data
            ObjType = OPENGL_OBJECT_CAM_POS;

            Done = FALSE;
            PtrPt1 = NULL;		PtrPt2 = NULL;		PtrPt3 = NULL;    PtrPt4 = NULL;     

            if(sscanf(buf, "CAMERA_POS %d%d%d", &ReadValue1, &ReadValue2, &ReadValue3) != 3)
            {
               ReadValue1 = 0;             ReadValue2 = 0;             ReadValue3 = 0;
            }

            TmpPt1.x = ReadValue1;    TmpPt1.y = ReadValue2;    TmpPt1.z = ReadValue3;    PtrPt1 = &TmpPt1;
         }

         // If I have read an object that is not OPENGL_OBJECT_NONE I create it into list
         // Warning : a 3D object means create 6 2D object. 
         // For each object I create the normal vector associated to this 2D object
         if(OPENGL_OBJECT_NONE != ObjType)
         {
            // If current object is already created, I add a new one at the end
            // otherwise, I complete fields for the current object
            if(OPENGL_OBJECT_NONE == Type)
            {
               // Current object is empty, I create it
               SetObject(ObjType, PtrPt1, PtrPt2, PtrPt3, PtrPt4, PtrRadius, PtrHeight, &TmpColor); 

            }
            else
            {
               // I need to create a new one
					AddObject(ObjType, PtrPt1, PtrPt2, PtrPt3, PtrPt4, PtrRadius, PtrHeight, &TmpColor);
				}

            if(ObjectHeight != 0)
            {
               // Then I add all other face
               TmpPt5.x = TmpPt1.x;    TmpPt5.y = TmpPt1.y;    TmpPt5.z = TmpPt1.z + ObjectHeight; 
               TmpPt6.x = TmpPt2.x;    TmpPt6.y = TmpPt2.y;    TmpPt6.z = TmpPt2.z + ObjectHeight; 
               TmpPt7.x = TmpPt3.x;    TmpPt7.y = TmpPt3.y;    TmpPt7.z = TmpPt3.z + ObjectHeight; 
               TmpPt8.x = TmpPt4.x;    TmpPt8.y = TmpPt4.y;    TmpPt8.z = TmpPt4.z + ObjectHeight; 

				   AddObject(ObjType, &TmpPt5, &TmpPt8, &TmpPt7, &TmpPt6, PtrRadius, PtrHeight, &TmpColor);
				   AddObject(ObjType, &TmpPt1, &TmpPt5, &TmpPt6, &TmpPt2, PtrRadius, PtrHeight, &TmpColor);
				   AddObject(ObjType, &TmpPt2, &TmpPt6, &TmpPt7, &TmpPt3, PtrRadius, PtrHeight, &TmpColor);
				   AddObject(ObjType, &TmpPt3, &TmpPt7, &TmpPt8, &TmpPt4, PtrRadius, PtrHeight, &TmpColor);
				   AddObject(ObjType, &TmpPt4, &TmpPt8, &TmpPt5, &TmpPt1, PtrRadius, PtrHeight, &TmpColor);
            }
         }
      }
   }

	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
int OpenGL_Object::AddObject(short _Type, Coord3D *_Pt1)
{
	OpenGL_Object *Current;
	Current = this;

	if(OPENGL_OBJECT_NONE != _Type)
	{
		while(NULL != Current->Next){	Current = Current->Next;	}

		Current->Next = new OpenGL_Object(_Type, _Pt1);
	}
	
	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
int OpenGL_Object::AddObject(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, ColorRGB *_Color)
{
	OpenGL_Object *Current;
	Current = this;

	if(OPENGL_OBJECT_NONE != _Type)
	{
		while(NULL != Current->Next){	Current = Current->Next;	}

		Current->Next = new OpenGL_Object(_Type, _Pt1, _Pt2, _Color);
	}
	
	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
int OpenGL_Object::AddObject(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, ColorRGB *_Color)
{
	OpenGL_Object *Current;
	Current = this;

	if(OPENGL_OBJECT_NONE != _Type)
	{
		while(NULL != Current->Next){	Current = Current->Next;	}

		Current->Next = new OpenGL_Object(_Type, _Pt1, _Pt2, _Pt3, _Color);
	}
	
	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
int OpenGL_Object::AddObject(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, Coord3D *_Pt4, ColorRGB *_Color)
{
	OpenGL_Object *Current;
	Current = this;

	if(OPENGL_OBJECT_NONE != _Type)
	{
		while(NULL != Current->Next){	Current = Current->Next;	}

		Current->Next = new OpenGL_Object(_Type, _Pt1, _Pt2, _Pt3, _Pt4, _Color);
	}
	
	return IHM_GLUT_NoError;
}

int OpenGL_Object::ComputeNormalVect()
{
   CoordVect TmpVectA, TmpVectB;
   float NormA, NormB;
   
   // Compute vectors
   TmpVectA.x = Pt3.x - Pt1.x;   TmpVectA.y = Pt3.y - Pt1.y;   TmpVectA.z = Pt3.z - Pt1.z;
   TmpVectB.x = Pt2.x - Pt1.x;   TmpVectB.y = Pt2.y - Pt1.y;   TmpVectB.z = Pt2.z - Pt1.z;
   
   // Normalize Vectors
   NormA = sqrt(TmpVectA.x * TmpVectA.x + TmpVectA.y * TmpVectA.y + TmpVectA.z * TmpVectA.z);
   NormB = sqrt(TmpVectB.x * TmpVectB.x + TmpVectB.y * TmpVectB.y + TmpVectB.z * TmpVectB.z);

   if(NormA > 0){ TmpVectA.x = TmpVectA.x / NormA;   TmpVectA.y = TmpVectA.y / NormA;   TmpVectA.z = TmpVectA.z / NormA;   }
   if(NormB > 0){ TmpVectB.x = TmpVectB.x / NormB;   TmpVectB.y = TmpVectB.y / NormB;   TmpVectB.z = TmpVectB.z / NormB;   }


   // COmpute Normal Vector
   VectProduct(TmpVectA, TmpVectB, &NormalVect);

   return IHM_GLUT_NoError;
}

// ##########################################################################################
// Private functions
// ##########################################################################################

int OpenGL_Object::SetObject(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, Coord3D *_Pt4, int *_Radius, int *_Height, ColorRGB *_Color)
{

   // Set TYPE field
   Type = _Type;

   // All other fields are filled only if they are not NULL
   if(NULL != _Pt1)        {     Pt1.x = _Pt1->x;                 Pt1.y = _Pt1->y;                 Pt1.z = _Pt1->z;                 }
   if(NULL != _Pt2)        {     Pt2.x = _Pt2->x;                 Pt2.y = _Pt2->y;                 Pt2.z = _Pt2->z;                 }
   if(NULL != _Pt3)        {     Pt3.x = _Pt3->x;                 Pt3.y = _Pt3->y;                 Pt3.z = _Pt3->z;                 }
   if(NULL != _Pt4)        {     Pt4.x = _Pt4->x;                 Pt4.y = _Pt4->y;                 Pt4.z = _Pt4->z;                 }
   if(NULL != _Radius)     {     Radius = *_Radius;                                                                                 }
   if(NULL != _Height)     {     Height = *_Height;                                                                                 }
   if(NULL != _Color)      {     Color.R = _Color->R;             Color.G = _Color->G;             Color.B = _Color->B;             }


   if((NULL != _Pt1) || (NULL != _Pt2) || (NULL != _Pt3) || (NULL != _Pt4)) 
   {
      ComputeNormalVect();
   }

	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
int OpenGL_Object::AddObject(short _Type, Coord3D *_Pt1, Coord3D *_Pt2, Coord3D *_Pt3, Coord3D *_Pt4, int *_Radius, int *_Height, ColorRGB *_Color)
{
	OpenGL_Object *Current;
	Current = this;

	if(OPENGL_OBJECT_NONE != _Type)
	{
		while(NULL != Current->Next){	Current = Current->Next;	}


		switch(_Type)
		{
		case OPENGL_OBJECT_LINE:
			Current->Next = new OpenGL_Object(_Type, _Pt1, _Pt2, _Color);
			break;

		case OPENGL_OBJECT_TRIANGLE:
			Current->Next = new OpenGL_Object(_Type, _Pt1, _Pt2, _Pt3, _Color);
			break;

		case OPENGL_OBJECT_SQUARE:
			Current->Next = new OpenGL_Object(_Type, _Pt1, _Pt2, _Pt3, _Pt4, _Color);
			break;

		case OPENGL_OBJECT_CYLINDER:
			Current->Next = new OpenGL_Object(_Type, _Pt1, _Radius, _Height, _Color);
			break;

		case OPENGL_OBJECT_INFO_MAPSIZE:
			Current->Next = new OpenGL_Object(_Type, _Pt1);
			break;

		case OPENGL_OBJECT_CAM_POS:
			Current->Next = new OpenGL_Object(_Type, _Pt1);
			break;

      default:
			Current->Next = NULL;
			break;
		}
	}
	
	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
int OpenGL_Object::InitObject()
{
	Type = OPENGL_OBJECT_NONE;
   Color.R = -1;		Color.G = -1;		Color.B = -1;		Color.A = -1;      
   Pt1.x = 0;			Pt1.y = 0;			Pt1.z = 0;
   Pt2.x = 0;			Pt2.y = 0;			Pt2.z = 0;
   Pt3.x = 0;			Pt3.y = 0;			Pt3.z = 0;
   Pt4.x = 0;			Pt4.y = 0;			Pt4.z = 0;
   NormalVect.x = 0; NormalVect.y = 0; NormalVect.z = 0; 
   Radius = -1;
   Height = -1;

   Next = NULL;

	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
int OpenGL_Object::VectProduct(CoordVect VectA, CoordVect VectB, CoordVect *VectOut)
{
   double Norm = 0;

   if(NULL == VectOut)
   {
      return IHM_GLUT_ERR_NOTENOUGHTPARAM;
   }

   // compute first Coord
   VectOut->x = (VectA.y)*(VectB.z) - (VectA.z)*(VectB.y);
   VectOut->y = (VectA.z)*(VectB.x) - (VectA.x)*(VectB.z);
   VectOut->z = (VectA.x)*(VectB.y) - (VectA.y)*(VectB.x);

	return IHM_GLUT_NoError;
}