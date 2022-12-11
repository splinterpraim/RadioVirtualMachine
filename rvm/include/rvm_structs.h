
#ifndef RVM_STRUCTS_H
#define RVM_STRUCTS_H

#include <iostream>
#include <string>

enum stDO
{
    empty = 0,
    full
};

enum exDO
{
    NOEXCEPT = 0,
    OP_WITH_BIGSIZE,
    WRITE_CONFL,
    READ_ERASE_CONFL
};

enum stAPE
{
    inactive,
    active
};

namespace at
{
    enum
    {
        read,
        write,
        readErase
    };

}
struct StatusFromDataObject
{
    uint8_t id : 8;
    uint8_t state : 1;      // stDO::empty - empty, stDO::full - full
    uint8_t accessType : 2; // 0 - at::read,  1 - at::write, 2 - at::readErase
    uint8_t exception : 2; //

    StatusFromDataObject() : id(0), state(stDO::empty), accessType(0), exception(0) {}

    std::string to_str() const
    {
        std::string result_str = "id " + std::to_string(id) + ", " +
                                 "state " + std::to_string(state) + ", " +
                                 "accessType " + std::to_string(accessType) + ", " +
                                 "exception " + std::to_string(exception);
        return result_str;
    }
};

struct StatusFromAbstractProcessingElement
{
    uint16_t id : 16;
    uint8_t state : 1; /* 0 - inactive, 1 - active */
    uint8_t exception : 2;

    StatusFromAbstractProcessingElement() : id(0), state(stAPE::inactive), exception(0) {}

    std::string to_str() const
    {
        std::string result_str = "id " + std::to_string(id) + ", " +
                                 "state " + std::to_string(state) + ", " +
                                 "exception " + std::to_string(exception);
        return result_str;
    }
};
#endif // RVM_STRUCTS_H
