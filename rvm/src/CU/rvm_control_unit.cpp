/**
 * @file rvm_control_unit.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Control Unit
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "CU/rvm_control_unit.hpp"

#include "config_code_structure.hpp"
#include "rvm_glob_define.hpp"

#include "rvm_program_memory.hpp"
#include "rvm_basic_operations.hpp"
#include "rvm_data_path.hpp"

ControlUnit::~ControlUnit() { }

void ControlUnit::work()
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
        cfgnBlock.configure(cfgCode);
        LLOG(LogLevels::SECOND, rvm_DataPathShow(*dataPath))

        /* Stage Run */
        LLOG(LogLevels::FIRST, std::cout << "STAGE RUN" << std::endl)
        cfgnBlock.runDataPath();
        LLOG(LogLevels::SECOND, rvm_DataPathShow(*dataPath))
        LLOG(LogLevels::FIRST, std::cout << "STAGE FINISH" << std::endl)

        cfgnBlock.clear();
        

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

void ControlUnit::associate(rvm_ProgramMemory &programMemory, rvm_BasicOperations &basicOperations, rvm_DataPath &dataPath)
{
    this->programMemory = &programMemory;
    this->basicOperations = &basicOperations;
    this->dataPath = &dataPath;

    /* Stage Associate */
    cfgFetcher.associate(*(this->programMemory));
    cfgnBlock.associate(*(this->dataPath), opFetcher);
}