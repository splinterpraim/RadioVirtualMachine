/**
 * @file frontend_compiler.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Front-end compiler
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef FC_FRONTEND_COMPILER_H
#define FC_FRONTEND_COMPILER_H

/* C++ headers */
#include <iostream>
#include <string>
#include <vector>

/* XML lib headers*/
#include "pugixml/pugixml.hpp"

/* Project headers */
#include "ir_objects.hpp"
#include "ir_data.hpp"
#include "ir_operator.hpp"
#include "ir_link.hpp"
#include "config_code_structure.hpp"

/**
 * @brief Parses XML file to Intermediate representation
 * 
 * @param[in] fileNameSWIR File name where store xml algorithm
 * 
 * @retval IrObjects IR objects
 */
IrObjects parseSWIR(const std::string &fileNameSWIR);

/**
 * @brief Shows IR objects in standart output
 * 
 * @param[in] irObjects IR objects for output
 */
void showIrObjects(const IrObjects &irObjects);

/**
 * @brief Creates RVM binary config code from Config Objects 
 * 
 * @param[in] cfgObj Reference to Config Objects
 * @param[in] fileNameBin File name where will be binary config code
 */
void createRVMcfgcode(ConfigObjects & cfgObj, const std::string &fileNameBin);

#endif // FC_FRONTEND_COMPILER_H
