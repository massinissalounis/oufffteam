using GalaSoft.MvvmLight;
using StrategyGenerator2.Model;
using System.Windows;
using StrategyGenerator2.View;
using System.Collections.ObjectModel;
using StrategyGenerator2.StrategyManager;
using System.Collections.Generic;

namespace StrategyGenerator2.ViewModel
{
    public class SubStrategiesRobot1VM : ViewModelBase
    {
        // Public ---------------------------------------------------------------------------------
        public SubStrategiesRobot1VM()
        {
            _mainModel = MainModel.GetInstance;

            if (_mainModel != null)
                _currentStrategy = _mainModel.strategyRobot1;
        }



        // Properties -----------------------------------------------------------------------------
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

        public ObservableCollection<RobotAction> ListRobotAction
        {
            get
            {
                ObservableCollection<RobotAction> Ret = null;

                if (_subStrategySelected != null)
                {
                    if (_subStrategySelected.Count() > 0)
                    {
                        Ret = new ObservableCollection<RobotAction>();
                        foreach (RobotAction currentRobotAction in _subStrategySelected.GetAllActions())
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
                _subStrategySelected = value;
                RaisePropertyChanged("ListRobotAction");
                return;
            }
        }

        public RobotAction SelectedRobotAction
        {
            get
            { return null; }
            set
            {
                RobotAction val = value;
                return;
            }
        }

        // Private --------------------------------------------------------------------------------
        private MainModel _mainModel = null;
        private Strategy _currentStrategy = null;
        private SubStrategy _subStrategySelected = null;
    }
}