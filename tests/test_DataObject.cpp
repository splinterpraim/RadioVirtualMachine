//
// Created by oem on 27.11.2021.
//
#include <iostream>

#include "../source/RVM_DataObject.h"
#include "test_DataObject.h"

using namespace std;

//! >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//// testing functions

void test_ConstructorDestructorDO() {
    cout << "-> run test_ConstructorDestructorDO" << endl;
    cout << "######################################################################" << endl;
    size_t countDO = 10;

    RVM_DataObject *ptrDO = &createDataObjects(countDO);

    displayDataObjects(*ptrDO, countDO);

    deleteDataObjects(*ptrDO, countDO);
    cout << "######################################################################" << endl << endl;
}

void test_SetFunctionDO() {
    cout << "-> run test_SetFunctionDO" << endl;
    cout << "######################################################################" << endl;
    size_t countDO = 10;

    // creating
    RVM_DataObject *ptrDO = &createDataObjects(countDO);
    Attributes *ptrAttributes = &createAttributes(countDO);

    callSetFromDataObjects(*ptrDO, *ptrAttributes, countDO);

    displayDataObjects(*ptrDO, countDO);

    // deleting
    deleteAttributes(*ptrAttributes, countDO);
    deleteDataObjects(*ptrDO, countDO);

    cout << "######################################################################" << endl << endl;
}

void test_InitFunctionDO() {
    cout << "-> run test_InitFunctionDO" << endl;
    cout << "######################################################################" << endl;
    size_t countDO = 10;

    // creating, setting
    RVM_DataObject *ptrDO = &createDataObjects(countDO);
    Attributes *ptrAttributes = &createAttributes(countDO);
    OneByte *ptrInitData = &createData(countDO);
    callSetFromDataObjects(*ptrDO, *ptrAttributes, countDO);

    callInitFromDataObjects(*ptrDO, *ptrInitData, countDO);

    displayDataObjects(*ptrDO, countDO);

    // deleting
    deleteData(*ptrInitData, countDO);
    deleteAttributes(*ptrAttributes, countDO);
    deleteDataObjects(*ptrDO, countDO);

    cout << "######################################################################" << endl << endl;
}

void test_WriteFunctionDO() {
    cout << "-> run test_WriteFunctionDO" << endl;
    cout << "######################################################################" << endl;
    size_t countDO = 10;

    // creating, setting, initialization
    RVM_DataObject *ptrDO = &createDataObjects(countDO);
    Attributes *ptrAttributes = &createAttributes(countDO);
    OneByte *ptrInitData = &createData(countDO);
    callSetFromDataObjects(*ptrDO, *ptrAttributes, countDO);
    callInitFromDataObjects(*ptrDO, *ptrInitData, countDO);

    OneByte *ptrWriteData = &createData(countDO, 2);
    callWriteFromDataObjects(*ptrDO, *ptrWriteData, countDO);

    displayDataObjects(*ptrDO, countDO);

    // deleting
    deleteData(*ptrWriteData, countDO);
    deleteData(*ptrInitData, countDO);
    deleteAttributes(*ptrAttributes, countDO);
    deleteDataObjects(*ptrDO, countDO);
    cout << "######################################################################" << endl << endl;
}

void test_ReadFunctionDO(){
    cout << "-> run test_ReadFunctionDO" << endl;
    cout << "######################################################################" << endl;
    size_t countDO = 10;

    // creating, setting, initialization
    RVM_DataObject *ptrDO = &createDataObjects(countDO);
    Attributes *ptrAttributes = &createAttributes(countDO);
    OneByte *ptrInitData = &createData(countDO, 2);
    callSetFromDataObjects(*ptrDO, *ptrAttributes, countDO);
    callInitFromDataObjects(*ptrDO, *ptrInitData, countDO);

    OneByte *ptrReadData = &createData(countDO, 0);
    callReadFromDataObjects(*ptrDO, *ptrReadData, countDO);

    displayData(*ptrReadData,countDO);
    displayDataObjects(*ptrDO, countDO);

    // deleting
    deleteData(*ptrReadData, countDO);
    deleteData(*ptrInitData, countDO);
    deleteAttributes(*ptrAttributes, countDO);
    deleteDataObjects(*ptrDO, countDO);
    cout << "######################################################################" << endl << endl;
}

