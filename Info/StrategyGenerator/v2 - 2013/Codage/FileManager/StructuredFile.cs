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
                        if (currentLine.Contains(DefaultPatternTag.HeaderBegin) == true)
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

                            if (DefaultPatternTag.HeaderBegin.Length > 0)
                                parsedLine = parsedLine.Replace(DefaultPatternTag.HeaderBegin, "");

                            if (DefaultPatternTag.HeaderEnd.Length > 0) 
                                parsedLine = parsedLine.Replace(DefaultPatternTag.HeaderEnd, "");

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
                            if (currentLine.Contains(DefaultPatternTag.LineBegin) && currentLine.Contains(DefaultPatternTag.LineSeparator) && currentLine.Contains(DefaultPatternTag.LineEnd))
                            {
                                // La ligne est valide, on la traite
                                // On supprime les entete et les fin de ligne
                                parsedLine = currentLine;

                                if (DefaultPatternTag.LineBegin.Length > 0)
                                    parsedLine = currentLine.Replace(DefaultPatternTag.LineBegin, "");

                                if (DefaultPatternTag.LineEnd.Length > 0)
                                    parsedLine = parsedLine.Replace(DefaultPatternTag.LineEnd, "");

                                // Récupération des noms de chaines et valeurs
                                currentIndex = parsedLine.IndexOf(DefaultPatternTag.LineSeparator);
                                currentKeyName = parsedLine.Substring(0, currentIndex);
                                currentKeyValue = parsedLine.Substring(currentIndex + DefaultPatternTag.LineSeparator.Length);

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
                outputFile.AddLine(DefaultPatternTag.HeaderBegin + tmpGroup.ID.ToString() + DefaultPatternTag.HeaderEnd);

                if(tmpGroup.GetAllKeys() != null)
                {
                    foreach (StructuredFileKey tmpKey in tmpGroup.GetAllKeys())
                    {
                        outputFile.AddLine(DefaultPatternTag.LineBegin +  tmpKey.keyName + DefaultPatternTag.LineSeparator + tmpKey.valueString + DefaultPatternTag.LineEnd);
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
                       if(tmpGroup.ID == groupToAdd.ID)
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
                    if (_group[i].ID == groupID)
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
                    if (tmpGroup.ID == groupID)
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

        /// <summary>
        /// Exporte tous les groupes définis dans le fichier en suivant le pattern file précédemment défini
        /// </summary>
        /// <param name="fileName">Nom du fichier pour l'export</param>
        /// <returns>Nombre de groupe ecrit (-1 en cas d'erreur)</returns>
        public int Export(String fileName)
        {
            int Ret = -1;
            TextFile outputFile = new TextFile();
            List<String> outputBuffer = new List<string>();
            int currentGroupIndex = -1;                         // Index du groupe pour le remplacement des gID
            int indexInLine = -1;                               // Index pour parser les différentes lignes
            String flagToCheck = null;                          // Permet l'analyse du tag


            // Verification des params d'entrée
            if (fileName != null)
            {
                // Verification des paramètres internes
                if ((_patternFile != null) && (_group != null))
                {
                    // Récupération du fichier pattern
                    for(int i=0; i<_patternFile.Count(); i++)
                    {
                        outputBuffer.Add(_patternFile.GetLine(i));
                    }

                    // Lecture de tout le fichier pour remplacer les Tags 'gID' par l'identifiant du groupe
                    for(int i=0; i<outputBuffer.Count(); i++)
                    {
                        // Permet d'initialiser la position de l'index pour la recherche par ligne
                        indexInLine = 0;

                        // Recherche sur la ligne de tous les Tags 'gID'
                        do
                        {
                            // Recherche de l'index dans la portion de la ligne (à chaque passage on se décale sur la ligne)
                            indexInLine = outputBuffer[i].IndexOf("gID", indexInLine);

                            if (indexInLine > 1) // Il y a dans tous les cas un caractère avant le Tag gID
                            {
                                // Analyse du tag pour connaitre le type ('gID ou @gID)
                                flagToCheck = outputBuffer[i].Substring(indexInLine - 1, 4);
                                if (flagToCheck == "'gID") // Il s'agit d'un flag de groupe, il faut changer de groupe
                                {
                                    currentGroupIndex = GetNextGroupIndex(currentGroupIndex);   // On change de groupe
                                    if (currentGroupIndex >= 0) // On verifie que le groupe est valide
                                    {
                                        outputBuffer[i] = outputBuffer[i].Substring(0, indexInLine - 1) + _group[currentGroupIndex].ID.ToString() + outputBuffer[i].Substring(indexInLine + 5);
                                    }
                                }

                                if ((flagToCheck == "@gID") && (currentGroupIndex >= 0)) // Il s'agit d'un flag à remplacer et le groupe est valide
                                {
                                    // On remplace ce gID avec la valeur du groupe actuel
                                    outputBuffer[i] = outputBuffer[i].Substring(0, indexInLine) + _group[currentGroupIndex].ID.ToString() + outputBuffer[i].Substring(indexInLine + 3);
                                }
                            }
                        } while ((indexInLine >= 0) && (currentGroupIndex > 0));
                    }

                    // Export des données du groupe pour toutes les lignes du fichier
                    for (int i = 0; i < outputBuffer.Count(); i++)
                    {
                        // On verifie si la ligne doit être traitée (présence du caractère @)
                        if (outputBuffer[i].Contains("@") == true)
                        {
                            // On parcourt toute la liste des groupes
                            foreach (StructuredFileGroup currentGroup in _group)
                            {
                                // On verifie si la ligne contient des données du groupe
                                if (outputBuffer[i].Contains("@" + currentGroup.ID.ToString()) == true)
                                {
                                    // On parcourt toutes les clées
                                    foreach (StructuredFileKey currentKey in currentGroup.GetAllKeys())
                                    {
                                        outputBuffer[i] = outputBuffer[i].Replace("'" + currentKey.keyName + "@" + currentGroup.ID.ToString() + "'", currentKey.valueString);
                                    }
                                }
                            }
                        }
 
                        // Ecriture de la ligne dans le fichier de sortie
                        outputFile.AddLine(outputBuffer[i]);
                    }

                    // Ecriture du fichier final
                    outputFile.SaveTo(fileName);
                    Ret = _group.Count();
                }
            }

            return Ret;
        }

        public int Import(String fileName)
        {
            int Ret = -1;
            int iCurrentIndex = -1;
            TextFile inputFile = new TextFile();
            List<String> inputBuffer = new List<string>();
            List<String> patternBuffer = new List<string>();
            string[] splitLinePattern = null;
            string[] patternSeparator = new string[1];
            String currentFullKey = null;
            String currentValueKey = null;
            String currentGroupID = "0";

            // Verification des params d'entrée
            if (fileName != null)
            {
                // Verification des paramètres internes
                if (_patternFile != null) 
                {
                    // Lecture du fichier
                    inputFile.Load(fileName);

                    // Comparaison des tailles de fichier
                    if (inputFile.Count() == _patternFile.Count())
                    {
                        // Comparaison des fichiers lignes à lignes, les lignes identiques sont supprimées, les lignes différentes sont stockées
                        for (int i = 0; i < inputFile.Count(); i++)
                        {
                            if (inputFile.GetLine(i) != _patternFile.GetLine(i)) // Les lignes sont différentes, on les ajoute pour traitement
                            {
                                inputBuffer.Add(inputFile.GetLine(i));
                                patternBuffer.Add(_patternFile.GetLine(i));
                            }
                        }

                        // Si des lignes doivent être traitées
                        if (inputBuffer.Count() > 0)
                        {
                            // Initialisation du séparateur
                            patternSeparator[0] = "'";

                            // analyse des lignes pour extraire les données
                            for (int iLine = 0; iLine < inputBuffer.Count(); iLine++)
                            {
                                // On découpe la ligne avec les caractères '
                                splitLinePattern = patternBuffer[iLine].Split(patternSeparator, StringSplitOptions.RemoveEmptyEntries);

                                foreach (string splitPattern in splitLinePattern)
                                {
                                    // Verification s'il s'agit d'une clé ou pas
                                    if ((splitPattern.Contains("@") == true) || (splitPattern.Contains(PatternTag.gID)))
                                    {
                                        // S'il s'agit d'un gID, il aut stocker la valeur pour les lectures successives
                                        if (splitPattern == PatternTag.gID)
                                        {
                                            // Il s'agit d'une déclaration de gID
                                            currentFullKey = PatternTag.gID;
                                        }
                                        else
                                        {
                                            // Il s'agit d'une clé
                                            currentFullKey = splitPattern.ToString();
                                        }
                                    }
                                    else
                                    {
                                        // Il ne s'agit pas d'une clé
                                        // Verification du positionnement de la chaine actuelle
                                        iCurrentIndex = inputBuffer[iLine].IndexOf(splitPattern.ToString());

                                        if (iCurrentIndex >= 0)     // La chaine a été trouvée
                                        {
                                            if (iCurrentIndex == 0)  // La chaine actuelle est la première de la ligne
                                            {
                                                // Suppression de la section sans clé
                                                inputBuffer[iLine] = inputBuffer[iLine].Substring(splitPattern.Length);
                                            }
                                            else
                                            {
                                                // Il y a une clé avant la chaine recherchée
                                                // On récupère la clé
                                                currentValueKey = inputBuffer[iLine].Substring(0, iCurrentIndex);

                                                // On supprime la section sans clé
                                                inputBuffer[iLine] = inputBuffer[iLine].Substring(iCurrentIndex + splitPattern.Length);

                                                // Verification des données avant l'ajout des clés
                                                if (currentFullKey == PatternTag.gID)
                                                {
                                                    // Il s'agit d'une clé générique 'groupID'
                                                    currentGroupID = currentValueKey;
                                                }
                                                else
                                                {
                                                    // Avant d'ajouter la clé, on remplace les données 'gID' par la valeur du groupe
                                                    if (currentFullKey.Contains("@" + PatternTag.gID) == true)
                                                    {
                                                        currentFullKey = currentFullKey.Replace("@" + PatternTag.gID, "@" + currentGroupID);
                                                    }

                                                    // Il faut ajouter la clé
                                                    AddKeyAndValue(currentFullKey, currentValueKey);
                                                }

                                                // Réinitialisation de la valeur de clé
                                                currentFullKey = null;
                                                currentValueKey = null;
                                            }
                                        }
                                        else
                                        {
                                            // La chaine n'a pas été trouvée
                                        }
                                    }
                                }

                                // Si le buffer de lecture n'est pas vide et une clé est en attente de lecture, on la traite
                                if (inputBuffer[iLine].Length > 0 && currentFullKey != null)
                                {
                                    currentValueKey = inputBuffer[iLine];
                                    inputBuffer[iLine] = "";

                                    // Verification des données avant l'ajout des clés
                                    if (currentFullKey == PatternTag.gID)
                                    {
                                        // Il s'agit d'une clé générique 'groupID'
                                        currentGroupID = currentValueKey;
                                    }
                                    else
                                    {
                                        // Avant d'ajouter la clé, on remplace les données 'gID' par la valeur du groupe
                                        if (currentFullKey.Contains("@" + PatternTag.gID) == true)
                                        {
                                            currentFullKey = currentFullKey.Replace("@" + PatternTag.gID, "@" + currentGroupID);
                                        }

                                        // Il faut ajouter la clé
                                        AddKeyAndValue(currentFullKey, currentValueKey);
                                    }

                                    // Réinitialisation de la valeur de clé
                                    currentFullKey = null;
                                    currentValueKey = null;
                                }
                            }
                        }

                        Ret = _group.Count();
                    }
                    else
                    {
                        _debugTool.WriteLine("StructuredFile (Import) : Impossible d'importer les données, les tailles de fichier sont différentes");
                    }
                }
            }

            return Ret;
        }

        // Private Functions ----------------------------------------------------------------------
        /// <summary>
        /// Permet de récupérer le gID suivant le gID donné en paramètre (le gID = 0 n'est pas pris en compte)
        /// Si le gID n'est pas défini, utiliser -1 pour currentGroupIndex
        /// </summary>
        /// <param name="currentGroupIndex">Groupe ID actuel</param>
        /// <returns>gID suivant (-2 en cas d'erreur)</returns>
        private int GetNextGroupIndex(int currentGroupIndex)
        {
            int Ret = -1;

            if (currentGroupIndex  < 0)  // Il n'y a pas de groupe actuellement configuré, utilisation du groupe pas défaut
            {
                if (currentGroupIndex == -1)
                    currentGroupIndex = 0;
                else
                    currentGroupIndex = -2;
            }
            else
            {
                currentGroupIndex = currentGroupIndex + 1;
            }

            // Verification des données
            if ((currentGroupIndex >= _group.Count()) || (currentGroupIndex < 0))    // Il n'y a plus de groupe disponible
            {
                Ret = -2;
            }
            else
            {
                // Verification du groupe (le groupe 0 ne peut pas être utilisé)
                if (_group[currentGroupIndex].ID == 0)
                {
                    Ret = GetNextGroupIndex(currentGroupIndex);
                }
                else
                {
                    Ret = currentGroupIndex;
                }
            }

            return Ret;
        }

        /// <summary>
        /// Ajoute une clé depuis le fichier d'import
        /// </summary>
        /// <param name="FullKey">Clé au format KeyName@GroupID</param>
        /// <param name="ValueKey">Valeur de la clé</param>
        private void AddKeyAndValue(String FullKey, String ValueKey)
        {
            string[] splitKey = null;
            string[] patternSeparator = new string[1]; patternSeparator[0] = "@";
            StructuredFileGroup groupToAdd = null;

            if ((FullKey != null) && (ValueKey != null))
            {
                // On verifie que la chaine est correctement formée
                if (FullKey.Contains("@") == true)
                {
                    splitKey = FullKey.Split(patternSeparator, StringSplitOptions.RemoveEmptyEntries);
                    if (splitKey != null)
                    {
                        try
                        {
                            groupToAdd = new StructuredFileGroup(Convert.ToUInt32(splitKey[1].ToString()), new StructuredFileKey(splitKey[0].ToString(), ValueKey));
                            AddGroup(groupToAdd);
                        }
                        catch (Exception)
                        {
                        }
                    }
                }
            }
        }

        // Private --------------------------------------------------------------------------------
        private TextFile _patternFile = null;               // Fichier texte contenant le pattern du fichier utilisé
        private List<StructuredFileGroup> _group = null;    // Liste de Keys spécifiques à écrire et/ou charger du fichier
        private DebugTool _debugTool;                       // Outil pour contrôler les informations de débug 
        private String _currentFileName = null;             // Chemin d'accès pour enregistrer le fichier

        private struct DefaultPatternTag
        {
            public const String HeaderBegin = "[Groupe ";   // Début de la chaine d'entête
            public const String HeaderEnd = "]";            // Fin de la chaine d'entête
            public const String LineBegin = "";             // Début de la ligne
            public const String LineSeparator = " = ";      // Séparateur de la ligne
            public const String LineEnd = "";               // Fin de la ligne
        }

        private struct PatternTag
        {
            public const String gID = "gID";
        }
    }
}
