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
                if (newTextFile.Count() == 0)
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
                if (newTextFile.Count() == 100)
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
                if (newTextFile.Count() == 1000)
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
                if (newTextFile.Count() == 1)
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
                if (newTextFile.Count() == 1)
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
                if (newTextFile.Count() == 2)
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
                if (newTextFile.Count() == 2)
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
                if (newTextFile.Count() == 3)
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
                if (newTextFile.Count() == 3)
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
                if (newTextFile.Count() == 3)
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
                if (newTextFile.Count() == 0)
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
                if (newTextFile.Count() == 0)
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
                if ((newTextFile.Count() == 2) && (newTextFile.GetLine(0) == "Ligne02"))
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
                if (newTextFile.Count() == 0)
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
                if ((null != testKey) && (testKey.keyName == null) && (testKey.valueString == null))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres ('keyString', 'valueString') :");
                testKey = new StructuredFileKey("keyString", "valueString");
                if ((null != testKey) && (testKey.keyName == "keyString") && (testKey.valueString == "valueString"))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres ('keyInt', 100) :");
                testKey = new StructuredFileKey("keyInt", 100);
                if ((null != testKey) && (testKey.keyName == "keyInt") && (testKey.valueInt == 100))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres ('keyDouble', 1.2) :");
                testKey = new StructuredFileKey("keyDouble", 1.2);
                if ((null != testKey) && (testKey.keyName == "keyDouble") && (testKey.valueDouble == 1.2))
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
            StructuredFileGroup testKeyGroup1 = null;
            StructuredFileGroup testKeyGroup2 = null;
            // Test 0301 : Constructeurs ________________________________________________________________________________________
            try
            {
                DisplaySeparator();
                Console.WriteLine("Test 0301 - StructuredFileGroup : \n");
                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Constructeur vide :");
                testKeyGroup = new StructuredFileGroup(0);
                if ((testKeyGroup.ID == 0) && (testKeyGroup.GetAllKeys() == null))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres (groupID = 0 et key = null) :");
                testKeyGroup = new StructuredFileGroup(0, null);
                if ((testKeyGroup.ID == 0) && (testKeyGroup.GetAllKeys() == null))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Constructeur avec paramètres (groupID=0 et key=(TestKey, TestValue) :");
                testKeyGroup = new StructuredFileGroup(5, new StructuredFileKey("TestKey", "TestValue"));
                if ((testKeyGroup.ID == 5) && (testKeyGroup.GetAllKeys().Count == 1))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Test de la fonction Add() :");
                testKeyGroup = new StructuredFileGroup(1);
                testKeyGroup.AddKey(new StructuredFileKey("1", "1"));
                testKeyGroup.AddKey(new StructuredFileKey("2", "2"));
                if ((testKeyGroup.ID == 1) && (testKeyGroup.GetAllKeys().Count == 2))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }
                
                Console.Write(" -> Test de la fonction Add(List<>) :");
                testKeyGroup = new StructuredFileGroup(1);
                List<StructuredFileKey> listToAdd = new List<StructuredFileKey>();
                listToAdd.Add(new StructuredFileKey("1", "1"));
                listToAdd.Add(new StructuredFileKey("2", "2"));
                testKeyGroup.AddKey(listToAdd);
                if ((testKeyGroup.ID == 1) && (testKeyGroup.Count() == 2))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }
                
                Console.Write(" -> Test de la fonction Count() :");
                testKeyGroup = new StructuredFileGroup(1, null);
                testKeyGroup1 = new StructuredFileGroup(1, new StructuredFileKey("Key1", "Value1"));
                testKeyGroup2 = new StructuredFileGroup(2, new StructuredFileKey("Key1", "Value1"));
                testKeyGroup2.AddKey(new StructuredFileKey("Key2", "Value2"));
                if ((testKeyGroup.Count() == 0) && (testKeyGroup1.Count() == 1) && (testKeyGroup2.Count() == 2))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Test de la fonction GetAllKeys() :");
                testKeyGroup = new StructuredFileGroup(1);
                testKeyGroup.AddKey(new StructuredFileKey("Key1", "Value1"));
                testKeyGroup.AddKey(new StructuredFileKey("Key2", "Value2"));
                if ((testKeyGroup.ID == 1) && (testKeyGroup.GetAllKeys().Count() == 2))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Test de la fonction GetKeys(keyID) :");
                testKeyGroup = new StructuredFileGroup(1);
                testKeyGroup.AddKey(new StructuredFileKey("Key1", "Value1"));
                testKeyGroup.AddKey(new StructuredFileKey("Key2", "Value2"));
                testKeyGroup.AddKey(new StructuredFileKey("Key2", "Value22"));
                if ((testKeyGroup.ID == 1) && (testKeyGroup.GetKeys("Key3") == null) && (testKeyGroup.GetKeys("Key2").Count() == 2))
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
            StructuredFile testStructuredFile2 = null;
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

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Constructeur avec paramètre :");
                testStructuredFile = new StructuredFile("CheminInvalid");
                if (null != testStructuredFile)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Fonction GetAllGroupID vide :");
                testStructuredFile = new StructuredFile();
                if (testStructuredFile.GetAllGroup() == null)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }
                
                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Fonction d'ajout :");
                testStructuredFile = new StructuredFile();
                testStructuredFile2 = new StructuredFile();
                testStructuredFile.AddGroup(new StructuredFileGroup(1));
                testStructuredFile.AddGroup(null);
                testStructuredFile2.AddGroup(new StructuredFileGroup(1, new StructuredFileKey("Key1", 1)));
                testStructuredFile2.AddGroup(new StructuredFileGroup(1, new StructuredFileKey("Key2", 2)));
                testStructuredFile2.AddGroup(new StructuredFileGroup(2, new StructuredFileKey("Key3", 3)));
                if ((testStructuredFile.GetAllGroup().Count() == 1) && (testStructuredFile.GetAllGroup().Count() == 1))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Fonction de suppression totale :");
                testStructuredFile = new StructuredFile();
                testStructuredFile2 = new StructuredFile();
                testStructuredFile.AddGroup(new StructuredFileGroup(1));
                testStructuredFile.AddGroup(new StructuredFileGroup(2));
                testStructuredFile.AddGroup(new StructuredFileGroup(3));
                testStructuredFile.RemoveAllGroup();
                testStructuredFile2.RemoveAllGroup();
                if ((testStructuredFile.GetAllGroup() == null) && (testStructuredFile2.GetAllGroup() == null))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Fonction de suppression à partir de l'ID :");
                testStructuredFile = new StructuredFile();
                testStructuredFile2 = new StructuredFile();
                testStructuredFile.AddGroup(new StructuredFileGroup(1));
                testStructuredFile.AddGroup(new StructuredFileGroup(2));
                testStructuredFile.AddGroup(new StructuredFileGroup(3));
                testStructuredFile.RemoveGroupByID(2);
                testStructuredFile.RemoveGroupByID(5);
                testStructuredFile2.RemoveGroupByID(5);
                if (testStructuredFile.GetAllGroup().Count() == 2)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Fonction de recherche à partir de l'ID :");
                testStructuredFile = new StructuredFile();
                testStructuredFile2 = new StructuredFile();
                testStructuredFile.AddGroup(new StructuredFileGroup(1));
                testStructuredFile.AddGroup(new StructuredFileGroup(2));
                testStructuredFile.AddGroup(new StructuredFileGroup(3));
                if ((testStructuredFile2.GetGroupByID(5) == null) && (testStructuredFile.GetGroupByID(5) == null) && (testStructuredFile.GetGroupByID(2).ID == 2))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Ecriture du fichier via SaveTo (format par défaut) :");
                testStructuredFile = new StructuredFile();
                testStructuredFile2 = new StructuredFile();
                testStructuredFile.AddGroup(new StructuredFileGroup(1));
                StructuredFileGroup newGroup = new StructuredFileGroup(2,new StructuredFileKey("Key1", 1));
                newGroup.AddKey(new StructuredFileKey("Key2", 2));
                newGroup.AddKey(new StructuredFileKey("Key3", 3));
                testStructuredFile.AddGroup(newGroup);
                testStructuredFile.AddGroup(new StructuredFileGroup(3,new StructuredFileKey("Key1", 10)));

                if ((testStructuredFile.SaveTo("TestFiles/StructuredFile.sfile") > 0) && (testStructuredFile2.SaveTo("TestFiles/StructuredFileErr.sfile") == -1))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                Console.Write(" -> Ecriture du fichier via Save (format par défaut) :");
                if ((testStructuredFile.Save() > 0) && (testStructuredFile2.Save() == -1))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Lecture d'un fichier :");
                newTextFile = new TextFile();
                newTextFile.AddLine("key1 = A");
                newTextFile.AddLine("key2 = B");
                newTextFile.AddLine("[Groupe 5]");
                newTextFile.AddLine("key3 = C");
                newTextFile.AddLine("key4 = D");
                newTextFile.AddLine("key5 E");
                newTextFile.AddLine("key6 = F");
                newTextFile.AddLine("key7 = G");
                newTextFile.AddLine("key8 = H");
                newTextFile.AddLine("key9 = I");
                newTextFile.AddLine("      ");
                newTextFile.AddLine("key10 = J");
                newTextFile.AddLine("[Groupe A]");
                newTextFile.AddLine("key11 = K");
                newTextFile.AddLine("key12 = L");
                newTextFile.AddLine("[ Groupe 5]");
                newTextFile.AddLine("[Groupe 7]");
                newTextFile.AddLine("[Groupe 5]");
                newTextFile.AddLine("key13 = M");
                
                testStructuredFile = new StructuredFile();

                if ((testStructuredFile.Load(newTextFile) > 0) && (testStructuredFile.SaveTo("TestFiles/StructuredFile2.sfile") > 0))
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Export d'un fichier :");
                newTextFile = new TextFile();
                newTextFile.AddLine("[Groupe 0]");
                newTextFile.AddLine("Key1 = (0,1)");
                newTextFile.AddLine("Key2 = (0,2)");
                newTextFile.AddLine("[Groupe 2]");
                newTextFile.AddLine("Key1 = (2,1)");
                newTextFile.AddLine("Key2 = (2,2)");
                newTextFile.AddLine("[Groupe 3]");
                newTextFile.AddLine("Key1 = (3,1)");
                newTextFile.AddLine("Key2 = (3,2)");
                newTextFile.AddLine("[Groupe 1]");
                newTextFile.AddLine("Var1 = Var1-1");
                newTextFile.AddLine("Var2 = Var2-1");
                newTextFile.AddLine("Var3 = Var3-1");
                newTextFile.AddLine("Var4 = Var4-1");
                newTextFile.AddLine("Var5 = Var5-1");
                newTextFile.AddLine("[Groupe 2]");
                newTextFile.AddLine("Var1 = Var1-2");
                newTextFile.AddLine("Var2 = Var2-2");
                newTextFile.AddLine("Var3 = Var3-2");
                newTextFile.AddLine("Var4 = Var4-2");
                newTextFile.AddLine("Var5 = Var5-2");
                newTextFile.AddLine("[Groupe 3]");
                newTextFile.AddLine("Var1 = Var1-3");
                newTextFile.AddLine("Var2 = Var2-3");
                newTextFile.AddLine("Var3 = Var3-3");
                newTextFile.AddLine("Var4 = Var4-3");
                newTextFile.AddLine("Var5 = Var5-3");
                newTextFile.AddLine("[Groupe 4]");
                newTextFile.AddLine("Var1 = Var1-4");
                newTextFile.AddLine("Var2 = Var2-4");
                newTextFile.AddLine("Var3 = Var3-4");
                newTextFile.AddLine("Var4 = Var4-4");
                newTextFile.AddLine("Var5 = Var5-4");
                newTextFile.AddLine("[Groupe 5]");
                newTextFile.AddLine("Var1 = Var1-5");
                newTextFile.AddLine("Var2 = Var2-5");
                newTextFile.AddLine("Var3 = Var3-5");
                newTextFile.AddLine("Var4 = Var4-5");
                newTextFile.AddLine("Var5 = Var5-5");

                testStructuredFile = new StructuredFile();
                testStructuredFile.Load(newTextFile);
                testStructuredFile.SetPatternFile("TestFiles/ExportPatternFile.pattern");

                if (testStructuredFile.Export("TestFiles/ExportPatternFile.output") == 6)
                {
                    Console.Write(" Ok\n");
                }
                else
                {
                    Console.Write(" Error !\n"); Validated = false;
                }

                // ------------------------------------------------------------------------------------------
                Console.Write(" -> Import d'un fichier :");
                testStructuredFile = new StructuredFile();
                testStructuredFile.SetPatternFile("TestFiles/ImportPatternFile.pattern");

                if ((testStructuredFile.Import("TestFiles/ImportFile.txt") > 0) && (testStructuredFile.SaveTo("TestFiles/ImportFile.sfile") > 0))
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
