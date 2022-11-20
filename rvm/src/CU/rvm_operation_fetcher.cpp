#include "CU/rvm_operation_fetcher.hpp"
#include "radiolib/functions.h"
void rvm_operationFetcher::getOpFunc(uint32_t opCode, int (**operation)(uint8_t argc, ...))
{
    *operation = radiolib::sum;
}
