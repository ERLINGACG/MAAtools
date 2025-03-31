#include "MAACoreInclude/MAAEntity_Tasker.h"
//  MaaTasker* SetTaskerHandle()
// MaaTaskId  SetTaskId() 
// void PostTask(const char* Task_json)

void IMAAEntity_Tasker::SetTaskerHandle(MaaController* controller_handle,MaaResource* resource_handle){
    this->tasker_handle =  MaaTaskerCreate(nullptr, nullptr);
    MaaTaskerBindController(tasker_handle,controller_handle);  //绑定资源管理器
    MaaTaskerBindResource(tasker_handle,resource_handle);  //绑定实体
}

MaaTasker* IMAAEntity_Tasker::GetTaskerHandle(){
    return this->tasker_handle;
}
int IMAAEntity_Tasker:: TaskerInit(){
    try{
        MaaTaskerInited(tasker_handle);
        return 0;
    }catch(...){    
        return -1;
    }
}

void IMAAEntity_Tasker::PostTask(const char* Task_json_path){ //连续执行任务
    std::cout << "PostTask" << std::endl;
    std::ifstream file(Task_json_path);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    json j = json::parse(str); //解析json文件
    file.close();
    for(auto& item : j.items()){
        this->task_id =MaaTaskerPostTask(
            this->tasker_handle,
            item.key().c_str(),
            j.dump().c_str()
        );
        MaaTaskerWait(this->tasker_handle,this->task_id);
    }
    
}
void IMAAEntity_Tasker::GetTaskDetial(){
    std::cout << "GetTaskDetial" << std::endl;
    MaaStringBuffer* detail_buffer = MaaStringBufferCreate();
    MaaSize node_id_list_size;
    
    std::vector<MaaNodeId> node_id_list(node_id_list_size);
    MaaStatus status;
         MaaTaskerGetTaskDetail(
             this->tasker_handle,
             this->task_id,
             detail_buffer,
             node_id_list.data(),
             &node_id_list_size,
             &status
         );
         const char* detail = MaaStringBufferGet(detail_buffer);
         std::cout << detail << std::endl;
         for(MaaSize i=0;i<node_id_list_size;i++){
            std::cout << "node_id_list[" << i << "]=" << node_id_list[i] << std::endl;
            std::cout << "Task status: " << status << std::endl;
         }

          MaaStringBufferDestroy(detail_buffer);
    
}
void IMAAEntity_Tasker::PostTaskTest(const char* Task_json_path){

    MaaStringBuffer* detail_buffer = MaaStringBufferCreate();
    MaaSize node_id_list_size=10;
    std::vector<MaaNodeId> node_id_list(node_id_list_size);
    MaaStatus status;
    MaaRecoId reco_id;
    MaaBool completed;

    std::cout << "PostTask2" << std::endl;
    std::ifstream file(Task_json_path);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    json j = json::parse(str); //解析json文件
    file.close();
    for(auto& item : j.items()){
        this->task_id =MaaTaskerPostTask(
            this->tasker_handle,
            item.key().c_str(),
            j.dump().c_str()   
        );
         
        MaaTaskerWait(this->tasker_handle,this->task_id);
        MaaTaskerGetTaskDetail(
             this->tasker_handle,
             this->task_id,
             detail_buffer,
             node_id_list.data(),
             &node_id_list_size,
             &status
         );
         const char* detail = MaaStringBufferGet(detail_buffer);
         std::cout << detail << std::endl;
         for(MaaSize i=0;i<node_id_list_size;i++){
            std::cout << "node_id_list[" << i << "]=" << node_id_list[i] << std::endl;
            std::cout << "Task status: " << status << std::endl;
            MaaTaskerGetNodeDetail(
                 this->tasker_handle,
                 node_id_list[i],
                 detail_buffer,
                 &reco_id,
                 &completed
            );
            const char* node_name = MaaStringBufferGet(detail_buffer);
            std::cout << "node_name: " << node_name << std::endl;
            std::cout << "reco_id: " << reco_id << std::endl;
            std::cout << "completed: " << (completed ? "true" : "false") << std::endl;
            MaaStringBufferDestroy(detail_buffer);
         }
    }
    
}

void IMAAEntity_Tasker::PostTaskOnce(const char* Task_json_path){  //单次执行任务
    std::ifstream file(Task_json_path);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    json j = json::parse(str); //解析json文件
    file.close();
    this->task_id =MaaTaskerPostTask(
        this->tasker_handle,
        j.items().begin().key().c_str(),  //取第一个任务名
        j.dump().c_str()                   //将json文件内容作为参数
    );
    MaaTaskerWait(this->tasker_handle,this->task_id);
}


