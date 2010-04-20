@echo off

echo -------------------- Export de la DLL dans la OufffLib --------------------

if "%OUFFFLIB_PATH%"=="" goto NoOufffLib 

if exist version.win (goto FileExists) else goto ErrFile 

rem File "version.win" exists and we read it to retreive info about current DLLVERSION
:FileExists

for /f "tokens=1 delims=# " %%a in ('TYPE version.win') do set DLLVERSION=%%a

rem Export des fichiers .dll, .lib et .h
for %%f IN (Release/*.dll) DO set DLLNAME=%%f

rem On enlève l'extension 
set DLLNAME=%DLLNAME:~0,-4%

rem On copie
echo Export du fichier %DLLNAME%.dll vers %DLLNAME%-%DLLVERSION%.dll :
copy "Release\%DLLNAME%.dll" "%OUFFFLIB_PATH%W32\%DLLNAME%-%DLLVERSION%.dll"

echo Export du fichier %DLLNAME%.lib vers %DLLNAME%-%DLLVERSION%.lib :
copy "Release\%DLLNAME%.lib" "%OUFFFLIB_PATH%W32\%DLLNAME%-%DLLVERSION%.lib"

echo Export du fichier %DLLNAME%.h vers %DLLNAME%-%DLLVERSION%.h :
copy "..\include\%DLLNAME%.h" "%OUFFFLIB_PATH%Include\W32\%DLLNAME%-%DLLVERSION%.h"

echo Mise à jours des fichiers de bases...
echo Création et copie des fichiers %DLLNAME%.dll, %DLLNAME%.lib et %DLLNAME%.h

copy "Release\%DLLNAME%.dll" "%OUFFFLIB_PATH%W32\%DLLNAME%.dll"
copy "Release\%DLLNAME%.lib" "%OUFFFLIB_PATH%W32\%DLLNAME%.lib"
copy "..\include\%DLLNAME%.h" "%OUFFFLIB_PATH%Include\W32\%DLLNAME%.h"

goto End

rem Nous n'avons pas le fichier contenant la version de la DLL on arrête l'export
:ErrFile
echo Le fichier "version.win" n'est pas présent dans le workspace. Export impossible
goto End

rem Nous n'avons pas installé la OufffLib sur le PC
:NoOufffLib
echo La OufffLib n'est pas installée (ou abimée) sur ce PC. Export impossible !
goto End

:End
echo ----------------------------- Fin de l'export ----------------------------- 
pause