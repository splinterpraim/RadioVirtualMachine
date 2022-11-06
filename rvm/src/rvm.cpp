#include "rvm.hpp"

void Rvm::run()
{
     controlUnit.associate(programMemory, basicOperations, dataPath);


     // programMemory.init(10);
        // progMem.load("./XML_files/bin/cfg1.bin");
     programMemory.load("./config_codes/cfgcode1.bin");
     
     controlUnit.work();
     
}