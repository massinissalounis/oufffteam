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
            TextFile TextFileFromFile = null;       // Fichier permettant de lire un fichier depuis le disque7
            bool Validated = true;
            int iRet = 0;


            // Test 1 : Creation d'un fichier texte 
            try
            {
                DisplaySeparator(); 
                Console.WriteLine("Test 01 - Creation et chargement d'un fichier texte : \n");
                Console.WriteLine(" -> Creation du fichier");
                TextFileFromFile = new TextFile();

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Chargement du fichier de test :");
                if (TextFileFromFile.Load("TestFiles/Test01_Load.txt") >= 0)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Chargement du fichier vide : ");
                if (TextFileFromFile.Load("TestFiles/Test01_EmptyFile.txt") >= 0)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Tentative d'ouverture d'un fichier inexistant : ");
                if (TextFileFromFile.Load("InvalidFile") == -1)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> FilePath vide : ");
                if (TextFileFromFile.Load("") == -1)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Chargement d'un fichier de 100 Lignes : ");
                if (TextFileFromFile.Load("TestFiles/Test01_100Lines.txt") == 100)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Chargement d'un fichier de 1000 Lignes : ");
                if (TextFileFromFile.Load("TestFiles/Test01_1000Lines.txt") == 1000)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Chargement d'un fichier de 10000 Lignes : ");
                if (TextFileFromFile.Load("TestFiles/Test01_10000Lines.txt") == 10000)
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
                Console.WriteLine("Test 1 Failed !!");
                Console.WriteLine(ex.Message);
            }

            // Fin du programme
            DisplaySeparator();
            Console.Write("\nTest terminé. Etat du module : ");
            
            if(Validated == true)
            {
                Console.Write("Validé !\n");
            }else{
                Console.Write("Non Validé !\n");
            }
            Console.Read();
        }

        static private void DisplaySeparator()
        {
            Console.WriteLine("------------------------------------------------------------------------------");
        }
    }
}
