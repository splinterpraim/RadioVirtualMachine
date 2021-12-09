//
// Created by oem on 05.12.2021.
//

#ifndef RADIOVIRTUALMACHINE_ASF_CONTAINERPORTS_H
#define RADIOVIRTUALMACHINE_ASF_CONTAINERPORTS_H

#include "RVM_Types.h"
#include "RVM_DataObject.h"

namespace ASF {

    //! ASF_PortData
    //!************************************************************************************************
    class ASF_PortData {
        Number number;
        RVM_DataObject *DO;

    public:
        ASF_PortData();

        ASF_PortData(const ASF_PortData &portDO);

        ~ASF_PortData();

        void setNumber(Number newNumber);

        Number getNumber();

        void setDataObject(RVM_DataObject &newDO);


        // interface functions
        void write(OneByte &ref, SizeType size);

        void read(OneByte &ref, SizeType size);

        void readErase(OneByte &ref, SizeType size);

        DataEnableFlag dataEnable();

        void setAccessType(AccessType newAccessType);
    };

    //! ASF_PortAPE
    //!************************************************************************************************
    using RVM_AbstractProcessingElement = int;

    class ASF_PortAPE {
        Number number;
        RVM_AbstractProcessingElement *APE;

    public:
        ASF_PortAPE();

        ASF_PortAPE(const ASF_PortAPE &portAPE);

        ~ASF_PortAPE();

        void setNumber(Number newNumber);

        Number getNumber();

        void setDataObject(RVM_AbstractProcessingElement &newAPE);

        // interface functions
        void write(OneByte &ref, SizeType size);

        void read(OneByte &ref, SizeType size) {}

        void readErase(OneByte &ref, SizeType size) {}

        DataEnableFlag dataEnable() {}

        void setAccessType(AccessType newAccessType) {}
    };

    //! ASF_ContainerPorts
    //!************************************************************************************************
    template<class T>
    class ASF_ContainerPorts {
        T *ports;
        size_t portsSize;
        size_t portsCapacity;

    public:

        ASF_ContainerPorts(size_t capacity);

        ~ASF_ContainerPorts();

        T &allocateMemory(size_t capacity);

        int freeMemory(T &firstMemoryObject);

        void append(T &object);

        int remove(Number number);

        T &get(Number number);

        size_t find(Number number);


        size_t size();

        size_t capacity();

        void displayAll();

        void displaySizeCapacity();

        void displayPorts();
    };


    template<class T>
    ASF_ContainerPorts<T>::ASF_ContainerPorts(size_t capacity) {
        std::cout << "call constructor ASF_ContainerPorts (" << capacity << ")" << std::endl;
        ports = &allocateMemory(capacity);
        this->portsSize = 0;
        this->portsCapacity = capacity;
    }

    template<class T>
    ASF_ContainerPorts<T>::~ASF_ContainerPorts() {
        std::cout << "call destructor ~ASF_ContainerPorts" << std::endl;
        if (portsCapacity != 0) {
            freeMemory(*ports);
        }
    }

    template<class T>
    T &ASF_ContainerPorts<T>::allocateMemory(size_t capacity) {
        std::cout << "-ASF_ContainerPorts::allocateMemory(" << capacity << ")" << std::endl;
        T *ptr;
        try {
            ptr = new T[capacity];
        }
        catch (const std::bad_alloc &err) {
            std::cout << err.what() << std::endl;
        }
        return *ptr;
    }

    template<class T>
    int ASF_ContainerPorts<T>::freeMemory(T &firstMemoryObject) {
        std::cout << "-ASF_ContainerPorts::freeMem()" << std::endl;
        delete[] &firstMemoryObject;
        return 0;
    }

    template<class T>
    void ASF_ContainerPorts<T>::append(T &object) {
        std::cout << "-ASF_ContainerPorts::append(" << static_cast<void *>(&object) << ")" << std::endl;
        if ((portsSize) >= portsCapacity) {
            std::cout << "Error: capacity exceeded" << std::endl;
        } else {
            ports[portsSize] = object;
            portsSize++;
        }
    }

    template<class T>
    int ASF_ContainerPorts<T>::remove(Number number) {
        Number localNumber = find(number);
        if (localNumber != -1){
            std::cout << "find Num = " << localNumber << std::endl;
            //remove
        }
        return -1;
    }

    template<class T>
    T &ASF_ContainerPorts<T>::get(Number number) {
        Number localNumber = find(number);
        if (localNumber != -1){
            std::cout << "find Num = " << localNumber << std::endl;
            return *(ports + localNumber);
        }
       // return buff object;
       //
    }

    template<class T>
    size_t ASF_ContainerPorts<T>::find(Number number) {
        T *ptr = ports;
        for (size_t i = 0; i < portsSize; i++) {
            Number localNumber= ptr->getNumber();
            if (localNumber == number)
                return i;
            ptr++;
        }
        std::cout << "Error: don't find number = " << number << std::endl;
        return -1;
    }

    template<class T>
    size_t ASF_ContainerPorts<T>::size() {
        return portsSize;
    }

    template<class T>
    size_t ASF_ContainerPorts<T>::capacity() {
        return portsCapacity;
    }

    template<class T>
    void ASF_ContainerPorts<T>::displayAll() {
        std::cout << "-ASF_ContainerPorts::displayAll()" << std::endl;
        displaySizeCapacity();
        displayPorts();
    }

    template<class T>
    void ASF_ContainerPorts<T>::displayPorts() {
        T *ptr = ports;
        for (size_t i = 0; i < portsSize; i++) {
            Number n = ptr->getNumber();
            std::cout << "ports number " << n << std::endl;
            ptr++;
        }
        std::cout << std::endl;
    }

    template<class T>
    void ASF_ContainerPorts<T>::displaySizeCapacity() {
        std::cout << "size =  " << portsSize << " capacity = " << portsCapacity << std::endl;

    }




}


#endif //RADIOVIRTUALMACHINE_ASF_CONTAINERPORTS_H
