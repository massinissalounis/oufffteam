/*******************************************************************************************
   File           :  Affichage.h
   Authors        :  Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  Functions to draw on OpenGL window 
   History        :
      2008_04_23 (Fifi_one)     : Initial version (C++ dev)

   Dependencies   :
      - OpenGL 
/*******************************************************************************************/

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

// included files
#include <windows.h>
#include <glut.h>
#include <stdio.h>
#include <math.h>

#include "IHM_GLUT_Error.h"
#include "IHM_BALISES_Config.h"
#include "OpenGL_Object.h"
#include "OpenGL_Texture.h"



// Functions -------------------------------------------------------------------------------------------------------
int OpenGL_Init();													// Function to initialize OpenGL
void OpenGL_Reshape(int width, int height);					// Function called when window is resized
void OpenGL_Draw();													// Function to draw scene on screen
int OpenGL_CreateMap();                                  // Function to create OpenGL list to draw Map
int OpenGL_CreateRobot();                                // Function to create OpenGL list to draw Robot
int OpenGL_DrawObject(OpenGL_Object *ObjToDraw);			// Draw all objects pointed by ObjToDraw

void OpenGL_Keyboard(unsigned char key, int x, int y);	// Function called when a key is pressed by user
void OpenGL_Mouse(int button, int state, int x, int y);	// Function called when mouse button is pressed
void OpenGL_MouseOnScreen(int x, int y);						// Function called when mouse is moved with a button pressed

int OpenGL_Translate(int Tx, int Ty, int Tz);				// Translate current scene with vector (Tx, Ty, Tz) into Map space
int OpenGL_Rotate(int Angle, short Axis);						// Rotate current scene with angle around Axis
int OpenGL_SetCamPos(int Tx, int Ty, int Tz);				// Set Cam position 
int OpenGL_SetCamRot(int Angle, short Axis);					// Set Cam rotation around Axis

int OpenGL_DrawHeader();											// Draw control pannel on the top of the screen
int OpenGL_WriteText2D(int x, int y, char* Text);			// Write Text at (x,y)
int OpenGL_DrawLogo();			                           // Draw logo 

void OpenGL_Activate2D();                                // Function to activate 2D draw on 3D buffer (to draw header)
void OpenGL_Desactivate2D();                             // Function to desactivate 2D draw on 3D buffer 

void ComputeLaserAngle();                                // Function to compute Laser Angle
void ComputeLaserReflexion();                            // Function co compute Laser Reflexion
#endif // AFFICHAGE_H