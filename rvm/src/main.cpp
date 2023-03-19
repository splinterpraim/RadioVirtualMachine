/**
 * @file main.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Main function
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <exception>
#include <stdexcept>

#include "rvm.hpp"
#include "rvm_glob_define.hpp"
#include "common.hpp"

/**
 * @brief Parses the command line arguments
 *
 * @param[in]       argc                    Amount of command line arguments
 * @param[in]       argv                    Values of command line arguments
 */
void parseArg(int argc, char *argv[])
{
    /* Arguments must be less than 2 */
    if (argc > 2)
    {
        throw std::runtime_error(RVM_ERR_STR("invalid program argument"));
    }

    /* Handling the log level argument */
    else if (argc == 2)
    {
        rvm_glob_t newGlob;
        int logLevel = -1;
        std::sscanf(argv[1], "%d", &logLevel);
        if (logLevel > static_cast<int>(LogLevels::SECOND) || logLevel < 0)
        {
            throw std::runtime_error(RVM_ERR_STR("invalid program argument - logLevel"));
        }
        newGlob.log_levl = static_cast<LogLevels>(logLevel);
        rvm_globFill(newGlob);
    }
}

/**
 * @brief Main function
 *
 * @param[in]       argc                    Amount of command line arguments
 * @param[in]       argv                    Values of command line arguments
 *
 * @retval          int                     Return code
 */
int main(int argc, char *argv[])
{
    try
    {
        rvm_globDefaultFill();
        parseArg(argc, argv);

        std::vector<std::string> cfgFileNames;
        // cfgFileNames.push_back("./config_codes/cfgcode1.bin");
        cfgFileNames.push_back("./config_codes/cc1/AlgScalar2.xml.bin");
        // cfgFileNames.push_back("./config_codes/cfgcode3.bin");
        Rvm rvm1(cfgFileNames);
        rvm1.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}