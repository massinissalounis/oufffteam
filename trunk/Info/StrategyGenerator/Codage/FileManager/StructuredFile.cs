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
            TextFile FileToLoad = new TextFile();
           // _File = FileToLoad.Load();

            FileToLoad = null;
        }

        public StructuredFile(String Pathname)
        {
            TextFile FileToLoad = new TextFile();
           // _File = FileToLoad.Load(Pathname);

            FileToLoad = null;
        }

        // Public ---------------------------------------------------------------------------------
//        public List<String> Parse(TextFile PatternFile, List<String> KeyToFind)
//        {
//            if ((null == PatternFile) || (null == KeyToFind))
//                return null;
//        }

        // Private --------------------------------------------------------------------------------
        private List<String> _File = null;
    }
}
