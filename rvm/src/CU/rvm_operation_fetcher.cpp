/**
 * @file rvm_operation_fetcher.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Operation Fetcher Block 
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "CU/rvm_operation_fetcher.hpp"

#include "radiolib/functions.hpp"

void rvm_operationFetcher::getOpFunc(uint32_t opCode, int (**operation)(uint8_t argc, ...))
{
    switch (opCode)
    {
    case 1 :
    {
        *operation = radiolib::add_i;
        break;
    }
    case 3 :
    {
        *operation = radiolib::mult_i;
        break;
    }
    
    default:
        break;
    }
}
