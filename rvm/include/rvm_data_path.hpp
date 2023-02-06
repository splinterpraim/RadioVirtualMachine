/**
 * @file rvm_data_path.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Data Path
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_DATA_PATH_CLASS
#define RVM_DATA_PATH_CLASS

#include <vector>

#include "DO/data_object.hpp"
#include "APE/abstract_processing_element.hpp"

class AbstractSwitchFabric;     /* Forward declaration of AbstractSwitchFabric class */

/**
 * @brief Data Path struct implementation
 */
struct rvm_DataPath_s
{
    std::vector<DataObject> dataObjs;               /* All Data Objects */
    std::vector<AbstractProcessingElement>  apes;   /* All Abstract Processing Element */
    AbstractSwitchFabric * asf = nullptr;           /* Pointer on Abstract Switch Fabric */
};
using  rvm_DataPath = struct rvm_DataPath_s;

/**
 * @brief Prints the Data Path to standard output.
 *
 * @param[in]       dataPath                Reference to the Data Path
 */
void rvm_DataPathShow(rvm_DataPath &dataPath);

#endif // RVM_DATA_PATH_CLASS