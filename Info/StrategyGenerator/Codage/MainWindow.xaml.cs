using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using StrategyGenerator.FileManager;
using StrategyGenerator.Strategy;

namespace StrategyGenerator
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        const int CONST_MAINWINDOWS_MIN_WIDTH = 1024;
        const int CONST_MAINWINDOWS_MIN_HEIGHT = 650;
        const int CONST_CMDVIEW_HEIGHT = 225;
        const int CONST_CMDVIEW_LINE = 30;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Activated(object sender, EventArgs e)
        {
            MainView.Width = CONST_MAINWINDOWS_MIN_WIDTH;
            MainView.Height = CONST_MAINWINDOWS_MIN_HEIGHT;

            SetCurrentCmd(0);

            LoadCmdListValues();
            LoadCmdTypeListValues();
            LoadActiveFlagListValues();
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            if (MainView.Width < CONST_MAINWINDOWS_MIN_WIDTH)
                MainView.Width = CONST_MAINWINDOWS_MIN_WIDTH;

            if (MainView.Height < CONST_MAINWINDOWS_MIN_HEIGHT)
                MainView.Height = CONST_MAINWINDOWS_MIN_HEIGHT;

            // Define Grid size and position
            // Main Grid
            MainGrid.Width = MainView.Width;
            MainGrid.Height = MainView.Height;

            // MapView ----------------------------------------------------------------------------
            MapView.Margin = new Thickness(0, 0, 0, 0);
            MapView.Width = MainGrid.Width * 0.80;
            MapView.Height = MainGrid.Height - CONST_CMDVIEW_HEIGHT;
            MapPicture.Width = 600;
            MapPicture.Height = 400;

            //CmdListView -------------------------------------------------------------------------
            CmdListView.Margin = new Thickness(MapView.Width, 0, 0, 0);
            CmdListView.Width = MainGrid.Width - MapView.Width;
            CmdListView.Height = MapView.Height;

            lblCmdList.Margin = new Thickness(5,0,0,0);
            lblStrategyName.Margin = new Thickness(lblCmdList.Width, 0, 0, 0);
            lblStrategyName.Width = CmdListView.Width - lblCmdList.Width;

            CmdList.Margin = new Thickness(5, lblCmdList.Height, 0, 0);
            CmdList.Width = CmdListView.Width - 30;
            CmdList.Height = CmdListView.Height - lblCmdList.Height - 10 - 25;

            CmdList_Load.Margin = new Thickness(5, CmdListView.Height - 30, 0, 0);
            CmdList_New.Margin = new Thickness(CmdList.Margin.Left + CmdList.Width / 2 - CmdList_New.Width / 2, CmdListView.Height - 30, 0, 0);
            CmdList_Save.Margin = new Thickness(0, CmdListView.Height - 30, 25, 0);

            // CmdView ----------------------------------------------------------------------------
            CmdView.Margin = new Thickness(0, MapView.Height, 0, 0);
            CmdView.Width = MainGrid.Width;
            CmdView.Height = CONST_CMDVIEW_HEIGHT;

            // Sub CmdView ------------------------------------------------------------------------
            CmdViewN2Before.Margin = new Thickness(0, 0, 0, 0);
            CmdViewN2Before.Height = (CmdView.Height - 35) * 0.5;
            CmdViewN2Before.Width = CmdView.Width * 0.3;

            CmdViewN1Before.Margin = new Thickness(0, CmdViewN2Before.Height, 0, 0);
            CmdViewN1Before.Height = CmdViewN2Before.Height;
            CmdViewN1Before.Width = CmdViewN2Before.Width;

            CmdViewN.Margin = new Thickness(CmdViewN1Before.Margin.Right, 0, 0, 0);
            CmdViewN.Height = CmdView.Height - 35;
            CmdViewN.Width = CmdView.Width * 0.4;

            CmdViewN1After.Margin = new Thickness(CmdViewN1Before.Width + CmdViewN.Width, 0, 0, 0);
            CmdViewN1After.Height = CmdViewN2Before.Height;
            CmdViewN1After.Width = CmdViewN2Before.Width;

            CmdViewN2After.Margin = new Thickness(CmdViewN1After.Margin.Left, CmdViewN1After.Height, 0, 0);
            CmdViewN2After.Height = CmdViewN1After.Height;
            CmdViewN2After.Width = CmdViewN1After.Width;

            // CmdView Borders --------------------------------------------------------------------
            MapBorder.Margin = new Thickness(0, 0, 0, 0);
            MapBorder.Height = MapView.Height;
            MapBorder.Width = MapView.Width;

            CmdListViewBorder.Margin = new Thickness(0, 0, 0, 0);
            CmdListViewBorder.Height = CmdListView.Height;
            CmdListViewBorder.Width = CmdListView.Width;

            CmdViewN2BeforeBorder.Margin = new Thickness(0, 0, 0, 0);
            CmdViewN2BeforeBorder.Height = CmdViewN2Before.Height;
            CmdViewN2BeforeBorder.Width = CmdViewN2Before.Width;

            CmdViewN1BeforeBorder.Margin = new Thickness(0, 0, 0, 0);
            CmdViewN1BeforeBorder.Height = CmdViewN1Before.Height;
            CmdViewN1BeforeBorder.Width = CmdViewN1Before.Width;

            CmdViewNBorder.Margin = new Thickness(0, 0, 0, 0);
            CmdViewNBorder.Height = CmdViewN.Height;
            CmdViewNBorder.Width = CmdViewN.Width;

            CmdViewN1AfterBorder.Margin = new Thickness(0, 0, 0, 0);
            CmdViewN1AfterBorder.Height = CmdViewN1After.Height;
            CmdViewN1AfterBorder.Width = CmdViewN1After.Width;

            CmdViewN2AfterBorder.Margin = new Thickness(0, 0, 0, 0);
            CmdViewN2AfterBorder.Height = CmdViewN2After.Height;
            CmdViewN2AfterBorder.Width = CmdViewN2After.Width;

            // CmdViewN
            CmdViewN_Cmd.Margin = new Thickness(10, 25, 0, 0);

            // CmdView N --------------------------------------------------------------------
            CmdViewN_ButtonPrev.Margin = new Thickness(10, CmdViewN.Height - 35, 0, 0);
            CmdViewN_ButtonNext.Margin = new Thickness(0, CmdViewN.Height - 35, 10, 0);
            CmdViewN_ButtonUpdate.Margin = new Thickness(CmdViewN.Width * 0.15, CmdViewN.Height - 35, 0, 0);
            CmdViewN_ButtonRemove.Margin = new Thickness(CmdViewN.Width * 0.65, CmdViewN.Height - 35, 0, 0);
            CmdViewN_ButtonAdd.Margin = new Thickness(CmdViewN.Width * 0.4, CmdViewN.Height - 35, 0, 0);

            CmdViewN_Cmd.Margin = new Thickness(10, CONST_CMDVIEW_LINE, 0, 0);
            CmdViewN_CmdBox.Margin = new Thickness(60, CONST_CMDVIEW_LINE, 0, 0);
            CmdViewN_CmdBox.Width = CmdViewN.Width * 0.3;

            CmdViewN_CmdType.Margin = new Thickness(CmdViewN.Width * 0.5, CONST_CMDVIEW_LINE, 0, 0);
            CmdViewN_CmdTypeBox.Margin = new Thickness(CmdViewN.Width * 0.5 + 60, CONST_CMDVIEW_LINE, 0, 0);
            CmdViewN_CmdTypeBox.Width = CmdViewN_CmdBox.Width;

            CmdViewN_LblParam1.Margin = new Thickness(10, CONST_CMDVIEW_LINE * 2, 0, 0);
            CmdViewN_Param1.Margin = new Thickness(60, CONST_CMDVIEW_LINE * 2, 0, 0);
            CmdViewN_Param1.Width = CmdViewN_CmdBox.Width;

            CmdViewN_LblParam2.Margin = new Thickness(CmdViewN.Width * 0.5, CONST_CMDVIEW_LINE * 2, 0, 0);
            CmdViewN_Param2.Margin = new Thickness(CmdViewN.Width * 0.5 + 60, CONST_CMDVIEW_LINE * 2, 0, 0);
            CmdViewN_Param2.Width = CmdViewN_Param1.Width;

            CmdViewN_LblParam3.Margin = new Thickness(10, CONST_CMDVIEW_LINE * 3, 0, 0);
            CmdViewN_Param3.Margin = new Thickness(60, CONST_CMDVIEW_LINE * 3, 0, 0);
            CmdViewN_Param3.Width = CmdViewN_Param1.Width;

            CmdViewN_LblParam4.Margin = new Thickness(CmdViewN.Width * 0.5, CONST_CMDVIEW_LINE * 3, 0, 0);
            CmdViewN_Param4.Margin = new Thickness(CmdViewN.Width * 0.5 + 60, CONST_CMDVIEW_LINE * 3, 0, 0);
            CmdViewN_Param4.Width = CmdViewN_Param1.Width;

            CmdViewN_LblCmdID.Margin = new Thickness(CmdViewN.Width * 0.72, CONST_CMDVIEW_LINE * 4, 0, 0);
            CmdViewN_CmdID.Margin = new Thickness(CmdViewN.Width * 0.72 + 50, CONST_CMDVIEW_LINE * 4, 0, 0);
            CmdViewN_CmdID.Width = CmdViewN.Width * 0.10;

            CmdViewN_Flag.Margin = new Thickness(10, CONST_CMDVIEW_LINE * 4, 0, 0);
            CmdViewN_FlagBox.Margin = new Thickness(60, CONST_CMDVIEW_LINE * 4, 0, 0);
            CmdViewN_FlagBox.Width = CmdViewN.Width * 0.55;

            // CmdView (N - 2) content --------------------------------------------------------------------
            CmdN2BeforeTxt.Margin = new Thickness(0, 25, 0, 0);
            CmdN2BeforeTxt.Width = CmdViewN2Before.Width;
            CmdN2BeforeTxt.Height = CmdViewN2Before.Height - 20;
            CmdN2BeforeTxt.TextAlignment = TextAlignment.Center;

            // CmdView (N - 1) content --------------------------------------------------------------------
            CmdN1BeforeTxt.Margin = new Thickness(0, 25, 0, 0);
            CmdN1BeforeTxt.Width = CmdViewN1Before.Width;
            CmdN1BeforeTxt.Height = CmdViewN1Before.Height - 20;
            CmdN1BeforeTxt.TextAlignment = TextAlignment.Center;

            // CmdView (N + 1) content --------------------------------------------------------------------
            CmdN1AfterTxt.Margin = new Thickness(0, 25, 0, 0);
            CmdN1AfterTxt.Width = CmdViewN1After.Width;
            CmdN1AfterTxt.Height = CmdViewN1After.Height - 20;
            CmdN1AfterTxt.TextAlignment = TextAlignment.Center;

            // CmdView (N + 2) content --------------------------------------------------------------------
            CmdN2AfterTxt.Margin = new Thickness(0, 25, 0, 0);
            CmdN2AfterTxt.Width = CmdViewN2After.Width;
            CmdN2AfterTxt.Height = CmdViewN2After.Height - 20;
            CmdN2AfterTxt.TextAlignment = TextAlignment.Center;
        }

        public void SetRobotPos(double _x, double _y, float _angle)
        {
            Robot.RenderTransform = new RotateTransform(_angle, Robot.Width / 2, Robot.Height / 2);
            Robot.Margin = new Thickness(_x - Robot.Width/2, _y - Robot.Height/2, 0, 0);
        }

        private void SetCurrentCmd(int CurrentCmdID)
        {
            if ((CurrentCmdID < 0) || (_CurrentStrategy == null) || (_CurrentStrategy.Count() < CurrentCmdID))
            {
                CmdN1AfterTxt.Text = "";
                CmdN2AfterTxt.Text = "";
                CmdN1BeforeTxt.Text = "";
                CmdN2BeforeTxt.Text = "";

                CmdViewN_isEnabled(false);
            }
            else
            {
                CmdViewN_isEnabled(true);

                // Display (N-2) Command
                if (CurrentCmdID - 2 >= 0)
                {

                }

                // Display (N-1) Command
                if (CurrentCmdID - 1 >= 0)
                {

                }

                // Display (N+1) Command
                if (CurrentCmdID + 1 <= _CurrentStrategy.Count())
                {

                }

                // Display (N+2) Command
                if (CurrentCmdID + 2 <= _CurrentStrategy.Count())
                {

                }
            }
            return;
        }

        private void CmdViewN_isEnabled(bool isEnabled)
        {
            CmdViewN_CmdBox.IsEnabled = isEnabled;
            CmdViewN_CmdTypeBox.IsEnabled = isEnabled;
            CmdViewN_FlagBox.IsEnabled = isEnabled;
            CmdViewN_Param1.IsEnabled = isEnabled;
            CmdViewN_Param2.IsEnabled = isEnabled;
            CmdViewN_Param3.IsEnabled = isEnabled;
            CmdViewN_Param4.IsEnabled = isEnabled;
            CmdViewN_ButtonRemove.IsEnabled = isEnabled;
            CmdViewN_ButtonUpdate.IsEnabled = isEnabled;
            CmdViewN_ButtonNext.IsEnabled = isEnabled;
            CmdViewN_ButtonPrev.IsEnabled = isEnabled;
            CmdViewN_ButtonAdd.IsEnabled = isEnabled;
            CmdViewN_CmdID.IsEnabled = isEnabled;
        }

        private void CmdList_Load_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            // Ask for file to load
            dlg.Filter = "C Files|*.c|All Files|*.*";
            dlg.Title = "Select the strategy file";
            dlg.ShowDialog();
            _CurrentStrategyFilename = dlg.FileName.ToString();

            // Ask for file to load
            dlg.Filter = "C Files|*.c|All Files|*.*";
            dlg.Title = "Select the pattern strategy file";
            dlg.ShowDialog();
            _CurrentStrategyPatternFilename = dlg.FileName.ToString();
            
            _CurrentStrategy = new FullStrategy(_CurrentStrategyFilename, _CurrentStrategyPatternFilename);
            LoadNewStrategy();
        }

        private void CmdList_Save_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            if (_CurrentStrategy != null)
            {
                // Ask for file to load
                dlg.Filter = "C Files|*.c|All Files|*.*";
                dlg.Title = "Select the output strategy file";
                dlg.FileName = _CurrentStrategyFilename;
                dlg.ShowDialog();
                _CurrentStrategyFilename = dlg.FileName.ToString();

                // Ask for file to load
                dlg.Filter = "C Files|*.c|All Files|*.*";
                dlg.Title = "Select the pattern strategy file to use for wrtting the output file";
                dlg.FileName = _CurrentStrategyPatternFilename;
                dlg.ShowDialog();
                _CurrentStrategyPatternFilename = dlg.FileName.ToString();

                _CurrentStrategy.WriteFile(_CurrentStrategyFilename, _CurrentStrategyPatternFilename);
            }
        }

        private void CmdList_New_Click(object sender, RoutedEventArgs e)
        {
            AskStrategyName StrategyName = new AskStrategyName();
            StrategyName.ShowDialog();

            if(StrategyName.StrategyNameTxt.Text != "")
            {
                _CurrentStrategy = new FullStrategy(StrategyName.StrategyNameTxt.Text);
                LoadNewStrategy();
                CmdViewN_isEnabled(true);
            }
        }

        private void LoadNewStrategy()
        {
            if (_CurrentStrategy != null)
            {
                lblStrategyName.Content = _CurrentStrategy.GetName;

                CmdList.Items.Clear();
                // Red the first item (inital cmd)
                CmdList.Items.Add("000 : " + _CurrentStrategy.InitialCmd.Cmd.ToString());

                // Read the current strategy
                for(int iterator = 0; iterator < _CurrentStrategy.Count(); iterator++)
                {
                    CmdList.Items.Add(_CurrentStrategy.GetCommandInfo(iterator));
                }

                                if (_CurrentStrategy.Count() == 0)
                    CmdViewN_ButtonAdd.IsEnabled = true;
            }
            else
            {
                lblStrategyName.Content = "STRATEGY_NOT_SET";
                CmdViewN_ButtonAdd.IsEnabled = false;
            }
        }

        private void LoadCmdListValues()
        {
            if (CmdViewN_CmdBox.Items.Count == 0)
            {
                foreach (EnumCmd ECmd in Enum.GetValues(typeof(EnumCmd)))
                {
                    if (ECmd.ToString() != "NotSet")
                        CmdViewN_CmdBox.Items.Add(ECmd.ToString());
                }
    
                if(CmdViewN_CmdBox.Items.Count > 0)
                    CmdViewN_CmdBox.Text = CmdViewN_CmdBox.Items[0].ToString();
            }
        }

        private void LoadCmdTypeListValues()
        {
            if (CmdViewN_CmdTypeBox.Items.Count == 0)
            {
                foreach (EnumCmdType ECmdType in Enum.GetValues(typeof(EnumCmdType)))
                {
                    if(ECmdType.ToString() != "NotSet")
                        CmdViewN_CmdTypeBox.Items.Add(ECmdType.ToString());
                }

                if (CmdViewN_CmdTypeBox.Items.Count > 0)
                    CmdViewN_CmdTypeBox.Text = CmdViewN_CmdTypeBox.Items[0].ToString();
            }
        }

        private void LoadActiveFlagListValues()
        {
            if (CmdViewN_FlagBox.Items.Count == 0)
            {
                foreach (EnumSensorsFlag EActiveFlag in Enum.GetValues(typeof(EnumSensorsFlag)))
                {
                     CmdViewN_FlagBox.Items.Add(EActiveFlag.ToString());
                }

                if (CmdViewN_FlagBox.Items.Count > 0)
                    CmdViewN_FlagBox.Text = CmdViewN_FlagBox.Items[0].ToString();
            }
        }

        // Private items --------------------------------------------------------------------------
        private String _CurrentStrategyFilename = null;
        private String _CurrentStrategyPatternFilename = null;
        private FullStrategy _CurrentStrategy = null;

    }
}

