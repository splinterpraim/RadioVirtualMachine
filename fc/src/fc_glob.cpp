/**
 * @file fc_glob.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Global variables
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "fc_glob.hpp"

#include "system_func.hpp"
#include "common.hpp"

fc_glob_t fc_glob;

void fc_glob_set()
{
    fc_glob.dirOfSWIR = "./XML_files";
    fc_glob.dirOfConfigCode = "./config_codes";
    fc_glob.fileOfSWIR = "./task.xml";
}