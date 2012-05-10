using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator.Strategy
{
    class RobotPos
    {
        public RobotPos(int x, int y, int angle, Command CurrentCmd, int Index)
        {
            _PosX = x;
            _PosY = y;
            _PosAngle = angle;

            _ComputedPosX = _PosX;
            _ComputedPosY = _PosY;
            _ComputedPosAngle = _PosAngle;

            _Index = Index;

            UpdateCmd(CurrentCmd);
        }

        public void UpdateCmd(Command CurrentCmd)
        {
            _CurrentCommand = CurrentCmd;
            ComputeNewPos();
        }

        // Property for Inital values
        public int InitalX { get { return _PosX; } }
        public int InitalY { get { return _PosY; } }
        public int InitalAngle { get { return _PosAngle; } }

        // Property for Computed values
        public int X { get { return _ComputedPosX; } }
        public int Y { get { return _ComputedPosY; } }
        public int Angle { get { return _ComputedPosAngle; } }

        public int Index { get { return _Index; } }
        
        // Function for computing final position 
        private void ComputeNewPos()
        {
            if (_CurrentCommand == null)
                return;

            // Compute new pos from CurrentCmd

            switch (_CurrentCommand.Cmd)
            {
                // ________________________________________
                case EnumCmd.Mvt_UseAngleOnly:
                case EnumCmd.MvtSimple_RotateInDeg:
                    _ComputedPosX = _PosX;
                    _ComputedPosY = _PosY;
                    _ComputedPosAngle = _PosAngle + Convert.ToInt32(_CurrentCommand.Param4);
                    break;

                // ________________________________________
                case EnumCmd.Mvt_UseDistOnly:
                    _ComputedPosX = _PosX;
                    _ComputedPosY = _PosY;
                    _ComputedPosAngle = _PosAngle;
                    break;

                // ________________________________________
                case EnumCmd.MvtSimple_RotateToAngleInDeg:
                    _ComputedPosX = _PosX;
                    _ComputedPosY = _PosY;
                    _ComputedPosAngle = Convert.ToInt32(_CurrentCommand.Param4);
                    break;

                // ________________________________________
                case EnumCmd.App_SetNewPos:
                    _PosX = Convert.ToInt32(_CurrentCommand.Param2);
                    _PosY = Convert.ToInt32(_CurrentCommand.Param3);
                    _PosAngle = Convert.ToInt32(_CurrentCommand.Param4);

                    _ComputedPosX = _PosX;
                    _ComputedPosY = _PosY;
                    _ComputedPosAngle = _PosAngle;
                    break;

                // ________________________________________
                case EnumCmd.Mvt_UseMixedMode:
                    _ComputedPosX = Convert.ToInt32(_CurrentCommand.Param2);
                    _ComputedPosY = Convert.ToInt32(_CurrentCommand.Param3);
                    _ComputedPosAngle = Convert.ToInt32(_CurrentCommand.Param4);
                    break;

                // ________________________________________
                case EnumCmd.MvtSimple_MoveInMM:
                    _ComputedPosX = _PosX + Convert.ToInt32(Convert.ToDouble(_CurrentCommand.Param2) * Math.Cos(_PosAngle * Math.PI / 180.0));
                    _ComputedPosY = _PosY + Convert.ToInt32(Convert.ToDouble(_CurrentCommand.Param2) * Math.Sin(_PosAngle * Math.PI / 180.0));;
                    _ComputedPosAngle = _PosAngle;
                    break;

                // ________________________________________
                case EnumCmd.Mvt_UsePivotMode:
                    int XWheel = 0;     // X Pos for the locked wheel
                    int YWheel = 0;     // Y Pos for the locked wheel
                    int Dist = 135;     // Distance between center and locked Wheel
                    int ExpectedAngle = Convert.ToInt32(_CurrentCommand.Param4);

                    if (_CurrentCommand.Param2 == "LEFT_WHEEL")
                    {
                        // Compute the position of the locked wheel
                        XWheel = Convert.ToInt32(_PosX - Dist * Math.Sin(_PosAngle * Math.PI / 180.0));
                        YWheel = Convert.ToInt32(_PosY + Dist * Math.Cos(_PosAngle * Math.PI / 180.0));

                        // Compute the robot center after this movement
                        _ComputedPosX = Convert.ToInt32(XWheel + Dist * Math.Sin(ExpectedAngle * Math.PI / 180.0));
                        _ComputedPosY = Convert.ToInt32(YWheel - Dist * Math.Cos(ExpectedAngle * Math.PI / 180.0));
                        _ComputedPosAngle = ExpectedAngle;

                    }
                    else
                    {
                        // Compute the position of the locked wheel
                        XWheel = Convert.ToInt32(_PosX + Dist * Math.Sin(_PosAngle * Math.PI / 180.0));
                        YWheel = Convert.ToInt32(_PosY - Dist * Math.Cos(_PosAngle * Math.PI / 180.0));

                        // Compute the robot center after this movement
                        _ComputedPosX = Convert.ToInt32(XWheel - Dist * Math.Sin(ExpectedAngle * Math.PI / 180.0));
                        _ComputedPosY = Convert.ToInt32(YWheel + Dist * Math.Cos(ExpectedAngle * Math.PI / 180.0));
                        _ComputedPosAngle = ExpectedAngle;
                    }

                     break;
                
                // ________________________________________
                case EnumCmd.Mvt_Stop:
                case EnumCmd.App_Wait:
                case EnumCmd.App_IfGoto:
                default:
                    _ComputedPosX = _PosX;
                    _ComputedPosY = _PosY;
                    _ComputedPosAngle = _PosAngle;
                    break;
            }

        }

        // ----------------------------------------------------------------------------------------
        private int _PosX = 0;
        private int _PosY = 0;
        private int _PosAngle = 0;

        private int _ComputedPosX = 0;
        private int _ComputedPosY = 0;
        private int _ComputedPosAngle = 0;

        private int _Index = 0;

        private Command _CurrentCommand = null;
    }
}
