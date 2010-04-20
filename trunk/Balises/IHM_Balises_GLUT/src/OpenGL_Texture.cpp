/*******************************************************************************************
      File           :  OpenGL_Texture.cpp
      See details on :  OpenGL_Texture.h
      Authors        :  Fifi_one    (philippe.bechet@cpe.fr)
      Team           :  OUFFF TEAM
/*******************************************************************************************/

#include "OpenGL_Texture.h"


// ------------------------------------------------------------------------------------------
OpenGL_Texture::OpenGL_Texture()
{
   BmpBuf = NULL;
   Texture = NULL;
   TexWidth = 0;                     
   TexHeight = 0;                     
}

// ------------------------------------------------------------------------------------------
OpenGL_Texture::~OpenGL_Texture()
{
   // If buffers are not null, I delete them
   // Delete BMP Buffer
   if(NULL != BmpBuf)
   {
      delete [] BmpBuf;
   }

   // Delete Texture Buffer
   if(NULL != Texture)
   {
      delete [] Texture;
   }
}

// ------------------------------------------------------------------------------------------
int OpenGL_Texture::LoadFromBmp(const char *PathName)
{
   if(NULL == PathName)
   {
      return IHM_GLUT_ERR_NOTENOUGHTPARAM;
   }

   // Open File
   File = fopen(PathName, "rb");
   if(NULL == File)
   {
      // Unable to read specified file
      return IHM_GLUT_ERR_OPEN_FILE;
   }

   // Read BMP file header
   fread (&BmpFileHeader, sizeof (BITMAPFILEHEADER), 1, File);
   fread (&BmpInfoHeader, sizeof (BITMAPINFOHEADER), 1, File);

   // I get image size so I can create buffer
   BmpBuf = new unsigned char[BmpInfoHeader.biSizeImage];
   memset(BmpBuf, 0, BmpInfoHeader.biSizeImage);

   fread (BmpBuf, 1, BmpInfoHeader.biSizeImage, File);

   fclose(File);

   // Load Texture
   Texture = GetTextureFromBmp();
   if(NULL != Texture)
   {
      TexHeight = BmpInfoHeader.biHeight;
      TexWidth = BmpInfoHeader.biWidth;
   }

   return IHM_GLUT_NoError;
}

// ##########################################################################################
// Private functions
// ##########################################################################################

GLubyte* OpenGL_Texture::GetTextureFromBmp()
{
   GLubyte* NewTexBuf = NULL;

   // Check if Bmp buffer is set
   if(NULL == BmpBuf)
   {
      return NULL;
   }

   // Allocate Texture buffer
   NewTexBuf = new GLubyte [BmpInfoHeader.biSizeImage];
   memset(NewTexBuf, 0, BmpInfoHeader.biSizeImage);

   for(int i=0; i<(int)BmpInfoHeader.biSizeImage; i=i+3)
   {
      // Copy buffer and make data in correct sens
      // Image is stored in RGB and it's used in BGR and It's necessary to flip and revert texture
      // Copy Red component
      *(NewTexBuf + i + 2) = *(BmpBuf + BmpInfoHeader.biSizeImage - 1 - i);  

      // Copy Green component
      *(NewTexBuf + i + 1) = *(BmpBuf + BmpInfoHeader.biSizeImage - 1 - i - 1);  

      // Copy Blue component
      *(NewTexBuf + i + 0) = *(BmpBuf + BmpInfoHeader.biSizeImage - 1 - i - 2);  
   }

   return NewTexBuf;
}
