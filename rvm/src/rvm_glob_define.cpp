/**
 * @file rvm_glob_define.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Global variables
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "rvm_glob_define.hpp"

rvm_glob_t rvm_glob;    /* Radio Virtual Machine global variable */

void rvm_globDefaultFill()
{
    rvm_glob.log_levl = LogLevels::FIRST;
}

void rvm_globFill(const rvm_glob_t &newGlob)
{
    rvm_glob.log_levl = newGlob.log_levl;
}
