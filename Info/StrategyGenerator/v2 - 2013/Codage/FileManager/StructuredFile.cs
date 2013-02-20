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
            _keys = null;
            _debugTool = new DebugTool(DebugTool.EDebugToolType.Disabled);
        }

        public StructuredFile(String patternFileName)
        {
            _debugTool = new DebugTool(DebugTool.EDebugToolType.Disabled);
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
        /// Fonction pour charger un fichier pattern pour la l'import ou l'export des données
        /// </summary>
        /// <param name="patternFileName">Nom du fichier model</param>
        /// <returns>Le nombre de lignes lues (-1 en cas d'erreur)</returns>
        public int SetPatternFile(String patternFileName)
        {
            int Ret = -1;

            // Desallocation des données déjà chargées
            if (_patternFile != null)
            {
                _patternFile.RemoveAllLine();
            }

            // Lecture du fichier pattern
            Ret = _patternFile.Load(patternFileName);

            return Ret;
        }
        
        public int Load(String fileName)
        {
            return 0;
        }

        /// <summary>
        /// Permet de sauvegarder le fichier précédemment ouvert.
        /// </summary>
        /// <returns>Nombre de lignes écrites (-1 en cas d'erreur)</returns>
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
        /// Ecriture du fichier sous la forme :
        /// [Groupe N]               <-- Avec N l'identifiant du groupe 
        /// keyName = keyValue       <-- Couple (key, value) pour le groupe considéré 
        /// etc...
        /// </summary>
        /// <param name="newFileName">Chemin d'accès au fichier</param>
        /// <returns>Nombre de lignes écrites (-1 en cas d'erreur)</returns>
        public int SaveTo(String newFileName)
        {
            int Ret = -1;
         
            // Verification des paramètres d'entrée
            if ((newFileName == null) || (newFileName == ""))
            {
                _debugTool.WriteLine("StructuredFile (SaveTo) : Nom de fichier invalide");
                return Ret;
            }

            if ((_keys == null) || (_keys.Count == 0))
            {
                _debugTool.WriteLine("StructuredFile (SaveTo) : Pas de données à sauvegarder");
                return Ret;
            }

            return Ret;
        }

        // Private --------------------------------------------------------------------------------
        private TextFile _patternFile = null;           // Fichier texte contenant le pattern du fichier utilisé
        private List<StructuredFileKey> _keys = null;   // Liste de Keys spécifiques à écrire et/ou charger du fichier
        private DebugTool _debugTool;                   // Outil pour contrôler les informations de débug 
        private String _currentFileName = null;         // Chemin d'accès pour enregistrer le fichier

    }
}
