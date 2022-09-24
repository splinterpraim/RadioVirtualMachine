#ifndef FC_GLOB_HPP
#define FC_GLOB_HPP

#include <cstdint>

struct fc_glob_s
{
    uint8_t endian; 
};

using fc_glob_t = struct fc_glob_s;

#endif // FC_GLOB_HPP