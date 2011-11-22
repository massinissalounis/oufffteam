using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using StrategyGenerator.FileManager;

namespace StrategyGenerator.Strategy
{
    /// <summary>
    /// Class for managing Active Sensors flag (for Oufff2012)
    /// This class reads "AppConfig.h" and generates active flags enables
    /// </summary>
    class CommandActiveSensorsFlag
    {
        // Constructor ----------------------------------------------------------------------------
        /// <summary>
        /// Try to read "AppConfig.h" for getting current flags enabled
        /// </summary>
        public CommandActiveSensorsFlag()
        {   
            List<string> Buffer = null;
            TextFile AppConfigFile = new TextFile();

            // First step : Read "../AppConfig.h"
            //Buffer = AppConfigFile.Load("../AppConfig.h");

            if (Buffer == null)
            {
  //              Buffer = AppConfigFile.Load();
            }

            if(Buffer == null)
                return;

            // Extratct data from buffer
            Extract(Buffer);

        }

        // Public ---------------------------------------------------------------------------------

        // Private --------------------------------------------------------------------------------
        /// <summary>
        /// Exctract data from Buffer
        /// </summary>
        private void Extract(List<string> Buffer)
        {
            int PatternFound = -1;
            int PatternLastId = -1;
            string SubBuffer = null;
            string FlagToAdd = null;

            if (Buffer == null)
                return;

            if (_Flags != null)
                _Flags = null;

            // Read Buffer to find the 'APP_PARAM_APPFLAG_SENSORS_' pattern
            for(int i=0; i<Buffer.Count(); i++)
            {
                // Search for the expected pattern
                PatternFound = Buffer[i].IndexOf(_PatternToFind);
                if(PatternFound > 0)
                {
                    // Search for the first remaining tabulation (to remove it))
                    SubBuffer = Buffer[i].Substring(PatternFound + (_PatternToFind.ToString().Length));
                    PatternLastId = SubBuffer.IndexOf("\t");

                    // If the list is empty, we create it
                    if (_Flags == null)
                        _Flags = new List<string>();

                    if (PatternLastId > 0)
                    {   // A tab has been found, we remove it
                        FlagToAdd = SubBuffer.Substring(0, PatternLastId);
                    }
                    else
                    {   // There is no tab, we add the current string without change
                        FlagToAdd = SubBuffer;
                    }

                    // Check for duplicated items
                    if(FlagToAdd != null)
                    {
                        if (_Flags.Contains(FlagToAdd) == false)
                            _Flags.Add(FlagToAdd);

                        FlagToAdd = null;
                    }

                }
            }

            return;
            
        }


        private string _PatternToFind = "APP_PARAM_APPFLAG_SENSORS_";   // Pattern to use to detect sensors group
        private List<string> _Flags = null;


    }
}
