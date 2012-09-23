using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace StrategyGenerator.FileManager
{
    public class TextFile
    {
        // Constructeur ---------------------------------------------------------------------------
        ///<summary>
        /// Open FileBrowser and ask for a file to load. Once selected, file is loaded into a buffer
        ///</summary>
        public TextFile()
        {
            // Clear current content
            _FileContents = null;
        }

        ///<summary>
        /// Open FileBrowser and ask for a file to load. Once selected, file is loaded into a table of string
        ///</summary>
        public TextFile(String FileName)
        {
            // Clear current content
            _FileContents = null;
            Load(FileName);
        }

        // Public ---------------------------------------------------------------------------------
        ///<summary>
        /// Open FileBrowser and ask for a file to save. Once selected, TextFile object is written into.
        ///</summary>
        public bool Save()
        {
            try
            {
                // Ask for file to save
                Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
                dlg.Filter = "C Files|*.c|All Files|*.*";
                dlg.ShowDialog();

                return Save(dlg.FileName.ToString());
            }
            catch (Exception ex)
            {
                // Code exécuté en cas d'exception 
                throw ex;
            }

        }

        ///<summary>
        /// Write TextFile object into FileName File.
        ///</summary>
        public bool Save(String FileName)            
        {
            try
            {
                if (FileName == "")
                    return false;

                if ((_FileContents == null) || (_FileContents.Count() == 0))
                {
                    Console.WriteLine("TextFile : CurrentFile is empty");
                    return false;
                }

                // Instanciation du StreamWriter avec passage du nom du fichier 
                StreamWriter monStreamWriter = new StreamWriter(FileName);

                //Ecriture du texte dans votre fichier
                for (int i = 0; i < _FileContents.Count(); i++)
                {
                    monStreamWriter.WriteLine(_FileContents[i]);
                }

                // Fermeture du StreamWriter 
                monStreamWriter.Close();
                return true;
            }
            catch (Exception ex)
            {
                // Code exécuté en cas d'exception 
                throw ex;
            }

        }

        ///<summary>
        /// Open FileBrowser and ask for a file to load. 
        /// Once selected, the content of selected file is added at the end of TextFile object.
        ///</summary>
        public void Load()
        {
            // Ask for file to load
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.Filter = "C Files|*.c|All Files|*.*";
            dlg.ShowDialog();

            // Read data 
            Load(dlg.FileName.ToString());
        }

        ///<summary>
        /// The content of FileName file is added at the end of TextFile object.
        ///</summary>
        public void Load(String FileName)
        {
            if ("" == FileName)
            {
                return;
            }

            try
            {
                // Create object for storing line
                _FileContents = new List<String>();

                // Création d'une instance de StreamReader pour permettre la lecture de notre fichier 
                StreamReader monStreamReader = new StreamReader(FileName);

                while (monStreamReader.EndOfStream != true)
                {
                    _FileContents.Add(monStreamReader.ReadLine());
                }

                // Fermeture du StreamReader (attention très important) 
                monStreamReader.Close();

                if (_FileContents.Count() == 0)
                {
                    _FileContents = null;
                    return;
                }
            
            }
            catch (Exception ex)
            {
                _FileContents = null;
                Console.WriteLine("TextFile = " + ex.Message);
                return;
            }
        }

         ///<summary>
        /// Returns the LineNumer-th line between (1 and MaxLine).
        ///</summary>
        public String GetLine(int LineNumber)
        {
            if ((_FileContents == null) || (_FileContents.Count() == 0) || (LineNumber <= 0) || (LineNumber > _FileContents.Count()))
                return null;

            return _FileContents[LineNumber-1];
        }

        ///<summary>
        /// Remove unused line (empty line or comment line)
        /// Line iterator is reset to 0 after this call
        ///</summary>
        public void RemoveUnusedLine()
        {
            if (null == _FileContents)
                return;

            for (int i = _FileContents.Count()-1; i >= 0; i--)
            {
                // Remove tabulations
                _FileContents[i] = _FileContents[i].Replace("\t", "");
                
                // Remove unecessary space
                for (int j = 20; j > 1; j--)
                {
                    string stringToRemove = new string(new char[j]);
                    stringToRemove = stringToRemove.Replace("\0", " ");

                    _FileContents[i] = _FileContents[i].Replace(stringToRemove, " ");
                }
                if ((_FileContents[i].Length > 0) && (_FileContents[i].Substring(0, 1) == " "))
                {
                    _FileContents[i] = _FileContents[i].Substring(1);
                }

                // Remove all emtpy line
                if((_FileContents[i].ToString() == "") || (_FileContents[i].ToString() == " "))
                {
                    _FileContents.RemoveAt(i);
                }
            }

            return;
        }

        ///<summary>
        /// Remove a specific line (pointed by LineNumber)
        ///</summary>
        public void RemoveLine(int LineNumber)
        {
            if (null == _FileContents)
                return;

            if ((LineNumber <= 0) || (LineNumber > _FileContents.Count()))
                return;

            _FileContents.RemoveAt(LineNumber - 1);
        }

            
        ///<summary>
        /// Search the pattern 'TextToFind' into current file. All lines that contain 'TextToFind are returned
        ///</summary>
        public List<String> Search(String TextToFind)
        {
            List<String> Result = null;

            if((TextToFind == null) || (_FileContents == null) || (_FileContents.Count() == 0))
                return null;

            for (int i = 0; i < _FileContents.Count(); i++)
            {
                // Search pattern into all lines
                if(_FileContents[i].Contains(TextToFind) == true)
                {
                    if(Result == null)
                        Result = new List<string>();

                    Result.Add(_FileContents[i].ToString());
                }
            }

            return Result;
        }


        ///<summary>
        /// Returns the nb of line 
        ///</summary>
        public int GetSize()
        {
            if (_FileContents == null)
                return 0;

            return _FileContents.Count();
        }

        /// <summary>
        /// Add a new line at the end of the current file
        /// </summary>
        /// <param name="LineToAdd">Line to Add</param>
        public void AddLine(String LineToAdd)
        {
            if (LineToAdd != null)
            {
                if (_FileContents == null)
                    _FileContents = new List<string>();

                _FileContents.Add(LineToAdd);
            }
        }

        /// <summary>
        /// Add a new line at the index specified
        /// </summary>
        /// <param name="LineToAdd">Line to add</param>
        /// <param name="IndexToAdd">Index where the line will be inserted</param>
        public void AddLine(String LineToAdd, int IndexToAdd)
        {
            if((LineToAdd != null) && (IndexToAdd >= 0))
            {
                _FileContents.Insert(IndexToAdd, LineToAdd);
            }
        }


        // Private --------------------------------------------------------------------------------
        private List<String>    _FileContents;              // Use to store last file name
    }
}
