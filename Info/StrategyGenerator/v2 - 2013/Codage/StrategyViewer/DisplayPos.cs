using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using StrategyGenerator2.StrategyManager;

namespace StrategyGenerator2.StrategyViewer
{
    public class DisplayPos
    {
        public DisplayPos(RobotAction robotAction)
        {
            if (robotAction != null)
            {
                _robotAction = robotAction;
                _initialPos = new List<RobotPos>();
            }
        }
        
        public void AddInitialPos(RobotPos initialPos)
        {
            if(initialPos != null)
            {
                if (_initialPos == null)
                    _initialPos = new List<RobotPos>();

                Boolean isNewData = true;

                // On verifie si la position n'existe pas déjà)
                foreach (RobotPos currentRobotPos in _initialPos)
                {
                    if ((initialPos.x == currentRobotPos.x) && (initialPos.y == currentRobotPos.y) && (initialPos.angle == currentRobotPos.angle) && (initialPos.statusFlag.GetValueString() == currentRobotPos.statusFlag.GetValueString()))
                        isNewData = false;
                }

                // L'objet n'a pas été trouvé, on l'ajoute
                if (isNewData == true)
                    _initialPos.Add(new RobotPos(initialPos.x, initialPos.y, initialPos.angle, initialPos.statusFlag));
            }
        }

        public void AddInitialPos(List<RobotPos> listInitialPos)
        {
            if(listInitialPos != null)
            {
                for (int i = 0; i < listInitialPos.Count(); i++)
                    AddInitialPos(listInitialPos[i]);
            }
        }

