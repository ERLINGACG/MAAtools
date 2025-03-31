#ifndef IMAAENTITY_CONTORLLER_H
#define IMAAENTITY_CONTORLLER_H

#include "MAACoreInclude/Core.h"

class IMAAEntity_Contorller final : public MAAEntity_Contorller {
public:
    MaaController* controller_handle = nullptr;
    MaaCtrlId ctrl_id = 0;

public:
    void SetControllerHandle(int index)  override;
    void SetCtrlId()                     override;
    int WaitConnect()                   override;
    MaaController* GetControllerHandle() override;
    MaaCtrlId GetCtrlId()                override;
};

#endif // IMAAENTITY_CONTORLLER_H