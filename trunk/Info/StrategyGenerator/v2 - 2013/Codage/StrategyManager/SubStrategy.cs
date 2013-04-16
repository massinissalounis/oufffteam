﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using StrategyGenerator2.FileManager;

namespace StrategyGenerator2.StrategyManager
{
    public class SubStrategy
    {
        // Public ---------------------------------------------------------------------------------
        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="subStrategyName">Nom de la nouvelle stratégie</param>
        public SubStrategy(String subStrategyName)
        {
            if (subStrategyName != null)
                _subStrategyName = subStrategyName;
        }

        /// <summary>
        /// Sauvegarde des informations de la substrategy dans le fichier spécifié en paramètre
        /// </summary>
        /// <param name="fileName">Nom du fichier pour la sauvegarde</param>
        /// <returns>Retourne le nombre d'action sauvegardée, -1 en cas d'erreur</returns>
        public int Save(String fileName)
        {
            int Ret = -1;
            int counter = 0;
            StructuredFile outputFile = null;
            StructuredFileGroup groupToAdd = null;

            if (fileName != null)
            {
                // Création du fichier pour la sauvegarde (fichier sans pattern)
                outputFile = new StructuredFile();

                // Création des objets globaux
                groupToAdd = new StructuredFileGroup(0);
                groupToAdd.AddKey(new StructuredFileKey("SubStrategyName", _subStrategyName));

                // Ajout des objets
                outputFile.AddGroup(groupToAdd);
                groupToAdd = null;

                // Création des objets relatifs aux RobotAction
                if (_actions != null)
                {
                    foreach (RobotAction currentRobotAction in _actions)
                    {
                        // Creation du groupe pour stocker les données
                        groupToAdd = currentRobotAction.Export();

                        // Ajout des données
                        outputFile.AddGroup(groupToAdd);
                        groupToAdd = null;

                        counter = counter + 1;
                    }
                }

                try
                {
                    outputFile.SaveTo(fileName);
                    Ret = counter;
                }
                catch (Exception ex)
                {
                    Ret = -1;
                }
                
            }

            return Ret;
        }

        /// <summary>
        /// Charge les informations de la substrategy à partir du fichier spécifié en paramètre
        /// Le chargement d'un fichier détruit toutes les données précédemment sauvegardée
        /// </summary>
        /// <param name="filename">Nom du fichier pour charger le fichier</param>
        /// <returns>Retourne le nombre d'action chargée, -1 en cas d'erreur</returns>
        public int Load(String filename)
        {
            int Ret = -1;
            StructuredFile inputFile = new StructuredFile();
            StructuredFileGroup globalGroup = null;
            List<StructuredFileGroup> actionsGroup = null;
            StructuredFileKey currentKey = null;
            RobotAction currentAction = null;

            if (filename != null)
            {
                // Ouverture du fichier
                inputFile.Load(filename);

                // Destruction des données actuelles
                _subStrategyName = "Not Set";
                _actions = null;

                // Chargement des données génériques
                globalGroup = inputFile.GetGroupByID(0);
                if (globalGroup != null)
                {
                    currentKey = globalGroup.GetFirstKey("SubStrategyName");
                    if (currentKey != null)
                        _subStrategyName = currentKey.valueString;
                }

                // Chargement des données liées aux actions
                actionsGroup = inputFile.GetAllGroup();
                if (actionsGroup != null)
                {
                    // Lecture de tous les groupes pour extraire les données liées aux actions
                    foreach (StructuredFileGroup currentGroup in actionsGroup)
                    {
                        // Nous ne devons extraire que les données des groupes > à 0
                        if (currentGroup.ID > 0)
                        {
                            currentAction = new RobotAction();
                            currentAction.Import(currentGroup);
                            
                            // On ajoute l'objet que l'on vient d'importer s'il est valide
                            if (currentAction.cmd != EnumCmd.NotSet)
                            {
                                if (_actions == null)
                                    _actions = new List<RobotAction>();

                                _actions.Add(currentAction);
                            }
                        }
                    }
                }


            }

            return Ret;
        }

        /// <summary>
        /// Vide tous les élements de la stratégie
        /// </summary>
        public void Clear()
        {
            _subStrategyName = "Not Set";
            _actions = null;
        }

        /// <summary>
        /// Retourne l'objet RobotAction ayant l'ID spécifié
        /// </summary>
        /// <param name="actionID">ID de l'objet recherché</param>
        /// <returns>Un objet RobotAction, null si l'objet n'est pas trouvé</returns>
        public RobotAction GetAction(int actionID)
        {
            RobotAction Ret = null;

            if (_actions != null)
            {
                foreach (RobotAction currentRobotAction in _actions)
                {
                    if (currentRobotAction.ID == actionID)
                        Ret = currentRobotAction;
                }
            }

            return Ret;
        }

