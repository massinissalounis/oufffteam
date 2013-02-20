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
            // ############################################################################################################################
            // ##### TextFile
            // ############################################################################################################################
            #region TexteFile
            //Declaration des variables
            TextFile textFileFromFile = null;       // Fichier permettant de lire un fichier depuis le disque
            TextFile newTextFile = null;            // Fichier pour tester l'ajout et la suppression de ligne
            bool Validated = true;

            // Test 0101 : Creation d'un fichier texte __________________________________________________________________________
            try
            {
                DisplaySeparator(); 
                Console.WriteLine("Test 0101 - Creation et chargement d'un fichier texte : \n");
                Console.WriteLine(" -> Creation du fichier");
                textFileFromFile = new TextFile();

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Chargement du fichier de test :");
                if (textFileFromFile.Load("TestFiles/Test_Load.txt") >= 0)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Chargement du fichier vide : ");
                if (textFileFromFile.Load("TestFiles/Test_EmptyFile.txt") >= 0)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Tentative d'ouverture d'un fichier inexistant : ");
                if (textFileFromFile.Load("InvalidFile") == -1)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> FilePath vide : ");
                if (textFileFromFile.Load("") == -1)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Chargement d'un fichier de 100 Lignes : ");
                if (textFileFromFile.Load("TestFiles/Test_100Lines.txt") == 100)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Chargement d'un fichier de 1000 Lignes : ");
                if (textFileFromFile.Load("TestFiles/Test_1000Lines.txt") == 1000)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Chargement d'un fichier de 10000 Lignes : ");
                if (textFileFromFile.Load("TestFiles/Test_10000Lines.txt") == 10000)
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
                Console.WriteLine("Test 0101 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }

            // Test 0102 : Verification des propriétés __________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0102 - Test des priorités : \n");
                Console.WriteLine(" -> Creation du fichier");
                newTextFile = new TextFile();

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Count sur un fichier vide :");
                if (newTextFile.Count == 0)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Count sur un fichier normal (100 Lignes) :");
                newTextFile.Load("TestFiles/Test_100Lines.txt");
                if (newTextFile.Count == 100)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Count sur un fichier normal (1000 Lignes) :");
                newTextFile.Load("TestFiles/Test_1000Lines.txt");
                if (newTextFile.Count == 1000)
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
                Console.WriteLine("Test 0102 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }

            // Test 0103 : Ajout de ligne _______________________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0103 - Ajout de nouvelle ligne : \n");
                Console.WriteLine(" -> Creation du fichier");
                newTextFile = new TextFile();

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Ajout d'une ligne dans un fichier vide:");
                newTextFile.AddLine("Ligne 01");
                if (newTextFile.Count == 1)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Ajout d'une ligne vide :");
                newTextFile.AddLine(null);
                if (newTextFile.Count == 1)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Ajout d'une ligne sans contenu :");
                newTextFile.AddLine("");
                if (newTextFile.Count == 2)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Ajout d'une ligne avec un index erroné :");
                newTextFile.AddLine("Ligne -1", -1);
                if (newTextFile.Count == 2)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Ajout d'une ligne à un index spécifié :");
                newTextFile.AddLine("Ligne 00", 0);
                if (newTextFile.Count == 3)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Ajout d'une ligne null à un index spécifié :");
                newTextFile.AddLine(null, 0);
                if (newTextFile.Count == 3)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Ajout d'une ligne à un index erroné :");
                newTextFile.AddLine(null, -1);
                if (newTextFile.Count == 3)
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
                Console.WriteLine("Test 0103 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }

            // Test 0104 : Récupération d'une ligne _____________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0104 - Lecture d'une ligne : \n");
                Console.WriteLine(" -> Creation du fichier");
                newTextFile = new TextFile();

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Lecture d'une ligne dans un fichier vide:");
                if (newTextFile.GetLine(0) == null)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Lecture d'une ligne avec un index négatif :");
                newTextFile.AddLine("Ligne 01");
                newTextFile.AddLine("Ligne 02");
                newTextFile.AddLine("Ligne 03");
                if (newTextFile.GetLine(-1) == null)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Lecture d'une ligne avec un index erroné :");
                if (newTextFile.GetLine(100) == null)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Lecture d'une ligne valide :");
                if (newTextFile.GetLine(0) == "Ligne 01")
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Lecture de la dernière ligne du fichier :");
                if (newTextFile.GetLine(2) == "Ligne 03")
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
                Console.WriteLine("Test 0104 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }

            // Test 0105 : Sauvegarde du fichier ________________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0105 - Sauvegarde des fichiers : \n");
                Console.WriteLine(" -> Creation du fichier");
                newTextFile = new TextFile();

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Sauvegarde d'un fichier non initialisé :");
                if (newTextFile.Save() == -1)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Sauvegarde d'un fichier null :");
                if (newTextFile.SaveTo(null) == -1)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Sauvegarde d'un fichier non valide :");
                if (newTextFile.SaveTo("Invalid") == -1)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Sauvegarde dans un fichier valide :");
                newTextFile.Load("TestFiles/Test_100Lines.txt");
                if (newTextFile.SaveTo("TestFiles/Test_100Lines_ouptut_SaveTo.txt") == 100)
                {
                    Console.Write(" Ok + Verification manuelle à réaliser\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Sauvegarde d'un fichier valide :");
                newTextFile.SaveTo("TestFiles/Test_100Lines_ouptut_Save.txt");
                if (newTextFile.Save() == 100)
                {
                    Console.Write(" Ok + Verification manuelle à réaliser\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Test 0105 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }

            // Test 0106 : Caractère spéciaux ___________________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0106 - Utilisation de caractères spéciaux : \n");
                Console.WriteLine(" -> Creation du fichier");
                newTextFile = new TextFile();
                String textToCheck = "\t&@éèàûîêäëïç'§µ%";
                newTextFile.AddLine(textToCheck);

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Ecriture du fichier :");
                if (newTextFile.SaveTo("TestFiles/SpecificChar.txt") > 0)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Relecture du fichier :");
                newTextFile.Load("TestFiles/SpecificChar.txt");
                if (newTextFile.GetLine(0) == textToCheck)
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
                Console.WriteLine("Test 0106 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }

            // Test 0107 : Suppression d'une ligne ______________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0107 - Suppression d'une ligne : \n");
                Console.WriteLine(" -> Creation du fichier");
                newTextFile = new TextFile();

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Suppression d'une ligne dans un fichier vide :");
                newTextFile.RemoveLine(0);
                if (newTextFile.Count == 0)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Suppression d'une ligne non valide :");
                newTextFile.RemoveLine(-1);
                if (newTextFile.Count == 0)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Suppression d'une ligne dans un fichier :");
                newTextFile.AddLine("Ligne01");
                newTextFile.AddLine("Ligne02");
                newTextFile.AddLine("Ligne03");
                newTextFile.RemoveLine(0);
                if ((newTextFile.Count == 2) && (newTextFile.GetLine(0) == "Ligne02"))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Suppression de toutes les lignes d'un fichier :");
                newTextFile.AddLine("Ligne01");
                newTextFile.AddLine("Ligne02");
                newTextFile.AddLine("Ligne03");
                newTextFile.RemoveAllLine();
                if (newTextFile.Count == 0)
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
                Console.WriteLine("Test 0107 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }
            #endregion 

            // ############################################################################################################################
            // ##### StructuredFileKey
            // ############################################################################################################################
            #region StructuredFileKey
            StructuredFileKey testKey = null;
            // Test 0201 : Constructeurs ________________________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0201 - StructuredFileKey : \n");
                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Constructeur vide :");
                testKey = new StructuredFileKey();
                if ((null != testKey) && (testKey.ID == null) && (testKey.valueString == null))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres ('keyString', 'valueString') :");
                testKey = new StructuredFileKey("keyString", "valueString");
                if ((null != testKey) && (testKey.ID == "keyString") && (testKey.valueString == "valueString"))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres ('keyInt', 100) :");
                testKey = new StructuredFileKey("keyInt", 100);
                if ((null != testKey) && (testKey.ID == "keyInt") && (testKey.valueInt == 100))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres ('keyDouble', 1.2) :");
                testKey = new StructuredFileKey("keyDouble", 1.2);
                if ((null != testKey) && (testKey.ID == "keyDouble") && (testKey.valueDouble == 1.2))
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
            // ##### StructuredFileGroup
            // ############################################################################################################################
            #region StructuredFileGroup
            StructuredFileGroup testKeyGroup = null;
            // Test 0301 : Constructeurs ________________________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0301 - StructuredFileGroup : \n");
                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Constructeur vide :");
                testKeyGroup = new StructuredFileGroup();
                if ((testKeyGroup.groupID == -1) && (testKeyGroup.GetAllKeys() == null))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres (groupID = -50) :");
                testKeyGroup = new StructuredFileGroup(-50, new StructuredFileKey("TestID", "TestValue"));
                if ((testKeyGroup.groupID == -1) && (testKeyGroup.GetAllKeys() == null))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres (groupID = 0 et key = null) :");
                testKeyGroup = new StructuredFileGroup(0, null);
                if ((testKeyGroup.groupID == -1) && (testKeyGroup.GetAllKeys() == null))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres (groupID = 0 et key = (TestKey, TestValue) :");
                testKeyGroup = new StructuredFileGroup(5, new StructuredFileKey("TestKey", "TestValue");
                if ((testKeyGroup.groupID == 5) && (testKeyGroup.GetAllKeys().Count == 1))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Test de la fonction GetAllKeys() :");
                testKeyGroup = new StructuredFileGroup();
                Faire la fonction d'ajout
                if ((testKeyGroup.groupID == 5) && (testKeyGroup.GetAllKeys().Count == 1))
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
                Console.WriteLine("Test 0301 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }
            #endregion

            // ############################################################################################################################
            // ##### StructuredFile
            // ############################################################################################################################
            #region StructuredFile
            StructuredFile testStructuredFile = null;
            // Test 0401 : Constructeurs ________________________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0401 - Constructeurs : \n");
                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Constructeur vide :");
                testStructuredFile = new StructuredFile();
                if (null != testStructuredFile)
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
                Console.WriteLine("Test 0401 Failed !!");
                Console.WriteLine(ex.Message);
                Validated = false;
            }

            #endregion

            // Fin du programme -----------------------------------------------------------------------------
            DisplaySeparator();
            Console.Write("\nTest terminé. Etat du module : ");
            
            if(Validated == true)
            {
                Console.Write("Validé ! \n(Sous réserve que les fichiers de sortie soit valides)\n");
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
