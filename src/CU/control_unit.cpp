#include "CU/control_unit.h"

// using namespace rvm;
int rvm::ControlUnit::configuringDataObjects()
{
    // int dataObjects_size = 10;
    // DataObject dataObjects[dataObjects_size];

    // data
    uint8_t binData[11] = {'v', 'e', 'c', 't', 'o', 'r', '.', 't', 'x', 't', '\n'};

    dataObjects = new DataObject[dataObjects_size];
    for (size_t i = 0; i < dataObjects_size; i++)
    {
        dataObjects[i].setSendControlUnit(*this);
        dataObjects[i].set(i, 4, i);
        // dataObjects[i].init(*binData,2);
        // dataObjects[i].setSendStatusFunction(sendStatusDO);
        // dataObjects[i].setID(i);

        // dataObjects[i].set();
        // dataObjects[i].init();
    }
    dataObjects[0].init(*binData, 255);
    for (size_t i = 0; i < dataObjects_size; i++)
    {
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
    }
    abstractProcessingElements[0].init(0,radiolib::sum);
    // dataObjects[0].init(*binData, 255);
    for (size_t i = 0; i < abstractProcessingElements_size; i++)
    {
        abstractProcessingElements[i].checkCallBack();
    }
    // delete[] abstractProcessingElements;
    return 0;
}

void rvm::ControlUnit::sendStatusFromDataObject(const StatusFromDataObject &statusDO)
{
    statusDO.show();

    if (statusDO.exception != 0)
    {
        std::cout << "error" << std::endl;
    }
}

void rvm::ControlUnit::sendStatusFromAbstractProcessingElement(const StatusFromAbstractProcessingElement &statusAPE)
{
    statusAPE.show();

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