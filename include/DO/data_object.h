#ifndef RVM_DATA_OBJECT_CLASS
#define RVM_DATA_OBJECT_CLASS

#include <iostream>
#include <fstream>
#include <string>
#include "class_definition.h"

#include "rvm_structs.h"
#include "CU/control_unit.h"

namespace rvm
{
    class DataObject
    {

    public:
        DataObject();
        ~DataObject();
        
        int set(const uint8_t &id, const uint32_t &size, const uint32_t &accessTime);
        int init(const uint8_t &initData, uint8_t length);

        void setSendControlUnit(ControlUnit &cu);
        void setID(int id) { this->id = id; }

        //
        int checkCallBack();

    private:
        uint8_t id = 0;
        uint32_t size = 0;  // in bytes
        uint32_t accessTime = 0;
        uint8_t *data = nullptr;

        // to ControlUnit
        ControlUnit *cu = nullptr;

        StatusFromDataObject status;

        void showData();
    };
};
#endif // RVM_DATA_OBJECT_CLASS
