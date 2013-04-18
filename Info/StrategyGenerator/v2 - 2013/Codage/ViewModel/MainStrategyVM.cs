using GalaSoft.MvvmLight;
using StrategyGenerator2.Model;
using System.Windows;
using StrategyGenerator2.View;
using System.Collections.ObjectModel;
using StrategyGenerator2.StrategyManager;
using System.Collections.Generic;

namespace StrategyGenerator2.ViewModel
{
    public class MainStrategyVM : ViewModelBase
    {
        // Public ---------------------------------------------------------------------------------
        public MainStrategyVM()
        {
            _mainModel = MainModel.GetInstance;
            _currentStrategy = null;
        }

        // Properties -----------------------------------------------------------------------------
        /// <summary>
        /// Fonction pour lister les actions du robot
        /// </summary>
        public ObservableCollection<RobotAction> ListRobotAction
        {
            get
            {
                ObservableCollection<RobotAction> Ret = null;

                if (_currentStrategy.GetMainStrategy() != null)
                {
                    Ret = new ObservableCollection<RobotAction>();
                    foreach (RobotAction currentRobotAction in _currentStrategy.GetMainStrategy().GetAllActions())
                    {
                        Ret.Add(currentRobotAction);
                    }
                }
                return Ret;
            }

            set
            {
            }
        }

        public RobotAction SelectedRobotAction
        {
            get
            { return null; }
            set
            {
                _selectedRobotAction = value;
                return;
            }
        }

        public int SelectedRobotActionIndex
        {
            get
            { return _selectedRobotActionIndex; }
            set
            {
                _selectedRobotActionIndex = value;
                return;
            }
        }



        // Private --------------------------------------------------------------------------------
        protected MainModel _mainModel = null;                      // Lien vers le model
        protected Strategy _currentStrategy = null;                 // Lien vers la stratégie actuelle
        protected RobotAction _selectedRobotAction = null;          // Action selectionnée
        protected int _selectedRobotActionIndex = -1;               // Index de l'action selectionnée
    }
}