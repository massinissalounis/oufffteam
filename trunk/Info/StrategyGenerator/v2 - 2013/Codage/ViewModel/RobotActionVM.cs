using GalaSoft.MvvmLight;
using StrategyGenerator2.Model;
using System.Collections.ObjectModel;
using StrategyGenerator2.StrategyManager;
using System;
using System.Collections.Generic;
using System.Windows.Input;
using GalaSoft.MvvmLight.Command;
using StrategyGenerator2.StrategyViewer;

namespace StrategyGenerator2.ViewModel
{
    public class RobotActionVM : ViewModelBase
    {
        // Public ---------------------------------------------------------------------------------
        public RobotActionVM()
        {
            _modifiedRobotAction = new RobotAction();
            _mainModel = MainModel.GetInstance;
            _mainModel.RobotActionChanged += new EventHandler(UpdateData);
        }

        // Properties -----------------------------------------------------------------------------
        /// <summary>
        /// Fonction pour lister les commandes disponibles
        /// </summary>
        public ObservableCollection<EnumCmd> ListCmd
        {
            get
            {
                ObservableCollection<EnumCmd> Ret = new ObservableCollection<EnumCmd>();

                foreach (EnumCmd currentValue in Enum.GetValues(typeof(EnumCmd)))
                {
                    if (EnumCmd.NotSet != currentValue)
                        Ret.Add(currentValue);
                }

                return Ret;
            }

            set
            {
            }
        }

        /// <summary>
        /// Fonction pour lister les type de commande
        /// </summary>
        public ObservableCollection<EnumCmdType> ListCmdType
        {
            get
            {
                ObservableCollection<EnumCmdType> Ret = new ObservableCollection<EnumCmdType>();

                foreach (EnumCmdType currentValue in Enum.GetValues(typeof(EnumCmdType)))
                {
                    if (EnumCmdType.CmdType_NotSet != currentValue)
                        Ret.Add(currentValue);
                }

                return Ret;
            }

            set
            {
            }
        }

        public ObservableCollection<Sensors> ListActiveSensors
        {
            get
            {
                ObservableCollection<Sensors> Ret = new ObservableCollection<Sensors>();

                if (_modifiedRobotAction != null)
                {
                    foreach (Sensors currentSensor in _modifiedRobotAction.activeSensors.GetAllSensors)
                    {
                        Ret.Add(currentSensor);
                    }
                }                        

                return Ret;
            }

            set
            {
            }

        }

        public EnumCmd SelectedCmd
        {
            get
            {
                EnumCmd Ret = EnumCmd.NotSet;
                if (_modifiedRobotAction != null)
                    Ret = _modifiedRobotAction.cmd;
                return Ret; 
            }
            set
            {
                if (_modifiedRobotAction != null)
                {
                    _modifiedRobotAction.cmd = value;
                    RaisePropertyChangedGrouped();
                }
                return;
            }
        }

        public EnumCmdType SelectedCmdType
        {
            get
            {
                EnumCmdType Ret = EnumCmdType.CmdType_NotSet;
                if (_modifiedRobotAction != null)
                    Ret = _modifiedRobotAction.cmdType;

                return Ret; 
            }
            set
            {
                if (_modifiedRobotAction != null)
                {
                    _modifiedRobotAction.cmdType = value;
                }

                return;
            }
        }

        public String Param1
        {
            get
            {
                String Ret = null;

                if (_modifiedRobotAction != null)
                    Ret = _modifiedRobotAction.param1;

                return Ret;
            }
            set
            {
                if (_modifiedRobotAction != null)
                {
                    _modifiedRobotAction.param1 = value;
                    RaiseDisplayPropertyChanged();
                }

                return;
            }
        }
        public String Param2
        {
            get
            {
                String Ret = null;

                if (_modifiedRobotAction != null)
                    Ret = _modifiedRobotAction.param2;

                return Ret;
            }
            set
            {
                if (_modifiedRobotAction != null)
                {
                    _modifiedRobotAction.param2 = value;
                    RaiseDisplayPropertyChanged();
                }

                return;
            }
        }
        public String Param3
        {
            get
            {
                String Ret = null;

                if (_modifiedRobotAction != null)
                    Ret = _modifiedRobotAction.param3;

                return Ret;
            }
            set
            {
                if (_modifiedRobotAction != null)
                {
                    _modifiedRobotAction.param3 = value;
                    RaiseDisplayPropertyChanged();
                }

                return;
            }
        }
        public String Param4
        {
            get
            {
                String Ret = null;

                if (_modifiedRobotAction != null)
                    Ret = _modifiedRobotAction.param4;

                return Ret;
            }
            set
            {
                if (_modifiedRobotAction != null)
                {
                    _modifiedRobotAction.param4 = value;
                    RaiseDisplayPropertyChanged();
                }

                return;
            }
        }

