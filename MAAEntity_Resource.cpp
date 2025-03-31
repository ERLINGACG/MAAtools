
#include "MAACoreInclude/MAAEntity_Resource.h"


//   SetResourceHandle() override;
//         MaaResId    SetResId()           override;

void IMAAEntity_Resource::SetResoursePath(const char* resource_path) {
    this->resource_dir = _strdup(resource_path);
}

void IMAAEntity_Resource::SetResourceHandle() {
    this->resource_handle = MaaResourceCreate(nullptr, nullptr);

}
int IMAAEntity_Resource::SetResId() {

    this->res_id = MaaResourcePostBundle(this->resource_handle, this->resource_dir);
    if (this->res_id == MaaInvalidId) {
        return -1;
    }else {
        return 0;
    }
}
MaaResource* IMAAEntity_Resource::GetResourceHandle() {
    return this->resource_handle;
}
MaaResId IMAAEntity_Resource::GetResId() {
    return this->res_id;
}

IMAAEntity_Resource::~IMAAEntity_Resource() {
    // if (resource_dir) {
    //     free((void*)resource_dir);
    //     resource_dir = nullptr;
    // }
}
int IMAAEntity_Resource::WaitsResource() {
    try{
        MaaResourceWait(this->resource_handle, this->res_id);
        return 0;
    }catch(...){
        return -1;
    }
}