void IMAAEntity_Tasker::PostTaskOnceShowDetail(const char* Task_json_path,int size){
    #ifdef _WIN32
       SetConsoleOutputCP(CP_UTF8); // 条件编译,设置控制台输出为UTF-8
    #endif

    MaaStringBuffer* detail_buffer = MaaStringBufferCreate();    //创建字符串缓冲区
    MaaSize node_id_list_size=size;                              //节点id列表大小
    std::vector<MaaNodeId> node_id_list(node_id_list_size);     //节点id列表
    MaaStatus status;                                           //任务状态
    MaaRecoId reco_id;                                          //节点reco_id
    MaaBool completed;                                          //节点是否完成
    MaaStringBuffer* _node_name=  MaaStringBufferCreate();        //节点名称
    MaaStringBuffer* algorithm=  MaaStringBufferCreate();                                 //算法名称
    MaaRect box;                                                                            //box
    MaaStringBuffer* detail_json=MaaStringBufferCreate();                               //详情json
    std::ifstream file(Task_json_path);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    json j = json::parse(str); //解析json文件
    file.close();

    this->task_id =MaaTaskerPostTask(
        this->tasker_handle,
        j.items().begin().key().c_str(),  //取第一个任务名
        j.dump().c_str()                   //将json文件内容作为参数
    );

    MaaTaskerWait(this->tasker_handle,this->task_id);
    MaaTaskerGetTaskDetail(
             this->tasker_handle,     //任务句柄
             this->task_id,           //任务id
             detail_buffer,           //任务详情
             node_id_list.data(),     //节点id列表
             &node_id_list_size,      //节点id列表大小
             &status                  //任务状态
    );
    const char* detail = MaaStringBufferGet(detail_buffer);
    std::cout << detail << std::endl;
    for(MaaSize i=0;i<node_id_list_size;i++){
        MaaTaskerGetNodeDetail(
             this->tasker_handle,     //任务句柄
             node_id_list[i],         //节点id
             detail_buffer,           //节点详情
             &reco_id,                //节点reco_id
             &completed               //节点是否完成
        );
        const char* node_name = MaaStringBufferGet(detail_buffer);
        std::cout << "node_name: " << node_name << std::endl;
        std::cout << "reco_id: " << reco_id << std::endl;
        std::cout << "completed: " << (completed ? "true" : "false") << std::endl;
        MaaTaskerGetRecognitionDetail(
             this->tasker_handle,     //任务句柄
             reco_id,                 //节点reco_id
             detail_buffer,           //节点详情
             algorithm,           //算法详情
             &completed,              //是否命中
             &box,                    //box
             detail_json,            //详情json
             nullptr,                 //raw
             nullptr                  //draws
        );
        const char* algorithm_name = MaaStringBufferGet(algorithm);
        std::cout << "algorithm_name: " << algorithm_name << std::endl;
        const char* detail_json_str = MaaStringBufferGet(detail_json);
        std::cout << "detail_json_str: " << detail_json_str << std::endl;
        std::cout << "box: " << box.x << " " << box.y << " " << box.width << " " << box.height << std::endl;
        MaaStringBufferDestroy(_node_name);
        MaaStringBufferDestroy(detail_json);
        MaaStringBufferDestroy(detail_buffer);
        MaaStringBufferDestroy(algorithm);
        MaaStringBufferDestroy(detail_buffer);
    }
}

MaaTasker* IMAAEntity_Tasker::GetTaskHandle(){
    return this->tasker_handle;
}