        public List<RobotPos> GetOutputPos()
        {
            List<RobotPos> outputPos = new List<RobotPos>();
            List<RobotPos> Ret = new List<RobotPos>();
            int transX = 0;
            int transY = 0;
            int transA = 0;

            if(_robotAction != null)
            {
                switch (_robotAction.cmd)
                {
                    // _______________________________________________________
                    case EnumCmd.Mvt_UseMixedMode:
                    case EnumCmd.Mvt_UseSpline:
                    case EnumCmd.App_SetNewPos:
                        if ((int.TryParse(_robotAction.param2, out transX) == true) && (int.TryParse(_robotAction.param3, out transY) == true) && (int.TryParse(_robotAction.param4, out transA) == true))
                        {
                            if (_initialPos.Count() > 0)
                            {
                                foreach (RobotPos currentRobotPos in _initialPos)
                                {
                                    outputPos.Add(new RobotPos(transX, transY, transA, currentRobotPos.statusFlag));
                                }
                            }
                            else
                            {
                                outputPos.Add(new RobotPos(transX, transY, transA, new RobotStatusFlag()));
                            }
                        }
                        else
                        {
                            outputPos.Add(new RobotPos(1500, 1000, 0, new RobotStatusFlag()));
                        }
                        break;

                    // _______________________________________________________
                    case EnumCmd.Mvt_UseAngleOnly:
                    case EnumCmd.MvtSimple_RotateToAngleInDeg:
                        if (int.TryParse(_robotAction.param4, out transA) == true)
                        {
                            foreach (RobotPos currentRobotPos in _initialPos)
                            {
                                outputPos.Add(new RobotPos(currentRobotPos.x, currentRobotPos.y, transA, currentRobotPos.statusFlag));
                            }
                        }
                        else
                        {
                            outputPos.Add(new RobotPos(0, 0, 0, new RobotStatusFlag()));
                        }
                        break;

                    // _______________________________________________________
                    case EnumCmd.MvtSimple_RotateInDeg:
                        if (int.TryParse(_robotAction.param4, out transA) == true)
                        {
                            foreach (RobotPos currentRobotPos in _initialPos)
                            {
                                outputPos.Add(new RobotPos(currentRobotPos.x, currentRobotPos.y, currentRobotPos.angle + transA, currentRobotPos.statusFlag));
                            }
                        }
                        else
                        {
                            outputPos.Add(new RobotPos(0, 0, 0, new RobotStatusFlag()));
                        }
                        break;

                    // _______________________________________________________
                    case EnumCmd.Mvt_UseDistOnly:
                        if ((int.TryParse(_robotAction.param2, out transX) == true) && (int.TryParse(_robotAction.param3, out transY) == true))
                        {
                            foreach (RobotPos currentRobotPos in _initialPos)
                            {
                                outputPos.Add(new RobotPos(transX, transY, currentRobotPos.angle, currentRobotPos.statusFlag));
                            }
                        }
                        else
                        {
                            outputPos.Add(new RobotPos(0, 0, 0, new RobotStatusFlag()));
                        }
                        break;

                    // _______________________________________________________
                    case EnumCmd.Mvt_UsePivotMode:
                        if (int.TryParse(_robotAction.param4, out transA) == true)
                        {
                            foreach (RobotPos currentRobotPos in _initialPos)
                            {
                                int XWheel = 0;     // X Pos for the locked wheel
                                int YWheel = 0;     // Y Pos for the locked wheel
                                int Dist = 135;     // Distance between center and locked Wheel
                                int ExpectedAngle = transA;
                                int _ComputedPosX, _ComputedPosY, _ComputedPosAngle;

                                if (_robotAction.param2 == "LEFT_WHEEL")
                                {
                                    // Compute the position of the locked wheel
                                    XWheel = Convert.ToInt32(currentRobotPos.x - Dist * Math.Sin(currentRobotPos.angle * Math.PI / 180.0));
                                    YWheel = Convert.ToInt32(currentRobotPos.y + Dist * Math.Cos(currentRobotPos.angle * Math.PI / 180.0));

                                    // Compute the robot center after this movement
                                    _ComputedPosX = Convert.ToInt32(XWheel + Dist * Math.Sin(ExpectedAngle * Math.PI / 180.0));
                                    _ComputedPosY = Convert.ToInt32(YWheel - Dist * Math.Cos(ExpectedAngle * Math.PI / 180.0));
                                    _ComputedPosAngle = ExpectedAngle;
                                }
                                else
                                {
                                    // Compute the position of the locked wheel
                                    XWheel = Convert.ToInt32(currentRobotPos.x + Dist * Math.Sin(currentRobotPos.angle * Math.PI / 180.0));
                                    YWheel = Convert.ToInt32(currentRobotPos.y - Dist * Math.Cos(currentRobotPos.angle * Math.PI / 180.0));

                                    // Compute the robot center after this movement
                                    _ComputedPosX = Convert.ToInt32(XWheel - Dist * Math.Sin(ExpectedAngle * Math.PI / 180.0));
                                    _ComputedPosY = Convert.ToInt32(YWheel + Dist * Math.Cos(ExpectedAngle * Math.PI / 180.0));
                                    _ComputedPosAngle = ExpectedAngle;
                                }
                                outputPos.Add(new RobotPos(_ComputedPosX, _ComputedPosY, _ComputedPosAngle, currentRobotPos.statusFlag));
                            }
                        }
                        else
                        {
                            outputPos.Add(new RobotPos(0, 0, 0, new RobotStatusFlag()));
                        }
                        break;

                    // _______________________________________________________
                    case EnumCmd.MvtSimple_MoveInMM:
                        if (int.TryParse(_robotAction.param2, out transX) == true)
                        {
                            foreach (RobotPos currentRobotPos in _initialPos)
                            {
                                int _ComputedPosX = currentRobotPos.x + Convert.ToInt32(Convert.ToDouble(transX) * Math.Cos(currentRobotPos.angle * Math.PI / 180.0));
                                int _ComputedPosY = currentRobotPos.y + Convert.ToInt32(Convert.ToDouble(transX) * Math.Sin(currentRobotPos.angle * Math.PI / 180.0)); ;
                                int _ComputedPosAngle = currentRobotPos.angle;
                                outputPos.Add(new RobotPos(_ComputedPosX, _ComputedPosY, _ComputedPosAngle, currentRobotPos.statusFlag));
                            }
                        }
                        else
                        {
                            outputPos.Add(new RobotPos(0, 0, 0, new RobotStatusFlag()));
                        }

                        break;

                    // _______________________________________________________
                    // Pas de modification sur la position du robot
                    case EnumCmd.Sensors_SetHoopLevel:
                        foreach (RobotPos currentRobotPos in _initialPos)
                        {
                            RobotStatusFlag newStatus = new RobotStatusFlag(currentRobotPos.statusFlag);
                            if (_robotAction.param1 == EnumSensorsHoopLevel.HOOP_LEVEL_UP.ToString())
                            {
                                newStatus.HoopStatus = EnumRobotStatusFlag.Closed;
                                outputPos.Add(new RobotPos(currentRobotPos.x, currentRobotPos.y, currentRobotPos.angle, newStatus));
                            }
                            else
                            {
                                newStatus.HoopStatus = EnumRobotStatusFlag.Open;
                                outputPos.Add(new RobotPos(currentRobotPos.x, currentRobotPos.y, currentRobotPos.angle, newStatus));
                            }
                        }
                        break;

                    // _______________________________________________________
                    // Pas de modification sur la position du robot
                    case EnumCmd.Sensors_SetArmsStatus:
                        foreach (RobotPos currentRobotPos in _initialPos)
                        {
                            RobotStatusFlag newStatus = new RobotStatusFlag(currentRobotPos.statusFlag);

                            if (_robotAction.param1 == "ARM_OPEN")
                                newStatus.RightArmStatus = EnumRobotStatusFlag.Open;
                            else if (_robotAction.param1 == "ARM_FRONT")
                                newStatus.RightArmStatus = EnumRobotStatusFlag.Front;
                            else
                                newStatus.RightArmStatus = EnumRobotStatusFlag.Closed;

                            if (_robotAction.param2 == "ARM_OPEN")
                                newStatus.LeftArmStatus = EnumRobotStatusFlag.Open;
                            else if (_robotAction.param2 == "ARM_FRONT")
                                newStatus.LeftArmStatus = EnumRobotStatusFlag.Front;
                            else
                                newStatus.LeftArmStatus = EnumRobotStatusFlag.Closed;

    
                            outputPos.Add(new RobotPos(currentRobotPos.x, currentRobotPos.y, currentRobotPos.angle, newStatus));
                        }
                        break;

                    // _______________________________________________________
                    // Pas de modification 
                    case EnumCmd.App_IfGoto_Strategy:
                    case EnumCmd.App_IfGoto_System:
                    case EnumCmd.App_SetStrategyFlags:
                    case EnumCmd.App_Wait:
                    case EnumCmd.Mvt_Stop:
                    case EnumCmd.NotSet:
                    default:
                        foreach (RobotPos currentRobotPos in _initialPos)
                        {
                            outputPos.Add(new RobotPos(currentRobotPos.x, currentRobotPos.y, currentRobotPos.angle, currentRobotPos.statusFlag));
                        }
                        break;
                }
            }


            // Verification des données de sortie
            Boolean isAlreadyAdded = false;

            // Pour chaque élément en sortie
            foreach (RobotPos robotPosToChecked in outputPos)
            {
                isAlreadyAdded = false;

                // On verifie s'il n'est pas déjà présent
                foreach (RobotPos currentRobotPos in Ret)
                {
                    if ((currentRobotPos.x == robotPosToChecked.x) && (currentRobotPos.y == robotPosToChecked.y) && (currentRobotPos.angle == robotPosToChecked.angle) && (currentRobotPos.statusFlag.GetValueString() == robotPosToChecked.statusFlag.GetValueString()))
                        isAlreadyAdded = true;
                }

                if (isAlreadyAdded == false)
                    Ret.Add(robotPosToChecked);
            }

            return Ret;
        }

        public List<RobotPos> GetInitialPos()
        {
            return _initialPos;
        }

        public RobotPos GetOutputPos(int index)
        {
            RobotPos Ret = null;

            if ((index >= 0) && (_initialPos != null))
            {
                List<RobotPos> resultList = GetOutputPos();

                if ((resultList != null) && (resultList.Count() > index))
                {
                    Ret = resultList[index];
                }
            }

            if (Ret == null)
                Ret =  new RobotPos();
            
            return Ret;
        }

        // Porperties -----------------------------------------------------------------------------
        public int actionID
        {
            get 
            {
                if (_robotAction != null)
                    return _robotAction.ID;
                else
                    return -1;
            }
            set { }
        }

        public int nextID
        {
            get
            {
                if (_robotAction != null)
                    return _robotAction.nextID;
                else
                    return -1;
            }
            set { }
        }

         // Private --------------------------------------------------------------------------------
        private RobotAction _robotAction = null;
        private List<RobotPos> _initialPos = null;

    }
}
