/**
 * @file data_object.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Data Object
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "DO/data_object.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <new>

#include "common.hpp"
#include "CU/rvm_data_path_configuration_block.hpp"


/* Private */

std::string DataObject::to_strData()
{
    std::stringstream resStream;

    for (size_t i = size; i != 0; i--)
    {
        resStream << std::hex << (int)data[i-1] << std::dec << " ";
    }
    return resStream.str();
}

std::string DataObject::convertToFilename(const uint8_t &dataFromMem)
{
    std::string filename;
    char symbol = ' ';
    for (size_t i = 0; i < 255; i++)
    {
        symbol = static_cast<char>((&dataFromMem)[i]);
        if (symbol == '\n')
        {
            break;
        }
        filename += symbol;
    }
    return filename;
}

void DataObject::readDataFromMemory(const uint8_t &dataFromMem, uint32_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        this->data[i] = (&dataFromMem)[i];
    }
}

void DataObject::readDataFromFile(std::string fileName)
{
    /* Open file */
    std::ifstream infile(fileName);
    if (!infile.is_open())
    {
        throw std::string(RVM_ERR_STR("Error DO_" + std::to_string(id) + ": in init(), file can't open"));
    }

    /* Read Data */
    std::string symbolDataFromFile;
    for (size_t i = 0; (i < size) && (!infile.eof()); i++)
    {
        infile >> symbolDataFromFile;
        if (symbolDataFromFile == "")
        {
            break;
        }
        data[i] = std::stoi(symbolDataFromFile); //! ex stoi (if symbol is not a integer)
        symbolDataFromFile = "";
    }

    infile.close();
}

/* Public */

DataObject::DataObject() { }

DataObject::~DataObject()
{
    delete[] data;
}

int DataObject::set(const uint8_t &id, const uint32_t &size, const uint32_t &accessTime)
{
    /* Throw exceptions */
    {
        /* Invalid argument */
        if (size == 0)
        {
            throw std::invalid_argument(RVM_ERR_STR("Setting DataObject failed, argument size = 0!"));
        }

        /* Double function call */
        if (data != nullptr)
        {
            throw std::runtime_error(RVM_ERR_STR("Setting DataObject failed, Double set function call!"));
        }
    }

    /* Exception Handle */
    {

        /* Allocate mem */
        try
        {
            data = new uint8_t[size];
            std::fill(data, data + size, 0);

            this->id = id;
            this->size = size;
            this->accessTime = accessTime;

            /* Set status */
            status.id = id;
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << RVM_ERR_STR("Bad_alloc: Setting DataObject failed, Memory allocation error ") << std::endl;
            return -1;
        }
        catch (const std::exception &e)
        {
            std::cerr << RVM_ERR_STR("Exception: Setting DataObject failed, error during function execution!") << std::endl;
            return -1;
        }
    }

    return 0;
}

int DataObject::init(const uint8_t &initData, uint8_t length)
{
    /* Throw exceptions */
    {
        /*  Error size */
        if ((length > size) && (length != 255))
        {
            throw std::invalid_argument(RVM_ERR_STR("Initialization DataObject failed, argument length > allocated size!"));
        }
#ifdef UNCOMENT
        if (cfgnBlock == nullptr)
        {
            throw std::runtime_error(RVM_ERR_STR("Initialization DataObject failed, Data Object is not related to  Control Unit's data path configuration block!"));
        }
#endif
    }

    /* Exception Handle */
    {
        try
        {
            /* Read non-empty data */
            if (length != 0)
            {
                /* Read data from file */ //?DELL
                if (length == 255)
                {
                    std::string filename = convertToFilename(initData);
                    readDataFromFile(filename);
                }

                /* Read data from memory */
                else
                {
                    readDataFromMemory(initData, length);
                }
                status.state = full;
                status.accessType = at::write;
            }
#ifdef UNCOMENT
            qDO->push(status);
#endif
        }
        catch (const std::exception &e)
        {
            std::cerr << RVM_ERR_STR("Exception: Initialization DataObject failed, error during function execution!") << std::endl;
            return -1;
        }
    }

    return 0;
}

void DataObject::associate(rvm_dataPathConfigurationBlock &cfgnBlock, rvm_ThreadsafeQueue<StatusFromDataObject>& qDO)
{
    this->cfgnBlock = &cfgnBlock;
    this->qDO = &qDO;
}

uint8_t DataObject::dataEnable()
{
    return status.state;
}

void DataObject::accessType(uint8_t at) { }

uint8_t &DataObject::read()
{
    if (!data)
    {
        throw std::runtime_error(RVM_ERR_STR("data is not initialized"));
    }

    if (status.state == stDO::empty)
    {
        throw std::runtime_error(RVM_ERR_STR("attempt to read empty data"));
    }

    uint8_t *tmpData = new uint8_t[size];
    for (uint32_t  i = 0; i < size; i++)
    {
        tmpData[i] = data[i];
        data[i] = 0;
    }

    status.state = stDO::empty; // todo: notify DP_cfgBlock
    qDO->push(status);
    return *tmpData;
}

void DataObject::write(uint8_t &tmpData)
{
    if (!data)
    {
        throw std::runtime_error(RVM_ERR_STR("data is not initialized"));
    }

    if (status.state == stDO::full)
    {
        throw std::runtime_error(RVM_ERR_STR("attempt to write in full data"));
    }
    uint8_t * ptrTmpData = &tmpData;
    for (uint32_t  i = 0; i < size; i++)
    {
        data[i] = ptrTmpData[i];
    }
    status.state = stDO::full; // todo: notify DP_cfgBlock
}

uint8_t DataObject::getId()
{
    return id;
}

std::string DataObject::to_str()
{
    std::string result_str = "id " + std::to_string(id) + ", " +
                             "size " + std::to_string(size) + ", " +
                             "accessTime " + std::to_string(accessTime) + "\n" +
                             "\tstatus: " + status.to_str() + "\n" +
                             "\tdata: " + (status.state? to_strData():std::string(""));
    return result_str;
}
