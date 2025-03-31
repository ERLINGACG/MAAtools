#ifndef IMAAENTITY_RESOURCE_H
#define IMAAENTITY_RESOURCE_H

#include "MAACoreInclude/Core.h"


class IMAAEntity_Resource final : public MAAEntity_Resource {

    public:
        MaaResource* resource_handle;
        MaaResId     res_id;
        const char*  resource_dir;
    public:
        ~IMAAEntity_Resource()                         override;
        void         SetResoursePath(const char* path) override;               
        void         SetResourceHandle()               override;
        int          SetResId()                        override;
        int          WaitsResource()                   override;
        MaaResource* GetResourceHandle()               override;
        MaaResId     GetResId()                        override;

};


#endif // IMAAENTITY_RESOURCE_H