//
// Created by Елена on 15.05.2022.
//

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


// todo: doxygen comment style
/**
 * @brief Parse XML file to Intermediate representation
 * 
 * @param fileNameSWIR File name where store xml algorithm
 * @return IrObjects 
 */
IrObjects parseSWIR(const std::string &fileNameSWIR);

/**
 * @brief Shows IR objects in standart output
 * 
 * @param irObjects IR objects for output
 */
void showIrObjects(const IrObjects &irObjects);

/**
 * @brief Convert from Ir Objects to RVM IR (config structs) 
 * 
 * @param irObjects IR Objects
 * @return ConfigObjects 
 */
ConfigObjects convert2rvmIr(IrObjects &irObjects); 

/**
 * @brief Create RVM binary config code from Config Objects 
 * 
 * @param[in] cfgObj Reference to Config Objects
 * @param[in] fileNameBin File name where will be binary config code
 */
void createRVMcfgcode(ConfigObjects & cfgObj, const std::string &fileNameBin);



#endif // FC_FRONTEND_COMPILER_H
