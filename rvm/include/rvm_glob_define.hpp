/**
 * @file rvm_dlob_define.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Abstract Processing Element
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_GLOB_DEFINE_HPP
#define RVM_GLOB_DEFINE_HPP

#include "common.hpp"

/* Macro for execute command depending on level of log */
#define LLOG(n, cmd)                \
    {                               \
        if (n <= rvm_glob.log_levl) \
        {                           \
            cmd;                    \
        }                           \
    }

/**
 * @brief Global variables description
 */
typedef struct rvm_glob_s
{
    LogLevels log_levl;     /* level of log */
} rvm_glob_t;

extern rvm_glob_t rvm_glob;

/**
 * @brief Fills the global variables with default values
 */
void rvm_globDefaultFill();

/**
 * @brief Fills the global variables with new values
 *
 * @param[in]       newGlob                 Reference on new global variables
 */
void rvm_globFill(const rvm_glob_t &newGlob);

#endif // RVM_GLOB_DEFINE_HPP