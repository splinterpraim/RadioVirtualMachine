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
    int numPortsAPE = countPortsAllAPE(); // plugs countPortsAllAPE()
    int numPortsDO = countPortsAllDO();   // plugs countPortsAllAPE()

    /* Set ASF */
    {
        /* Create data and processing ports (empty) */
        abstractSwitchFabric->set(numPortsDO, numPortsAPE);

        /* Create connectors loop */
        for (int i = 0; i < numPortsDO; i++)
        {
            /* Read current ASF config */
            struct ASF_Config record = readASFconfig(i);

            /* Range on related APE */
            for (int j = 0; j < record.N; j++)
            {
                int dir = getDirectionFromAPE(record.APE_KP[j].APE_number,record.APE_KP[j].port_number);

                /* Create connectors between data ports (dataId) and next available processing ports  */
                abstractSwitchFabric->createConnector(i, (i + j), dir); // other approach to identify connectors without i , i + j
            }
            //************************************************************************************************
             delete [] record.APE_KP;
            //************************************************************************************************
        }
    }

    /* Init ASF */
    // {
    //     /* Associate DO and data ports*/
    //     {
    //         for (range DO_N : i)
    //         {
    //             abstractSwitchFabric.associateDataPort(dataPortId = i, DO = &dataObjects[i]);
    //         }
    //     }

    //     /* Associate APE and processing ports*/
    //     {
    //         counterAPEPort = 0;

    //         for (range DO_N : i)
    //         {
    //             /* Read current ASF config */
    //             record = readASFconfig(i);

    //             /* Range on related APE */
    //             for (range record.N : j)
    //             {
    //                 /* Create connectors between data ports (dataId) and next available processing ports  */
    //                 abstractSwitchFabric.associateProccessingPort(processingPortId = counterAPEPort, APE = &record.APE_part[j].ape_id);
    //                 counterAPEPort++;
    //             }

    //         }
    //     }
    // }
    return 0;
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

/// plugs
int countPortsAllAPE()
{
    return 9;
}

int countPortsAllDO()
{
    return 7;
}

struct ASF_Config readASFconfig(int index)
{
    struct ASF_Config asfConfig;

    /* DO =  d1 */
    if (index == 0)
    {
        asfConfig.DO = 0;
        asfConfig.N = 1;
        /* ASF_variable_part */
        {
            asfConfig.APE_KP = new struct ASF_variable_part[asfConfig.N];
            asfConfig.APE_KP[0].APE_number = 0;
            asfConfig.APE_KP[0].port_number = 0;
        }
    }

    /* DO =  d2 */
    if (index == 1)
    {
        asfConfig.DO = 1;
        asfConfig.N = 1;
        /* ASF_variable_part */
        {
            asfConfig.APE_KP = new struct ASF_variable_part[asfConfig.N];
            asfConfig.APE_KP[0].APE_number = 0;
            asfConfig.APE_KP[0].port_number = 1;
        }
    }

    /* DO =  d3 */
    if (index == 2)
    {
        asfConfig.DO = 2;
        asfConfig.N = 1;
        /* ASF_variable_part */
        {
            asfConfig.APE_KP = new struct ASF_variable_part[asfConfig.N];
            asfConfig.APE_KP[0].APE_number = 1;
            asfConfig.APE_KP[0].port_number = 0;
        }
    }

    /* DO =  d4 */
    if (index == 3)
    {
        asfConfig.DO = 3;
        asfConfig.N = 1;
        /* ASF_variable_part */
        {
            asfConfig.APE_KP = new struct ASF_variable_part[asfConfig.N];
            asfConfig.APE_KP[0].APE_number = 1;
            asfConfig.APE_KP[0].port_number = 1;
        }
    }

    /* DO =  d5 */
    if (index == 4)
    {
        asfConfig.DO = 4;
        asfConfig.N = 2;
        /* ASF_variable_part */
        {
            asfConfig.APE_KP = new struct ASF_variable_part[asfConfig.N];
            asfConfig.APE_KP[0].APE_number = 0;
            asfConfig.APE_KP[0].port_number = 2;
            asfConfig.APE_KP[1].APE_number = 2;
            asfConfig.APE_KP[1].port_number = 0;
        }
    }

    /* DO =  d6 */
    if (index == 5)
    {
        asfConfig.DO = 5;
        asfConfig.N = 2;
        /* ASF_variable_part */
        {
            asfConfig.APE_KP = new struct ASF_variable_part[asfConfig.N];
            asfConfig.APE_KP[0].APE_number = 1;
            asfConfig.APE_KP[0].port_number = 2;
            asfConfig.APE_KP[1].APE_number = 2;
            asfConfig.APE_KP[1].port_number = 1;
        }
    }

    /* DO =  d7 */
    if (index == 6)
    {
        asfConfig.DO = 5;
        asfConfig.N = 1;
        /* ASF_variable_part */
        {
            asfConfig.APE_KP = new struct ASF_variable_part[asfConfig.N];
            asfConfig.APE_KP[0].APE_number = 2;
            asfConfig.APE_KP[0].port_number = 2;
        }
    }

    return asfConfig;
}

int getDirectionFromAPE(uint8_t APE_number, uint8_t port_number)
{
    /* return - 0 - from data port to processing port,
                                   1 - from processing port to data port */
    if ((APE_number == 0) || (APE_number == 1) ||  (APE_number == 2))
    {
        if((port_number == 0) || (port_number == 1))
        {
            return 0; 
        }
        else if(port_number == 2)
        {
            return 1; 
        }
    }

}