#ifndef RVM_I_DATA_OBJECT_CLASS
#define RVM_I_DATA_OBJECT_CLASS
#include <iostream>


namespace rvm {

    class IDataObject
    {
    public:
        virtual int set(const uint8_t &id, const uint32_t &size, const uint32_t &accessTime) = 0;
        virtual ~IDataObject() = default;
    };
}

#endif // RVM_I_DATA_OBJECT_CLASS
