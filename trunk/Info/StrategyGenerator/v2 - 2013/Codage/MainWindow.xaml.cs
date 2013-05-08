using System.Windows;
using StrategyGenerator2.ViewModel;
using StrategyGenerator2.Model;

namespace StrategyGenerator2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            //InitializeComponent();
            Closing += (s, e) => CleanUp();
        }

        private void CleanUp()
        {
            return;
        }
    }
}
