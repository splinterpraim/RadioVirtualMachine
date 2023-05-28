/**
 * @file main.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief A program to compile a single task
 * @version 0.1
 * @copyright Copyright (c) 2023
 */


/* C++ headers */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <cstdio>

/* XML lib headers*/
#include "pugixml/pugixml.hpp"

/* Project headers */
#include "common.hpp"
#include "ir_data.hpp"
#include "ir_operator.hpp"
#include "ir_link.hpp"
#include "config_code_structure.hpp"
#include "fc_glob.hpp"
#include "fc_parser.hpp"
#include "fc.hpp"
#include "fc_logger.hpp"
#include "reference_radio_library.hpp"


/**
 * @brief Parses the command line arguments
 *
 * @param[in]       argc                    Amount of command line arguments
 * @param[in]       argv                    Values of command line arguments
 */
void parseArg(int argc, char *argv[])
{
    if (argc > 4)
    {
        throw std::runtime_error(FC_ERR_STR("invalid program argument"));
    }
    switch (argc)
    {
    /* Using default names of directorys and file */    
    case 1: 
        break;
    /* Change name for file of SWIR */
    case 2:
        fc_glob.fileOfSWIR = argv[1];
        break;
    /* Change names for file of SWIR and input directory of SWIR */
    case 3:
        fc_glob.fileOfSWIR = argv[1];
        fc_glob.dirOfSWIR = argv[2];
        break;
    /* Change names for file of SWIR and input directory of SWIR and result configcode files */
    case 4:
        fc_glob.fileOfSWIR = argv[1];
        fc_glob.dirOfSWIR = argv[2];
        fc_glob.dirOfConfigCode = argv[3];
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

        Fc compiler(fc_glob.dirOfSWIR, fc_glob.dirOfConfigCode);
        compiler.compile(fc_glob.fileOfSWIR);
        std::cout << "Сompilation was " << GN <<"successful" << RT << std::endl;
        std::cout << "- Input file of SWIR: " << fc_glob.fileOfSWIR << std::endl;
        std::cout << "- Input directory of SWIR: " << fc_glob.dirOfSWIR << std::endl;
        std::cout << "- Output directory for configcodes: " << fc_glob.dirOfConfigCode << std::endl;

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "Сompilation " << RD <<"failed" << RT << std::endl;
        std::cout << "- Input file of SWIR: " << fc_glob.fileOfSWIR << std::endl;
        std::cout << "- Input directory of SWIR: " << fc_glob.dirOfSWIR << std::endl;
        std::cout << "- Output directory for configcodes: " << fc_glob.dirOfConfigCode << std::endl;
    }

    return 0;
}
