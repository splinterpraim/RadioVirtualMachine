
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
    dataPath->dataObjs.resize(doSec.N_DO); // = new DataObject[doSec.N_DO];

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
}
void rvm_dataPathConfigurationBlock::configureAbstractProcessingElements(ConfigObjects &cfgCode)
{
    APE_Section &apeSec = cfgCode.apeSection;
    dataPath->apes.resize(apeSec.N_APE);

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
