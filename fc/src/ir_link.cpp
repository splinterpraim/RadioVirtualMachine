#include "ir_link.hpp"


void IrLink::setDataId(std::string dataId){
    if (dataId == "")
        throw std::invalid_argument("setDataId function failed, argument 'id' is empty");
    this->dataId = dataId;
}

void IrLink::setDataOrder(int dataOrder){
    if (dataOrder < 0)
        throw std::invalid_argument("setDataOrder function failed, argument 'dataOrder' is negative");
    this->dataOrder = dataOrder;

}

void IrLink::setOperatorId(std::string operatorId){
    if (operatorId.size() == 0)
    {
        throw std::invalid_argument("setOperatorId function failed, argument 'operatorId' is empty");
    }
	this->operatorId = operatorId;
}

void IrLink::setDir(int dir){
    if (dir < 0)
    {
        throw std::invalid_argument("setDir function failed, argument 'dir' is negative");
    }
	this->dir = dir;
}

std::string IrLink::getDataId(){
	return dataId;
}

int IrLink::getDataOrder(){
    return dataOrder;
}

std::string IrLink::getOperatorId(){
	return operatorId;
}

int IrLink::getDir(){
	return dir;
}

std::string IrLink::to_str(){
	std::string res = "data_id = " +  dataId +
                      ", op_id = "  + operatorId +
                      ", dir = "  + std::to_string(dir) +
                      ", data_order = " + std::to_string(dataOrder);
	return res;
}
