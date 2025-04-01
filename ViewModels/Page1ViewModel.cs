// ViewModels/Page1ViewModel.cs
using System;
using System.Windows.Input;
using MAAtools.Utilities;
using MAAtools.MAA_DLL;
// using MAAtools.Utilities;
using MAAtools.API;
using MAAtools.Services;
using MAAtools.Models;
using System.Runtime.InteropServices;
using System.IO;
using MAAtools.Imp;
using Avalonia.Threading;
using System.Threading;
namespace MAAtools.ViewModels;

public class Page1ViewModel: ViewModelBase 
{
    private readonly Page1Model _model;

    Imp.Implementation implementation=new();
    
    public ICommand ClickCommand { get; }
    public ICommand Checked_All {get;}
    public ICommand Unchecked_All {get;}

    public ICommand StartGame {get;}
    // public string CPUUsage { get; }="test";
     
    public bool test1=false;
        private bool _isTask1Checked;
        private bool _isTask2Checked;
        private bool _isTask3Checked;
        private bool _isTask4Checked;
        private bool _isTask5Checked;
  
    public bool IsTask1Checked {
        get => _isTask1Checked;
        set {
                _isTask1Checked = value;
                OnPropertyChanged(); // 触发属性变更通知
                test1 = value;       // 如果需要同步到test1字段
        }
    }
    public bool IsTask2Checked {
        get => _isTask2Checked;
        set {
                _isTask2Checked = value;
                OnPropertyChanged(); // 触发属性变更通知
        }
    }
    public bool IsTask3Checked {
        get => _isTask3Checked;
        set {
                _isTask3Checked = value;
                OnPropertyChanged(); // 触发属性变更通知
        }
    }
    public bool IsTask4Checked {
        get => _isTask4Checked;
        set {
                _isTask4Checked = value;
                OnPropertyChanged(); // 触发属性变更通知
        }
    }
    public bool IsTask5Checked {
        get => _isTask5Checked;
        set {
                _isTask5Checked = value;
                OnPropertyChanged(); // 触发属性变更通知
        }
    }
    private bool _isBusy;
    public bool IsBusy
    {
        get => _isBusy;
        set => SetProperty(ref _isBusy, value); // 需要实现 INotifyPropertyChanged
    }
     private void ExecuteClick()
    {
        Console .WriteLine("Click");
        MAAtoolsAPI api = new();
        MAAtoolsAPI2 aPI2 = new();
        api.Start();
        aPI2.Start();
        if (test1){
            Console .WriteLine("Task1 is checked");
        }
        // Console .WriteLine(test1);
    }

    public string CPUUsage => _model.CPUUsage;
    public string MemoryUsage => _model.MemoryUsage;
    public Page1ViewModel()
    {   
        
        implementation.Init();
        ClickCommand = new RelayCommand(
            execute: ExecuteClick,
            canExecute: () => true // 明确返回true
        );
        Checked_All = new RelayCommand(
            execute: () => {
                IsTask1Checked = true;
                IsTask2Checked = true;
                IsTask3Checked = true;
                IsTask4Checked = true;
                IsTask5Checked = true;
            },
            canExecute: () => true
        );
        Unchecked_All = new RelayCommand(
            execute: () => {
                IsTask1Checked = false;
                IsTask2Checked = false;
                IsTask3Checked = false;
                IsTask4Checked = false;
                IsTask5Checked = false;
                
            },
            canExecute: () => true
        );
       
        StartGame = new RelayCommand(
            execute: () => {
                IsBusy = true;
                 Console.WriteLine(System.IO.Directory.GetCurrentDirectory());
                System.Threading.Tasks.Task.Run(() => {
            
                    if (IsTask1Checked) {
                        for(int i= 0;i<10;i++){
                        Console.WriteLine("Task1 is checked "+i);
                        implementation.StartGame();
                                           
                        implementation.talk();
                        implementation.Fitting();
                        implementation.NextDay();
                        Thread.Sleep(5000); 
                        implementation.DoNetwCycling();
                        implementation.DeleteGame();
                        }
                        // implementation.Test();
                    }
                    if (IsTask2Checked) {
                        implementation.Test();
                        // implementation.talk();
                    }
                    if (IsTask3Checked) {
                        // Console.WriteLine("Task3 is checked");
                        
                        implementation.Fitting();
                    }
                    if (IsTask4Checked) {
                        // Console.WriteLine("Task4 is checked");
                        implementation.NextDay();
                        Thread.Sleep(5000); 
                        implementation.DoNetwCycling();
                    }
                    if (IsTask5Checked) {
                        // Console.WriteLine("Task5 is checked");
                        
                        // Thread.Sleep(5000); 
                        implementation.DeleteGame();
                    }
                    
                }
                    
                    ) .ContinueWith(t => 
                {
            // 通过 Dispatcher 切回 UI 线程
                Dispatcher.UIThread.InvokeAsync(() => IsBusy = false);
                });
            },
            canExecute: () => !IsBusy
        );

        
        _model = new Page1Model();
        _model.PropertyChanged += (s, e) => 
        {
            if (e.PropertyName == nameof(_model.CPUUsage))
            {
                OnPropertyChanged(nameof(CPUUsage));
            }
            if (e.PropertyName == nameof(_model.MemoryUsage))
            {
                OnPropertyChanged(nameof(MemoryUsage));
            }
        };

    }
    public void Shutdown()
    {
        implementation.DeStroy();
    }

   
}