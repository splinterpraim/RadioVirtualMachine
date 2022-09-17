

#include <iostream>
#include <exception>
#include <stdexcept>
#include "rvm_program_mem.hpp"
#include "rvm_glob_define.h"

void RUN_TESTS_rvm_ProgramMemory()
{
    rvm_ProgramMemory pMem;

    pMem.init(0);
    pMem.load("/home/xivvxx/buff/cfgfile");
    // progMem.load("/home/xivvxx/buff/cfgfile2");
    // progMem.load("/home/xivvxx/buff/cfgfile3");
    std::cout << pMem.get(0) << std::endl;
}

int main(int argc, char *argv[])
{
    try
    {
        RUN_TESTS_rvm_ProgramMemory();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}