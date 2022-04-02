
#include "DO/data_object.h"

// using namespace rvm;
rvm::DataObject::DataObject()
{
}

rvm::DataObject::~DataObject()
{
    delete[] data;
}

int rvm::DataObject::set(const uint8_t &id, const uint32_t &size, const uint32_t &accessTime)
{
    if (size == 0)
    {
        throw std::string("Error DO_" + std::to_string(id) + ": in set(), size == 0");
    }

    this->id = id;
    this->size = size;
    this->accessTime = accessTime;

    /* Allocate mem */
    data = new uint8_t[size];

    /* Filling zeros */
    for (size_t i = 0; i < size; i++)
    {
        data[i] = 0;
    }

    /* Set status */
    status.id = id;

    //! need to confirm to CU?
    // cu->sendStatusFromDataObject(status);
    return 0;
}

int rvm::DataObject::init(const uint8_t &initData, uint8_t length)
{
    //! in init set exception if Error size
    /*  Error size */
    if ((length > size) && (length != 255))
    {
        throw std::string("Error DO_" + std::to_string(id) + ": in init(), length > size");
    }

    /* Read non-empty data */
    if (length != 0)
    {
        /* Read data from file */
        if (length == 255)
        {
            std::string filename = convertToFilename(initData);
            readDataFromFile(filename);
        }

        /* Read data from initData */
        else
        {
            readDataFromMemory(initData, length);
        }
        status.state = full;
    }

    //! need to confirm to CU?
    cu->sendStatusFromDataObject(status);
    return 0;
}

void rvm::DataObject::setSendControlUnit(ControlUnit &cu)
{
    this->cu = &cu;
}

std::string rvm::DataObject::to_str()
{
    std::string result_str = "id " + std::to_string(id) + ", " +
                             "size " + std::to_string(size) + ", " +
                             "accessTime " + std::to_string(accessTime) + "\n" +
                             "status: " + status.to_str() + "\n" +
                             "data: " + to_strData();
    return result_str;
}

int rvm::DataObject::checkCallBack()
{
    std::cout << "d" << std::endl;
    status.id = id;
    status.state = empty;
    status.accessType = 1;
    status.exception = 0;
    // sendStatus(*this->cu, status);
    // cu->sendStatusFromDataObject(status);
    return 0;
}

std::string rvm::DataObject::to_strData()
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
std::string rvm::DataObject::convertToFilename(const uint8_t &initData)
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

int rvm::DataObject::readDataFromMemory(const uint8_t &data, uint32_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        this->data[i] = (&data)[i];
    }
}

int rvm::DataObject::readDataFromFile(std::string filename)
{
    /* Open file */
    std::ifstream infile(filename);
    if (!infile.is_open())
    {
        throw std::string("Error DO_" + std::to_string(id) + ": in init(), file can't open");
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
        data[i] = std::stoi(symbolDataFromFile);
        symbolDataFromFile = "";
    }
    infile.close();
}
