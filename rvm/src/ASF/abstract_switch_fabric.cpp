/**
 * @file abstract_switch_fabric.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Abstract Switch Fabric
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "ASF/abstract_switch_fabric.hpp"

#include <exception>
#include <stdexcept>
#include <string>

#include "common.hpp"
#include "rvm_structs.h"
#include "DO/data_object.hpp"
#include "APE/abstract_processing_element.hpp"



/* Private */

Connector &AbstractSwitchFabric::findConnectorByProccessingPortId(uint32_t processingPortId)
{
    for (auto &contr : connectors)
    {
        if (contr.processingPortId == processingPortId)
        {
            return contr;
        }
    }
    throw std::runtime_error("Connector not found");
}

void AbstractSwitchFabric::createDataPorts(uint8_t numberPorts)
{
    dataPorts.resize(numberPorts);
}

void AbstractSwitchFabric::createProcessingPorts(uint32_t numberPorts)
{
    processingPorts.resize(numberPorts);
}

void AbstractSwitchFabric::allocConnectors(int numConnectors)
{
    connectors.resize(numConnectors);
}

/* Public */

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

void AbstractSwitchFabric::createConnector(int DataPortsId, int ProcessingPortsId, int dir)
{
    static int i = 0;
    connectors[i].dataPortId = DataPortsId;
    connectors[i].processingPortId = ProcessingPortsId;
    connectors[i].dir = dir;
    connectors[i].set = 1;
    i++;
}

void AbstractSwitchFabric::associateDataPort(int dataPortId, DataObject &DO)
{
    if (dataPortId > static_cast<int>(dataPorts.size()))
    {
        throw std::runtime_error(RVM_ERR_STR("Incorrect dataPortId. Out of range in ASF data ports"));
    }
    dataPorts[dataPortId].relatedDO = &DO;
}

void AbstractSwitchFabric::associateProccessingPort(int processingPortId, AbstractProcessingElement &APE, uint8_t portAPE)
{

    if (processingPortId > static_cast<int>(processingPorts.size()))
    {
        throw std::runtime_error(RVM_ERR_STR("Incorrect dataPortId. Out of range in ASF data ports"));
    }
    processingPorts[processingPortId].relatedAPE = &APE;
    processingPorts[processingPortId].port_number = portAPE;
}

void AbstractSwitchFabric::run()
{
    bool finish = false;

    int zeroWork = 0;
    while (!finish)
    {
        /* Data Enable */
        /* Iterate over all data ports */
        size_t port_i = 0;
        for (auto &dPort : dataPorts)
        {
            /* Get current data enable */
            auto dEnable = dPort.relatedDO->dataEnable();

            /* Find related processing ports */
            for (auto &contr : connectors)
            {
                if (contr.dataPortId == port_i)
                {
                    auto &pPort = processingPorts[contr.processingPortId];

                    pPort.relatedAPE->dataEnable(pPort.port_number, dEnable);
                }
            }
            port_i++;
        }

        /* Access type */
        AbstractProcessingElement * readyAPE = nullptr;
        uint16_t readyAPEId = 0;
        bool readyFlag = false;

        /* Iterate over all processing ports */
        port_i = 0;
        uint8_t acType = 0;
        for (auto &pPort : processingPorts)
        {

            /* Ready APE is  not found */
            if(!readyFlag)
            {
                if (pPort.relatedAPE->accessType(pPort.port_number, acType))
                {
                    readyAPE = pPort.relatedAPE;
                    readyAPEId = pPort.relatedAPE->getId();
                    readyFlag = true;
                }
            }

            /* Ready APE is found */
            if (readyFlag)
            {
                if (readyAPEId == pPort.relatedAPE->getId())
                {
                    if (pPort.relatedAPE->accessType(pPort.port_number, acType))
                    {
                        /* Search connector by processing port id */
                        auto &contr = findConnectorByProccessingPortId(port_i);

                        /* Access type matching check */
                        if (acType != contr.dir)
                        {
                            throw std::runtime_error(RVM_ERR_STR("access type and direction of connector mismatch for found APE"));
                        }
                        if (acType == APE_ACCESS_TYPE_R)
                        {
                            auto &ptrTmpData = dataPorts[contr.dataPortId].relatedDO->read();
                            pPort.relatedAPE->read(pPort.port_number, ptrTmpData);
                        }
                    }
                    else
                    {
                        throw std::runtime_error(RVM_ERR_STR("found APE for transfer is failed"));
                    }
                }
            }
           
            port_i++;
        }

        if (readyFlag)
        {
            zeroWork++;
            readyAPE->run();
            port_i = 0;
            for (auto &pPort : processingPorts)
            {
                if (readyAPEId == pPort.relatedAPE->getId())
                {
                    if (pPort.relatedAPE->accessType(pPort.port_number, acType))//? mb not ready after running 
                    {
                        if (acType == APE_ACCESS_TYPE_W)
                        {
                            /* Search connector by processing port id */
                            auto &contr = findConnectorByProccessingPortId(port_i);
                            auto & ptrTmpData = readyAPE->write(pPort.port_number); 
                            dataPorts[contr.dataPortId].relatedDO->write(ptrTmpData);
                            
                        }
                    }

                }
                port_i++;
            }

        }
        
        if (zeroWork == 0)
        {
            finish = true;
        }
        else if( zeroWork > 0)
        {
            zeroWork = 0;
        }
    }

}

std::string AbstractSwitchFabric::to_str()
{
    std::string result_str = "data ports related " + std::to_string(dataPorts.size()) + ":\n";
    for (auto &port : dataPorts)
    {
        if (port.relatedDO != nullptr)
            result_str += std::to_string(port.relatedDO->getId()) + " ";
    }

    result_str += "\nprocessing ports related " + std::to_string(processingPorts.size()) + ":\n(APE Id, port):\n";
    for (auto &port : processingPorts)
    {
        if (port.relatedAPE != nullptr)
            result_str += "(" + std::to_string(port.relatedAPE->getId()) + ":" + std::to_string(port.port_number) + ") ";
    }

    result_str += "\nconnectors " + std::to_string(connectors.size()) + ":\n(dataPortId, processingPortId, dir):\n";
    for (auto &con : connectors)
    {
        if (con.set == 1)
        {
            result_str += "(" + std::to_string(con.dataPortId) + ":" +
                          std::to_string(con.processingPortId) + ":" +
                          std::to_string(con.dir) + ") ";
        }
    }
    result_str += "\n";
    return result_str;
}