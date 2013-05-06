using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.StrategyViewer
{
    public class RobotPos
    {
        public RobotPos()
        {
            _x = -1;
            _y = -1;
            _angle = 0;
        }

        public RobotPos(int x, int y, int angle, RobotStatusFlag statusFlag)
        {
            _x = x;
            _y = y;
            _angle = angle % 360;
            _statusFlag.HoopStatus = statusFlag.HoopStatus;
            _statusFlag.LeftArmStatus = statusFlag.LeftArmStatus;
            _statusFlag.RightArmStatus = statusFlag.RightArmStatus;
        }

        // Porperties -----------------------------------------------------------------------------
        public int x
        {
            get { return _x; }
            set { _x = value; }
        }

        public int y
        {
            get { return _y; }
            set { _y = value; }
        }

        public int angle
        {
            get { return _angle; }
            set { _angle = value; }
        }

        public RobotStatusFlag statusFlag
        {
            get { return _statusFlag; }
            set 
            {
                if (value != null)
                {
                    _statusFlag.HoopStatus = value.HoopStatus;
                    _statusFlag.LeftArmStatus = value.LeftArmStatus;
                    _statusFlag.RightArmStatus = value.RightArmStatus;
                }
            }
        }

        public String Margin
        {
            get
            {
                double x, y;
                int retX, retY;

                y = Math.Ceiling((2000 - _y - (RobotHeight / 2)) * 0.2);
                
                x = Math.Ceiling((_x - (RobotWidth / 2)) * 0.2);

                retX = Convert.ToInt32(x);
                retY = Convert.ToInt32(y);

                return (retX.ToString() + "," + retY.ToString() + ",0,0");
            }
            set { }
        }

        public String Visibility
        {
            get { if ((_x < 0) || (_y < 0)) { return "Hidden"; } else { return "Visible"; } }
            set { }
        }

        public int Width
        {
            get 
            {
                return Convert.ToInt32(RobotWidth * 0.2);
            }
            set { }
        }

        public int Height
        {
            get { return Convert.ToInt32(RobotHeight * 0.2); }
            set { }
        }

        public String Status
        {
            get
            {
                String Ret = "Robot_";
                // Hoop Status
                if (_statusFlag.HoopStatus == EnumRobotStatusFlag.Open)
                    Ret = Ret + "HO_";
                else
                    Ret = Ret + "HC_";

                // Right Arm
                if (_statusFlag.RightArmStatus == EnumRobotStatusFlag.Front)
                    Ret = Ret + "RF_";
                else if (_statusFlag.RightArmStatus == EnumRobotStatusFlag.Open)
                    Ret = Ret + "RO_";
                else
                    Ret = Ret + "RC_";

                // Left Arm
                if (_statusFlag.LeftArmStatus == EnumRobotStatusFlag.Front)
                    Ret = Ret + "LF";
                else if (_statusFlag.LeftArmStatus == EnumRobotStatusFlag.Open)
                    Ret = Ret + "LO";
                else
                    Ret = Ret + "LC";

                // Final string
                Ret = Ret + ".png";

                return "/StrategyGenerator2;component/Res/" + Ret;
            }
            set { }
        }

        public int CenterX
        {
            get 
            {
                return Convert.ToInt32(RobotWidth / 2 * 0.2);
            }
            set { }
        }

        public int CenterY
        {
            get { return Convert.ToInt32(RobotHeight / 2 * 0.2); }
            set { }
        }

        public int Angle
        {
            get { return (_angle * (-1)); }
            set { }
        }

        // Private --------------------------------------------------------------------------------
        int _x = 0;
        int _y = 0;
        int _angle = 0;
        RobotStatusFlag _statusFlag = new RobotStatusFlag();


        private const int RobotHeight = 465;
        private const int RobotWidth = 705;

    }
}
