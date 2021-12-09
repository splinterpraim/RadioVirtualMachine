//
// Created by oem on 12.11.2021.
//

#ifndef RADIOVIRTUALMACHINE_RVM_TYPES_H
#define RADIOVIRTUALMACHINE_RVM_TYPES_H
#include <cstdint>
//! DataObject
//! >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


using OneByte = uint8_t;
using IdType = unsigned int;
using SizeType = unsigned int;
using AccessTime = unsigned int;

struct Attributes {
    IdType id;
    SizeType size;
    AccessTime accessTime;
};

struct RMV_DataObject_Exceptions { // 00 - (value1, value0)
    OneByte value0: 1;
    OneByte value1: 1;
};

struct AccessType{
    OneByte value: 1; // 0 - r/re,  1 - w
};

struct DataEnableFlag{
    OneByte value: 1; // 0 - empty, 1 - full
};

//! AbstractSwitchFabric
//! >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
using Number = unsigned int;


#endif //RADIOVIRTUALMACHINE_RVM_TYPES_H
