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


        // Private --------------------------------------------------------------------------------
        // Declaration du singleton
        private static MainModel _model;

        // Constructeur privé (dû au singleton)
        private MainModel()
        {
            // Creation des objets pour la conception
            strategyRobot1 = new Strategy("StrategyRobot_1");
            strategyRobot2 = new Strategy("StrategyRobot_2");

            strategyRobot1.Load("StrategyRobot_1");
            strategyRobot2.Load("StrategyRobot_2");

            return;
        }

        // Données private ------------------------------------------------------------------------
        public Strategy strategyRobot1 = null;              // First robot or Robot Color A
        public Strategy strategyRobot2 = null;              // Second robot or Robot Color B

        public RobotAction currentRobotAction1 = null;      // Action pour le Robot 1 à modifier 
        public RobotAction currentRobotAction2 = null;      // Action pour le Robot 2 à modifier 

    }
}
