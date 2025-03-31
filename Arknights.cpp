#include "MAACoreInclude/MAAEntity_Tasker.h"

void IMAAEntity_Arknights::SetJsonPath(const char*  json_path){
    this->Json_path = json_path;
}
// void IMAAEntity_Arknights::SetTaskerHandle(MaaTasker* tasker_handle){
//     this->Tasker_handle = tasker_handle;
// }
int IMAAEntity_Arknights::Login(const char* json_path1, const char* json_path2){
    #ifdef _WIN32
       SetConsoleOutputCP(CP_UTF8); // 条件编译,设置控制台输出为UTF-8
    #endif
    
    MaaStringBuffer* detail_buffer = MaaStringBufferCreate();
    MaaSize node_id_list_size=10;
    std::vector<MaaNodeId> node_id_list(node_id_list_size);
    MaaStatus status;

    std::ifstream file(json_path1);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    json task_json1 = json::parse(str); //解析json文件
    file.close();
     this->task_id = MaaTaskerPostTask(this->tasker_handle,
        task_json1.items().begin().key().c_str(), //任务名
        task_json1.dump().c_str()
      );
     MaaTaskerWait(this->tasker_handle, this->task_id); //等待任务完成
     MaaTaskerGetTaskDetail(
             this->tasker_handle,
             this->task_id,
             detail_buffer,
             node_id_list.data(),
             &node_id_list_size,
             &status
    );
    if(status==3000){
        std::cout << "任务执行成功" << std::endl;
        return 0;
    }else{
        std::cout << "任务执行失败" << std::endl;
        std::cout<<"执行另一个任务"<<std::endl;
        std::ifstream file(json_path2);
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        json task_json2 = json::parse(str); //解析json文件
        file.close();
        this->task_id = MaaTaskerPostTask(this->tasker_handle,
            task_json2.items().begin().key().c_str(), //任务名
            task_json2.dump().c_str()
        );
        MaaTaskerWait(this->tasker_handle, task_id); //等待任务完成
        MaaTaskerGetTaskDetail(
             this->tasker_handle,
             this->task_id,
             detail_buffer,
             node_id_list.data(),
             &node_id_list_size,
             &status
    );
        if(status==3000){
            std::cout << "任务执行成功" << std::endl;
            return 0;
        }else{
            std::cout << "任务执行失败" << std::endl;
            return 1;
        }
    }
    
}
void IMAAEntity_Arknights::SatrtTask(){}
void IMAAEntity_Arknights::StopTask(){}
