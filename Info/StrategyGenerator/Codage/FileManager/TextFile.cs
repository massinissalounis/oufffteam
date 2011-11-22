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
        public bool WriteFile()
        {
            try
            {
                // Ask for file to save
                Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
                dlg.Filter = "C Files|*.c|All Files|*.*";
                dlg.ShowDialog();

                return WriteFile(dlg.FileName.ToString());
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
        public bool WriteFile(String FileName)            
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
        /// Returns the next line from TextFile object.
        ///</summary>
        public String GetNextLine()
        {
            String CurrentLine = null;

            if ((_FileContents == null) || (_FileContents.Count() == 0) || (_LineIterator > _FileContents.Count()))
                return null;

            CurrentLine = _FileContents[_LineIterator];
            _LineIterator = _LineIterator + 1;

            if (_LineIterator > _FileContents.Count())
                _LineIterator = _FileContents.Count();

            return CurrentLine;
        }

        ///<summary>
        /// Returns the previous line from TextFile object.
        ///</summary>
        public String GetPreviousLine()
        {
            String CurrentLine = null;

            if ((_FileContents == null) || (_FileContents.Count() == 0) || (_LineIterator <= 0))
                return null;

            _LineIterator = _LineIterator - 2;

            if (_LineIterator <= 0)
                _LineIterator = 0;

            CurrentLine = _FileContents[_LineIterator];

            return CurrentLine;
        }


        // Private --------------------------------------------------------------------------------
        // Var
        private List<String>    _FileContents;              // Use to store last file name
        int                     _LineIterator;              // Iterator used to navigate into TextFile object
       
    }
}
