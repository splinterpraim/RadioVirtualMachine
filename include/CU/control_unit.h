#ifndef RVM_CONTROL_UNIT_CLASS
#define RVM_CONTROL_UNIT_CLASS

#include <iostream>
#include "class_definition.h"
#include "rvm_structs.h"
#include "DO/data_object.h"
#include "APE/abstract_processing_element.h"
#include "ASF/abstract_switch_fabric.h"

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
        DataObject *dataObjects;
        AbstractProcessingElement *abstractProcessingElements;
        AbstractSwitchFabric *abstractSwitchFabric; 
        size_t dataObjects_size = 10;
        size_t abstractProcessingElements_size = 10;


    };
};
#endif // RVM_CONTROL_UNIT_CLASS
