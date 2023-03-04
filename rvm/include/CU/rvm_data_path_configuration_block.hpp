/**
 * @file rvm_data_path_configuration_block.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Data Path Configuration Block
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_DATA_PATH_CONFIGURATION_BLOCK_CLASS
#define RVM_DATA_PATH_CONFIGURATION_BLOCK_CLASS

#include <cstdint>

class rvm_operationFetcher;                     /* Forward declaration of rvm_operationFetcher class */
struct StatusFromDataObject;                    /* Forward declaration of StatusFromDataObject struct */
struct StatusFromAbstractProcessingElement;     /* Forward declaration of StatusFromAbstractProcessingElement struct */
struct ConfigObjects;                           /* Forward declaration of ConfigObjects struct */
using ControlSection = struct ControlSection;
struct rvm_DataPath_s;                          /* Forward declaration of rvm_DataPath struct */
using rvm_DataPath = struct rvm_DataPath_s;


/**
 * @brief Data Path Configuration Block class implementation
 */
class rvm_dataPathConfigurationBlock
{
public:

    /**
     * @brief Constructs a new rvm dataPathConfigurationBlock object
     */
    rvm_dataPathConfigurationBlock();

    /**
     * @brief Associates Data path configuration block with other related blocks
     *
     * @param[in]       dataPath                Related Data path Block
     * @param[in]       opFetcher               Related Operation Fetcher Block
     */
    void associate(rvm_DataPath &dataPath, rvm_operationFetcher &opFetcher);

    /**
     * @brief Сonfigures data path using a config code objects
     *
     * @param[in]       cfgCode                 Reference on Config code objects
     */
    void configure(ConfigObjects &cfgCode);

    /**
     * @brief Launches the DataPath for main work
     */
    void runDataPath();

    /**
     * @brief Clears Data Path configured by configure()
     */
    void clear();

    /**
     * @brief Sends status from Data Object
     *
     * @param[in]       statusDO                Status of Data Object
     */
    void sendStatusFromDataObject(const StatusFromDataObject &statusDO);

    /**
     * @brief Sends status from Abstract Processing Element
     *
     * @param[in]       statusAPE               Status of Abstract Processing Element
     */
    void sendStatusFromAbstractProcessingElement(const StatusFromAbstractProcessingElement &statusAPE);

private:

    rvm_DataPath *dataPath = nullptr;           /* Externally related Data Path Block */
    rvm_operationFetcher *opFetcher = nullptr;  /* Externally related Operation Fetcher Block */
    bool errorHand = false;                     /* Error handle */

    /**
     * @brief Сonfigures data objects using a config code objects
     *
     * @param[in]       cfgCode                 Reference on Config code objects
     */
    void configureDataObjects(ConfigObjects &cfgCode);

    /**
     * @brief Сonfigures abstract processing elements using a config code objects
     *
     * @param[in]       cfgCode                 Reference on Config code objects
     */
    void configureAbstractProcessingElements(ConfigObjects &cfgCode);

    /**
     * @brief Сonfigures abstract switch fabric using a config code objects
     *
     * @param[in]       cfgCode                 Reference on Config code objects
     */
    void configureAbstractSwitchFabric(ConfigObjects &cfgCode);

    /**
     * @brief Gets the direction of DO to APE
     *
     * @param[in]       cfgCode                 Reference on Config code objects
     * @param[in]       APE_Id                  Abstract proccessing element ID
     * @param[in]       port_number             Port number of APE
     *
     * @retval          int                     Direction of DO to APE
     */
    int getDirectionFromAPE(ConfigObjects &cfgCode, uint8_t APE_Id, uint8_t port_number);
};

#endif // RVM_DATA_PATH_CONFIGURATION_BLOCK_CLASS