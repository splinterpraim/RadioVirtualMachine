#include "system_func.hpp"

#include <exception>
#include <stdexcept>
#include <algorithm>
#include <fstream>

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

void getName(std::string fileName,  std::string& name)
{
    size_t splitPos = fileName.find(".");
    if( splitPos != std::string::npos)
    {
        name = fileName.substr(0, splitPos);
    }
    else
    {
        name = fileName;
    }
}

void getExt(std::string fileName, std::string& ext)
{
    size_t fsize = fileName.size();
    std::string res;
    bool fDot = false;
    for(size_t i = 0; i < fsize; i++)
    {
        size_t pos = fsize - i -1;
        char& c = fileName[pos];
        if (c == '.')
        {
            fDot = true;
            break;
        }
        res = c + res ;
    }
    if(fDot)
    {
        ext = res;
    }
    else
    {
        ext = "";
    }
}

void file2array(std::string filePath, uint8_t** cc, size_t &size)
{
    std::ifstream file;
    file.open(filePath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        throw std::runtime_error("file " + filePath + " does not open");
    }
    uint64_t cntByte = file.tellg();
    if (cntByte != 0)
    {
        uint8_t *memPtr = new uint8_t[cntByte];
        file.seekg(0, std::ios::beg);
        file.read((char *)memPtr, cntByte);
        *cc = memPtr;
    }
    file.close();
    size = cntByte;
}

std::vector<std::string> file2strLine(std::string filePath)
{
    std::vector<std::string> res;
    std::ifstream file;

    file.open(filePath, std::ios::in);
    if (!file.is_open())
    {
        throw std::runtime_error("file " + filePath + " does not open");
    }
    std::string line;
    while (std::getline(file, line))
    {
        res.push_back(line);
    }
    file.close();
    return res;
}
