#include "rvm.hpp"

void Rvm::run()
{
     controlUnit.associate(programMemory, basicOperations, dataPath);
}