#ifndef RVM_GLOB_DEFINE_HPP
#define RVM_GLOB_DEFINE_HPP

// #include "rvm_program_mem.hpp"
#include "common.hpp"
#define LLOG(n, cmd)                \
    {                               \
        if (n <= rvm_glob.log_levl) \
        {                           \
            cmd;                    \
        }                           \
    }

typedef struct rvm_glob_s
{
    LogLevels log_levl; /*  */
} rvm_glob_t;

extern rvm_glob_t rvm_glob;

void rvm_globDefaultFill();
void rvm_globFill(const rvm_glob_t &newGlob);
// rvm_ProgramMemory progMem;
#endif // RVM_GLOB_DEFINE_HPP