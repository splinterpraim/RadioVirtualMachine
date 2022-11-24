#include "ASF/abstract_switch_fabric.h"

#include <exception>
#include <stdexcept>
#include <string>
#include "common.hpp"

AbstractSwitchFabric::~AbstractSwitchFabric()
{
}

void AbstractSwitchFabric::set(int numPortsDO, int numPortsAPE)
{
    /* Throw exceptions */
    {
        if (numPortsDO <= 0)
        {
            throw std::runtime_error(RVM_ERR_STR("cannot set ASF, numPortsDO <= 0"));
        }
        if (numPortsAPE <= 0)
        {
            throw std::runtime_error(RVM_ERR_STR("cannot set ASF, numPortsAPE <= 0"));
        }
    }

    createDataPorts(numPortsDO);
    createProcessingPorts(numPortsAPE);
    allocConnectors(numPortsAPE);
}
void AbstractSwitchFabric::createDataPorts(uint8_t numberPorts)
{
    dataPorts.resize(numberPorts);
}

void AbstractSwitchFabric::createProcessingPorts(uint32_t numberPorts)
{
    processingPorts.resize(numberPorts);
}

/* Create connectors */
void AbstractSwitchFabric::allocConnectors(int numConnectors)
{
    connectors.resize(numConnectors);
}

void AbstractSwitchFabric::createConnector(int DataPortsId, int ProcessingPortsId, int dir)
{
    static int i = 0;
    connectors[i].dataPortId = DataPortsId;
    connectors[i].processingPortId = ProcessingPortsId;
    connectors[i].dir = dir;
    connectors[i].set = 1;
    i++;
}

std::string AbstractSwitchFabric::to_str()
{
    std::string result_str = "data ports related " + std::to_string(dataPorts.size()) + ":\n";
    for (auto &port : dataPorts)
    {
        if (port.relatedDO != nullptr)
            result_str += std::to_string(port.relatedDO->getId()) + " ";
    }

    result_str += "\nprocessing ports related " + std::to_string(processingPorts.size()) + ":\n";
    for (auto &port : processingPorts)
    {
        if (port.relatedAPE != nullptr)
            result_str += std::to_string(port.relatedAPE->getId()) + " ";
    }

    result_str += "\nconnectors " + std::to_string(connectors.size()) + ":\n(dataPortId, processingPortId, dir):\n";
    for (auto &con : connectors)
    {
        if (con.set == 1)
        {
            result_str += "  " + std::to_string(con.dataPortId) + " " +
                          std::to_string(con.processingPortId) + " " +
                          std::to_string(con.dir) + "\n";
        }
    }

    return result_str;
}