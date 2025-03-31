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




extern "C" {

    TEST_API void  MAA_API_Init()
    {       
         std::string user_path = "./";
         MaaToolkitConfigInitOption(user_path.c_str(), "{}");//初始化配置
         auto controller_handle = Auto_create_adb_controller(0);         //创建adb控制器
        auto tasker_handle     = MaaTaskerCreate(nullptr, nullptr);     //创建任务管理器
        auto resource_handle   = MaaResourceCreate(nullptr, nullptr);    //创建资源管理器



        auto ctrl_id = MaaControllerPostConnection(controller_handle); //连接设备，获取设备ID
        MaaControllerWait(controller_handle, ctrl_id);                 //等待设备连接成功  

        MaaTaskerBindResource(tasker_handle, resource_handle);  //绑定资源管理器
        MaaTaskerBindController(tasker_handle, controller_handle);//绑定控制器

        auto destroy = [&]() {      // 定义一个销毁函数
            MaaTaskerDestroy(tasker_handle);
            MaaResourceDestroy(resource_handle);
            MaaControllerDestroy(controller_handle);
        };
        
        std::string resource_dir = R"(./resource)";                                 //资源目录
        auto res_id = MaaResourcePostBundle(resource_handle, resource_dir.c_str()); //获取资源id
        
        if (res_id == MaaInvalidId) {
            std::cout << "no resource bundle" << std::endl;
            MaaControllerDestroy(controller_handle); //销毁控制器

        } else {
            std::cout << " Resource ID:" << res_id << std::endl;
        }
        MaaResourceWait(resource_handle, res_id); //等待资源加载完成

        if (!MaaTaskerInited(tasker_handle)) { //初始化任务
            std::cout << "Tasker init failed" << std::endl;
            destroy();
        }else{
            std::cout << "Tasker init success" << std::endl;
        }
        std::cout << "MAA_API_Init" << std::endl;
         std::string task_json = R"( 
            {
                "MyTask": {
                    "recognition": "OCR",           
                    "expected": "电池",            
                    "action": "Click"
                }
            }
        )";
        std::ifstream file("./resource/TestJson/task.json"); //读取json文件
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        //将文件流中读取的字符存储到str中
        json j = json::parse(str); //解析json文件
        auto task_id = MaaTaskerPostTask(tasker_handle, "MyTask", j.dump().c_str()); //提任务列表
        file.close();
        // auto task_id = MaaTaskerPostTask(tasker_handle, "MyTask", task_json.c_str()); 
         std::cout << "Start task " << std::endl;
            if (task_id == MaaInvalidId) {
                std::cout << "Failed to post task" << std::endl;
                destroy();
                
            } else {
                std::cout << "Task posted: " << task_id << std::endl;
            }
        destroy();
    };

    TEST_API int MAA_API_TEST_NUM(int a, int b){
        return a+b;
    };

    TEST_API char* MAA_API_TEST_STR(char* str){
        std::cout<<str<<std::endl;
        return str;
    };

    TEST_API std::string MAA_API_TEST_STRING(std::string str){
        // std::cout<<str<<std::endl;
        // std::cout<<"MAA_API_TEST_VOID"<<std::endl;
        return str;
    };
    TEST_API const void MAA_API_TEST_JSON(const char* json_path) {
        std::ifstream file(json_path);
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        nlohmann::json j = nlohmann::json::parse(str);
        for (auto& [key, value] : j.items()){
            std::cout << key << " : " << value << std::endl;
        }
        // 将JSON对象序列化为字符串
        
        // return result;
    };
    TEST_API void FreeJsonResult(char* ptr){
        delete[] ptr;
    };
}
