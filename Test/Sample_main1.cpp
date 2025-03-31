#include <array>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#ifdef _WIN32
#include <Windows.h>
#endif

#include "MaaFramework/MaaAPI.h"
#include "MaaToolkit/MaaToolkitAPI.h"
#include "nlohmann/json.hpp"
//  命令行编译参数
//  g++ -fdiagnostics-color=always -g main.cpp -I E:\\Python_poj\\MaaPy\\MaaPracticeBoilerplate\\deps\\include\\ -L E:\\Python_poj\\MaaPy\\MaaPracticeBoilerplate\\deps\\lib\\ -lMaaFramework -lMaaToolkit -o main.exe

struct OCR_Result {
    std::string text;
    double score;
};

struct TextScorePair {
    std::string text;
    double score;
};

using json = nlohmann::json;




MaaController* create_adb_controller();
MaaBool my_reco(
    MaaContext* context,
    MaaTaskId task_id,
    const char* node_name,
    const char* custom_recognition_name,
    const char* custom_recognition_param,
    const MaaImageBuffer* image,
    const MaaRect* roi,
    void* trans_arg,
    /* out */ MaaRect* out_box,
    /* out */ MaaStringBuffer* out_detail);


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



int main(int argc, char** argv)
{
    std::cout << "Hello, MaaFramework!" << std::endl;
    
       #ifdef _WIN32
       SetConsoleOutputCP(CP_UTF8); // 条件编译,设置控制台输出为UTF-8
       #endif
    std::string user_path = ".";
    MaaToolkitConfigInitOption(user_path.c_str(), "{}");//初始化配置

    auto controller_handle = create_adb_controller(); //创建adb控制器
    if (!controller_handle) {
        std::cout << "Failed to create controller" << std::endl;
        std::cout << "Program finished. Press Enter to exit..." << std::endl;
        std::cin.get();
        return -1;
    } else {
        std::cout << "Controller created: " << controller_handle << std::endl;
    }

    auto ctrl_id = MaaControllerPostConnection(controller_handle); //连接设备，获取设备ID
    MaaControllerWait(controller_handle, ctrl_id); //等待设备连接成功     

    auto resource_handle = MaaResourceCreate(nullptr, nullptr); //创建资源管理器
    std::string resource_dir = R"(./resource)";                 //资源目录
    auto res_id = MaaResourcePostBundle(resource_handle, resource_dir.c_str()); //获取资源id
    if (res_id == MaaInvalidId) {
        std::cout << "Failed to post resource" << std::endl;
        std::cout << "Program finished. Press Enter to exit..." << std::endl;
        std::cin.get();
        MaaControllerDestroy(controller_handle); //销毁控制器
        return -1;
    } else {
        std::cout << "Resource posted: " << res_id << std::endl;
    }
    MaaResourceWait(resource_handle, res_id); //等待资源加载完成

    auto tasker_handle = MaaTaskerCreate(nullptr, nullptr); //创建任务管理器
    MaaTaskerBindResource(tasker_handle, resource_handle);  //绑定资源管理器
    MaaTaskerBindController(tasker_handle, controller_handle);//绑定控制器

    auto destroy = [&]() {      // 定义一个销毁函数
        MaaTaskerDestroy(tasker_handle);
        MaaResourceDestroy(resource_handle);
        MaaControllerDestroy(controller_handle);
    };

    if (!MaaTaskerInited(tasker_handle)) { //初始化任务
        std::cout << "Failed to init MAA" << std::endl;
        std::cout << "Program finished. Press Enter to exit..." << std::endl;
        std::cin.get();
        destroy();
        return -1;
    }

    // MaaResourceRegisterCustomRecognition(resource_handle, "MyReco", my_reco, nullptr); //注册回调函数

    // 创建一个简单的点击任务
    // 这个任务会在屏幕中匹配一个模板，并在找到匹配项时点击
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
    // MaaRecoId reco_id =  MaaTaskerPostTask(tasker_handle, "MyTask", task_json.c_str());
    std::cout << "已开始任务" << std::endl;
    if (task_id == MaaInvalidId) {
        std::cout << "Failed to post task" << std::endl;
        destroy();
        return -1;
    } else {
        std::cout << "Task posted: " << task_id << std::endl;
    }
    MaaTaskerWait(tasker_handle, task_id);
    auto detail_buffer = MaaStringBufferCreate(); 
    auto detail_img_buffer = MaaImageBufferCreate();   //

    // my_reco(nullptr, task_id, "MyTask", "MyReco", nullptr, detail_img_buffer,nullptr,nullptr,nullptr,nullptr);

     std::vector<MaaNodeId> node_id_list = get_task_detail(tasker_handle, task_id);
    
    // 
    
    // MaaTaskerGetTaskDetail(tasker_handle, task_id, detail_buffer);
    auto node_name_buffer1   =     MaaStringBufferCreate();
    auto node_name_buffer2   =     MaaStringBufferCreate();
    auto algorithm_buffer    =     MaaStringBufferCreate();
    auto  detail_json_buffer =     MaaStringBufferCreate();
    auto  raw_img_buffer     =     MaaImageBufferCreate();
    auto  roi_buffer         =     MaaImageListBufferCreate();
    MaaBool is_hit1;
    MaaBool is_hit2;
    MaaRect box;
    MaaRecoId reco_id;
    // MaaTaskerGetRecognitionDetail(tasker_handle ,reco_id,node_name_buffer,algorithm_buffer,&is_hit,&box,detail_json_buffer,raw_img_buffer,roi_buffer);
    // std::cout << "is_hit:" << is_hit << std::endl;
    // std::cout << "box:" << box.x << "," << box.y << "," << box.width << "," << box.height << std::endl;
    // std::cout << "detail_json:" << MaaStringBufferGet(detail_json_buffer) << std::endl;
    // std::cout << "roi_buffer:" << MaaImageListBufferSize(roi_buffer) << std::endl;
    // std::cout << "reco_id:" << reco_id << std::endl;
    MaaTaskerGetNodeDetail(tasker_handle, node_id_list[0],node_name_buffer1,&reco_id,&is_hit1);
    // std::cout << reco_id <<std::endl;
    MaaTaskerGetRecognitionDetail(tasker_handle ,reco_id,node_name_buffer2,algorithm_buffer,&is_hit2,&box,detail_json_buffer,raw_img_buffer,roi_buffer);
    std::cout << "is_hit:" << is_hit2 << std::endl;
    std::cout << "box:" << box.x << "," << box.y << "," << box.width << "," << box.height << std::endl;
    std::cout << MaaStringBufferGet(node_name_buffer1)<<std::endl;
    std::cout << MaaStringBufferGet(node_name_buffer2)<<std::endl;
    // std::cout << "detail_json:" << MaaStringBufferGet(detail_json_buffer) << std::endl;
    std::cout << "roi_buffer:" << MaaImageListBufferSize(roi_buffer) << std::endl;
    std::cout << "reco_id:" << reco_id << std::endl;
    // MaaStringBufferDestroy(node_name_buffer);
    // MaaStringBufferDestroy(detail_buffer);
    std::string delete_json =MaaStringBufferGet(detail_json_buffer);
    std::cout << "delete_json:" << delete_json << std::endl;

    auto json_data = json::parse(delete_json);

     for (const auto& item : json_data["all"]) {
        std::string text = item["text"];
        double score = item["score"];
        std::cout << "文本: " << text << ", 分数: " << score << std::endl;
        if(text=="接管作战"){
            std::cout << "命中目标" << std::endl;
        }
    }
    std::cout << "Task finished" << std::endl;
    destroy();

    std::cout << "Program finished. Press Enter to exit..." << std::endl;
    std::cin.get();
    return 0;
}

