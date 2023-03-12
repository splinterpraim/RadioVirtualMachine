/**
 * @file main.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Main
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#define FC_LOG(s) std::cout << s << std::endl

/* C++ headers */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

/* XML lib headers*/
#include "pugixml/pugixml.hpp"

/* Project headers */
#include "common.hpp"
#include "ir_data.hpp"
#include "ir_operator.hpp"
#include "ir_link.hpp"
#include "radio_library.hpp"
#include "config_code_structure.hpp"
#include "fc_glob.hpp"
#include "fc_parser.hpp"

RadioLibrary radioLib;

/**
 * @brief Parses the command line arguments
 *
 * @param[in]       argc                    Amount of command line arguments
 * @param[in]       argv                    Values of command line arguments
 */
void parseArg(int argc, char *argv[])
{
    if (argc > 3)
    {
        throw std::runtime_error(FC_ERR_STR("invalid program argument"));
    }
    switch (argc)
    {
    /* Using default names of files */    
    case 1: 
        break;
    /* Change name for XML file */
    case 2:
        fc_glob.file_nameSWIR = argv[1];
        break;
    /* Change names for XML and result configcode files */
    case 3:
        fc_glob.file_nameSWIR = argv[1];
        fc_glob.file_nameBin = argv[2];
        break;
    default:
        throw std::runtime_error(FC_ERR_STR("invalid program argument"));
        break;
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
        /* Set global var */
        fc_glob_set();

        parseArg(argc, argv);

        fc_Parser parcer;
        parcer.parse(fc_glob.file_nameSWIR, fc_glob.file_nameBin);

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
