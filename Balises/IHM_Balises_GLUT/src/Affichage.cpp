/*******************************************************************************************
      File           :  Affichage.cpp
      See details on :  Affichage.h
      Authors        :  Fifi_one    (philippe.bechet@cpe.fr)
      Team           :  OUFFF TEAM
/*******************************************************************************************/

#include "Affichage.h"

// OpenGL objects
OpenGL_Object Map;
OpenGL_Object Beacon;
OpenGL_Object Axis;

// OpenGL lists (to optimize display)
GLuint OpenGL_ListMap = 1;
GLuint OpenGL_ListRobot = 2;

int MapSizeX, MapSizeY, MapSizeZ;
int InitialVisualAngle, InitialVisualHeight, InitialLentghToScene;
Coord3D PosBeaconBlue[3];
int BeaconRayon;
float RefPointX, RefPointY;
float ReflexionAngle;
int LaserDepth = LASER_DEPTH;	 			// Distance between laser and beacon

// Other variable
int Initial_x;
int Initial_y;
int Button;
int LentghToScene;                     // Length between map center and eye
int VisualHeight;                      // Height of eye
int VisualAngle;								// Visual angle around map	in degree
int WinSizeX, WinSizeY;
float LaserAngle;                      // Laser angle in degree (origin on Y AXIS)
LARGE_INTEGER TimeLastDraw;            // Time of previous Draw
LARGE_INTEGER Frequency;               // Processor frequency

// Extern variable to set new Robot Position
int RobotPosX;
int RobotPosY;
int RobotSize;
int RobotHeight;
int RobotPosAngle;
int LaserHeight;
int DisplayFreq;		// OpenGL display freq en FPS
float LaserSpeed;    // Speed in Hz of laser
float LaserAlpha;    // Transparency of laser
bool MutexPos;			// Mutex to block reading when other module is wrinting

// OpenGL textures
OpenGL_Texture GdLogoTexture;
OpenGL_Texture PttLogoTexture;
GLuint GdLogoTexId = 0;
GLuint PttLogoTexId = 0;

GLfloat white[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat red[] = { 1.0, 0.0, 0.0, 0.0 };
GLfloat green[] = { 0.0, 1.0, 0.0, 0.0 };
GLfloat blue[] = { 0.0, 0.0, 1.0, 0.0 };
GLfloat black[] = { 0.0, 0.0, 0.0, 0.0 };

GLfloat light0_position[4];
GLfloat light1_position[4];
GLfloat light2_position[4];

GLfloat specular[] = { 1.0,1.0,1.0,1.0 };
GLfloat shinines[] = { 30.0 };
GLfloat ambiant[] = { 0.2,0.2,0.2,1.0 };
GLfloat none[] = { 0,0.0,0 };



// ------------------------------------------------------------------------------------------
int OpenGL_Init()
{
   VisualHeight = 0;
	LentghToScene = 0;
	VisualAngle = 0;
   LaserAngle = 0;
   QueryPerformanceFrequency(&Frequency);    // Computer freq
   QueryPerformanceCounter(&TimeLastDraw);   // Set initial value
   

   if(0 != GdLogoTexId)    {      glDeleteTextures(1, &GdLogoTexId);    } 	           //Delete a texture ID   
   if(0 != PttLogoTexId)   {      glDeleteTextures(1, &PttLogoTexId); 	}             //Delete a texture ID   
  

   // Load LogoTexture;
   GdLogoTexture.LoadFromBmp("LogoGd.bmp");
   PttLogoTexture.LoadFromBmp("ALTERA.bmp");
   glGenTextures(1, &GdLogoTexId); 	               //Create a texture ID
   glGenTextures(1, &PttLogoTexId); 	            //Create a texture ID

	glClearColor (0.2, 0.2, 0.2, 1);
	glShadeModel (GL_SMOOTH);
	glMatrixMode (GL_MODELVIEW);

	// Setting Cam
	gluLookAt (0, 0, 0, 0, 0, -1, 0, 1, 0);
      // param 1,2,3 : eye position (use 3D-coord)
      // param 4,5,6 : stared point (use 3D-coord)
      // param 7,8,9 : define which axis will be used as vertical axis on screen
		// 1,0,0 -> x-axis will be drawn as vertical axis on screen 
		// 0,1,0 -> y-axis will be drawn as vertical axis on screen 
		// 0,0,1 -> z-axis will be drawn as vertical axis on screen 
   
	glMatrixMode(GL_MODELVIEW); 							// Set Matrix Model used
	glEnable(GL_DEPTH_TEST);								// Enable DEPTH (hides hidden faces)
	glEnable(GL_COLOR_MATERIAL);							// To draw materials more real


   glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinines);
   

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambiant);   glLightfv(GL_LIGHT0, GL_DIFFUSE, white);  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
   glLightfv(GL_LIGHT1, GL_AMBIENT, ambiant);   glLightfv(GL_LIGHT1, GL_DIFFUSE, white);  glLightfv(GL_LIGHT1, GL_SPECULAR, white);
   glLightfv(GL_LIGHT2, GL_AMBIENT, ambiant);   glLightfv(GL_LIGHT2, GL_DIFFUSE, white);  glLightfv(GL_LIGHT2, GL_SPECULAR, white);

   glEnable(GL_LIGHT0); 
   glEnable(GL_LIGHT1); 
   glEnable(GL_LIGHT2); 

   glEnable(GL_LIGHTING);

   // delete all OpenGL list previously declared
   glDeleteLists(0, 10);

   // Objects creation
   OpenGL_CreateMap();
   OpenGL_CreateRobot();

   return IHM_GLUT_NoError;
}

