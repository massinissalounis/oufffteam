using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using StrategyGenerator2.FileManager;

namespace StrategyGenerator2.Model
{
    class MainModel
    {
        // Public ---------------------------------------------------------------------------------
        public static MainModel Instance
        {
            get
            {
                if (_model == null)
                {
                    _model = new MainModel();
                }
                return _model;
            }
        }


        // Private --------------------------------------------------------------------------------
        // Declaration du singleton
        private static MainModel _model;

        // Constructeur privé (dû au singleton)
        private MainModel()
        {
            // Test !! ########################################################
            TextFile FichierTest = new TextFile();
            FichierTest.Load("D:/Robotique/Info/StrategyGenerator/v2 - 2013/Test/TestLoad.txt");
            FichierTest.Save();
            FichierTest.SaveTo("D:/Robotique/Info/StrategyGenerator/v2 - 2013/Test/TestLoadOutput.txt");

            // ################################################################

            return;
        }

    }
}
