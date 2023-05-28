/**
 * @file fc_logger.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Logger for Front-end compiler
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef FC_LOGGER_HPP
#define FC_LOGGER_HPP

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdarg>

#include "fc_config.hpp"

#define RT "\033[0m"                  /* Reset */
#define RD "\033[31m"                 /* Red */
#define GN "\033[32m"                 /* Green */
#define MAGENTA "\033[35m"            /* Magenta */

#define FC_LOGGER_MAX_STRING 1024

#ifdef FC_DEBUG
#define FC_ERR_STR(format, ...) fcLoggerStr("FC: " RD "Error: " RT format " ( %s:%d )\n", ##__VA_ARGS__, __FILE__,  __LINE__)
#define FC_WARN_STR(format, ...) fcLoggerStr("FC: " MAGENTA "Warning: " RT format " ( %s:%d )\n", ##__VA_ARGS__, __FILE__,  __LINE__)
#else
#define FC_ERR_STR(format, ...) fcLoggerStr("FC: " RD "Error: " RT format "\n", ##__VA_ARGS__)
#define FC_WARN_STR(format, ...) fcLoggerStr("FC: " MAGENTA "Warning: " RT format "\n", ##__VA_ARGS__)
#endif

#define FC_LOG_STR(format,...) fcLoggerStr("FC: "  format, ##__VA_ARGS__)

#define FC_LOG(format,...) std::cout << FC_LOG_STR(format, ##__VA_ARGS__) << std::flush;

std::string fcLoggerStr(const char* format, ...);

#endif // FC_LOGGER_HPP