#! /bin/sh

# Variables
Cpt=0

# Clear screen
clear
echo "Lecture du répertoire \"$(pwd)\""
echo " "
echo " Lib trouvées dans ce répertoire :"

# Read the current file
for FILES in `find *.so.*` ; do
   let $[Cpt+=1]
   echo "   $Cpt) $FILES"
   Tab[$Cpt]=$FILES
done

echo " "
echo -n " Selectionner la lib à activer par défaut (0 pour quitter) : "
read LibDefaut

if (($LibDefaut != 0)) && (($LibDefaut < $(($Cpt+1)))); then
   # Recherche du nom de la lib (on enleve l'extension)
   LgNomLib=$(expr index ${Tab[$LibDefaut]} .so.)
   NomLib=${Tab[$LibDefaut]}
   Version=${NomLib:$(($LgNomLib+5))}
   NomLib=${NomLib:0:$(($LgNomLib+1))}
   
   # Suppression des liens existant
   rm -f "$NomLib.so"
   rm -f "../Include/Linux/$NomLib.h"
   
   echo " "
   echo "   Lib choisie : \"${Tab[$LibDefaut]}\""
   echo "   Creation des liens "
   
   # Gestion du fichier .so
   echo -n "      $NomLib.so -> ${Tab[$LibDefaut]} : "
   
   if $(ln -s ${Tab[$LibDefaut]} $NomLib.so); then
      echo "ok"
   else
      echo "ERREUR !!"
   fi

   # Gestion du fichier .h
   echo -n "      ../Include/Linux/$NomLib-$Version.h -> ../Include/Linux/${Tab[$LibDefaut]} : "
   
   cd ../Include/Linux/
   if $(ln -s $NomLib-$Version.h $NomLib.h); then
      echo "ok"
   else
      echo "ERREUR !!"
   fi
   
else
   echo " "
   echo "Annulation... Fin du script."
   echo " "
fi