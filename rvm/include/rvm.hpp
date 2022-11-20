#ifndef RVM_CLASS
#define RVM_CLASS

#include <vector>
#include <string>

#include "CU/control_unit.h"
#include "rvm_program_mem.hpp"
#include "rvm_basic_operations.hpp"
#include "rvm_data_path.hpp"


class Rvm
{

public:
    Rvm(std::vector<std::string> &cfgFileNames);
    void run();

private:
    ControlUnit controlUnit;
    rvm_ProgramMemory programMemory;
    rvm_BasicOperations basicOperations;
    rvm_DataPath dataPath;
    // progmem
    // basic op
    // datapath
    std::vector<std::string> cfgFileNames;

};

#endif // RVM_CLASS