        public String CmdID
        {
            get
            {
                if (_modifiedRobotAction != null)
                    return _modifiedRobotAction.ID.ToString();
                else
                    return "";
            }

            set
            {
                int intValue = -1;
                int currentSubStrategyID = _modifiedRobotAction.ID - (_modifiedRobotAction.ID % 100);

                // On verifie si la valeur est utilisable en integer
                if (int.TryParse(value, out intValue) == true)
                {
                    // On verifie si on a la possibilité d'utiliser cette ID
                    if ((intValue >= currentSubStrategyID) && (intValue < currentSubStrategyID + 100))
                    {
                        // Sinon on verifie si la nouvelle valeur est utilisable
                        if (_mainModel.selectedStrategy.FindRobotActionByID(intValue) == null)
                        {
                            _modifiedRobotAction.ID = intValue;
                        }
                    }
                }

            }
        }

        public string NextID
        {
            get
            {
                if (_modifiedRobotAction != null)
                    return _modifiedRobotAction.nextID.ToString();
                else
                    return "";
            }

            set
            {
                int intValue = -1;
                int currentSubStrategyID = _modifiedRobotAction.ID - (_modifiedRobotAction.ID % 100);

                // On verifie si la valeur est utilisable en integer
                if (int.TryParse(value, out intValue) == true)
                {
                    // Si la valeur est -1, on la garde (valeur desactivée)
                    if (intValue == -1)
                    {
                        _modifiedRobotAction.nextID = intValue;
                    }
                    else
                    {
                        // On verifie si on a la possibilité d'utiliser cette ID
                        if ((currentSubStrategyID == 0) || (intValue < 100) || ((intValue >= currentSubStrategyID) && (intValue < currentSubStrategyID + 100)))
                        {
                            // Sinon on verifie si la nouvelle valeur est utilisable
                            if (_mainModel.selectedStrategy.FindRobotActionByID(intValue) != null)
                            {
                                _modifiedRobotAction.nextID = intValue;
                            }
                        }
                    }
                }
            }
        }
 
        public String TimeoutID
        {
            get
            {
                if (_modifiedRobotAction != null)
                    return _modifiedRobotAction.timeoutID.ToString();
                else
                    return "";
            }

            set
            {
                int intValue = -1;

                // On verifie si la valeur est utilisable en integer
                if (int.TryParse(value, out intValue) == true)
                {
                    // Si la valeur est -1, on la garde (valeur desactivée)
                    if (intValue == -1)
                    {
                        _modifiedRobotAction.timeoutID = intValue;
                    }
                    else
                    {
                        // Sinon on verifie si la nouvelle valeur est utilisable
                        if (_mainModel.selectedStrategy.FindRobotActionByID(intValue) != null)
                        {
                            _modifiedRobotAction.timeoutID = intValue;
                        }
                    }
                }
            }
        }

