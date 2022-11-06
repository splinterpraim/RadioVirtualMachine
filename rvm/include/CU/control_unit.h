#ifndef RVM_CONTROL_UNIT_CLASS
#define RVM_CONTROL_UNIT_CLASS

/* C++ Headers */
#include <iostream>

/* Project Headers */
#include "class_definition.h"
#include "rvm_structs.h"
#include "CU/rvm_cfg_code_fetcher.hpp"
#include "CU/rvm_data_path_configuration_block.hpp"
#include "DO/data_object.h"
#include "APE/abstract_processing_element.h"
#include "ASF/abstract_switch_fabric.h"

#include "rvm_program_mem.hpp"
#include "rvm_basic_operations.hpp"
#include "rvm_data_path.hpp"


#include "config_code_structure.hpp"

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


        /* Work function */
        void work();


        /**
         * @brief Associates Control Unit with other related blocks
         * 
         * @param programMemory 
         * @param basicOperations 
         * @param dataPath 
         */
        void associate(rvm_ProgramMemory &programMemory, rvm_BasicOperations &basicOperations, rvm_DataPath & dataPath);

        
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

        uint32_t cfgCounter = 0;
        rvm_cfgCodeFetcher cfgFetcher;
        rvm_dataPathConfigurationBlock cfgnBlock;



        /* Associated objects */
        rvm_ProgramMemory * programMemory  = nullptr;
        rvm_BasicOperations * basicOperations  = nullptr;
        rvm_DataPath * dataPath  = nullptr;


    };
};

///plugs
int countPortsAllAPE();
int countPortsAllDO();
struct ASF_Config readASFconfig(int index);
int getDirectionFromAPE(uint8_t APE_number, uint8_t port_number);

#endif // RVM_CONTROL_UNIT_CLASS
