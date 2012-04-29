using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using StrategyGenerator.Strategy;

namespace StrategyGenerator.FileManager
{
    class StructuredFile : TextFile
    {
        // Constructeur ---------------------------------------------------------------------------
        /// <summary>
        /// Open an existing Structured file by openning a dialog box
        /// </summary>
        public StructuredFile()
        {
            _File = new TextFile();
            _File.Load();
        }

        /// <summary>
        /// Open an existing Structured file by using the filename 
        /// </summary>
        /// <param name="Pathname"></param>
        public StructuredFile(String Pathname)
        {
            _File = new TextFile(Pathname);
        }

        /// <summary>
        /// Create a new object by using an existing List of StructuredFileKey objects 
        /// </summary>
        /// <param name="Items">List of StructuredFileKey used to create the new structured file</param>
        public StructuredFile(List<StructuredFileKey> Items)
        {
            if ((Items != null) && (Items.Count() > 0))
            {
                _Items = new List<StructuredFileKey>();

                // Copy all data into _Items object
                foreach (StructuredFileKey CurrentItem in Items)
                {
                    _Items.Add(CurrentItem);
                }
            }
        }

        // Public ---------------------------------------------------------------------------------
        public void Parse(String PatternFilename)
        {
            List<String> PatternLine = null;
            List<String> PatternLoop = null;
            List<String> LineToCheck = null;
            List<String> LoopToCheck = null;
            String CurrentLine, TestLine, ResultPattern, ResultValue;

            int iCurrentLine = 0, PatternLen = 0, iterator = 0, PatternLoopInitialValue = 0;

            TextFile PatternFile = new TextFile(PatternFilename);

            if ((_File == null) || (null == PatternFile))
                return;

            // Clear unused data
            PatternFile.RemoveUnusedLine();
            _File.RemoveUnusedLine();

            // Search for Loops
            for (iCurrentLine = 1; iCurrentLine <= PatternFile.GetSize(); iCurrentLine++)
            {
                // Read the current line from patter file
                CurrentLine = PatternFile.GetLine(iCurrentLine);

                // Search for inital tag 
                if (CurrentLine == "// StructuredFileLoopBegin")
                {
                    // Read the next line
                    iCurrentLine++;
                    CurrentLine = PatternFile.GetLine(iCurrentLine);
                    PatternLen = 0;

                    if (PatternLoop == null)
                        PatternLoopInitialValue = 0;
                    else
                        PatternLoopInitialValue = PatternLoop.Count();

                    // Search for final tag into Pattern File
                    while ((CurrentLine != "// StructuredFileLoopEnd") && (iCurrentLine <= PatternFile.GetSize()))
                    {
                        if (PatternLoop == null)
                            PatternLoop = new List<string>();

                        if (LoopToCheck == null)
                            LoopToCheck = new List<string>();

                        // Check equivalent line into _File
                        TestLine = _File.GetLine(iCurrentLine);

                        // Add lines into the loop checker (if TestLine is valid)
                        if (TestLine != "// StructuredFileLoopEnd")
                        {
                            PatternLoop.Add(CurrentLine);
                            LoopToCheck.Add(TestLine);
                            if(CurrentLine != "// LoopID = 'LOOPID'")   // This line is not included into the pattern
                                PatternLen++;

                            // Remove added line (for current file)
                            _File.RemoveLine(iCurrentLine);
                        }
                        // Remove added line (for pattern file)
                        PatternFile.RemoveLine(iCurrentLine);

                        CurrentLine = PatternFile.GetLine(iCurrentLine);
                    }

                    iterator = PatternLoopInitialValue + 1; // Initial value is computed before adding the first LoopPattern value
                    CurrentLine = _File.GetLine(iCurrentLine);
                    
                    // Search for final tag into current File
                    while ((CurrentLine != "// StructuredFileLoopEnd") && (iCurrentLine <= _File.GetSize()))
                    {
                   
                        // Add lines to the loop checker
                        PatternLoop.Add(PatternLoop[iterator].ToString());
                        LoopToCheck.Add(_File.GetLine(iCurrentLine));

                        // Remove added lines
                        _File.RemoveLine(iCurrentLine);

                        CurrentLine = _File.GetLine(iCurrentLine);

                        iterator++;
                        if (iterator > PatternLoopInitialValue + PatternLen)
                            iterator = PatternLoopInitialValue + 1;
                    }

                }

            }

            // Clear unchanged line between the Pattern File and currentFile
            for (int i = 1; i <= _File.GetSize(); i++)
            {
                if (PatternFile.GetLine(i) != _File.GetLine(i))
                {
                    if (PatternLine == null)
                        PatternLine = new List<string>();

                    if (LineToCheck == null)
                        LineToCheck = new List<string>();

                    // Add line we have to compare
                    PatternLine.Add(PatternFile.GetLine(i));
                    LineToCheck.Add(_File.GetLine(i));

                }
            }

            // Create the result list for non-loop values
            if (PatternLine != null)
            {
                if (_Items == null)
                    _Items = new List<StructuredFileKey>();

                // Lecture ligne a ligne et sauvegarde des infos
                for (iCurrentLine = 0; iCurrentLine < PatternLine.Count(); iCurrentLine++)
                {
                    int iCurrentPatternChar = 0, iCurrentValueChar = 0;
                    // Traitement de la ligne en cours
                    for (iCurrentValueChar = 0; iCurrentValueChar < LineToCheck[iCurrentLine].Length; iCurrentValueChar++)
                    {
                        // Si nous n'avons pas d'overflow
                        if (iCurrentPatternChar < PatternLine[iCurrentLine].Length)
                        {
                            if (PatternLine[iCurrentLine].Substring(iCurrentPatternChar, 1) != LineToCheck[iCurrentLine].Substring(iCurrentValueChar, 1))
                            {
                                iCurrentPatternChar++;
                                iCurrentValueChar++;

                                int iStartPatternChar = iCurrentPatternChar;
                                // Des que nous voyons une difference dans les lignes
                                // On recherche la fin du pattern
                                while ((iCurrentPatternChar < PatternLine[iCurrentLine].Length) && (PatternLine[iCurrentLine].Substring(iCurrentPatternChar, 1) != "'"))
                                {
                                    iCurrentPatternChar++;
                                }

                                ResultPattern = PatternLine[iCurrentLine].Substring(iStartPatternChar, iCurrentPatternChar - iStartPatternChar);

                                // Read the next char to get the end of pattern block
                                iCurrentPatternChar++;

                                if (iCurrentPatternChar < PatternLine[iCurrentLine].Length)
                                {
                                    int iFirstChar = iCurrentValueChar - 1;
                                    string sLastChar = PatternLine[iCurrentLine].Substring(iCurrentPatternChar, 1);

                                    // Lecture de la valeur reelle dans la liste LineToCheck
                                    while ((iCurrentValueChar < LineToCheck[iCurrentLine].Length) && (LineToCheck[iCurrentLine].Substring(iCurrentValueChar, 1) != sLastChar))
                                    {
                                        iCurrentValueChar++;
                                    }

                                    // if the correct kay has been found
                                    if (LineToCheck[iCurrentLine].Substring(iCurrentValueChar, 1) == sLastChar)
                                    {
                                        ResultValue = LineToCheck[iCurrentLine].Substring(iFirstChar, iCurrentValueChar - iFirstChar);
                                        _Items.Add(new StructuredFileKey(-1, iCurrentLine, ResultPattern, ResultValue));
                                    }
                                }
                            }
                        }

                        // Incremente la valeur pour suivre iCurrentValueChar
                        iCurrentPatternChar++;
                    }
                }
            }

            // Create result list for loop values
            if (PatternLoop != null)
            {
                int CurrentLoopID = -1;

                if (_Items == null)
                    _Items = new List<StructuredFileKey>();

                // Lecture ligne a ligne et sauvegarde des infos
                for (iCurrentLine = 0; iCurrentLine < PatternLoop.Count(); iCurrentLine++)
                {
                    if (PatternLoop[iCurrentLine] == "// LoopID = 'LOOPID'")
                    {
                        CurrentLoopID = int.Parse(LoopToCheck[iCurrentLine].Substring("// LoopID = ".Length));
                    }
                    else if (PatternLoop[iCurrentLine] == "// StructuredFileLoopEnd")
                    {
                        CurrentLoopID = -1;
                    }
                    else
                    {
                        int iCurrentPatternChar = 0, iCurrentValueChar = 0;
                        // Traitement de la ligne en cours
                        for (iCurrentValueChar = 0; iCurrentValueChar < LoopToCheck[iCurrentLine].Length; iCurrentValueChar++)
                        {
                            // Si nous n'avons pas d'overflow
                            if (iCurrentPatternChar < PatternLoop[iCurrentLine].Length)
                            {
                                if (PatternLoop[iCurrentLine].Substring(iCurrentPatternChar, 1) != LoopToCheck[iCurrentLine].Substring(iCurrentValueChar, 1))
                                {

                                    iCurrentPatternChar++;
                                    iCurrentValueChar++;

                                    int iStartPatternChar = iCurrentPatternChar;
                                    // Des que nous voyons une difference dans les lignes
                                    // On recherche la fin du pattern
                                    while ((iCurrentPatternChar < PatternLoop[iCurrentLine].Length) && (PatternLoop[iCurrentLine].Substring(iCurrentPatternChar, 1) != "'"))
                                    {
                                        iCurrentPatternChar++;
                                    }

                                    ResultPattern = PatternLoop[iCurrentLine].Substring(iStartPatternChar, iCurrentPatternChar - iStartPatternChar);

                                    // Read the next char to get the end of pattern block
                                    iCurrentPatternChar++;

                                    if (iCurrentPatternChar < PatternLoop[iCurrentLine].Length)
                                    {
                                        int iFirstChar = iCurrentValueChar - 1;
                                        string sLastChar = PatternLoop[iCurrentLine].Substring(iCurrentPatternChar, 1);

                                        // Lecture de la valeur reelle dans la liste LineToCheck
                                        while ((iCurrentValueChar < LoopToCheck[iCurrentLine].Length) && (LoopToCheck[iCurrentLine].Substring(iCurrentValueChar, 1) != sLastChar))
                                        {
                                            iCurrentValueChar++;
                                        }

                                        // if the correct key has been found
                                        if (LoopToCheck[iCurrentLine].Substring(iCurrentValueChar, 1) == sLastChar)
                                        {
                                            ResultValue = LoopToCheck[iCurrentLine].Substring(iFirstChar, iCurrentValueChar - iFirstChar);
                                            _Items.Add(new StructuredFileKey(CurrentLoopID, iCurrentLine, ResultPattern, ResultValue));
                                        }
                                    }
                                }
                            }

                            // Incremente la valeur pour suivre iCurrentValueChar
                            iCurrentPatternChar++;
                        }
                    }
                }
            }

            return;
        }

