@echo off

echo --------------- Export des fichiers de config du programme -----------------

copy "..\src\*.bmp" "Release\"
copy "..\src\*.txt" "Release\"

echo ----------------------------- Fin de l'export ----------------------------- 
pause