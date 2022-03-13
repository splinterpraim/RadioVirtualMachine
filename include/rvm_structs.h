
#ifndef RVM_STRUCTS_H
#define RVM_STRUCTS_H

#include <iostream>

enum
{
    empty,
    full
};

enum
{
    inactive,
    active
};
struct StatusFromDataObject
{
    unsigned id : 8;
    unsigned state : 1;      // 0 - empty, 1 - full
    unsigned accessType : 1; // 0 - read,  1 - write
    unsigned exception : 2;

    StatusFromDataObject() : id(0), state(empty), accessType(0), exception(0){}

    void show() const
    {
        std::cout << "id = " << id << std::endl;
        std::cout << "state = " << state << std::endl;
        std::cout << "accessType = " << accessType << std::endl;
        std::cout << "exception = " << exception << std::endl;
    }
};

struct StatusFromAbstractProcessingElement
{
    unsigned id : 8;
    unsigned state : 1; /* 0 - inactive, 1 - active */
    unsigned exception : 2;

    StatusFromAbstractProcessingElement() : id(0), state(inactive), exception(0) {}
    
    void show() const
    {
        std::cout << "id = " << id << std::endl;
        std::cout << "state = " << state << std::endl;
        std::cout << "exception = " << exception << std::endl;
    }
};
#endif // RVM_STRUCTS_H
