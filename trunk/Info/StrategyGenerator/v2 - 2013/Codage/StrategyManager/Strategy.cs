using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using StrategyGenerator2.Tools;
using StrategyGenerator2.FileManager;

namespace StrategyGenerator2.StrategyManager
{
    public class Strategy
    {

        // Public ---------------------------------------------------------------------------------
        public Strategy(String strategyName)
        {
            // Si le nom est non nul, on ajoute ce nom à la stratégie
            if (strategyName != null)
                _strategyName = strategyName;

            // Creation du premier objet pour la partie décisionnelle
            _subStrategies = new List<SubStrategy>();
            _subStrategies.Add(new SubStrategy(PrivateConst.mainStrategyName));

            _debugTool = new DebugTool(DebugTool.EDebugToolType.Console);
        }

        /// <summary>
        /// Ajoute un nouvel objet. Si l'objet est déjà défini, on le met juste à jour
        /// </summary>
        /// <param name="newStrategy">Objet à ajouter</param>
        public void AddSubStrategy(SubStrategy newStrategy)
        {
            UpdateSubStrategy(newStrategy);
        }

        /// <summary>
        /// Permet de recupérer la stratégie ayant le nom 'subStrategyName'
        /// </summary>
        /// <param name="subStrategyName">Nom de la stratégie</param>
        /// <returns>Null si l'objet n'est pas trouvé</returns>
        public SubStrategy GetSubStrategy(String subStrategyName)
        {
            SubStrategy Ret = null;
            
            if (subStrategyName != null)
            {
                foreach (SubStrategy currentSubStrategy in _subStrategies)
                {
                    if (currentSubStrategy.Name == subStrategyName)
                        Ret = currentSubStrategy;
                }
            }

            return Ret;
        }

        /// <summary>
        /// Récupère toutes les substratégies 
        /// </summary>
        /// <returns>Liste de tous les substrategies</returns>
        public List<SubStrategy> GetAllSubStrategy()
        {
            List<SubStrategy> Ret = null;

            if (_subStrategies != null)
            {
                foreach (SubStrategy currentSubStrategy in _subStrategies)
                {
                    if (currentSubStrategy.Name != PrivateConst.mainStrategyName)
                    {
                        if (Ret == null)
                            Ret = new List<SubStrategy>();

                        Ret.Add(currentSubStrategy);
                    }
                }
            }

            return Ret;
        }

        /// <summary>
        /// Permet de vider la stratégie actuelle
        /// </summary>
        public void Clear()
        {
            _subStrategies = new List<SubStrategy>();
            _subStrategies.Add(new SubStrategy(PrivateConst.mainStrategyName));
        }

        /// <summary>
        /// Permet de supprimer la substrategy passée en paramètre
        /// </summary>
        /// <param name="subStrategyName">Nom de la substratégy à supprimer</param>
        public void RemoveSubStrategy(String subStrategyName)
        {
            // Verification des paramètres d'entrée
            if ((subStrategyName != null) && (subStrategyName != PrivateConst.mainStrategyName))
            {
                List<SubStrategy> newSubStrategy = null;

                // On parcourt tous les objets de la liste
                foreach (SubStrategy currentSubStrategy in _subStrategies)
                {
                    // Si l'objet ne doit pas être supprimer, il faut l'ajouter à la nouvelle liste
                    if (currentSubStrategy.Name != subStrategyName)
                    {
                        // Si la liste est vide
                        if (newSubStrategy == null)
                            newSubStrategy = new List<SubStrategy>();

                        // On ajoute l'objet
                        newSubStrategy.Add(currentSubStrategy);
                    }
                }

                // On remplace les listes
                _subStrategies = newSubStrategy;
            }
        }

