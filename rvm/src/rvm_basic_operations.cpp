#include "rvm_basic_operations.hpp"

#include <exception>
#include <stdexcept>
#include <cstring>
#include <cstdio>

#include "common.hpp"

void rvm_BasicOperations::addRLOperator(uint32_t opcode, rl_operator_fn opFn)
{
    radioLibraryOperations[opcode] = opFn;
}

void rvm_BasicOperations::addRVMOperator(std::string opName,uint8_t* cc, size_t cc_size, const std::map<int,std::string> &map)
{
    if (!cc)
    {
        throw std::runtime_error("Nullptr for cc");
    }

    uint8_t* cc_tmp = new uint8_t[cc_size];
    std::memcpy(cc_tmp,cc,cc_size);
    complex_t cplx;
    cplx.cc.bytes = cc_tmp;
    cplx.cc.size = cc_size;
    cplx.map = map;
    RVMOperations[opName] = cplx;
}


bool rvm_BasicOperations::getFirstRLOperator(uint32_t &opcode, rl_operator_fn* opFn)
{
    auto search = radioLibraryOperations.cbegin();
    if(search == radioLibraryOperations.end())
    {
        return false;
    }
    opcode = search->first;
    *opFn = search->second;
    return true;
}

bool rvm_BasicOperations::getNextRLOperator(uint32_t prevOpcode, uint32_t &opcode, rl_operator_fn* opFn)
{
    auto search = radioLibraryOperations.find(prevOpcode);
    search++;
    if(search == radioLibraryOperations.end())
    {
        return false;
    }
    opcode = search->first;
    *opFn = search->second;
    return true;
}


bool rvm_BasicOperations::getFirstRVMOperator(std::string &name, uint8_t** cc, size_t &cc_size, std::map<int,std::string> &map)
{
    auto search = RVMOperations.cbegin();
    if(search == RVMOperations.end())
    {
        return false;
    }
    name = search->first;
    cc_size = search->second.cc.size;
    *cc = search->second.cc.bytes;
    map = search->second.map;
    return true;
}

bool rvm_BasicOperations::getNextRVMOperator(std::string prevName, std::string &name, uint8_t** cc, size_t &cc_size, std::map<int,std::string> &map)
{
    auto search = RVMOperations.find(prevName);
    search++;
    if(search == RVMOperations.end())
    {
        return false;
    }
    name = search->first;
    cc_size = search->second.cc.size;
    *cc = search->second.cc.bytes;
    map = search->second.map;
    return true;
}

size_t rvm_BasicOperations::RLOperatorSize()
{
    return radioLibraryOperations.size();
}

size_t rvm_BasicOperations::RVMOperatorSize()
{
    return RVMOperations.size();
}

void rvm_BasicOperations::show()
{
    /* Show radio lib operators */
    std::printf("Radio library operators (cnt %lu)->\n", radioLibraryOperations.size());
    for(const auto& op: radioLibraryOperations)
    {
        std::printf("\topcode %u, fn %p\n",op.first, op.second);
    }
    /* Show complex operators */
    std::printf("Complex operators (cnt %lu)->\n", RVMOperations.size());
    for(const auto& op: RVMOperations)
    {
        std::printf("\tname: %s\n", op.first.c_str());
        std::printf("\tmap ->\n");
        for(const auto& m : op.second.map)
        {
            std::printf("\t\t%d : %s\n", m.first, m.second.c_str());
        }
        std::printf("\tconfig code (len %lu bytes) ->\n",op.second.cc.size);
        size_t i = 0;
        while( i < op.second.cc.size)
        {
            std::printf("\t\t");
            for(size_t j = 0; j < BIN_INPUT_ROW_SIZE; j++)
            {
                if( i < op.second.cc.size)
                {
                    std::printf("%.2x ", op.second.cc.bytes[i]);
                }
                i++;
            }
            std::printf("\n");
        }
        std::printf("\n");
        
    }
}
