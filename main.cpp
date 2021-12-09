#include <iostream>
#include "source/RVM_DataObject.h"
#include "source/ASF_ContainerPorts.h"

#include <thread>
#include <chrono>
#include <string>
#include <mutex>
#include <stdio.h>
#include <typeinfo>
#include <array>
#include <vector>


// file with function to test
#include "tests/test_DataObject.h"

using namespace std;
//using OneByte = uint8_t;



void showDataEnable(RVM_DataObject &obj) {
    cout << "     || data enable = " << static_cast<unsigned int>(obj.dataEnable().value) << endl;
}

void showDOException(RVM_DataObject &obj) {
    RMV_DataObject_Exceptions ex;
    ex = obj.readException();
    cout << " ||| ex =  " << static_cast<unsigned int>(ex.value1) << " " << static_cast<unsigned int>(ex.value0)
         << endl;
}

void testing() {
    test_ConstructorDestructorDO();
    test_SetFunctionDO();
    test_InitFunctionDO();
    test_WriteFunctionDO();
    test_ReadFunctionDO();
    test_ReadEraseFunctionDO();
    test_DataEnableFunctionDO();
    test_GetAccessTypeFunctionDO();

}

void foo() {

//    RVM_DataObject DO;
//    OneByte * ptrOneData = new OneByte[1];
//    ptrOneData[0] = 2;
//    DO.set({1,1,1});
//    DO.init(*ptrOneData,1);
//    DO.displayAll();

    // create ASF_ContainerPorts
    size_t capacity = 2;
    ASF::ASF_ContainerPorts<ASF::ASF_PortData> dataPorts(capacity);
    cout << "capacity = " << dataPorts.capacity() << endl;
    cout << "size = " << dataPorts.size() << endl;
    ASF::ASF_PortData *portDO = new ASF::ASF_PortData[capacity];
    auto *portMoveDO = portDO;
    portMoveDO->setNumber(2);     portMoveDO++;
    portMoveDO->setNumber(1);
    portMoveDO = portDO;

    dataPorts.append(*portMoveDO);
    portMoveDO++;
    dataPorts.append(*portMoveDO);
    dataPorts.append(*portMoveDO);
    dataPorts.displayAll();
    dataPorts.get(0).setNumber(3);
    dataPorts.displayAll();



//    portDO.setNumber(1);
//    portDO.setDataObject(DO);
//    ptrOneData[0] = 3;
//    portDO.write(*ptrOneData, 1);
//    DO.displayAll();
//
    delete[] portDO;
}


int main() {
    try {
        foo();

    }

    catch (int er) {
        cout << "catch in main " << er << endl;
    }

    return 0;
}
