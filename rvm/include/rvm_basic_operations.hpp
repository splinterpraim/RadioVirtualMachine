/**
 * @file rvm_basic_operations.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Basic Operations Block
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_BASIC_OPERATIONS_CLASS
#define RVM_BASIC_OPERATIONS_CLASS

#include<string>
#include <map>

#include "reference_radio_library.hpp"


/**
 * @brief Basic Operations Block class implementation
 */
class rvm_BasicOperations
{
public:
    void addRLOperator(uint32_t opcode, rl_operator_fn opFn);

    void addRVMOperator(std::string opName,uint8_t* cc, size_t cc_size, const std::map<int,std::string> &map);

    bool getFirstRLOperator(uint32_t &opcode, rl_operator_fn* opFn);

    bool getNextRLOperator(uint32_t prevOpcode, uint32_t &opcode, rl_operator_fn* opFn);

    bool getFirstRVMOperator(std::string &name, uint8_t** cc, size_t &cc_size, std::map<int,std::string> &map);

    bool getNextRVMOperator(std::string prevName, std::string &name, uint8_t** cc, size_t &cc_size, std::map<int,std::string> &map);

    size_t RLOperatorSize();

    size_t RVMOperatorSize();

    void show();

private:
    typedef struct
    {
        size_t size;
        uint8_t* bytes;
    } cc_t;

    typedef struct
    {
        cc_t cc;
        std::map<int,std::string> map;
    } complex_t;

    std::map<uint32_t,rl_operator_fn> radioLibraryOperations; /* key(opcode):value(fn) */
    std::map<std::string,complex_t> RVMOperations;
};

#endif // RVM_BASIC_OPERATIONS_CLASS