        /// <summary>
        /// Donne la première valeur de Key trouvée dans le fichier. 
        /// </summary>
        /// <returns>Retourne DefaultValue si Key n'a pas été trouvé</returns>
        public String GetValue(String Key, String DefaultValue)
        {
            for (int i = 0; i < _Items.Count(); i++)
            {
                // Seule les valeurs en dehors des boucles sont lues
                if (_Items[i].GetLoopID() == -1)
                {
                    // Verification des clees
                    if (_Items[i].GetName() == Key)
                        return _Items[i].GetValue();
                }
            }

            return DefaultValue;
        }

        /// <summary>
        /// Recupère la valeur max pour le nombre de boucle
        /// </summary>
        /// <returns>La valeur max pour LoopID</returns>
        public int GetMaxLoopID()
        {
            int MaxLoopID = 0;

            // Lecture de toute la liste pour déterminer le Max Loop ID
            for (int i = 0; i < _Items.Count(); i++)
            {
                // Verification de la valeur trouvée
                if (_Items[i].GetLoopID() > MaxLoopID)
                    MaxLoopID = _Items[i].GetLoopID();
            }

            return MaxLoopID;
        }

        /// <summary>
        /// Récupère le nombre max de GID pour une boucle donnée
        /// </summary>
        /// <param name="LoopID">Boucle dans laquelle il faut faire une recherche</param>
        /// <returns>La valeur max de GID pour un LoopID donné</returns>
        public int GetMaxGID(int LoopID)
        {
            int MaxGID = 0;

            // Lecture de toute la liste pour déterminer le Max Group ID pour une boucle donnée
            for (int i = 0; i < _Items.Count(); i++)
            {
                // Si nous sommes dans la bonne boucle et le le GID est > au maxGID, nous le gardons
                if ((_Items[i].GetLoopID() == LoopID) && (_Items[i].GetGID() > MaxGID))
                    MaxGID = _Items[i].GetGID();
            }

            return MaxGID;
        }

