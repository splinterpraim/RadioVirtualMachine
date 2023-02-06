/**
 * @file rvm_dlob_define.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Abstract Processing Element
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "rvm_glob_define.hpp"

rvm_glob_t rvm_glob;

void rvm_globDefaultFill()
{
    rvm_glob.log_levl = LogLevels::FIRST;
}

void rvm_globFill(const rvm_glob_t &newGlob)
{
    rvm_glob.log_levl = newGlob.log_levl;
}
