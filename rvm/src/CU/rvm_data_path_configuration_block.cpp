
#include "CU/rvm_data_path_configuration_block.hpp"

void rvm_dataPathConfigurationBlock::associate(rvm_DataPath &dataPath)
{
    this->dataPath = &dataPath;
}

int rvm_dataPathConfigurationBlock::configure(ConfigObjects &cfgCode)
{

    // get real data from cfgCode
     configuringDataObjects();
     configuringAbstractProcessingElements();
     configuringAbstractSwitchFabric();
}

int rvm_dataPathConfigurationBlock::configuringDataObjects()
{
}
int rvm_dataPathConfigurationBlock::configuringAbstractProcessingElements()
{
}
int rvm_dataPathConfigurationBlock::configuringAbstractSwitchFabric()
{
}