        /// <summary>
        /// Donne le numéro pour identifier la commande au sein d'une boucle (le numéro du case pour le switch)
        /// </summary>
        /// <param name="LoopID">Identifiant de la boucle</param>
        /// <param name="GID">Identifiant du GID</param>
        /// <returns>Retourne l'ID au sein de la boucle (l'entête de boucle est supprimé)</returns>
        public int GetActionID(int LoopID, int GID)
        {
            int CurrentActionID = -1;

            for (int i = 0; i < _Items.Count(); i++)
            {
                if ((_Items[i].GetLoopID() == LoopID) && (_Items[i].GetGID() == GID))
                {
                    if(_Items[i].GetName() == "PATTERN_COUNTER")
                        CurrentActionID = int.Parse(_Items[i].GetValue());
                }
            }

            if((CurrentActionID >= LoopID * 100) && (CurrentActionID < (LoopID + 1) * 100))
            {
                return CurrentActionID;
            }

            // Invalid value
            return -1;
        }

        /// <summary>
        /// Récupère le NextActionID pour une boucle et un GID donnés
        /// </summary>
        /// <param name="LoopID">Identifiant de la boucle</param>
        /// <param name="GID">Identifiant du GID</param>
        /// <returns>Idenfiant de la prochaine action à réaliser</returns>
        public int GetNextActionID(int LoopID, int GID)
        {
            int NextActionID = -1;

            for (int i = 0; i < _Items.Count(); i++)
            {
                if ((_Items[i].GetLoopID() == LoopID) && (_Items[i].GetGID() == GID))
                {
                    if (_Items[i].GetName() == "PATTERN_NEXT_ACTION_ID")
                        NextActionID = int.Parse(_Items[i].GetValue());
                }
            }

            // Invalid value
            return NextActionID;
        }


