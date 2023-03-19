#include "fc.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "fc_parser.hpp"
#include "common.hpp"

Fc::Fc(const std::string &dirXML, const std::string &dirCC)
{
    settigBlock.setDirXML(dirXML);
    settigBlock.setDirCC(dirCC);
}

void Fc::compile()
{
    // create DirCC & DirCC/cc1
    std::string ccDir = settigBlock.getDirCC();
    std::string cc1Dir = ccDir + std::string("/cc1");
    if (mkdir(ccDir.c_str(), S_IRWXU|S_IRGRP|S_IXGRP) != 0)
    {
        int e = errno;
        if (e != EEXIST)
        {
            std::string errMsg = std::string("Cann't create directory") + std::string("'") + ccDir + std::string("'");
            throw std::runtime_error(errMsg.c_str());
        }
    }
    if (mkdir(cc1Dir.c_str(), S_IRWXU|S_IRGRP|S_IXGRP) != 0)
    {
        int e = errno;
        if (e != EEXIST)
        {
            std::string errMsg = std::string("Cann't create directory") + std::string("'") + cc1Dir.c_str() + std::string("'");
            throw std::runtime_error(errMsg.c_str());
        }
    }
    fc_Parser parser(settigBlock, settigBlock.getDirCC() + "/cc1", false);
    parser.parse("Adder.xml");
    
}
