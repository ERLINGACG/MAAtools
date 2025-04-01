// Utilities/RelayCommand.cs
using System;
using System.Windows.Input;
namespace MAAtools.Utilities;
public class RelayCommand : ICommand
{
    private readonly Action _execute;          // 参数类型改为 Action，存储命令的执行方法
    private readonly Func<bool>? _canExecute;  // 参数类型改为 Func<bool>? 判断命令是否可以执行的函数

    // 参数类型添加可空标记
    public RelayCommand(Action execute, Func<bool>? canExecute = null) // 参数类型改为 Action 和 Func<bool>?
    {   //注册命令的执行方法和判断是否可以执行的函数
        _execute = execute ?? throw new ArgumentNullException(nameof(execute));
        _canExecute = canExecute;
        //第一个参数必须提供方方法，否者抛出ArgumentNullException异常
        //第二个参数可空，可以不提供，表示命令可以执行任意条件
    }

    // 参数类型改为 object?
    public bool CanExecute(object? parameter) => _canExecute?.Invoke() ?? true;


    // 参数类型改为 object?
    public void Execute(object? parameter) => _execute();

    // 事件声明为可空类型
    public event EventHandler? CanExecuteChanged;

    // 添加外部触发方法
    public void RaiseCanExecuteChanged()
    {
        CanExecuteChanged?.Invoke(this, EventArgs.Empty);
    }
}