void test_ReadEraseFunctionDO(){
    cout << "-> run test_ReadEraseFunctionDO" << endl;
    cout << "######################################################################" << endl;
    size_t countDO = 10;

    // creating, setting, initialization
    RVM_DataObject *ptrDO = &createDataObjects(countDO);
    Attributes *ptrAttributes = &createAttributes(countDO);
    OneByte *ptrInitData = &createData(countDO, 2);
    callSetFromDataObjects(*ptrDO, *ptrAttributes, countDO);
    callInitFromDataObjects(*ptrDO, *ptrInitData, countDO);

    OneByte *ptrReadEraseData = &createData(countDO, 0);
    callReadEraseFromDataObjects(*ptrDO, *ptrReadEraseData, countDO);

    displayData(*ptrReadEraseData,countDO);
    displayDataObjects(*ptrDO, countDO);

    // deleting
    deleteData(*ptrReadEraseData, countDO);
    deleteData(*ptrInitData, countDO);
    deleteAttributes(*ptrAttributes, countDO);
    deleteDataObjects(*ptrDO, countDO);
    cout << "######################################################################" << endl << endl;
}

void test_DataEnableFunctionDO(){
    cout << "-> run test_DataEnableFunctionDO" << endl;
    cout << "######################################################################" << endl;
    size_t countDO = 10;

    // creating
    RVM_DataObject *ptrDO = &createDataObjects(countDO);
    Attributes *ptrAttributes = &createAttributes(countDO);
    OneByte *ptrInitData = &createData(countDO, 2);
    OneByte *ptrReadEraseData = &createData(countDO, 0);
    OneByte *ptrWriteData = &createData(countDO, 5);

    // calling functions (set, init, write, read, readErase. dataEnable)
    callSetFromDataObjects(*ptrDO, *ptrAttributes, countDO);
    callInitFromDataObjects(*ptrDO, *ptrInitData, countDO);
    displayDataObjects(*ptrDO, countDO);
    callDataEnableFromDataObjects(*ptrDO, countDO);

    callReadEraseFromDataObjects(*ptrDO, *ptrReadEraseData, countDO);
    displayDataObjects(*ptrDO, countDO);
    displayData(*ptrReadEraseData,countDO);
    callDataEnableFromDataObjects(*ptrDO, countDO);

    callWriteFromDataObjects(*ptrDO, *ptrWriteData, countDO);
    displayDataObjects(*ptrDO, countDO);
    callDataEnableFromDataObjects(*ptrDO, countDO);

    callReadFromDataObjects(*ptrDO, *ptrReadEraseData, countDO);
    displayData(*ptrReadEraseData,countDO);
    callDataEnableFromDataObjects(*ptrDO, countDO);


    // deleting
    deleteData(*ptrWriteData, countDO);
    deleteData(*ptrReadEraseData, countDO);
    deleteData(*ptrInitData, countDO);
    deleteAttributes(*ptrAttributes, countDO);
    deleteDataObjects(*ptrDO, countDO);
    cout << "######################################################################" << endl << endl;
}

void test_GetAccessTypeFunctionDO(){
    cout << "-> run test_GetAccessTypeFunctionDO" << endl;
    cout << "######################################################################" << endl;
    size_t countDO = 10;

    // creating
    RVM_DataObject *ptrDO = &createDataObjects(countDO);
    Attributes *ptrAttributes = &createAttributes(countDO);
    OneByte *ptrInitData = &createData(countDO, 2);
    OneByte *ptrReadEraseData = &createData(countDO, 0);
    OneByte *ptrWriteData = &createData(countDO, 5);

    // calling functions (set, init, write, read, readErase. dataEnable)
    callSetFromDataObjects(*ptrDO, *ptrAttributes, countDO);
    callInitFromDataObjects(*ptrDO, *ptrInitData, countDO);
    displayDataObjects(*ptrDO, countDO);
    callGetAccessTypeFromDataObjects(*ptrDO, countDO);

    callReadEraseFromDataObjects(*ptrDO, *ptrReadEraseData, countDO);
    displayDataObjects(*ptrDO, countDO);
    displayData(*ptrReadEraseData,countDO);
    callGetAccessTypeFromDataObjects(*ptrDO, countDO);

    callWriteFromDataObjects(*ptrDO, *ptrWriteData, countDO);
    displayDataObjects(*ptrDO, countDO);
    callGetAccessTypeFromDataObjects(*ptrDO, countDO);

    callReadFromDataObjects(*ptrDO, *ptrReadEraseData, countDO);
    displayData(*ptrReadEraseData,countDO);
    callGetAccessTypeFromDataObjects(*ptrDO, countDO);


    // deleting
    deleteData(*ptrWriteData, countDO);
    deleteData(*ptrReadEraseData, countDO);
    deleteData(*ptrInitData, countDO);
    deleteAttributes(*ptrAttributes, countDO);
    deleteDataObjects(*ptrDO, countDO);
    cout << "######################################################################" << endl << endl;
}
void test_SetAccessTypeFunctionDO(){

}
void test_readExceptionFunctionDO();


