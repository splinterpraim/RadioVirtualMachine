#ifndef RVM_OPERATION_FETCHER_CLASS
#define RVM_OPERATION_FETCHER_CLASS

#include <cstdint>
#include "class_definition.h"

class rvm_operationFetcher
{
    public:
    void  getOpFunc(uint32_t opCode, int (**operation)(uint8_t argc, ...));
};

#endif // RVM_OPERATION_FETCHER_CLASS
