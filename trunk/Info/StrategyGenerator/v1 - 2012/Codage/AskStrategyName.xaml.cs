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
using System.Windows.Shapes;

namespace StrategyGenerator
{
    /// <summary>
    /// Logique d'interaction pour AskStrategyName.xaml
    /// </summary>
    public partial class AskStrategyName : Window
    {
        public AskStrategyName()
        {
            InitializeComponent();
            StrategyNameTxt.Focus();
        }

        public String StrategyName { get { return _NewStrategyName; } }


        private void ButtonOK_Click(object sender, RoutedEventArgs e)
        {
            if (StrategyNameTxt.Text != "")
            {
                _NewStrategyName = StrategyNameTxt.Text;
            }

            this.Close();
        }

        private void StrategyNameTxt_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                ButtonOK_Click(sender, e);
            }
        }

        //-----------------------------------------------------------------------------------------
        private String _NewStrategyName = null;

 
    }
}
