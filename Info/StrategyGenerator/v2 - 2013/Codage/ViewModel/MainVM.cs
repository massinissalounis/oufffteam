using GalaSoft.MvvmLight;
using StrategyGenerator2.Model;

namespace StrategyGenerator2.ViewModel
{
    public class MainVM : ViewModelBase
    {
        // Public ---------------------------------------------------------------------------------
        public MainVM()
        {
            _mainModel = MainModel.GetInstance;
        }

        // Properties -----------------------------------------------------------------------------
        
        // Private --------------------------------------------------------------------------------
        MainModel _mainModel = null;            
    }
}