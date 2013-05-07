using System;
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
        /// <param name="subStrategyID">ID pour la nouvelle sous-stratégie</param>
        public SubStrategy(String subStrategyName, int subStrategyID)
        {
            if ((subStrategyName != null) && (subStrategyID >= 0))
            {
                _subStrategyName = subStrategyName;
                _subStrategyID = subStrategyID;

                // Création du premier objet
                _actions = new List<RobotAction>();
                _actions.Add(GetFirstRobotAction());
            }
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
                groupToAdd.AddKey(new StructuredFileKey("SubStrategyID", _subStrategyID));

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
        /// <param name="forcedID">ID à utiliser à la place de l'ID du fichier</param>
        /// <returns>Retourne le nombre d'action chargée, -1 en cas d'erreur</returns>
        public int Load(String filename, int forcedID)
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

                    if (forcedID > 0)
                    {
                        // Un ID a été imposé, nous l'utilisons
                        _subStrategyID = forcedID;
                    }
                    else
                    {
                        // Nous utilisons l'ID du fichier
                        currentKey = globalGroup.GetFirstKey("SubStrategyID");
                        if (currentKey != null)
                            _subStrategyID = currentKey.valueInt;
                    }
                }

                // Chargement des données liées aux actions
                actionsGroup = inputFile.GetAllGroup();
                if (actionsGroup != null)
                {
                    Ret = 0;
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
                                {
                                    _actions = new List<RobotAction>();
                                }
                                
                                // Verification des ID
                                currentAction.ID = CheckID(currentAction.ID);
                                currentAction.nextID = CheckLinkID(currentAction.nextID);
                                currentAction.timeoutID = CheckLinkID(currentAction.timeoutID);

                                _actions.Add(currentAction);
                                Ret = Ret + 1;
                            }
                        }
                    }
                }


            }

            SortRobotActions();

            return Ret;
        }

        public void SortRobotActions()
        {
            if (_actions != null)
                _actions.Sort(RobotAction.ComparisonID);
        }

        /// <summary>
        /// Vide tous les élements de la stratégie
        /// </summary>
        public void Clear()
        {
            _subStrategyName = "Not Set";
            _actions = new List<RobotAction>();
            _actions.Add(GetFirstRobotAction());
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
                // Verification des ID
                newAction.ID = CheckID(newAction.ID);
                newAction.nextID = CheckLinkID(newAction.nextID);
                newAction.timeoutID = CheckLinkID(newAction.timeoutID);

                // On ajoute l'objet dans la liste
                if (_actions == null)
                {
                    _actions = new List<RobotAction>();
                    _actions.Add(GetFirstRobotAction());
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

            SortRobotActions();

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

            if ((_actions != null) && (actionID >1) && (actionID != (_subStrategyID * 1000)))
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
                // Verification des ID
                newAction.ID = CheckID(newAction.ID);
                newAction.nextID = CheckLinkID(newAction.nextID);
                newAction.timeoutID = CheckLinkID(newAction.timeoutID);

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

        /// <summary>
        /// Permet de retourner une copie de l'objet courant
        /// </summary>
        /// <returns>Une copie de l'objet courant</returns>
        public SubStrategy Clone()
        {
            SubStrategy newObject = new SubStrategy(_subStrategyName, _subStrategyID);
            if (_actions != null)
            {
                foreach (RobotAction currentRobotAction in _actions)
                {
                    newObject.AddAction(currentRobotAction);
                }
            }

            return newObject;
        }

        /// <summary>
        /// Recherche une RobotAction à partir d'un ID dans la sous-stratégie courante
        /// </summary>
        /// <param name="IDtoFind">ID de la RobotAction à trouver</param>
        /// <returns>RobotAction recherchée ou null s'il n'est pas défini</returns>
        public RobotAction FindRobotActionByID(int IDtoFind)
        {
            RobotAction Ret = null;

            if (_actions != null)
            {
                foreach (RobotAction currentAction in _actions)
                {
                    if (currentAction.ID == IDtoFind)
                        Ret = currentAction;
                }
            }

            return Ret;
        }

        public void ChangeCmdID(int oldValue, int newValue)
        {
            if (_actions != null)
            {
                foreach (RobotAction currentAction in _actions)
                {
                    if ((currentAction.ID == oldValue) && (currentAction.ID % 1000 != 0))
                        currentAction.ID = newValue;

                    if (currentAction.nextID == oldValue)
                        currentAction.nextID = newValue;

                    if (currentAction.timeoutID == oldValue)
                        currentAction.timeoutID = newValue;
                }
            }
        }

        public int GetFreeID()
        {
            int Ret = _subStrategyID * 1000;
            Boolean isValid = false;

            if (_actions != null)
            {
                while (isValid == false)
                {
                    Ret = Ret + 1;

                    isValid = true;
                    foreach (RobotAction currentRobotAction in _actions)
                    {
                        if (currentRobotAction.ID == Ret)
                            isValid = false;
                    }

                    if (Ret > _subStrategyID * 1000 + 999)
                    {
                        Ret = -1;
                        isValid = true;
                    }

                }
            }

            return Ret;
        }


        // Properties -----------------------------------------------------------------------------
        public String Name
        {
            get { return _subStrategyName;  }
            set { _subStrategyName = value; }
        }

        public String ID
        {
            get
            {
                int Ret = _subStrategyID * 1000;

                return Ret.ToString();
            }

            internal set { }
        }
          
        // Private functions ----------------------------------------------------------------------
        private RobotAction GetFirstRobotAction()
        {
            RobotAction Ret = null;

            if(_subStrategyID == 0)
                Ret = new RobotAction(1);
            else
                Ret = new RobotAction(_subStrategyID * 1000);

            Ret.cmd = EnumCmd.App_Wait;
            Ret.cmdType = EnumCmdType.CmdType_Blocking;
            Ret.param1 = "0";
            Ret.param2 = "0";
            Ret.param3 = "0";
            Ret.param4 = "1";
            Ret.nextID = 0;

            return Ret;
        }

        private int CheckID(int currentValue)
        {
            int Ret = 0;

            // Il faut verifier l'ID
            if ((currentValue >= _subStrategyID * 1000) && (currentValue < (_subStrategyID + 1) * 1000))
            {
                // Si nous sommes dans la gamme actuelle, l'ID reste inchangé
                Ret = currentValue;
            }
            else
            {
                // Nous devons mettre à jour l'ID
                Ret = currentValue % 1000;

                Ret = Ret + _subStrategyID * 1000;
            }

            return Ret;
        }

        private int CheckLinkID(int currentValue)
        {
            int Ret = 0;

            // Si nous faisons appelle à la stratégie principale, on ne change pas l'ID
            if ((currentValue < 1000) || (_subStrategyID == 0))
            {
                Ret = currentValue;
            }
            else
            {
                Ret = CheckID(currentValue);
            }

            return Ret;
        }

        public static int ComparisonID(SubStrategy firstSubStrategy, SubStrategy secondSubStrategy)
        {
            if (firstSubStrategy != null)
            {
                if (secondSubStrategy != null)
                {
                    if (firstSubStrategy.Name == "MainStrategy")
                    {
                        return -1;
                    }
                    else if (secondSubStrategy.Name == "MainStrategy")
                    {
                        return -1;
                    }
                    else
                        return firstSubStrategy.ToString().CompareTo(secondSubStrategy.ToString());
                }
                else
                    return 1;
            }
            else
            {
                if (secondSubStrategy != null)
                    return -1;
                else
                    return 0;
            }
        }


        // Private --------------------------------------------------------------------------------
        String _subStrategyName = "Not Set";            // Nom de la stratégie
        List<RobotAction> _actions = null;              // Regroupe toutes les actions de la strategy
        int _subStrategyID = 1;                         // 
    }

}
