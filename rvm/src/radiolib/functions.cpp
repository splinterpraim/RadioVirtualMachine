/**
 * @file function.сpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Radio Library function declaration
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "radiolib/functions.hpp"

#include <stdexcept>

int radiolib::add_i(uint8_t argc, ...) /* 1 [ptr_data1, ptr_data2, ptr_resdata]  */
{
     int *resultMult = new int[1];
    *resultMult = 0;

    std::va_list argptr;
    va_start(argptr, argc);
    rl_ArgArray &fargv = *(va_arg(argptr, rl_ArgArray *));

    for (int i = 0; i < fargv.inNum; i++)
    {
        /* Check on nullptr */
        if (!fargv.inPorts[i])
        {
            throw std::invalid_argument("invalid argument in Radio Lib function");
            va_end(argptr);
        }
        /* Mult count */
        *resultMult += (int)*((int*)(fargv.inPorts[i]));
    }


    fargv.outPorts[fargv.outNum - 1] = (uint8_t*)resultMult;

    va_end(argptr);
    return 0;
}

int radiolib::add_f(uint8_t argc, ...) /* 3 ptr_data1, ptr_data2, ptr_resdata  */ //todo: this incorrect
{
    uint8_t *resultSum = (uint8_t *)new float[1];
    *resultSum = 0;

    std::va_list argptr;
    va_start(argptr, argc);
    rl_ArgArray &fargv = *(va_arg(argptr, rl_ArgArray *));

    for (int i = 0; i < fargv.inNum; i++)
    {
        /* Check on nullptr */
        if (!fargv.inPorts[i])
        {
            throw std::invalid_argument("invalid argument in Radio Lib function");
            va_end(argptr);
        }
        /* Sum count */
        *resultSum += (float)*(fargv.inPorts[i]);
    }
    fargv.outPorts[fargv.outNum - 1] = resultSum;

    va_end(argptr);
    return 0;
}

int radiolib::mult_i(uint8_t argc, ...)
{
    int *resultMult = new int[1];
    *resultMult = 1;

    std::va_list argptr;
    va_start(argptr, argc);
    rl_ArgArray &fargv = *(va_arg(argptr, rl_ArgArray *));

    for (int i = 0; i < fargv.inNum; i++)
    {
        /* Check on nullptr */
        if (!fargv.inPorts[i])
        {
            throw std::invalid_argument("invalid argument in Radio Lib function");
            va_end(argptr);
        }
        /* Mult count */
        *resultMult *= (int)*((int*)(fargv.inPorts[i]));
    }


    fargv.outPorts[fargv.outNum - 1] = (uint8_t*)resultMult;

    va_end(argptr);
    return 0;
}
