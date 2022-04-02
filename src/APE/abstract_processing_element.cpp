#include "APE/abstract_processing_element.h"

rvm::AbstractProcessingElement::AbstractProcessingElement()
{
}
rvm::AbstractProcessingElement::~AbstractProcessingElement()
{
    delete[] ports;
}

int rvm::AbstractProcessingElement::setID(uint16_t id, uint8_t numPorts)
{
    this->id = id;
    this->numPorts = numPorts;
    ports = new portAPE[numPorts];
    return 0;
}

int rvm::AbstractProcessingElement::set(uint8_t portNumber, const uint8_t accessTypes, uint16_t cost, uint16_t time)
{
    //! each ports have cost/time?
    this->cost = cost;
    this->time = time;

    /* Out-of-bounds check ports */
    if (portNumber >= numPorts)
    {
        throw std::string("Error APE_" + std::to_string(id) + ": in set(), portNumber >= numPorts");
    }
    ports[portNumber].accessTypes = accessTypes;
    return 0;
}
int rvm::AbstractProcessingElement::init(const uint32_t &opcode, int (*operation)(uint8_t argc, ...))
{
    this->opcode = opcode;
    this->operation = operation;
    return 0;
}

void rvm::AbstractProcessingElement::setSendControlUnit(ControlUnit &cu)
{
    this->cu = &cu;
}

int rvm::AbstractProcessingElement::checkCallBack()
{
    std::cout << "d" << std::endl;
    // status.id = id;
    // status.state = inactive;
    // status.exception = 0;
    // cu->sendStatusFromAbstractProcessingElement(status);
    int result;
    operation(3, 1, 2, result);
    return 0;
}

void rvm::AbstractProcessingElement::doOperation()
{
    int rez = 0;
    operation(3,2,2,1,&rez);
    LogManager().makeLog(std::to_string(rez));
}
std::string rvm::AbstractProcessingElement::to_str()
{
    std::string result_str = "id " + std::to_string(id) + ", cost " + std::to_string(cost) +
                             ", time " + std::to_string(time) + ", opcode " + std::to_string(opcode) + "\n";
    for (size_t i = 0; i < numPorts; i++)
    {
        result_str += "  " + std::to_string(i) + " port: " + std::to_string((ports + i)->accessTypes) + "\n";
    }

    return result_str;
}