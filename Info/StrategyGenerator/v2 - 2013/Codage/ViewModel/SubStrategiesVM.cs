using GalaSoft.MvvmLight;
using StrategyGenerator2.Model;
using System.Windows;
using StrategyGenerator2.View;
using System.Collections.ObjectModel;
using StrategyGenerator2.StrategyManager;
using System.Collections.Generic;

namespace StrategyGenerator2.ViewModel
{
    public class SubStrategiesVM : ViewModelBase
    {
        // Public ---------------------------------------------------------------------------------
        public SubStrategiesVM()
        {
            _mainModel = MainModel.GetInstance;
            _currentStrategy = null;
        }



        // Properties -----------------------------------------------------------------------------
        /// <summary>
        /// Fonction pour lister les sous-stratégies
        /// </summary>
        public ObservableCollection<SubStrategy> ListSubStrategies 
        {
            get
            {
                ObservableCollection<SubStrategy> Ret = null;

                if (_currentStrategy != null)
                {
                    if(_currentStrategy.GetAllSubStrategy() != null)
                    {
                        Ret = new ObservableCollection<SubStrategy>();
                        foreach(SubStrategy currentSubStrategy in _currentStrategy.GetAllSubStrategy())
                        {
                            Ret.Add(currentSubStrategy);
                        }
                    }
                }
                return Ret;
            }

            set
            {

            }
        }

        /// <summary>
        /// Fonction pour lister les actions du robot
        /// </summary>
        public ObservableCollection<RobotAction> ListRobotAction
        {
            get
            {
                ObservableCollection<RobotAction> Ret = null;

                if (_selectedSubStrategy != null)
                {
                    if (_selectedSubStrategy.Count() > 0)
                    {
                        Ret = new ObservableCollection<RobotAction>();
                        foreach (RobotAction currentRobotAction in _selectedSubStrategy.GetAllActions())
                        {
                            Ret.Add(currentRobotAction);
                        }
                    }
                }
                return Ret;
            }

            set
            {
            }
        }

        public SubStrategy SelectedSubStrategy
        {
            get
            { return null; }
            set
            {
                _selectedSubStrategy = value;
                RaisePropertyChanged("ListRobotAction");
                return;
            }
        }

        public int SelectedSubStrategyIndex
        {
            get
            { return _selectedSubStrategyIndex; }
            set
            {
                _selectedSubStrategyIndex = value;
                return;
            }
        }

        public RobotAction SelectedRobotAction
        {
            get
            { return null; }
            set
            {
                _selectedRobotAction = value;
                _mainModel.selectedRobotAction = value;

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
        protected SubStrategy _selectedSubStrategy = null;          // Sous-strategie selectionnée
        protected int _selectedSubStrategyIndex = -1;               // Index de la sous-stratégie
        protected RobotAction _selectedRobotAction = null;          // Action selectionnée
        protected int _selectedRobotActionIndex = -1;               // Index de l'action selectionnée
    }
}