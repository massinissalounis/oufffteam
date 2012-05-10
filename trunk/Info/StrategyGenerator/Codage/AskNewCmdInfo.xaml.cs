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
    public partial class AskNewCmdInfo : Window
    {
        public AskNewCmdInfo()
        {
            InitializeComponent();

            if (comboBox_Cmd.Items.Count == 0)
            {
                foreach (EnumCmd ECmd in Enum.GetValues(typeof(EnumCmd)))
                {
                    if (ECmd.ToString() != "NotSet")
                        comboBox_Cmd.Items.Add(ECmd.ToString());
                }

                if (comboBox_Cmd.Items.Count > 0)
                    comboBox_Cmd.SelectedIndex = 0;

                _NewCmd = comboBox_Cmd.SelectedItem.ToString();
            }
 
        }

        public String NewCmd { get { return _NewCmd; } }
        public int NewCmdID { get { return _NewCmdID; } }


        private void ButtonOK_Click(object sender, RoutedEventArgs e)
        {
            _NewCmd = comboBox_Cmd.SelectedItem.ToString();
            
            try
            {
                _NewCmdID = Convert.ToInt32(textBox_CmdID.Text);
            }
            catch (Exception)
            {
                _NewCmdID = 0;
            }
            
            this.Close();
        }

        private void checkBox_Auto_Checked(object sender, RoutedEventArgs e)
        {
            if (checkBox_Auto.IsChecked == true)
            {
                _NewCmdID = 0;
                textBox_CmdID.IsEnabled = false;
            }
            else
            {
                textBox_CmdID.IsEnabled = true;
            }
        }

        //-----------------------------------------------------------------------------------------
        private String _NewCmd = EnumCmd.NotSet.ToString();
        private int _NewCmdID = 0;

        private void textBox_CmdID_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
                ButtonOK_Click(sender, e);
        }

 
    }
}
