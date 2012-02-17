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
        public StructuredFile()
        {
            _File = new TextFile();
            _File.Load();
        }

        public StructuredFile(String Pathname)
        {
            _File = new TextFile(Pathname);
        }

        // Public ---------------------------------------------------------------------------------
        public List<StructuredFileKey> Parse(TextFile PatternFile)
        {
            List<String> PatternLine = null;
            List<String> PatternLoop = null;
            List<String> LineToCheck = null;
            List<String> LoopToCheck = null;
            List<StructuredFileKey> Result = null;
            String CurrentLine, TestLine, ResultPattern, ResultValue;

            int iCurrentLine = 0, PatternLen = 0, iterator = 0, PatternLoopInitialValue = 0;

            if ((_File == null) || (null == PatternFile))
                return null;

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
                if (Result == null)
                    Result = new List<StructuredFileKey>();

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
                                        Result.Add(new StructuredFileKey(-1, iCurrentLine, ResultPattern, ResultValue));
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

                if (Result == null)
                    Result = new List<StructuredFileKey>();

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

                                        // if the correct kay has been found
                                        if (LoopToCheck[iCurrentLine].Substring(iCurrentValueChar, 1) == sLastChar)
                                        {
                                            ResultValue = LoopToCheck[iCurrentLine].Substring(iFirstChar, iCurrentValueChar - iFirstChar);
                                            Result.Add(new StructuredFileKey(CurrentLoopID, iCurrentLine, ResultPattern, ResultValue));
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

            return Result;
        }

        // Private --------------------------------------------------------------------------------
        private TextFile _File = null;
    }
}
