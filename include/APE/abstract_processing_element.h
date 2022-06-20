#ifndef RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS
#define RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS

#include <iostream>
#include <string>
#include <map>

#include "CU/control_unit.h"

namespace rvm
{

    // struct PortsAccessTypes{
    //     int size;
    //     std::vector<int> accessTypes;
    // };

    class AbstractProcessingElement
    {
    public:
        /* Constructor */
        AbstractProcessingElement();

        /* Destructor */
        ~AbstractProcessingElement();

        /**
         * @brief Sets Abstract Processing Element attributes
         *
         * @param id[in] Identifier to Abstract Processing Element
         * @param cost[in] The execution cost
         * @param time[in] The execution time
         * @param T[in] Flag dynamic operations
         * @param portsAccessTypes[in] Map of  
         * @return int: 0 - if the function worked without errors, -1 - if the function worked with errors
         */
        int set(uint16_t id,  uint16_t cost, uint16_t time, uint16_t T, const std::map<uint8_t, uint8_t> & portsAccessTypes);

        
        /* Initializes APE of a specific operation */
        /**
         * @brief Initializes bstract Processing Element of a specific operation 
         *
         * @param opcode[in] The specific operation code 
         * @param operation[in] The specific operation from Radio Library
         * @return int: 0 - if the function worked without errors, -1 - if the function worked with errors
         */
        int init(const uint32_t &opcode, int (*operation)(uint8_t argc, ...));

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
        uint8_t T = 0;


        uint32_t opcode = 0;
        int (*operation)(uint8_t argc, ...);

        ControlUnit *cu = nullptr;

        StatusFromAbstractProcessingElement status;

        struct portAPE //? map using?
        {
            uint8_t num = 0;
            uint8_t accessTypes = 0; /*  Port type  */
        };

        portAPE *ports = nullptr;
        uint8_t numPorts = 0;

        /* for dynamic operations */
    };
};

#endif // RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS
