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
int reverseEndian(int val);

void createDir(std::string dir);

#endif // SYSTEM_FUNC_HPP