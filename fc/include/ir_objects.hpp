#ifndef FC_IR_OBJECTS_HPP
#define FC_IR_OBJECTS_HPP

/* C++ headers */
#include <iostream>
#include <vector> 

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
using IrObjects = struct IrObjects;

#endif // FC_IR_OBJECTS_HPP