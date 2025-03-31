

#include "MAACoreInclude/Core.h"


 class IMAAEntity_C final : public MAAEntity_C{
     private:
            MaaController* controller_handle;
            MaaCtrlId      ctrl_id;
            MaaResource*   resource_handle;
            MaaResId       res_id;
            MaaTasker*     tasker_handle;
            MaaTaskId      task_id;
            const char*    Task_name;
            const char*    resource_dir;
            const char*    user_path;
            int            device_index;        
     public:
       const char* GetTaskName();
       void SetDeviceIndex(int index);
       void SetUserPath(const char* path);
       void SetResourcePath(const char* path);


       void InitOption()          override;
       void SetControllerHandle() override;
       void SetCtrlId()           override;
       void SetResourceHandle()   override;
       void SetResId()            override;
       void WaitConnect()         override;
       void WaitResource()        override;
       void SetTaskerHandle()     override;
       void Init()                override;
       
    //    void GetTaskDetial() override;
    //    void GetTaskResult() override;
    //    void PostTask() override;
      void Destroy() override;
};
void IMAAEntity_C::SetDeviceIndex(int index) {
    this->device_index = index;
}

void IMAAEntity_C::SetResourcePath(const char* path) {
    this->resource_dir = _strdup(path);
}

void IMAAEntity_C::SetUserPath(const char* path) {
    this->user_path = _strdup(path);
}

const char* IMAAEntity_C::GetTaskName() {
    return this->Task_name;
}

void IMAAEntity_C::InitOption() {
    std::cout << "InitOption,TEST" << std::endl;
    MaaToolkitConfigInitOption(this->user_path,"{}");
    this->Task_name = "init_option";
}


void IMAAEntity_C::SetControllerHandle() {
    std::cout << "SetControllerHandle,TEST" << std::endl;
    this->controller_handle = Auto_create_adb_controller(this->device_index);
    this->Task_name = "connect_find";
}

void IMAAEntity_C::SetCtrlId() {
    std::cout << "SetCtrlId,TEST" << std::endl;
    this->ctrl_id = MaaControllerPostConnection(this->controller_handle);
    this->Task_name = "connect_init";
}

void IMAAEntity_C::WaitConnect() {
    std::cout << "WaitConnect,TEST" << std::endl;
    MaaControllerWait(this->controller_handle, this->ctrl_id);
    this->Task_name = "connect_wait";
}

void  IMAAEntity_C::SetResourceHandle() {
    std::cout << "SetResourceHandle,TEST" << std::endl;
    this->resource_handle =MaaResourceCreate(nullptr, nullptr);
    this->Task_name = "adb_connect";
}

void IMAAEntity_C::SetResId() {
    std::cout << "SetResId,TEST" << std::endl;
    this->res_id =MaaResourcePostBundle(this->resource_handle, this->resource_dir);
    if(this->res_id == MaaInvalidId){
        std::cout << "MaaResourcePostBundle failed" << std::endl;
        MaaControllerDestroy(this->controller_handle);
    }
    this->Task_name = "adb_post";
}
void IMAAEntity_C::WaitResource() {
    std::cout << "WaitResource,TEST" << std::endl;
    MaaResourceWait(this->resource_handle, this->res_id);
    this->Task_name = "adb_wait";
}



void IMAAEntity_C::SetTaskerHandle() {
    std::cout << "SetTaskerHandle,TEST" << std::endl;
    this->tasker_handle = MaaTaskerCreate(nullptr, nullptr);
    this->Task_name = "tasker_create";
    MaaTaskerBindResource(this->tasker_handle, this->resource_handle);  //绑定资源管理器
    MaaTaskerBindController(this->tasker_handle, this->controller_handle);//绑定控制器
}

void IMAAEntity_C::Init() {
    std::cout << "Init,TEST" << std::endl;
    if(!MaaTaskerInited(this->tasker_handle)){
        std::cout << "MaaTaskerInited failed" << std::endl;
        MaaControllerDestroy(this->controller_handle);
        MaaResourceDestroy(this->resource_handle);
        this->Task_name = "tasker_init_failed";
    }
    else{
        this->Task_name = "tasker_init_success";
    }
}


void IMAAEntity_C::Destroy() {
    std::cout << "Destroy,TEST" << std::endl;
    MaaControllerDestroy(this->controller_handle);
    MaaResourceDestroy(this->resource_handle);
    MaaTaskerDestroy(this->tasker_handle);
    free((void*)this->user_path);
    free((void*)this->resource_dir);
    this->Task_name = "Task_destroy Over";
}

extern "C" {

    /*------对象操作管理------*/
    MAA_API const char* GetTaskName(IMAAEntity_C* entity) {
        const char* Task_name = _strdup(entity->GetTaskName()); //获取任务名称
        return Task_name;
    }
    MAA_API void InitOption(IMAAEntity_C* entity) {        //初始化配置
        entity->InitOption();
    }

    MAA_API void SetUserPath(IMAAEntity_C* entity, const char* path) { //设置用户路径
        entity->SetUserPath(_strdup(path));
    }
    MAA_API void SetResourcePath(IMAAEntity_C* entity, const char* path) { //设置资源路径
        entity->SetResourcePath(_strdup(path));
    }

    MAA_API void SetDeviceIndex(IMAAEntity_C* entity, int index) {  //设置设备索引
        entity->SetDeviceIndex(index);
    }


    MAA_API void SetResourceHandle(IMAAEntity_C* entity) { //设置资源句柄
        entity->SetResourceHandle();
    }
    MAA_API void SetControllerHandle(IMAAEntity_C* entity) { //设置控制器句柄
        entity->SetControllerHandle();
    }
    MAA_API void SetCtrlId(IMAAEntity_C* entity) {   //设置控制器ID
        entity->SetCtrlId();
    }
    MAA_API void SetResId(IMAAEntity_C* entity) {    //设置资源ID
        entity->SetResId();
    }

    MAA_API void WaitResource(IMAAEntity_C* entity) { //等待资源
        entity->WaitResource();
    }
        MAA_API void WaitConnect(IMAAEntity_C* entity) { //等待连接
        entity->WaitConnect();
    }

    MAA_API void SetTaskerHandle(IMAAEntity_C* entity) { //设置任务管理器句柄
        entity->SetTaskerHandle();
    }
    MAA_API void Init(IMAAEntity_C* entity) { //初始化对象
        entity->Init();
    }

    MAA_API void Destroy(IMAAEntity_C* entity) {   //销毁对象资源
        entity->Destroy();
    }

    /*------对象操作管理------*/


    /*------生命周期管理------*/
    MAA_API IMAAEntity_C* CreateEntity() { //创建对象
        return new IMAAEntity_C();
    }

    MAA_API void ReleaseEntity(IMAAEntity_C* entity) { //释放对象
        delete entity;
    }
    /*------生命周期管理------*/
    
    // MAA_API void ReleaseEntity(MAAEntity_C* entity) {
    //     if(entity) entity->Destroy();
    // }
}