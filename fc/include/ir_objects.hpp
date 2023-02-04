/**
 * @file ir_objects.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Intermediate representation Objects
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef FC_IR_OBJECTS_HPP
#define FC_IR_OBJECTS_HPP

/* C++ headers */
#include <iostream>
#include <vector> 

/* Project headers */
#include "ir_data.hpp"
#include "ir_operator.hpp"
#include "ir_link.hpp"

/**
 * @brief Class for describing of Intermediate representation objects
 */
struct IrObjects
{
    std::vector<IrOperator> operators;
    std::vector<IrData> data;
    std::vector<IrLink> links;
};
using IrObjects = struct IrObjects;

#endif // FC_IR_OBJECTS_HPP