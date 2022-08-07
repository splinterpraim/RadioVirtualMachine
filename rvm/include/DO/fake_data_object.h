#ifndef RVM_FAKE_DATA_OBJECT_CLASS
#define RVM_FAKE_DATA_OBJECT_CLASS
#include <iostream>
#include "DO/idata_object.h"
#include "rvm_structs.h"


namespace rvm
{
      class FakeDataObject : public IDataObject
    {
    public:
        uint8_t id = 0;
        uint32_t size = 0;
        uint32_t accessTime = 0;
        uint8_t *data = nullptr;
        StatusFromDataObject status;

        /* Sets DO id, size and access time */
        int set(const uint8_t &id, const uint32_t &size, const uint32_t &accessTime) override;
    };
};
#endif // RVM_FAKE_DATA_OBJECT_CLASS