//! >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//// secondary functions

//! -- creating function
RVM_DataObject &createDataObjects(size_t count) {

    cout << "--- create " << count << " Data Objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    RVM_DataObject *ptrDO = new RVM_DataObject[count];

    cout << "----------------------------------------------------------------------" << endl << endl;
    return *ptrDO;
}

Attributes &createAttributes(size_t count) {
    cout << "--- create Attributes to set functions of Data objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    Attributes *ptrAttributes = new Attributes[count];
    Attributes *ptrMoveAttributes = ptrAttributes;
    for (size_t i = 0; i < count; i++) {
        ptrMoveAttributes->id = i;
        ptrMoveAttributes->size = i;
        ptrMoveAttributes->accessTime = i;
        cout << "Attributes for Data object " << i << ": id = " << ptrMoveAttributes->id << " size = "
             << ptrMoveAttributes->size << " accessTime =" << ptrMoveAttributes->accessTime << endl;
        ptrMoveAttributes++;
    }
    ptrMoveAttributes = nullptr;

    cout << "----------------------------------------------------------------------" << endl << endl;
    return *ptrAttributes;
}

OneByte &createData(size_t count, int start) {
    cout << "--- create Data to functions of Data objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    OneByte *ptrInitData = new OneByte[count];
    OneByte *ptrMoveInitData = ptrInitData;
    for (size_t i = start; i < count + start; i++) {
        *ptrMoveInitData = i;
        ptrMoveInitData++;
    }
    ptrMoveInitData = ptrInitData;
    for (size_t i = 0; i < count; i++) {
        ptrMoveInitData = ptrInitData;
        cout << "Data for Data object " << i << ":  = ";
        for (size_t j = 0; j < i; j++) {
            cout << static_cast<int>(*ptrMoveInitData) << " ";
            ptrMoveInitData++;
        }
        cout << endl;
    }

    ptrMoveInitData = nullptr;

    cout << "----------------------------------------------------------------------" << endl << endl;
    return *ptrInitData;
}


//! -- calling function
void callSetFromDataObjects(RVM_DataObject &firstDataObject, Attributes &firstObjectAttributes, size_t count) {
    cout << "--- calling set functions Data objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    Attributes *ptrAttributes = &firstObjectAttributes;
    RVM_DataObject *ptrDO = &firstDataObject;
    for (size_t i = 0; i < count; i++) {
        cout << "Data object " << i << endl;
        ptrDO->set(*ptrAttributes);
        ptrDO++;
        ptrAttributes++;
    }
    ptrAttributes = nullptr;
    ptrAttributes = nullptr;

    cout << "----------------------------------------------------------------------" << endl << endl;
}

void callInitFromDataObjects(RVM_DataObject &firstDataObject, OneByte &firstObjectInitData, size_t count) {
    cout << "--- calling init functions Data objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    OneByte *ptrInitData = &firstObjectInitData;
    RVM_DataObject *ptrDO = &firstDataObject;
    for (size_t i = 0; i < count; i++) {
        cout << "Data object " << i << endl;
        ptrDO->init(*ptrInitData, i);
        ptrDO++;
    }
    ptrInitData = nullptr;
    ptrDO = nullptr;

    cout << "----------------------------------------------------------------------" << endl << endl;
}

