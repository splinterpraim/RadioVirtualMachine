/**
 * @file rvm.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Radio Virtual Machine
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_CLASS
#define RVM_CLASS

#include <vector>
#include <string>

#include "CU/rvm_control_unit.hpp"
#include "rvm_program_memory.hpp"
#include "rvm_basic_operations.hpp"
#include "rvm_data_path.hpp"
#include "common.hpp"

/**
 * @brief Radio Virtual Machine class implementation
 */
class Rvm
{
public:

    /**
     * @brief Constructs a new Rvm object
     */
    Rvm();

    void addRLOperator(uint32_t opcode, rl_operator_fn opFn);

    void addRVMOperator(std::string opName,uint8_t* cc, size_t cc_size, const std::map<int, std::string> &map);

    void addProgram(const uint8_t* cc, size_t cc_size);


    /**
     * @brief Launches the Radio Virtual Machine 
     */
    void run();
    void run(const std::vector<array_t>& externalInputDO, const std::vector<array_t>& externalOutputDO);

    void show();

private:

    rvm_ControlUnit controlUnit;                /* Control Unit Block */
    rvm_ProgramMemory programMemory;        /* Program Memory Block */
    rvm_BasicOperations basicOperations;    /* Basic Operations Block */
    rvm_DataPath dataPath;                  /* Data Path */
    std::vector<std::string> cfgFileNames;  /* Configcode files name */
};

#endif // RVM_CLASS