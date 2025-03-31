#ifndef IMAAENTITY_TASKER_H
#define IMAAENTITY_TASKER_H


#include "MAACoreInclude/Core.h"

class MAA_API IMAAEntity_Tasker: public MAAEntity_Tasker{
    public:
        MaaTasker* tasker_handle;
        MaaId task_id=0;
    public:
         void SetTaskerHandle(MaaController* controller_handle,MaaResource* resource_handle)        override;
        //  void PostTask(const char* Task_json) override;      
         MaaTasker* GetTaskerHandle()                                                               override;  
         int TaskerInit()                                                                           override;
         void PostTask(const char* Task_Path)                                                       override;
         void GetTaskDetial()                                                                       override;
         void PostTaskTest(const char* Task_Path);
         void PostTaskOnce(const char* Task_Path);
         void PostTaskOnceShowDetail(const char* Task_Path,int size);
         MaaTasker* GetTaskHandle();
         void  Login();
         int   OCRClick(const char* expected,int timeout);     //期望字符串
         int   TemplateMatchClick(const char* Ttemplate,int timeout); //模板匹配
         int   FeatureMatchClick(const  char* Ftemplate,int timeout);
         

};     

class IMAAEntity_Arknights: public IMAAEntity_Tasker{
    public:
        std::string        Json_path;
    public:
          void SetJsonPath(const char* jsonPath)            ;
        //   void SetTaskerHandle(MaaTasker* taskerHandle)     ;
          int  Login(const char* json_path1,const char* json_path2)                                      ;    
          void SatrtTask()                                  ;
          void StopTask()                                   ;
          int  StartGame();
          void Talker();
};




#endif // IMAAENTITY_TASKER_H