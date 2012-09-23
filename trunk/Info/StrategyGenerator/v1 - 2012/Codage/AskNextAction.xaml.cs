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
using StrategyGenerator.Strategy;

namespace StrategyGenerator
{
    /// <summary>
    /// Logique d'interaction pour AskStrategyName.xaml
    /// </summary>
    public partial class AskNextAction : Window
    {
        public AskNextAction(String Condition, String ActionID_True, String ActionID_False)
        {
            InitializeComponent();

            try
            {
                String ConditionText = Condition.Replace("+ ", "+\n");
                textBox_Condition.Text = ConditionText;
                _ActionID_True = Convert.ToInt32(ActionID_True);
                _ActionID_False = Convert.ToInt32(ActionID_False);
            }
            catch (Exception)
            {
                this.Close();
            }
        }

        public int NextCmdIDSelected { get { return _NextCmdIDSelected; } }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            String ButtonSelected= ((Button)sender).Content.ToString();
            if (ButtonSelected == "True")
                _NextCmdIDSelected = _ActionID_True;
            else
                _NextCmdIDSelected = _ActionID_False;

            this.Close();
        }

        private int _NextCmdIDSelected = 0;
        private int _ActionID_True = 0;
        private int _ActionID_False = 0;
    }
}