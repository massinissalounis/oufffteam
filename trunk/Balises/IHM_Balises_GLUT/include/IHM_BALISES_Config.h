/*******************************************************************************************
   File           :  IHM_BALISES_Config.h
   Authors        :  Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  Constants used in project "IHM_BALISES"
   History        :
      2008_04_23 (Fifi_one)     : Initial version

   Dependencies   :
      None
/*******************************************************************************************/

#ifndef IHM_BALISES_CONFIG_H
#define IHM_BALISES_CONFIG_H

// Project Constants ----------------------------------------------------------------------- 
#define WIDTH				800			// Screen Width
#define HEIGHT				600			// Screen Height
#define DEPTH				10000			// Perspective Limit for display (in mm)
#define AXIS_SIZE			1000			// Axis Size
#define VISUAL_CIRCLE	2000			// Radius of visual circle
#define LENGTH_TO_SCENE	3000			// Length between cam and scene 
#define HEIGHT_TO_SCENE	1000			// Height between cam and scene 

#define R_ROBOT			150			// Robot radius  
#define HEIGHT_ROBOT		300			// Robot height  

#define R_LASER			10			   // Support Laser radius
#define HEIGHT_LASER		470			// Laser Height 
#define LASER_SPEED		1			   // Laser speed in round per sec  
#define LASER_ALPHA		128		   // Laser transparency between 0 and 255
#define REFLEXION_ANGLE 5	   	   // Reflexion angle in degree
#define LASER_DEPTH     10000       // Laser Depth max 

#define START_POS_X	   150			// Robot Start PosX
#define START_POS_Y		150			// Robot Start PosY
#define START_POS_ANGLE	0				// Robot Start Angle

#define HEADER_SIZE     0.15        // Header size (in % of screen) 

#define T_STEP				5				// Step (in mm) to move cam
#define R_STEP				0.8			// Step (in degree) to rotate cam

#define AXIS_X				1				// Permits to identifie X axis
#define AXIS_Y				2				// Permits to identifie Y axis
#define AXIS_Z				3				// Permits to identifie Z axis


#define RS232_PATTERN	"@%d,%d,%d#"		// Pattern use to read RS232 data


#define M_PI 3.14159265358979323846 

// OpenGL_Object Class --------------------------------------------------------------------- 
// Object Type :
#define OPENGL_OBJECT_NONE             0
#define OPENGL_OBJECT_LINE             1
#define OPENGL_OBJECT_TRIANGLE         2
#define OPENGL_OBJECT_SQUARE           3
#define OPENGL_OBJECT_CYLINDER         4
#define OPENGL_OBJECT_CIRCLE           5
#define OPENGL_OBJECT_INFO_MAPSIZE     6
#define OPENGL_OBJECT_INFO_BEACON      7
#define OPENGL_OBJECT_AXIS             8
#define OPENGL_OBJECT_CAM_POS          9

#define OPENGL_MAX_OBJECT_TO_DRAW     50


#endif // IHM_BALISES_CONFIG_H