// ------------------------------------------------------------------------------------------
void OpenGL_Reshape(int width, int height)
{ 	 
  	glViewport(0, 0, width, height);											// Set display size on OpenGL window
  	glMatrixMode(GL_PROJECTION);												// Set Matrix Model used
  	glLoadIdentity();																// Matrix initialisation
  	gluPerspective(60, float(width)/float(height), 500, DEPTH); 	// Set perspective settings
  	glMatrixMode(GL_MODELVIEW); 												// Set Matrix Model used
	OpenGL_Init();

	WinSizeX = width;
	WinSizeY = height;
}

// ------------------------------------------------------------------------------------------
void OpenGL_Draw()
{
	GLUquadric *gluObj_Laser = gluNewQuadric(	);
	CoordVect NormalVect, LaserVect;
   double BeaconAngle[3] = {0};
   float Norm;

   if(LentghToScene == 0)  {    LentghToScene = InitialLentghToScene;  }
   if(VisualHeight == 0)   {    VisualHeight = InitialVisualHeight;  }
   if(VisualAngle == 0)    {    VisualAngle = InitialVisualAngle;   }

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 	//Clear frame buffer and Z-buffer

    // set lights position
   light0_position[0] = MapSizeX/2;    light0_position[1] = 500.0;   light0_position[2] = MapSizeX/2;  light0_position[3] = 0.0;
   light1_position[0] = -MapSizeX/2;   light1_position[1] = 500.0;   light1_position[2] = -MapSizeX/2; light1_position[3] = 0.0;
   light2_position[0] = MapSizeX+1000; light2_position[1] = 500.0;   light2_position[2] = -MapSizeX/2; light2_position[3] = 0.0;

	OpenGL_DrawHeader();												// Draw window header 
	
	glLoadIdentity(); 												// Matrix initialisation
	gluLookAt (0, 0, 0, 0, 0, -1, 0, 1, 0);					// Setting Cam

   // Move Cam to set correct eye position
	// I rotate map to show it with correct angle to see everywhere scene
   OpenGL_Rotate((int)(asin((double)VisualHeight/(double)(2*LentghToScene))*180/M_PI), AXIS_X);		
   
	OpenGL_SetCamPos(0, -LentghToScene, VisualHeight);

   // Positionnement de l'éclairage
   glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
   glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
   glLightfv(GL_LIGHT2, GL_POSITION, light2_position);


	glPushMatrix();									         // I save current Matrix to draw Map
		OpenGL_Rotate(VisualAngle, AXIS_Z);		         // I rotate map to show it with correct angle
		OpenGL_Translate(-MapSizeX/2, -MapSizeY/2, 0);	// I center map on screen space
      glCallList(OpenGL_ListMap);                     // Draw Map
		OpenGL_DrawObject(&Beacon);                     // Draw Beacons

	   glPushMatrix();									         // I save current Matrix to draw Map
		   // Draw Robot
		   while(true == MutexPos){	Sleep(1);	}		// Mutex to not read value when I write them in other module
         OpenGL_Translate(RobotPosX, RobotPosY, RobotHeight);	
         glCallList(OpenGL_ListRobot);                     // Draw Robot

         // Compute laser angle
         ComputeLaserAngle();
         ComputeLaserReflexion();

         if(0 != LaserSpeed)
         {
   	      // Draw laser spot
     	      glPushMatrix();									// I save current Matrix 
			      // Disable light reflexion on laser
		         glMaterialfv(GL_FRONT,GL_SPECULAR,none);
		         glMaterialfv(GL_FRONT,GL_SHININESS,none);

		         OpenGL_Rotate(-90, AXIS_X);
               OpenGL_Translate(0, 0, LaserHeight - RobotHeight);	
		         OpenGL_Rotate(LaserAngle + 90, AXIS_Z);

               // Draw Laser
               glEnable(GL_BLEND);                                // Use transparency
               glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set transparency settings
		         glColor4d(1, 0, 0, LaserAlpha);
		         gluCylinder(gluObj_Laser, 5, 5, LaserDepth, 20, 20);
               glDisable(GL_BLEND);
 
		         glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		         glMaterialfv(GL_FRONT,GL_SHININESS,shinines);
		      glPopMatrix();
         }
      glPopMatrix();									       

      if(0 != LaserSpeed)
      {
		   // If reflexion, we draw reflexion ray
		   if((0 != RefPointX) && (0 != RefPointY))
		   {
			   // Case of balise 1
			   if(RefPointX < 200)
			   {
				   // Compute normal vector in point (RefPointX, RefPointY)
				   NormalVect.z = 0;		NormalVect.x = RefPointX - PosBeaconBlue[0].x;			NormalVect.y = RefPointY - PosBeaconBlue[0].y;
				   LaserVect.z = 0;		LaserVect.x = RefPointX - RobotPosX;	LaserVect.y = RefPointY - RobotPosY;	
			   }

			   // Case of balise 2
			   if(RefPointX > 2000)
			   {
				   // Compute normal vector in point (RefPointX, RefPointY)
				   NormalVect.z = 0;		NormalVect.x = RefPointX - PosBeaconBlue[1].x;			NormalVect.y = RefPointY - PosBeaconBlue[1].y;
				   LaserVect.z = 0;		LaserVect.x = RefPointX - RobotPosX;	LaserVect.y = RefPointY - RobotPosY;	
			   }

			   // Case of balise 3
			   if((RefPointX > 200) && (RefPointX < 2000))
			   {
				   // Compute normal vector in point (RefPointX, RefPointY)
				   NormalVect.z = 0;		NormalVect.x = RefPointX - PosBeaconBlue[2].x;			NormalVect.y = RefPointY - PosBeaconBlue[2].y;
				   LaserVect.z = 0;		LaserVect.x = RefPointX - RobotPosX;	LaserVect.y = RefPointY - RobotPosY;	
			   }

			   // Compute Angle between normal vector and laser vector
			   Norm = sqrt(NormalVect.x*NormalVect.x + NormalVect.y*NormalVect.y + NormalVect.z*NormalVect.z);
			   NormalVect.x /= Norm;		NormalVect.y /= Norm;		NormalVect.z /= Norm;		

			   Norm = sqrt(LaserVect.x*LaserVect.x + LaserVect.y*LaserVect.y + LaserVect.z*LaserVect.z);
			   LaserVect.x /= Norm;		LaserVect.y /= Norm;		LaserVect.z /= Norm;	
			   
			   // Angle
			   ReflexionAngle = acos(NormalVect.x*LaserVect.x + NormalVect.y*LaserVect.y + NormalVect.z*LaserVect.z) * 180 / M_PI;
	         while(ReflexionAngle >= 90){   ReflexionAngle = ReflexionAngle - 90;   }
	         while(ReflexionAngle <= -90){   ReflexionAngle = ReflexionAngle + 90;   }

			   // Compute OpenGL angle
			   ReflexionAngle = LaserAngle + 180 + ReflexionAngle;
	         while(ReflexionAngle >= 360){   ReflexionAngle = ReflexionAngle - 360;   }

			   // Draw Reflexion
			   glPushMatrix();									// I save current Matrix 
				   glMaterialfv(GL_FRONT,GL_SPECULAR,none);
				   glMaterialfv(GL_FRONT,GL_SHININESS,none);

				   OpenGL_Translate(RefPointX, RefPointY, LaserHeight);	
				   OpenGL_Rotate(ReflexionAngle + 90, AXIS_Z);

				   // Draw Laser
				   glEnable(GL_BLEND);                                // Use transparency
				   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set transparency settings
				   glColor4d(1, 0, 0, LaserAlpha/3);
				   gluCylinder(gluObj_Laser, 5, 0, 10000, 20, 20);
				   glDisable(GL_BLEND);
		   
				   glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
			      glMaterialfv(GL_FRONT,GL_SHININESS,shinines);
			   glPopMatrix();										// I restore current Matrix 
		   }
      }
   glPopMatrix();													// I restore previous Matrix

	// Flush display
	glutSwapBuffers();

   // Delete object
   gluDeleteQuadric(gluObj_Laser);


	// Compute new scene
	Sleep(1/(float)DisplayFreq * 1000);
   glFinish();
	glutPostRedisplay();
}

