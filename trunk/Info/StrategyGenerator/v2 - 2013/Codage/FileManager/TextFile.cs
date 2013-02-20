using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using StrategyGenerator2.Tools;

namespace StrategyGenerator2.FileManager
{
    public class TextFile:IFile
    {
        // Constructeur ---------------------------------------------------------------------------
        ///<summary>
        /// Initialisation d'un objet vide
        ///</summary>
        public TextFile()
        {
            // Clear current content
            _fileContents = null;
            _currentFileName = null;
            _debugTool = new DebugTool(DebugTool.EDebugToolType.Disabled);
        }

        // Properties -----------------------------------------------------------------------------
        public int Count
        {
            get
            {
                if (_fileContents == null)
                    return 0;
                else
                    return _fileContents.Count;
            }
        }
            

        // Public ---------------------------------------------------------------------------------
        /// <summary>
        /// Charge un fichier texte dont le nom est contenu dans 'fileName'
        /// </summary>
        /// <param name="fileName">Chemin d'accès au fichier</param>
        /// <returns>Nombre de lignes chargées (-1 en cas d'erreur)</returns>
        public int Load(String fileName)
        {
            int Ret = -1;   // Valeur de retour

            if ("" == fileName)
                return -1;

            try
            {
                // Create object for storing line
                _fileContents = new List<String>();

                // Création d'une instance de StreamReader pour permettre la lecture de notre fichier 
                StreamReader monStreamReader = new StreamReader(fileName, Encoding.Default);

                while (monStreamReader.EndOfStream != true)
                {
                    _fileContents.Add(monStreamReader.ReadLine());
                }

                // Fermeture du StreamReader (attention très important) 
                monStreamReader.Close();
            }
            catch (Exception ex)
            {
                _fileContents = null;
                _currentFileName = null;
                _debugTool.WriteLine("TextFile = " + ex.Message);
                return -1;
            }

            // Le fichier a été correctement lu
            _currentFileName = fileName;
            Ret = _fileContents.Count;

            return Ret;
        }

        /// <summary>
        /// Enregistre le contenu du fichier dans le nom de fichier précédemment utilisé
        /// </summary>
        /// <returns>Nombre de lignes écrites (-1 en cas d'erreur)</returns>
        public int Save()
        {
            return SaveTo(_currentFileName);
        }

        /// <summary>
        /// Enregistre un fichier texte au chemin d'accès 'newFileName'. 
        /// Une fois le fichier enregisté le nom de fichier 'newFileName' utilisé est mis à jour
        /// </summary>
        /// <param name="fileName">Chemin d'accès au fichier</param>
        /// <returns>Nombre de lignes écrites (-1 en cas d'erreur)</returns>
        public int SaveTo(String fileName)
        {
            int Ret = -1;

            try
            {
                if ((fileName == null) || (fileName == ""))
                {
                    _debugTool.WriteLine("TextFile (SaveTo) : Nom de fichier invalide");
                    return Ret;
                }

                if (contentIsValid() == false)
                {
                    _debugTool.WriteLine("TextFile (SaveTo) : Pas de données à sauvegarder");
                    return Ret;
                }

                // Instanciation du StreamWriter avec passage du nom du fichier 
                StreamWriter monStreamWriter = new StreamWriter(fileName, false, Encoding.Default);

                //Ecriture du texte dans votre fichier
                for (int i = 0; i < _fileContents.Count(); i++)
                {
                    monStreamWriter.WriteLine(_fileContents[i]);
                }

                // Fermeture du StreamWriter 
                monStreamWriter.Close();
            }
            catch (Exception ex)
            {
                // Code exécuté en cas d'exception 
                throw ex;
            }

            // Le fichier a été écrit. On garde le nom de fichier
            _currentFileName = fileName;
            Ret = _fileContents.Count();
            return Ret;
        }

        /// <summary>
        /// Permet de récupérer la ligne numéro 'lineNumber'
        /// </summary>
        /// <param name="lineNumber">Numéro de la ligne à lire (de 0 à MaxLine-1)</param>
        /// <returns>Retourne la ligne au format string (null en cas d'erreur)</returns>
        public String GetLine(int lineNumber)
        {
            String Ret = null;

            // Verification du fichier courant
            if (contentIsValid() == false)
            {
                _debugTool.WriteLine("TextFile (GetLine) : Fichier vide, pas de ligne disponible");
                return Ret;
            }

            // Verification des paramètres d'entrée
            if ((lineNumber < 0) || (lineNumber >= _fileContents.Count))
            {
                _debugTool.WriteLine("TextFile (GetLine) : Numéro de ligne invalide");
                return Ret;
            }

            return _fileContents[lineNumber];
        }

        /// <summary>
        /// Ajoute une ligne à la fin du fichier
        /// </summary>
        /// <param name="lineToAdd">Ligne à ajouter</param>
        public void AddLine(String lineToAdd)
        {
            if (lineToAdd != null)
            {
                if (_fileContents == null)
                    _fileContents = new List<string>();

                _fileContents.Add(lineToAdd);
            }
        }

        /// <summary>
        /// Ajoute une ligne à la position spécfiée
        /// </summary>
        /// <param name="lineToAdd">Ligne à ajouter</param>
        /// <param name="indexToAdd">Index de la ligne à ajouter (entre 0 et MaxLine)</param>
        public void AddLine(String lineToAdd, int indexToAdd)
        {
            // Verification des paramètres d'entrée
            if ((lineToAdd != null) && (indexToAdd >= 0))
            {
                if (_fileContents == null) // Dans le cas où le fichier est vide
                {
                    AddLine(lineToAdd);
                }
                else // Si le fichier n'est pas vide
                {
                    // Verification si l'index est valide
                    if (indexToAdd < (_fileContents.Count - 1))
                        _fileContents.Insert(indexToAdd, lineToAdd);
                    else
                    {   // Si l'index n'est pas valide, on l'ajoute à la fin
                        AddLine(lineToAdd);
                    }
                }
            }
            else
            {   // Ligne non valide
                _debugTool.WriteLine("TextFile (AddLine) : Paramètre d'entrée non valide");
            }
        }

        public void RemoveLine(int indexToRemove)
        {
            // Verification de la structure du fichier
            if(_fileContents == null)
            {
                _debugTool.WriteLine("TextFile (RemoveLine) : Impossible de supprimer la ligne, le fichier est vide");
            }
            else
            {
                // Verification des paramètres d'entrée
                if ((indexToRemove >= 0) && (indexToRemove < _fileContents.Count()))
                {
                    _fileContents.RemoveAt(indexToRemove);
                }
                else
                {   // Ligne non valide
                    _debugTool.WriteLine("TextFile (RemoveLine) : Paramètre d'entrée non valide");
                }
            }
        }

        public void RemoveAllLine()
        {
            // Verification de la structure du fichier
            if (_fileContents == null)
            {
                _debugTool.WriteLine("TextFile (RemoveAllLine) : Impossible de supprimer, le fichier est vide");
            }
            else
            {
                _fileContents.Clear();
            }
        }
        
        // Private --------------------------------------------------------------------------------
        private List<String>    _fileContents;              // Permet de stocker le contenu du fichier
        private String          _currentFileName;           // Permet de stocker le chemin d'accès courrant
        private DebugTool       _debugTool;                 // Outil pour contrôler les informations de débug 

        private bool contentIsValid()
        {
            bool Ret = false;

            if ((_fileContents != null) && (_fileContents.Count > 0))
                Ret = true;

            return Ret;
        }   
    }
}
