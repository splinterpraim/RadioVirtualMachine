//
// Created by oem on 27.11.2021.
//

#ifndef RADIOVIRTUALMACHINE_TEST_DATAOBJECT_H
#define RADIOVIRTUALMACHINE_TEST_DATAOBJECT_H
//! >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// testing functions
void test_ConstructorDestructorDO();
void test_SetFunctionDO();
void test_InitFunctionDO();
void test_WriteFunctionDO();
void test_ReadFunctionDO();
void test_ReadEraseFunctionDO();
void test_DataEnableFunctionDO();
void test_GetAccessTypeFunctionDO();
void test_SetAccessTypeFunctionDO();
void test_readExceptionFunctionDO();

//! >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// secondary functions
//! -- creating function
RVM_DataObject& createDataObjects(size_t count);
Attributes& createAttributes(size_t count);
OneByte& createData(size_t count, int start = 0);

//! -- calling function
void callSetFromDataObjects(RVM_DataObject &firstDataObject, Attributes &firstObjectAttributes, size_t count);
void callInitFromDataObjects(RVM_DataObject &firstDataObject,OneByte &firstObjectInitData, size_t count);
void callWriteFromDataObjects(RVM_DataObject &firstDataObject,OneByte &firstObjectWriteData, size_t count);
void callReadFromDataObjects(RVM_DataObject &firstDataObject,OneByte &firstObjectReadData, size_t count);
void callReadEraseFromDataObjects(RVM_DataObject &firstDataObject,OneByte &firstObjectReadData, size_t count);
void callDataEnableFromDataObjects(RVM_DataObject &firstDataObject, size_t count);
void callGetAccessTypeFromDataObjects(RVM_DataObject &firstDataObject, size_t count);

//! -- displaying function
void displayDataObjects(RVM_DataObject &firstObject, size_t count);
void displayData(OneByte &firstObject, size_t count);

//! -- deleting function
int deleteDataObjects(RVM_DataObject &firstObject, size_t count);
int  deleteAttributes(Attributes &firstObject,size_t count);
int deleteData(OneByte &firstObject, size_t count);

#endif //RADIOVIRTUALMACHINE_TEST_DATAOBJECT_H
