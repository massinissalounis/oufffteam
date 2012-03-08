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

            string Filename = "C:/Users/Philippe/Desktop/Test/FileColorA.c";
            string OutputFilename = "C:/Users/Philippe/Desktop/Test/OutputFileColorA.c";
            string PatternFilename = "C:/Users/Philippe/Desktop/Test/PatternFileColorA.c";

            FullStrategy Strategy = new FullStrategy(Filename, PatternFilename);
            Strategy.WriteFile(OutputFilename, PatternFilename);

         }
    }
}