// ------------------------------------------------------------------------------------------
int OpenGL_CreateMap()
{
   glNewList(OpenGL_ListMap, GL_COMPILE);
		OpenGL_DrawObject(&Map);                        // Draw Map
 		OpenGL_DrawObject(&Axis);                       // Draw Axis
   glEndList();

   return IHM_GLUT_NoError;
}

// ------------------------------------------------------------------------------------------
int OpenGL_CreateRobot()
{
	GLUquadric *gluObj_Robot = gluNewQuadric(	);
	GLUquadric *gluObj_TopRobot = gluNewQuadric(	);
	GLUquadric *gluObj_LaserSupp = gluNewQuadric(	);

   glNewList(OpenGL_ListRobot, GL_COMPILE);

      if(0 != LaserSpeed)
      {
         // Draw Laser Support
     	   glPushMatrix();
            glColor3d(0.05, 0.05, 0.05);
   		   OpenGL_Rotate(-90, AXIS_X);
		      gluCylinder(gluObj_LaserSupp, R_LASER, R_LASER, LaserHeight - RobotHeight, 20, 20);
         glPopMatrix();
      }

      // Draw Robot
  		glColor3d(0,0,1);
		OpenGL_Rotate(90, AXIS_X);
		gluCylinder(gluObj_Robot, RobotSize, RobotSize, RobotHeight, 20, 20);
		gluDisk(gluObj_TopRobot, 0, RobotSize, 20, 20);
   glEndList();
   
   gluDeleteQuadric(gluObj_Robot);     gluObj_Robot = NULL;
   gluDeleteQuadric(gluObj_TopRobot);  gluObj_TopRobot = NULL;
   gluDeleteQuadric(gluObj_LaserSupp); gluObj_LaserSupp = NULL;


   return IHM_GLUT_NoError;
}

