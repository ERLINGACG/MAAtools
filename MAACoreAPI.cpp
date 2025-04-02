#include "MAACoreInclude/Core.h"
#include "MAACoreInclude/MAAEntity_Controller.h"
#include "MAACoreInclude/MAAEntity_Resource.h"
#include "MAACoreInclude/MAAEntity_Tasker.h"



extern "C" { //控制器API
    MAA_API IMAAEntity_Contorller* CreateController() {
        return new IMAAEntity_Contorller();
    }
    MAA_API void ReleaseController(IMAAEntity_Contorller* pController) {
        if (pController)
        delete pController;
    }

    MAA_API void SetControllerHandle(IMAAEntity_Contorller* pController,int index) {
        pController->SetControllerHandle(index);
    }
    MAA_API void SetCtrlId(IMAAEntity_Contorller* pController){
        pController->SetCtrlId();
    }
    MAA_API MaaController* GetControllerHandle(IMAAEntity_Contorller* pController) {
        return pController->controller_handle;
    }
    MAA_API int64_t GetCtrlId(IMAAEntity_Contorller* pController) {
        return pController->ctrl_id;
    }
    MAA_API int WaitConnect(IMAAEntity_Contorller* pController){
        return pController->WaitConnect();
    }
        
}

extern "C" { //资源API
    MAA_API IMAAEntity_Resource* CreateResource() {
        return new IMAAEntity_Resource();
    }
    MAA_API void ReleaseResource(IMAAEntity_Resource* pResource) {
        if (pResource)
        delete pResource;
    }
    MAA_API void SetResoursePath(IMAAEntity_Resource* pResource, const char* resource_path) {
        pResource->SetResoursePath(_strdup(resource_path));
       
        
    }
    MAA_API void SetResourceHandle(IMAAEntity_Resource* pResource) {
        pResource->SetResourceHandle();
    } 
    MAA_API int64_t SetResId(IMAAEntity_Resource* pResource){
        return pResource->SetResId();
    }

    MAA_API MaaResource* GetResourceHandle(IMAAEntity_Resource* pResource) {
        return pResource->GetResourceHandle();
    }
    MAA_API MaaResId GetResId(IMAAEntity_Resource* pResource) {
        return pResource->GetResId();
    }
    MAA_API int WaitResource(IMAAEntity_Resource* pResource) {
        return pResource->WaitsResource();
    }

}

extern "C" { //任务API
    MAA_API IMAAEntity_Tasker* CreateTasker() {
        return new IMAAEntity_Tasker();
    }
    MAA_API void ReleaseTasker(IMAAEntity_Tasker* pTasker) {
        if (pTasker)
        delete pTasker;
    }
    MAA_API void SetTaskerHandle(IMAAEntity_Tasker* pTasker, IMAAEntity_Contorller* controller,IMAAEntity_Resource* resource) 
    {
        pTasker->SetTaskerHandle(controller->GetControllerHandle(), 
                                resource->GetResourceHandle());
    }

    MAA_API MaaTasker* GetTaskerHandle(IMAAEntity_Tasker* pTasker) {
        return pTasker->GetTaskerHandle();
    }
    MAA_API int TaskerInit(IMAAEntity_Tasker* pTasker) {
        return pTasker->TaskerInit();
    }
    MAA_API void PostTask(IMAAEntity_Tasker* pTasker,const char* task_path) {
        char* temp = _strdup(task_path); 
        pTasker->PostTask(temp);
        free(temp);
    }
    MAA_API void GetTaskerDetial(IMAAEntity_Tasker* pTasker) {
        pTasker->GetTaskDetial();
    }
    MAA_API void PostTask2(IMAAEntity_Tasker* pTasker,const char* task_path) {
        pTasker->PostTaskTest(_strdup(task_path));

    }
    MAA_API void PostTaskOnce(IMAAEntity_Tasker* pTasker,const char* task_path){
        pTasker->PostTaskOnce(_strdup(task_path));
    }
    MAA_API void PostTaskOnceShowDetail(IMAAEntity_Tasker* pTasker,const char* task_path,int size){
        pTasker->PostTaskOnceShowDetail(_strdup(task_path),size);
    
    }
    MAA_API void Login(IMAAEntity_Tasker* pTasker){
        pTasker->Login();
    }

    // MAA_API int OCRClickTask(IMAAEntity_Tasker* pTasker,const char* str,){
    //     return pTasker->OCRClick(_strdup(str));
    // }
    
}

extern "C"{
    MAA_API void TestDoSomething(IMAAEntity_Tasker* pTasker){ //测试用
        int result = 0;
        while (true) {
           int result = pTasker->OCRClick("电池",2000);
           std::cout << "result:" << result << std::endl;
           std::cout << "not found the glabal try to continue" << std::endl;
           if(result == 3000){ //3000表示识别成功
               std::cout<<"found the glabal try to break"<<std::endl;
               break;
           }
        }
    }
    MAA_API void TestDoSomething2(IMAAEntity_Tasker* pTasker){ //测试用
        int result = 0;
        while(true){
            int result = pTasker->TemplateMatchClick("Arknights/gamestart/开始演算.png",20000);
            if(result == 3000){
                std::cout<<"found the glabal try to break"<<std::endl;
                break;
            }
        }
    }
}

// extern "C" { 
//     MAA_API IMAAEntity_Arknights* CreateArknights() {
//         return new IMAAEntity_Arknights();
//     }

//     MAA_API void ReleaseArknights(IMAAEntity_Arknights* pArknights) {
//         if (pArknights)
//         delete pArknights;
//     }

//     MAA_API void SetArknightsHandle(IMAAEntity_Arknights* pArknights, IMAAEntity_Contorller* controller,IMAAEntity_Resource* resource) {
//         pArknights->SetTaskerHandle(controller->GetControllerHandle(), resource->GetResourceHandle());
//     }

//     MAA_API void ArknightsInit(IMAAEntity_Arknights* pArknights) {
//         pArknights->TaskerInit();
//     }
//     MAA_API int ArknightsLogin(IMAAEntity_Arknights* pArknights,const char* json_path1,const char* json_path2){
//         return pArknights->Login(_strdup(json_path1),_strdup(json_path2));
//     }
// }

