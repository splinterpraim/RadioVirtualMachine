/**
 * @file rvm_operation_fetcher.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Operation Fetcher Block 
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_OPERATION_FETCHER_CLASS
#define RVM_OPERATION_FETCHER_CLASS

#include <cstdint>

/**
 * @brief Operation Fetcher Block class implementation
 */
class rvm_operationFetcher
{
    public:

    /**
     * @brief Gets a function pointer to the specified operation
     *
     * @param[in]       opCode                  Operation code of operator
     * @param[in]       operation               Function pointer to the specified operation
     */
    void  getOpFunc(uint32_t opCode, int (**operation)(uint8_t argc, ...));
};

#endif // RVM_OPERATION_FETCHER_CLASS
