using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

            SubStrategy strategy1 = new SubStrategy("Strategy 1");

            // Test 0202 : SubStrategy ____________________________________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0202 - Verification des subStrategy : \n");
                // ------------------------------------------------------------------------------------------
                if (false)
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
