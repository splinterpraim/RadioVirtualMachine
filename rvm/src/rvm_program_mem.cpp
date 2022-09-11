
#include "rvm_program_mem.hpp"
#include <exception>
#include <new>

rvm_ProgramMemory::rvm_ProgramMemory()
{
}

rvm_ProgramMemory::rvm_ProgramMemory(uint64_t initSize)
{
    init(initSize);
}

rvm_ProgramMemory::~rvm_ProgramMemory()
{
    if (mem != nullptr)
    {
        delete[] mem;
    }
}

void rvm_ProgramMemory::init(uint64_t initSize)
{
    //! if initSize == 0
    try
    {
        mem = new uint8_t[initSize];
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Error: bad allocate rvm_ProgramMemory" << std::endl;
        throw std::string("Error: init rvm_ProgramMemory with size: " + std::to_string(initSize) + " failed");
    }
}

uint64_t rvm_ProgramMemory::load(std::string fileName)
{
    uint64_t retCntByte = 0;
    // todo: Load bytes from file
    return retCntByte;
}

uint8_t rvm_ProgramMemory::get(uint64_t addr)
{
    //! check overflow
    // todo: get byte from cell
    return 0;
}