        /// <summary>
        /// Retourne tous les objets de la sub-stratégie
        /// </summary>
        /// <returns>Tous les objets ou null</returns>
        public List<RobotAction> GetAllActions()
        {
            return _actions;
        }

        /// <summary>
        /// Ajoute un nouvel objet RobotAction dans la sub-stratégie
        /// Si l'ID est déjà utilisé, on met à jour les données avec l'objet en paramètre
        /// </summary>
        /// <param name="newAction">Nouvel objet à ajouter</param>
        /// <returns>True si l'ajout s'effectue correctement, False sinon</returns>
        public bool AddAction(RobotAction newAction)
        {
            bool Ret = false;
            
            if (newAction != null)
            {
                // On ajoute l'objet dans la liste
                if (_actions == null)
                {
                    _actions = new List<RobotAction>();
                    _actions.Add(newAction);
                }
                else
                {
                    // On verifie si l'ID n'est pas déjà utilisé
                    RobotAction isPresent = GetAction(newAction.ID);
                    if (isPresent != null)
                    {
                        // L'ID existe déjà, on le met à jour
                        isPresent.UpdateValue(newAction);
                    }
                    else
                    {
                        // L'objet n'existe pas, on peut l'ajouter
                        _actions.Add(newAction);
                    }
                }

                Ret = true;
            }

            return Ret;
        }

        /// <summary>
        /// Supprime l'objet ayant l'identifiant actionID
        /// </summary>
        /// <param name="actionID">ID de l'action a supprimer</param>
        /// <returns>True si l'objet avec l'ID spécifié n'est plus présent dans la strategie, False sinon</returns>
        public bool RemoveAction(int actionID)
        {
            bool Ret = false;
            List<RobotAction> newList = new List<RobotAction>();

            if (_actions != null)
            {
                // On parcourt la liste actuelle
                foreach (RobotAction currentRobotAction in _actions)
                {
                    // Si l'objet courant n'est pas l'objet recherché, on le copie dans l'objet newList
                    if (currentRobotAction.ID != actionID)
                        newList.Add(currentRobotAction);
                }

                // On permute la liste
                _actions = newList;
                Ret = true;
            }

            return Ret;
        }

        /// <summary>
        /// Permet de mettre à jour l'action ayant l'id actionID avec les données en paramètre
        /// L'ID n'est pas mis à jour
        /// </summary>
        /// <param name="actionID">ID de l'action à mettre à jour</param>
        /// <param name="newAction">Nouvelles données à mettre à jour</param>
        /// <returns>True si l'ajout a été fait correctement, False sinon</returns>
        public bool UpdateAction(int actionID, RobotAction newAction)
        {
            bool Ret = false;

            if ((newAction != null) && (_actions != null) && (actionID > 0))
            {
                // On verifie les ID
                // On met à jour les données que si on modifie l'objet courant ou si le nouvel ID n'est pas utilisé
                if ((newAction.ID == actionID) || (GetAction(newAction.ID) == null))
                {
                    // On parcourt tous les objets pour mettre à jour les actions ayant le bon ID
                    foreach (RobotAction currentRobotAction in _actions)
                    {
                        if (currentRobotAction.ID == actionID)
                        {
                            currentRobotAction.UpdateValue(newAction);
                            Ret = true;
                        }
                    }
                }
            }

            return Ret;
        }

        /// <summary>
        /// Retourne le nombre d'action dans la stratégie
        /// </summary>
        /// <returns>Nombre d'actions</returns>
        public int Count()
        {
            int Ret = 0;

            if (_actions != null)
                Ret = _actions.Count();

            return Ret;
        }

        public SubStrategy Clone()
        {
            SubStrategy newObject = new SubStrategy(_subStrategyName);
            if (_actions != null)
            {
                foreach (RobotAction currentRobotAction in _actions)
                {
                    newObject.AddAction(currentRobotAction);
                }
            }

            return newObject;
        }

        // Properties -----------------------------------------------------------------------------
        public String Name
        {
            get { return _subStrategyName;  }
            set { _subStrategyName = value; }
        }


          
        // Private functions ----------------------------------------------------------------------
        
        // Private --------------------------------------------------------------------------------
        String _subStrategyName = "Not Set";                    // Nom de la stratégie
        List<RobotAction> _actions = null;               // Regroupe toutes les actions de la strategy
    }

}
