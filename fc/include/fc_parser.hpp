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
#include "fc_converter_ir.hpp"
#include "fc_setting_block.hpp"

#define PROGRAM_MODE 0
#define COMPLEX_MODE 1

class fc_Parser
{
public:
    /**
     * @brief Constructs a new fc Parser object with parametr
     */
    fc_Parser(fc_SettingBlock& settingBlock, const std::string& targetDir, bool noChangeTargetDirectory);

    /**
     * @brief Parses XML program file and generates configcode file
     * 
     * @param progFileName Input XML program file
     */
    void parse(std::string progFileName);

    /**
     * @brief Parses XML program file for complex operator and generates configcode file
     * 
     * @param progFileName Input XML program file of complex operator
     */
    void parseComplex(std::string progFileName);

private:
    fc_SettingBlock& settingBlock;
    std::string targetDir; /* Directory where the program configcode file is located */
    IrObjects IrObj;
    fc_Parser* insideParsers;
    fc_ParserSWIR parserSWIR;
    fc_ConverterIR converterIR;
    bool noChangeTargetDirectory {false};

    void processComplexOperator(IrObjects &irObj);

    /**
     * @brief Creates RVM binary config code from Config Objects
     *
     * @param[in] cfgObj Reference to Config Objects
     * @param[in] fileNameBin File name where will be binary config code
     */
    void createRVMcfgcode(ConfigObjects &cfgObj, const std::string &fileNameBin);
};

#endif // FC_PARSER_CLASS