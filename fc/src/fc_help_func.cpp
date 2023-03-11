/**
 * @file fc_help_func.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Help functions for front-end compiler
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "fc_help_func.hpp"
#include "common.hpp"
#include "fc_glob.hpp"
#include "fc_system.hpp"

#include "radio_library.hpp"

#include <fstream>
#include <cstring>
#include <exception>
#include <stdexcept>

#define XML_TYPE_INT "int"
#define XML_TYPE_FLOAT "float"
#define XML_TYPE_STRING "string"

#define DO_CFG_LEN_FOR_FILE 255

extern fc_glob_t fc_glob;
extern RadioLibrary radioLib;

void showIrOperators(const std::vector<IrOperator> &operators)
{
    for (auto el : operators)
    {
        std::cout << "id = " << el.getId() << ", "
                  << "type = " << el.getType() << ", "
                  << "opcode = " << el.getOpcode() << std::endl;
    }
}

void showIrData(const std::vector<IrData> &data)
{
    for (auto el : data)
    {
        std::cout << "id = " << el.getId() << ", ";
        // std::cout << "type = " << el.getType() << ", ";
        std::cout << "path = " << el.getPath() << ", ";
        std::cout << "access_time = " << el.getAccessTime() << ", ";
        std::cout << "value = " << el.getValue() << std::endl;
    }
}

void showIrLinks(const std::vector<IrLink> &links)
{
    for (auto el : links)
    {
        std::cout << el.to_str() << std::endl;
    }
}

