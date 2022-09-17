
#include "rvm_program_mem.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <new>

#include "common.hpp"

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
    if (initSize == 0)
    {
        throw std::invalid_argument(RVM_ERR_STR("init size cannot be '0'"));
    }

    try
    {
        mem = new uint8_t[initSize];
        _capacity = initSize;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << RVM_ERR_STR("bad allocate rvm_ProgramMemory") << std::endl;
        throw std::runtime_error(RVM_ERR_STR("init rvm_ProgramMemory with size " + std::to_string(initSize) + " failed"));
    }
}

uint64_t rvm_ProgramMemory::load(std::string fileName)
{
    uint64_t cntByte = 0;

    std::ifstream cfgFile;
    cfgFile.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);

    if (!cfgFile.is_open())
    {
        throw std::runtime_error(RVM_ERR_STR("file " + fileName + " does not open"));
    }

    cntByte = cfgFile.tellg();
    if (cntByte != 0)
    {
        uint8_t *memPtr = getPtrOnFreeSpace(cntByte);
        cfgFile.seekg(0, std::ios::beg);
        cfgFile.read((char *)memPtr, cntByte);
        cfgFile.close();

        _size += cntByte;
    }
    return cntByte;
}

uint8_t rvm_ProgramMemory::get(uint64_t addr)
{
    /* Check out of range */
    if (addr > _size)
    {
        throw std::out_of_range(RVM_ERR_STR("аccessing an element out of Program memory"));
    }
    
    return mem[addr];
}

/* Private */

uint8_t *rvm_ProgramMemory::getPtrOnFreeSpace(uint64_t size)
{
    if (!hasFreeSpace(size))
    {
        reallocateMem(size);
    }

    return &(mem[_size]);
}

bool rvm_ProgramMemory::hasFreeSpace(uint64_t size)
{
    uint64_t freeSpace = _capacity - _size;
    if (freeSpace >= size)
        return true;
    return false;
}

uint8_t *rvm_ProgramMemory::reallocateMem(uint64_t size)
{
    /* Delete mem */
    if (size == 0)
    {
        delete[] mem;
        mem = nullptr;
    }
    /* Realloc size > 0 */
    else
    {
        /* Init memory if memory is not initialized */
        if (mem == nullptr)
        {
            init(size);
        }
        /* Realloc memory */
        else
        {
            uint64_t newSize = _capacity + size;
            uint8_t *newMem = nullptr;
            try
            {
                newMem = new uint8_t[newSize];
            }
            catch (const std::bad_alloc &e)
            {
                std::cerr << RVM_ERR_STR("bad reallocate rvm_ProgramMemory") << std::endl;
                throw std::runtime_error(RVM_ERR_STR("reallocateMem rvm_ProgramMemory with size " + std::to_string(newSize) + " failed"));
            }

            /* Move data in new mem */
            std::memcpy(newMem, mem, _size);
            delete[] mem;
            mem = newMem;

            _capacity = newSize;
        }
    }
    return mem;
}
