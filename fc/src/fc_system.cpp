#include "fc_system.hpp"
#include <cstddef>
bool endianIsLittle()
{
    short int word = 0x0001;
    char *b = (char *)&word;
    return (b[0] ? true : false);
}

int convertToLittleEndian(int val)
{
    int res = 0;
    for (std::size_t i = 0; i < sizeof(val); ++i)
    {
        res = (res << 8) | ((val >> 8 * i) & 0xFF);
    }
    return res;
}


