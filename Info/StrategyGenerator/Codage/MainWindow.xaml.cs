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

            StructuredFile  File = new StructuredFile();
            TextFile        PatternFile = new TextFile();
            PatternFile.Load();

            List<String> Key = new List<String>();

            File.Parse(PatternFile);

        }
    }
}
