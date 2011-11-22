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

            TextFile File1 = new TextFile();
            File1.WriteFile("C:/Users/Philippe/Desktop/Test/Output1.c");

            TextFile File2 = new TextFile("C:/Users/Philippe/Desktop/Test/Test1.c");
            Console.WriteLine(File2.GetPreviousLine());
            Console.WriteLine(File2.GetNextLine());
            Console.WriteLine(File2.GetNextLine());
            Console.WriteLine(File2.GetNextLine());
            Console.WriteLine(File2.GetNextLine());
            Console.WriteLine(File2.GetNextLine());
            Console.WriteLine(File2.GetNextLine());
            Console.WriteLine(File2.GetNextLine());
            Console.WriteLine(File2.GetNextLine());
            Console.WriteLine(File2.GetPreviousLine());
            File2.WriteFile("C:/Users/Philippe/Desktop/Test/Output1.c");
        }
    }
}
