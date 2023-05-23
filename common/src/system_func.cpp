#include "system_func.hpp"

#include <exception>
#include <stdexcept>

extern "C" {
#include <cstddef>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
};

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

void createDir(std::string dir)
{
    if (mkdir(dir.c_str(), S_IRWXU|S_IRGRP|S_IXGRP) != 0)
    {
        int e = errno;
        if (e != EEXIST)
        {
            std::string errMsg = std::string("Cannot create directory") + std::string("'") + dir + std::string("'");
            throw std::runtime_error(errMsg.c_str());
        }
    }
}
