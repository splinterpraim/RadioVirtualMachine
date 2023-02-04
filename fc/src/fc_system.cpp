/**
 * @file fc_system.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief System endians
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "fc_system.hpp"
#include <cstddef>
bool endianIsLittle()
{
    short int word = 0x0001;
    char *b = (char *)&word;
    return (b[0] ? true : false);
}

int reverseEndian(int val)
{
    int res = 0;
    for (std::size_t i = 0; i < sizeof(val); ++i)
    {
        res = (res << 8) | ((val >> 8 * i) & 0xFF);
    }
    return res;
}


