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
#include <vector>
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

void getName(std::string fileName,  std::string& name);

void getExt(std::string fileName, std::string& ext);

void file2array(std::string filePath, uint8_t** cc, size_t &size);

std::vector<std::string> file2strLine(std::string filePath);

#endif // SYSTEM_FUNC_HPP