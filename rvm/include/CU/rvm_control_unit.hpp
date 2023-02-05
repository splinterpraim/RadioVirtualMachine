/**
 * @file rvm_control_unit.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Control Unit
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_CONTROL_UNIT_CLASS
#define RVM_CONTROL_UNIT_CLASS

/* C++ Headers */
#include <iostream>

/* Project Headers */
#include "class_definition.h"
#include "rvm_structs.h"
#include "CU/rvm_cfg_code_fetcher.hpp"
#include "CU/rvm_data_path_configuration_block.hpp"
#include "CU/rvm_operation_fetcher.hpp"

#include "DO/data_object.h"
#include "APE/abstract_processing_element.hpp"
#include "ASF/abstract_switch_fabric.hpp"


#include "rvm_program_mem.hpp"
#include "rvm_basic_operations.hpp"
#include "rvm_data_path.hpp"


/**
 * @brief Control Unit class implementation
 */
class ControlUnit
{
public:

    /**
     * @brief Destroys the Control Unit object
     */
    ~ControlUnit();

    /**
     * @brief Launches the Control Unit for main work
     */
    void work();

    /**
     * @brief Associates Control Unit with other related blocks
     *
     * @param[in]       programMemory           Reference to related program memory
     * @param[in]       basicOperations         Reference to related basic operations block
     * @param[in]       dataPath                Reference to related data path
     */
    void associate(rvm_ProgramMemory &programMemory, rvm_BasicOperations &basicOperations, rvm_DataPath & dataPath);

private:

    uint32_t cfgCounter = 0;                    /* Config code counter */
    rvm_cfgCodeFetcher cfgFetcher;              /* Config code Fetcher Block */
    rvm_dataPathConfigurationBlock cfgnBlock;   /* Data Path Configuration Block */
    rvm_operationFetcher opFetcher;             /* Operation Fetcher Block */

    /* External Relations */
    rvm_ProgramMemory * programMemory  = nullptr;       /* Externally related Program memory */
    rvm_BasicOperations * basicOperations  = nullptr;   /* Externally related Basic Operations Block */
    rvm_DataPath * dataPath  = nullptr;                 /* Externally related Data Path */
};

#endif // RVM_CONTROL_UNIT_CLASS
