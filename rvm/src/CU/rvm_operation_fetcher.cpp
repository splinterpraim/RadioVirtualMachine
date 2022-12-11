#include "CU/rvm_operation_fetcher.hpp"
#include "radiolib/functions.h"
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
