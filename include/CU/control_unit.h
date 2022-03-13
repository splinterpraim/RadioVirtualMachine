#ifndef RVM_CONTROL_UNIT_CLASS
#define RVM_CONTROL_UNIT_CLASS

#include <iostream>
#include "class_definition.h"
#include "rvm_structs.h"
#include "DO/data_object.h"
#include "APE/abstract_processing_element.h"

/* Radio Library */
#include "radiolib/functions.h"

// #include "call_back_functions.h"

namespace rvm
{
    // friends functions

    class ControlUnit
    {
    public:
        int configuringDataObjects();
        int configuringAbstractProcessingElements();

        void showStatus(){}
        void sendStatusFromDataObject(const StatusFromDataObject &statusDO);
        void sendStatusFromAbstractProcessingElement(const StatusFromAbstractProcessingElement &statusAPE);


    private:
        DataObject *dataObjects;
        AbstractProcessingElement *abstractProcessingElements;
        size_t dataObjects_size = 10;
        size_t abstractProcessingElements_size = 10;


    };
};
#endif // RVM_CONTROL_UNIT_CLASS