        /// <summary>
        /// Récupère la commande complète d'après la Loop et le GID
        /// </summary>
        /// <param name="LoopID">Identifiant de la boucle</param>
        /// <param name="GID">Identifiant du GID</param>
        /// <returns>La commande complétée de toutes les infos de la LoopID + GID</returns>
        public Command GetCommand(int LoopID, int GID)
        {
            Command ReadCommand = null;
            EnumCmd CmdFromFile = EnumCmd.NotSet;
            EnumCmdType CmdTypeFromFile = EnumCmdType.NotSet;
            string [] ParamsFromFile = null;
            EnumSensorsFlag ActiveSensorsFromFile = EnumSensorsFlag.APPFLAG_NONE;

            // Lecture de toute la liste pour trouver la bonne LoopID et GID
            for (int i = 0; i < _Items.Count(); i++)
            {
                // Si nous sommes dans la bonne LoopID et GID
                if ((_Items[i].GetLoopID() == LoopID) && (_Items[i].GetGID() == GID))
                {
                    // Lecture des informations
                    // Lecture de la commande
                    if (_Items[i].GetName() == "PATTERN_CMD")
                        CmdFromFile = Command.GetCmdFromString(_Items[i].GetValue());

                    // Lecture du type de la commande
                    if (_Items[i].GetName() == "PATTERN_CMD_TYPE")
                        CmdTypeFromFile = Command.GetCmdTypeFromString(_Items[i].GetValue());

                    // Lecture des flags des sensors
                    if (_Items[i].GetName() == "PATTERN_ACTIVE_SENSORS_FLAG")
                        ActiveSensorsFromFile = Command.GetSensorsFlagFromString(_Items[i].GetValue());

                    // Lecture des paramètres
                    if (_Items[i].GetName() == "PATTERN_PARAMS")
                    {
                        ParamsFromFile = Command.GetParamsListFromString(_Items[i].GetValue());
                    }
                }
            }

            // Creation de l'objet de retour
            if (CmdFromFile != EnumCmd.NotSet)
            {
                ReadCommand = new Command(CmdFromFile, CmdTypeFromFile, ParamsFromFile[0], ParamsFromFile[1], ParamsFromFile[2], ParamsFromFile[3], ActiveSensorsFromFile);
            }

            return ReadCommand;
        }

