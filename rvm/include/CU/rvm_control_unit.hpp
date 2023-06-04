/**
 * @file rvm_control_unit.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Control Unit
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_CONTROL_UNIT_CLASS
#define RVM_CONTROL_UNIT_CLASS

#include <iostream>

#include "CU/rvm_cfg_code_fetcher.hpp"
#include "CU/rvm_data_path_configuration_block.hpp"
#include "CU/rvm_operation_fetcher.hpp"
#include "CU/rvm_threadsafe_queue.hpp"
#include "rvm_structs.h"
#include"common.hpp"

class rvm_ProgramMemory;    /* Forward declaration of rvm_ProgramMemory class */
class rvm_BasicOperations;  /* Forward declaration of rvm_BasicOperations class */
struct rvm_DataPath_s;                          /* Forward declaration of rvm_DataPath struct */
using rvm_DataPath = struct rvm_DataPath_s;

/**
 * @brief Control Unit class implementation
 */
class rvm_ControlUnit
{
public:

    /**
     * @brief Destroys the Control Unit object
     */
    ~rvm_ControlUnit();

    void addExternals(const std::vector<array_t>& externalInputDO, const std::vector<array_t>& externalOutputDO);

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

    void handleQueueDO(bool &terminateSignal);
    void handleQueueAPE(bool &terminateSignal);
private:

    uint32_t cfgCounter = 0;                    /* Config code counter */
    rvm_cfgCodeFetcher cfgFetcher;              /* Config code Fetcher Block */
    rvm_dataPathConfigurationBlock cfgnBlock;   /* Data Path Configuration Block */
    rvm_operationFetcher opFetcher;             /* Operation Fetcher Block */
    rvm_ThreadsafeQueue<StatusFromDataObject> qDO;  /* Queue for receive statuses from DOs */
    rvm_ThreadsafeQueue<StatusFromAbstractProcessingElement> qAPE;  /* Queue for receive statuses from APEs */

    /* External Relations */
    rvm_ProgramMemory * programMemory  = nullptr;       /* Externally related Program memory */
    rvm_BasicOperations * basicOperations  = nullptr;   /* Externally related Basic Operations Block */
    rvm_DataPath * dataPath  = nullptr;                 /* Externally related Data Path */
};

#endif // RVM_CONTROL_UNIT_CLASS
