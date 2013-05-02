using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using StrategyGenerator2.FileManager;
using StrategyGenerator2.StrategyManager;

namespace StrategyGenerator2.Model
{
    public class MainModel
    {
        // Public ---------------------------------------------------------------------------------
        public static MainModel GetInstance
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

        public event EventHandler RobotActionChanged = null;
        public event EventHandler RobotActionListChanged = null;

        public void UpdateRobotActionList()
        {
            RaiseRobotActionListChanged();
        }

        public void ChangeCmdID(int oldValue, int newValue)
        {
            // On effectue l'action pour la stratégie actuellement selectionnée
            if (_selectedStrategy != null)
            {
                _selectedStrategy.ChangeCmdID(oldValue, newValue);
            }
        }

        // Private --------------------------------------------------------------------------------
        private void RaiseRobotActionChanged()
        {
            if (RobotActionChanged != null)
                RobotActionChanged(this, new EventArgs());
        }

        private void RaiseRobotActionListChanged()
        {
            if (RobotActionListChanged != null)
                RobotActionListChanged(this, new EventArgs());
        }

        // Declaration du singleton
        private static MainModel _model;

        // Constructeur privé (dû au singleton)
        private MainModel()
        {
            // Creation des objets pour la conception
            strategyRobot1 = new Strategy("UnamedStrategy1");
            strategyRobot2 = new Strategy("UnamedStrategy2");

            return;
        }

        // Properties -----------------------------------------------------------------------------
        public RobotAction selectedRobotAction
        {
            get
            {
                return _selectedRobotAction;
            }
            set
            {
                _selectedRobotAction = value;
                RaiseRobotActionChanged();
            }
        }

        public Strategy selectedStrategy
        {
            get
            {
                return _selectedStrategy;
            }
            set
            {
                _selectedStrategy = value;
            }
        }

        public SubStrategy selectedSubStrategy
        {
            get
            {
                return _selectedSubStrategy;
            }
            set
            {
                _selectedSubStrategy = value;
            }
        }

        // Données publiques ----------------------------------------------------------------------
        public Strategy strategyRobot1 = null;              // First robot or Robot Color A
        public Strategy strategyRobot2 = null;              // Second robot or Robot Color B

        // Données private ------------------------------------------------------------------------
        private RobotAction _selectedRobotAction = null;
        private Strategy _selectedStrategy = null;
        private SubStrategy _selectedSubStrategy = null;

    }
}
