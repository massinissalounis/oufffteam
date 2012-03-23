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
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Activated(object sender, EventArgs e)
        {
            MainView.Width = 1024;
            MainView.Height = 600;
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            // Define Grid size and position
            // Main Grid
            MainGrid.Width = MainView.Width;
            MainGrid.Height = MainView.Height;

            // MapView ----------------------------------------------------------------------------
            Map.Margin = new Thickness(0, 0, 0, 0);
            Map.Width = MainGrid.Width * 0.75;
            Map.Height = MainGrid.Height * 0.8;

            //CmdListView -------------------------------------------------------------------------
            CmdListView.Margin = new Thickness(Map.Width, 0, 0, 0);
            CmdListView.Width = MainGrid.Width - Map.Width;
            CmdListView.Height = Map.Height;

            lblCmdList.Margin = new Thickness(0,0,0,0);
            lblStrategyName.Margin = new Thickness(lblCmdList.Width, 0, 0, 0);
            lblStrategyName.Width = CmdListView.Width - lblCmdList.Width;

            CmdList.Margin = new Thickness(0, lblCmdList.Height, 0, 0);
            CmdList.Width = CmdListView.Width;
            CmdList.Height = CmdListView.Height - lblCmdList.Height;

            //CurrentCmdView ----------------------------------------------------------------------
            CurrentCmdView.Margin = new Thickness(0, Map.Height, 0, 0);
            CurrentCmdView.Width = MainGrid.Width;
            CurrentCmdView.Height = MainGrid.Height - Map.Height;
        }
    }
}