// ------------------------------------------------------------------------------------------
int OpenGL_DrawObject(OpenGL_Object *ObjToDraw)
{
	
   GLUquadric *GluObject1 = NULL;      GLUquadric *GluObject2 = NULL;
   GLUquadric *GluObject3 = NULL;      GLUquadric *GluObject4 = NULL;
   GLUquadric *GluObject5 = NULL;      GLUquadric *GluObject6 = NULL;

   OpenGL_Object *CurrentObj = ObjToDraw;
   int ObjectIterator = 0;

	if(NULL != CurrentObj)
	{
		while(NULL != CurrentObj)
		{
			switch(CurrentObj->Type)
			{
			case OPENGL_OBJECT_LINE:		// We want to draw a LINE
				glBegin(GL_LINES);
					glColor3d(CurrentObj->Color.R, CurrentObj->Color.G, CurrentObj->Color.B);
					glVertex3i(CurrentObj->Pt1.x, CurrentObj->Pt1.z, (-1)*(CurrentObj->Pt1.y));	
					glVertex3i(CurrentObj->Pt2.x, CurrentObj->Pt2.z, (-1)*(CurrentObj->Pt2.y));
				glEnd();
				break;

			case OPENGL_OBJECT_SQUARE:		// We want to draw a SQUARE
				glBegin(GL_QUADS);
					glColor3d(CurrentObj->Color.R, CurrentObj->Color.G, CurrentObj->Color.B);
					glVertex3i(CurrentObj->Pt1.x, CurrentObj->Pt1.z, (-1)*(CurrentObj->Pt1.y));	
					glVertex3i(CurrentObj->Pt2.x, CurrentObj->Pt2.z, (-1)*(CurrentObj->Pt2.y));	
					glVertex3i(CurrentObj->Pt3.x, CurrentObj->Pt3.z, (-1)*(CurrentObj->Pt3.y));	
					glVertex3i(CurrentObj->Pt4.x, CurrentObj->Pt4.z, (-1)*(CurrentObj->Pt4.y));
               
               glNormal3f( (float)(CurrentObj->NormalVect.x),
                           (float)(CurrentObj->NormalVect.z),
                           (float)(CurrentObj->NormalVect.y)*(-1));
				glEnd();
            break;

			case OPENGL_OBJECT_TRIANGLE:		// We want to draw a TRIANGLE
				glBegin(GL_TRIANGLES);
					glColor3d(CurrentObj->Color.R, CurrentObj->Color.G, CurrentObj->Color.B);
					glVertex3i(CurrentObj->Pt1.x, CurrentObj->Pt1.z, (-1)*(CurrentObj->Pt1.y));	
					glVertex3i(CurrentObj->Pt2.x, CurrentObj->Pt2.z, (-1)*(CurrentObj->Pt2.y));	
					glVertex3i(CurrentObj->Pt3.x, CurrentObj->Pt3.z, (-1)*(CurrentObj->Pt3.y));	
				glEnd();
				break;
				
			case OPENGL_OBJECT_CYLINDER:		// We want to draw a CYLINDER
            GluObject1 = gluNewQuadric();
            GluObject2 = gluNewQuadric();
	         glPushMatrix();									// I save current Matrix 
               OpenGL_Translate(CurrentObj->Pt1.x, CurrentObj->Pt1.y, CurrentObj->Pt1.z + CurrentObj->Height);	
		         OpenGL_Rotate(90, AXIS_X);	

				   glColor3d(CurrentObj->Color.R, CurrentObj->Color.G, CurrentObj->Color.B);
		         gluCylinder(GluObject1, CurrentObj->Radius, CurrentObj->Radius, CurrentObj->Height, 20, 20);
		         gluDisk(GluObject2, 0, CurrentObj->Radius, 20, 20);
	         glPopMatrix();													// I restore previous Matrix
            gluDeleteQuadric(GluObject1);            
            gluDeleteQuadric(GluObject1);
            break;

         case OPENGL_OBJECT_INFO_MAPSIZE:
            MapSizeX = CurrentObj->Pt1.x;    MapSizeY = CurrentObj->Pt1.y;    MapSizeZ = CurrentObj->Pt1.z;
            break;

         case OPENGL_OBJECT_INFO_BEACON:
            PosBeaconBlue[0].x = CurrentObj->Pt1.x;    PosBeaconBlue[0].y = CurrentObj->Pt1.y;    PosBeaconBlue[0].z = CurrentObj->Pt1.z;
            PosBeaconBlue[1].x = CurrentObj->Pt2.x;    PosBeaconBlue[1].y = CurrentObj->Pt2.y;    PosBeaconBlue[1].z = CurrentObj->Pt2.z;
            PosBeaconBlue[2].x = CurrentObj->Pt3.x;    PosBeaconBlue[2].y = CurrentObj->Pt3.y;    PosBeaconBlue[2].z = CurrentObj->Pt3.z;
            BeaconRayon = CurrentObj->Radius;
            break;

  			case OPENGL_OBJECT_AXIS:		// We want to draw 3D axis
            GluObject1 = gluNewQuadric();       GluObject2 = gluNewQuadric();
            GluObject3 = gluNewQuadric();       GluObject4 = gluNewQuadric();
            GluObject5 = gluNewQuadric();       GluObject6 = gluNewQuadric();

            // Draw Ox
	         glPushMatrix();									// I save current Matrix 
				   glColor3d(1.0, 0.0, 0.0);
		         OpenGL_Rotate(90, AXIS_Z);	
		         gluCylinder(GluObject1, CurrentObj->Pt2.x, CurrentObj->Pt2.x, CurrentObj->Pt1.x, 20, 20);
	            glPushMatrix();									// I save current Matrix 
                  OpenGL_Translate(0, -CurrentObj->Pt1.x, 0);	
		            gluCylinder(GluObject2, CurrentObj->Radius, 0, CurrentObj->Height, 20, 20);
	            glPopMatrix();													// I restore previous Matrix
	         glPopMatrix();    												// I restore previous Matrix

            // Draw Oy
	         glPushMatrix();									// I save current Matrix 
				   glColor3d(0.0, 1.0, 0.0);
		         OpenGL_Rotate(180, AXIS_X);	
		         gluCylinder(GluObject3, CurrentObj->Pt2.x, CurrentObj->Pt2.x, CurrentObj->Pt1.x, 20, 20);
	            glPushMatrix();									// I save current Matrix 
                  OpenGL_Translate(0, -CurrentObj->Pt1.x, 0);	
		            gluCylinder(GluObject4, CurrentObj->Radius, 0, CurrentObj->Height, 20, 20);
	            glPopMatrix();													// I restore previous Matrix
	         glPopMatrix();													// I restore previous Matrix

            // Draw Oz
	         glPushMatrix();									// I save current Matrix 
				   glColor3d(0.0, 0.0, 1.0);
		         OpenGL_Rotate(-90, AXIS_X);	
		         gluCylinder(GluObject5, CurrentObj->Pt2.x, CurrentObj->Pt2.x, CurrentObj->Pt1.x, 20, 20);
	            glPushMatrix();									// I save current Matrix 
                  OpenGL_Translate(0, -CurrentObj->Pt1.x, 0);	
		            gluCylinder(GluObject6, CurrentObj->Radius, 0, CurrentObj->Height, 20, 20);
	            glPopMatrix();													// I restore previous Matrix
	         glPopMatrix();													// I restore previous Matrix

            gluDeleteQuadric(GluObject1);    gluDeleteQuadric(GluObject2);
            gluDeleteQuadric(GluObject3);    gluDeleteQuadric(GluObject4);
            gluDeleteQuadric(GluObject5);    gluDeleteQuadric(GluObject6);
            break;

         case OPENGL_OBJECT_CAM_POS:
            InitialVisualAngle = CurrentObj->Pt1.x;   InitialVisualHeight = CurrentObj->Pt1.y;   InitialLentghToScene = CurrentObj->Pt1.z;
            break;

         default:
				break;
			}

			CurrentObj = CurrentObj->Next;
		}
	}

	return IHM_GLUT_NoError;
}

