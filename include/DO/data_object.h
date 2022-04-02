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
        /* Constructor */
        DataObject();

        /* Destructor */
        ~DataObject();
        
        /* Sets DO id, size and access time */
        int set(const uint8_t &id, const uint32_t &size, const uint32_t &accessTime);

        /* Initializes DO of a specific data */
        int init(const uint8_t &initData, uint8_t length);

        /* Sets a pointer to the associated Control Unit */
        void setSendControlUnit(ControlUnit &cu);
        

        /* Other functions */
        std::string to_str();
        int checkCallBack();

    private:
        uint8_t id = 0;
        uint32_t size = 0;  // in bytes
        uint32_t accessTime = 0;
        uint8_t *data = nullptr;

        // to ControlUnit
        ControlUnit *cu = nullptr;

        StatusFromDataObject status;

        


        /* Other functions */
        std::string to_strData();
        std::string convertToFilename(const uint8_t &initData);
        int readDataFromMemory(const uint8_t &data, uint32_t length);
        int readDataFromFile(std::string filename);
    };
};
#endif // RVM_DATA_OBJECT_CLASS
