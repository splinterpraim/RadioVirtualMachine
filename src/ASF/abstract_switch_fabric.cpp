#include "abstract_switch_fabric.h"

rvm::AbstractSwitchFabric::~AbstractSwitchFabric()
{
    delete[] dataPorts;
    delete[] processingPorts;
    delete[] connectors;
}

void rvm::AbstractSwitchFabric::createDataPorts(uint8_t numberPorts)
{
    dataPorts = new  struct DataPort[numberPorts];
}

void rvm::AbstractSwitchFabric::createProcessingPorts(uint32_t numberPorts)
{
    processingPorts = new struct ProcessingPort[numberPorts];
}
