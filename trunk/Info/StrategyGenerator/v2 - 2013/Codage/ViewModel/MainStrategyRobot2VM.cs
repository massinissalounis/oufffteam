using GalaSoft.MvvmLight;
using StrategyGenerator2.Model;
using System.Windows;
using StrategyGenerator2.View;
using System.Collections.ObjectModel;
using StrategyGenerator2.StrategyManager;
using System.Collections.Generic;

namespace StrategyGenerator2.ViewModel
{
    public class MainStrategyRobot2VM : MainStrategyVM
    {
        // Public ---------------------------------------------------------------------------------
        public MainStrategyRobot2VM()
        {
            _mainModel = MainModel.GetInstance;

            if (_mainModel != null)
            {
                _currentStrategy = _mainModel.strategyRobot2;
                _currentStrategyDisplay = _mainModel.strategy2Display;
            }
        }


        // Properties -----------------------------------------------------------------------------
  
        // Private --------------------------------------------------------------------------------
    }
}