        /// <summary>
        /// Crée un dossier ayant le nom de la stratégie dans le dossier "Data" à coté de l'executable
        /// La stratégie principale + toutes les sous-stratégies sont exportées dans des fichiers indépendants
        /// ATTENTION : Si le sous dossier existe déjà, il est détruit et remplacé par la sauvegarde courante (sans confirmation)
        /// </summary>
        public void Save()
        {
            // Verification des données internes
            if ((_strategyName != null) && (_subStrategies != null))
            {
                try
                {
                    String outputDir = "./" + PrivateConst.outputDir + _strategyName +"/";

                    // Verification du répertoire de sortie
                    if (Directory.Exists("./" + PrivateConst.outputDir) != true)
                    {
                        // Si le dossier n'existe pas, il faut le créer
                        Directory.CreateDirectory("./" + PrivateConst.outputDir);
                    }

                    // Verification du sous répertoire de sortie
                    if (Directory.Exists(outputDir) == true)
                    {
                        // Si le dossier existe, il faut le vider
                        Directory.Delete(outputDir, true);
                    }

                    // Creation du répertoire de sortie
                    Directory.CreateDirectory(outputDir);

                    // Sauvegarde des informations générales
                    StructuredFile mainFile = new StructuredFile();
                    StructuredFileGroup mainGroup = new StructuredFileGroup(0);
                    mainGroup.AddKey(new StructuredFileKey(PrivateConst.mainStrategyName, _strategyName));

                    mainFile.AddGroup(mainGroup);
                    mainFile.SaveTo(outputDir + _strategyName + ".strategy");
                    mainFile = null;
                    mainGroup = null;

                    // Sauvegarde des sub-stratégies
                    foreach(SubStrategy currentSubStrategy in _subStrategies)
                    {
                        currentSubStrategy.Save(outputDir + currentSubStrategy.Name + ".sfile");

                        // Verification du répertoire d'import
                        if (Directory.Exists("./" + PrivateConst.outputDir) != true)
                        {
                            // Si le dossier n'existe pas, il faut le créer
                            Directory.CreateDirectory("./" + PrivateConst.outputDir);
                        }

                    }
                }
                catch (Exception ex)
                {
                    _debugTool.WriteLine("Strategy.cs = " + ex.Message);
                }
            }
        }

        /// <summary>
        /// Charge les informations de la stratégie donnée en paramètre
        /// </summary>
        /// <param name="strategyName">Nom de la stratégie à chargée</param>
        public void Load(String strategyName)
        {
            try
            {
                String inputDir = "./" + PrivateConst.outputDir + strategyName + "/";
                StructuredFile mainFile = new StructuredFile();
                StructuredFileGroup currentGroup = null;
                StructuredFileKey currentKey = null;
                SubStrategy currentSubStrategy = null;


                // Verification du répertoire d'import
                if (Directory.Exists(inputDir) == true)
                {
                    // Chargement des données générale

                    mainFile.Load(inputDir + strategyName + ".strategy");
                    if (mainFile != null)
                    {
                        // Lecture des informations générales ---------------------------------------------------------
                        // On ne charge les données que si le fichier de base est disponible
                        currentGroup = mainFile.GetGroupByID(0);
                        if (currentGroup != null)
                        {
                            // Chargement des données générale
                            currentKey = currentGroup.GetFirstKey(PrivateConst.mainStrategyName);
                            if (currentKey != null)
                                _strategyName = currentKey.valueString;
                            else
                                _strategyName = "NewStrategy";
                        }

                        // Lecture des sous-stratégies ----------------------------------------------------------------
                        // Récupération des noms de fichier
                        IEnumerable<String> inputFiles = Directory.EnumerateFiles(inputDir, "*.sfile");

                        foreach (String currentFile in inputFiles)
                        {
                            // Chargement du fichier
                            currentSubStrategy = new SubStrategy("NewSubStrategy");
                            currentSubStrategy.Load(currentFile);

                            if (currentSubStrategy.Name == PrivateConst.mainStrategyName)
                                _subStrategies[0] = currentSubStrategy;
                            else
                                _subStrategies.Add(currentSubStrategy);
                        }
                    }

                }
                else
                {
                    _debugTool.WriteLine("Strategy.cs = Directory '" + strategyName + "' not found !");
                }
            }
            catch (Exception ex)
            {
                _debugTool.WriteLine("Strategy.cs = " + ex.Message);
            }
        }


