using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.FileManager
{
    interface IFile
    {
        /// <summary>
        /// Charge un fichier texte dont le nom est contenu dans 'fileName'
        /// </summary>
        /// <param name="fileName">Chemin d'accès au fichier</param>
        /// <returns>Nombre de lignes chargées (-1 en cas d'erreur)</returns>
        int Load(String fileName);

        /// <summary>
        /// Enregistre le contenu du fichier dans le nom de fichier précédemment utilisé
        /// </summary>
        /// <returns>Nombre de lignes écrites (-1 en cas d'erreur)</returns>
        int Save();

        /// <summary>
        /// Enregistre un fichier texte au chemin d'accès 'newFileName'. 
        /// Une fois le fichier enregisté le nom de fichier 'newFileName' utilisé est mis à jour
        /// </summary>
        /// <param name="fileName">Chemin d'accès au fichier</param>
        /// <returns>Nombre de lignes écrites (-1 en cas d'erreur)</returns>
        int SaveTo(String newFileName);
    }
}
