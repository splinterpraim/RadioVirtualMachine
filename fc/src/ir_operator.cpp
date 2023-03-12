/**
 * @file ir_operator.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Intermediate representation of operator
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "ir_operator.hpp"

void IrOperator::setId(const std::string &id)
{
    if (id == "")
        throw std::invalid_argument("setId function failed, argument 'id' is empty");

    this->id = id;
}

std::string IrOperator::getId()
{
    return id;
}

void IrOperator::setType(const std::string &type)
{
    if (type == "")
        throw std::invalid_argument("setType function failed, argument 'type' is empty");

    this->type = type;
}

std::string IrOperator::getType()
{
    return type;
}

void IrOperator::setOpcode(const std::string &opcode)
{
    if (opcode == "")
        throw std::invalid_argument("setOpcode function failed, argument 'opcode' is empty");

    this->opcode = opcode;
}

std::string IrOperator::getOpcode()
{
    return opcode;
}

void IrOperator::setSubname(const std::string &subname)
{
    if (subname == "")
        throw std::invalid_argument("setOpcode function failed, argument 'subname' is empty");

    this->subname = subname;
}

std::string IrOperator::getSubname()
{
    return subname;
}

void IrOperator::setSubpath(const std::string &subpath)
{
    if (subpath == "")
        throw std::invalid_argument("setOpcode function failed, argument 'subpath' is empty");

    this->subpath = subpath;
}

std::string IrOperator::getSubpath()
{
    return subpath;
}