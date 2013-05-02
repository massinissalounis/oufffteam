using GalaSoft.MvvmLight;
using StrategyGenerator2.Model;
using System.Windows;
using StrategyGenerator2.View;
using System.Collections.ObjectModel;
using StrategyGenerator2.StrategyManager;
using System.Collections.Generic;
using System;
using System.Windows.Input;
using GalaSoft.MvvmLight.Command;
using System.Windows.Forms;
using System.IO;

namespace StrategyGenerator2.ViewModel
{
    public class SubStrategiesVM : ViewModelBase
    {
        // Public ---------------------------------------------------------------------------------
        public SubStrategiesVM()
        {
            _mainModel = MainModel.GetInstance;
            _currentStrategy = null;
            _mainModel.RobotActionListChanged += new EventHandler(UpdateData);
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

                    _firstRobotAction = Ret[0];
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
            { return _selectedSubStrategy; }
            set
            {
                _selectedSubStrategy = value;
                RaisePropertyChanged("ListRobotAction");
                RaisePropertyChanged("SelectedSubStrategyName");

                SelectedRobotAction = _firstRobotAction;
                RaisePropertyChanged("SelectedRobotAction");

                return;
            }
        }

        public String SelectedSubStrategyName
        {
            get 
            {
                if (_selectedSubStrategy != null)
                    return _selectedSubStrategy.Name;
                else
                    return "";
            }
            set 
            {
                Boolean isValid = false;

                if ((_selectedSubStrategy != null) && (value != ""))
                {
                    // Verification si le nom n'est pas déjà pris
                    if ((_currentStrategy != null) && (_currentStrategy.GetAllSubStrategy() != null))
                    {
                        isValid = true;

                        foreach (SubStrategy currentSubStrategy in _currentStrategy.GetAllSubStrategy())
                        {
                            if(currentSubStrategy.Name.ToUpper() == value.ToUpper())
                                isValid = false;
                        }
                    }

                    if(isValid == true)
                    {
                        _selectedSubStrategy.Name = value;
                        RaisePropertyChanged("ListSubStrategies");
                    }
                }
            }
        }
        
        public RobotAction SelectedRobotAction
        {
            get
            {
                return _currentRobotAction;
            }
            set
            {
                _currentRobotAction = value;
                _mainModel.selectedRobotAction = value;
                _mainModel.selectedStrategy = _currentStrategy;
                _mainModel.selectedSubStrategy = _selectedSubStrategy;

                return;
            }
        }

        public ICommand ILoadNewSubStrategy
        {
            get
            {
                return new RelayCommand(LoadNewSubStrategy);
            }
            set {}
        }

        public ICommand ICreateNewStrategy
        {
            get
            {
                return new RelayCommand(CreateNewSubStrategy);
            }
            set {}
        }

        // Private --------------------------------------------------------------------------------
        protected MainModel _mainModel = null;                      // Lien vers le model
        protected Strategy _currentStrategy = null;                 // Lien vers la stratégie actuelle
        protected SubStrategy _selectedSubStrategy = null;          // Sous-strategie selectionnée
        protected RobotAction _currentRobotAction = null;
        protected RobotAction _firstRobotAction = null;

        private void UpdateData(object sender, EventArgs e)
        {
            RaisePropertyChanged("ListSubStrategies");
            RaisePropertyChanged("ListRobotAction");

            return;
        }

        private int GetFreeSubStrategyID()
        {
            int Ret = -1;
            Boolean isOK = false;

            // SI une stratégie est chargée
            if (_currentStrategy != null)
            {
                Ret = 1;
                if (_currentStrategy.GetAllSubStrategy() != null)
                {
                    // Il y a des sous stratégies, on cherche un ID vide
                    while (isOK == false)
                    {
                        isOK = true;
                        // On parcourt tous les ID courants
                        foreach (SubStrategy currentSubStrategy in _currentStrategy.GetAllSubStrategy())
                        {
                            // Si l'ID actuel est déjà utilisé, on le rend invalid
                            if (currentSubStrategy.ID == ((Ret * 100).ToString()))
                            {
                                isOK = false;
                            }
                        }

                        // Si l'ID n'est pas bon, on incrémente
                        if(isOK == false)
                            Ret = Ret + 1;
                    }
                }
            }

            return Ret;
        }

        private void LoadNewSubStrategy()
        {
            String importFile = null;
            SubStrategy subStrategyToImport = null;

            // Lance la fenetre d'import
            OpenFileDialog importWindow = new OpenFileDialog();

            importWindow.InitialDirectory = Directory.GetCurrentDirectory();
            importWindow.Filter = "OufffTEAM StructuredFile|*.sfile";

            if (importWindow.ShowDialog() == DialogResult.OK)
                importFile = importWindow.FileName;

            // On récupère un ID
            int newID = GetFreeSubStrategyID();

            if ((importFile != null) && (newID > 0))
            {
                // On essaye de charger la stratégie
                subStrategyToImport = new SubStrategy("NewStrategy", newID);
                if (subStrategyToImport.Load(importFile, newID) > 0)
                {
                    _currentStrategy.AddSubStrategy(subStrategyToImport);
                    _mainModel.UpdateRobotActionList();
                }
            }

            importWindow.Dispose();
        }

        private void CreateNewSubStrategy()
        {
            SubStrategy newSubStrategy = null;

            // On récupère un ID
            int newID = GetFreeSubStrategyID();

            if (newID > 0)
            {
                // On essaye de charger la stratégie
                newSubStrategy = new SubStrategy("NewSubStrategy", newID);
                _currentStrategy.AddSubStrategy(newSubStrategy);
                _mainModel.UpdateRobotActionList();
            }
        }
    }
}