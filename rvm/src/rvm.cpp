/**
 * @file rvm.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Radio Virtual Machine
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "rvm.hpp"

Rvm::Rvm(std::vector<std::string> &cfgFileNames)
{
   this->cfgFileNames = cfgFileNames;
}

void Rvm::run()
{
   /* Stage associate */
   controlUnit.associate(programMemory, basicOperations, dataPath); //todo: replace to constructor

   /* Program memory load */
   for (auto fileName : cfgFileNames)
   {
      programMemory.load(fileName); //"./config_codes/cfgcode1.bin"
   }

   controlUnit.work();
}