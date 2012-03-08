using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using StrategyGenerator.FileManager;

namespace StrategyGenerator.Strategy
{
    /// <summary>
    /// List of Command that define a full strategy
    /// </summary>
    class FullStrategy
    {
        // Constructor ----------------------------------------------------------------------------
        /// <summary>
        /// Default constructor : Create an empty strategy
        /// </summary>
        public FullStrategy()
        {
            _StrategyName = "New Strategy";
            _InitialCmd = null;
            _Strategy = null;
        }

        /// <summary>
        /// Create a new FullStrategy object from file
        /// Filename : contains path to file to load
        /// PatternFilename : contains path to pattern file to load
        /// </summary>
        public FullStrategy(string Filename, string PatternFilename)
        {
            if ((Filename == null) || (PatternFilename == null))
            {
                throw(new Exception("Invalid Filename/PatternFilename"));
            }

            // Read files
            StructuredFile StrategyFile = new StructuredFile(Filename);
            StrategyFile.Parse(PatternFilename);

            // Store data into private data
            // Store PATTERN_STRATEGY_NAME
            _StrategyName = StrategyFile.GetValue("PATTERN_STRATEGY_NAME", "Undefined");

            // Store initial cmd (setpos)
            EnumCmd CurrentCmd = Command.GetCmdFromString(StrategyFile.GetValue("PATTERN_INIT_CMD", "App_SetNewPos"));
            EnumCmdType CurrentCmdType = Command.GetCmdTypeFromString(StrategyFile.GetValue("PATTERN_INIT_CMD_TYPE", "NonBlocking"));
            String ParamX = StrategyFile.GetValue("PATTERN_INIT_POS_X", "0");
            String ParamY = StrategyFile.GetValue("PATTERN_INIT_POS_Y", "0");
            String ParamAngle = StrategyFile.GetValue("PATTERN_INIT_POS_ANGLE", "0.0");
            String ActiveSensors = StrategyFile.GetValue("PATTERN_INIT_ACTIVE_SENSORS", "APP_PARAM_APPFLAG_NONE");

            _InitialCmd = new Command(CurrentCmd, CurrentCmdType, null, ParamX, ParamY, ParamAngle, ActiveSensors);
            
            // Read other items (Loops)
            // Try to read all loops
            for (int iLoop = 0; iLoop <= StrategyFile.GetMaxLoopID(); iLoop++)
            {
                for (int iCount = 0; iCount <= StrategyFile.GetMaxGID(iLoop); iCount++)
                {
                    // Read ActionID and NextActionID
                    int ActionID = StrategyFile.GetActionID(iLoop, iCount);
                    int NextActionID = StrategyFile.GetNextActionID(iLoop, iCount);

                    // If current action is valid
                    if (ActionID >= 0)
                    {
                        // Read command data from StratgeyFile
                        Command ReadCommand = StrategyFile.GetCommand(iLoop, iCount);

                        // If current command is valid, we store it
                        if (ReadCommand != null)
                        {
                            // If current list is empty, we create it
                            if (_Strategy == null)
                                _Strategy = new List<StrategyItem>();

                            // Create new entry
                            _Strategy.Add(new StrategyItem(ReadCommand, ActionID, NextActionID));
                        }
                    }
                }
            }
         }

        /// <summary>
        /// Function to export current strategy into extern file
        /// </summary>
        /// <param name="Filename">File to write</param>
        /// <param name="PatternFilename">Pattern to use for writting the file</param>
        /// <returns></returns>
        public bool WriteFile(string Filename, string PatternFilename)
        {
            bool Ret = false;
            List<StructuredFileKey> ExportFile = new List<StructuredFileKey>();
            StructuredFile OutputStructuredFile = null;

            // First, we have to create the StrucuredFileKey in order to create a Strucutred File
            // Create items that are not included into Loop
            ExportFile.Add(new StructuredFileKey(-1, 0, "PATTERN_STRATEGY_NAME", _StrategyName));
            
            // Store initial cmd (setpos)
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_CMD", Command.GetCmdToString(_InitialCmd.Cmd)));
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_CMD_TYPE", Command.GetCmdTypeToString(_InitialCmd.CmdType)));
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_POS_X", _InitialCmd.Param2));
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_POS_Y", _InitialCmd.Param3));
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_POS_ANGLE", _InitialCmd.Param4));
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_ACTIVE_SENSORS", _InitialCmd.ActiveSensors));

            // Create Loops
            foreach (StrategyItem Item in _Strategy)
            {
                ExportFile.Add(new StructuredFileKey(Item.LoopID, Item.GID, "PATTERN_CMD", Command.GetCmdToString(Item.Cmd.Cmd)));
                ExportFile.Add(new StructuredFileKey(Item.LoopID, Item.GID, "PATTERN_CMD_TYPE", Command.GetCmdTypeToString(Item.Cmd.CmdType)));
                ExportFile.Add(new StructuredFileKey(Item.LoopID, Item.GID, "PATTERN_ACTIVE_SENSORS_FLAG", Item.Cmd.ActiveSensors));
                ExportFile.Add(new StructuredFileKey(Item.LoopID, Item.GID, "PATTERN_PARAMS", Item.Cmd.ExportParamsIntoString()));
            }

            OutputStructuredFile = new StructuredFile(ExportFile);
            OutputStructuredFile.WriteFile(Filename, PatternFilename);

            return Ret;
        }

        // Private --------------------------------------------------------------------------------
        private String _StrategyName;               // Nom de la strategie pour le #define
        private Command _InitialCmd;                // Contient les infos relatives à la commande d'initialisation

        private List<StrategyItem> _Strategy;       // Contient tous les objets de la stratégie
    }
}
