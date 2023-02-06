/**
 * @file function.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Radio Library function declaration
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_RADIOLIB_FUNCTIONS_HPP
#define RVM_RADIOLIB_FUNCTIONS_HPP

#include <cstdint>
#include <cstdarg>

/**
 * @brief Description of Input/Output arguments of Radio Library functions
 */
typedef struct
{
    int inNum;              /* Number of input arguments */
    int outNum;             /* Number of output arguments */
    uint8_t ** inPorts;     /* Pointer on input arguments array */
    uint8_t ** outPorts;    /* Pointer on output arguments array */
} rl_ArgArray;

/**
 * @brief Declaration of Radio Library functions
 */
namespace radiolib
{
    /**
     * @brief Summarizes integer type arguments
     *
     * @param[in]       argc                    Count of arguments
     * @param[in,out]   ...                     Arguments as rl_ArgArray type
     *
     * @retval          int                     0
     */
    int add_i(uint8_t argc, ...);

    /**
     * @brief Summarizes float type arguments
     *
     * @param[in]       argc                    Count of arguments
     * @param[in,out]   ...                     Arguments as rl_ArgArray type
     *
     * @retval          int                     0
     */
    int add_f(uint8_t argc, ...);

    /**
     * @brief Multiplies integer type arguments
     *
     * @param[in]       argc                    Count of arguments
     * @param[in,out]   ...                     Arguments as rl_ArgArray type
     *
     * @retval          int                     0
     */
    int mult_i(uint8_t argc, ...);
};

#endif // RVM_RADIOLIB_FUNCTIONS_HPP
