using System;
using MAAtools.MAA_DLL;
using MAA_TEST;
using System.Threading;
using System.Text;

namespace MAAtools.Imp;

public class Implementation{
    
    TController controller = new TController();
    TReasource reasource = new TReasource();
    Taks tasker = new Taks();
    public void Init(){
        reasource.SetResoursePath("./lib/resource/");
        reasource.SetReasourceHandle();
        reasource.SetResId();
        reasource.WaitsResource();
        controller.SetControllerHandle();
        controller.SetCtrlId();
        controller.WaitConnect();
        tasker.SetTaskerHandle(controller.ReturnSelf(), reasource.ReturnSelf());
        tasker.TaskerInit();
    }
    public void Test(){
        
         Test t = new Test();
        //  t.Test1(tasker.ReturnSelf());
        t.Test2(tasker.ReturnSelf());
    }
    
    public void DeStroy(){
        controller.Dispose();
        reasource.Dispose();
        tasker.Dispose();
    }
    public void StartGame(){
        tasker.PostTaskOnce("./lib/resource/pipeline/start.json");
        tasker.PostTaskOnce("./lib/resource/pipeline/pass2.json");
    }
    public void talk(){
        tasker.PostTaskOnce("./lib/resource/pipeline/talk.json");
        tasker.PostTaskOnce("./lib/resource/pipeline/exit.json");
       
    }
    public void Fitting(){
         Thread.Sleep(10000); //暂停6秒
        tasker.PostTaskOnce("./lib/resource/pipeline/move.json");
       
        tasker.PostTaskOnce("./lib/resource/pipeline/start_action.json");
        tasker.PostTaskOnce("./lib/resource/pipeline/start_action2.json");
    }
    public void NextDay(){
        // Thread.Sleep(10000);
        // tasker.PostTaskOnce("./lib/resource/pipeline/nextday1.json");
        // Thread.Sleep(10000);
        // tasker.PostTaskOnce("./lib/resource/pipeline/nextday2.json");
        tasker.PostTaskOnce("./lib/resource/pipeline/NextDayZ1.json");
        Console.WriteLine("NextDayZ1 is over");
        Thread.Sleep(10000);
        tasker.PostTaskOnce("./lib/resource/pipeline/NextDayZ2.json");
        tasker.PostTaskOnce("./lib/resource/pipeline/NextDayZ1.json");
        Console.WriteLine("NextDayZ2 is over");
         Thread.Sleep(10000);
         tasker.PostTaskOnce("./lib/resource/pipeline/NextDayZ3.json");
         tasker.PostTaskOnce("./lib/resource/pipeline/NextDayZ1.json");
         Console.WriteLine("NextDayZ3 is over");

    }
    public void DeleteGame(){
        tasker.PostTaskOnce("./lib/resource/pipeline/deleteGame.json");
    }
    public void DoNetwCycling(){
        tasker.PostTaskOnce("./lib/resource/pipeline/new_cycle1.json");
        Thread.Sleep(5000); //暂停6秒
        tasker.PostTaskOnce("./lib/resource/pipeline/new_cycle2.json");
    }
}