using GalaSoft.MvvmLight;
using StrategyGenerator2.Model;
using System.Collections.ObjectModel;
using StrategyGenerator2.StrategyManager;
using System;

namespace StrategyGenerator2.ViewModel
{
    public class RobotActionVM : ViewModelBase
    {
        // Public ---------------------------------------------------------------------------------
        public RobotActionVM()
        {
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

        public EnumCmd SelectedCmd
        {
            get
            {
                EnumCmd Ret = EnumCmd.NotSet;
                if (_currentRobotAction != null)
                    Ret = _currentRobotAction.cmd;
                return Ret; 
            }
            set
            {
                if (_currentRobotAction != null)
                {
                    _currentRobotAction.cmd = value;
                    UpdateData(null, null);
                }
                return;
            }
        }

        public EnumCmdType SelectedCmdType
        {
            get
            {
                EnumCmdType Ret = EnumCmdType.CmdType_NotSet;
                if (_currentRobotAction != null)
                    Ret = _currentRobotAction.cmdType;

                return Ret; 
            }
            set
            {
                if (_currentRobotAction != null) 
                    _currentRobotAction.cmdType = value;

                return;
            }
        }

        public String Param1
        {
            get
            {
                String Ret = null;

                if (_currentRobotAction != null)
                    Ret = _currentRobotAction.param1;

                return Ret;
            }
            set
            {
                if (_currentRobotAction != null)
                    _currentRobotAction.param1 = value;

                return;
            }
        }
        public String Param2
        {
            get
            {
                String Ret = null;

                if (_currentRobotAction != null)
                    Ret = _currentRobotAction.param2;

                return Ret;
            }
            set
            {
                if (_currentRobotAction != null)
                    _currentRobotAction.param2 = value;

                return;
            }
        }
        public String Param3
        {
            get
            {
                String Ret = null;

                if (_currentRobotAction != null)
                    Ret = _currentRobotAction.param3;

                return Ret;
            }
            set
            {
                if (_currentRobotAction != null)
                    _currentRobotAction.param3 = value;

                return;
            }
        }
        public String Param4
        {
            get
            {
                String Ret = null;

                if (_currentRobotAction != null)
                    Ret = _currentRobotAction.param4;

                return Ret;
            }
            set
            {
                if (_currentRobotAction != null)
                    _currentRobotAction.param4 = value;

                return;
            }
        }


        // Private --------------------------------------------------------------------------------
        protected MainModel _mainModel = null;                      // Lien vers le model
        protected RobotAction _currentRobotAction;                  // Action courante

        private void UpdateData(object sender, EventArgs e)
        {
            _currentRobotAction = _mainModel.selectedRobotAction;
            RaisePropertyChanged("SelectedCmd");
            RaisePropertyChanged("SelectedCmdType");
            RaisePropertyChanged("Param1");
            RaisePropertyChanged("Param2");
            RaisePropertyChanged("Param3");
            RaisePropertyChanged("Param4");

            return;
        }
    }
}