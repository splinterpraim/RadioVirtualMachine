#include "rvm.hpp"
Rvm::Rvm(std::vector<std::string> &cfgFileNames)
{
   this->cfgFileNames = cfgFileNames;
}

void Rvm::run()
{
   controlUnit.associate(programMemory, basicOperations, dataPath);

   /* Program memory load */
   for (auto fileName : cfgFileNames)
   {
      programMemory.load(fileName); //"./config_codes/cfgcode1.bin"
   }

   controlUnit.work();
}