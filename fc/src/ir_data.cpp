/**
 * @file ir_data.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Intermediate representation of data
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "ir_data.hpp"

void IrData::setId(const string &id) {
    if (id == "")
        throw std::invalid_argument("setId function failed, argument 'id' is empty");

    this->id = id;
}

string IrData::getId() {
    return id;
}

void IrData::setType(const int &type) {
    // if (type == "")
    //     throw std::invalid_argument("setType function failed, argument 'type' is empty");

    this->type = type;
}

int IrData::getType() {
    return type;
}

void IrData::setPath(const string &path) {

    this->path = path;
}

string IrData::getPath() {
    return path;
}

void IrData::setAccessTime(const string &accessTime) {
    // if (accessTime < 0)
    //     throw std::invalid_argument("setAccessTime function failed, argument 'accessTime' is negative");

    this->accessTime = accessTime;
}

string IrData::getAccessTime() {
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
