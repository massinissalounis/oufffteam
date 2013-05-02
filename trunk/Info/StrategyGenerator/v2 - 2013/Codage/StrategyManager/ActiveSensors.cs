using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator2.StrategyManager
{
    public class ActiveSensors
    {
        public ActiveSensors()
        {
            int sensorsCount = Enum.GetNames(typeof(EnumCollisionSensors)).Length;
            int counter = 0;

            _activeSensors = new Sensors[sensorsCount];

            foreach (EnumCollisionSensors currentValue in Enum.GetValues(typeof(EnumCollisionSensors)))
            {
                _activeSensors[counter] = new Sensors(currentValue);
                counter++;
            }
        }

        /// <summary>
        /// Desactive tous les sensors
        /// </summary>
        public void DesactivateAllSensors()
        {
            if (_activeSensors != null)
            {
                foreach (Sensors currentValue in _activeSensors)
                {
                    currentValue.isActivated = false;
                }
            }
        }

        /// <summary>
        /// Active tous les sensors passés en paramètre. Les paramètres non spécifiés restent inchangés
        /// </summary>
        /// <param name="sensorsToActivate">Nom du(des) sensor(s) à activer (utilisation du nom long)</param>
        public void ActivateSensors(String sensorsToActivate)
        {
            if ((_activeSensors != null) && (sensorsToActivate != null))
            {
                foreach (Sensors current in _activeSensors)
                {
                    if (sensorsToActivate.Contains(current.fullName) == true)
                    {
                        current.isActivated = true;
                    }
                }
            }
        }

        /// <summary>
        /// Active les paramètres passés en paramètres. Tous les autres sensors non passés en paramètres sont remis à 0.
        /// </summary>
        /// <param name="sensorsToActivate">Nom du(des) sensor(s) à activer (utilisation du nom long)</param>
        public void ForceSensors(String sensorsToActivate)
        {
            DesactivateAllSensors();
            ActivateSensors(sensorsToActivate);
        }

        /// <summary>
        /// Desactive tous les sensors passés en paramètre
        /// </summary>
        /// <param name="sensorsToActivate">Nom du(des) sensor(s) à activer (utilisation du nom long)</param>
        public void DesactivateSensors(String sensorsToActivate)
        {
            if ((_activeSensors != null) && (sensorsToActivate != null))
            {
                foreach (Sensors currentValue in _activeSensors)
                {
                    if (sensorsToActivate.Contains(currentValue.fullName) == true)
                    {
                        currentValue.isActivated = false;
                    }
                }
            }
        }

        /// <summary>
        /// Retourne la chaine de caractère (complète) listant tous les sensors activés
        /// </summary>
        public String Activated
        {
            get
            {
                String Ret = "(APP_PARAM_STRATEGYFLAG_" + EnumAppParamStrategyFlags.NONE.ToString() + ")";

                if (_activeSensors != null)
                {
                    // Creation de l'entete
                    Ret = "(";

                    // Creation des flags
                    foreach (Sensors currentValue in _activeSensors)
                    {
                        if(currentValue.isActivated == true)
                            Ret = Ret + " + " + currentValue.fullName;
                    }

                    // Creation de la fin de chaine
                    Ret = Ret + ")";

                    // Verification des cas particuliers
                    Ret = Ret.Replace("( + ", "(");     // Debut de chaine

                    if(Ret == "()")
                        Ret = Ret = "(APP_PARAM_STRATEGYFLAG_" + EnumAppParamStrategyFlags.NONE.ToString() + ")";
                }

                return Ret;
            }
            set
            {
            }
        }

        public List<Sensors> GetAllSensors
        {
            get
            {
                List<Sensors> Ret = null;

                if(_activeSensors != null)
                {
                    Ret = new List<Sensors>();
                    for (int i = 0; i < _activeSensors.Length; i++)
                    {
                        Ret.Add(_activeSensors[i]);
                    }
                }
                return Ret;
            }

            set { }
        }


        // Private --------------------------------------------------------------------------------
        private Sensors [] _activeSensors = null;
    }
}
