
#include "CU/rvm_data_path_configuration_block.hpp"
#include <iostream>
#include <vector>
#include "class_definition.h"
#include "common.hpp"

#include "DO/data_object.h"

rvm_dataPathConfigurationBlock::rvm_dataPathConfigurationBlock()
{
}

void rvm_dataPathConfigurationBlock::associate(rvm_DataPath &dataPath, rvm_operationFetcher &opFetcher)
{
    this->dataPath = &dataPath;
    this->opFetcher = &opFetcher;
}

int rvm_dataPathConfigurationBlock::configure(ConfigObjects &cfgCode)
{
    configureDataObjects(cfgCode);
    configureAbstractProcessingElements(cfgCode);
    configureAbstractSwitchFabric(cfgCode);
    return 0;
}

void rvm_dataPathConfigurationBlock::runDataPath()
{
}

void rvm_dataPathConfigurationBlock::sendStatusFromDataObject(const StatusFromDataObject &statusDO)
{
    if (statusDO.exception != 0)
    {
        errorHand = true;
        std::cout << RVM_ERR_STR("Status error") << std::endl;
    }
}
void rvm_dataPathConfigurationBlock::sendStatusFromAbstractProcessingElement(const StatusFromAbstractProcessingElement &statusAPE)
{
    if (statusAPE.exception != 0)
    {
        errorHand = true;
        std::cout << RVM_ERR_STR("Status error") << std::endl;
    }
}

void rvm_dataPathConfigurationBlock::configureDataObjects(ConfigObjects &cfgCode)
{
    DO_Section &doSec = cfgCode.doSection;
    dataPath->dataObjs = new DataObject[doSec.N_DO];

    for (size_t i = 0; i < doSec.N_DO; ++i)
    {
        dataPath->dataObjs[i].associate(*this);
        dataPath->dataObjs[i].set(doSec.DOs[i].DO_ID, doSec.DOs[i].size, doSec.DOs[i].access_time);
        dataPath->dataObjs[i].init(*(doSec.DOs[i].data), doSec.DOs[i].length); //! len > size
        if (errorHand)
        {
            throw std::runtime_error(RVM_ERR_STR("Configuring Data Objects failed!"));
        }
    }

    for (size_t i = 0; i < doSec.N_DO; ++i)
    {
        std::cout << dataPath->dataObjs[i].to_str() << std::endl;
    }
}
void rvm_dataPathConfigurationBlock::configureAbstractProcessingElements(ConfigObjects &cfgCode)
{
    APE_Section &apeSec = cfgCode.apeSection;
    dataPath->apes = new AbstractProcessingElement[apeSec.N_APE];

    for (size_t i = 0; i < apeSec.N_APE; ++i)
    {
        dataPath->apes[i].associate(*this);

        /* Prepares portAccessType data */
        std::vector<uint8_t> portsAccessType;
        for (size_t j = 0; j < apeSec.APEs[i].NN; ++j)
        {
            portsAccessType.push_back(apeSec.APEs[i].access_type[j]);
        }
        /* Gets operation func */
        int (*operation)(uint8_t argc, ...);
        opFetcher->getOpFunc(apeSec.APEs[i].op_code, &operation);
        
        /* Sets & inits */
        dataPath->apes[i].set(apeSec.APEs[i].APE_ID, apeSec.APEs[i].cost, apeSec.APEs[i].time, apeSec.APEs[i].T, portsAccessType);
        dataPath->apes[i].init(apeSec.APEs[i].op_code, operation);
        if (errorHand)
        {
            throw std::runtime_error(RVM_ERR_STR("Configuring Data Objects failed!"));
        }
    }

    for (size_t i = 0; i < apeSec.N_APE; ++i)
    {
        std::cout << dataPath->apes[i].to_str() << std::endl;
    }
}
void rvm_dataPathConfigurationBlock::configureAbstractSwitchFabric(ConfigObjects &cfgCode)
{
    DO_Section &doSec = cfgCode.doSection;
    APE_Section &apeSec = cfgCode.apeSection;

    /* Create ASF */
    dataPath->asf = new AbstractSwitchFabric;

    /* Counting the total number of all ports APE */
    int numPortsDO = doSec.N_DO; 
    int numPortsAPE = 0; 
    for (size_t i = 0; i < apeSec.N_APE; i++)
    {
        numPortsAPE += apeSec.APEs[i].NN;
    }

    /* Set ASF */
    {
        /* Creates data and processing ports (empty) */
        dataPath->asf->set(numPortsDO, numPortsAPE);

        /* Loop to create connectors  */
        for (int i = 0; i < numPortsDO; i++)
        {
            /* Read current ASF config */
            ASF_Config &record = doSec.ASFs[i];

            /* Range on related APE */
            for (int j = 0; j < record.N; j++)
            {

                int dir = getDirectionFromAPE(record.APE_KP[j].APE_number, record.APE_KP[j].port_number);

                /* Create connectors between data ports (dataId) and next available processing ports  */
                dataPath->asf->createConnector(i, (i + j), dir); // other approach to identify connectors without i , i + j
            }
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
}