
#include "MAACoreInclude/MAAEntity_Controller.h"

void IMAAEntity_Contorller::SetControllerHandle(int index) {
    this->controller_handle = Auto_create_adb_controller(index);
}

void IMAAEntity_Contorller::SetCtrlId() {
    this->ctrl_id = MaaControllerPostConnection(this->controller_handle);

}
MaaController* IMAAEntity_Contorller::GetControllerHandle() {
    return this->controller_handle;
}
MaaCtrlId IMAAEntity_Contorller::GetCtrlId(){
    
    return this->ctrl_id;
}
int IMAAEntity_Contorller::WaitConnect() {
    try {
        MaaControllerWait(this->controller_handle, this->ctrl_id);
        return 0;
    }catch (...) {
        return -1;
    }
}