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
    fc_glob.endian = endianIsLittle() ? CMN_LITTLE_ENDIAN : CMN_BIG_ENDIAN;
    fc_glob.file_nameSWIR = "./XML_files";
    fc_glob.file_nameBin = "./config_codes";
}