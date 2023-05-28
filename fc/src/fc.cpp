/**
 * @file fc.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Implementation of Front-end Compiler.
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "fc.hpp"

#include "fc_parser.hpp"
#include "common.hpp"
#include "system_func.hpp"

/* Private */


/* Public */
Fc::Fc(const std::string &dirXML, const std::string &dirCC)
{
    settigBlock.setDirXML(dirXML);
    settigBlock.setDirCC(dirCC);
    scheduler.setSettingBlock(settigBlock);
}

void Fc::compile(std::string inputTaskFileName)
{
    /* Create output configcode directory */
    createDir(settigBlock.getDirCC());

    std::string inputTaskFilePath = settigBlock.getDirXML() + std::string("/") + inputTaskFileName;
    scheduler.schedule(inputTaskFilePath, parsers);

    for(auto & p : parsers)
    {
        p.parse();
    }
}
