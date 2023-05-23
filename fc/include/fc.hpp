/**
 * @file fc.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Front-end compiler
 * @version 0.2
 * @copyright Copyright (c) 2023
 */

#ifndef FC_CLASS
#define FC_CLASS

#include <string>
#include <vector>

#include "fc_setting_block.hpp"
#include "fc_scheduler.hpp"
#include "fc_parser.hpp"


class Fc
{
public:
    /**
     * @brief Constructs a new Fc object with parametr
     * 
     * @param[in] dirXML directory of XML files
     * @param[in] dirCC directory of configcode files
     */
    Fc(const std::string &dirXML, const std::string &dirCC);

    void compile(std::string inputTaskFileName);
private:
    fc_SettingBlock settigBlock;
    fc_Scheduler scheduler;
    std::vector<fc_Parser> parsers;
};

#endif // FC_CLASS