// ------------------------------------------------------------------------------------------
void OpenGL_Keyboard(unsigned char key, int x, int y)
{
   glFlush();
	switch (key) 
	{
	case 27:
		exit(0);
		break;

	case 32:
		OpenGL_Init();
		break;

   case '+':
      VisualHeight += 50;
      if(VisualHeight > 1800)
      {
         VisualHeight = 1800;
      }
      break;

   case '-':
      VisualHeight -= 50;
      if(VisualHeight < 100)
      {
         VisualHeight = 100;
      }
      break;

	default:
		break;
	}
}


// ------------------------------------------------------------------------------------------
void OpenGL_Mouse(int button, int state, int x, int y)
{

	if(GLUT_DOWN == state)
	{
		switch(button)
		{
		case  GLUT_LEFT_BUTTON:
			Initial_x = x;
			Initial_y = y;
			Button = GLUT_LEFT_BUTTON;
			break;
		
		case  GLUT_RIGHT_BUTTON:
			Initial_x = x;
			Initial_y = y;
			Button = GLUT_RIGHT_BUTTON;
			break;
		}
	}
	else
	{
		Initial_x = 0;
		Initial_y = 0;
		Button = 0;
	}
}

// ------------------------------------------------------------------------------------------
void OpenGL_MouseOnScreen(int x, int y)
{

	switch(Button)
	{
	case  GLUT_LEFT_BUTTON:
		VisualAngle += (x-Initial_x)*R_STEP;
		Initial_x = x;
		Initial_y = y;
		break;
	
	case  GLUT_RIGHT_BUTTON:
		LentghToScene -= (y-Initial_y)*T_STEP;
		Initial_x = x;
		Initial_y = y;

      if(LentghToScene < 1800)      // Limit set to block cam outsite of map
      {
         LentghToScene = 1800;
      }
		break;
	}
}


// ------------------------------------------------------------------------------------------
int OpenGL_Translate(int Tx, int Ty, int Tz)
{
	// Be careful : Map space (x,y,z) and graphic space (X,Y,Z) are different
	// (x, y, z) <=> (X, -Z, Y)

	glTranslatef(Tx, Tz, -Ty);			

	return IHM_GLUT_NoError;
}

// ------------------------------------------------------------------------------------------
int OpenGL_Rotate(int Angle, short Axis)
{
	switch(Axis)
	{
		// Select axis for rotation
	case AXIS_X:
		glRotatef(Angle, 1, 0, 0);
		break;

	case AXIS_Y:
		glRotatef(Angle, 0, 0, -1);
		break;
	
	case AXIS_Z:
		glRotatef(Angle, 0, 1, 0);
		break;

	default:
		break;
	}

	return IHM_GLUT_NoError;
}

// ------------------------------------------------------------------------------------------
int OpenGL_SetCamPos(int Tx, int Ty, int Tz)
{
	// Be careful : Map space (x,y,z) and graphic space (X,Y,Z) are different
	// (x, y, z) <=> (X, -Z, Y)

	glTranslatef(-Tx, -Tz, Ty);			

	return IHM_GLUT_NoError;

}

