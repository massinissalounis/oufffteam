/*******************************************************************************************
   File           :  Main.cpp
   Authors        :  Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  HMI to display position found thanks to detectors 
   History        :
      2008_04_23 (Fifi_one)     : Initial version (C++ dev)

   Dependencies   :
      - OpenGL 
/*******************************************************************************************/

// included files
#include <windows.h>
#include <glut.h>

#include "Affichage.h"
#include "IHM_GLUT_Error.h"
#include "OpenGL_Object.h"
#include "Oufff_Lib.h"
#include "OpenGL_Texture.h"

// Global
int WindowName;
extern OpenGL_Object Map;
extern OpenGL_Object Beacon;
extern OpenGL_Object Axis;

// Extern variable to set new Robot Position
extern int RobotPosX;
extern int RobotPosY;
extern int RobotSize;
extern int RobotHeight;
extern int RobotPosAngle;
extern int LaserHeight;
extern bool MutexPos;			// Mutex to block reading when other module is wrinting
extern float LaserSpeed;
extern float LaserAlpha;
extern int DisplayFreq;

// Use Configuration File
Oufff_ConfigFile Config;


// RS232 Thread
DWORD WINAPI RS232_Thread(LPVOID ThreadParam);
int RS232_Simulation();                            // Function to simulate RS232 comm
int RS232_Status;
bool RS232_StopThread;

int main( int argc, char **argv)
{

	HANDLE PtrThreadRS232;
	DWORD ThreadId;
	char *MapFileName = NULL;
	char *BeaconFileName = NULL;
	char *AxisFileName = NULL;
	int UseConsole = 1;
   int FullScreen = 0;


	// Open config File
	Config.OpenFile("Config_IHM_Balises_GLUT.txt");

	// Read file config to get all values
	if(OUFFF_LIB_NOERR != Config.GetValue("MapFile", &MapFileName))
	{
		// Unable to read MapFile
		printf("Impossible de charger la Map. Arret du programme.\n");
		return 1;
	}
	printf(" Chargement de la Map : Fichier '%s' correctement charge\n", MapFileName);

  	Config.GetValue("BeaconFile", &BeaconFileName);
  	Config.GetValue("AxisFile", &AxisFileName);

	if(OUFFF_LIB_NOERR != Config.GetValue("RobotSize", &RobotSize))
	{
		RobotSize = R_ROBOT;
	}

	if(OUFFF_LIB_NOERR != Config.GetValue("RobotHeight", &RobotHeight))
	{
		RobotHeight = HEIGHT_ROBOT;
	}

	if(OUFFF_LIB_NOERR != Config.GetValue("UseConsole", &UseConsole))
	{
		printf("Impossible de lire la variable UseConsole. Desactivation.\n");
	}

	if(OUFFF_LIB_NOERR != Config.GetValue("FullScreen", &FullScreen))
	{
		FullScreen = 0;
	}

   if(OUFFF_LIB_NOERR != Config.GetValue("LaserSpeed", &LaserSpeed))
	{
		LaserSpeed = LASER_SPEED;
	}

   if(OUFFF_LIB_NOERR != Config.GetValue("LaserHeight", &LaserHeight))
	{
		LaserSpeed = HEIGHT_LASER;
	}

   if(OUFFF_LIB_NOERR != Config.GetValue("DisplayFreq", &DisplayFreq))
	{
		DisplayFreq = 40;
	}

   if(OUFFF_LIB_NOERR != Config.GetValue("LaserAlpha", &LaserAlpha))
	{
		LaserAlpha = LASER_ALPHA;
	}
   LaserAlpha = LaserAlpha / 255;

   if(0 == UseConsole){			FreeConsole();		}

	// Load Map
   Map.LoadObjFromFile(MapFileName);

   // LoadBeacon
   if(BeaconFileName != NULL)
      Beacon.LoadObjFromFile(BeaconFileName);

   // Load Axis
   if(AxisFileName != NULL)
      Axis.LoadObjFromFile(AxisFileName);

   // Delete unusable pointer
   if(AxisFileName != NULL)   {     delete AxisFileName;    AxisFileName = NULL;    }
   if(MapFileName != NULL)    {     delete MapFileName;     MapFileName = NULL;     }
   if(BeaconFileName != NULL) {     delete BeaconFileName;  BeaconFileName = NULL;  }

	// Init variables
	RobotPosX = START_POS_X;
	RobotPosY = START_POS_Y;
	RobotPosAngle = START_POS_ANGLE;
	MutexPos = false;

	// Start RS232 thread
	RS232_StopThread = false;
	RS232_Status = IHM_GLUT_THREAD_INIT;
	
	PtrThreadRS232 = CreateThread(0, 0, RS232_Thread, NULL, 0, &ThreadId);

	if(NULL == PtrThreadRS232)
	{
		printf("Impossible de creer le thread de communication... Fin du programme !\n");
	}

	while(IHM_GLUT_THREAD_INIT == RS232_Status){		Sleep(1);	}

	// Init de OpenGL
 	glutInit(&argc, argv);							
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	
	// Window creation
	WindowName = glutCreateWindow("OufffTeam : Suivi du robot via balises");
   
   if(1 == FullScreen)
   {
      glutFullScreen();		// Use this option to display on full screen
   }

	// Register functions 
	glutReshapeFunc(OpenGL_Reshape);							// When window is resized
	glutDisplayFunc(OpenGL_Draw);								// When window is refreshed
   glutKeyboardFunc(OpenGL_Keyboard);						// When a key is pressed
	glutMouseFunc(OpenGL_Mouse);								// When button mouse is pressed
	glutMotionFunc(OpenGL_MouseOnScreen);					// When mouse is used with button pressed

	glutMainLoop();		// Wait for OpenGL end signal


	// Terminating thread
	RS232_StopThread = true;

	while(IHM_GLUT_THREAD_RUNNING == RS232_Status){		Sleep(1);	}

	if(NULL != PtrThreadRS232)
	{
		CloseHandle(PtrThreadRS232);
	}


	// Delete data
	if(NULL != MapFileName)		{	delete [] MapFileName;		MapFileName = NULL;		}
	Config.CloseFile();

	return 0;
}


