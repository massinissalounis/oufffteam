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
using System.Threading;
using System.Windows.Threading;

namespace StrategyGenerator
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        const int CONST_MAINWINDOWS_MIN_WIDTH = 1024;
        const int CONST_MAINWINDOWS_MIN_HEIGHT = 650;
        const int CONST_CMDVIEW_HEIGHT = 235;
        const int CONST_CMDVIEW_LINE = 30;

        public MainWindow()
        {
            InitializeComponent();

            MainView.Width = CONST_MAINWINDOWS_MIN_WIDTH;
            MainView.Height = CONST_MAINWINDOWS_MIN_HEIGHT;

            SetCurrentCmd(0);

            LoadCmdListValues();
            LoadCmdTypeListValues();
            LoadActiveFlagListValues();
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            MainView.Width = CONST_MAINWINDOWS_MIN_WIDTH;
            MainView.Height = CONST_MAINWINDOWS_MIN_HEIGHT;

            // Define Grid size and position
            // Main Grid
            MainGrid.Width = MainView.Width;
            MainGrid.Height = MainView.Height;

            // MapView ----------------------------------------------------------------------------
            MapView.Margin = new Thickness(0, 0, 0, 0);
            MapView.Width = MainGrid.Width * 0.8;
            MapView.Height = MainGrid.Height - CONST_CMDVIEW_HEIGHT;
            MapPicture.Width = 600;
            MapPicture.Height = 400;

            textBlock_IsEditing.Margin = new Thickness(0, 0, 0, 0);
            textBlock_IsEditing.Width = 100;
            textBlock_IsEditing.Height = 60;
            textBlock_IsEditing.Text = "Modification\nau clavier :\nDesactivée";

            textBlock_MousePos.Margin = new Thickness(0, textBlock_IsEditing.Height, 0, 0);
            textBlock_MousePos.Width = textBlock_IsEditing.Width;
            textBlock_MousePos.Height = 60;

            textBlock_RobotPos.Margin = new Thickness(0, textBlock_MousePos.Height + textBlock_IsEditing.Height, 0, 0);
            textBlock_RobotPos.Width = textBlock_MousePos.Width;
            textBlock_RobotPos.Height = 80;

            textBlock_HelpParam1.Width = textBlock_IsEditing.Width - 10;
            textBlock_HelpParam1.Height = (MapView.Height - 20) / 8;
            textBlock_HelpParam1.Margin = new Thickness(MapView.Width - textBlock_HelpParam1.Width - 10, 10 + 0 * textBlock_HelpParam1.Height, 0, 0);

            textBlock_CmdHelpParam1.Width = textBlock_HelpParam1.Width;
            textBlock_CmdHelpParam1.Height = textBlock_HelpParam1.Height;
            textBlock_CmdHelpParam1.Margin = new Thickness(textBlock_HelpParam1.Margin.Left, 10 + 1 * textBlock_HelpParam1.Height, 0, 0);

            textBlock_HelpParam2.Width = textBlock_HelpParam1.Width;
            textBlock_HelpParam2.Height = textBlock_HelpParam1.Height;
            textBlock_HelpParam2.Margin = new Thickness(textBlock_HelpParam1.Margin.Left, 10 + 2 * textBlock_HelpParam1.Height, 0, 0);

            textBlock_CmdHelpParam2.Width = textBlock_HelpParam1.Width;
            textBlock_CmdHelpParam2.Height = textBlock_HelpParam1.Height;
            textBlock_CmdHelpParam2.Margin = new Thickness(textBlock_HelpParam1.Margin.Left, 10 + 3 * textBlock_HelpParam1.Height, 0, 0);

            textBlock_HelpParam3.Width = textBlock_HelpParam1.Width;
            textBlock_HelpParam3.Height = textBlock_HelpParam1.Height;
            textBlock_HelpParam3.Margin = new Thickness(textBlock_HelpParam1.Margin.Left, 10 + 4 * textBlock_HelpParam1.Height, 0, 0);

            textBlock_CmdHelpParam3.Width = textBlock_HelpParam1.Width;
            textBlock_CmdHelpParam3.Height = textBlock_HelpParam1.Height;
            textBlock_CmdHelpParam3.Margin = new Thickness(textBlock_HelpParam1.Margin.Left, 10 + 5 * textBlock_HelpParam1.Height, 0, 0);

            textBlock_HelpParam4.Width = textBlock_HelpParam1.Width;
            textBlock_HelpParam4.Height = textBlock_HelpParam1.Height;
            textBlock_HelpParam4.Margin = new Thickness(textBlock_HelpParam1.Margin.Left, 10 + 6 * textBlock_HelpParam1.Height, 0, 0);

            textBlock_CmdHelpParam4.Width = textBlock_HelpParam1.Width;
            textBlock_CmdHelpParam4.Height = textBlock_HelpParam1.Height;
            textBlock_CmdHelpParam4.Margin = new Thickness(textBlock_HelpParam1.Margin.Left, 10 + 7 * textBlock_HelpParam1.Height, 0, 0);

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
            CmdViewN1Before.Margin = new Thickness(0, 0, 0, 0);
            CmdViewN1Before.Height = (CmdView.Height - 35) * 0.5;
            CmdViewN1Before.Width = CmdView.Width * 0.3;

            CmdViewN.Margin = new Thickness(CmdViewN1Before.Margin.Right, 0, 0, 0);
            CmdViewN.Height = CmdView.Height - 35;
            CmdViewN.Width = CmdView.Width * 0.4;

            CmdViewN1After.Margin = new Thickness(0, CmdViewN1Before.Height, 0, 0);
            CmdViewN1After.Height = CmdViewN1Before.Height;
            CmdViewN1After.Width = CmdViewN1Before.Width;

            GeneralInfo.Margin = new Thickness(CmdViewN.Width + CmdViewN1Before.Width, 0, 0, 0);
            GeneralInfo.Height = CmdViewN.Height;
            GeneralInfo.Width = CmdView.Width * 0.3;

            // General View -----------------------------------------------------------------------
            General_DefaultSpeedLabel.Margin = new Thickness(10, 30, 0, 0);
            General_DefaultSpeedLabel.Width = 100;

            General_DefaultSpeed.Margin = new Thickness(10 + General_DefaultSpeedLabel.Width, 30, 0, 0);
            General_DefaultSpeed.Width = 50;

            General_RobotPosBeforeLabel.Margin = new Thickness(10, 30 + General_DefaultSpeedLabel.Height, 0, 0);
            General_RobotPosBeforeLabel.Width = General_DefaultSpeedLabel.Width;

            General_RobotPosAfterLabel.Margin = new Thickness(10, 30 + General_DefaultSpeedLabel.Height + General_RobotPosAfterLabel.Height, 0, 0);
            General_RobotPosAfterLabel.Width = General_DefaultSpeedLabel.Width;

            General_RobotPosBefore.Margin = new Thickness(10 + General_DefaultSpeedLabel.Width, 30 + General_DefaultSpeedLabel.Height, 0, 0);
            General_RobotPosBefore.Width = General_DefaultSpeedLabel.Width;

            General_RobotPosAfter.Margin = new Thickness(10 + General_DefaultSpeedLabel.Width, 30 + General_DefaultSpeedLabel.Height + General_RobotPosAfterLabel.Height, 0, 0);
            General_RobotPosAfter.Width = General_DefaultSpeedLabel.Width;

            General_buttonConvert.Margin = new Thickness(GeneralInfo.Width / 2 - General_buttonConvert.Width / 2, General_RobotPosAfter.Margin.Top + 30, 0, 0);
            General_buttonImport.Margin = new Thickness(General_buttonConvert.Margin.Left, General_buttonConvert.Margin.Top + 30, 0, 0);

            // CmdView Borders --------------------------------------------------------------------
            MapBorder.Margin = new Thickness(0, 0, 0, 0);
            MapBorder.Height = MapView.Height;
            MapBorder.Width = MapView.Width;

            CmdListViewBorder.Margin = new Thickness(0, 0, 0, 0);
            CmdListViewBorder.Height = CmdListView.Height;
            CmdListViewBorder.Width = CmdListView.Width;

            CmdViewN1BeforeBorder.Margin = new Thickness(0, 0, 0, 0);
            CmdViewN1BeforeBorder.Height = CmdViewN1Before.Height;
            CmdViewN1BeforeBorder.Width = CmdViewN1Before.Width;

            CmdViewNBorder.Margin = new Thickness(0, 0, 0, 0);
            CmdViewNBorder.Height = CmdViewN.Height;
            CmdViewNBorder.Width = CmdViewN.Width;

            CmdViewN1AfterBorder.Margin = new Thickness(0, 0, 0, 0);
            CmdViewN1AfterBorder.Height = CmdViewN1After.Height;
            CmdViewN1AfterBorder.Width = CmdViewN1After.Width;

            GeneralInfoBorder.Margin = new Thickness(0, 0, 0, 0);
            GeneralInfoBorder.Height = GeneralInfo.Height;
            GeneralInfoBorder.Width = GeneralInfo.Width;

            // CmdViewN
            CmdViewN_Cmd.Margin = new Thickness(10, 25, 0, 0);

            // CmdView N --------------------------------------------------------------------
            CmdViewN_ButtonAddBefore.Margin = new Thickness(CmdViewN.Width * 0.1, CmdViewN.Height - 40, 0, 0);
            CmdViewN_ButtonRemove.Margin = new Thickness(CmdViewN.Width * 0.4, CmdViewN.Height - 40, 0, 0);
            CmdViewN_ButtonAddAfter.Margin = new Thickness(CmdViewN.Width * 0.7, CmdViewN.Height - 40, 0, 0);
            CmdViewN_ButtonNext.Margin = new Thickness(CmdViewN.Width * 0.87, 3, 0, 0);
            CmdViewN_ButtonPrev.Margin = new Thickness(CmdViewN.Width * 0.78, 3, 0, 0);

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

            CmdViewN_LblCmdID.Margin = new Thickness(10, 3, 0, 0);
            CmdViewN_CmdID.Margin = new Thickness(60, 3, 0, 0);
            CmdViewN_CmdID.Width = CmdViewN.Width * 0.10;

            CmdViewN_LblNextCmdID.Margin = new Thickness(CmdViewN.Width * 0.73, CONST_CMDVIEW_LINE * 4, 0, 0);
            CmdViewN_NextCmdID.Margin = new Thickness(CmdViewN.Width * 0.78 + 25, CONST_CMDVIEW_LINE * 4, 0, 0);
            CmdViewN_NextCmdID.Width = CmdViewN.Width * 0.10;

            CmdViewN_Flag.Margin = new Thickness(10, CONST_CMDVIEW_LINE * 4, 0, 0);
            CmdViewN_FlagBox.Margin = new Thickness(60, CONST_CMDVIEW_LINE * 4, 0, 0);
            CmdViewN_FlagBox.Width = CmdViewN.Width * 0.58;

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

            DisplayRobotPos();
        }

        private void DisplayRobotPos()
         {
             if(_PositionList == null)
             {
                 textBlock_RobotPos.Text = "Movement :\n";
                 textBlock_RobotPos.Text += "Simulation\nis disabled";
                 textBlock_RobotPos.Foreground = new SolidColorBrush(Colors.Red);

                 Robot.Visibility = Visibility.Hidden;
             }
             else
             {
                 General_RobotPosBefore.Content = "(" + (_PositionList[0].InitalX).ToString() + ", " + (_PositionList[0].InitalY).ToString() + ", " + (_PositionList[0].InitalAngle).ToString() + ")";
                 General_RobotPosAfter.Content = "(" + (_PositionList[0].X).ToString() + ", " + (_PositionList[0].Y).ToString() + ", " + (_PositionList[0].Angle).ToString() + ")";

                 textBlock_RobotPos.Text = "Movement :\n";
                 textBlock_RobotPos.Text += "Simulation\nis enabled";
                 textBlock_RobotPos.Foreground = new SolidColorBrush(Colors.Green);

                 Robot.Visibility = Visibility.Visible;
                 SetRobotPos(_PositionList[0].X, _PositionList[0].Y, _PositionList[0].Angle);
             }
         }

        public void SetRobotPos(int _x, int _y, int _angle)
        {
            int DisplayX = _x / 5;
            int DisplayY = _y / 5;
            int DisplayAngle = _angle;

            Robot.RenderTransform = new RotateTransform(90 + (float)DisplayAngle * -1, (double)Robot.Width / 2, (double)Robot.Height / 2);
            Robot.Margin = new Thickness(DisplayX - Robot.Width / 2, 400 - DisplayY - Robot.Height / 2, 0, 0);
        }

        private void SetCurrentCmd(int CurrentCmdID)
        {
            if ((CurrentCmdID < 0) || (_CurrentStrategy == null) || (_CurrentStrategy.Count() < CurrentCmdID))
            {
                CmdN1AfterTxt.Text = "";
                CmdN1BeforeTxt.Text = "";

                CmdViewN_isEnabled(false);
            }
            else
            {
                CmdViewN_isEnabled(true);

                // Display Current Command
                Command CurrentCmd = _CurrentStrategy.GetCommand(CurrentCmdID);
                if(CurrentCmd != null)
                {
                    CmdViewN_CmdID.Text = _CurrentStrategy.GetActionID(CurrentCmdID).ToString();
                    CmdViewN_NextCmdID.Text = _CurrentStrategy.GetNextActionID(CurrentCmdID).ToString();
                    CmdViewN_Param1.Text = CurrentCmd.Param1;
                    CmdViewN_Param2.Text = CurrentCmd.Param2;
                    CmdViewN_Param3.Text = CurrentCmd.Param3;
                    CmdViewN_Param4.Text = CurrentCmd.Param4;
                    CmdViewN_CmdBox.SelectedItem = CurrentCmd.Cmd.ToString();
                    CmdViewN_CmdTypeBox.SelectedItem = CurrentCmd.CmdType.ToString();
                    CmdViewN_FlagBox.SelectedItem = CurrentCmd.ActiveSensors.ToString();

                    DataChanged();
                }

                // Display (N-1) Command
                if ((_PositionList != null) && (_PositionList.Count > 1))
                {
                    CmdN1BeforeTxt.Text = _CurrentStrategy.GetCommandDetailed(_PositionList[1].Index);
                }
                else
                {
                    CmdN1BeforeTxt.Text = _CurrentStrategy.GetCommandDetailed(-1);
                }

                // Display (N+1) Command
                int NextIndex = _CurrentStrategy.GetIndexFromCmdID(_CurrentStrategy.GetNextActionID(CmdList.SelectedIndex));
                CmdN1AfterTxt.Text = _CurrentStrategy.GetCommandDetailed(NextIndex);
             }
            return;
        }

        private void CmdViewN_isEnabled(bool isEnabled)
        {
            if (_CurrentStrategy == null)
                isEnabled = false;

            CmdList.IsEnabled = isEnabled;
            CmdViewN_CmdTypeBox.IsEnabled = isEnabled;
            CmdViewN_FlagBox.IsEnabled = isEnabled;
            CmdViewN_Param1.IsEnabled = isEnabled;
            CmdViewN_Param2.IsEnabled = isEnabled;
            CmdViewN_Param3.IsEnabled = isEnabled;
            CmdViewN_Param4.IsEnabled = isEnabled;
            CmdViewN_ButtonRemove.IsEnabled = isEnabled;
            CmdViewN_ButtonAddAfter.IsEnabled = isEnabled;
            CmdViewN_ButtonNext.IsEnabled = isEnabled;
            CmdViewN_CmdID.IsEnabled = isEnabled;
            CmdViewN_NextCmdID.IsEnabled = isEnabled;
            General_DefaultSpeed.IsEnabled = isEnabled;

            if ((_PositionList == null) || (_PositionList.Count <= 1))
                CmdViewN_ButtonPrev.IsEnabled = false;
            else
                CmdViewN_ButtonPrev.IsEnabled = isEnabled;

            if (CmdList.SelectedIndex == 0)
            {
                CmdViewN_CmdBox.IsEnabled = false;
                CmdViewN_ButtonAddBefore.IsEnabled = false;
            }
            else
            {
                CmdViewN_CmdBox.IsEnabled = isEnabled;
                CmdViewN_ButtonAddBefore.IsEnabled = isEnabled;
            }
        }

        private void CmdList_Load_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            // Ask for file to load
            dlg.Filter = "C Files|*.c";
            dlg.Title = "Select the strategy file (A=Red, B=Purple)";
            dlg.CheckFileExists = true;
            dlg.ShowDialog();
            _CurrentStrategyFilename = dlg.FileName.ToString();

            if (_CurrentStrategyFilename != "")
            {
                // Ask for file to load
                dlg.Filter = "Pattern Files|*.pattern";
                dlg.Title = "Select the pattern strategy file (A=Red, B=Purple)";
                dlg.CheckFileExists = true;
                dlg.ShowDialog();
                _CurrentStrategyPatternFilename = dlg.FileName.ToString();

                if (_CurrentStrategyPatternFilename != "")
                {
                    _CurrentStrategy = new FullStrategy(_CurrentStrategyFilename, _CurrentStrategyPatternFilename);
                    LoadNewStrategy();
                }
            }
        }

        private void CmdList_Save_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            if (_CurrentStrategy != null)
            {
                // Ask for file to write
                dlg.Filter = "C Files|*.c";
                dlg.Title = "Select the output strategy file (A=Red, B=Purple)";
                dlg.FileName = "";
                dlg.CheckFileExists = false;
                dlg.ShowDialog();
                _CurrentStrategyFilename = dlg.FileName.ToString();

                if (_CurrentStrategyFilename != "")
                {
                    // Ask for file to load
                    dlg.Filter = "Pattern Files|*.pattern";
                    dlg.Title = "Select the pattern strategy file to use for wrtting the output file (A=Red, B=Purple)";
                    dlg.FileName = "";
                    dlg.CheckFileExists = true;
                    dlg.ShowDialog();
                    _CurrentStrategyPatternFilename = dlg.FileName.ToString();

                    if (_CurrentStrategyPatternFilename != "")
                    {
                        _CurrentStrategy.WriteFile(_CurrentStrategyFilename, _CurrentStrategyPatternFilename);
                    }
                }
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
                lblStrategyName.Content = _CurrentStrategy.StrategyName;
                General_DefaultSpeed.Text = _CurrentStrategy.DefaultSpeed.ToString();

                CmdList.Items.Clear();

                // Read the current strategy
                for(int iterator = 0; iterator <= _CurrentStrategy.Count(); iterator++)
                {
                    CmdList.Items.Add(_CurrentStrategy.GetCommandInfo(iterator));
                }

                CmdList.SelectedIndex = 0;
            }
            else
            {
                lblStrategyName.Content = "STRATEGY_NOT_SET";
                CmdViewN_ButtonAddBefore.IsEnabled = false;
                CmdViewN_ButtonAddAfter.IsEnabled = false;
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

                if (CmdViewN_CmdBox.Items.Count > 0)
                    CmdViewN_CmdBox.SelectedIndex = 0;
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
                    CmdViewN_CmdTypeBox.SelectedIndex = 0;
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
                    CmdViewN_FlagBox.SelectedIndex = 0;
            }
        }

        private void CmdList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            SetCurrentCmd(((ListBox)sender).SelectedIndex);

            if (CmdList.SelectedIndex <= 0)
                CmdViewN_CmdBox.IsEnabled = false;
            else
            {
                CmdViewN_CmdBox.IsEnabled = true;
            }
        }

        private void CmdViewN_CmdTypeBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            DataChanged();
        }

        private void CmdViewN_FlagBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            DataChanged();
        }

        private void CmdViewN_CmdBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (CmdList.SelectedIndex >= 0)
            {
                Command SelectedCmd = _CurrentStrategy.GetCommand(CmdList.SelectedIndex);
                CmdViewN_Param1.Text = SelectedCmd.Param1;
                CmdViewN_Param2.Text = SelectedCmd.Param2;
                CmdViewN_Param3.Text = SelectedCmd.Param3;
                CmdViewN_Param4.Text = SelectedCmd.Param4;
                CmdViewN_FlagBox.SelectedItem = SelectedCmd.ActiveSensors.ToString();
            }
            else
            {
                CmdViewN_Param1.Text = "";
                CmdViewN_Param2.Text = "";
                CmdViewN_Param3.Text = "";
                CmdViewN_Param4.Text = "";
                CmdViewN_FlagBox.SelectedItem = EnumSensorsFlag.APP_PARAM_STRATEGYFLAG_NONE.ToString();
            }

            CheckParam();

            DisplayHelpForSelectedCmd();

            DataChanged();
        }

        private void CmdViewN_CmdBox_MouseLeave(object sender, MouseEventArgs e)
        {
            // Update CmdList value
            if (CmdList.SelectedIndex >= 0)
            {
                int CmdIndex = CmdList.SelectedItem.ToString().IndexOf(": ");
                String CurrentCmdString = CmdList.SelectedItem.ToString().Substring(CmdIndex + 2);
                int ActionID = _CurrentStrategy.GetActionID(CmdList.SelectedIndex);
                String SelectedCmdString = _CurrentStrategy.GetCommand(CmdList.SelectedIndex).Cmd.ToString();

                if (CurrentCmdString != SelectedCmdString)
                {
                    int SelectedIndex = CmdList.SelectedIndex;
                    LoadNewStrategy();
                    CmdList.SelectedIndex = SelectedIndex;
                }
            }
        }

        private void CmdList_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            _PositionList = null;
        }

        private void CmdViewN_ButtonNext_Click(object sender, RoutedEventArgs e)
        {
            Command SelectedCmd = _CurrentStrategy.GetCommand(CmdList.SelectedIndex);
            int NextActionID = 0;

            if ((SelectedCmd.Cmd == EnumCmd.App_IfGoto_Strategy) || (SelectedCmd.Cmd == EnumCmd.App_IfGoto_System))
            {
                // If the current command is App_IfGoto, we ask for the next cmd ID
                AskNextAction NextActionWindow = new AskNextAction(SelectedCmd.Param1, SelectedCmd.Param2, SelectedCmd.Param3);
                NextActionWindow.ShowDialog();

                NextActionID = NextActionWindow.NextCmdIDSelected;
            }
            else
            {
                NextActionID = _CurrentStrategy.GetNextActionID(CmdList.SelectedIndex);
            }

            if (NextActionID > 0)
            {
                int NextIndex = _CurrentStrategy.GetIndexFromCmdID(NextActionID);

                if (_PositionList != null)
                {
                    int x = _PositionList[0].X;
                    int y = _PositionList[0].Y;
                    int angle = _PositionList[0].Angle;

                    Command Cmd = _CurrentStrategy.GetCommand(NextActionID);

                    _PositionList.Insert(0, new RobotPos(x, y, angle, Cmd, NextIndex));
                    CmdViewN_ButtonPrev.IsEnabled = true;
                }

                CmdList.SelectedIndex = NextIndex;
            }
        }

        private void CmdViewN_ButtonPrev_Click(object sender, RoutedEventArgs e)
        {
            if ((_PositionList != null) && (_PositionList.Count > 1))
            {
                int PrevIndex = _PositionList[1].Index;
                _PositionList.RemoveAt(0);
                CmdList.SelectedIndex = PrevIndex;
                return;
            }

            CmdViewN_ButtonPrev.IsEnabled = false;
        }

        private void CmdViewN_ButtonRemove_Click(object sender, RoutedEventArgs e)
        {
            if (_CurrentStrategy != null)
            {
                try
                {
                    _CurrentStrategy.RemoveCmd(CmdList.SelectedIndex);
                    CmdList.Items.RemoveAt(CmdList.SelectedIndex);
                }
                catch (Exception)
                {
                    MessageBox.Show("Unable to remove current command.\nDelete all links to this command before.");
                }
            }
        }

        private void CmdViewN_AddBefore_Click(object sender, RoutedEventArgs e)
        {
            if (CmdList.SelectedIndex <= 0)
                return;

            AskNewCmdInfo NewCmdWindow = new AskNewCmdInfo();
            NewCmdWindow.ShowDialog();
            EnumCmd NewCommand = Command.GetCmdFromString(NewCmdWindow.NewCmd);
            int NewCommandID = NewCmdWindow.NewCmdID;

            if (_CurrentStrategy != null)
            {
                int CurrentIndex = CmdList.SelectedIndex;
                _CurrentStrategy.InsertNewCmd_Before(CurrentIndex, NewCommand, NewCommandID);
                String CmdListInfo = _CurrentStrategy.GetActionID(CurrentIndex) + " : " + _CurrentStrategy.GetCommand(CurrentIndex).Cmd.ToString();
                CmdList.Items.Insert(CurrentIndex, CmdListInfo);
                CmdList.SelectedIndex = CurrentIndex;
            }
        }

        private void CmdViewN_AddAfter_Click(object sender, RoutedEventArgs e)
        {
            if (CmdList.SelectedIndex < 0)
                return;

            AskNewCmdInfo NewCmdWindow = new AskNewCmdInfo();
            NewCmdWindow.ShowDialog();
            EnumCmd NewCommand = Command.GetCmdFromString(NewCmdWindow.NewCmd);
            int NewCommandID = NewCmdWindow.NewCmdID;

            if (_CurrentStrategy != null)
            {
                _CurrentStrategy.InsertNewCmd_After(CmdList.SelectedIndex, NewCommand, NewCommandID);
                String CmdListInfo = _CurrentStrategy.GetActionID(CmdList.SelectedIndex + 1) + " : " + _CurrentStrategy.GetCommand(CmdList.SelectedIndex + 1).Cmd.ToString();
                CmdList.Items.Insert(CmdList.SelectedIndex + 1, CmdListInfo);
            }

            // Update the previous NextActionID item
            _CurrentStrategy.UpdateNextActionID(CmdList.SelectedIndex, _CurrentStrategy.GetActionID(CmdList.SelectedIndex + 1).ToString());

            CmdViewN_ButtonNext.RaiseEvent(e);
        }

        private void MapPicture_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            EnumCmd SelectedCmd = Command.GetCmdFromString(CmdViewN_CmdBox.SelectedItem.ToString());

            if (_IsModificationModeActivated == true)
            {
                switch (SelectedCmd)
                {
                    case EnumCmd.App_SetNewPos:
                    case EnumCmd.Mvt_UseMixedMode:
                        // Change the robot position
                        Point MousePoint = e.GetPosition(MapGrid);
                        CmdViewN_Param2.Text = Convert.ToInt32((MousePoint.X * 5)).ToString();
                        CmdViewN_Param3.Text = Convert.ToInt32((2000 - MousePoint.Y * 5)).ToString();
                        break;
                }

                DataChanged();
            }
        }

        private void DataChanged()
        {
            if (_CurrentStrategy == null)
                return;

            Command SelectedCmd = _CurrentStrategy.GetCommand(CmdList.SelectedIndex);
            _CurrentStrategy.UpdateNextActionID(CmdList.SelectedIndex, CmdViewN_NextCmdID.Text);

            if (SelectedCmd == null)
                return;

            // First, check current params
            CheckParam();

            EnumCmd UpdateCmd = Command.GetCmdFromString(CmdViewN_CmdBox.SelectedItem.ToString());
            EnumCmdType UpdateCmdType = Command.GetCmdTypeFromString(CmdViewN_CmdTypeBox.SelectedItem.ToString());
            EnumSensorsFlag ActiveFlags = Command.GetSensorsFlagFromString(CmdViewN_FlagBox.SelectedItem.ToString());
            SelectedCmd.Update(UpdateCmd, UpdateCmdType, CmdViewN_Param1.Text, CmdViewN_Param2.Text, CmdViewN_Param3.Text, CmdViewN_Param4.Text, ActiveFlags);

            BitmapImage NewRobot = null;

            if (_PositionList == null)
            {
                switch (SelectedCmd.Cmd)
                {
                    case EnumCmd.App_SetNewPos:
                        // Convert Values
                        int x = Convert.ToInt32(Convert.ToDouble(CmdViewN_Param2.Text));
                        int y = Convert.ToInt32(Convert.ToDouble(CmdViewN_Param3.Text));
                        int angle = Convert.ToInt32(Convert.ToDouble(CmdViewN_Param4.Text));

                        _PositionList = new List<RobotPos>();
                        _PositionList.Add(new RobotPos(x, y, angle, SelectedCmd, CmdList.SelectedIndex));

                        CmdViewN_ButtonNext.IsEnabled = true;

                        NewRobot = new BitmapImage(new Uri("D:\\Robotique\\Info\\StrategyGenerator\\Codage\\Images\\RobotStart.png"));
                        Robot.Source = NewRobot;
                        Robot.Width = NewRobot.Width;
                        Robot.Height = NewRobot.Height;
                        break;

                    default:
                        break;
                }
            }
            else
            {
                switch(SelectedCmd.Cmd)
                {
                    case EnumCmd.Sensors_ArmsOpenDown:
                    case EnumCmd.Sensors_ArmsOpenUp:
                    case EnumCmd.Sensors_ArmsOpenTotem:
                    case EnumCmd.Sensors_ArmsDeployment:
                        NewRobot = new BitmapImage(new Uri("D:\\Robotique\\Info\\StrategyGenerator\\Codage\\Images\\RobotOpen.png"));
                        Robot.Source = NewRobot;
                        Robot.Width = NewRobot.Width;
                        Robot.Height = NewRobot.Height;
                        break;

                    case EnumCmd.Sensors_ArmsClose:
                    case EnumCmd.Sensors_ArmsCloseTotem:
                        NewRobot = new BitmapImage(new Uri("D:\\Robotique\\Info\\StrategyGenerator\\Codage\\Images\\RobotClose.png"));
                        Robot.Source = NewRobot;
                        Robot.Width = NewRobot.Width;
                        Robot.Height = NewRobot.Height;
                        break;

                    case EnumCmd.Sensors_ArmsUngrab:
                        NewRobot = new BitmapImage(new Uri("D:\\Robotique\\Info\\StrategyGenerator\\Codage\\Images\\RobotUngrab.png"));
                        Robot.Source = NewRobot;
                        Robot.Width = NewRobot.Width;
                        Robot.Height = NewRobot.Height;
                        break;

                    default:
                        _PositionList[0].UpdateCmd(SelectedCmd);
                        break;
                }
            }

            // Update values
            if (_PositionList == null)
            {
                CmdViewN_ButtonNext.IsEnabled = false;
                CmdViewN_ButtonPrev.IsEnabled = false;

                General_RobotPosBefore.Content = "Not Set";
                General_RobotPosAfter.Content = "Not Set";
            }

            DisplayRobotPos();
        }

        private void CheckParam()
        {
            EnumCmd CurrentCmd = Command.GetCmdFromString(CmdViewN_CmdBox.SelectedItem.ToString());

            switch (CurrentCmd)
            {
                // Cmd Modif : Add new command here
                // ________________________________________
                case EnumCmd.App_SetNewPos:
                    CmdViewN_Param1.Text = "Not Used";
                    CmdViewN_Param2.Text = CheckParam_XPos(CmdViewN_Param2.Text);
                    CmdViewN_Param3.Text = CheckParam_YPos(CmdViewN_Param3.Text);
                    CmdViewN_Param4.Text = CheckParam_Angle(CmdViewN_Param4.Text);
                    break;
                
                // ________________________________________
                case EnumCmd.Mvt_UseAngleOnly:
                case EnumCmd.MvtSimple_RotateInDeg:
                case EnumCmd.MvtSimple_RotateToAngleInDeg:
                    CmdViewN_Param1.Text = CheckParam_Speed(CmdViewN_Param1.Text);
                    CmdViewN_Param2.Text = "Not Used";
                    CmdViewN_Param3.Text = "Not Used";
                    CmdViewN_Param4.Text = CheckParam_Angle(CmdViewN_Param4.Text);
                    break;

                // ________________________________________
                case EnumCmd.Mvt_UseDistOnly:
                    CmdViewN_Param1.Text = CheckParam_Speed(CmdViewN_Param1.Text);
                    CmdViewN_Param2.Text = CheckParam_XPos(CmdViewN_Param2.Text);
                    CmdViewN_Param3.Text = CheckParam_YPos(CmdViewN_Param3.Text);
                    CmdViewN_Param4.Text = "Not Used";
                    break;

                // ________________________________________
                case EnumCmd.App_IfGoto_System:
                case EnumCmd.App_IfGoto_Strategy:
                    //CmdViewN_Param1.Text = Check ??
                    CmdViewN_Param2.Text = CheckParam_Goto(CmdViewN_Param2.Text);
                    CmdViewN_Param3.Text = CheckParam_Goto(CmdViewN_Param3.Text);
                    CmdViewN_Param4.Text = "Not Used";
                    CmdViewN_NextCmdID.Text = _CurrentStrategy.GetActionID(CmdList.SelectedIndex).ToString();
                    break;

                // ________________________________________
                case EnumCmd.App_SetStrategyFlags:
                    //CmdViewN_Param1.Text = Check ??
                    CmdViewN_Param2.Text = CheckParam_Bool(CmdViewN_Param2.Text);
                    CmdViewN_Param3.Text = "Not Used";
                    CmdViewN_Param4.Text = "Not Used";
                    break;

                // ________________________________________
                case EnumCmd.Mvt_UseMixedMode:
                    CmdViewN_Param1.Text = CheckParam_Speed(CmdViewN_Param1.Text);
                    CmdViewN_Param2.Text = CheckParam_XPos(CmdViewN_Param2.Text);
                    CmdViewN_Param3.Text = CheckParam_YPos(CmdViewN_Param3.Text);
                    CmdViewN_Param4.Text = CheckParam_Angle(CmdViewN_Param4.Text);
                    break;
                
                // ________________________________________
                case EnumCmd.App_Wait:
                    CmdViewN_Param1.Text = CheckParam_Time(CmdViewN_Param1.Text);
                    CmdViewN_Param2.Text = CheckParam_Time(CmdViewN_Param2.Text);
                    CmdViewN_Param3.Text = CheckParam_Time(CmdViewN_Param3.Text);
                    CmdViewN_Param4.Text = CheckParam_Time(CmdViewN_Param4.Text);
                    break;

                // ________________________________________
                case EnumCmd.Mvt_UsePivotMode:
                    CmdViewN_Param1.Text = CheckParam_Speed(CmdViewN_Param1.Text);
                    CmdViewN_Param2.Text = CheckParam_Wheel(CmdViewN_Param2.Text);
                    CmdViewN_Param3.Text = "Not Used";
                    CmdViewN_Param4.Text = CheckParam_Angle(CmdViewN_Param4.Text);
                    break;

                // ________________________________________
                case EnumCmd.MvtSimple_MoveInMM:
                    CmdViewN_Param1.Text = CheckParam_Speed(CmdViewN_Param1.Text);
                    CmdViewN_Param2.Text = CheckParam_Dist(CmdViewN_Param2.Text);
                    CmdViewN_Param3.Text = "Not Used";
                    CmdViewN_Param4.Text = "Not Used";
                    break;

                // ________________________________________
                case EnumCmd.NotSet: 
                case EnumCmd.Mvt_Stop:
                default:
                    CmdViewN_Param1.Text = "Not Used";
                    CmdViewN_Param2.Text = "Not Used";
                    CmdViewN_Param3.Text = "Not Used";
                    CmdViewN_Param4.Text = "Not Used";
                    break;
            }

            // Disable all unused param
            if (CmdViewN_Param1.Text == "Not Used") { CmdViewN_Param1.IsReadOnly = true; } else { CmdViewN_Param1.IsReadOnly = false; }
            if (CmdViewN_Param2.Text == "Not Used") { CmdViewN_Param2.IsReadOnly = true; } else { CmdViewN_Param2.IsReadOnly = false; }
            if (CmdViewN_Param3.Text == "Not Used") { CmdViewN_Param3.IsReadOnly = true; } else { CmdViewN_Param3.IsReadOnly = false; }
            if (CmdViewN_Param4.Text == "Not Used") { CmdViewN_Param4.IsReadOnly = true; } else { CmdViewN_Param4.IsReadOnly = false; }
        }

        private void General_buttonConvert_Click(object sender, RoutedEventArgs e)
        {
            Command CurrentCmd;
            EnumCmd Cmd;
            EnumCmdType CmdType;
            String NewParam1;
            String NewParam2;
            String NewParam3;
            String NewParam4;
            EnumSensorsFlag Flags;

            for (int i = 0; i < CmdList.Items.Count; i++)
            {
                CurrentCmd = _CurrentStrategy.GetCommand(i);
                Cmd = CurrentCmd.Cmd;
                CmdType = CurrentCmd.CmdType;
                NewParam1 = CurrentCmd.Param1;
                NewParam2 = CurrentCmd.Param2;
                NewParam3 = CurrentCmd.Param3;
                NewParam4 = CurrentCmd.Param4;
                Flags = CurrentCmd.ActiveSensors;

                // Update value from command
                switch (CurrentCmd.Cmd)
                {
                    case EnumCmd.Mvt_UseAngleOnly:
                    case EnumCmd.MvtSimple_RotateInDeg:
                    case EnumCmd.MvtSimple_RotateToAngleInDeg:
                        NewParam4 = (180 - Convert.ToInt32(CurrentCmd.Param4)).ToString();
                        CurrentCmd.Update(Cmd, CmdType, NewParam1, NewParam2, NewParam3, NewParam4, Flags);
                        break;

                    case EnumCmd.Mvt_UsePivotMode:
                        if (NewParam2 == "RIGHT_WHEEL")
                            NewParam2 = "LEFT_WHEEL";
                        else
                            NewParam2 = "RIGHT_WHEEL";

                        NewParam4 = (180 - Convert.ToInt32(CurrentCmd.Param4)).ToString();
                        CurrentCmd.Update(Cmd, CmdType, NewParam1, NewParam2, NewParam3, NewParam4, Flags);
                        break;

                    case EnumCmd.App_SetNewPos:
                    case EnumCmd.Mvt_UseMixedMode:
                        NewParam2 = (3000 - Convert.ToInt32(CurrentCmd.Param2)).ToString();
                        NewParam4 = (180 - Convert.ToInt32(CurrentCmd.Param4)).ToString();
                        CurrentCmd.Update(Cmd, CmdType, NewParam1, NewParam2, NewParam3, NewParam4, Flags);
                        break;

                    case EnumCmd.Mvt_UseDistOnly:
                        NewParam2 = (3000 - Convert.ToInt32(CurrentCmd.Param2)).ToString();
                        CurrentCmd.Update(Cmd, CmdType, NewParam1, NewParam2, NewParam3, NewParam4, Flags);
                        break;
                    
                    default:
                        break;
                }
            }

            CmdList.SelectedIndex = -1;
            CmdList.SelectedIndex = 0;
        }

        private void General_buttonImport_Click(object sender, RoutedEventArgs e)
        {
            String LoopFilename = "";
            String PatternFileName = "";
            FullStrategy LoopsToImport = null;

            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            // Ask for file to load
            dlg.Filter = "C Files|*.c";
            dlg.Title = "Select the strategy file (A=Red, B=Purple)";
            dlg.CheckFileExists = true;
            dlg.ShowDialog();
            LoopFilename = dlg.FileName.ToString();

            if (LoopFilename != "")
            {
                // Ask for file to load
                dlg.Filter = "Pattern Files|*.pattern";
                dlg.Title = "Select the pattern strategy file (A=Red, B=Purple)";
                dlg.CheckFileExists = true;
                dlg.ShowDialog();
                PatternFileName = dlg.FileName.ToString();

                if (PatternFileName != "")
                {
                    LoopsToImport = new FullStrategy(LoopFilename, PatternFileName);
                    
                    // Check for imported loops
                    if (LoopsToImport != null)
                    {
                        for (int i = 0; i<=LoopsToImport.Count(); i++)
                        {
                            Command CommandToAdd = LoopsToImport.GetCommand(i);
                            int CommandIDToAdd = LoopsToImport.GetActionID(i);
                            int NextCommandIDToAdd = LoopsToImport.GetNextActionID(i);

                            if (CommandIDToAdd >= 100)
                            {
                                _CurrentStrategy.InsertCmd(CommandToAdd, CommandIDToAdd, NextCommandIDToAdd);
                            }
                        }

                        LoadNewStrategy();
                    }
                }
            }
        }

        private void Position_KeyDown(object sender, KeyEventArgs e)
        {
            EnumCmd CurrentCmd = Command.GetCmdFromString(CmdViewN_CmdBox.SelectedItem.ToString());
            
            int MvtStep = 10;
            int AngleStep = 5;
            int SpeedStep = 5;

            if (_IsModificationModeActivated == true)
            {
                switch (CurrentCmd)
                {
                    // ________________________________________
                    case EnumCmd.App_SetNewPos:
                        if (e.Key == Key.Left)      { CmdViewN_Param2.Text = (Convert.ToDouble(CmdViewN_Param2.Text) - MvtStep).ToString(); }
                        if (e.Key == Key.Right)     { CmdViewN_Param2.Text = (Convert.ToDouble(CmdViewN_Param2.Text) + MvtStep).ToString();   }
                        if (e.Key == Key.Up)        { CmdViewN_Param3.Text = (Convert.ToDouble(CmdViewN_Param3.Text) + MvtStep).ToString();  }
                        if (e.Key == Key.Down)      { CmdViewN_Param3.Text = (Convert.ToDouble(CmdViewN_Param3.Text) - MvtStep).ToString();    }
                        if (e.Key == Key.Add)       { CmdViewN_Param4.Text = (Convert.ToDouble(CmdViewN_Param4.Text) + AngleStep).ToString();   }
                        if (e.Key == Key.Subtract)  { CmdViewN_Param4.Text = (Convert.ToDouble(CmdViewN_Param4.Text) - AngleStep).ToString(); }
                        break;

                    // ________________________________________
                    case EnumCmd.Mvt_UseAngleOnly:
                    case EnumCmd.MvtSimple_RotateInDeg:
                    case EnumCmd.MvtSimple_RotateToAngleInDeg:
                        if (e.Key == Key.PageUp)    { CmdViewN_Param1.Text = (Convert.ToDouble(CmdViewN_Param1.Text) + SpeedStep).ToString(); }
                        if (e.Key == Key.PageDown)  { CmdViewN_Param1.Text = (Convert.ToDouble(CmdViewN_Param1.Text) - SpeedStep).ToString(); }
                        if (e.Key == Key.Add)       { CmdViewN_Param4.Text = (Convert.ToDouble(CmdViewN_Param4.Text) + AngleStep).ToString();   }
                        if (e.Key == Key.Subtract)  { CmdViewN_Param4.Text = (Convert.ToDouble(CmdViewN_Param4.Text) - AngleStep).ToString(); }
                        break;

                    // ________________________________________
                    case EnumCmd.Mvt_UseDistOnly:
                        if (e.Key == Key.PageUp)    { CmdViewN_Param1.Text = (Convert.ToDouble(CmdViewN_Param1.Text) + SpeedStep).ToString(); }
                        if (e.Key == Key.PageDown)  { CmdViewN_Param1.Text = (Convert.ToDouble(CmdViewN_Param1.Text) - SpeedStep).ToString(); }
                        if (e.Key == Key.Left)      { CmdViewN_Param2.Text = (Convert.ToDouble(CmdViewN_Param2.Text) - MvtStep).ToString(); }
                        if (e.Key == Key.Right)     { CmdViewN_Param2.Text = (Convert.ToDouble(CmdViewN_Param2.Text) + MvtStep).ToString();   }
                        if (e.Key == Key.Up)        { CmdViewN_Param3.Text = (Convert.ToDouble(CmdViewN_Param3.Text) + MvtStep).ToString();  }
                        if (e.Key == Key.Down)      { CmdViewN_Param3.Text = (Convert.ToDouble(CmdViewN_Param3.Text) - MvtStep).ToString();    }
                        break;

                    // ________________________________________
                    case EnumCmd.Mvt_UseMixedMode:
                        if (e.Key == Key.PageUp)    { CmdViewN_Param1.Text = (Convert.ToDouble(CmdViewN_Param1.Text) + SpeedStep).ToString(); }
                        if (e.Key == Key.PageDown)  { CmdViewN_Param1.Text = (Convert.ToDouble(CmdViewN_Param1.Text) - SpeedStep).ToString(); }
                        if (e.Key == Key.Left)      { CmdViewN_Param2.Text = (Convert.ToDouble(CmdViewN_Param2.Text) - MvtStep).ToString(); }
                        if (e.Key == Key.Right)     { CmdViewN_Param2.Text = (Convert.ToDouble(CmdViewN_Param2.Text) + MvtStep).ToString();   }
                        if (e.Key == Key.Up)        { CmdViewN_Param3.Text = (Convert.ToDouble(CmdViewN_Param3.Text) + MvtStep).ToString();  }
                        if (e.Key == Key.Down)      { CmdViewN_Param3.Text = (Convert.ToDouble(CmdViewN_Param3.Text) - MvtStep).ToString();    }
                        if (e.Key == Key.Add)       { CmdViewN_Param4.Text = (Convert.ToDouble(CmdViewN_Param4.Text) + AngleStep).ToString();   }
                        if (e.Key == Key.Subtract)  { CmdViewN_Param4.Text = (Convert.ToDouble(CmdViewN_Param4.Text) - AngleStep).ToString(); }
                        break;

                    // ________________________________________
                    case EnumCmd.Mvt_UsePivotMode:
                       if (e.Key == Key.PageUp)    { CmdViewN_Param1.Text = (Convert.ToDouble(CmdViewN_Param1.Text) - SpeedStep).ToString();}
                        if (e.Key == Key.PageDown)  { CmdViewN_Param1.Text = (Convert.ToDouble(CmdViewN_Param2.Text) + SpeedStep).ToString(); }
                        if (e.Key == Key.Add)       { CmdViewN_Param4.Text = (Convert.ToDouble(CmdViewN_Param4.Text) + AngleStep).ToString(); }
                        if (e.Key == Key.Subtract)  { CmdViewN_Param4.Text = (Convert.ToDouble(CmdViewN_Param4.Text) - AngleStep).ToString();}
                        if (e.Key == Key.W)
                        {
                            if (CmdViewN_Param2.Text == "RIGHT_WHEEL")
                                CmdViewN_Param2.Text = "LEFT_WHEEL";
                            else
                                CmdViewN_Param2.Text = "RIGHT_WHEEL";
                        }
                        break;

                    // ________________________________________
                    case EnumCmd.MvtSimple_MoveInMM:
                        if (e.Key == Key.PageUp)    { CmdViewN_Param1.Text = (Convert.ToDouble(CmdViewN_Param1.Text) + SpeedStep).ToString(); }
                        if (e.Key == Key.PageDown)  { CmdViewN_Param1.Text = (Convert.ToDouble(CmdViewN_Param1.Text) - SpeedStep).ToString(); }
                        if (e.Key == Key.Add)       { CmdViewN_Param2.Text = (Convert.ToDouble(CmdViewN_Param2.Text) + MvtStep).ToString();   }
                        if (e.Key == Key.Subtract)  { CmdViewN_Param2.Text = (Convert.ToDouble(CmdViewN_Param2.Text) - MvtStep).ToString(); }
                        break;

                    // ________________________________________
                    default:
                        break;
                }

                // Update display
                DataChanged();
            }            
        }

        private void MapPicture_MouseMove(object sender, MouseEventArgs e)
        {
            if (_IsModificationModeActivated == true)
            {
                textBlock_MousePos.Text = "Mouse Position :";
                textBlock_MousePos.Text += "\nX = ";
                textBlock_MousePos.Text += (Math.Round(e.MouseDevice.GetPosition(MapPicture).X * 5)).ToString();
                textBlock_MousePos.Text += "\nY = ";
                textBlock_MousePos.Text += (Math.Round(2000 - e.MouseDevice.GetPosition(MapPicture).Y * 5)).ToString();
            }
            else
            {
                textBlock_MousePos.Text = "";
            }
        }

        private void MapPicture_MouseEnter(object sender, MouseEventArgs e)
        {
            if (_CurrentStrategy != null)
            {
                _IsModificationModeActivated = true;
                CmdViewN_isEnabled(false);
                textBlock_IsEditing.Text = "Modification\nau clavier :\nActivée";
                
                textBlock_CmdHelpParam1.Visibility = Visibility.Visible;
                textBlock_CmdHelpParam2.Visibility = Visibility.Visible;
                textBlock_CmdHelpParam3.Visibility = Visibility.Visible;
                textBlock_CmdHelpParam4.Visibility = Visibility.Visible;
            }
        }

        private void MapPicture_MouseLeave(object sender, MouseEventArgs e)
        {
            _IsModificationModeActivated = false;
            textBlock_MousePos.Text = "";
            CmdViewN_isEnabled(true);
            textBlock_IsEditing.Text = "Modification\nau clavier :\nDesactivée";

            textBlock_CmdHelpParam1.Visibility = Visibility.Hidden;
            textBlock_CmdHelpParam2.Visibility = Visibility.Hidden;
            textBlock_CmdHelpParam3.Visibility = Visibility.Hidden;
            textBlock_CmdHelpParam4.Visibility = Visibility.Hidden;
        }

        private void CmdViewN_Param_LostKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            DataChanged();
        }


        private void CmdViewN_CmdID_Validate(object sender, KeyboardFocusChangedEventArgs e)
        {
            if (CmdList.SelectedIndex > 1)
            {
                _CurrentStrategy.UpdateActionID(CmdList.SelectedIndex, CmdViewN_CmdID.Text);
                
                int SelectedIndex = CmdList.SelectedIndex;
                LoadNewStrategy();
                CmdList.SelectedIndex = SelectedIndex;
            }
        }

        private void CmdViewN_CmdID_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
                CmdViewN_CmdID_Validate(sender, null);
        }

        private void CmdViewN_Param_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
                DataChanged();
        }

        private void CmdViewN_Param1_GotFocus(object sender, RoutedEventArgs e)
        {
            if (CmdViewN_CmdBox.SelectedItem.ToString() == EnumCmd.App_IfGoto_System.ToString())
            {
                GetSystemFlags WindowFlags = new GetSystemFlags(CmdViewN_Param1.Text);
                WindowFlags.ShowDialog();

                CmdViewN_Param1.Text = WindowFlags.SelectedFlags;
            }
            

            if ((CmdViewN_CmdBox.SelectedItem.ToString() == EnumCmd.App_SetStrategyFlags.ToString()) ||
                (CmdViewN_CmdBox.SelectedItem.ToString() == EnumCmd.App_IfGoto_Strategy.ToString()))
            {
                GetStrategyFlags WindowFlags = new GetStrategyFlags(CmdViewN_Param1.Text);
                WindowFlags.ShowDialog();

                CmdViewN_Param1.Text = WindowFlags.SelectedFlags;
            }
        }

        private void General_DefaultSpeed_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                try
                {
                    _CurrentStrategy.DefaultSpeed = Convert.ToInt32(General_DefaultSpeed.Text);
                }
                catch (Exception)
                {
                    _CurrentStrategy.DefaultSpeed = 50;
                }

                General_DefaultSpeed.Text = _CurrentStrategy.DefaultSpeed.ToString();
            }
        }

        private void DisplayHelpForSelectedCmd()
        {
            if (_CurrentStrategy != null)
            {
                EnumCmd CurrentCmd = Command.GetCmdFromString(CmdViewN_CmdBox.SelectedItem.ToString());

                textBlock_HelpParam1.Text = "_______________\n";
                textBlock_HelpParam2.Text = "_______________\n";
                textBlock_HelpParam3.Text = "_______________\n";
                textBlock_HelpParam4.Text = "_______________\n";

                switch (CurrentCmd)
                {
                    // Cmd Modif : Add new command here
                    // ________________________________________
                    case EnumCmd.App_SetNewPos:
                        textBlock_HelpParam1.Text += "Param 1 :\nNot Used";
                        textBlock_CmdHelpParam1.Text = "";
                        textBlock_HelpParam2.Text += "Param 2 :\nPos X";
                        textBlock_CmdHelpParam2.Text = "(Left or Right)";
                        textBlock_HelpParam3.Text += "Param 3 :\nPos Y";
                        textBlock_CmdHelpParam3.Text = "(Up or Down)";
                        textBlock_HelpParam4.Text += "Param 4 :\nAngle";
                        textBlock_CmdHelpParam4.Text = "(+ or -)";
                        break;

                    // ________________________________________
                    case EnumCmd.Mvt_UseAngleOnly:
                    case EnumCmd.MvtSimple_RotateInDeg:
                    case EnumCmd.MvtSimple_RotateToAngleInDeg:
                        textBlock_HelpParam1.Text += "Param 1 :\nSpeed";
                        textBlock_CmdHelpParam1.Text = "(PageUp or\nPageDown)";
                        textBlock_HelpParam2.Text += "Param 2 :\nNot Used";
                        textBlock_CmdHelpParam2.Text = "";
                        textBlock_HelpParam3.Text += "Param 3 :\nNot Used";
                        textBlock_CmdHelpParam3.Text = "";
                        textBlock_HelpParam4.Text += "Param 4 :\nAngle";
                        textBlock_CmdHelpParam4.Text = "(+ or -)";
                        break;

                    // ________________________________________
                    case EnumCmd.Mvt_UseDistOnly:
                        textBlock_HelpParam1.Text += "Param 1 :\nSpeed";
                        textBlock_CmdHelpParam1.Text = "(PageUp or\nPageDown)";
                        textBlock_HelpParam2.Text += "Param 2 :\nPos X";
                        textBlock_CmdHelpParam2.Text = "(Left or Right)";
                        textBlock_HelpParam3.Text += "Param 3 :\nPos Y";
                        textBlock_CmdHelpParam3.Text = "(Up or Down)";
                        textBlock_HelpParam4.Text += "Param 4 :\nNot Used";
                        textBlock_CmdHelpParam4.Text = "";
                        break;

                    // ________________________________________
                    case EnumCmd.App_IfGoto_System:
                    case EnumCmd.App_IfGoto_Strategy:
                        textBlock_HelpParam1.Text += "Param 1 :\nTest";
                        textBlock_CmdHelpParam1.Text = "";
                        textBlock_HelpParam2.Text += "Param 2 :\nID if True";
                        textBlock_CmdHelpParam2.Text = "";
                        textBlock_HelpParam3.Text += "Param 3 :\nID if False";
                        textBlock_CmdHelpParam3.Text = "";
                        textBlock_HelpParam4.Text += "Param 4 :\nNot Used";
                        textBlock_CmdHelpParam4.Text = "";
                        break;

                    // ________________________________________
                    case EnumCmd.App_SetStrategyFlags:
                        textBlock_HelpParam1.Text += "Param 1 :\nFlags to Set";
                        textBlock_CmdHelpParam1.Text = "";
                        textBlock_HelpParam2.Text += "Param 2 :\nNew Value";
                        textBlock_CmdHelpParam2.Text = "";
                        textBlock_HelpParam3.Text += "Param 3 :\nNot Used";
                        textBlock_CmdHelpParam3.Text = "";
                        textBlock_HelpParam4.Text += "Param 4 :\nNot Used";
                        textBlock_CmdHelpParam4.Text = "";
                        break;

                    // ________________________________________
                    case EnumCmd.Mvt_UseMixedMode:
                        textBlock_HelpParam1.Text += "Param 1 :\nSpeed";
                        textBlock_CmdHelpParam1.Text = "(PageUp or\nPageDown)";
                        textBlock_HelpParam2.Text += "Param 2 :\nPos X";
                        textBlock_CmdHelpParam2.Text = "(Left or Right)";
                        textBlock_HelpParam3.Text += "Param 3 :\nPos Y";
                        textBlock_CmdHelpParam3.Text = "(Up or Down)";
                        textBlock_HelpParam4.Text += "Param 4 :\nAngle";
                        textBlock_CmdHelpParam4.Text = "(+ or -)";
                        break;

                    // ________________________________________
                    case EnumCmd.App_Wait:
                        textBlock_HelpParam1.Text += "Param 1 :\nHour";
                        textBlock_CmdHelpParam1.Text = "";
                        textBlock_HelpParam2.Text += "Param 2 :\nMinute";
                        textBlock_CmdHelpParam2.Text = "";
                        textBlock_HelpParam3.Text += "Param 3 :\nSecond";
                        textBlock_CmdHelpParam3.Text = "";
                        textBlock_HelpParam4.Text += "Param 4 :\nMillisecond";
                        textBlock_CmdHelpParam4.Text = "";
                        break;

                    // ________________________________________
                    case EnumCmd.Mvt_UsePivotMode:
                        textBlock_HelpParam1.Text += "Param 1 :\nSpeed";
                        textBlock_CmdHelpParam1.Text = "(PageUp or\nPageDown)";
                        textBlock_HelpParam2.Text += "Param 2 :\nWheel for pivot";
                        textBlock_CmdHelpParam2.Text = "(w/W)";
                        textBlock_HelpParam3.Text += "Param 3 :\nNot Used";
                        textBlock_CmdHelpParam3.Text = "";
                        textBlock_HelpParam4.Text += "Param 4 :\nAngle";
                        textBlock_CmdHelpParam4.Text = "(+ or -)";
                        break;

                    // ________________________________________
                    case EnumCmd.MvtSimple_MoveInMM:
                        textBlock_HelpParam1.Text += "Param 1 :\nSpeed";
                        textBlock_CmdHelpParam1.Text = "(PageUp or\nPageDown)";
                        textBlock_HelpParam2.Text += "Param 2 :\nDistance";
                        textBlock_CmdHelpParam2.Text = "(+ or -)";
                        textBlock_HelpParam3.Text += "Param 3 :\nNot Used";
                        textBlock_CmdHelpParam3.Text = "";
                        textBlock_HelpParam4.Text += "Param 4 :\nNot Used";
                        textBlock_CmdHelpParam4.Text = "";
                        break;

                    // ________________________________________
                    default:
                        textBlock_HelpParam1.Text += "Param 1 :\nNot Used";
                        textBlock_CmdHelpParam1.Text = "";
                        textBlock_HelpParam2.Text += "Param 2 :\nNot Used";
                        textBlock_CmdHelpParam2.Text = "";
                        textBlock_HelpParam3.Text += "Param 3 :\nNot Used";
                        textBlock_CmdHelpParam3.Text = "";
                        textBlock_HelpParam4.Text += "Param 4 :\nNot Used";
                        textBlock_CmdHelpParam4.Text = "";
                        break;
                }
            }
            else
            {
                textBlock_HelpParam1.Text = "";
                textBlock_HelpParam2.Text = "";
                textBlock_HelpParam3.Text = "";
                textBlock_HelpParam4.Text = "";
                textBlock_CmdHelpParam1.Text = "";
                textBlock_CmdHelpParam2.Text = "";
                textBlock_CmdHelpParam3.Text = "";
                textBlock_CmdHelpParam4.Text = "";
            }
        }

        // ----------------------------------------------------------------------------------------
        private string CheckParam_Speed(string SpeedToCheck)
        {
            try
            {
                if (SpeedToCheck == "")
                    return "DEFAULT_SPEED";

                if (SpeedToCheck == "DEFAULT_SPEED")
                    return "DEFAULT_SPEED";

                if (Convert.ToInt32(SpeedToCheck) <= 0)
                    return "DEFAULT_SPEED";

                if (Convert.ToInt32(SpeedToCheck) > 100)
                    return "100";

                decimal SpeedValue = Math.Round(Convert.ToDecimal(SpeedToCheck));
                return SpeedValue.ToString();
            }
            catch (Exception)
            {
                return "DEFAULT_SPEED";
            }
        }

        private string CheckParam_Angle(string AngleToCheck)
        {
            try
            {
                if (AngleToCheck == "")
                    return "0";

                if (Convert.ToInt32(AngleToCheck) <= -180)
                    return (Convert.ToInt32(AngleToCheck) + 360).ToString();

                if (Convert.ToInt32(AngleToCheck) > 180)
                    return (Convert.ToInt32(AngleToCheck) - 360).ToString();

                decimal AngleValue = Math.Round(Convert.ToDecimal(AngleToCheck));
                return AngleValue.ToString();
            }
            catch (Exception)
            {
                return "0";
            }
        }

        private string CheckParam_XPos(string PosToCheck)
        {
            try
            {
                if (PosToCheck == "")
                    return "1500";

                if (Convert.ToInt32(PosToCheck) <= 0)
                    return "0";

                if (Convert.ToInt32(PosToCheck) > 3000)
                    return "3000";

                decimal PosValue = Math.Round(Convert.ToDecimal(PosToCheck));
                return PosValue.ToString();
            }
            catch (Exception)
            {
                return "1500";
            }
        }

        private string CheckParam_YPos(string PosToCheck)
        {
            try
            {
                if (PosToCheck == "")
                    return "1000";

                if (Convert.ToInt32(PosToCheck) <= 0)
                    return "0";

                if (Convert.ToInt32(PosToCheck) > 2000)
                    return "2000";

                decimal PosValue = Math.Round(Convert.ToDecimal(PosToCheck));
                return PosValue.ToString();
            }
            catch (Exception)
            {
                return "1000";
            }

        }

        private string CheckParam_Dist(string DistToCheck)
        {
            try
            {
                if (DistToCheck == "")
                    return "0";

                if (Convert.ToInt32(DistToCheck) <= -3600)
                    return "-3600";

                if (Convert.ToInt32(DistToCheck) > 3600)
                    return "3600";

                decimal DistValue = Math.Round(Convert.ToDecimal(DistToCheck));
                return DistValue.ToString();
            }
            catch (Exception)
            {
                return "0";
            }
        }

        private string CheckParam_Time(string TimeToCheck)
        {
            try
            {
                if (TimeToCheck == "")
                    return "0";

                if (Convert.ToInt32(TimeToCheck) <= 0)
                    return "0";

                if (Convert.ToInt32(TimeToCheck) >= 1000)
                    return "999";

                decimal TimeValue = Math.Round(Convert.ToDecimal(TimeToCheck));
                return TimeValue.ToString();
            }
            catch (Exception)
            {
                return "0";
            }
        }

        private string CheckParam_Goto(string ValueToCheck)
        {
            try
            {
                if (ValueToCheck == "")
                    return "0";

                if (Convert.ToInt32(ValueToCheck) <= 0)
                    return "0";

                decimal Value = Math.Round(Convert.ToDecimal(ValueToCheck));
                return Value.ToString();
            }
            catch (Exception)
            {
                return "0";
            }
        }

        private string CheckParam_Wheel(string WheelToCheck)
        {
                if (WheelToCheck == "")
                    return "RIGHT_WHEEL";

                if ((WheelToCheck == "RIGHT_WHEEL") || (WheelToCheck == "LEFT_WHEEL"))
                    return WheelToCheck;

                return "RIGHT_WHEEL";
        }

        private string CheckParam_Bool(string ValueToCheck)
        {
            if (ValueToCheck == "")
                return "0";

            if (ValueToCheck == "0")
                return ValueToCheck;

            return "1";
        }

        // Private items --------------------------------------------------------------------------
        private String _CurrentStrategyFilename = null;
        private String _CurrentStrategyPatternFilename = null;
        private FullStrategy _CurrentStrategy = null;

        private List<RobotPos>_PositionList = null;

        private Boolean _IsModificationModeActivated = false;
     }
}

