#include "ASF/abstract_switch_fabric.h"

rvm::AbstractSwitchFabric::~AbstractSwitchFabric()
{
    delete[] dataPorts;
    delete[] processingPorts;
    delete[] connectors;
}

void rvm::AbstractSwitchFabric::set(int numPortsDO, int numPortsAPE)
{
    if(numPortsDO<0){
        /* exeption */
    }
    createDataPorts(numPortsDO);
    createProcessingPorts(numPortsAPE);
    allocConnectors(numPortsAPE);
    dataPorts_size = numPortsDO;
    processingPorts_size = numPortsAPE;
    connectors_size = numPortsAPE;
}
void rvm::AbstractSwitchFabric::createDataPorts(uint8_t numberPorts)
{
    dataPorts = new struct DataPort[numberPorts];
}

void rvm::AbstractSwitchFabric::createProcessingPorts(uint32_t numberPorts)
{
    processingPorts = new struct ProcessingPort[numberPorts];
}

/* Create connectors */
void rvm::AbstractSwitchFabric::allocConnectors(int numConnectors)
{
    connectors = new struct Connector[numConnectors];
}

void rvm::AbstractSwitchFabric::createConnector(int DataPortsId, int ProcessingPortsId, int dir)
{
    static int i = 0;
    connectors[i].dataPortId = DataPortsId;
    connectors[i].processingPortId = ProcessingPortsId;
    connectors[i].dir = dir;
    i++;
}