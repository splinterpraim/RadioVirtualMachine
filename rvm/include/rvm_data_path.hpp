#ifndef RVM_DATA_PATH_CLASS
#define RVM_DATA_PATH_CLASS

#include "DO/data_object.h"
#include "APE/abstract_processing_element.h"
#include "ASF/abstract_switch_fabric.h"

struct rvm_DataPath_s
{
    rvm::DataObject * dataObjs = nullptr;
    rvm::AbstractProcessingElement * ape = nullptr;
    rvm::AbstractSwitchFabric * asf = nullptr;
};
using  rvm_DataPath = struct rvm_DataPath_s;


#endif // RVM_DATA_PATH_CLASS