void callWriteFromDataObjects(RVM_DataObject &firstDataObject, OneByte &firstObjectWriteData, size_t count) {
    cout << "--- calling write functions Data objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    OneByte *ptrData = &firstObjectWriteData;
    RVM_DataObject *ptrDO = &firstDataObject;
    for (size_t i = 0; i < count; i++) {
        cout << "Data object " << i << endl;
        ptrDO->write(*ptrData, i);
        ptrDO++;
    }
    ptrData = nullptr;
    ptrDO = nullptr;

    cout << "----------------------------------------------------------------------" << endl << endl;
}

void callReadFromDataObjects(RVM_DataObject &firstDataObject,OneByte &firstObjectReadData, size_t count){
    cout << "--- calling read functions Data objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    OneByte *ptrData = &firstObjectReadData;
    RVM_DataObject *ptrDO = &firstDataObject;
    for (size_t i = 0; i < count; i++) {
        cout << "Data object " << i << endl;
        ptrDO->read(*ptrData, i);
        ptrDO++;
    }
    ptrData = nullptr;
    ptrDO = nullptr;

    cout << "----------------------------------------------------------------------" << endl << endl;
}

void callReadEraseFromDataObjects(RVM_DataObject &firstDataObject,OneByte &firstObjectReadEraseData, size_t count){
    cout << "--- calling readErase functions Data objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    OneByte *ptrData = &firstObjectReadEraseData;
    RVM_DataObject *ptrDO = &firstDataObject;
    for (size_t i = 0; i < count; i++) {
        cout << "Data object " << i << endl;
        ptrDO->readErase(*ptrData, i);
        ptrDO++;
    }
    ptrData = nullptr;
    ptrDO = nullptr;

    cout << "----------------------------------------------------------------------" << endl << endl;
}

void callDataEnableFromDataObjects(RVM_DataObject &firstDataObject, size_t count){
    cout << "--- calling dataEnable functions Data objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    RVM_DataObject *ptrDO = &firstDataObject;
    for (size_t i = 0; i < count; i++) {
        cout << "Data object " << i << " dataEnable = " << static_cast<int>(ptrDO->dataEnable().value) << endl;
        ptrDO++;
    }
    ptrDO = nullptr;

    cout << "----------------------------------------------------------------------" << endl << endl;
}

void callGetAccessTypeFromDataObjects(RVM_DataObject &firstDataObject, size_t count){
    cout << "--- calling getAccessType functions Data objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    RVM_DataObject *ptrDO = &firstDataObject;
    for (size_t i = 0; i < count; i++) {
        cout << "Data object " << i << " getAccessType = " << static_cast<int>(ptrDO->getAccessType().value) << endl;
        ptrDO++;
    }
    ptrDO = nullptr;

    cout << "----------------------------------------------------------------------" << endl << endl;
}

//! -- displaying function
void displayDataObjects(RVM_DataObject &firstDataObject, size_t count) {
    cout << "--- data into Data objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    RVM_DataObject *ptrShowDO = &firstDataObject;
    for (size_t i = 0; i < count; i++) {
        cout << "Data object " << i << endl;
        ptrShowDO->displayAll();
        ptrShowDO++;
    }
    ptrShowDO = nullptr;

    cout << "----------------------------------------------------------------------" << endl << endl;
}

void displayData(OneByte &firstObject, size_t count){
    cout << "--- data out" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    OneByte *ptrMoveInitData = &firstObject;
    for (size_t i = 0; i < count; i++) {
        ptrMoveInitData = &firstObject;
        cout << "Data for Data object " << i << ":  = ";
        for (size_t j = 0; j < i; j++) {
            cout << static_cast<int>(*ptrMoveInitData) << " ";
            ptrMoveInitData++;
        }
        cout << endl;
    }

    cout << "----------------------------------------------------------------------" << endl << endl;
}

//! -- deleting function
int deleteDataObjects(RVM_DataObject &firstDataObject, size_t count) {
    cout << "--- delete " << count << " Data Objects" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    delete[] &firstDataObject;

    cout << "----------------------------------------------------------------------" << endl << endl;
    return 0;
}

int deleteAttributes(Attributes &firstObject, size_t count) {
    cout << "--- delete " << count << " Attributes" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    delete[] &firstObject;

    cout << "----------------------------------------------------------------------" << endl << endl;
    return 0;
}

int deleteData(OneByte &firstObject, size_t count) {
    cout << "--- delete " << count << " Data" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    delete[] &firstObject;

    cout << "----------------------------------------------------------------------" << endl << endl;
    return 0;
}