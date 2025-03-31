#ifndef MAAENTITY_INIT_H
#define MAAENTITY_INIT_H
#include "MAACoreInclude/Core.h"

class MAA_API IMAAEntity_Init final : public MAAEntity_Init{
    public:
       const char* user_path;
    public:
        int Init(MaaTasker* tasker_handle) override;
        void InitOption() override;
        void SetUserPath(const char* path);
};


#endif