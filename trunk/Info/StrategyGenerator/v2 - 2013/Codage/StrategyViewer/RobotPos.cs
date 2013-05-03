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
            _statusFlag = EnumStatusFlag.RobotIsClosed;
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

        // Private --------------------------------------------------------------------------------
        int _x = 0;
        int _y = 0;
        int _angle = 0;
        EnumStatusFlag _statusFlag = EnumStatusFlag.NotSet;
    }
}
