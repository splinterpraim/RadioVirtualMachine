#ifndef RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS
#define RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS

#include <iostream>
#include <string>
#include "CU/control_unit.h"

namespace rvm
{
    class AbstractProcessingElement
    {
    public:
        /* Constructor */
        AbstractProcessingElement();
 
        /* Destructor */
        ~AbstractProcessingElement();

        /* Sets APE id and number of ports */
        int setID(uint16_t id, uint8_t numPorts);

        /* Sets access type to specific port, and cost, time */
        int set(uint8_t portNumber, const uint8_t accessTypes, uint16_t cost, uint16_t time);

        /* Initializes APE of a specific operation */
        int init(const uint32_t &opcode,  int (*operation)(uint8_t argc, ...));

        /* Sets a pointer to the associated Control Unit */
        void setSendControlUnit(ControlUnit &cu);
        
        
        /* other */
        int checkCallBack();
        void doOperation();
        std::string to_str();

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
