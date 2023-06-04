/**
 * @file rvm.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Radio Virtual Machine
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "rvm.hpp"

Rvm::Rvm()
{
   controlUnit.associate(programMemory, basicOperations, dataPath);
}


void Rvm::run()
{
   controlUnit.work();
}
void Rvm::run(const std::vector<array_t>& externalInputDO, const std::vector<array_t>& externalOutputDO)
{
   controlUnit.addExternals(externalInputDO, externalOutputDO);
}

void Rvm::addRLOperator(uint32_t opcode, rl_operator_fn opFn)
{
   basicOperations.addRLOperator(opcode, opFn);
}

void Rvm::addRVMOperator(std::string opName,uint8_t* cc, size_t cc_size, const std::map<int, std::string> &map)
{
   basicOperations.addRVMOperator(opName, cc, cc_size, map);
}

void Rvm::addProgram(const uint8_t* cc, size_t cc_size)
{
   programMemory.loadFromArray(cc, cc_size);
}


void Rvm::show()
{
   basicOperations.show();
}