        public int Export(String outputFileName, String patternFileName)
        {
            int Ret = -1;
            int iLine = 0;                                              // iterator
            bool loopSubStrategyPatternFlag = false;                    // Flag pour indiquer si la ligne en cours est une ligne de sub-stratégie pattern
            String currentLine = "";                                    // Ligne courrante (pour copie et/ou analyse)
            StructuredFile outputFile = new StructuredFile();           // Fichier de sortie
            TextFile patternFile = new TextFile();                      // Fichier pattern
            TextFile outputPatternFile = new TextFile();                // Fichier pattern à utiliser pour écrire le fichier de sortie
            List<String> loopSubStrategyPattern = new List<string>();   // Lignes à répéter pour les subStratégies dans le fichier de sortie

            // Verification des paramètres d'entrée et des paramètres internes
            if ((outputFileName != null) && (patternFileName != null) && (_subStrategies != null))
            {
                // Chargement du fichier model
                patternFile.Load(patternFileName);

                // Verification du fichier pattern et création du fichier réel de sortie
                if (patternFile.Count() > 0)
                {
                    // On parcourt tout le fichier et on copie toutes les lignes qui n'appartiennent pas à boucle de stratégie
                    for (iLine = 0; iLine < patternFile.Count(); iLine++)
                    {
                        // Lecture de la ligne
                        currentLine = patternFile.GetLine(iLine);

                        // Analyse de la ligne
                        // Est-ce dans une boucle de lecture de pattern
                        if (loopSubStrategyPatternFlag == true)
                        {
                            if (loopSubStrategyPatternFlag == true)
                            {
                                // A-t-on trouver le flag de fin de boucle
                                if (currentLine.ToUpper().Contains(PrivateConst.subStrategyEndTag.ToUpper()) == true)
                                {
                                    // La fin de boucle a été trouvée. On abaisse le flag
                                    loopSubStrategyPatternFlag = false;

                                    // On duplique le modèle en fonction des données en interne
                                    // Pour toutes les sub-stratégies
                                    for (int iSubStrategy = 0; iSubStrategy < _subStrategies.Count(); iSubStrategy++)
                                    {
                                        SubStrategy currentSubStrategy = _subStrategies[iSubStrategy];

                                        // Export des données de la sous-stratégie
                                        for (int i = 0; i < currentSubStrategy.Count(); i++)
                                        {
                                            // Ecriture des infos de la stratégie
                                            foreach (String patternLineToAdd in loopSubStrategyPattern)
                                                outputPatternFile.AddLine(patternLineToAdd);
                                        }

                                        // Ecriture d'un saut de ligne pour la mise en page
                                        outputPatternFile.AddLine("");
                                    }

                                    // On ajoute la Tag de fin de boucle
                                    outputPatternFile.AddLine(currentLine);
                                }
                                else
                                {   
                                    // Nous ajoutons la ligne courante au pattern
                                    loopSubStrategyPattern.Add(currentLine);
                                }
                            }
                        }
                        else
                        {
                            if (currentLine.ToUpper().Contains(PrivateConst.subStrategyBeginTag.ToUpper()) == true)
                                loopSubStrategyPatternFlag = true;

                            // Nous sommes en lecture normale, cette ligne sera copiée dans le fichier de pattern final
                            outputPatternFile.AddLine(currentLine);
                        }
                    }
                }

                // Si le fichier pattern est prêt, nous écrivons les données dans le fichier de sortie
                if (outputPatternFile.Count() > 0)
                {
                    StructuredFileGroup groupToAdd = null;

                    // Creation des données génériques
                    groupToAdd = new StructuredFileGroup(0);     // Creation du groupe générique
                    groupToAdd.AddKey(new StructuredFileKey(PrivateConst.TAG_StrategyName, _strategyName));

                    // Ajout du groupe
                    outputFile.AddGroup(groupToAdd);
                    
                    // Creation des données spécifiques
                    if(_subStrategies.Count() > 0)
                    {
                        // Pour chaque sous stratégies
                        foreach(SubStrategy currentSubStrategy in _subStrategies)
                        {
                            String currentSubStrategyName = currentSubStrategy.Name;

                            if (currentSubStrategy.Count() > 0)
                            {
                                // Pour chacune des actions de la stratégie
                                foreach (RobotAction currentAction in currentSubStrategy.GetAllActions())
                                {
                                    groupToAdd = currentAction.Export();
                                    groupToAdd.AddKey(new StructuredFileKey(PrivateConst.TAG_SubStrategyName, currentSubStrategyName));
                                    outputFile.AddGroup(groupToAdd);
                                }
                            }
                        }
                    }

                    // Ecriture du fichier final
                    outputFile.SetPatternFile(outputPatternFile);
                    outputFile.Export(outputFileName);
                }
            }

            return Ret;
        }


