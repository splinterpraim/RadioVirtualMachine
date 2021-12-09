//
// Created by oem on 25.10.2021.
//

#ifndef RADIOVIRTUALMACHINE_RVM_DATAOBJECT_H
#define RADIOVIRTUALMACHINE_RVM_DATAOBJECT_H

#include <iostream>
#include "RVM_SharedMemory.h"
#include "RVM_Types.h"


//!************************************************************************************************
//! IMPL WITH POINTER
class RVM_DataObject {
private:
    OneByte *data;                  // pointer to the first byte of data
    Attributes attributes; //> 0
    DataEnableFlag dataEnableFlag;
    RMV_DataObject_Exceptions DO_exception;  //может вынести в отдельный класс
    AccessType accessType; // 0 - r/re, 1 - w

    // functions to work with data;
    OneByte &allocateMem(SizeType size);

    void freeMem();

    void fillDataZero();


    // functions to set DO Exception
    void setNoException();

    void setSizeException();

    void setConflictingWriteException();

    void setConflictingReadEraseException();


    // functions to display parts of DO
//    void displayAll();

    void displayAttributes();

    void displayDataEnable();

    void displayAccessType();

    void displayDO_exception();

    void displaySeparatingLine();

    void displayHat();

    void displayByte(size_t number, OneByte &byte);


public:
    RVM_DataObject();

    ~RVM_DataObject();

    void set(const Attributes &newAttributes);

    void init(OneByte &ref, SizeType size);

    void write(OneByte &ref, SizeType size);

    void read(OneByte &ref, SizeType size);

    void readErase(OneByte &ref, SizeType size);

    DataEnableFlag dataEnable();

    AccessType getAccessType();

    void setAccessType(AccessType newAccessType);

    RMV_DataObject_Exceptions readException();


    void displayAll();

    void throwEx() { throw 1; }
};
//!************************************************************************************************

#endif //RADIOVIRTUALMACHINE_RVM_DATAOBJECT_H


