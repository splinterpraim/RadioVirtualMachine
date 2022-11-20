#include "APE/abstract_processing_element.h"

AbstractProcessingElement::AbstractProcessingElement()
{
}
AbstractProcessingElement::~AbstractProcessingElement()
{
    delete[] ports;
}

int AbstractProcessingElement::set(uint16_t id, uint16_t cost, uint16_t time, uint16_t T, const std::vector<uint8_t> &portsAccessTypes)
{
    /* Throw exceptions */
    {
        /* Invalid argument T */
        if (T > 1)
        {
            throw std::invalid_argument("Setting AbstractProcessingElement failed, argument T > 1!");
        }

        /* Invalid argument portsAccessTypes */
        if (portsAccessTypes.size() == 0)
        {
            throw std::runtime_error("Setting AbstractProcessingElement failed, portsAccessTypes.size() == 0!");
        }

        /* Double function call */
        if (ports != nullptr)
        {
            throw std::runtime_error("Setting AbstractProcessingElement failed, Double set function call!");
        }
    }

    /* Exception Handle */
    {

        /* Allocate mem */
        try
        {
            ports = new portAPE[portsAccessTypes.size()];
            int i = 0;
            for (auto el : portsAccessTypes)
            {
                ports[i].num = 0;
                ports[i].accessTypes = el;
                i++;
            }
            this->id = id;
            this->cost = cost;
            this->time = time;
            this->T = T;
            this->numPorts = portsAccessTypes.size();
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Bad_alloc: Setting DataObject failed, Memory allocation error " << std::endl;
            return -1;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception: Setting DataObject failed, error during function execution!" << std::endl;
            return -1;
        }
    }

    return 0;
}



int AbstractProcessingElement::init(const uint32_t &opcode, int (*operation)(uint8_t argc, ...))
{
    /* Throw exceptions */
    {
        /* Invalid argument operation */
        if (operation ==  nullptr)
        {
            throw std::invalid_argument("Setting AbstractProcessingElement failed, operation ==  nullptr!");
        }
    }
    this->opcode = opcode;
    this->operation = operation;
    return 0;
}

void AbstractProcessingElement::setSendControlUnit(ControlUnit &cu)
{
    this->cu = &cu;
}

void AbstractProcessingElement::associate(rvm_dataPathConfigurationBlock &cfgnBlock)
{
    this->cfgnBlock = &cfgnBlock;
}

int AbstractProcessingElement::checkCallBack()
{
    std::cout << "d" << std::endl;
    // status.id = id;
    // status.state = inactive;
    // status.exception = 0;
    // cu->sendStatusFromAbstractProcessingElement(status);
    int result = 0;
    operation(3, 1, 2, result);
    return 0;
}

void AbstractProcessingElement::doOperation()
{
    int rez = 0;
    operation(3, 2, 2, 1, &rez);
    LogManager().makeLog(std::to_string(rez));
}
std::string AbstractProcessingElement::to_str()
{
    std::string result_str = "id " + std::to_string(id) + ", cost " + std::to_string(cost) +
                             ", time " + std::to_string(time) + ", opcode " + std::to_string(opcode) + "\n";
    for (size_t i = 0; i < numPorts; i++)
    {
        result_str += "  " + std::to_string(i) + " port: " + std::to_string((ports + i)->accessTypes) + "\n";
    }

    return result_str;
}