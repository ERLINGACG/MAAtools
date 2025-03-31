#ifndef CORE_H
#define CORE_H

#ifdef _WIN32
#   ifdef MAA_API_EXPORT
#       define MAA_API __declspec(dllexport)
#   else
#       define MAA_API __declspec(dllimport) 
#   endif
#else
#   define MAA_API __attribute__((visibility("default")))
#endif


#ifdef _WIN32
    #include <Windows.h>
#endif

#include <array>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <nlohmann/json.hpp>    
#include "MaaFramework/MaaAPI.h"
#include "MaaToolkit/MaaToolkitAPI.h"

#include <cstdlib>
using json = nlohmann::json;

   

static MaaController* Auto_create_adb_controller(const int kIndex){
    auto list_handle = MaaToolkitAdbDeviceListCreate();
    MaaToolkitAdbDeviceFind(list_handle);
    auto device_handle = MaaToolkitAdbDeviceListAt(list_handle, kIndex);
    size_t size = MaaToolkitAdbDeviceListSize(list_handle);
    if (size == 0) {
        std::cout << "未找到ADB设备,请检查ADB是否安装或连接正确" << std::endl;
        std::cout << "按回车键退出...." << std::endl;
        std::cin.get();
        MaaToolkitAdbDeviceListDestroy(list_handle);
     
        return nullptr;
    }
    std::string agent_path = "share/MaaAgentBinary";
    auto controller_handle = MaaAdbControllerCreate(
        MaaToolkitAdbDeviceGetAdbPath(device_handle),           //获取adb
        MaaToolkitAdbDeviceGetAddress(device_handle),           //获取设备地址
        MaaToolkitAdbDeviceGetScreencapMethods(device_handle),  //获取截屏方式
        MaaToolkitAdbDeviceGetInputMethods(device_handle),      //获取输入方式
        MaaToolkitAdbDeviceGetConfig(device_handle),            //获取配置
        agent_path.c_str(),
    
        nullptr,
        nullptr);
    std::cout<< "Adb path:"<<MaaToolkitAdbDeviceGetAdbPath(device_handle)<<std::endl;
    std::cout<< "Adb address:"<<MaaToolkitAdbDeviceGetAddress(device_handle)<<std::endl;
    std::cout<< "Adb screencap methods:"<<MaaToolkitAdbDeviceGetScreencapMethods(device_handle)<<std::endl;
    std::cout<< "Adb input methods:"<<MaaToolkitAdbDeviceGetInputMethods(device_handle)<<std::endl;
    std::cout<< "Adb config:"<<MaaToolkitAdbDeviceGetConfig(device_handle)<<std::endl;
    MaaToolkitAdbDeviceListDestroy(list_handle);
    return controller_handle;

}
class MAA_API MAAEntity_C{
       
        public:
            virtual ~MAAEntity_C() = default;
            virtual void InitOption()=0;
            virtual void SetControllerHandle()=0;
            virtual void SetCtrlId()=0;
            virtual void SetResourceHandle()=0;
            virtual void SetResId()=0;
            virtual void WaitConnect()=0;
            virtual void WaitResource()=0;
            virtual void SetTaskerHandle()=0;
            virtual void Init()=0;
            // 
            // 
            // virtual void GetTaskDetial()=0;
            // virtual void GetTaskResult()=0;
            // virtual void PostTask()=0;
            virtual void Destroy()=0;
            

};

class MAA_API MAAEntity_Contorller{
        public:
            virtual ~MAAEntity_Contorller() = default;
            virtual void SetControllerHandle(int index)=0;
            virtual MaaController* GetControllerHandle()=0;
            virtual int WaitConnect()=0;
            virtual void SetCtrlId()=0;
            virtual MaaCtrlId GetCtrlId()=0;
            
};
class MAA_API MAAEntity_Resource{
        public:
            virtual ~MAAEntity_Resource() = default;
            virtual void         SetResoursePath(const char* path)=0;
            virtual void SetResourceHandle()=0;
            virtual int SetResId()=0;
            virtual MaaResId GetResId()=0;
            virtual MaaResource* GetResourceHandle()=0;
            virtual int WaitsResource()=0;
};
class MAA_API MAAEntity_Tasker{
        public:
            virtual ~MAAEntity_Tasker() = default;
            virtual void SetTaskerHandle(MaaController* controller_handle, MaaResource* resource_handle)=0;
            virtual MaaTasker* GetTaskerHandle()=0;
            virtual int TaskerInit()=0;
            virtual void PostTask(const char* task__path)=0;
            virtual void GetTaskDetial()=0;

};
class MAA_API MAAEntity_Init{
        public:
            virtual ~MAAEntity_Init() = default;
            virtual void InitOption()=0;
            virtual int Init( MaaTasker* tasker_handle)=0;
            
};





extern "C" {

    // struct MAAEntity_S
    // {
    //     MaaController* controller_handle;
    //     MaaCtrlId      ctrl_id;
    //     MaaResource*   resource_handle;
    //     MaaResId       res_id;
    //     MaaTasker*     tasker_handle;
    //     MaaTaskId      task_id;
    // };

   

    // MAA_API void MAAIntiController();
    // MAA_API void MAAInitResource();
    // MAA_API void MAAInitTask();
    // MAA_API void MAAGetTaskDetial();
    // MAA_API void MAAGetTaskResult();
    // MAA_API void MAAPostTask();
    // MAA_API void MAADestroy();
}

#endif // CORE_H