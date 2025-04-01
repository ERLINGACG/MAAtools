using System;
using System.Windows.Input;
using CommunityToolkit.Mvvm.Input;

namespace MAAtools.ViewModels;

public partial class MainWindowViewModel : ViewModelBase
{
    public string Greeting { get; } = "Welcome to Avalonia!";
   
    
    public ICommand ShowPage1 { get; }
    // public double CPU_data { get; } = 0.0;
    public MainWindowViewModel(){

        ShowPage1 = new RelayCommand(
            execute: ExecuteClick1,
            canExecute: () => true // 明确返回true
        );
        
    
    }

    private void ExecuteClick1()
    {
        // throw new NotImplementedException();
    }
}