// ------------------------------------------------------------------------------------------
int OpenGL_SetCamRot(int Angle, short Axis)
{
	switch(Axis)
	{
		// Select axis for rotation
	case AXIS_X:
		glRotatef(Angle, -1, 0, 0);
		break;

	case AXIS_Y:
		glRotatef(Angle, 0, 0, -1);
		break;
	
	case AXIS_Z:
		glRotatef(Angle, 0, -1, 0);
		break;

	default:
		break;
	}

	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
int OpenGL_DrawHeader()
{
   char TmpBuf[1024];
   memset(TmpBuf, 0, 1024);

   // Write text
	glColor3d(1,1,1);
	OpenGL_WriteText2D(WinSizeX/2 - 100, HEADER_SIZE*WinSizeY*0.3, "Position actuelle du robot :");

   // Pos string creation
   sprintf(TmpBuf, "x = %d mm ; y = %d mm ; Angle = %d °", RobotPosX, RobotPosY, RobotPosAngle);
	OpenGL_WriteText2D(WinSizeX/2 - strlen(TmpBuf)*4, HEADER_SIZE*WinSizeY*0.7, TmpBuf);
   int test = strlen(TmpBuf);


	OpenGL_DrawLogo();
   
   // Draw header border
   OpenGL_Activate2D();          // Enable 2D buffer

	glBegin(GL_QUADS);
		glColor3d(1, 0, 0);        glVertex2i(HEADER_SIZE*WinSizeY*2,0);
		glColor3d(0, 0, 1);        glVertex2i(WinSizeX - HEADER_SIZE*WinSizeY,0);	
		glColor3d(0.2, 0.2, 0.2);  glVertex2i(WinSizeX - HEADER_SIZE*WinSizeY,HEADER_SIZE*WinSizeY);	
		glColor3d(0.2, 0.2, 0.2);  glVertex2i(HEADER_SIZE*WinSizeY*2,HEADER_SIZE*WinSizeY);	
	glEnd();

   OpenGL_Desactivate2D();       // Disable 2D buffer



	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
int OpenGL_WriteText2D(int x, int y, char* Text)
{

	if(NULL == Text)
	{
		return IHM_GLUT_ERR_NOTENOUGHTPARAM;
	}

 	// Save current transformation attributs
	glPushAttrib(GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);

	glMatrixMode(GL_PROJECTION);			// Set Matrix mode
	glPushMatrix();							// Save trans matrix
	glLoadIdentity();							// Load identity matrix

	glMatrixMode(GL_MODELVIEW);			// Set 2D matrix mode
	glPushMatrix();							// Save current matrix
	glLoadIdentity();							// Load identity matrix

	glViewport(x, WinSizeY-y, 0, 0);		// Set text position
	glRasterPos4f(0, 0, 0, 1);

	// Write Text
	for (int i=0;i<(int)strlen(Text);i++)
	{
	  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *(Text+i));
	}

	glPopMatrix();								// Restore previous matrix
	glMatrixMode(GL_PROJECTION);			// Set correct transformation mode
	glPopMatrix();								// Restore previous matrix

	glPopAttrib();								// Restore transformation attributs

	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
int OpenGL_DrawLogo()
{

   OpenGL_Activate2D();          // Enable 2D buffer

   // Activate Texturing on 2D
   glEnable(GL_TEXTURE_2D);  	

   // Draw Large Logo
   glBindTexture(GL_TEXTURE_2D, GdLogoTexId);  	   //Use this ID
   glTexImage2D (
      GL_TEXTURE_2D, 	                           //Type : 2D texture
      0, 	                                       //Mipmap : none
      3, 	                                       //Colors : 3 (24 bits)
      GdLogoTexture.TexWidth,                      //Width
      GdLogoTexture.TexHeight,                     //Height
      0, 	                                       //Border Width
      GL_RGB, 	                                    //Format : BGR
      GL_UNSIGNED_BYTE, 	                        //Color Type
      GdLogoTexture.Texture                        //Pointer to texture
   ); 	
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Draw square which contain logo (thanks to texture) 
	glBegin(GL_QUADS);
      glTexCoord2i(1,0);   glVertex2i(0,0);
		glTexCoord2i(0,0);   glVertex2i(HEADER_SIZE*WinSizeY*2,0);	
		glTexCoord2i(0,1);   glVertex2i(HEADER_SIZE*WinSizeY*2,HEADER_SIZE*WinSizeY);	
		glTexCoord2i(1,1);   glVertex2i(0,HEADER_SIZE*WinSizeY);	
	glEnd();
   
   // Draw Small Logo
   glBindTexture(GL_TEXTURE_2D, PttLogoTexId); 	   //Use this ID
   glTexImage2D (
      GL_TEXTURE_2D, 	                           //Type : 2D texture
      0, 	                                       //Mipmap : none
      3, 	                                       //Colors : 3 (24 bits)
      PttLogoTexture.TexWidth,                     //Width
      PttLogoTexture.TexHeight,                    //Height
      0, 	                                       //Border Width
      GL_RGB, 	                                    //Format : BGR
      GL_UNSIGNED_BYTE, 	                        //Color Type
      PttLogoTexture.Texture                       //Pointer to texture
   ); 	
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Draw square which contain logo (thanks to texture) 
	glBegin(GL_QUADS);
      glTexCoord2i(1,0);   glVertex2i(WinSizeX - HEADER_SIZE*WinSizeY*2,  0);
		glTexCoord2i(0,0);   glVertex2i(WinSizeX,                         0);	
		glTexCoord2i(0,1);   glVertex2i(WinSizeX,                         HEADER_SIZE*WinSizeY);	
		glTexCoord2i(1,1);   glVertex2i(WinSizeX - HEADER_SIZE*WinSizeY*2,  HEADER_SIZE*WinSizeY);	
	glEnd();

   glDisable(GL_TEXTURE_2D);  	

   OpenGL_Desactivate2D();       // Disable 2D buffer
	return IHM_GLUT_NoError;
}


// ------------------------------------------------------------------------------------------
void OpenGL_Activate2D()
{
   glMatrixMode(GL_PROJECTION) ;             // Change matrix mode for viewing
   glLoadIdentity();                         // Init matrix transformation
   gluOrtho2D(0, WinSizeX, WinSizeY, 0);     // Set 2D buffer
   glMatrixMode(GL_MODELVIEW) ;              // Change matrix mode for viewing
   glLoadIdentity() ;                        // Load initial matrix

}

// ------------------------------------------------------------------------------------------
void OpenGL_Desactivate2D()
{
  	glMatrixMode(GL_PROJECTION);												   // Set Matrix Model used
  	glLoadIdentity();																   // Matrix initialisation
  	gluPerspective(60, float(WinSizeX)/float(WinSizeY), 0.1, DEPTH); 	// Set perspective settings
  	glMatrixMode(GL_MODELVIEW); 												   // Set Matrix Model used
}

// ------------------------------------------------------------------------------------------
void ComputeLaserAngle()
{
   LARGE_INTEGER CurrentTime;
   float TmpLaserAngle = 0;

   // Compute new laser angle
   QueryPerformanceCounter(&CurrentTime);   // Read Current time

   // Laser angle is computed with time in us
   TmpLaserAngle = (float)((CurrentTime.QuadPart - TimeLastDraw.QuadPart) * 1000000 / Frequency.QuadPart);  // time in us from last draw
   LaserAngle -= TmpLaserAngle / 1000000 * LaserSpeed * 360;

   while(LaserAngle < 360){   LaserAngle = LaserAngle + 360;   }
   while(LaserAngle >= 360){   LaserAngle = LaserAngle - 360;   }

   // Record time of drawing
   QueryPerformanceCounter(&TimeLastDraw);   // Read Current time
}

// ------------------------------------------------------------------------------------------
void ComputeLaserReflexion()
{
   double BeaconAngle[3] = {0};
	int PointOnBeaconX[2], PointOnBeaconY[2];	// Border Points (used to compute relexion)
	float D, X, Y;										// Discriminant and var to solve 2µ° eq
	float Coef;											// Coef of straight line
	float Sol1, Sol2;									// Solutions for 2° eq
   float LeftBorder, RightBorder;

   LaserDepth = LASER_DEPTH;
   RefPointX = 0;
   RefPointY = 0;

   // Search for collision with beacon
   // Beacon 1
   BeaconAngle[0] = atan2((double)(RobotPosX-PosBeaconBlue[0].x), (PosBeaconBlue[0].y-RobotPosY));
   BeaconAngle[0] = BeaconAngle[0] * 180 / M_PI + 90;

   // Beacon 2
   BeaconAngle[1] = atan2((double)(PosBeaconBlue[1].y-RobotPosY), (PosBeaconBlue[1].x-RobotPosX));
   BeaconAngle[1] = BeaconAngle[1] * 180 / M_PI;

   // Beacon 3
   BeaconAngle[2] = atan2((double)(PosBeaconBlue[2].x-RobotPosX), (RobotPosY-PosBeaconBlue[2].y));
   BeaconAngle[2] = BeaconAngle[2] * 180 / M_PI + 270;

   if((LaserAngle > BeaconAngle[0] - REFLEXION_ANGLE) && (LaserAngle < BeaconAngle[0] + REFLEXION_ANGLE))
   {
      // Compute Angle limite of beacon
      PointOnBeaconX[0] = PosBeaconBlue[0].x + BeaconRayon * cos((BeaconAngle[0] - 90) * M_PI / 180);
      PointOnBeaconY[0] = PosBeaconBlue[0].y + BeaconRayon * sin((BeaconAngle[0] - 90) * M_PI / 180);
		RightBorder = 180 - atan2((PointOnBeaconY[0] - RobotPosY), (RobotPosX - PointOnBeaconX[0])) * 180 / M_PI;
	   while(RightBorder >= 360){   RightBorder = RightBorder - 360;   }

      PointOnBeaconX[1] = PosBeaconBlue[0].x - BeaconRayon * cos((BeaconAngle[0] - 90) * M_PI / 180);
      PointOnBeaconY[1] = PosBeaconBlue[0].y - BeaconRayon * sin((BeaconAngle[0] - 90) * M_PI / 180);
		LeftBorder = 180 - atan2((PointOnBeaconY[1] - RobotPosY), (RobotPosX - PointOnBeaconX[1])) * 180 / M_PI;
	   while(LeftBorder >= 360){   LeftBorder = LeftBorder - 360;   }


	   if((LaserAngle > RightBorder) && (LaserAngle < LeftBorder))
		{
			// Compute length
			LaserDepth = sqrt((RobotPosX - PosBeaconBlue[0].x)*(RobotPosX - PosBeaconBlue[0].x) + (PosBeaconBlue[0].y - RobotPosY)*(PosBeaconBlue[0].y - RobotPosY));
			
			// Compute reflexion point
			// Solve 2° eq
			Coef = -tan((180-LaserAngle)*M_PI/180);
			X = PosBeaconBlue[0].x - RobotPosX;
			Y = PosBeaconBlue[0].y - RobotPosY;

			D = 4*(X+Y*Coef)*(X+Y*Coef) - 4*(1+Coef*Coef)*(Y*Y + X*X - BeaconRayon*BeaconRayon);
			if(D>0)
			{
				// There is one or two solution.
				Sol1 = (2*(X+Y*Coef) + sqrt(D)) / (2*(1+Coef*Coef));
				Sol2 = (2*(X+Y*Coef) - sqrt(D)) / (2*(1+Coef*Coef));
				
				// We keep sol that is between LeftBorder and Right Border
				if(((Sol1 + RobotPosX) > PointOnBeaconX[1]) && ((Sol1 + RobotPosX) < PointOnBeaconX[0]))
				{
					RefPointX = Sol1 + RobotPosX;
					RefPointY = Sol1 * Coef + RobotPosY;
				}

				if(((Sol2 + RobotPosX) > PointOnBeaconX[1]) && ((Sol2 + RobotPosX) < PointOnBeaconX[0]))
				{
					RefPointX = Sol2 + RobotPosX;
					RefPointY = Sol2 * Coef + RobotPosY;
				}
			}
		}
   }
	else if((LaserAngle > BeaconAngle[1] - REFLEXION_ANGLE) && (LaserAngle < BeaconAngle[1] + REFLEXION_ANGLE))
   {
      // Compute Angle limite of beacon
      PointOnBeaconX[0] = PosBeaconBlue[1].x + BeaconRayon * sin(BeaconAngle[1] * M_PI / 180);
      PointOnBeaconY[0] = PosBeaconBlue[1].y - BeaconRayon * cos(BeaconAngle[1] * M_PI / 180);
		RightBorder = atan2((PointOnBeaconY[0] - RobotPosY), (PointOnBeaconX[0] - RobotPosX)) * 180 / M_PI;
	   while(RightBorder >= 360){   RightBorder = RightBorder - 360;   }

      PointOnBeaconX[1] = PosBeaconBlue[1].x - BeaconRayon * sin(BeaconAngle[1] * M_PI / 180);
      PointOnBeaconY[1] = PosBeaconBlue[1].y + BeaconRayon * cos(BeaconAngle[1] * M_PI / 180);
		LeftBorder = atan2((PointOnBeaconY[1] - RobotPosY), (PointOnBeaconX[1] - RobotPosX)) * 180 / M_PI;
	   while(LeftBorder >= 360){   LeftBorder = LeftBorder - 360;   }


	   if((LaserAngle > RightBorder) && (LaserAngle < LeftBorder))
		{
			// Compute length
			LaserDepth = sqrt((PosBeaconBlue[1].x - RobotPosX)*(PosBeaconBlue[1].x - RobotPosX) + (PosBeaconBlue[1].y - RobotPosY)*(PosBeaconBlue[1].y - RobotPosY));
			
			// Compute reflexion point
			// Solve 2° eq
			Coef = tan(LaserAngle*M_PI/180);
			X = PosBeaconBlue[1].x - RobotPosX;
			Y = PosBeaconBlue[1].y - RobotPosY;

			D = 4*(X+Y*Coef)*(X+Y*Coef) - 4*(1+Coef*Coef)*(Y*Y + X*X - BeaconRayon*BeaconRayon);
			if(D>0)
			{
				// There is one or two solution.
				Sol1 = (2*(X+Y*Coef) + sqrt(D)) / (2*(1+Coef*Coef));
				Sol2 = (2*(X+Y*Coef) - sqrt(D)) / (2*(1+Coef*Coef));
				
				// We keep sol that is between LeftBorder and Right Border
				if(((Sol1 + RobotPosX) > PointOnBeaconX[1]) && ((Sol1 + RobotPosX) < PointOnBeaconX[0]))
				{
					RefPointX = Sol1 + RobotPosX;
					RefPointY = Sol1 * Coef + RobotPosY;
				}

				if(((Sol2 + RobotPosX) > PointOnBeaconX[1]) && ((Sol2 + RobotPosX) < PointOnBeaconX[0]))
				{
					RefPointX = Sol2 + RobotPosX;
					RefPointY = Sol2 * Coef + RobotPosY;
				}
			}
		}
   }
   else if((LaserAngle > BeaconAngle[2] - REFLEXION_ANGLE) && (LaserAngle < BeaconAngle[2] + REFLEXION_ANGLE))
   {
      // Compute Angle limite of beacon
		PointOnBeaconX[0] = PosBeaconBlue[2].x - BeaconRayon * cos((BeaconAngle[2]-270) * M_PI / 180);
      PointOnBeaconY[0] = PosBeaconBlue[2].y - BeaconRayon * sin((BeaconAngle[2]-270) * M_PI / 180);
		RightBorder = atan2((PointOnBeaconY[0] - RobotPosY), (PointOnBeaconX[0] - RobotPosX)) * 180 / M_PI;
	   while(RightBorder >= 360)	{   RightBorder = RightBorder - 360;   }
	   while(RightBorder < 0)		{   RightBorder = RightBorder + 360;   }

      PointOnBeaconX[1] = PosBeaconBlue[2].x + BeaconRayon * cos((BeaconAngle[2]-270) * M_PI / 180);
      PointOnBeaconY[1] = PosBeaconBlue[2].y + BeaconRayon * sin((BeaconAngle[2]-270) * M_PI / 180);
		LeftBorder = atan2((PointOnBeaconY[1] - RobotPosY), (PointOnBeaconX[1] - RobotPosX)) * 180 / M_PI;
	   while(LeftBorder >= 360){   LeftBorder = LeftBorder - 360;   }
	   while(LeftBorder < 0)	{   LeftBorder = LeftBorder + 360;   }


	   if((LaserAngle > RightBorder) && (LaserAngle < LeftBorder))
		{
			// Compute length
			LaserDepth = sqrt((RobotPosX - PosBeaconBlue[2].x)*(RobotPosX - PosBeaconBlue[2].x) + (PosBeaconBlue[2].y - RobotPosY)*(PosBeaconBlue[2].y - RobotPosY));
			
			// Compute reflexion point
			// Solve 2° eq
			Coef = tan(LaserAngle*M_PI/180);

			X = PosBeaconBlue[2].x - RobotPosX;
			Y = PosBeaconBlue[2].y - RobotPosY;

			D = 4*(X+Y*Coef)*(X+Y*Coef) - 4*(1+Coef*Coef)*(Y*Y + X*X - BeaconRayon*BeaconRayon);
			if(D>0)
			{
				// There is one or two solution.
				Sol1 = (2*(X+Y*Coef) + sqrt(D)) / (2*(1+Coef*Coef));
				Sol2 = (2*(X+Y*Coef) - sqrt(D)) / (2*(1+Coef*Coef));
				
				// We keep sol that is between LeftBorder and Right Border
            if(sqrt(Sol1*Sol1 + Sol1*Coef * Sol1*Coef) < sqrt(Sol2*Sol2 + Sol2*Coef * Sol2*Coef))
            {
					RefPointX = Sol1 + RobotPosX;
					RefPointY = Sol1 * Coef + RobotPosY;
				}
            else
            {
					RefPointX = Sol2 + RobotPosX;
					RefPointY = Sol2 * Coef + RobotPosY;
				}
			}
		}
   }
}