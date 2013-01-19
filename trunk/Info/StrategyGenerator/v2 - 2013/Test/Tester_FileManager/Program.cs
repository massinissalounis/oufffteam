using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using StrategyGenerator2.FileManager;

namespace FileManagerTester
{
    class Program
    {
        static void Main(string[] args)
        {
            //Declaration des variables


            // Test 1 : Creation d'un fichier texte 
            try
            {
                Console.WriteLine("Test 1 - Creation d'un fichier texte :");


            }
            catch (Exception ex)
            {
                Console.WriteLine("Test 1 Failed !!");
                Console.WriteLine(ex.Message);
            }

            // Fin du programme
            DisplaySeparator();
            Console.WriteLine("\nTest terminé.");
            Console.Read();
        }

        static private void DisplaySeparator()
        {
            Console.WriteLine("------------------------------------------------------------------------------");
        }
    }
}
