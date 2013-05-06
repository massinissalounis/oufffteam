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
    public partial class RobotActionView : UserControl
    {
        public RobotActionView()
        {
            InitializeComponent();
        }

        private void Image_MouseMove(object sender, MouseEventArgs e)
        {
            textBlock_MousePos.Text = "(X = ";
            textBlock_MousePos.Text += (Math.Round(e.MouseDevice.GetPosition(MapPicture).X * 5)).ToString();
            textBlock_MousePos.Text += ", Y = ";
            textBlock_MousePos.Text += (Math.Round(2000 - e.MouseDevice.GetPosition(MapPicture).Y * 5)).ToString();
            textBlock_MousePos.Text += ")";
        }
    }
}
