using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using StrategyGenerator2.StrategyManager;

namespace StrategyGenerator2.StrategyViewer
{
    public class StrategyDisplay
    {
        public StrategyDisplay()
        {
            _displayPos = null;
        }

        public void ComputeRobotPos(Strategy currentStrategy)
        {
            DisplayPos currentDisplayPos = null;
            List<DisplayPos> nextList = new List<DisplayPos>();
            RobotPos currentRobotPos = new RobotPos();
            List<RobotAction> allRobotActions = null;

            if (currentStrategy != null)
            {
                // On commence par détruire les anciens éléments
                _displayPos = null;
                _displayPos = new List<DisplayPos>();

                // Creation de la liste 
                allRobotActions = currentStrategy.GetAllRobotAction();
                foreach (RobotAction currentRobotAction in allRobotActions)
                {
                    currentDisplayPos = new DisplayPos(currentRobotAction);
                    _displayPos.Add(currentDisplayPos);
                }

                // Creation de l'objet initial
                currentRobotPos.x = currentStrategy.DefaultPosX;
                currentRobotPos.y = currentStrategy.DefaultPosY;
                currentRobotPos.angle = currentStrategy.DefaultPosA;
                currentRobotPos.statusFlag = EnumStatusFlag.RobotIsClosed;

                // Creation du premier élément
                nextList.Clear();
                currentDisplayPos = GetDisplayPosByID(1);
                if (currentDisplayPos != null)
                {
                    currentDisplayPos.AddInitialPos(currentRobotPos);
                    nextList.Add(currentDisplayPos);
                }

                // On ajoute tous les élements de la stratégie principale
                foreach (DisplayPos current in _displayPos)
                {
                    if ((current.actionID >= 1) && (current.actionID < 100))
                        nextList.Add(current);
                }

                while (nextList.Count() > 0)
                {
                    // Etape 1 : On transfert les données de la liste nextIDs vers currentIDs
                    List<DisplayPos> currentList = new List<DisplayPos>(nextList);
                    DisplayPos currentItem = null;
                    nextList.Clear();
                    
                    // Etape 2 : Pour chaque élément de la liste
                    while (currentList.Count() > 0)
                    {
                        // On récupère le premier élément de la liste et on le supprimer de la liste courante
                        currentItem = currentList[0];
                        currentList.RemoveAt(0);

                        // Etape 2.1 : On calcule la position de sortie
                        List<RobotPos> outputPos = currentItem.GetOutputPos();

                        if ((outputPos != null) && (outputPos.Count() > 0))
                        {
                            // On ajoute les données que si on ne boucle pas sur nous même et qu'on a un ID valide
                            if((currentItem.nextID != currentItem.actionID) && (currentItem.nextID > 0))
                            {
                                // On ajoute que si on est dans la stratégie principale
                                if (((currentItem.actionID > 0) && (currentItem.actionID <100)) || ((currentItem.actionID >=100) && (currentItem.nextID > 100)))
                                {
                                    currentDisplayPos = GetDisplayPosByID(currentItem.nextID);
                                    if (currentDisplayPos != null)
                                    {
                                        Boolean addNewItemToList = true;

                                        currentDisplayPos.AddInitialPos(outputPos);
                                        foreach(DisplayPos current in nextList)
                                        {
                                            if (current.actionID == currentDisplayPos.actionID)
                                                addNewItemToList = false;
                                        }

                                        foreach (DisplayPos current in currentList)
                                        {
                                            if (current.actionID == currentDisplayPos.actionID)
                                                addNewItemToList = false;
                                        }

                                        if(addNewItemToList == true)
                                            nextList.Add(currentDisplayPos);
                                    }
                                }
                            }
                        }
                    }

                    currentList.Clear();
                    currentList = null;
                }
            }
        }

        public DisplayPos GetDisplayPosByID(int IDtoFind)
        {
            DisplayPos Ret = null;

            if ((IDtoFind > 0) && (_displayPos != null))
            {
                foreach (DisplayPos current in _displayPos)
                {
                    if (current.actionID == IDtoFind)
                        Ret = current;
                }
            }

            return Ret;
        }

        // Private --------------------------------------------------------------------------------
        private List<DisplayPos> _displayPos;
    }
}
