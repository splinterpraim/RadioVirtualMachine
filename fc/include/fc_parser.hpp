/**
 * @file fc_parser.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Parser class
 * @version 0.2
 * @copyright Copyright (c) 2023
 */

#ifndef FC_PARSER_CLASS
#define FC_PARSER_CLASS

#include <string>
#include "ir_objects.hpp"
#include "config_code_structure.hpp"
#include "fc_parser_swir.hpp"

class fc_Parser
{
public:
    void parse(std::string progFileName, std::string ccFileName);

private:
    std::string programDir; /* Directory where the XML program file is located */
    std::string ccDir;      /* Directory where the program configcode file is located */
    IrObjects IrObj;
    fc_Parser* insideParsers;
    fc_Parser_SWIR parserSWIR;

    /**
     * @brief Shows IR objects in standart output
     *
     * @param[in] irObjects IR objects for output
     */
    void showIrObjects(const IrObjects &irObjects);

    /**
     * @brief Converts from Ir Objects to RVM IR (config structs)
     *
     * @param[in] irObjects IR Objects
     *
     * @retval ConfigObjects Config Objects
     */
    ConfigObjects convert2rvmIr(IrObjects &irObjects);

    /**
     * @brief Creates RVM binary config code from Config Objects
     *
     * @param[in] cfgObj Reference to Config Objects
     * @param[in] fileNameBin File name where will be binary config code
     */
    void createRVMcfgcode(ConfigObjects &cfgObj, const std::string &fileNameBin);
};

#endif // FC_PARSER_CLASS