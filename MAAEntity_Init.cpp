#include "MAACoreInclude/MAAEntity_Init.h"

void IMAAEntity_Init::SetUserPath(const char* path){
    this->user_path = _strdup(path);
}

void IMAAEntity_Init::InitOption(){
     MaaToolkitConfigInitOption(this->user_path, "{}");
}
int IMAAEntity_Init::Init( MaaTasker* tasker_handle){
    try{

        MaaTaskerInited(tasker_handle);
        return 0;
    }catch(...){
        return -1;
    }
}