        public Boolean isFormEnabled
        {
            get
            {
                if (_currentRobotAction != null)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            set { }
        }

        public ICommand CmdUpdate
        {
            get { return new RelayCommand(ValidateParams); }
            set { }
        }
        public ICommand CmdAdd
        {
            get { return new RelayCommand(AddNewCmd); }
            set { }
        }

        public String initPos
        {
            get
            {
                String Ret = "";

                if (_modifiedDisplayRobot != null)
                {
                    List<RobotPos> listInitPos = _modifiedDisplayRobot.GetInitialPos();
                    if (listInitPos != null)
                    {
                        foreach (RobotPos currentRobotPos in listInitPos)
                        {
                            if (Ret != "")
                                Ret = Ret + " ou ";

                            Ret = Ret + "(";
                            Ret = Ret + currentRobotPos.x;
                            Ret = Ret + ",";
                            Ret = Ret + currentRobotPos.y;
                            Ret = Ret + ",";
                            Ret = Ret + currentRobotPos.angle;
                            Ret = Ret + ")";
                        }
                    }

                }

                return Ret;
            }
            set { }
        }

        public String finalPos
        {
            get
            {
                String Ret = "";

                if (_modifiedDisplayRobot != null)
                {
                    List<RobotPos> listFinalPos = _modifiedDisplayRobot.GetOutputPos();
                    if (listFinalPos != null)
                    {
                        foreach (RobotPos currentRobotPos in listFinalPos)
                        {
                            if (Ret != "")
                                Ret = Ret + " ou ";

                            Ret = Ret + "(";
                            Ret = Ret + currentRobotPos.x;
                            Ret = Ret + ",";
                            Ret = Ret + currentRobotPos.y;
                            Ret = Ret + ",";
                            Ret = Ret + currentRobotPos.angle;
                            Ret = Ret + ")";
                        }
                    }

                }

                return Ret;
            }
            set { }
        }

        // Private --------------------------------------------------------------------------------
        private MainModel _mainModel = null;                        // Lien vers le model
        private RobotAction _currentRobotAction;                    // Action courante
        private RobotAction _modifiedRobotAction;                   // Action pour la mise à jour
        private DisplayPos _modifiedDisplayRobot = null;             // Objet pour le rendu graphique


        private void UpdateData(object sender, EventArgs e)
        {
            _currentRobotAction = _mainModel.selectedRobotAction;

            if (_currentRobotAction != null)
            {
                // Copie de l'objet en local
                _modifiedRobotAction.ID = _currentRobotAction.ID;
                _modifiedRobotAction.cmd = _currentRobotAction.cmd;
                _modifiedRobotAction.cmdType = _currentRobotAction.cmdType;
                _modifiedRobotAction.nextID = _currentRobotAction.nextID;
                _modifiedRobotAction.param1 = _currentRobotAction.param1;
                _modifiedRobotAction.param2 = _currentRobotAction.param2;
                _modifiedRobotAction.param3 = _currentRobotAction.param3;
                _modifiedRobotAction.param4 = _currentRobotAction.param4;
                _modifiedRobotAction.timeoutID = _currentRobotAction.timeoutID;
                _modifiedRobotAction.activeSensors.ForceSensors(_currentRobotAction.activeSensors.Activated);

                LoadDisplayPos();
            }
            RaisePropertyChangedGrouped();
        }

        private void LoadDisplayPos()
        {
            if ((_mainModel.selectedStrategyDisplay != null) && (_modifiedRobotAction != null))
            {
                DisplayPos currentDisplayPos = _mainModel.selectedStrategyDisplay.GetDisplayPosByID(_currentRobotAction.ID);

                if (currentDisplayPos != null)
                {
                    _modifiedDisplayRobot = new DisplayPos(_modifiedRobotAction);
                    _modifiedDisplayRobot.AddInitialPos(currentDisplayPos.GetInitialPos());
                }
            }
        }

        private void RaisePropertyChangedGrouped()
        {
            RaisePropertyChanged("CmdID");
            RaisePropertyChanged("NextID");
            RaisePropertyChanged("TimeoutID");
            RaisePropertyChanged("SelectedCmd");
            RaisePropertyChanged("SelectedCmdType");
            RaisePropertyChanged("Param1");
            RaisePropertyChanged("Param2");
            RaisePropertyChanged("Param3");
            RaisePropertyChanged("Param4");
            RaisePropertyChanged("ListActiveSensors");
            RaisePropertyChanged("isUpdateButtonEnabled");
            RaisePropertyChanged("isFormEnabled");
            RaisePropertyChanged("initPos");
            RaisePropertyChanged("finalPos");

            return;
        }

        private void RaiseDisplayPropertyChanged()
        {
            RaisePropertyChanged("initPos");
            RaisePropertyChanged("finalPos");
        }

        private void ValidateParams()
        {
            // Mise à jour des paramètres
            if ((_modifiedRobotAction != null) && (_currentRobotAction != null))
            {
                if ((_currentRobotAction.ID != _modifiedRobotAction.ID) && (_currentRobotAction.ID % 100 != 0))
                {
                    // Mise à jour des données pour toutes la stratégies
                    _mainModel.ChangeCmdID(_currentRobotAction.ID, _modifiedRobotAction.ID);
                }

                _currentRobotAction.cmd = _modifiedRobotAction.cmd;
                _currentRobotAction.cmdType = _modifiedRobotAction.cmdType;
                _currentRobotAction.nextID = _modifiedRobotAction.nextID;
                _currentRobotAction.param1 = _modifiedRobotAction.param1;
                _currentRobotAction.param2 = _modifiedRobotAction.param2;
                _currentRobotAction.param3 = _modifiedRobotAction.param3;
                _currentRobotAction.param4 = _modifiedRobotAction.param4;
                _currentRobotAction.timeoutID = _modifiedRobotAction.timeoutID;
                _currentRobotAction.activeSensors.ForceSensors(_modifiedRobotAction.activeSensors.Activated);
            }

            _mainModel.UpdateRobotActionList();
        }

        private void AddNewCmd()
        {           
            int newID = -1;
            RobotAction newRobotAction = null;

            if (_mainModel.selectedSubStrategy != null)
            {
                newID = _mainModel.selectedSubStrategy.GetFreeID();

                if (newID > 0)
                {
                    newRobotAction = new RobotAction(newID);
                    newRobotAction.cmd = EnumCmd.App_Wait;
                    newRobotAction.nextID = _currentRobotAction.nextID;
                    _currentRobotAction.nextID = newID;

                    _mainModel.selectedSubStrategy.AddAction(newRobotAction);
                    _mainModel.UpdateRobotActionList();
                }
            }
        }
    }
}