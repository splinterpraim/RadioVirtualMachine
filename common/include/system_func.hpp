/**
 * @file system_func.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief System endians
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef SYSTEM_FUNC_HPP
#define SYSTEM_FUNC_HPP

#include <string>

/**
 * @brief Checks whether the endian in the system is little
 * 
 * @retval true - Little endian
 * @retval false - Big endian
 */
bool endianIsLittle();

/**
 * @brief Reverses byte order
 * 
 * @param val Input value
 * @return Reversed value
 */
template<typename T>
T reverseEndian(T val, uint8_t size)
{
    T res = 0;
    for (std::size_t i = 0; i < size; ++i)
    {
        res = (res << 8) | ((val >> 8 * i) & 0xFF);
    }
    return res;
}

float reverseEndianFloat(float val, uint8_t size);
double reverseEndianDouble(double val, uint8_t size);

void createDir(std::string dir);

#endif // SYSTEM_FUNC_HPP