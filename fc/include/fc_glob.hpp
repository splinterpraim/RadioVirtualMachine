/**
 * @file fc_glob.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Global variables
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef FC_GLOB_HPP
#define FC_GLOB_HPP

#include <cstdint>

/**
 * @brief Struct for storage global variables
 */
struct fc_glob_s
{
    uint8_t endian;     /* Current order of bytes in the system */
};

using fc_glob_t = struct fc_glob_s;

extern fc_glob_t fc_glob; /* Global variable of front-end compiler */

/**
 * @brief Sets global variables
 */
void fc_glob_set();

#endif // FC_GLOB_HPP