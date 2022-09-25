

#include <iostream>
#include <exception>
#include <stdexcept>
#include "rvm_program_mem.hpp"
#include "rvm_glob_define.h"
#include "common.hpp"

#define TEST_GOOD std::cout << __func__ << " is " << SET_GREEN("GOOD") << std::endl;
#define TEST_BAD std::cout << __func__ << " is " << SET_RED("BAD") << std::endl;

void TEST_rvm_ProgramMemory_init0()
{
    rvm_ProgramMemory pMem;

    try
    {
        pMem.init(0);
        TEST_BAD
    }
    catch (const std::exception &e)
    {
        TEST_GOOD
        return;
    }
    // bad test
    throw std::runtime_error("B");
}

void TEST_rvm_ProgramMemory_initPos()
{
    rvm_ProgramMemory pMem;

    try
    {
        pMem.init(10);
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cout << e.what() << std::endl;
        // bad test
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_loadNorm()
{
    rvm_ProgramMemory pMem;

    try
    {
        pMem.init(100);
        pMem.load("/home/xivvxx/buff/cfgfile");
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cerr << e.what() << '\n';
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_loadMoreSize()
{
    rvm_ProgramMemory pMem;

    try
    {
        pMem.init(1);
        pMem.load("/home/xivvxx/buff/cfgfile");
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cerr << e.what() << '\n';
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_loadNoData()
{
    rvm_ProgramMemory pMem;
    try
    {
        pMem.init(1);
        pMem.load("/home/xivvxx/buff/cfgfile3");
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cerr << e.what() << '\n';
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_loadMultData()
{
    rvm_ProgramMemory pMem;
    try
    {
        pMem.init(1);
        pMem.load("/home/xivvxx/buff/cfgfile");
        pMem.load("/home/xivvxx/buff/cfgfile2");
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cerr << e.what() << '\n';
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_getNorm()
{
    rvm_ProgramMemory pMem;
    try
    {
        pMem.init(1);
        pMem.load("/home/xivvxx/buff/cfgfile");
        pMem.get(0);
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cerr << e.what() << '\n';
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_getOutOfRange()
{
    rvm_ProgramMemory pMem;
    try
    {
        pMem.init(1);
        pMem.load("/home/xivvxx/buff/cfgfile");
        pMem.get(100);
        TEST_BAD
    }
    catch (const std::exception &e)
    {
        TEST_GOOD

        return;
    }
    throw std::runtime_error("B");
}

void RUN_TESTS_rvm_ProgramMemory()
{
    try
    {
        TEST_rvm_ProgramMemory_init0();
        TEST_rvm_ProgramMemory_initPos();
        TEST_rvm_ProgramMemory_loadNorm();
        TEST_rvm_ProgramMemory_loadMoreSize();
        TEST_rvm_ProgramMemory_loadMultData();
        TEST_rvm_ProgramMemory_getNorm();
        TEST_rvm_ProgramMemory_getOutOfRange();
    }
    catch (const std::exception &e)
    {
    }
}

int main(int argc, char *argv[])
{
    try
    {
        RUN_TESTS_rvm_ProgramMemory();
    }
    catch (const std::exception &e)
    {
    }
}