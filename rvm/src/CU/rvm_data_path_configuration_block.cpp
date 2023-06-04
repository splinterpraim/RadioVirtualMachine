/**
 * @file rvm_data_path_configuration_block.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Data Path Configuration Block
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "CU/rvm_data_path_configuration_block.hpp"

#include <iostream>
#include <vector>
#include <cstring>

#include "common.hpp"
#include "rvm_glob_define.hpp"
#include "system_func.hpp"
#include "config_code_structure.hpp"
#include "rvm_structs.h"
#include "rvm_data_path.hpp"
#include "CU/rvm_operation_fetcher.hpp"
#include "DO/data_object.hpp"
#include "APE/abstract_processing_element.hpp"
#include "ASF/abstract_switch_fabric.hpp"

/* Private */

void rvm_dataPathConfigurationBlock::configureDataObjects(ConfigObjects &cfgCode)
{
    DO_Section &doSec = cfgCode.doSection;
    dataPath->dataObjs.resize(doSec.N_DO); // = new DataObject[doSec.N_DO];

    for (size_t i = 0; i < doSec.N_DO; ++i)
    {
        dataPath->dataObjs[i].associate(*this, *qDO);
        dataPath->dataObjs[i].set(doSec.DOs[i].DO_ID, doSec.DOs[i].size, doSec.DOs[i].access_time);
        if ( doSec.DOs[i].data )
        {
            if(endianIsLittle())
            {
                int tmpData0 = 0;
                std::memcpy((void *)&tmpData0, (const void *) doSec.DOs[i].data, sizeof(tmpData0));

                int tmpData1= reverseEndian(tmpData0, 4);
                std::memcpy((void *)doSec.DOs[i].data, (const void *)&tmpData1, sizeof(tmpData1));

            }
        }
        dataPath->dataObjs[i].init(*(doSec.DOs[i].data), doSec.DOs[i].length); //! len > size
        if (errorHand)
        {
            throw std::runtime_error(RVM_ERR_STR("Configuring Data Objects failed!"));
        }
    }
}

void rvm_dataPathConfigurationBlock::configureAbstractProcessingElements(ConfigObjects &cfgCode)
{
    APE_Section &apeSec = cfgCode.apeSection;
    dataPath->apes.resize(apeSec.N_APE);

    for (size_t i = 0; i < apeSec.N_APE; ++i)
    {
        dataPath->apes[i].associate(*this, *qAPE);

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
        int cntPortsDO = 0;
        int cntPortsAPE = 0;

        /* Loop to create connectors  */
        for (int i = 0; i < numPortsDO; i++)
        {
            /* Read current ASF config */
            ASF_Config &record = doSec.ASFs[i];
            
            /* Range on related APE */
            for (int j = 0; j < record.N; j++)
            {

                int dir = getDirectionFromAPE(cfgCode, record.APE_KP[j].APE_number, record.APE_KP[j].port_number-1); 

                /* Create connectors between data ports (dataId) and next available processing ports  */
                dataPath->asf->createConnector(cntPortsDO, cntPortsAPE, dir); 
                cntPortsAPE++;
            }
            cntPortsDO++;
        }
    }

    /* Init ASF */
    {
        /* Associate DO and data ports*/
        {
            for (int i = 0; i < numPortsDO; i++)
            {
                dataPath->asf->associateDataPort(i, dataPath->dataObjs[i]);
            }
        }

        /* Associate APE and processing ports*/
        {
            int cntPortsAPE = 0;

            for (int i = 0; i < numPortsDO; i++)
            {
                /* Read current ASF config */
                ASF_Config &record = doSec.ASFs[i];

                /* Range on related APE */
                for (int j = 0; j < record.N; j++)
                {
                    /* Create connectors between data ports (dataId) and next available processing ports  */
                    uint8_t apeIdFind= record.APE_KP[j].APE_number;
                    AbstractProcessingElement * apeFind = nullptr;
                    for (auto& ape : dataPath->apes)
                    {
                        if (ape.getId() == apeIdFind)
                        {
                            apeFind = &ape;
                        }
                    }
                    if (apeFind == nullptr)
                    {
                        throw std::runtime_error(RVM_ERR_STR("APE id not found"));
                    }
                    dataPath->asf->associateProccessingPort(cntPortsAPE, *apeFind, record.APE_KP[j].port_number-1);
                    cntPortsAPE++;
                }

            }
        }
    }
}

int rvm_dataPathConfigurationBlock::getDirectionFromAPE(ConfigObjects &cfgCode, uint8_t APE_Id, uint8_t port_number)
{
    for (size_t i = 0; i < cfgCode.apeSection.N_APE; i++)
    {
        if (cfgCode.apeSection.APEs[i].APE_ID == APE_Id)
        {
            /* Check out of range in port of APE */
            if (port_number > cfgCode.apeSection.APEs[i].NN)
            {
                throw std::runtime_error(RVM_ERR_STR("Incorrect port of APE"));
            }
            return cfgCode.apeSection.APEs[i].access_type[port_number];
        }
    }
    throw std::runtime_error(RVM_ERR_STR("Cannot find APE id "));
    
}

/* Public */

rvm_dataPathConfigurationBlock::rvm_dataPathConfigurationBlock() { }

void rvm_dataPathConfigurationBlock::associate(rvm_DataPath &dataPath, rvm_operationFetcher &opFetcher,rvm_ThreadsafeQueue<StatusFromDataObject> &qDO, rvm_ThreadsafeQueue<StatusFromAbstractProcessingElement> &qAPE)
{
    this->dataPath = &dataPath;
    this->opFetcher = &opFetcher;
    this->qDO = &qDO;
    this->qAPE = &qAPE;
}

void rvm_dataPathConfigurationBlock::configureAndRun(ConfigObjects &cfgCode)
{
    configureDataObjects(cfgCode);
    configureAbstractProcessingElements(cfgCode);
    configureAbstractSwitchFabric(cfgCode);
    //todo: collect status and check it
    LLOG(LogLevels::SECOND, rvm_DataPathShow(*dataPath))
    LLOG(LogLevels::FIRST, std::cout << "STAGE RUN" << std::endl)
    dataPath->asf->run();
    LLOG(LogLevels::SECOND, rvm_DataPathShow(*dataPath))
    LLOG(LogLevels::FIRST, std::cout << "STAGE FINISH" << std::endl)
}

void rvm_dataPathConfigurationBlock::clear()
{
    delete dataPath->asf;
    dataPath->dataObjs.resize(0); /* clear */
    dataPath->apes.resize(0);
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
