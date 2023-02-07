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
#include "ir_data.hpp"
#include "ir_operator.hpp"
#include "ir_link.hpp"
#include "frontend_compiler.hpp"
#include "radio_library.hpp"
#include "config_code_structure.hpp"
#include "fc_glob.hpp"

RadioLibrary radioLib;

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

        std::string file_nameSWIR = "./XML_files/AlgScalar2.xml";
        std::string file_nameBin = "./config_codes/cfgcode1.bin";

        if (argc == 2)
        {
            file_nameSWIR = argv[1];
        }

        FC_LOG("----- parseSWIR");
        struct IrObjects irObjects = parseSWIR(file_nameSWIR);
        showIrObjects(irObjects);

        FC_LOG("----- convert2rvmIr");
        ConfigObjects configObjects = convert2rvmIr(irObjects);
        showConfigObjects(configObjects);

        FC_LOG("----- create RVM configcode");
        createRVMcfgcode(configObjects, file_nameBin);

        clearConfigObjects(configObjects);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
