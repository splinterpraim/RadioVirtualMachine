#include "APE/abstract_processing_element.h"

rvm::AbstractProcessingElement::AbstractProcessingElement()
{
}
rvm::AbstractProcessingElement::~AbstractProcessingElement()
{
    delete[] ports;
}

int rvm::AbstractProcessingElement::set(uint8_t numPorts, const uint8_t &accessTypes, uint16_t cost, uint16_t time)
{
    this->numPorts = numPorts;
    this->cost = cost;
    this->time = time;

    ports = new portAPE[numPorts];
    for (size_t i = 0; i < numPorts; i++)
    {
        ports[i].accessTypes = (&accessTypes)[i];
    }
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