        public int Import(String inputFileName, String patternFileName)
        {
            int Ret = -1;

            return Ret;
        }

        /// <summary>
        /// Met à jour les données de la MainStrategy à partir de l'objet passé en paramètre
        /// </summary>
        /// <param name="newStrategy">Données à mettre à jour</param>
        public void UpdateMainStrategy(SubStrategy newStrategy)
        {
            if ((newStrategy != null) && (_subStrategies.Count() > 0))
            {
                _subStrategies[0] = newStrategy.Clone();
                _subStrategies[0].Name = PrivateConst.mainStrategyName;
            }
        }

        /// <summary>
        /// Met à jour la sous stratégie.
        /// Si l'élément existe dans la stratégie actuelle, elle est mise à jour.
        /// Si l'élément n'existe pas, l'élément est ajouté
        /// </summary>
        /// <param name="newSubStrategy">Nouvelles données à ajouter</param>
        public void UpdateSubStrategy(SubStrategy newSubStrategy)
        {
            bool isUpdated = false;

            // Verification des paramètres d'entrée
            if (newSubStrategy != null)
            {
                // Verification des données internes
                if (_subStrategies.Count() > 0)
                {
                    // On cherche l'élément dans les données internes
                    for (int i = 0; i < _subStrategies.Count(); i++)
                    {
                        if (_subStrategies[i].Name == newSubStrategy.Name)
                        {
                            _subStrategies[i] = newSubStrategy;
                            isUpdated = true;
                        }
                    }
                }

                // Si l'élément n'a pas été mis à jour (non trouvé) on l'ajoute
                if(isUpdated == false)
                    _subStrategies.Add(newSubStrategy);
            }
        }

        /// <summary>
        /// Récupère la stratégie principale
        /// </summary>
        /// <returns>MainStrategy ou null si pas de stratégie n'a été définie</returns>
        public SubStrategy GetMainStrategy()
        {
            SubStrategy Ret = null;

            if (_subStrategies.Count() > 0)
                Ret = _subStrategies[0];

            return Ret;
        }


        // Properties -----------------------------------------------------------------------------
        public String Name
        {
            get { return _strategyName;  }
            set 
            {
                if (value != null)
                    _strategyName = value;
            }
        }

        // Private functions ----------------------------------------------------------------------

        // Private --------------------------------------------------------------------------------
        private String _strategyName = "NewStrategy";               // Nom de la stragégie (utilisé pour le répertoire de sortie)
        private List<SubStrategy> _subStrategies = null;            // Toutes les sous stratégies 
        private DebugTool _debugTool;                               // Outil pour contrôler les informations de débug 

        private struct PrivateConst
        {
            public const String mainStrategyName = "MainStrategy";
            public const String outputDir = "Data/";
            public const String subStrategyBeginTag = "SUB_STRATEGY_BEGIN_LOOP";
            public const String subStrategyEndTag = "SUB_STRATEGY_END_LOOP";
            public const String TAG_StrategyName = "StrategyName";
            public const String TAG_SubStrategyName = "SubStrategyName";
        }
    }
}