MaaController* create_adb_controller()
{
    auto list_handle = MaaToolkitAdbDeviceListCreate();
    auto destroy = [&]() {
        MaaToolkitAdbDeviceListDestroy(list_handle);
    };

    MaaToolkitAdbDeviceFind(list_handle);

    size_t size = MaaToolkitAdbDeviceListSize(list_handle);
    if (size == 0) {
        std::cout << "No device found" << std::endl;

        destroy();
        return nullptr;
    }

    const int kIndex = 0; // for demo, we just use the first device 
    auto device_handle = MaaToolkitAdbDeviceListAt(list_handle, kIndex);

    std::string agent_path = "share/MaaAgentBinary";

    auto controller_handle = MaaAdbControllerCreate(
        MaaToolkitAdbDeviceGetAdbPath(device_handle), //获取adb
        MaaToolkitAdbDeviceGetAddress(device_handle), //获取设备地址
        MaaToolkitAdbDeviceGetScreencapMethods(device_handle),//获取截屏方式
        MaaToolkitAdbDeviceGetInputMethods(device_handle),   //获取输入方式
        MaaToolkitAdbDeviceGetConfig(device_handle),        //获取配置

        // std::cout << "ADB Path: " << MaaToolkitAdbDeviceGetAdbPath(device_handle) << std::endl;
        agent_path.c_str(),
    
        nullptr,
        nullptr);
    std::cout<< "Adb path:"<<MaaToolkitAdbDeviceGetAdbPath(device_handle)<<std::endl;
    std::cout<< "Adb address:"<<MaaToolkitAdbDeviceGetAddress(device_handle)<<std::endl;
    std::cout<< "Adb screencap methods:"<<MaaToolkitAdbDeviceGetScreencapMethods(device_handle)<<std::endl;
    std::cout<< "Adb input methods:"<<MaaToolkitAdbDeviceGetInputMethods(device_handle)<<std::endl;
    std::cout<< "Adb config:"<<MaaToolkitAdbDeviceGetConfig(device_handle)<<std::endl;
    std::cout << "Controller created address: " << device_handle << std::endl;

    destroy();

    return controller_handle;
}

// 自定义识别回调函数
MaaBool my_reco(
    MaaContext* context,
    MaaTaskId task_id,
    const char* node_name,
    const char* custom_recognition_name,
    const char* custom_recognition_param,
    const MaaImageBuffer* image,
    const MaaRect* roi,
    void* trans_arg,
    /* out */ MaaRect* out_box,
    /* out */ MaaStringBuffer* out_detail)
{
    // 这里您可以实现自己的识别逻辑
    // 这里简单地返回一个固定的矩形区域作为识别结果
    std::array<int, 4> my_box = { 100, 200, 200, 300 }; // 假设识别到的区域在(100, 200)到(200, 300)
    MaaRectSet(out_box, my_box[0], my_box[1], my_box[2], my_box[3]);

    // 输出识别细节
    MaaStringBufferSet(
        out_detail,
        R"({"result": "success", "box": [100, 200, 200, 300]})");

    // 如果任务被命中，返回true以执行操作
    return true;
}
