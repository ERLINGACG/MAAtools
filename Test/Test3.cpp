#ifdef _WIN32                           //在windows下编译时
    #ifdef MAA_TEST_EXPORTS                    
        #define TEST_API __declspec(dllexport) //
    #else
        #define TEST_API __declspec(dllimport)
    #endif
#else
    #define TEST_API    // 非Windows下编译时
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
using json = nlohmann::json;
#ifdef _WIN32
#include <Windows.h>
#endif


MaaController* Auto_create_adb_controller(const int kIndex){
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

extern "C"{
    struct Test_3{
        MaaController* controller_handle;
        MaaCtrlId      ctrl_id;
        MaaResource*   resource_handle;
        MaaResId       res_id;
        MaaTasker*     tasker_handle;
        MaaTaskId      task_id;
    };

    TEST_API void Test3InitController(Test_3* test_3, const int kIndex){
        if(test_3->controller_handle!=nullptr && test_3->ctrl_id!=0){
            MaaControllerDestroy(test_3->controller_handle);
            test_3->controller_handle = nullptr;
            test_3->ctrl_id = 0;
        }
        test_3->controller_handle = Auto_create_adb_controller(kIndex);
        test_3->ctrl_id          =MaaControllerPostConnection(test_3->controller_handle);
        
    }

    TEST_API void Test3InitResource(Test_3* test_3, const char* resource_path){
            if(test_3->resource_handle!=nullptr && test_3->res_id!=0){
                MaaResourceDestroy(test_3->resource_handle);
                test_3->resource_handle = nullptr;
                test_3->res_id = 0;
            }
            test_3->resource_handle = MaaResourceCreate(nullptr, nullptr);
            test_3->res_id          = MaaResourcePostBundle(test_3->resource_handle, resource_path);
            if(test_3->res_id == MaaInvalidId){
                std::cout << "Resource post bundle failed" << std::endl;
            }else{
                std::cout << "Resource post bundle success" << std::endl;
            }   
    }

    TEST_API void Test3TaskerInit(Test_3* test_3){
            if(test_3->tasker_handle!=nullptr){ 
                MaaTaskerDestroy(test_3->tasker_handle);
                test_3->tasker_handle = nullptr;
               
            }
            test_3->tasker_handle = MaaTaskerCreate(nullptr, nullptr);
            if(test_3->tasker_handle != nullptr && 
               test_3->resource_handle!=nullptr && 
               test_3->controller_handle!=nullptr){

            MaaTaskerBindResource  (test_3->tasker_handle, test_3->resource_handle);  //绑定资源管理器
            MaaTaskerBindController(test_3->tasker_handle, test_3->controller_handle);//绑定控制器

            }
            if(!MaaTaskerInited(test_3->tasker_handle)){
                std::cout << "Tasker init failed" << std::endl;

            }
    }

    
    TEST_API void Test3Wait(Test_3* test_3){
        if(test_3->controller_handle!=nullptr && test_3->ctrl_id!=0 && test_3->resource_handle!=nullptr && test_3->res_id!=0){
            MaaControllerWait(test_3->controller_handle,test_3->ctrl_id); //等待控制器完成
            MaaResourceWait(test_3->resource_handle,test_3->res_id);     //等待资源完成
        }
    }
    TEST_API void Test3PostTask_T(Test_3* test_3){
        std::string task_json = R"( 
            {
                "MyTask": {
                    "recognition": "OCR",           
                    "expected": "电池",            
                    "action": "Click"
                }
            }
        )";
        test_3->task_id = MaaTaskerPostTask(test_3->tasker_handle, "MyTask", task_json.c_str()); 
        if(test_3->task_id == MaaInvalidId){
            std::cout << "Task post failed" << std::endl;
        }else{
            std::cout << "Task post success" << std::endl;
        }
        MaaTaskerWait(test_3->tasker_handle, test_3->task_id); //等待任务完成

    }


    
    TEST_API void Test3Destroy(Test_3* test_3){
        MaaControllerDestroy(test_3->controller_handle);
        MaaResourceDestroy(test_3->resource_handle);
        MaaTaskerDestroy(test_3->tasker_handle);

        test_3->resource_handle = nullptr;
        test_3->res_id = 0;
        test_3->controller_handle = nullptr;
        test_3->ctrl_id = 0;
        test_3->tasker_handle = nullptr;
        test_3->task_id = 0;
        
    }

}




