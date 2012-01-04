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
        public List<String> Parse(TextFile PatternFile)
        {
            List<String> PatternLine = null;
            List<String> PatternLoop = null;
            List<String> LineToCheck = null;
            List<String> LoopToCheck = null;
            List<String> Result = null;
            String CurrentLine, TestLine;

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
                            PatternLen++;

                            // Remove added line (for current file)
                            _File.RemoveLine(iCurrentLine);
                        }
                        // Remove added line (for pattern file)
                        PatternFile.RemoveLine(iCurrentLine);

                        CurrentLine = PatternFile.GetLine(iCurrentLine);
                    }

                    iterator = PatternLoopInitialValue;
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
                        if (iterator >= PatternLoopInitialValue + PatternLen)
                            iterator = PatternLoopInitialValue;
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

            // Create the result list
            if (PatternLine != null)
            {
                if (Result == null)
                    Result = new List<string>();


            }

            return null;
        }

        // Private --------------------------------------------------------------------------------
        private TextFile _File = null;
    }
}
