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

#define NOT_FOUND_APE -1

/* Iterates over the processing ports related with a specific data port 
    dPort_i - Input Index of specific data port 
    pPort_i - Output Index of related processing ports */
#define ITERATE_OVER_PROCESSING_PORTS_RELATED_WITH_DATA_PORT(dPort_i, pPort_i) \
        for (pPort_i = getFirstRelatedProcessingPort(dPort_i);  pPort_i < processingPorts.size() ; pPort_i = getNextRelatedProcessingPort(dPort_i, pPort_i))

#define ITERATE_OVER_PROCESSING_PORTS_RELATED_WITH_APE(APE_id, pPort_i) \
        for (pPort_i = getFirstProcessingPortRelatedWithAPE(APE_id);  pPort_i < processingPorts.size() ; pPort_i = getNextProcessingPortRelatedWithAPE(APE_id, pPort_i))


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

size_t AbstractSwitchFabric::getFirstRelatedProcessingPort(size_t dPort_i)
{
    /* Find the first connector related with an data port */
    for (auto &contr : connectors)
    {
        /* Return processing port id from founded connector */
        if (contr.dataPortId == dPort_i)
        {
            return contr.processingPortId;
        }
    }
    return processingPorts.size();
}

size_t AbstractSwitchFabric::getNextRelatedProcessingPort(size_t dPort_i, size_t pPort_i)
{
    bool startConnectorFound = false;

    /* Find the connector related with an data port since of specific processing port */
    for (auto &contr : connectors)
    {
        /* Find start connector that contains a specific data port and a specific processing port */
        if ( !startConnectorFound )
        {
            if ( ( contr.dataPortId == dPort_i) && (contr.processingPortId == pPort_i) )
            {
                startConnectorFound = true;
            }
        }
        /* Return next processing port id from founded connector */
        else if ( contr.dataPortId == dPort_i )
        {
             return contr.processingPortId;
        }
    }
    return processingPorts.size();
}

size_t AbstractSwitchFabric::getFirstProcessingPortRelatedWithAPE(size_t APE_id)
{
    /* Find the first processing port related with an APE */
    for (size_t pPort_i = 0; pPort_i < processingPorts.size(); pPort_i++)
    {
        /* Return processing port index */
        if (processingPorts[pPort_i].relatedAPE->getId() == APE_id)
        {
            return pPort_i;
        }
    }
    return processingPorts.size();
}

size_t AbstractSwitchFabric::getNextProcessingPortRelatedWithAPE(size_t APE_id, size_t pPort_i)
{
    bool startPPortFound = false;

    /* Find the processing port related with an APE since of specific processing port */
    for (size_t i = pPort_i + 1; i < processingPorts.size(); i++)
    {
        /* Return processing port index */
        if (processingPorts[i].relatedAPE->getId() == APE_id)
        {
             return i;
        }
    }
    return processingPorts.size();
}


void AbstractSwitchFabric::askDOAndNotifyAPE_DataEnable()
{
    size_t dPort_i = 0;     /* Data ports index */
    size_t pPort_i = 0;     /* Processing ports index */

    /* Ask DOs */
    for (auto &dPort : dataPorts)
    {
        /* Get data enable */
        auto dEnable = dPort.relatedDO->dataEnable();

        /* Notify related APEs */
        ITERATE_OVER_PROCESSING_PORTS_RELATED_WITH_DATA_PORT(dPort_i, pPort_i)
        {
            ProcessingPort &pPort = processingPorts[pPort_i];
            pPort.relatedAPE->dataEnable(pPort.port_number, dEnable);
        }
        dPort_i++;
    }
}

int32_t AbstractSwitchFabric::findAPEReadyToDataTransfer()
{
    for (auto &pPort : processingPorts)
    {
        if(pPort.relatedAPE->portsReadyToTransfer())
        {
            return pPort.relatedAPE->getId();
        }
    }
    return NOT_FOUND_APE;
}



void AbstractSwitchFabric::askAPEAndNotifyDO_AccessType(int32_t APE_id)
{
    size_t pPort_i = 0;     /* Processing ports index */

    ITERATE_OVER_PROCESSING_PORTS_RELATED_WITH_APE(APE_id, pPort_i)
    {
        ProcessingPort &pPort = processingPorts[pPort_i];

        /* Ask APE access type */
        auto at = pPort.relatedAPE->accessType(pPort.port_number);

        auto &contr = findConnectorByProccessingPortId(pPort_i);

        /* Access type matching check */
        if (at != contr.dir)
        {
            throw std::runtime_error(RVM_ERR_STR("access type and direction of connector mismatch for found APE"));
        }

        /* Notify DO about access type */
        dataPorts[contr.dataPortId].relatedDO->accessType(at);
    }
}


/* Public */

AbstractSwitchFabric::~AbstractSwitchFabric() { }

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

    while (!finish)
    {
        /* Data Enable */
        askDOAndNotifyAPE_DataEnable();

        auto APE_id = findAPEReadyToDataTransfer();

        if (APE_id != NOT_FOUND_APE)
        {
            /* Access type */
            askAPEAndNotifyDO_AccessType(APE_id);

            /* Read */
            transferToAPE(APE_id);

            runAPE(APE_id);

            /* Write */
            transferFromAPE(APE_id);
        }
        else
        {
            finish = true;
        }
        


        size_t port_i = 0;
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