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
    /* Stage Fetch */
    LLOG(LogLevels::FIRST, std::cout << "STAGE FETCH" << std::endl)
    ConfigObjects *cfgCode = cfgFetcher.fetch(cfgCounter);
    uint64_t lastCfgAddr = cfgFetcher.getLastAddress();
    (void)lastCfgAddr; /* fix warn */
    LLOG(LogLevels::SECOND, showConfigObjects((*cfgCode)))

    /* Stage Configure */
    LLOG(LogLevels::FIRST, std::cout << "STAGE CONFIGURE" << std::endl)
    cfgnBlock.configure(*cfgCode);
    LLOG(LogLevels::SECOND, rvm_DataPathShow(*dataPath))

    LLOG(LogLevels::FIRST, std::cout << "STAGE RUN" << std::endl)
    cfgnBlock.runDataPath();
    LLOG(LogLevels::SECOND, rvm_DataPathShow(*dataPath))
    LLOG(LogLevels::FIRST, std::cout << "STAGE FINISH" << std::endl)

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