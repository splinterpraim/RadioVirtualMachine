/**
 * @file fc_scheduler.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Implementation of FC Scheduler
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "fc_scheduler.hpp"

#include "pugixml/pugixml.hpp"

#include "system_func.hpp"


/* Private */
bool fc_Scheduler::loadProgram2Parser(pugi::xml_node programNode, std::vector<fc_Parser>& parsers)
{
    std::string name = programNode.attribute("name").as_string();
    std::string path = programNode.attribute("path").as_string();

    /* Load program from current document */
    if (programNode.first_child())
    {
        auto position = parsers.size();
        std::string targetDir = settingBlock->getDirCC() + std::string("/cc") + std::to_string(position);
        createDir(targetDir);
        parsers.resize(position+1);
        parsers[position].setSettingBlock(*settingBlock);
        parsers[position].setProgramName(name);
        parsers[position].setTargetDir(targetDir);
        parsers[position].loadProgramFromNode(programNode);
    }
    /* Load program from child document */
    else if(path.compare("") != 0)
    {
        auto position = parsers.size();
        std::string targetDir = settingBlock->getDirCC() + std::string("/cc") + std::to_string(position);
        std::string progPath = settingBlock->getDirXML() + std::string("/") + path;
        createDir(targetDir);
        parsers.resize(position+1);
        parsers[position].setSettingBlock(*settingBlock);
        parsers[position].setProgramName(name);
        parsers[position].setTargetDir(targetDir);
        parsers[position].loadProgramFromFile(progPath);
    }
    else
    {
        return false;
    }
    return true;
}

void fc_Scheduler::schedule(std::string inputTaskFilePath, std::vector<fc_Parser>& parsers)
{
    /* Load xml file */
    pugi::xml_document doc;
    pugi::xml_parse_result ret = doc.load_file(inputTaskFilePath.c_str());
    if(!ret)
    {
        std::string errMsg = std::string("Failed to load xml file: ") + inputTaskFilePath + std::string(" (description: ") + ret.description() + std::string(")");
        throw std::runtime_error(errMsg);
    }

    /* Take task tag */
    pugi::xml_node task = doc.child("task"); 
    if (!task)
    {
        std::string err = std::string("not found <task> tag in file: ") + inputTaskFilePath;
        throw std::runtime_error(err);
    }

    /* Iterate over program tag */
    for(pugi::xml_node program : task.children("program"))
    {
        if (!loadProgram2Parser(program, parsers))
        {
            std::string err = std::string("body for program '") + program.attribute("name").as_string() + 
                              std::string("' not found in file: ") + inputTaskFilePath;
            throw std::runtime_error(err);
        }
    }
}

void fc_Scheduler::setSettingBlock(fc_SettingBlock& settingBlock)
{
    this->settingBlock = &settingBlock;
}
