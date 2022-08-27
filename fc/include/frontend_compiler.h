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
#include "ir_data.h"
#include "ir_operator.h"
#include "ir_link.h"
#include "config_code_structure.hpp"

struct IrObjects
{
    std::vector<IrOperator> operators;
    std::vector<IrData> data;
    std::vector<IrLink> links;
};
using IrObjects = struct IrObjects;


// todo: continue filling of config structure
// todo: doxygen comment style
IrObjects parseSWIR(const std::string &fileNameSWIR);
// Convert to RVM IR (structs)
ConfigObjects convert2rvmIr(IrObjects &irObjects); 
// Create RVM Input


void showIrObjects(const IrObjects &irObjects);

#endif // FC_FRONTEND_COMPILER_H
