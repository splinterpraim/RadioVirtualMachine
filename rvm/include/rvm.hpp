#ifndef RVM_CLASS
#define RVM_CLASS

#include "CU/control_unit.h"
#include "rvm_program_mem.hpp"
#include "rvm_basic_operations.hpp"
#include "rvm_data_path.hpp"


class Rvm
{

public:
    void run();

private:
    rvm::ControlUnit controlUnit;
    rvm_ProgramMemory programMemory;
    rvm_BasicOperations basicOperations;
    rvm_DataPath dataPath;
    // progmem
    // basic op
    // datapath
};

#endif // RVM_CLASS