#ifndef RVM_DATA_PATH_CONFIGURATION_BLOCK_CLASS
#define RVM_DATA_PATH_CONFIGURATION_BLOCK_CLASS

#include "class_definition.h"
#include "CU/rvm_operation_fetcher.hpp"

#include "rvm_data_path.hpp"
#include "config_code_structure.hpp"
#include "rvm_structs.h"

class rvm_dataPathConfigurationBlock
{
public:
    rvm_dataPathConfigurationBlock();

    /**
     * @brief Associates Data path configuration block with other related blocks
     *
     * @param[in] dataPath Data path
     */
    void associate(rvm_DataPath &dataPath, rvm_operationFetcher &opFetcher);

    /**
     * @brief Сonfigures data path using a config code objects
     *
     * @param cfgCode Config code objects
     * @return int
     */
    int configure(ConfigObjects &cfgCode);

    /**
     * @brief Runs data path on work
     *
     */
    void runDataPath();

    void sendStatusFromDataObject(const StatusFromDataObject &statusDO);
    void sendStatusFromAbstractProcessingElement(const StatusFromAbstractProcessingElement &statusAPE);

private:
    rvm_DataPath *dataPath = nullptr;
    rvm_operationFetcher *opFetcher = nullptr;

    bool errorHand = false; /* Error handle */

    /**
     * @brief Сonfigures data objects using a config code objects
     *
     * @param[in] cfgCode Config code objects
     */
    void configureDataObjects(ConfigObjects &cfgCode);

    /**
     * @brief Сonfigures abstract processing elements using a config code objects
     *
     * @param[in] cfgCode Config code objects
     */
    void configureAbstractProcessingElements(ConfigObjects &cfgCode);

    /**
     * @brief Сonfigures abstract switch fabric using a config code objects
     *
     * @param[in] cfgCode Config code objects
     */
    void configureAbstractSwitchFabric(ConfigObjects &cfgCode);


    int getDirectionFromAPE(ConfigObjects &cfgCode, uint8_t APE_Id, uint8_t port_number);
};
#endif // RVM_DATA_PATH_CONFIGURATION_BLOCK_CLASS