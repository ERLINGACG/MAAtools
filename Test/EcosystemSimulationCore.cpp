
//此为生息演算模式的核心代码
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

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;
using json = nlohmann::json;

void GetEnterExit(){
    std::cout << "按回车键退出...." << std::endl;
    std::cin.get();
    exit(0);
}
class Resource_Json{
    private:
        std::string Resource_path;
    public:
        void Set_path(std::string path){
            Resource_path = path;
        }

        std::string Get_path(){
            return Resource_path;
        }

        std::string Read_Json(string filename){
            try{
                std::ifstream file(Resource_path + filename);
                std::cout<<Resource_path + filename<<std::endl;
                std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                json j = json::parse(str);
                file.close();
                return j.dump();
            }
            catch(const std::exception& e){

                std::cerr << "Error: " << e.what() << std::endl;
                return "Not read file";
            }

        }


        json Get_Json_file(string filename){
            try{
                std::ifstream file(Resource_path + filename);
                std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                json j = json::parse(str);
                return j;
            }
            catch(const std::exception& e){
                std::cerr << "Error: " << e.what() << std::endl;
                return json();
            }
        }

        std::vector<std::pair<std::string, json>> Get_Json_detail(json jsonfile) {
            std::vector<std::pair<std::string, json>> result; // 创建一个vector来存储键值对
            try{
                for (auto& [key, value] : jsonfile.items()) {
                    // cout << "任务名称: " << key << endl;
                    // cout << "任务内容: " << value << endl;

                    result.push_back({key, value}); // 将键值对添加到vector中
                }

                return result; // 返回包含键值对的vector
            }
            catch(const std::exception& e){
                std::cerr << "Error: " << e.what() << std::endl;
                return result;
                }
        }

};


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
std::vector<MaaNodeId>  get_task_detail(MaaTasker* tasker_handle, MaaTaskId task_id) {
    auto detail_buffer = MaaStringBufferCreate();
    MaaSize node_id_list_size = 10; // 假设最多有10个节点
    std::vector<MaaNodeId> node_id_list(node_id_list_size);
    MaaStatus status;

    if (MaaTaskerGetTaskDetail(
         tasker_handle, //任务句柄
         task_id,       //任务ID
         detail_buffer, //任务详情字符串
         node_id_list.data(), //节点ID列表
         &node_id_list_size, //节点ID列表大小
         &status            //任务状态
         )
         
         ) {
        // 获取任务详情字符串
        const char* detail = MaaStringBufferGet(detail_buffer);
        std::cout << "Task detail: " << detail << std::endl;

        // 输出节点 ID 列表
        std::cout << "Node ID list: ";
        for (MaaSize i = 0; i < node_id_list_size; ++i) {
            std::cout << node_id_list[i] << " ";
        }
        std::cout << std::endl;

        // 输出任务状态
        std::cout << "Task status: " << status << std::endl;
    } else {
        std::cout << "Failed to get task detail" << std::endl;
    }

    MaaStringBufferDestroy(detail_buffer);
    return node_id_list;
}


int Run(){
    Resource_Json resource_json;
    resource_json.Set_path("./resource/TestJson/");
    std::string user_path = "./";
    MaaToolkitConfigInitOption(user_path.c_str(), "{}");//初始化配置

    try{
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
            std::cout << "未找到资源,请检查资源路径是否正确" << std::endl;
            MaaControllerDestroy(controller_handle); //销毁控制器
            GetEnterExit();
            return -1;
        } else {
            std::cout << "资源ID:" << res_id << std::endl;
        }
        MaaResourceWait(resource_handle, res_id); //等待资源加载完成

        if (!MaaTaskerInited(tasker_handle)) { //初始化任务
            std::cout << "任务管理器未初始化,请检查配置是否正确" << std::endl;
            GetEnterExit();
            destroy();
            return -1;
        
        }else{
            std::cout << "任务管理器初始化成功" << std::endl;
        }
        
        std::string task = resource_json.Read_Json("task.json");
        std::vector<std::pair<std::string, json>> result = resource_json.Get_Json_detail(json::parse(task));
        for (auto& [key, value] : result) {
            auto task_id = MaaTaskerPostTask(tasker_handle, key.c_str(), task.c_str());
            std::cout << "正在开始任务,当前任务:"<< key << std::endl;
            if (task_id == MaaInvalidId) {
                std::cout << "开始任务失败" << std::endl;
                destroy();
                return -1;
            } else {
                std::cout << "任务ID:" << task_id << std::endl;
            }
            MaaTaskerWait(tasker_handle, task_id);
        }
        std::cout << "所有任务完成" << std::endl;
        
        destroy();

        GetEnterExit();
    }catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        GetEnterExit();
        return 1;
    }
    return 0;
}

void Debug_Json(){
    Resource_Json resource_json;
    resource_json.Set_path("./resource/TestJson/");
    std::string json_str = resource_json.Read_Json("task.json");
    std::cout << "Json的内容:"<<json_str << std::endl;
    json json_data = resource_json.Get_Json_file("task.json");
    std::vector<std::pair<std::string, json>> result = resource_json.Get_Json_detail(json_data);
    
}

int main(){
   
    // resource_json.Get_Json_detail(resource_json.Get_Json_file("task.json"));
    #ifdef _WIN32
     SetConsoleOutputCP(CP_UTF8); // 条件编译,设置控制台输出为UTF-8
     SetConsoleCP(CP_UTF8); // 设置控制台输入为UTF-8
    #endif
    // Debug_Json();
    Run();
    return 0;
}