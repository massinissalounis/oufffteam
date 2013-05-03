using GalaSoft.MvvmLight;
using StrategyGenerator2.Model;
using System.Collections.ObjectModel;
using StrategyGenerator2.StrategyManager;
using StrategyGenerator2.FileManager;
using System;
using System.Windows.Input;
using GalaSoft.MvvmLight.Command;
using System.Windows.Forms;
using System.IO;
using StrategyGenerator2.StrategyViewer;

namespace StrategyGenerator2.ViewModel
{
    public class MainStrategyVM : ViewModelBase
    {
        // Public ---------------------------------------------------------------------------------
        public MainStrategyVM()
        {
            _mainModel = MainModel.GetInstance;
            _currentStrategy = null;
            _mainModel.RobotActionListChanged += new EventHandler(UpdateData);
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
                if (_currentStrategy != null)
                {
                    if ((_currentStrategy.GetMainStrategy() != null) && (_currentStrategy.GetMainStrategy().GetAllActions() != null))
                    {
                        Ret = new ObservableCollection<RobotAction>();
                        foreach (RobotAction currentRobotAction in _currentStrategy.GetMainStrategy().GetAllActions())
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

        public RobotAction SelectedRobotAction
        {
            get
            { return _currentRobotAction; }
            set
            {
                _mainModel.selectedStrategyDisplay = _currentStrategyDisplay;
                _mainModel.selectedStrategy = _currentStrategy;
                _mainModel.selectedSubStrategy = _currentStrategy.GetMainStrategy();
                _currentRobotAction = value;
                _mainModel.selectedRobotAction = value;
                return;
            }
        }

        public ICommand LoadStrategyFile
        {
            get
            {
                return new RelayCommand(LoadMainStrategyFile);
            }

            set { }
        }

        public ICommand SaveStrategyFile
        {
            get
            {
                return new RelayCommand(SaveMainStrategyFile);
            }

            set { }
        }

        public ICommand ImportStrategy
        {
           get
            {
                return new RelayCommand(ImportCurrentStrategy);
            }

            set { }
        }

        public ICommand ExportStrategy
        {
           get
            {
                return new RelayCommand(ExportCurrentStrategy);
            }

            set { }
        }

        public String CurrentStrategyName
        {
            get
            {
                if ((_currentStrategy != null) && (_currentStrategy.Name != "NotSet"))
                    return _currentStrategy.Name;
                else
                    return "";
            }

            set 
            {
                _currentStrategy.Name = value;
            }
        }

        public int CurrentStrategyDefaultPosX
        {
            get
            {
                if ((_currentStrategy != null) && (_currentStrategy.Name != "NotSet"))
                    return _currentStrategy.DefaultPosX;
                else
                    return 0;
            }

            set
            {
                _currentStrategy.DefaultPosX = value;
            }
        }
        public int CurrentStrategyDefaultPosY
        {
            get
            {
                if ((_currentStrategy != null) && (_currentStrategy.Name != "NotSet"))
                    return _currentStrategy.DefaultPosY;
                else
                    return 0;
            }

            set
            {
                _currentStrategy.DefaultPosY = value;
            }
        }
        public int CurrentStrategyDefaultPosA
        {
            get
            {
                if ((_currentStrategy != null) && (_currentStrategy.Name != "NotSet"))
                    return _currentStrategy.DefaultPosA;
                else
                    return 0;
            }

            set
            {
                _currentStrategy.DefaultPosA = value;
            }
        }
        public int CurrentStrategyDefaultSpeed
        {
            get
            {
                if ((_currentStrategy != null) && (_currentStrategy.Name != "NotSet"))
                    return _currentStrategy.DefaultSpeed;
                else
                    return 0;
            }

            set
            {
                _currentStrategy.DefaultSpeed = value;
            }
        }


        // Private --------------------------------------------------------------------------------
        protected MainModel _mainModel = null;                      // Lien vers le model
        protected Strategy _currentStrategy = null;                 // Lien vers la stratégie actuelle
        protected RobotAction _currentRobotAction = null;           // Sauvegarde du RobotAction
        protected StrategyDisplay _currentStrategyDisplay = null;

        private void UpdateData(object sender, EventArgs e)
        {
            RaisePropertyChanged("ListRobotAction");
            RaisePropertyChanged("CurrentStrategyName");
            RaisePropertyChanged("CurrentStrategyDefaultPosX");
            RaisePropertyChanged("CurrentStrategyDefaultPosY");
            RaisePropertyChanged("CurrentStrategyDefaultPosA");
            RaisePropertyChanged("CurrentStrategyDefaultSpeed");

            return;
        }

        private void LoadMainStrategyFile()
        {
            StrategyLoader LoadWindow = new StrategyLoader();
            LoadWindow.Load();

            // Lecture du nom de la stratégie
            String strategyToLoad = LoadWindow.SelectedStrategyName;

            if (strategyToLoad != "")
            {
                _currentStrategy.Clear();
                _currentStrategy.Load(strategyToLoad);
                _mainModel.UpdateRobotActionList();
            }

            LoadWindow = null;
        }

        private void SaveMainStrategyFile()
        {
            _currentStrategy.Save();
        }

        private void SaveToMainStrategyFile()
        {
            StrategyLoader LoadWindow = new StrategyLoader();

            if ((_currentStrategy != null) && (_currentStrategy.Name != "NotSet"))
                LoadWindow.Save(_currentStrategy.Name);
            else
                LoadWindow.Save();

            // Lecture du nom de la stratégie
            String strategyToSave = LoadWindow.SelectedStrategyName;

            if (strategyToSave != "")
            {
                _currentStrategy.Name = strategyToSave;
                _currentStrategy.Save();
                _mainModel.UpdateRobotActionList();
            }

            LoadWindow = null;
        }

        private void ImportCurrentStrategy()
        {
            String importFile = null;
            String importPatternFile = null;

            // Lance la fenetre d'import
            OpenFileDialog importWindow = new OpenFileDialog();
            OpenFileDialog importPatternWindow = new OpenFileDialog();

            importWindow.InitialDirectory = Directory.GetCurrentDirectory();
            importPatternWindow.InitialDirectory = Directory.GetCurrentDirectory();

            importWindow.Filter = "C Files (*.c)|*.c|All files (*.*)|*.*";
            importPatternWindow.Filter = "OufffTEAM StrategyFile|*.spattern";

            if (importWindow.ShowDialog() == DialogResult.OK)
                importFile = importWindow.FileName;

            if (importPatternWindow.ShowDialog() == DialogResult.OK)
                importPatternFile = importPatternWindow.FileName;

            if ((importFile != null) && (importPatternFile != null))
            {
                _currentStrategy.Clear();
                _currentStrategy.Import(importFile, importPatternFile);
                _mainModel.UpdateRobotActionList();
            }

            importWindow.Dispose();
            importPatternWindow.Dispose();
        }

        private void ExportCurrentStrategy()
        {
            String exportFile = null;
            String exportPatternFile = null;

            // Lance la fenetre d'import
            OpenFileDialog exportWindow = new OpenFileDialog();
            OpenFileDialog exportPatternWindow = new OpenFileDialog();

            exportWindow.InitialDirectory = Directory.GetCurrentDirectory();
            exportPatternWindow.InitialDirectory = Directory.GetCurrentDirectory();

            exportWindow.Filter = "C Files (*.c)|*.c|All files (*.*)|*.*";
            exportPatternWindow.Filter = "OufffTEAM StrategyFile|*.spattern";

            exportWindow.CheckFileExists = false;

            if (exportWindow.ShowDialog() == DialogResult.OK)
                exportFile = exportWindow.FileName;

            if (exportPatternWindow.ShowDialog() == DialogResult.OK)
                exportPatternFile = exportPatternWindow.FileName;

            if ((exportFile != null) && (exportPatternFile != null))
            {
                _currentStrategy.Export(exportFile, exportPatternFile);
            }


            exportPatternWindow.Dispose();
            exportWindow.Dispose();
        }

    }
}