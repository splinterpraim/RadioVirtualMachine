#ifndef RVM_DATA_OBJECT_CLASS
#define RVM_DATA_OBJECT_CLASS

/* C++ Headers */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

/* Exception Headers */
#include <exception>
#include <stdexcept>
#include <new>
#include <functional>

/* Project Headers */
#include "class_definition.h"
#include "rvm_structs.h"
#include "CU/control_unit.h"
#include "CU/rvm_data_path_configuration_block.hpp"
#include "DO/idata_object.h"

class DataObject
{

public:
    /* Constructor */
    DataObject();

    /* Destructor */
    ~DataObject();

    /**
     * @brief Sets Data Object id, size and access time
     *
     * @param[in] id Identifier to Data Object
     * @param[in] size The size of the memory area(in bytes) for storing data to Data Object
     * @param[in] accessTime  Access time to data in ns.
     * @return int: 0 - if the function worked without errors, -1 - if the function worked with errors
     */
    int set(const uint8_t &id, const uint32_t &size, const uint32_t &accessTime);

    /**
     * @brief Initializes Data Object  of a specific data
     *
     * @param initData[in] Data or File name with data to initialize Data Object
     * @param length[in]  Data length to initialize Data Object or if length = 255 indicator that initData contains a file name
     * @return int: 0 - if the function worked without errors, -1 - if the function worked with errors
     */
    int init(const uint8_t &initData, uint8_t length);

    /**
     * @brief Sets a pointer to the associated Control Unit
     *
     * @param cu[in] associated Control Unit object
     * @return void
     */
    void setSendControlUnit(ControlUnit &cu);
    void associate(rvm_dataPathConfigurationBlock &cfgnBlock);

    uint8_t getId();

    /* Other functions */
    std::string to_str();

private:
    uint8_t id = 0;          /* Identifier to Data Object  */
    uint32_t size = 0;       /* The size of the memory area(in bytes) for storing data to Data Object */
    uint32_t accessTime = 0; /* Access time to data in ns */
    uint8_t *data = nullptr; /* Pointer to start of data to Data Object */

    ControlUnit *cu = nullptr; /* Pointer to associated Control Unit object */
    rvm_dataPathConfigurationBlock * cfgnBlock = nullptr; /* Pointer to associated Data path congiguration block object */

    StatusFromDataObject status; /* Status information to associated Control Unit object */
    uint8_t configured = 0;

    /* Other functions */
    std::string to_strData();
    std::string convertToFilename(const uint8_t &initData);
    int readDataFromMemory(const uint8_t &dataFromMem, uint32_t length);
    int readDataFromFile(std::string fileName);
};

#endif // RVM_DATA_OBJECT_CLASS
