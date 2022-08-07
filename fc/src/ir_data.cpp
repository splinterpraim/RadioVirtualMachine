#include "ir_data.h"


void IrData::setId(const string &id) {
    if (id == "")
        throw std::invalid_argument("setId function failed, argument 'id' is empty");

    this->id = id;
}

string IrData::getId() {
    return id;
}


void IrData::setType(const string &type) {
    if (type == "")
        throw std::invalid_argument("setType function failed, argument 'type' is empty");

    this->type = type;
}

string IrData::getType() {
    return type;
}

void IrData::setPath(const string &path) {

    this->path = path;
}

string IrData::getPath() {
    return path;
}


void IrData::setAccessTime(const int &accessTime) {
    if (accessTime < 0)
        throw std::invalid_argument("setAccessTime function failed, argument 'accessTime' is negative");

    this->accessTime = accessTime;
}

int IrData::getAccessTime() {
    return accessTime;
}

void IrData::setValue(const string &value) {
    this->value = value;
}

string IrData::getValue() {
    return value;
}


bool IrData::operator==(const IrData &rData) {
    if (id == rData.id)
        return 1;
    return 0;
}
