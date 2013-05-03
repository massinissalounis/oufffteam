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
            _x = 0;
            _y = 0;
            _angle = 0;
            _statusFlag = EnumStatusFlag.NotSet;
        }

        public RobotPos(int x, int y, int angle, EnumStatusFlag statusFlag)
        {
            _x = x;
            _y = y;
            _angle = angle % 180;
            _statusFlag = statusFlag;
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

        public EnumStatusFlag statusFlag
        {
            get { return _statusFlag; }
            set { _statusFlag = value; }
        }

        public String Margin
        {
            get
            {
                double x, y;
                int retX, retY;

                y = Math.Ceiling((2000 - _y - (RobotHeight / 2)) * 0.2);
                
                if(_statusFlag == EnumStatusFlag.RobotIsOpen)
                    x = Math.Ceiling((_x - (OpenedRobotWidth / 2)) * 0.2);
                else
                    x = Math.Ceiling((_x - (ClosedRobotWidth / 2)) * 0.2);

                retX = Convert.ToInt32(x);
                retY = Convert.ToInt32(y);

                return (retX.ToString() + "," + retY.ToString() + ",0,0");
            }
            set { }
        }

        public String Visibility
        {
            get { if (_statusFlag == EnumStatusFlag.NotSet) { return "Hidden"; } else { return "Visible"; } }
            set { }
        }

        public int Width
        {
            get 
            {
                if (_statusFlag == EnumStatusFlag.RobotIsOpen)
                    return Convert.ToInt32(OpenedRobotWidth * 0.2);
                else
                    return Convert.ToInt32(ClosedRobotWidth * 0.2);
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
                if (_statusFlag == EnumStatusFlag.RobotIsOpen)
                    return "/StrategyGenerator2;component/Res/RobotOuvert.png";
                else
                    return "/StrategyGenerator2;component/Res/RobotFermé.png";
            }
            set            { }
        }

        public int CenterX
        {
            get 
            {
                if (_statusFlag == EnumStatusFlag.RobotIsOpen)
                    return Convert.ToInt32(OpenedRobotWidth / 2 * 0.2);
                else
                    return Convert.ToInt32(ClosedRobotWidth / 2 * 0.2);
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
        EnumStatusFlag _statusFlag = EnumStatusFlag.NotSet;


        private const int RobotHeight = 295;
        private const int OpenedRobotWidth = 705;
        private const int ClosedRobotWidth = 195;

    }
}
