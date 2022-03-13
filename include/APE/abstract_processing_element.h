#ifndef RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS
#define RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS

#include <iostream>

#include "CU/control_unit.h"

namespace rvm
{
    class AbstractProcessingElement
    {
    public:
        AbstractProcessingElement();
        ~AbstractProcessingElement();

        int set(uint8_t numPorts, const uint8_t &accessTypes, uint16_t cost, uint16_t time);
        int init(const uint32_t &opcode,  int (*operation)(uint8_t argc, ...));

        void setSendControlUnit(ControlUnit &cu);


        int checkCallBack();

    private:
        uint16_t id = 0;
        uint16_t cost = 0;
        uint16_t time = 0;
        uint32_t opcode = 0;
        int (*operation)(uint8_t argc, ...);

        ControlUnit *cu = nullptr;

        StatusFromAbstractProcessingElement status;

        struct portAPE {
            uint8_t accessTypes = 0;    /*  Port type  */
        };

        portAPE *ports = nullptr;
        uint8_t numPorts = 0;
    };
};

#endif // RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS
