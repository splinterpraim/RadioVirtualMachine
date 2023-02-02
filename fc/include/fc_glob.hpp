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

#endif // FC_GLOB_HPP