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

            StructuredFile  File = new StructuredFile("C:/Users/Philippe/Desktop/Test/FileColorA.c");
            TextFile PatternFile = new TextFile("C:/Users/Philippe/Desktop/Test/PatternFileColorA.c");
            //PatternFile.Load("C:/Users/Philippe/Desktop/Test/PatternFileColorA.c");

            List<StructuredFileKey> Res = File.Parse(PatternFile);

            for (int i = 0; i < Res.Count(); i++)
            {
                Console.WriteLine(Res[i].Debug());
            }
        }
    }
}