void IMAAEntity_Tasker::Login(){
     #ifdef _WIN32
       SetConsoleOutputCP(CP_UTF8); // 条件编译,设置控制台输出为UTF-8
    #endif
    std::string task_json = R"( 
        {
            "MyTask": {
                "recognition": "OCR",           
                "expected": "电池",            
                "action": "Click"
            }
        }
    )";
    std::string task_json2 = R"(
        {
            "MyTask": {
                        "recognition": "OCR",           
                        "expected": "设置",            
                        "action": "Click"
                    }
            }

    )";
     this->task_id = MaaTaskerPostTask(this->tasker_handle,
        "MyTask", //任务名
        task_json.c_str()
      );
    MaaTaskerWait(this->tasker_handle, task_id); //等待任务完成

    MaaStringBuffer* detail_buffer = MaaStringBufferCreate();
    MaaSize node_id_list_size=10;
    std::vector<MaaNodeId> node_id_list(node_id_list_size);
    MaaStatus status;
     
     MaaTaskerGetTaskDetail(
             this->tasker_handle,
             this->task_id,
             detail_buffer,
             node_id_list.data(),
             &node_id_list_size,
             &status
    );

    std::cout <<"status: "<< status <<std::endl;
    if(status == 3000){
        std::cout << "任务执行成功" << std::endl;
    }else{
        std::cout << "任务执行失败" << std::endl;
        std::cout<<"执行另一个任务"<<std::endl;
        this->task_id = MaaTaskerPostTask(this->tasker_handle,
        "MyTask", //任务名
        task_json2.c_str()
      );
        MaaTaskerWait(this->tasker_handle, task_id); //等待任务完成
    }
}


int IMAAEntity_Tasker::OCRClick(const char* expected_str){

    
     #ifdef _WIN32
       SetConsoleOutputCP(CP_UTF8); // 条件编译,设置控制台输出为UTF-8
    #endif
    std::cout<<expected_str<<std::endl;
    MaaStringBuffer* detail_buffer = MaaStringBufferCreate();
    MaaSize node_id_list_size=10;
    std::vector<MaaNodeId> node_id_list(node_id_list_size);
    MaaStatus status;
    try{
        std::string ORCtask_json = R"(
        {
            "OCRTask": {
                        "recognition": "OCR",           
                        "expected": ")" + std::string(expected_str) + R"(",            
                        "action": "Click"
                    }
        }
        )";
        this->task_id = MaaTaskerPostTask(this->tasker_handle,
            "OCRTask", //任务名
            ORCtask_json.c_str());
    MaaTaskerWait(this->tasker_handle,this->task_id);
    MaaTaskerGetTaskDetail(
             this->tasker_handle,
             this->task_id,
             detail_buffer,
             node_id_list.data(),
             &node_id_list_size,
             &status
    );
        return status;
    }catch(...){
        return -1;
    }
}
int IMAAEntity_Tasker::TemplateMatchClick(const char* Template_path){
     #ifdef _WIN32
       SetConsoleOutputCP(CP_UTF8); // 条件编译,设置控制台输出为UTF-8
    #endif
    std::cout<<Template_path<<std::endl;
    MaaStringBuffer* detail_buffer = MaaStringBufferCreate();
    MaaSize node_id_list_size=10;
    std::vector<MaaNodeId> node_id_list(node_id_list_size);
    MaaStatus status;
    try{
        std::string ORCtask_json = R"(
        {
            "OCRTask": {
                        "recognition": "TemplateMatch",           
                        "template": ")" + std::string(Template_path) + R"(",            
                        "action": "Click"
                    }
        }
        )";
        this->task_id = MaaTaskerPostTask(this->tasker_handle,
            "OCRTask", //任务名
            ORCtask_json.c_str());
    MaaTaskerWait(this->tasker_handle,this->task_id);
    MaaTaskerGetTaskDetail(
             this->tasker_handle,
             this->task_id,
             detail_buffer,
             node_id_list.data(),
             &node_id_list_size,
             &status
    );
        return status;
    }catch(...){
        return -1;
    }

}
int IMAAEntity_Tasker::FeatureMatchClick(const char* Template_path){
     #ifdef _WIN32
       SetConsoleOutputCP(CP_UTF8); // 条件编译,设置控制台输出为UTF-8
    #endif
    std::cout<<Template_path<<std::endl;
    MaaStringBuffer* detail_buffer = MaaStringBufferCreate();
    MaaSize node_id_list_size=10;
    std::vector<MaaNodeId> node_id_list(node_id_list_size);
    MaaStatus status;
    try{
        std::string ORCtask_json = R"(
        {
            "OCRTask": {
                        "recognition": "FeatureMatch",           
                        "expected": ")" + std::string(Template_path) + R"(",            
                        "action": "Click"
                    }
        }
        )";
        this->task_id = MaaTaskerPostTask(this->tasker_handle,
            "OCRTask", //任务名
            ORCtask_json.c_str());
    MaaTaskerWait(this->tasker_handle,this->task_id);
    MaaTaskerGetTaskDetail(
             this->tasker_handle,
             this->task_id,
             detail_buffer,
             node_id_list.data(),
             &node_id_list_size,
             &status
    );
        return status;
    }catch(...){
        return -1;
    }

}