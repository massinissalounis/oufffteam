using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using StrategyGenerator2.Tools;

namespace StrategyGenerator2.FileManager
{
    public class StructuredFile : IFile
    {
        // Constructor ----------------------------------------------------------------------------
        public StructuredFile()
        {
            _patternFile = null;
            _group = null;
            _debugTool = new DebugTool(DebugTool.EDebugToolType.Disabled);
        }

        public StructuredFile(String patternFileName)
        {
            _debugTool = new DebugTool(DebugTool.EDebugToolType.Disabled);
            _group = null;
            _patternFile = new TextFile();
            if (_patternFile.Load(patternFileName) <= 0)
            {
                _debugTool.WriteLine("StructuredFile = Invalid patternFile");
                _patternFile = null;
            }
        }

        // Properties -----------------------------------------------------------------------------

        // Public ---------------------------------------------------------------------------------
        /// <summary>
        /// Fonction pour charger un fichier pattern pour l'import ou l'export des données
        /// </summary>
        /// <param name="patternFileName">Nom du fichier modèle</param>
        /// <returns>Le nombre de lignes lues (-1 en cas d'erreur)</returns>
        public int SetPatternFile(String patternFileName)
        {
            int Ret = -1;
            TextFile fileToLoad = null;

            // Desallocation des données déjà chargées
            if (_patternFile != null)
            {
                _patternFile.RemoveAllLine();
                _patternFile = null;
            }

            if (patternFileName != null)
            {
                // Lecture du fichier pattern
                fileToLoad = new TextFile();
                fileToLoad.Load(patternFileName);

                Ret = SetPatternFile(fileToLoad);
            }
 
            return Ret;
        }

        /// <summary>
        /// Fonction pour charger un fichier pattern pour l'import ou l'export des données
        /// </summary>
        /// <param name="newPatternFile">FIchier pattern à charger</param>
        /// <returns>Le nombre de lignes lues (-1 en cas d'erreur)</returns>
        public int SetPatternFile(TextFile newPatternFile)
        {
            int Ret = -1;

            // Desallocation des données déjà chargées
            if (_patternFile != null)
            {
                _patternFile.RemoveAllLine();
                _patternFile = null;
            }

            if (newPatternFile != null)
            {
                _patternFile = newPatternFile;
                Ret = _patternFile.Count();
            }

            return Ret;

        }
        
        /// <summary>
        /// Charge un fichier structuré à partir d'un nom de fichier
        /// </summary>
        /// <param name="fileName">Nom du fichier à charger</param>
        /// <returns>Le nombre de groupe chargé (-1 en cas d'erreur)</returns>
        public int Load(String fileName)
        {
            int Ret = -1;
            TextFile inputFile = null;

            // Verification des paramètres d'entrée
            if (fileName != null)
            {
                // Ouverture du fichier selectionné
                inputFile = new TextFile();
                if (inputFile.Load(fileName) > 0)
                    Load(inputFile);
            }

            return Ret;
        }


