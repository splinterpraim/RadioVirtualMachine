#ifndef RVM_DATA_PATH_CLASS
#define RVM_DATA_PATH_CLASS

#include "class_definition.h"


struct rvm_DataPath_s
{
    DataObject * dataObjs = nullptr;
    AbstractProcessingElement * apes = nullptr;
    AbstractSwitchFabric * asf = nullptr;
};
using  rvm_DataPath = struct rvm_DataPath_s;


#endif // RVM_DATA_PATH_CLASS