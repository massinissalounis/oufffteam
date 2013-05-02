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

namespace StrategyGenerator2.View
{
    public partial class SubStrategiesView : UserControl
    {
        public SubStrategiesView()
        {
            InitializeComponent();
        }

        private void listSubStrategies_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            listSubStrategies.SelectedIndex = -1;
        }

        private void listSubStrategyItems_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            listSubStrategyItems.SelectedIndex = -1;
        }
    }
}
