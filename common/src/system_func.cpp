#include "system_func.hpp"

#include <exception>
#include <stdexcept>
#include <algorithm>

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
float reverseEndianFloat(float val, uint8_t size)
{
    union {float f; uint8_t bytes[4];} res;
    res.f = val;
    std::swap(res.bytes[0], res.bytes[3]);
    std::swap(res.bytes[1], res.bytes[2]);

    return res.f;
}

double reverseEndianDouble(double val, uint8_t size)
{
    union {double f; uint8_t bytes[8];} res;
    res.f = val;
    std::swap(res.bytes[0], res.bytes[7]);
    std::swap(res.bytes[1], res.bytes[6]);
    std::swap(res.bytes[2], res.bytes[5]);
    std::swap(res.bytes[3], res.bytes[4]);

    return res.f;
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
