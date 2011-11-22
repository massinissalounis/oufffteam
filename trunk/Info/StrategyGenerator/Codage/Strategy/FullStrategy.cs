using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StrategyGenerator.Strategy
{
    /// <summary>
    /// List of Command that define a full strategy
    /// </summary>
    class FullStrategy
    {
        // Constructor ----------------------------------------------------------------------------
        /// <summary>
        /// Default constructor : Create an empty strategy
        /// </summary>
        FullStrategy()
        {
            _Strategy = null;
        }

        // Private --------------------------------------------------------------------------------
        private List<Command> _Strategy;
    }
}
