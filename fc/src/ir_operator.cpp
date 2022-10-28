#include "ir_operator.h"

void IrOperator::setId(const std::string &id){
    if (id == "")
        throw std::invalid_argument("setId function failed, argument 'id' is empty");

    this->id = id;
}

std::string IrOperator::getId(){
	return id;
}

void IrOperator::setType(const std::string &type){
    if (type == "")
        throw std::invalid_argument("setType function failed, argument 'type' is empty");

    this->type = type;
}

std::string IrOperator::getType(){
    return type;
}

void IrOperator::setOpcode(const std::string &opcode){
    if (opcode == "")
        throw std::invalid_argument("setOpcode function failed, argument 'opcode' is empty");

    this->opcode = opcode;
}

std::string IrOperator::getOpcode(){
    return opcode;
}