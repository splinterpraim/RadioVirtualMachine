#include "CU/control_unit.h"

// using namespace rvm;

rvm::ControlUnit::~ControlUnit()
{
    delete[] dataObjects;
    delete[] abstractProcessingElements;
    delete abstractSwitchFabric;
}

int rvm::ControlUnit::configuringDataObjects()
{
    LogManager("DO.log").clear();

    uint8_t binFileData[11] = {'v', 'e', 'c', 't', 'o', 'r', '.', 't', 'x', 't', '\n'};
    uint8_t binData[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    /* Allocate mem */
    dataObjects = new DataObject[dataObjects_size];

    /* Do setting, initialazing */
    for (size_t i = 0; i < dataObjects_size; i++)
    {
        dataObjects[i].setSendControlUnit(*this);
        dataObjects[i].set(i + 1, dataObjects_size, 0);
        dataObjects[i].init(*binFileData, 255);
    }
    // dataObjects[0].init(*binData, dataObjects_size - 2);
    // dataObjects[1].init(*binData, dataObjects_size);

    for (size_t i = 0; i < dataObjects_size; i++)
    {
        LogManager("DO.log").makeLog(dataObjects[i].to_str());
        // dataObjects[i].checkCallBack();
        // showStatus();
    }
    delete[] dataObjects;
    return 0;
}

int rvm::ControlUnit::configuringAbstractProcessingElements()
{

    // data
    uint8_t binData[11] = {'v', 'e', 'c', 't', 'o', 'r', '.', 't', 'x', 't', '\n'};

    abstractProcessingElements = new AbstractProcessingElement[abstractProcessingElements_size];
    for (size_t i = 0; i < abstractProcessingElements_size; i++)
    {
        abstractProcessingElements[i].setSendControlUnit(*this);
        abstractProcessingElements[i].setID(i + 1, 2);
        for (size_t j = 0; j < 2; j++)
        {
            abstractProcessingElements[i].set(j, 0, 1, 1);
        }
    }
    abstractProcessingElements[0].init(0, radiolib::sum);
    for (size_t i = 0; i < abstractProcessingElements_size; i++)
    {
        LogManager().makeLog(abstractProcessingElements[i].to_str());
    }
    abstractProcessingElements[0].doOperation();
    delete[] abstractProcessingElements;
    return 0;
}

int rvm::ControlUnit::configuringAbstractSwitchFabric()
{
    /* Create ASF */
    abstractSwitchFabric = new AbstractSwitchFabric;

    /* Counting the total number of all ports APE */
    int numPortsAPE = countPortsAllAPE();

    /* Set ASF */
    {
        /* Create data and processing ports (empty) */
        abstractSwitchFabric.set(dataObjects_size, numPortsAPE);

        /* Create connectors loop */
        for (range DO_N : i)
        {
            /* Read current ASF config */
            record = readASFconfig(i);

            /* Range on related APE */
            for (range record.N : j)
            {
                dir = getDirectionFromAPE(APE_ID = record.APE_part[j].ape_id, portNum = record.APE_part[j].port_num);

                /* Create connectors between data ports (dataId) and next available processing ports  */
                abstractSwitchFabric.createConnector(dataId = i, dir);
            }
        }
    }

    /* Init ASF */
    {
        /* Associate DO and data ports*/
        {
            for (range DO_N : i)
            {
                abstractSwitchFabric.associateDataPort(dataPortId = i, DO = &dataObjects[i]);
            }
        }

        /* Associate APE and processing ports*/
        {
            counterAPEPort = 0;
            
            for (range DO_N : i)
            {
                /* Read current ASF config */
                record = readASFconfig(i);

                /* Range on related APE */
                for (range record.N : j)
                {
                    /* Create connectors between data ports (dataId) and next available processing ports  */
                    abstractSwitchFabric.associateProccessingPort(processingPortId = counterAPEPort, APE = &record.APE_part[j].ape_id);
                    counterAPEPort++;
                }
                
            }
        }
    }
}

void rvm::ControlUnit::sendStatusFromDataObject(const StatusFromDataObject &statusDO)
{
    if (statusDO.exception != 0)
    {
        std::cout << "error" << std::endl;
    }
}

void rvm::ControlUnit::sendStatusFromAbstractProcessingElement(const StatusFromAbstractProcessingElement &statusAPE)
{
    if (statusAPE.exception != 0)
    {
        std::cout << "error" << std::endl;
    }
}

// int ControlUnit::monitoringDataObjects(struct StatusFromDataObject currentStatus)
// {
//     if (currentStatus.exception != 0)
//     {
//         std::cout << "error" << std::endl;
//     }
//     return 0;
// }

// namespace rvm{

// }