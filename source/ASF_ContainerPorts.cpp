//
// Created by oem on 05.12.2021.
//

#include "ASF_ContainerPorts.h"

namespace ASF {

    //! ASF_PortData
    //!************************************************************************************************
    ASF_PortData::ASF_PortData() {
        std::cout << "call constructor ASF_PortData" << std::endl;
        number = 0;
        DO = nullptr;
    }

    ASF_PortData::ASF_PortData(const ASF_PortData &portDO) {
        std::cout << "call copy constructor ASF_PortData" << std::endl;
        number = portDO.number;
        DO = portDO.DO;
    }

    ASF_PortData::~ASF_PortData() {
        std::cout << "call destructor ~ASF_PortData" << std::endl;
    }

    void ASF_PortData::setNumber(Number newNumber) {
        std::cout << "-ASF_PortData::setNumber(" << newNumber << ")" << std::endl;
        number = newNumber;
    }

    Number ASF_PortData::getNumber() {
        std::cout << "-ASF_PortData::getNumber()" << std::endl;
        return number;
    }

    void ASF_PortData::setDataObject(RVM_DataObject &newDO) {
        std::cout << "-ASF_PortData::setDataObject(" << static_cast<void *>(&newDO) << ")" << std::endl;
        DO = &newDO;
    }


    //! interface functions
    void ASF_PortData::write(OneByte &ref, SizeType size) {
        std::cout << "-ASF_PortData::write(" << static_cast<void *>(&ref) << ", " << size << ")" << std::endl;
        DO->write(ref, size);
    }

    void ASF_PortData::read(OneByte &ref, SizeType size) {
        std::cout << "-ASF_PortData::read(" << static_cast<void *>(&ref) << ", " << size << ")" << std::endl;
        DO->read(ref, size);
    }

    void ASF_PortData::readErase(OneByte &ref, SizeType size) {
        std::cout << "-ASF_PortData::readErase(" << static_cast<void *>(&ref) << ", " << size << ")" << std::endl;
        DO->readErase(ref, size);
    }

    DataEnableFlag ASF_PortData::dataEnable() {
        std::cout << "-ASF_PortData::dataEnable()" << std::endl;
        return DO->dataEnable();
    }

    void ASF_PortData::setAccessType(AccessType newAccessType) {
        std::cout << "-ASF_PortData::setAccessType(" << static_cast<int>(newAccessType.value) << ")" << std::endl;
        DO->setAccessType(newAccessType);
    }




    //! ASF_PortAPE
    //!************************************************************************************************
    ASF_PortAPE::ASF_PortAPE() {
        std::cout << "call constructor ASF_PortAPE" << std::endl;
        number = 0;
        APE = nullptr;
    }

    ASF_PortAPE::ASF_PortAPE(const ASF_PortAPE &portAPE) {
        number = portAPE.number;
        APE = portAPE.APE;
    }

    ASF_PortAPE::~ASF_PortAPE() {
        std::cout << "call destructor ~ASF_PortAPE" << std::endl;

    }

    void ASF_PortAPE::setNumber(Number newNumber) {
        std::cout << "-ASF_PortAPE::setNumber(" << newNumber << ")" << std::endl;
        number = newNumber;
    }

    Number ASF_PortAPE::getNumber() {
        std::cout << "-ASF_PortAPE::getNumber()" << std::endl;
        return number;
    }

    void ASF_PortAPE::setDataObject(RVM_AbstractProcessingElement &newAPE) {
        std::cout << "-ASF_PortAPE::setDataObject(" << static_cast<void *>(&newAPE) << ")" << std::endl;
        APE = &newAPE;
    }

    void ASF_PortAPE::write(OneByte &ref, SizeType size) {
        std::cout << "-ASF_PortAPE::write(" << static_cast<void *>(&ref) << ", " << size << ")" << std::endl;
//        APE->write(ref, size);
    }


}
