namespace MAA_TEST;

using System;
using System.ComponentModel.Design.Serialization;
using System.Threading;
using MAAtools.MAA_DLL;
class MAA_Test{
    TController controller = new TController();
        TReasource reasource = new TReasource();
        Taks tasker = new Taks();
        Arknights arknights = new Arknights();
    public void Test(){
        Console.WriteLine("MAA_TEST");
        
        reasource.SetResoursePath("./lib/resource/");
        reasource.SetReasourceHandle();
        reasource.SetResId();
        reasource.WaitsResource();
        controller.SetControllerHandle();
        controller.SetCtrlId();
        controller.WaitConnect();
        // arknights.SetArknightsHandle(controller.ReturnSelf(), reasource.ReturnSelf());
        // arknights.ArknightsInit();
        //arknights.ArknightsLogin("./lib/resource/pipeline/my_task1.json","./lib/resource/pipeline/my_task2.json");
        tasker.SetTaskerHandle(controller.ReturnSelf(), reasource.ReturnSelf());
        tasker.TaskerInit();
        // tasker.Login(); 
        // tasker.PostTask("./lib/resource/pipeline/my_task.json");
        // tasker.PostTask2("./lib/resource/pipeline/my_task.json");
            // tasker.PostTaskOnceShowDetail("./lib/resource/pipeline/test_task.json", 10);
        // tasker.PostTaskOnce("./lib/resource/pipeline/start.json");
        // tasker.PostTaskOnce("./lib/resource/pipeline/pass2.json");
        // tasker.PostTaskOnce("./lib/resource/pipeline/talk.json");
        // tasker.PostTaskOnce("./lib/resource/pipeline/exit.json");
        // Console.WriteLine("MAA_TEST Delay 10s");
        // Thread.Sleep(10000);
        // tasker.PostTaskOnce("./lib/resource/pipeline/test_task.json");
        // tasker.PostTaskOnce("./lib/resource/pipeline/start_action.json");
        // tasker.PostTaskOnce("./lib/resource/pipeline/start_action2.json");
        // tasker.PostTaskOnceShowDetail("./lib/resource/pipeline/TESTJSON2.json",10);
        // Thread.Sleep(10000);
        // tasker.PostTaskOnce("./lib/resource/pipeline/start_action3.json");
        tasker.Dispose();
        arknights.Dispose();
        reasource.Dispose();
        controller.Dispose();

    }
}
class TController:IDisposable{
    public IntPtr _controllerPtr;

    public TController(){
        _controllerPtr =  MAA_DLL_Controller.CreateController();
    }
    public void SetControllerHandle(){
        MAA_DLL_Controller.SetControllerHandle(_controllerPtr,0);
    }
    public void SetCtrlId(){
        MAA_DLL_Controller.SetCtrlId(_controllerPtr);
    }
    public IntPtr GetControllerHandle(){
        return MAA_DLL_Controller.GetControllerHandle(_controllerPtr);
    }
    public int WaitConnect(){
        return MAA_DLL_Controller.WaitConnect(_controllerPtr);
    }

    public IntPtr ReturnSelf(){
        return _controllerPtr;
    }
    public void Dispose()
    {
        // throw new NotImplementedException();
        MAA_DLL_Controller.ReleaseController(_controllerPtr);
    }
}
class TReasource : IDisposable
{   
    public IntPtr _reasourcePtr;
    public TReasource(){
        _reasourcePtr = MAA_DLL_Resouce.CreateResource();
    }
    public void SetResoursePath(string resource_path){
        MAA_DLL_Resouce.SetResoursePath(_reasourcePtr, resource_path);
    }
    public void SetReasourceHandle(){
        MAA_DLL_Resouce.SetResourceHandle(_reasourcePtr);
    }
    public long GetResId(){
        Console.WriteLine("GetResId:"+MAA_DLL_Resouce.GetResId(_reasourcePtr));
        return MAA_DLL_Resouce.GetResId(_reasourcePtr);
    }
    public IntPtr GetResourceHandle(){
        Console.WriteLine("GetResourceHandle:"+MAA_DLL_Resouce.GetResourceHandle(_reasourcePtr));
        return MAA_DLL_Resouce.GetResourceHandle(_reasourcePtr);
    }
    public long SetResId(){
        Console.WriteLine("SetResId:"+MAA_DLL_Resouce.SetResId(_reasourcePtr));
        return MAA_DLL_Resouce.SetResId(_reasourcePtr);
    }
    public int WaitsResource(){
        return MAA_DLL_Resouce.WaitResource(_reasourcePtr);
    }
    public IntPtr ReturnSelf(){
        return _reasourcePtr;
    }
    public void Dispose()

    {
        MAA_DLL_Resouce.ReleaseResource(_reasourcePtr);
        // throw new NotImplementedException();
    }
}
class Taks : IDisposable

{
    public IntPtr _taskerPtr;
    public Taks(){
        _taskerPtr = MAA_DLL_Task.CreateTasker();
    }
    public void SetTaskerHandle(IntPtr pController_handle, IntPtr pResource_handle){
        MAA_DLL_Task.SetTaskerHandle(_taskerPtr, pController_handle, pResource_handle);
    }
    public void TaskerInit(){
        MAA_DLL_Task.TaskerInit(_taskerPtr);
    }
    public void PostTask(string task_jons_path){
        MAA_DLL_Task.PostTask(_taskerPtr, task_jons_path);
    }
    public void PostTaskOnce(string task_jons_path)
    {
        MAA_DLL_Task.PostTaskOnce(_taskerPtr, task_jons_path);
    }
    public void PostTask2(string task_jons_path){
        MAA_DLL_Task.PostTask2(_taskerPtr, task_jons_path);
    }
    public void GetTaskerDetial(){
        MAA_DLL_Task.GetTaskerDetial(_taskerPtr);
    }
    public void PostTaskOnceShowDetail(string task_jons_path, int size){
        MAA_DLL_Task.PostTaskOnceShowDetail(_taskerPtr, task_jons_path, size);
    }
    public void Login(){
        MAA_DLL_Task.Login(_taskerPtr);
    }
    public IntPtr ReturnSelf(){
        return _taskerPtr;
    }
    public int OCRTask(string exception_str){
        return MAA_DLL_Task.OCRTask(_taskerPtr, exception_str);
    }
    public void Dispose()
    {
        // throw new NotImplementedException();
        MAA_DLL_Task.ReleaseTasker(_taskerPtr);
    }
}
class Test{
     
     public void Test1(IntPtr pTasker){
        MAA_DLL_Test.TestDoSomething(pTasker);
     }
     public void Test2(IntPtr pTasker){
        MAA_DLL_Test.TestDoSomething2(pTasker);
     }
}


class Arknights : IDisposable

{   
    private IntPtr _arknightsPtr;
    public Arknights(){
        _arknightsPtr = MAA_DLL_Arknights.CreateArknights();
    }
    public void SetArknightsHandle(IntPtr pController, IntPtr pResource){
        MAA_DLL_Arknights.SetArknightsHandle(_arknightsPtr, pController, pResource);
    }
    public void ArknightsInit(){
        MAA_DLL_Arknights.ArknightsInit(_arknightsPtr);
    }
    public void ArknightsLogin(string json_path1,string json_path2){
        MAA_DLL_Arknights.ArknightsLogin(_arknightsPtr, json_path1, json_path2);
    }
    public IntPtr ReturnSelf(){
        return _arknightsPtr;
    }
    public void Dispose()
    {
        MAA_DLL_Arknights.ReleaseArknights(_arknightsPtr);
    }
}