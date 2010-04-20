# Microsoft Developer Studio Project File - Name="Oufff_Lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Oufff_Lib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Oufff_Lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Oufff_Lib.mak" CFG="Oufff_Lib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Oufff_Lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Oufff_Lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Oufff_Lib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=ExportDll.bat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Oufff_Lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Oufff_Lib - Win32 Release"
# Name "Oufff_Lib - Win32 Debug"
# Begin Group "Modules"

# PROP Default_Filter ""
# Begin Group "Oufff_RS232"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\Oufff_RS232\Oufff_RS232.cpp
# End Source File
# Begin Source File

SOURCE=..\include\Oufff_RS232.h
# End Source File
# End Group
# Begin Group "Oufff_ConfigFile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\Oufff_ConfigFile\Oufff_ConfigFile.cpp
# End Source File
# Begin Source File

SOURCE=..\include\Oufff_ConfigFile.h
# End Source File
# End Group
# End Group
# Begin Group "Project Source"

# PROP Default_Filter ""
# End Group
# Begin Group "Project Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\Oufff_Lib.h
# End Source File
# Begin Source File

SOURCE=..\include\Oufff_LibConfig.h
# End Source File
# Begin Source File

SOURCE=..\include\Oufff_LibErrorCode.h
# End Source File
# Begin Source File

SOURCE=.\version.win
# End Source File
# End Group
# End Target
# End Project
