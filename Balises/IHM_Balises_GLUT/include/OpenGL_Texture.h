/*******************************************************************************************
   File           :  OpenGL_Texture.h
   Authors        :  Fifi_one       (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description    :  Class to manage OpenGL texture 
   History        :
      2008_05_06 (Fifi_one)     : Initial version (C++ dev)

   Dependencies   :
      - OpenGL 
/*******************************************************************************************/

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

// included files
#include <windows.h>
#include <glut.h>
#include <stdio.h>

#include "IHM_GLUT_Error.h"
#include "IHM_BALISES_Config.h"


// Class definition ----------------------------------------------------------------------------
class OpenGL_Texture
{
public:
   // Texture
   GLubyte *Texture;                      // Texture Buffer
   GLsizei TexWidth;                      // Texture Width
   GLsizei TexHeight;                     // Texture Height

   // Constructor / Destructor
   OpenGL_Texture();
   ~OpenGL_Texture();

   // Read Image File
   int LoadFromBmp(const char *PathName);

private:
   FILE *File;                            // File that contains image

   // Read a BMP file
   BITMAPFILEHEADER BmpFileHeader;        // Bmp Header             
   BITMAPINFOHEADER BmpInfoHeader;        // Bmp Header
   unsigned char     *BmpBuf;             // BMP buffer  
   
   
   // Functions
   GLubyte* GetTextureFromBmp();          // Create a texture from a bmp buffer

};



#endif // OPENGL_LOADTEXTURE_H