        /// <summary>
        /// Charge un fichier structuré à partir d'un fichier texte
        /// </summary>
        /// <param name="fileName">Fichier à charger</param>
        /// <returns>Le nombre de groupe chargé (-1 en cas d'erreur)</returns>
        public int Load(TextFile fileToLoad)
        {
            int Ret = -1;
            int currentIndex = 0;
            String currentLine = null;
            String parsedLine = null;
            String currentKeyName = null;
            String currentKeyValue = null;
            uint currentGroupID = 0;
            StructuredFileGroup currentGroup = null;
            List<StructuredFileGroup> groupToAdd = null;

            // Verification des params d'entrée
            if (fileToLoad != null)
            {
                // Lecture du fichier ligne à ligne
                for (int i = 0; i < fileToLoad.Count(); i++)
                {
                    currentLine = fileToLoad.GetLine(i);
                    if (currentLine != null)
                    {
                        // Analyse de la ligne lue
                        // Est-ce une ligne d'entête
                        if (currentLine.Contains(DefaultPattern.HeaderBegin) == true)
                        {
                            // Si jamais il y a déjà un groupe en cours de traitement, on l'ajoute à la liste
                            if (currentGroup != null)
                            {
                                if (groupToAdd == null)
                                    groupToAdd = new List<StructuredFileGroup>();

                                groupToAdd.Add(currentGroup);
                                currentGroup = null;
                            }

                            // C'est une ligne d'entête, il faut la parser pour récupérer le numéro de groupe
                            // Suppression de la balise d'entête
                            parsedLine = currentLine;

                            if (DefaultPattern.HeaderBegin.Length > 0)
                                parsedLine = parsedLine.Replace(DefaultPattern.HeaderBegin, "");

                            if (DefaultPattern.HeaderEnd.Length > 0) 
                                parsedLine = parsedLine.Replace(DefaultPattern.HeaderEnd, "");

                            // On essaye de lire le numéro du groupe
                            try
                            {
                                currentGroupID = Convert.ToUInt32(parsedLine);
                            }
                            catch (Exception)
                            {
                                currentGroupID = 0;
                            }

                            currentGroup = new StructuredFileGroup(currentGroupID);
                        }
                        else
                        {
                            // C'est une ligne à analyser
                            // Verification si la ligne est valable (si elle est non valable, elle est non traitée)
                            if (currentLine.Contains(DefaultPattern.LineBegin) && currentLine.Contains(DefaultPattern.LineSeparator) && currentLine.Contains(DefaultPattern.LineEnd))
                            {
                                // La ligne est valide, on la traite
                                // On supprime les entete et les fin de ligne
                                parsedLine = currentLine;

                                if (DefaultPattern.LineBegin.Length > 0)
                                    parsedLine = currentLine.Replace(DefaultPattern.LineBegin, "");

                                if (DefaultPattern.LineEnd.Length > 0)
                                    parsedLine = parsedLine.Replace(DefaultPattern.LineEnd, "");

                                // Récupération des noms de chaines et valeurs
                                currentIndex = parsedLine.IndexOf(DefaultPattern.LineSeparator);
                                currentKeyName = parsedLine.Substring(0, currentIndex);
                                currentKeyValue = parsedLine.Substring(currentIndex + DefaultPattern.LineSeparator.Length);

                                // Ajout de la clé considérée
                                if (currentGroup == null)
                                    currentGroup = new StructuredFileGroup(0);

                                currentGroup.AddKey(new StructuredFileKey(currentKeyName, currentKeyValue));
                            }
                        }
                    }
                }

                // On ajoute le tout dernier groupe
                if (currentGroup != null)
                {
                    if (groupToAdd == null)
                        groupToAdd = new List<StructuredFileGroup>();

                    groupToAdd.Add(currentGroup);
                    currentGroup = null;
                }

                if (groupToAdd != null)
                {
                    // On ajoute tous les groupes que l'on vient de charger dans le fichier final
                    foreach (StructuredFileGroup tmpGroup in groupToAdd)
                    {
                        this.AddGroup(tmpGroup);
                    }

                    Ret = groupToAdd.Count();
                }
            }

            return Ret;
        }

        /// <summary>
        /// Permet de sauvegarder le fichier précédemment ouvert suivant le format :
        /// [Groupe N]               <-- Avec N l'identifiant du groupe 
        /// keyName = keyValue       <-- Couple (key, value) pour le groupe considéré 
        /// etc...
        /// </summary>
        /// <returns>Nombre de groupe écrit (-1 en cas d'erreur)</returns>
        public int Save()
        {
            int Ret = -1;

            // Verification des paramètres d'entrée
            if (_currentFileName == null)
            {
                _debugTool.WriteLine("StructuredFile (Save) : Aucun fichier chargé");
            }
            else
            {
                Ret = SaveTo(_currentFileName);
            }

            return Ret;
        }

        /// <summary>
        /// Ecriture du fichier suivant le format :
        /// [Groupe N]               <-- Avec N l'identifiant du groupe 
        /// keyName = keyValue       <-- Couple (key, value) pour le groupe considéré 
        /// etc...
        /// </summary>
        /// <param name="newFileName">Chemin d'accès au fichier</param>
        /// <returns>Nombre de groupe écrit (-1 en cas d'erreur)</returns>
        public int SaveTo(String newFileName)
        {
            int Ret = -1;
            TextFile outputFile = null;
         
            // Verification des paramètres d'entrée
            if ((newFileName == null) || (newFileName == ""))
            {
                _debugTool.WriteLine("StructuredFile (SaveTo) : Nom de fichier invalide");
                return Ret;
            }

            if ((_group == null) || (_group.Count == 0))
            {
                _debugTool.WriteLine("StructuredFile (SaveTo) : Pas de données à sauvegarder");
                return Ret;
            }

            // Creation du fichier de sortie
            outputFile = new TextFile();

            // Lecture des groupes
            foreach (StructuredFileGroup tmpGroup in _group)
            {
                // Creation de l'entête du groupe
                outputFile.AddLine(DefaultPattern.HeaderBegin + tmpGroup.groupID.ToString() + DefaultPattern.HeaderEnd);

                if(tmpGroup.GetAllKeys() != null)
                {
                    foreach (StructuredFileKey tmpKey in tmpGroup.GetAllKeys())
                    {
                        outputFile.AddLine(DefaultPattern.LineBegin +  tmpKey.ID + DefaultPattern.LineSeparator + tmpKey.valueString + DefaultPattern.LineEnd);
                    }
                }
                
                // Saut de ligne
                outputFile.AddLine("");

            }

            // Ecriture du fichier de sortie
            if (outputFile.SaveTo(newFileName) > 0)
            {
                // On garde le dernier fichier ecrit
                _currentFileName = newFileName;
                
                // On indique le nombre de groupe ecrit
                Ret = _group.Count();
            }
 
            return Ret;
        }

