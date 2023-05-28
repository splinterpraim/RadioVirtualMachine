/**
 * @file fc.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Scheduler for front-end compiler
 * @version 0.2
 * @copyright Copyright (c) 2023
 */

#ifndef FC_SCHEDULER_CLASS
#define FC_SCHEDULER_CLASS

#include <string>
#include <vector>
#include "pugixml/pugixml.hpp"

// #include "fc_setting_block.hpp"
#include "fc_parser.hpp"

class fc_Scheduler
{
public:
    // fc_Scheduler(fc_SettingBlock& settingBlock);

    void schedule(std::string inputTaskFilePath, std::vector<fc_Parser>& parsers);

    void setSettingBlock(fc_SettingBlock& settingBlock);
private:
    fc_SettingBlock* settingBlock;

    bool loadProgram2Parser(pugi::xml_node programNode,std::vector<fc_Parser>& parsers);

};

#endif // FC_SCHEDULER_CLASS