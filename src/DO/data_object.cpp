
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

    // allocate mem;
    data = new uint8_t[size];
    // filling zeros
    for (size_t i = 0; i < size; i++)
    {
        data[i] = 0;
    }

    // set status
    status.id = id;
    status.state = empty;

    // cu->sendStatusFromDataObject(status);
    return 0;
}
int rvm::DataObject::init(const uint8_t &initData, uint8_t length)
{

    // Error size
    if ((length > size) && (length != 255))
    {
        throw std::string("Error DO_" + std::to_string(id) + ": in init(), length > size");
    }

    if (length != 0)
    {
        // Data from file
        if (length == 255)
        {
            // convert_to_string(initData)
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

            // read Data from file
            std::ifstream infile(filename);
            if (!infile.is_open())
            {
                throw std::string("Error DO_" + std::to_string(id) + ": in init(), file can't open");
            }
            std::string dataFromFile;
            std::string symbolDataFromFile;

            for (size_t i = 0; (i < size) && (!infile.eof()); i++)
            {
                
                infile >> symbolDataFromFile;
                if(symbolDataFromFile == ""){
                    break;
                }
                data[i] = symbolDataFromFile[0] - 48;

                symbolDataFromFile = "";
            }

            infile.close();

            std::cout << dataFromFile << std::endl;
        }

        // Data from initData, not empty
        else
        {
            for (size_t i = 0; i < length; i++)
            {
                data[i] = (&initData)[i];
            }
        }
        status.state = full;
    }

    cu->sendStatusFromDataObject(status);
    showData();
    return 0;
}

// void DataObject::setSendStatusFunction(int (*sendStatus)(ControlUnit &cu, StatusFromDataObject statusDO))
// {
//     this->sendStatus = sendStatus;
// }
void rvm::DataObject::setSendControlUnit(ControlUnit &cu)
{
    this->cu = &cu;
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

void rvm::DataObject::showData()
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << static_cast<int>(data[i]) << " ";
    }
    std::cout << std::endl;
}