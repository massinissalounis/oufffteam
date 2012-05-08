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
        public FullStrategy(String StrategyName)
        {
            if ((StrategyName != null) && (StrategyName != ""))
            {
                _StrategyName = StrategyName;
                _DefaultSpeed = "50";
                _InitialCmd = new Command(EnumCmd.App_SetNewPos, EnumCmdType.NonBlocking, null, "1500", "1000", "0");
                _Strategy = null;
            }
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
            _DefaultSpeed = StrategyFile.GetValue("PATTERN_DEFAULT_SPEED", "50");

            // Store initial cmd (setpos)
            EnumCmd CurrentCmd = Command.GetCmdFromString(StrategyFile.GetValue("PATTERN_INIT_CMD", "App_SetNewPos"));
            EnumCmdType CurrentCmdType = Command.GetCmdTypeFromString(StrategyFile.GetValue("PATTERN_INIT_CMD_TYPE", "NonBlocking"));
            String ParamX = StrategyFile.GetValue("PATTERN_INIT_POS_X", "0");
            String ParamY = StrategyFile.GetValue("PATTERN_INIT_POS_Y", "0");
            String ParamAngle = StrategyFile.GetValue("PATTERN_INIT_POS_ANGLE", "0.0");
            EnumSensorsFlag ActiveSensors = Command.GetSensorsFlagFromString(StrategyFile.GetValue("PATTERN_INIT_ACTIVE_SENSORS", "APP_PARAM_APPFLAG_NONE"));

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
            ExportFile.Add(new StructuredFileKey(-1, 0, "PATTERN_DEFAULT_SPEED", _DefaultSpeed));
            
            // Store initial cmd (setpos)
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_CMD", Command.GetCmdToString(_InitialCmd.Cmd)));
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_CMD_TYPE", Command.GetCmdTypeToString(_InitialCmd.CmdType)));
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_POS_X", _InitialCmd.Param2));
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_POS_Y", _InitialCmd.Param3));
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_POS_ANGLE", _InitialCmd.Param4));
            ExportFile.Add(new StructuredFileKey(-1, 1, "PATTERN_INIT_ACTIVE_SENSORS", Command.GetSensorsFlagToString(_InitialCmd.ActiveSensors)));

            if (_Strategy != null)
            {
                // Create Loops
                foreach (StrategyItem Item in _Strategy)
                {
                    ExportFile.Add(new StructuredFileKey(Item.LoopID, Item.GID, "PATTERN_CMD", Command.GetCmdToString(Item.Cmd.Cmd)));
                    ExportFile.Add(new StructuredFileKey(Item.LoopID, Item.GID, "PATTERN_CMD_TYPE", Command.GetCmdTypeToString(Item.Cmd.CmdType)));
                    ExportFile.Add(new StructuredFileKey(Item.LoopID, Item.GID, "PATTERN_ACTIVE_SENSORS_FLAG", Command.GetSensorsFlagToString(Item.Cmd.ActiveSensors)));
                    ExportFile.Add(new StructuredFileKey(Item.LoopID, Item.GID, "PATTERN_PARAMS", Item.Cmd.ExportParamsIntoString()));
                    ExportFile.Add(new StructuredFileKey(Item.LoopID, Item.GID, "PATTERN_NEXT_ACTION_ID", Item.NextActionID.ToString()));
                }
            }
            OutputStructuredFile = new StructuredFile(ExportFile);
            OutputStructuredFile.WriteFile(Filename, PatternFilename);
           

            return Ret;
        }

        public int Count()
        {
            if (_Strategy == null)
                return 0;

            return (_Strategy.Count());
        }

        public String StrategyName { get { return _StrategyName; } }

        public int DefaultSpeed
        {
            get
            {
                try
                {
                    return Convert.ToInt32(_DefaultSpeed);
                }
                catch (Exception)
                {
                    _DefaultSpeed = "50";
                    return 50;
                }
            }

            set
            {
                int CheckedValue = value;

                if (CheckedValue <= 0) { CheckedValue = 1; }
                if (CheckedValue > 100) { CheckedValue = 100; }
                _DefaultSpeed = CheckedValue.ToString();
            }
       }

        public Command GetCommand(int Index)
        {
            if (Index == 0)
                return _InitialCmd;

            if ((_Strategy != null) && (Index > 0) && (Index <= _Strategy.Count()))
            {
                return _Strategy[Index-1].Cmd;
            }

            return null;
        }

        public int GetActionID(int Index)
        {
            if (Index == 0)
                return 0;

            if ((_Strategy != null) && (Index > 0) && (Index <= _Strategy.Count()))
            {
                return _Strategy[Index - 1].ActionID;
            }

            return (-1);
        }

        public int GetNextActionID(int Index)
        {
            if (Index == 0)
                return 1;

            if ((_Strategy != null) && (Index > 0) && (Index <= _Strategy.Count()))
            {
                return _Strategy[Index - 1].NextActionID;
            }

            return (-1);
        }

        public String GetCommandInfo(int Index)
        {
            if (Index == 0)
                return "0 : " + _InitialCmd.Cmd.ToString();

            if ((_Strategy != null) && (Index > 0) && (Index <= _Strategy.Count()))
            {
                return (_Strategy[Index - 1].ActionID.ToString() + " : " + _Strategy[Index - 1].Cmd.Cmd.ToString());
            }

            return "Cmd not defined";
        }

        public String GetCommandDetailed(int Index)
        {
            String CommandDetailed = "Command Not Defined";

            if (Index == 0)
            {
                CommandDetailed = "0 : ";
                CommandDetailed += _InitialCmd.Cmd.ToString();
                CommandDetailed += " (" + _InitialCmd.CmdType.ToString() + ")";
                CommandDetailed += "\n";

                if(_InitialCmd.Param1 == null)
                    CommandDetailed += "P1: Not Set";
                else
                    CommandDetailed += "P1: " + _InitialCmd.Param1;
                
                if(_InitialCmd.Param2 == null)
                    CommandDetailed += " / P2: Not Set";
                else
                    CommandDetailed += " / P2: " + _InitialCmd.Param2;
    
                if(_InitialCmd.Param3 == null)
                    CommandDetailed += "\nP3: Not Set";
                else
                    CommandDetailed += "\nP3: " + _InitialCmd.Param3;
                
                if(_InitialCmd.Param4 == null)
                    CommandDetailed += " / P4: Not Set";
                else
                    CommandDetailed += " / P4: " + _InitialCmd.Param4;
    
                CommandDetailed += "\n";
                CommandDetailed += "Flag: " + _InitialCmd.ActiveSensors;
            }

            if ((_Strategy != null) && (Index > 0) && (Index <= _Strategy.Count()))
            {
                CommandDetailed = "";
                CommandDetailed += _Strategy[Index - 1].ActionID.ToString();
                CommandDetailed += " : ";
                CommandDetailed += _Strategy[Index - 1].Cmd.Cmd.ToString();
                CommandDetailed += " (" + _Strategy[Index - 1].Cmd.CmdType.ToString() + ")";
                CommandDetailed += "\n";

                if (_Strategy[Index - 1].Cmd.Param1 == null)
                    CommandDetailed += "P1: Not Set";
                else
                    CommandDetailed += "P1: " + _Strategy[Index - 1].Cmd.Param1;

                if (_Strategy[Index - 1].Cmd.Param2 == null)
                    CommandDetailed += " / P2: Not Set";
                else
                    CommandDetailed += " / P2: " + _Strategy[Index - 1].Cmd.Param2;

                if (_Strategy[Index - 1].Cmd.Param3 == null)
                    CommandDetailed += "\nP3: Not Set";
                else
                    CommandDetailed += "\nP3: " + _Strategy[Index - 1].Cmd.Param3;

                if (_Strategy[Index - 1].Cmd.Param4 == null)
                    CommandDetailed += "/ P4: Not Set";
                else
                    CommandDetailed += " / P4: " + _Strategy[Index - 1].Cmd.Param4;

                CommandDetailed += "\n";
                CommandDetailed += "Flag: " + _Strategy[Index - 1].Cmd.ActiveSensors;                
            }

            return CommandDetailed;
        }

        public int GetIndexFromCmdID(int CommandID)
        {
            if (CommandID == 0)
                return 0;

            if (_Strategy != null)
            {
                for (int i = 0; i < _Strategy.Count(); i++)
                {
                    if (CommandID == _Strategy[i].ActionID)
                        return (i + 1);
                }
            }
            return (-1);
        }

        public void RemoveCmd(int Index)
        {
            if(Index <= 0)
                return;

            if ((_Strategy != null) && (Index <= _Strategy.Count()))
            {
                // Check if there is no other command that points to this command
                for (int i = 1; i <= _Strategy.Count; i++)
                {
                    if (Index != i)
                    {
                        if (_Strategy[i - 1].NextActionID == _Strategy[Index - 1].ActionID)
                        {
                            throw (new Exception());
                        }
                    }
                }

                _Strategy.RemoveAt(Index - 1);
            }

            return;
        }

        public void InsertNewCmd_Before(int Index)
        {
            if (Index <= 0)
                throw (new Exception("Invalid Param"));

            if (_Strategy == null)
                throw (new Exception("Invalid Param"));

            if (Index > _Strategy.Count)
                throw (new Exception("Invalid Param"));

            Command NewCommand = new Command(EnumCmd.App_Wait, EnumCmdType.Blocking, "0", "0", "0", "0"); 
            int FreeActionID = GetPrevFreeActionID(_Strategy[Index - 1].ActionID);
            StrategyItem NewStrategyItem = new StrategyItem(NewCommand, FreeActionID, FreeActionID);
            _Strategy.Insert(Index - 1, NewStrategyItem);
        }

        public void InsertNewCmd_After(int Index)
        {
            int FreeActionID = -1;
            if (Index < 0)
                throw (new Exception("Invalid Param"));

            if (_Strategy == null)
            {
                _Strategy = new List<StrategyItem>();
            }

            if (Index > _Strategy.Count)
                throw (new Exception("Invalid Param"));

            Command NewCommand = new Command(EnumCmd.App_Wait, EnumCmdType.Blocking, "0", "0", "0", "0");
            
            if(_Strategy.Count == 0)
                FreeActionID = 1;
            else
                FreeActionID = GetNextFreeActionID(_Strategy[Index - 1].ActionID);

            StrategyItem NewStrategyItem = new StrategyItem(NewCommand, FreeActionID, FreeActionID);
            _Strategy.Insert(Index, NewStrategyItem);
        }

        public void UpdateNextActionID(int Index, String NewNextActionIDString)
        {
            try
            {
                int NewNextActionID = Convert.ToInt32(NewNextActionIDString);

                if(Index < 0)
                    throw (new Exception("Invalid Param"));

                if (_Strategy == null)
                    throw (new Exception("Invalid Param"));

                if (Index > _Strategy.Count)
                    throw (new Exception("Invalid Param"));

                Boolean IsFound = false;

                for (int i = 0; i < _Strategy.Count; i++)
                {
                    if (_Strategy[i].ActionID == NewNextActionID)
                        IsFound = true;
                }

                if (IsFound == true)
                {
                    _Strategy[Index - 1].NextActionID = NewNextActionID;
                }
            }
            catch (Exception)
            {
                return;
            }
        }

        private int GetNextFreeActionID(int MinValue)
        {
            int SelectedValue = MinValue;
            Boolean IsFree = false;

            if(SelectedValue == 0)
                SelectedValue++;

            if(_Strategy == null)
                return SelectedValue;

            while(IsFree == false)
            {
                SelectedValue++;
                IsFree = true;

                for (int i = 0; i < _Strategy.Count; i++)
                {
                    if (_Strategy[i].ActionID == SelectedValue)
                        IsFree = false;
                }
            }
            return SelectedValue;
        }

        private int GetPrevFreeActionID(int MaxValue)
        {
            int SelectedValue = MaxValue;
            Boolean IsFree = false;

            if (SelectedValue == 0)
                return -1;

            if (_Strategy == null)
                return MaxValue;
            
            while((IsFree == false) && (SelectedValue > 0))
            {
                SelectedValue--;
                IsFree = true;

                for (int i = 0; i < _Strategy.Count; i++)
                {
                    if (_Strategy[i].ActionID == SelectedValue)
                        IsFree = false;
                }
            }
            if (SelectedValue <= 0)
                SelectedValue = GetNextFreeActionID(MaxValue);

            return SelectedValue;
        }

        // Private --------------------------------------------------------------------------------
        private String _StrategyName;               // Nom de la strategie pour le #define
        private Command _InitialCmd;                // Contient les infos relatives à la commande d'initialisation
        private String _DefaultSpeed;               // Contient la vitesse par defaut pour la strategie

        private List<StrategyItem> _Strategy;       // Contient tous les objets de la stratégie

    }
}
