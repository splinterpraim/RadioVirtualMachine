#ifndef RVM_CONTROL_UNIT_CLASS
#define RVM_CONTROL_UNIT_CLASS

/* C++ Headers */
#include <iostream>

/* Project Headers */
#include "class_definition.h"
#include "rvm_structs.h"
#include "DO/data_object.h"
#include "APE/abstract_processing_element.h"
#include "ASF/abstract_switch_fabric.h"

#include "configCodeStructure.h"

#include "log_manager.h"


/* Radio Library */
#include "radiolib/functions.h"

// #include "call_back_functions.h"

namespace rvm
{
    // friends functions

    class ControlUnit
    {
    public:

        /* Destructor */
        ~ControlUnit();

        
        /* Configuring */
        int configuringDataObjects();
        int configuringAbstractProcessingElements();
        int configuringAbstractSwitchFabric();


        void showStatus(){}
        void sendStatusFromDataObject(const StatusFromDataObject &statusDO);
        void sendStatusFromAbstractProcessingElement(const StatusFromAbstractProcessingElement &statusAPE);


    private:
        DataObject *dataObjects = nullptr;
        AbstractProcessingElement *abstractProcessingElements = nullptr;
        AbstractSwitchFabric *abstractSwitchFabric = nullptr; 
        size_t dataObjects_size = 0; 
        size_t abstractProcessingElements_size = 0; 


    };
};

///plugs
int countPortsAllAPE();
int countPortsAllDO();
struct ASF_Config readASFconfig(int index);
int getDirectionFromAPE(uint8_t APE_number, uint8_t port_number);

#endif // RVM_CONTROL_UNIT_CLASS
