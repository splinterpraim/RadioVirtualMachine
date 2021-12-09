//
// Created by oem on 25.10.2021.
//

#include "RVM_DataObject.h"
#include <iostream>
#include <iomanip>
#include <exception>



//!************************************************************************************************
//!************************************************************************************************
//! function public

RVM_DataObject::RVM_DataObject() {
    std::cout << "call constructor RVM_DataObject  " << std::endl;
    data = nullptr;
    attributes = {0, 0, 0};
    dataEnableFlag.value = 0;
    accessType.value = 0;
    setNoException();
}

RVM_DataObject::~RVM_DataObject() {
    std::cout << "call destructor ~RVM_DataObject  " << std::endl;
    freeMem();
}

void RVM_DataObject::set(const Attributes &newAttributes) {
    std::cout << "-RVM_DataObject::set(" << newAttributes.id << ", " << newAttributes.size << ", "
              << newAttributes.accessTime << ")" << std::endl;
    if (newAttributes.size == 0) {
        std::cout << "Error: attribute size = 0" << std::endl;
    } else {
        attributes = newAttributes;
        data = &allocateMem(newAttributes.size);
        fillDataZero();
    }
}

void RVM_DataObject::init(OneByte &ref, SizeType size) {
    std::cout << "-RVM_DataObject::init(" << static_cast<void *>(&ref) << ", " << size << ")" << std::endl;
    if (size == 0) {
        std::cout << "Error: attribute size = 0" << std::endl;
    } else {
        write(ref, size);
    }
}

void RVM_DataObject::write(OneByte &ref, SizeType size) {
    std::cout << "-RVM_DataObject::write(" << static_cast<void *>(&ref) << ", " << size << ")" << std::endl;
    try {
        if (size == 0) {
            std::cout << "Error: attribute size = 0" << std::endl;
        } else {

            if (data == nullptr) {
                std::cout << "Error: memory dont allocate" << std::endl;
            } else {
                if (size > attributes.size) { //exept size
                    setSizeException();
                    std::cout << "Error: input data size more then need" << std::endl;
                } else {
                    OneByte *ptr_input = &ref;
                    OneByte *ptr_data = data;
                    for (size_t i = 0; i < size; ++i) {
                        *ptr_data = *ptr_input;
                        ptr_data++;
                        ptr_input++;
                    }
                    dataEnableFlag.value = 1;
                    accessType.value = 1;
                }
            }
        }
    }
    catch (const std::exception &err) {
        setConflictingWriteException();
        fillDataZero();
        dataEnableFlag.value = 0;
        std::cout << err.what() << std::endl;
    }
}

void RVM_DataObject::read(OneByte &ref, SizeType size) {
    std::cout << "-RVM_DataObject::read(" << static_cast<void *>(&ref) << ", " << size << ")" << std::endl;
    try {
        if (size == 0) {
            std::cout << "Error: attribute size = 0" << std::endl;
        } else {

            if (data == nullptr) {
                std::cout << "Error: memory dont allocate" << std::endl;
            } else {
                if (size > attributes.size) {
                    setSizeException();
                    std::cout << "Error: input data size more then need" << std::endl;
                } else {
                    OneByte *ptr_output = &ref;
                    OneByte *ptr_data = data;
                    for (size_t i = 0; i < size; ++i) {
                        *ptr_output = *ptr_data;
                        ptr_data++;
                        ptr_output++;
                    }
                    accessType.value = 0;
                }
            }
        }
    }
    catch (const std::exception &err) {
        setConflictingReadEraseException();
        std::cout << err.what() << std::endl;
    }
}

void RVM_DataObject::readErase(OneByte &ref, SizeType size) {
    std::cout << "-RVM_DataObject::readErase(" << static_cast<void *>(&ref) << ", " << size << ")" << std::endl;

    try {
        if (size == 0) {
            std::cout << "Error: attribute size = 0" << std::endl;
        } else {
            read(ref, size);
            fillDataZero();

        }
    }
    catch (const std::exception &err) {
        setConflictingReadEraseException();
        std::cout << err.what() << std::endl;
    }
}

DataEnableFlag RVM_DataObject::dataEnable() {
    std::cout << "-RVM_DataObject::dataEnable()" << std::endl;
    return dataEnableFlag;
}

AccessType RVM_DataObject::getAccessType() {
    std::cout << "-RVM_DataObject::getAccessType()" << std::endl;
    return accessType;
}

