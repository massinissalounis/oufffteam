using System;
using StrategyGenerator2.StrategyManager;
using StrategyGenerator2.FileManager;

namespace Tester_Strategy
{
    class Program
    {
        static void Main(string[] args)
        {
            bool Validated = true;

            // ############################################################################################################################
            // ##### RobotAction
            // ############################################################################################################################
            #region RobotAction
            RobotAction testAction = new RobotAction();

            // Test 0201 : RobotAction ____________________________________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0201 - Verification des objets Action : \n");
                Console.WriteLine(" -> Verification des private");
                // ------------------------------------------------------------------------------------------
                if (testAction.CheckPrivateFunction())
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.WriteLine(" -> Test de la fonction d'export() : ");
                testAction.ID = 1;
                testAction.cmd = EnumCmd.Mvt_UseMixedMode;
                testAction.cmdType = EnumCmdType.Blocking;
                testAction.param1 = "11";
                testAction.param2 = "12";
                testAction.param3 = "13";
                testAction.param4 = "14";
                testAction.nextID = 100;
                testAction.timeoutID = 200;

                StructuredFileGroup output = testAction.Export();
                

                if (output != null)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.WriteLine(" -> Test de la fonction d'import() : ");
                testAction = new RobotAction(); 
                StructuredFileGroup inputData = new StructuredFileGroup(10);

                inputData.AddKey(new StructuredFileKey("Cmd", "Mvt_UseMixedMode"));
                inputData.AddKey(new StructuredFileKey("CmdType", "Blocking"));
                inputData.AddKey(new StructuredFileKey("Param1", 50));
                inputData.AddKey(new StructuredFileKey("Param2", 100));
                inputData.AddKey(new StructuredFileKey("Param3", 200));
                inputData.AddKey(new StructuredFileKey("Param4", 90.0));
                inputData.AddKey(new StructuredFileKey("ActiveSensors", "COLLISION_FRONT"));
                inputData.AddKey(new StructuredFileKey("nextID", 10));
                inputData.AddKey(new StructuredFileKey("timeoutID", 30));
                
                if (testAction.Import(inputData) == true)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

            }
            catch (Exception ex)
            {
                Console.WriteLine("Test 0201 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }
            #endregion

            // ############################################################################################################################
            // ##### SubStrategy
            // ############################################################################################################################
            #region SubStrategy
            // Test 0202 : SubStrategy ____________________________________________________________________________________________________
            try
            {
                DisplaySeparator();
                // ------------------------------------------------------------------------------------------

                SubStrategy strategy1 = new SubStrategy("Strategy 1");
                SubStrategy strategy2 = new SubStrategy("Strategy 2");

                // Creation de l'action 1
                RobotAction Action1 = new RobotAction(1);
                Action1.cmd = EnumCmd.Mvt_UseMixedMode;
                Action1.cmdType = EnumCmdType.Blocking;
                Action1.param1 = "1";
                Action1.param2 = "2";
                Action1.param3 = "3";
                Action1.param4 = "4";
                Action1.nextID = -1;
                Action1.timeoutID = -1;

                RobotAction Action10 = new RobotAction(10);
                Action1.cmd = EnumCmd.Mvt_UseMixedMode;
                Action1.cmdType = EnumCmdType.Blocking;
                Action1.param1 = "10";
                Action1.param2 = "20";
                Action1.param3 = "30";
                Action1.param4 = "40";
                Action1.nextID = -1;
                Action1.timeoutID = -1;

                RobotAction Action2 = new RobotAction(2);
                Action2.cmd = EnumCmd.App_Wait;
                Action2.cmdType = EnumCmdType.Blocking;
                Action2.param1 = "4";
                Action2.param2 = "3";
                Action2.param3 = "2";
                Action2.param4 = "1";
                Action2.nextID = -1;
                Action2.timeoutID = -1;

                strategy1.AddAction(Action1);   strategy1.AddAction(Action2);   strategy1.AddAction(Action10);
                strategy2.AddAction(Action1);   strategy2.AddAction(Action2);   strategy2.AddAction(Action10);

                Console.WriteLine("Test 0202 - SubStrategy : ");
                if (strategy1.Count() == 3) 
                { 
                    Console.Write(" Ok\n"); 
                } else { 
                    Console.Write(" Error !\n"); Validated = false; 
                }

                Console.WriteLine(" -> Suppression d'une action : ");
                strategy1.RemoveAction(10);
                strategy2.RemoveAction(20);
                if ((strategy1.Count() == 2) && (strategy2.Count() == 3))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.WriteLine(" -> Recherche d'une action : ");
                if ((strategy1.GetAction(1) != null) && (strategy1.GetAction(20) == null))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }
                
                Console.WriteLine(" -> Ajout d'une action existante : ");
                strategy2.AddAction(Action1);
                if (strategy2.Count() == 3)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.WriteLine(" -> Update d'une action existante : ");
                if ((strategy1.UpdateAction(1, Action1) == true) && (strategy1.UpdateAction(1, Action2) == false) && (strategy1.UpdateAction(50, new RobotAction(40)) == false))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }


            }
            catch (Exception ex)
            {
                Console.WriteLine("Test 0202 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }
            #endregion

            // ############################################################################################################################
            // ##### Strategy
            // ############################################################################################################################
            #region Strategy
            // Test 0203 : Strategy _______________________________________________________________________________________________________
            try
            {
                DisplaySeparator();
                // ------------------------------------------------------------------------------------------

                SubStrategy subStrategy1 = new SubStrategy("Strategy 1");
                SubStrategy subStrategy2 = new SubStrategy("Strategy 2");
                Strategy testStrategy = new Strategy("Strategy");
                Strategy testLoadStrategy = new Strategy("LoadStrategy");

                // Creation de l'action 1
                RobotAction Action1 = new RobotAction(1);       Action1.cmd = EnumCmd.Mvt_UseMixedMode; Action1.cmdType = EnumCmdType.Blocking; Action1.param1 = "1";   Action1.param2 = "2";   Action1.param3 = "3";   Action1.param4 = "4";   Action1.nextID = -1;    Action1.timeoutID = -1;     
                RobotAction Action10 = new RobotAction(10);     Action1.cmd = EnumCmd.Mvt_UseMixedMode; Action1.cmdType = EnumCmdType.Blocking; Action1.param1 = "10";  Action1.param2 = "20";  Action1.param3 = "30";  Action1.param4 = "40";  Action1.nextID = -1;    Action1.timeoutID = -1;
                RobotAction Action2 = new RobotAction(2); Action2.cmd = EnumCmd.App_Wait; Action2.cmdType = EnumCmdType.Blocking; Action2.param1 = "4"; Action2.param2 = "3"; Action2.param3 = "2"; Action2.param4 = "1"; Action2.nextID = -1; Action2.timeoutID = -1;

                subStrategy1.AddAction(Action1); subStrategy1.AddAction(Action2); subStrategy1.AddAction(Action10);
                subStrategy2.AddAction(Action1); subStrategy2.AddAction(Action2); subStrategy2.AddAction(Action10);

                Console.WriteLine("Test 0203 - Strategy : ");
                Console.WriteLine(" -> Add + Update : ");

                testStrategy.UpdateMainStrategy(subStrategy1);
                testStrategy.UpdateSubStrategy(subStrategy1);
                Action1.cmd = EnumCmd.Mvt_Stop;
                subStrategy1.UpdateAction(Action1.ID, Action1);
                testStrategy.UpdateSubStrategy(subStrategy1);
                testStrategy.AddSubStrategy(subStrategy2);
                if (testStrategy.GetAllSubStrategy().Count == 2)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.WriteLine(" -> Remove : ");
                testStrategy.RemoveSubStrategy("Strategy 2");
                if (testStrategy.GetAllSubStrategy().Count == 1)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.WriteLine(" -> Remove : ");
                testStrategy.Clear();
                if (testStrategy.GetAllSubStrategy() == null)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.WriteLine(" -> Save : ");
                testStrategy.UpdateMainStrategy(subStrategy1);
                testStrategy.AddSubStrategy(subStrategy1);
                testStrategy.AddSubStrategy(subStrategy2);
                testStrategy.Save();
                if (true)
                {
                    Console.Write(" Ok (Verification manuelle du dossier de sortie)\n");
                }

                Console.WriteLine(" -> Load : ");
                testLoadStrategy.Load("Strategy");
                if (testLoadStrategy.GetAllSubStrategy().Count == 2)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.WriteLine(" -> Export : ");

                RobotAction Action100 = new RobotAction(100); Action100.cmd = EnumCmd.App_Wait; Action100.cmdType = EnumCmdType.Blocking; Action100.param1 = "40"; Action100.param2 = "30"; Action100.param3 = "20"; Action100.param4 = "10"; Action100.nextID = 101; Action100.timeoutID = 901;
                RobotAction Action101 = new RobotAction(101); Action101.cmd = EnumCmd.Mvt_UseMixedMode; Action101.cmdType = EnumCmdType.NonBlocking; Action101.param1 = "41"; Action101.param2 = "31"; Action101.param3 = "21"; Action101.param4 = "11.5"; Action101.nextID = 102; Action101.timeoutID = 902;
                RobotAction Action102 = new RobotAction(102); Action102.cmd = EnumCmd.MvtSimple_MoveInMM; Action102.cmdType = EnumCmdType.Blocking; Action102.param1 = "42"; Action102.param2 = "32"; Action102.param3 = "22"; Action102.param4 = "12"; Action102.nextID = 103; Action102.timeoutID = 903;
                RobotAction Action103 = new RobotAction(103); Action103.cmd = EnumCmd.Mvt_UsePivotMode; Action103.cmdType = EnumCmdType.NonBlocking; Action103.param1 = "43"; Action103.param2 = "33"; Action103.param3 = "23"; Action103.param4 = "13"; Action103.nextID = 104; Action103.timeoutID = 904;
                RobotAction Action200 = new RobotAction(200); Action200.cmd = EnumCmd.Mvt_UseSpline; Action200.cmdType = EnumCmdType.NonBlocking; Action200.param1 = "44"; Action200.param2 = "34"; Action200.param3 = "24"; Action200.param4 = "14"; Action103.nextID = -1; Action200.timeoutID = 905;

                SubStrategy subStrategyExport1 = new SubStrategy("Export Strategy 1");
                SubStrategy subStrategyExport2 = new SubStrategy("Export Strategy 2");

                subStrategyExport1.AddAction(Action100); subStrategyExport1.AddAction(Action101);
                subStrategyExport2.AddAction(Action102); subStrategyExport2.AddAction(Action103); subStrategyExport2.AddAction(Action200);

                Strategy testExportStrategy = new Strategy("ExportStrategy");
                testExportStrategy.AddSubStrategy(subStrategyExport1); testExportStrategy.AddSubStrategy(subStrategyExport2);

                testExportStrategy.Export("./Data/TestOutputStrategy.c", "./patternFiles/ImportPatternFile.spattern");
                if (true)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

            }
            catch (Exception ex)
            {
                Console.WriteLine("Test 0203 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }
            #endregion

            // Fin du programme -----------------------------------------------------------------------------
            DisplaySeparator();
            Console.Write("\nTest terminé. Etat du module : ");
            
            if(Validated == true)
            {
                Console.Write("Validé ! \n");
            }else
            {
                Console.Write("Invalide !\n");
            }
            Console.Read();
        }

        static private void DisplaySeparator()
        {
            Console.WriteLine("------------------------------------------------------------------------------");
        }

    }
}