        /// <summary>
        /// Write the current data stored into this object into a specific file
        /// </summary>
        /// <param name="Filename">Name of the file to use for storing data</param>
        /// <returns>True if the file has been written, false otherwise</returns>
        public bool WriteFile(String OutputFilename, String PatternFilename)
        {
            bool Ret = false;
            String ReadPatternLine = null;
            String CheckPatternLine = null;
            int CurrentLoop = -1;
            List<String> PatternBlock = null;

            if ((OutputFilename != null) && (PatternFilename != null) && (_Items.Count() > 0))
            {
                // Create the output file and open the pattern file
                TextFile PatternFile = new TextFile(PatternFilename);
                _File = new TextFile();

                if (_File != null)
                {
                    for (int i = 1; i <= PatternFile.GetSize(); i++)
                    {
                        // Check all line to change patterns into real value
                        ReadPatternLine = PatternFile.GetLine(i);

                        if (ReadPatternLine != null)
                        {
                            // Check line to remove unused char
                            CheckPatternLine = ReadPatternLine;
                            CheckPatternLine = CheckPatternLine.Replace("\t", "");

                            if (CheckPatternLine == "// LoopID = 'LOOPID'")
                            {
                                // Create the pattern block
                                PatternBlock = new List<string>();
                                CurrentLoop++;  // Update the current LoopID
                                _File.AddLine(ReadPatternLine.Replace("'LOOPID'", CurrentLoop.ToString()));
                            }

                            if(CheckPatternLine == "// StructuredFileLoopEnd")
                            {
                                if((PatternBlock != null) && (PatternBlock.Count() > 1))
                                {
                                    // Extact values ordered by GID
                                    List<StructValueList> KeyValues = ExtractValues(CurrentLoop);
                                    if (KeyValues != null)
                                    {
                                        int PatternIterator = 1;    // The first line contains the LOOPID

                                        // Check all items and write only items from current Loop
                                        foreach (StructValueList Values in KeyValues)
                                        {
                                            // Create pattern line
                                            if (PatternIterator >= PatternBlock.Count())
                                                PatternIterator = 1;    // The first line contains the LOOPID

                                            string ExportLine = PatternBlock[PatternIterator];

                                            // We have found value for the current GID, we split it to add them to the specific loop
                                            string[] KeyToAdd = Values.KeyList.Split('|');
                                            string[] ValueToAdd = Values.ValueList.Split('|');

                                            // Change the 'PATTERN_COUNTER' value
                                            ExportLine = ExportLine.Replace("'PATTERN_COUNTER'", Values.CaseID.ToString());

                                            // Write values into final string
                                            for (int j = 0; j < KeyToAdd.Length; j++)
                                            {
                                                ExportLine = ExportLine.Replace("'" + KeyToAdd[j] + "'", ValueToAdd[j]);
                                            }

                                            // Write final line
                                            _File.AddLine(ExportLine);
                                        }
                                    }
                                }

                                // Clear PatternBlock
                                PatternBlock = null;
                            }

                            if (PatternBlock == null)
                            {
                                foreach(StructuredFileKey PatternKey in _Items)
                                {
                                    if(PatternKey.GetLoopID() == -1)
                                    {
                                        ReadPatternLine = ReadPatternLine.Replace("'" + PatternKey.GetName() + "'", PatternKey.GetValue());
                                    }
                                }

                                _File.AddLine(ReadPatternLine);
                            }
                            else
                            {
                                // We are reading a pattern block, we add this line into PatternBlock
                                PatternBlock.Add(ReadPatternLine);
                            }
                              
                        }
                    }
                }
            }

            _File.Save(OutputFilename);
            return (Ret);

        }


        // Private --------------------------------------------------------------------------------
        private struct StructValueList
        {
            public int CaseID;
            public String KeyList;
            public String ValueList;
        }
        
        /// <summary>
        /// Create a list of key value grouped by GID
        /// </summary>
        /// <param name="LoopIDToExtract">Value to extract</param>
        /// <returns>A list that contains all Key and Values into strings</returns>
        private List<StructValueList> ExtractValues(int LoopIDToExtract)
        {
            List<StructValueList> RetNotSorted = null;
            StructValueList ValueToAdd;
            bool IsValueAdded = false;

            if (_Items != null)
            {
                // Read all items and try to add values into list
                foreach (StructuredFileKey CurrentValue in _Items)
                {
                    // Clear added flags
                    IsValueAdded = false;

                    // Check if current value is included in a loop
                    if (CurrentValue.GetLoopID() == LoopIDToExtract)
                    {
                        int CaseID = CurrentValue.GetLoopID() * 100 + CurrentValue.GetGID();

                        if (RetNotSorted == null)
                        {
                            RetNotSorted = new List<StructValueList>();
                            IsValueAdded = false;
                        }
                        else
                        {
                            // Read all ValueList and add the current value (and key) into the correct loop
                            for (int i = 0; i < RetNotSorted.Count(); i++)
                            {
                                if (RetNotSorted[i].CaseID == CaseID)
                                {
                                    ValueToAdd.CaseID = CaseID;
                                    ValueToAdd.KeyList = RetNotSorted[i].KeyList + "|" + CurrentValue.GetName();
                                    ValueToAdd.ValueList = RetNotSorted[i].ValueList + "|" + CurrentValue.GetValue();

                                    RetNotSorted[i] = ValueToAdd;

                                    IsValueAdded = true;
                                }
                            }
                        }
                         
                        // If current value has not been added, we create a new entry
                        if (IsValueAdded == false)
                        {
                            // Create the new entry
                            ValueToAdd.CaseID = CaseID;
                            ValueToAdd.KeyList = CurrentValue.GetName();
                            ValueToAdd.ValueList = CurrentValue.GetValue();

                            RetNotSorted.Add(ValueToAdd);
                        }
                    }
                }
            }

            return RetNotSorted;
        }

        private TextFile _File = null;
        List<StructuredFileKey> _Items = null;
    }
}
