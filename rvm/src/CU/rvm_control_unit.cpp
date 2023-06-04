/**
 * @file rvm_control_unit.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Control Unit
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "CU/rvm_control_unit.hpp"

#include <thread>
#include <functional>
#include <exception>
#include <stdexcept>

#include "config_code_structure.hpp"
#include "rvm_glob_define.hpp"
#include "rvm_program_memory.hpp"
#include "rvm_basic_operations.hpp"
#include "rvm_data_path.hpp"

rvm_ControlUnit::~rvm_ControlUnit() { }

void rvm_ControlUnit::addExternals(const std::vector<array_t>& externalInputDO, const std::vector<array_t>& externalOutputDO)
{
    if(!dataPath)
    {
        throw std::runtime_error("Data path is not accossiate with Control Unit");
    }
    // dataPath->dataObjsExt();
}


void rvm_ControlUnit::work()
{
    bool finished = false;
    while (!finished)
    {
        /* Stage Fetch */
        LLOG(LogLevels::FIRST, std::cout << "STAGE FETCH" << std::endl)
        ConfigObjects &cfgCode = cfgFetcher.fetch(cfgCounter);
        uint64_t lastCfgAddr = cfgFetcher.getLastAddress();
        uint32_t sizeCC = lastCfgAddr - cfgCounter;
        uint8_t f_LCF = cfgCode.controlSection.LCF;
        uint8_t f_NAF = cfgCode.controlSection.NAF;
        uint16_t NCAO = cfgCode.NCAO;
        LLOG(LogLevels::SECOND, showConfigObjects(cfgCode))

        /* Stage Configure */
        LLOG(LogLevels::FIRST, std::cout << "STAGE CONFIGURE" << std::endl)
        // запустить hendler 

        bool f_terminateQueueDO = false;
        bool f_terminateQueueAPE = false;
        std::thread t_handleQueueDO(&rvm_ControlUnit::handleQueueDO, this, std::ref(f_terminateQueueDO));
        std::thread t_handleQueueAPE(&rvm_ControlUnit::handleQueueAPE, this, std::ref(f_terminateQueueAPE));
        std::thread t_configureAndRun(&rvm_dataPathConfigurationBlock::configureAndRun,&cfgnBlock, std::ref(cfgCode));

        /* Stage Run */

        cfgnBlock.clear();
        t_configureAndRun.join();
        
        f_terminateQueueDO = true;
        f_terminateQueueAPE = true;
        qDO.push(StatusFromDataObject()); /* notify queue DO */
        qAPE.push(StatusFromAbstractProcessingElement()); /* notify queue DO */
        t_handleQueueDO.join();
        t_handleQueueAPE.join();

        /* Next Address Block */
        if (f_LCF)
        {
            finished = true;
        }
        else
        {
            /* Next CC address offset */
            if (f_NAF)
            {
                cfgCounter += NCAO;
            }
            else
            {
                cfgCounter += sizeCC + 1;  /* incorrect */
            }
        }

        
    }

}

void rvm_ControlUnit::associate(rvm_ProgramMemory &programMemory, rvm_BasicOperations &basicOperations, rvm_DataPath &dataPath)
{
    this->programMemory = &programMemory;
    this->basicOperations = &basicOperations;
    this->dataPath = &dataPath;

    /* Stage Associate */
    cfgFetcher.associate(*(this->programMemory));
    cfgnBlock.associate(*(this->dataPath), opFetcher, qDO, qAPE);
}

void rvm_ControlUnit::handleQueueDO(bool &terminateSignal)
{
    while(true)
    {
        StatusFromDataObject statusDO;
        qDO.wait_and_pop(statusDO);

        /* Exit on external signal */
        if (terminateSignal == true)
        {
            return;
        }
        std::cout << "(DO status log) >" << statusDO.to_str() << std::endl;
        /* Exit on DO errors */
        if (statusDO.exception != 0)
        {
            std::string errMsg = std::string(RVM_ERR_STR("status DO err"));
            throw std::runtime_error(errMsg);
        }
    }

}

void rvm_ControlUnit::handleQueueAPE(bool &terminateSignal)
{
        while(true)
    {
        StatusFromAbstractProcessingElement statusAPE;
        qAPE.wait_and_pop(statusAPE);

        /* Exit on external signal */
        if (terminateSignal == true)
        {
            return;
        }
        std::cout << "(APE status log) >" << statusAPE.to_str() << std::endl;
        /* Exit on DO errors */
        if (statusAPE.exception != 0)
        {
            std::string errMsg = std::string(RVM_ERR_STR("status APE err"));
            throw std::runtime_error(errMsg);
        }
    }
}
