/**
 * @file data_object.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Data Object
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_DATA_OBJECT_CLASS
#define RVM_DATA_OBJECT_CLASS

#include <cstdint>
#include <string>

#include "rvm_structs.h"

class rvm_dataPathConfigurationBlock;   /* Forward declaration of rvm_dataPathConfigurationBlock class */

/**
 * @brief Data Object class implementation
 */
class DataObject
{
public:

    /**
     * @brief Constructs a new Data Object object
     */
    DataObject();

    /**
     * @brief Destroys the Data Object object
     */
    ~DataObject();

    /**
     * @brief Sets Data Object id, size and access time
     *
     * @param[in]       id                      Identifier to Data Object
     * @param[in]       size                    The size of the memory area(in bytes) for storing data to Data Object
     * @param[in]       accessTime              Access time to data in ns.
     *
     * @retval          0                       Success
     * @retval          -1                      Failure
     */
    int set(const uint8_t &id, const uint32_t &size, const uint32_t &accessTime);

    /**
     * @brief Initializes Data Object  of a specific data
     *
     * @param[in]       initData                Data or File name with data to initialize Data Object
     * @param[in]       length                  Data length to initialize Data Object or if length = 255 indicator that initData contains a file name
     * 
     * @retval          0                       Success
     * @retval          -1                      Failure
     */
    int init(const uint8_t &initData, uint8_t length);

    /**
     * @brief Associates Data Object with related Data path configuration block
     *
     * @param[in]       cfgnBlock               Reference to related Data path configuration block
     */
    void associate(rvm_dataPathConfigurationBlock &cfgnBlock);

    /**
     * @brief Returns a value indicating the availability of the data
     *
     * @retval          stDO::empty             if data is empty 
     * @retval          stDO::full              if data is full 
     */
    uint8_t dataEnable(); 

    /**
     * @brief Notifies about Access Type 
     * 
     * @param[in]       at                      Access Type form APE
     */
    void accessType(uint8_t at);

    /**
     * @brief Returns reference to temporary data from Data Object
     *
     * @retval          uint8_t&                Reference to temporary data
     */
    uint8_t & read();

    /**
     * @brief Writes temporary data to Data Object
     *
     * @param[in]       tmpData                 Reference to temporary data
     */
    void write(uint8_t & tmpData);

    /**
     * @brief Gets unique Data Object identifier
     * 
     * @retval          uint16_t                Unique Data Object identifier
     */
    uint8_t getId();

    /**
     * @brief Converts Data Object to string
     *
     * @retval          std::string             Data Object as string
     */
    std::string to_str();

private:

    uint8_t id = 0;                 /* Unique Data Object identifier */
    uint32_t size = 0;              /* The size of the memory area(in bytes) for storing data to Data Object */
    uint32_t accessTime = 0;        /* Access time to data in ns */
    uint8_t *data = nullptr;        /* Pointer to start of data to Data Object */
    rvm_dataPathConfigurationBlock * cfgnBlock = nullptr; /* Externally related Data path congiguration block */
    StatusFromDataObject status = {};    /* Current status of Data Object */

    /**
     * @brief Converts data of Data Object to string hex format
     *
     * @retval          std::string             Data of string hex format
     */
    std::string to_strData();

    /**
     * @brief Converts data array of memory to string filename
     *
     * @param[in]       dataFromMem             Reference on first element of data array. Maximum size of array equals 255.
     *
     * @retval          std::string             String filename
     */
    std::string convertToFilename(const uint8_t &dataFromMem);

    /**
     * @brief Reads data from memory at a pointer and writes to Data Object data.
     *
     * @param[in]       dataFromMem             Reference on first element of data array in memory.
     * @param[in]       length                  Number of elements in array
     */
    void readDataFromMemory(const uint8_t &dataFromMem, uint32_t length);

    /**
     * @brief Reads data from file and writes to Data Object data.
     *
     * @param[in]       fileName                File name for reading data
     */
    void readDataFromFile(std::string fileName);
};

#endif // RVM_DATA_OBJECT_CLASS