        /// <summary>
        /// Permet d'ajouter un groupe 
        /// </summary>
        /// <param name="groupToAdd">Groupe de données à ajouter</param>
        /// <returns>True si l'ajout est correct, false sinon</returns>
        public bool AddGroup(StructuredFileGroup groupToAdd)
        {
            bool Ret = false;

            // Check des paramètres d'entrée
            if (groupToAdd != null)
            {
                // Verification de la liste de groupe
                if (_group == null)
                {
                    // Creation de la liste + ajout du groupe
                    _group = new List<StructuredFileGroup>();
                    _group.Add(groupToAdd);
                }
                else
                {
                    // Verification si le groupe à ajouter n'existe pas déjà
                   foreach(StructuredFileGroup tmpGroup in _group)
                   {
                       //Si le groupe existe déjà, on ajoute tous les éléments dans le groupe existant
                       if(tmpGroup.groupID == groupToAdd.groupID)
                       {
                           // On copie toute les clés dans la nouvelle liste
                           tmpGroup.AddKey(groupToAdd.GetAllKeys());
                           Ret = true; // On a ajouter les clés, on sort
                       }
                   }

                   // Si la liste n'a pas été ajoutée, on ajoute le nouveau groupe
                   if(Ret == false)
                   {
                       _group.Add(groupToAdd);
                       Ret = true;
                   }
                }
            }

            return Ret;
        }

        /// <summary>
        /// Permet de supprimer tous les groupes présents dans le fichier
        /// </summary>
        public void RemoveAllGroup()
        {
            if (_group != null)
            {
                _group.Clear();
                _group = null;
            }
        }

        /// <summary>
        /// Supprime le groupe ayant le groupID indiqué
        /// </summary>
        /// <param name="groupID">ID du groupe à supprimer</param>
        public void RemoveGroupByID(uint groupID)
        {
            // Verification des params internes
            if (_group != null)
            {
                for (int i = 0; i<_group.Count(); i++) 
                {
                    if (_group[i].groupID == groupID)
                        _group.RemoveAt(i);
                }
            }
        }

        /// <summary>
        /// Récupère un groupe de clé à partir d'un ID
        /// </summary>
        /// <param name="groupID">ID du groupe à récupérer</param>
        /// <returns>Group demandé ou null si le groupe n'est pas trouvé</returns>
        public StructuredFileGroup GetGroupByID(uint groupID)
        {
            StructuredFileGroup Ret = null;

            // Verification des params intenes
            if (_group != null)
            {
                // Recherche du groupe
                foreach (StructuredFileGroup tmpGroup in _group)
                {
                    if (tmpGroup.groupID == groupID)
                        Ret = tmpGroup;
                }
            }

            return Ret;
        }

        /// <summary>
        /// Retourne tous les groupes chargés dans le fichier
        /// </summary>
        /// <returns>Liste de StructuredFileGroup</returns>
        public List<StructuredFileGroup> GetAllGroup()
        {
            return _group;
        }

        // Private --------------------------------------------------------------------------------
        private TextFile _patternFile = null;               // Fichier texte contenant le pattern du fichier utilisé
        private List<StructuredFileGroup> _group = null;    // Liste de Keys spécifiques à écrire et/ou charger du fichier
        private DebugTool _debugTool;                       // Outil pour contrôler les informations de débug 
        private String _currentFileName = null;             // Chemin d'accès pour enregistrer le fichier

        private struct DefaultPattern
        {
            public const String HeaderBegin = "[Groupe ";   // Début de la chaine d'entête
            public const String HeaderEnd = "]";            // Fin de la chaine d'entête
            public const String LineBegin = "";             // Début de la ligne
            public const String LineSeparator = " = ";      // Séparateur de la ligne
            public const String LineEnd = "";               // Fin de la ligne
        }
    }
}
