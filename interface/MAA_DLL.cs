using System;
using System.Runtime.InteropServices;

namespace MAAtools.MAA_DLL;

class MAA_DLL_Controller{
     [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr CreateController();

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void ReleaseController(IntPtr pController);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetControllerHandle(IntPtr pController, int index);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetCtrlId(IntPtr pController);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr GetControllerHandle(IntPtr pController);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern long GetCtrlId(IntPtr pController);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int WaitConnect(IntPtr pController);
}


class MAA_DLL_Resouce{

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr CreateResource();

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void ReleaseResource(IntPtr pResource);

    // 资源路径设置（注意保留原拼写）
    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern void SetResoursePath(IntPtr pResource, string resource_path);

    // 资源句柄操作
    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetResourceHandle(IntPtr pResource);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern long SetResId(IntPtr pResource);

    // 资源信息获取
    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr GetResourceHandle(IntPtr pResource);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern long GetResId(IntPtr pResource);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int WaitResource(IntPtr pResource);
    

}

class MAA_DLL_Task{
    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr CreateTasker();
    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void ReleaseTasker(IntPtr pTasker);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr SetTaskerHandle(IntPtr pTasker, IntPtr pController_handle, IntPtr pResource_handle);


    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int TaskerInit(IntPtr pTasker);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void PostTask(IntPtr pTasker,string task_jons_path);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void PostTaskOnce(IntPtr pTasker,string task_jons_path);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void  PostTask2(IntPtr pTasker,string task_jons_path);


    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void GetTaskerDetial(IntPtr pTasker);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void PostTaskOnceShowDetail(IntPtr pTasker, string task_jons_path, int size);
     
    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void  Login(IntPtr pTasker);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern int OCRTask(IntPtr pTasker,string exception_str);
}
class MAA_DLL_Test{
    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void TestDoSomething(IntPtr pTasker);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void TestDoSomething2(IntPtr pTasker);
}
class MAA_DLL_Arknights{
    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr CreateArknights();
    
    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void ReleaseArknights(IntPtr pArknights);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetArknightsHandle(IntPtr pArknights, IntPtr pController, IntPtr pResource);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void ArknightsInit(IntPtr pArknights);

    [DllImport("lib/libMAACoreAPI.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void ArknightsLogin(IntPtr pArknights,string json_path1,string json_path2);


}