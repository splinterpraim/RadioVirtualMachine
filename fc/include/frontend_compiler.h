//
// Created by Елена on 15.05.2022.
//

#ifndef FRONT_END_RVM_COMPILER_FRONTEND_COMPILER_H
#define FRONT_END_RVM_COMPILER_FRONTEND_COMPILER_H

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

struct IrObjects
{
    std::vector<IrOperator> operators;
    std::vector<IrData> data;
    std::vector<IrLink> links;
};


// todo: doxygen comment style
struct IrObjects parseSWIR(const std::string &fileNameSWIR);
// Convert to RVM IR (structs)
// Create RVM Input


void showIrObjects(const struct IrObjects &irObjects);

#endif // FRONT_END_RVM_COMPILER_FRONTEND_COMPILER_H
