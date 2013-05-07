using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GalaSoft.MvvmLight;
using StrategyGenerator2.Model;

namespace StrategyGenerator2.ViewModel
{
    public class HelperVM : ViewModelBase
    {
        public HelperVM()
        {
            _mainModel = MainModel.GetInstance;
            _mainModel.EUpdateCmdDescription += new EventHandler(UpdateData);

        }

        public String HelperDescription
        {
            get
            {
                if (_mainModel != null)
                    return _mainModel.RobotActionDescription;
                else
                    return "";
            }
            set { }
        }


        public String softwareVersion
        {
            get
            {
                if (_mainModel != null)
                    return _mainModel.softwareVersion;
                else
                    return "Version NotSet";
            }
            set
            { }
        }

        // Private --------------------------------------------------------------------------------
        protected MainModel _mainModel = null;                      // Lien vers le model

        private void UpdateData(object sender, EventArgs e)
        {
            RaisePropertyChanged("HelperDescription");
        }
    }
}
