#ifndef RVM_DATA_PATH_CONFIGURATION_BLOCK_CLASS
#define RVM_DATA_PATH_CONFIGURATION_BLOCK_CLASS

#include "rvm_data_path.hpp"
#include "config_code_structure.hpp"


class rvm_dataPathConfigurationBlock
{
public:
    void associate(rvm_DataPath &dataPath);

    int configure(ConfigObjects &cfgCode);
private:
    rvm_DataPath *dataPath = nullptr;

    /* Configuring */
    int configuringDataObjects();
    int configuringAbstractProcessingElements();
    int configuringAbstractSwitchFabric();
};
#endif // RVM_DATA_PATH_CONFIGURATION_BLOCK_CLASS