void RVM_DataObject::setAccessType(AccessType newAccessType) {
    std::cout << "-RVM_DataObject::setAccessType("<< static_cast<int>(newAccessType.value) <<")" << std::endl;
    accessType = newAccessType;
}

RMV_DataObject_Exceptions RVM_DataObject::readException() {
    std::cout << "-RVM_DataObject::readException()" << std::endl;
    return DO_exception;
}

//!************************************************************************************************


//!************************************************************************************************
//!************************************************************************************************
//! function private
//!****************************************
//!************ functions to work with data

OneByte &RVM_DataObject::allocateMem(SizeType size) {
    std::cout << "-RVM_DataObject::allocateMem(" << size << ")" << std::endl;
    OneByte *result;
    if (data != nullptr) { // exeption
        std::cout << "Error: memory is exists yet" << std::endl;
        result = data;
    } else {
        try {
            result = new OneByte[size];
        }
        catch (const std::bad_alloc &err) {
            std::cout << err.what() << std::endl;
        }
    }
    return *result;
}

void RVM_DataObject::freeMem() {
    std::cout << "-RVM_DataObject::freeMem()" << std::endl;
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
}

void RVM_DataObject::fillDataZero() {
    std::cout << "-RVM_DataObject::fillDataZero()" << std::endl;
    if (data != nullptr) {
        OneByte *ptr = data;
        for (size_t i = 0; i < attributes.size; i++) {
            *ptr = 0;
            ptr++;
        }
        dataEnableFlag.value = 0;
    }
}
//!****************************************

//!****************************************
//!************ functions to set DO Exception

void RVM_DataObject::setNoException() {
    DO_exception.value0 = 0;
    DO_exception.value1 = 0;
}

void RVM_DataObject::setSizeException() {
    DO_exception.value0 = 1;
    DO_exception.value1 = 0;
}

void RVM_DataObject::setConflictingWriteException() {
    DO_exception.value0 = 0;
    DO_exception.value1 = 1;
}

void RVM_DataObject::setConflictingReadEraseException() {
    DO_exception.value0 = 1;
    DO_exception.value1 = 1;
}
//!****************************************

//!****************************************
//!************ functions to display parts of DO

void RVM_DataObject::displayAll() {
    std::cout << "-RVM_DataObject::displayAll()" << std::endl;
    displayAttributes();
    displayDataEnable();
    displayAccessType();
    displayDO_exception();
    if (data == nullptr) {
        std::cout.setf(std::ios::right);
        std::cout << std::setw(5) << "" << "data = nullptr" << std::endl;
        std::cout.setf(std::ios::left);
    } else {
        OneByte *ptr = data;

        displaySeparatingLine();
        displayHat();
        for (size_t i = 0; i < attributes.size; ++i) {
            displayByte(i, *ptr);
            ptr++;
        }
        displaySeparatingLine();
    }
}

void RVM_DataObject::displayAttributes() {
    std::cout << std::setw(5) << "" << "Attributes id = " << attributes.id << " size = " << attributes.size
              << " access time = " << attributes.accessTime << std::endl;
}

void RVM_DataObject::displayDataEnable() {
    std::cout << std::setw(5) << "" << "dataEnable = " << static_cast<int>(dataEnableFlag.value);
}

void RVM_DataObject::displayAccessType() {
    std::cout << " " << "accessType = " << static_cast<int>(accessType.value) << std::endl;
}

void RVM_DataObject::displayDO_exception() {
    std::cout << std::setw(5) << "" << "DO_exception = " << static_cast<int>(DO_exception.value1)
              << static_cast<int>(DO_exception.value0) << std::endl;
}

void RVM_DataObject::displaySeparatingLine() {
    std::cout << std::setw(5) << "" << "--------------------------------------------" << std::endl;
}

void RVM_DataObject::displayHat() {
    std::cout << std::setw(10) << "Byte" << std::setw(20) << std::right << "address" << std::setw(10) << "data"
              << std::endl;
}

void RVM_DataObject::displayByte(size_t number, OneByte &byte) {
    std::cout << std::setw(10) << number << std::setw(20) << std::right << static_cast<void *>(&byte) << std::setw(10)
              << static_cast<unsigned int>(byte)
              << std::endl;
}
//!****************************************

//!************************************************************************************************
