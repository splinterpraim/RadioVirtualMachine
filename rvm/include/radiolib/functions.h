#ifndef RVM_RADIOLIB_FUNCTIONS_H
#define RVM_RADIOLIB_FUNCTIONS_H
#include <iostream>
#include <cstdarg>

typedef struct
{
    int inNum;
    int outNum;
    uint8_t ** inPorts;
    uint8_t ** outPorts;
} rl_ArgArray;
namespace radiolib
{
    int sum(uint8_t argc, ...);
    int add_i(uint8_t argc, ...);
    int add_f(uint8_t argc, ...);
    int mult_i(uint8_t argc, ...);
}
#endif // RVM_RADIOLIB_FUNCTIONS_H
