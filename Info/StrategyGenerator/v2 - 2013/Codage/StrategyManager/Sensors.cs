using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.StrategyManager
{
    public class Sensors
    {
        // Public 
        public Sensors(EnumCollisionSensors sensorName)
        {
            _name = sensorName.ToString();
            _fullName = "APP_PARAM_STRATEGYFLAG_" + sensorName;
        }

        public String name
        {
            get { return _name; }
            set { }
        }

        public String fullName
        {
            get { return _fullName; }
            set { }
        }

        public Boolean isActivated
        {
            get { return _isActivated; }
            set { _isActivated = value; }
        }

        // Private --------------------------------------------------------------------------------
        private String _name = "NotSet";
        private String _fullName = "NotSet";
        private Boolean _isActivated = false;
    }
}
