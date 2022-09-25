#include "fc_glob_func.hpp"

#include "fc_glob.hpp"
#include "fc_system.hpp"
#include "common.hpp"

extern fc_glob_t fc_glob;

void fc_glob_set()
{
    fc_glob.endian = endianIsLittle() ? CMN_LITTLE_ENDIAN : CMN_BIG_ENDIAN;
}