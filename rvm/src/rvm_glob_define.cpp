#include "rvm_glob_define.h"


rvm_glob_t rvm_glob;

void rvm_globDefaultFill()
{
    rvm_glob.log_levl = LogLevels::FIRST;
}

void rvm_globFill(const rvm_glob_t &newGlob)
{
    rvm_glob.log_levl = newGlob.log_levl;
}
