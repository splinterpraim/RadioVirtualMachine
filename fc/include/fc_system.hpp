/**
 * @file fc_system.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief System endians
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef FC_SYSTEM_HPP
#define FC_SYSTEM_HPP

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
 * @param[in] val Input value
 * 
 * @retval Reversed value
 */
int reverseEndian(int val);

#endif // FC_SYSTEM_HPP