DWORD WINAPI RS232_Thread(LPVOID ThreadParam)
{
	char Buffer[1024];
   char *RS232Pattern;
	int DataReceived;
	int Value1, Value2, Value3;
	int PortNumber = -1;
	int PortSpeed = -1;

	// Read config file to know which port use
	if(OUFFF_LIB_NOERR != Config.GetValue("COM", &PortNumber))
	{
		// Unable to read MapFile
		printf("Impossible d'ouvrir le port série. Arret du programme.\n");
		RS232_Status = IHM_GLUT_THREAD_ERR_RS232;
		return IHM_GLUT_THREAD_ERR_RS232;
	}

	if(OUFFF_LIB_NOERR != Config.GetValue("PortSpeed", &PortSpeed))
	{
		// Unable to read MapFile
		printf("Impossible d'ouvrir le port série. Arret du programme.\n");
		RS232_Status = IHM_GLUT_THREAD_ERR_RS232;
		return IHM_GLUT_THREAD_ERR_RS232;
	}

	if(OUFFF_LIB_NOERR != Config.GetValue("TrameRS232", &RS232Pattern))
	{
		// Unable to read MapFile
		printf("Impossible de déterminer le model de trame utilise. Arret du programme.\n");
		RS232_Status = IHM_GLUT_THREAD_ERR_RS232;
		return IHM_GLUT_THREAD_ERR_RS232;
	}

   if(0 == PortNumber)
	{
		printf("Le port RS232 a ete desactive.\n");
		RS232_Status = IHM_GLUT_THREAD_TERMINATE;
		return IHM_GLUT_THREAD_TERMINATE;
	}

   if(-1 == PortNumber)
   {
		printf("Mode simulation RS232 active.\n");
      RS232_Status = IHM_GLUT_THREAD_RUNNING;
      RS232_Simulation();
      RS232_Status = IHM_GLUT_THREAD_TERMINATE;
		return IHM_GLUT_THREAD_TERMINATE;
   }      

	// RS232 Init
	Oufff_RS232 RS232Port;
	if(OUFFF_LIB_NOERR != RS232Port.OpenPort(PortNumber, PortSpeed))
	{
		RS232Port.ClosePort();

		RS232_Status = IHM_GLUT_THREAD_ERR_RS232;
		return IHM_GLUT_THREAD_ERR_RS232;
	}

	printf(" RS232 ouvert sur COM%d a la vitesse de :%d\n", PortNumber, PortSpeed);

	RS232_Status = IHM_GLUT_THREAD_RUNNING;

	// Main function of thread
	while(false == RS232_StopThread)
	{
		// If we received data from port
		if(OUFFF_LIB_NOERR == RS232Port.Receive(Buffer, &DataReceived))
		{
			if(DataReceived > 0)
			{
				// Checking if received string is correct
				if(3 == sscanf(Buffer, RS232Pattern, &Value1, &Value2, &Value3))
				{
					// Registering values
					MutexPos = true;
						RobotPosX = Value1;
						RobotPosY = Value2;
						RobotPosAngle = Value3;
						printf("Trame lue : %d\t%d\t%d\n", RobotPosX, RobotPosY, RobotPosAngle);
					MutexPos = false;
				}
			}
		}
		Sleep(1);
	}

   if(NULL != RS232Pattern)
   {
      delete [] RS232Pattern;
      RS232Pattern = NULL;
   }

	// Closing port
	RS232Port.ClosePort();

	RS232_Status = IHM_GLUT_THREAD_TERMINATE;
	return IHM_GLUT_THREAD_TERMINATE;
}



int RS232_Simulation()
{
   FILE *SimulFile = NULL;
   char ReadLine[1024];

   int PosX[100];     // We can simulate only 100 pos
   int PosY[100];     // We can simulate only 100 pos
   int PosA[100];     // We can simulate only 100 pos

   int CurrentPos = 0;
   int NbPos = 0;

   // Read Simulation file
   SimulFile = fopen("RS232SimulationFile.txt", "r");

   if(NULL == SimulFile)
   {
      // ERR
      return -1;
   }

   while(NULL != fgets(ReadLine, 256, SimulFile))
   {
      // If it's a commentary line, i don't read it
		if(NULL == strstr(ReadLine, "//"))
      {
         // I register only 100 pos
         if(CurrentPos < 100)
         {
            if(sscanf(ReadLine, "%d %d %d", &PosX[CurrentPos], &PosY[CurrentPos], &PosA[CurrentPos])==3)
            {
               // Data read are correct, I register this pos
               CurrentPos++;
            }
         }
      }
   }

   fclose(SimulFile);

   // LastPos is not valable
   NbPos = CurrentPos - 1;
   CurrentPos = 0;

	while(false == RS232_StopThread)
	{
      // Simlate : Waiting data from RS232
      Sleep(1000);
      if(CurrentPos < NbPos)
      {
		   // Registering values
		   MutexPos = true;
			   RobotPosX = PosX[CurrentPos];
			   RobotPosY = PosY[CurrentPos];
			   RobotPosAngle = PosA[CurrentPos];
			   printf("Trame lue : %d\t%d\t%d\n", RobotPosX, RobotPosY, RobotPosAngle);
		   MutexPos = false;

         CurrentPos++;
      }
      else
      {
         CurrentPos = 0;
      }
   }
   return 0;
}
