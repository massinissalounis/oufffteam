using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.IO;

namespace StrategyGenerator2.StrategyManager
{
    /// <summary>
    /// Logique d'interaction pour StrategyLoader.xaml
    /// </summary>
    public partial class StrategyLoader : Window
    {
        public StrategyLoader()
        {
            InitializeComponent();
            PopulateStrategies();
        }

        public void Load()
        {
            Load(null);
        }

        public void Load(String defaultName)
        {
            try
            {
                if (defaultName != null)
                    textBoxStrategyName.Text = defaultName;

                buttonValidate.Content = "Charger";
                this.ShowDialog();
            }
            catch (Exception)
            {
            }
        }

        public void Save()
        {
            Save(null);
        }

        public void Save(String defaultName)
        {
            try
            {
                if (defaultName != null)
                    textBoxStrategyName.Text = defaultName;

                buttonValidate.Content = "Sauvegarder";
                this.ShowDialog();
            }
            catch (Exception)
            {
            }
        }

        public String SelectedStrategyName
        {
            get { return _selectedStrategyName; }
            internal set { }
        }

        // Private ------------------------------------------------------------------------------------
        private String _selectedStrategyName = "";

        private void PopulateStrategies()
        {
            String loadDirectory = Directory.GetCurrentDirectory() + "\\Data\\";

            if (Directory.Exists(loadDirectory) == true)
            {
                // Lecture des dossiers présents dans le répertoire Data
                foreach (String subDir in Directory.GetDirectories(loadDirectory))
                {
                    listStrategies.Items.Add(subDir.Replace(loadDirectory, ""));
                }
            }
            else
            {
                SetErrorMsg("Erreur : Le répertoire 'Data' n'a pas été trouvé.");
            }
        }

        private void SetErrorMsg(String errorMsg)
        {
            Boolean newStatus = false;

            if (errorMsg == null)    // Il n'y a pas de message d'erreur
                newStatus = true;

            // Desactive/active les éléments de la fenêtre
            listStrategies.IsEnabled = newStatus;
            textBoxStrategyName.IsEnabled = newStatus;
            buttonValidate.IsEnabled = newStatus;

            if (errorMsg != null)
            {
                textBoxError.Text = errorMsg;
                textBoxError.Visibility = System.Windows.Visibility.Visible;
            }
        }

        private void listStrategies_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(listStrategies.SelectedItem != null)
                textBoxStrategyName.Text = listStrategies.SelectedItem.ToString();
        }

        private void buttonValidate_Click(object sender, RoutedEventArgs e)
        {
            if (buttonValidate.Content.ToString() == "Charger") 
            {
                // Nous sommes en train de charger le fichier
                foreach (String currentName in listStrategies.Items)
                {
                    // On verifie si le dossier existe
                    if (currentName.ToString().ToUpper() == textBoxStrategyName.Text.ToString().ToUpper())
                        _selectedStrategyName = currentName;
                }

                // Femeture de la fenêtre si l'objet a été selectionné
                if (_selectedStrategyName != "")
                    this.Close();
                else
                    MessageBox.Show("Impossible de trouver la stratégie selectionnée.", "Strategy Loader", MessageBoxButton.OK, MessageBoxImage.Warning);

            }
            else
            {
                Boolean isStrategyAlreadyExist = false;

                // Nous sommes en train d'écrire le fichier
                foreach (String currentName in listStrategies.Items)
                {
                    // On verifie si le dossier n'existe pas déjà
                    if (currentName.ToString().ToUpper() == textBoxStrategyName.Text.ToString().ToUpper())
                    {
                        isStrategyAlreadyExist = true;
                    }
                }

                if (isStrategyAlreadyExist == true)
                {
                    // Le dossier existe, on affiche un message d'alerte
                    if (MessageBox.Show("La stratégie selectionnée existe déjà.\nVoulez vous la remplacer ?", "Strategy Loader", MessageBoxButton.YesNo, MessageBoxImage.Question) != MessageBoxResult.Yes)
                    {
                        // Sinon on ne fait rien
                        return;
                    }
                }

                _selectedStrategyName = textBoxStrategyName.Text.ToString();

                // Femeture de la fenêtre si l'objet a été selectionné
                if (_selectedStrategyName != "")
                    this.Close();
                else
                    MessageBox.Show("Nom de stratégie non valide.", "Strategy Loader", MessageBoxButton.OK, MessageBoxImage.Warning);

            }
        }

        private void listStrategies_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            listStrategies.SelectedIndex = -1;
        }

        private void listStrategies_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            buttonValidate_Click(sender, e);
        }
    }

}
