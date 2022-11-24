#ifndef RVM_DATA_PATH_CLASS
#define RVM_DATA_PATH_CLASS

#include "class_definition.h"
#include <vector>


struct rvm_DataPath_s
{
    std::vector<DataObject> dataObjs;
    std::vector<AbstractProcessingElement>  apes;
    AbstractSwitchFabric * asf = nullptr;
};
using  rvm_DataPath = struct rvm_DataPath_s;

void rvm_DataPathShow(rvm_DataPath &dataPath);

#endif // RVM_DATA_PATH_CLASS