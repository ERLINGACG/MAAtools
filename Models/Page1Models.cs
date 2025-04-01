using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Timers;
using MAATools.Models;

namespace MAAtools.Models;

public class Page1Model : PageModelBase
{
    private string _cpuUsage = "0%";

    private string _memoryUsage = "0%";
    private readonly PerformanceCounter _cpuCounter;
    private readonly PerformanceCounter _memoryCounter;
    private readonly Timer _timer;

    #if NETFRAMEWORK || NET5_0_OR_GREATER
    [System.Runtime.Versioning.SupportedOSPlatform("windows")]
    public Page1Model()
    {
        // 初始化性能计数器（需要管理员权限）
        _cpuCounter = new PerformanceCounter("Processor Information", "% Processor Performance", "_Total");
         _cpuCounter.NextValue(); // 首次获取需要预热
        
        _memoryCounter = new PerformanceCounter("Memory", "Available MBytes");
        _memoryCounter.NextValue(); // 首次获取需要预热

        // 设置定时器（每1秒更新一次）
        _timer = new Timer(300);// 毫秒
        _timer.Elapsed += (s, e) => UpdateCpuUsage();
        _timer.Start();
    }
    #endif

    public string CPUUsage
    {
        get => _cpuUsage;
        set
        {
            _cpuUsage = value;
            OnPropertyChanged(nameof(CPUUsage));
        }
    }
    public string MemoryUsage
    {
        get => _memoryUsage;
        set
        {
            _memoryUsage = value;
            OnPropertyChanged(nameof(MemoryUsage));
        }
    }


    #if NETFRAMEWORK || NET5_0_OR_GREATER
    [System.Runtime.Versioning.SupportedOSPlatform("windows")]
    private void UpdateCpuUsage()
    {
        try
        {   int logicalCores = Environment.ProcessorCount;
            var value = (int)_cpuCounter.NextValue()/logicalCores;
            CPUUsage = $"{value}%";


            var availableMB = (int)_memoryCounter.NextValue();
            var availableMemory = (int)_memoryCounter.NextValue();
            MemoryUsage = $"{availableMemory}MB";

        }
        catch
        {
            CPUUsage = "N/A";
            MemoryUsage = "N/A";
        }
    }
    #endif

}
