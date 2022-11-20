
#include "DO/data_object.h"
#include "common.hpp"

// using namespace rvm;
DataObject::DataObject()
{
}

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
        if (cfgnBlock == nullptr)
        {
            throw std::runtime_error(RVM_ERR_STR("Initialization DataObject failed, Data Object is not related to  Control Unit's data path configuration block!"));
        }
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
            }

            cfgnBlock->sendStatusFromDataObject(status);
        }
        catch (const std::exception &e)
        {
            std::cerr << RVM_ERR_STR("Exception: Initialization DataObject failed, error during function execution!") << std::endl;
            return -1;
        }
    }

    return 0;
}

void DataObject::setSendControlUnit(ControlUnit &cu)
{
    this->cu = &cu;
}

void DataObject::associate(rvm_dataPathConfigurationBlock &cfgnBlock)
{
    this->cfgnBlock = &cfgnBlock;
}


std::string DataObject::to_str()
{
    std::string result_str = "id " + std::to_string(id) + ", " +
                             "size " + std::to_string(size) + ", " +
                             "accessTime " + std::to_string(accessTime) + "\n" +
                             "status: " + status.to_str() + "\n" +
                             "data: " + to_strData();
    return result_str;
}



std::string DataObject::to_strData()
{
    std::string result_str;

    for (size_t i = 0; i < size; i++)
    {
        result_str += std::to_string(data[i]) + " ";
    }
    result_str += '\n';
    return result_str;
}

/* Other functions */
std::string DataObject::convertToFilename(const uint8_t &initData)
{
    std::string filename;
    char symbol = ' ';
    for (size_t i = 0; i < 255; i++)
    {
        symbol = static_cast<char>((&initData)[i]);
        if (symbol == '\n')
        {
            break;
        }
        filename += symbol;
    }
    return filename;
}

int DataObject::readDataFromMemory(const uint8_t &dataFromMem, uint32_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        this->data[i] = (&dataFromMem)[i];
    }
    return 0;
}

int DataObject::readDataFromFile(std::string fileName)
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
    return 0;
}
