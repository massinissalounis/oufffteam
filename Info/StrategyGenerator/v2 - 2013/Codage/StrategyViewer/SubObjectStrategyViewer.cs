using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.StrategyViewer
{
    public class RobotStatusFlag
    {
        public RobotStatusFlag()
        {
            _hoopStatus = EnumRobotStatusFlag.Closed;
            _leftArmStatus = EnumRobotStatusFlag.Closed;
            _rightArmStatus = EnumRobotStatusFlag.Closed;
        }

        public RobotStatusFlag(RobotStatusFlag newValue)
        {
            if(newValue != null)
            {
                HoopStatus = newValue.HoopStatus;
                LeftArmStatus = newValue.LeftArmStatus;
                RightArmStatus = newValue.RightArmStatus;
            }
            else
            {
                _hoopStatus = EnumRobotStatusFlag.Closed;
                _leftArmStatus = EnumRobotStatusFlag.Closed;
                _rightArmStatus = EnumRobotStatusFlag.Closed;
            }
        }

        // Public ---------------------------------------------------------------------------------
        public EnumRobotStatusFlag HoopStatus
        {
            get { return _hoopStatus; }
            set
            {
                if (value != null)
                {
                    if (value == EnumRobotStatusFlag.Open)
                        _hoopStatus = value;
                    else
                        _hoopStatus = EnumRobotStatusFlag.Closed;
                }
            }
        }
        public EnumRobotStatusFlag LeftArmStatus
        {
            get { return _leftArmStatus; }
            set
            {
                if (value != null)
                {
                    if ((value == EnumRobotStatusFlag.Open) || (value == EnumRobotStatusFlag.Closed) || (value == EnumRobotStatusFlag.Front))
                        _leftArmStatus = value;
                    else
                        _leftArmStatus = EnumRobotStatusFlag.Closed;
                }
            }
        }
        public EnumRobotStatusFlag RightArmStatus
        {
            get { return _rightArmStatus; }
            set
            {
                if (value != null)
                {

                    if ((value == EnumRobotStatusFlag.Open) || (value == EnumRobotStatusFlag.Closed) || (value == EnumRobotStatusFlag.Front))
                        _rightArmStatus = value;
                    else
                        _rightArmStatus = EnumRobotStatusFlag.Closed;
                }
            }
        }

        // Private --------------------------------------------------------------------------------
        private EnumRobotStatusFlag _hoopStatus = EnumRobotStatusFlag.Closed;
        private EnumRobotStatusFlag _leftArmStatus = EnumRobotStatusFlag.Closed;
        private EnumRobotStatusFlag _rightArmStatus = EnumRobotStatusFlag.Closed;
    }

    public enum EnumRobotStatusFlag
    {
        Closed = 1,
        Open = 2,
        Front = 4,
    }
}
