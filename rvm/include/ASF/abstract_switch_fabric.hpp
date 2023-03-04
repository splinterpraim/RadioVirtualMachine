/**
 * @file abstract_switch_fabric.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Abstract Switch Fabric
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef ABSTRACT_SWITCH_FABRIC_CLASS
#define ABSTRACT_SWITCH_FABRIC_CLASS

#include <iostream>
#include <vector>

class DataObject;                   /* Forward declaration of DataObject class */
class AbstractProcessingElement;    /* Forward declaration of AbstractProcessingElement class */

/**
 * @brief Abstract Switch Fabric data port description
 */
typedef struct DataPort_s
{
    DataObject *relatedDO = nullptr; /* Realted Data Object */
} DataPort;

/**
 * @brief Abstract Switch Fabric processing port description
 */
typedef struct ProcessingPort_s
{
    AbstractProcessingElement *relatedAPE = nullptr;    /* Realted Abstract Processing Element */
    uint8_t port_number = 0;                            /* Port number */
} ProcessingPort;

/**
 * @brief Abstract Switch Fabric connector description
 */
typedef struct Connector_s
{
    uint8_t dataPortId = 0;         /* Data port ID */
    uint32_t processingPortId = 0;  /* Processing port ID */
    uint8_t dir : 1;                /* Direction of data port to processing port: LINK_INPUT - from data port to processing port, LINK_OUTPUT - from processing port to data port */
    uint8_t set = 0;                /* Flag set or not set connector */
} Connector;

/**
 * @brief Abstract Switch Fabric class implementation
 */
class AbstractSwitchFabric
{
public:

    /**
     * @brief Destroys the Abstract Switch Fabric object
     */
    ~AbstractSwitchFabric();

    /**
     * @brief Sets number of data ports and processing ports and creates them
     *
     * @param[in]       numPortsDO              Number of data ports
     * @param[in]       numPortsAPE             Number of processing ports
     */
    void set(int numPortsDO, int numPortsAPE);

    /**
     * @brief Creates another new connector
     *
     * @param[in]       DataPortsId             Data port ID
     * @param[in]       ProcessingPortsId       Processing port ID
     * @param[in]       dir                     Direction of data port to processing port
     */
    void createConnector(int DataPortsId, int ProcessingPortsId, int dir);

    /**
     * @brief Associates data port with related Data Object
     *
     * @param[in]       dataPortId              Data port ID
     * @param[in]       DO                      Reference to related Data Object
     */
    void associateDataPort(int dataPortId, DataObject &DO);

    /**
     * @brief Associates processing port with related Abstract Processing Element
     *
     * @param[in]       processingPortId        Processing port ID
     * @param[in]       APE                     Reference to related Abstract Processing Element
     * @param[in]       portAPE                 Ports number of APE
     */
    void associateProccessingPort(int processingPortId, AbstractProcessingElement &APE, uint8_t portAPE);

    /**
     * @brief Launches the Abstract Switch Fabric for execution
     */
    void run();

    /**
     * @brief Converts Abstract Switch Fabric to string
     *
     * @retval           std::string            Abstract Switch Fabric as string
     */
    std::string to_str();

private:

    std::vector<DataPort> dataPorts;                /* Array of data ports */
    std::vector<ProcessingPort> processingPorts;    /* Array of processing ports */
    std::vector<Connector> connectors;              /* Array of connectors */
    uint32_t connectorCount = 0;                    /* Number of connectors */

    /**
     * @brief Finds connector by processing port ID
     *
     * @param[in]       processingPortId        Processing port ID
     *
     * @retval          Connector&              Reference to the found connector
     */
    Connector & findConnectorByProccessingPortId(uint32_t processingPortId);

    /**
     * @brief Creates a data ports
     *
     * @param[in]       numberPorts             Number of data ports
     */
    void createDataPorts(uint8_t numberPorts);

    /**
     * @brief Creates a processing ports
     *
     * @param[in]       numberPorts             Number of processing ports
     */
    void createProcessingPorts(uint32_t numberPorts);

    /**
     * @brief Allocates connestors
     *
     * @param[in]       numConnectors           Number of connestors
     */
    void allocConnectors(int numConnectors);

    /**
     * @brief Asks Data Objects for their Data Enable state and notifies related Abstract Processing Elements
     */
    void askDOAndNotifyAPE_DataEnable();

    /**
     * @brief Finds an operator ready for data transfer
     *
     * @retval          int32_t                 Unique APE identifier
     * @retval          NOT_FOUND_APE           If unique APE identifier not found
     */
    int32_t findAPEReadyToDataTransfer();

    /**
     * @brief Asks Abstract Processing Element for Access type and notifies related Data Objects
     *
     * @param[in]       APE_id                  Unique APE identifier
     */
    void askAPEAndNotifyDO_AccessType(uint16_t APE_id);

    /**
     * @brief Transfers data from Data Objects to the input ports of a specific Abstract Processing Element
     *
     * @param[in]       APE_id                  Unique APE identifier
     */
    void transferToAPE(uint16_t APE_id);

    /**
     * @brief Transfers data from output ports of specific Abstract Processing Element to the Data Objects
     *
     * @param[in]       APE_id                  Unique APE identifier
     */
    void transferFromAPE(uint16_t APE_id);

    /**
     * @brief Launches a Abstract Processing Element for execution
     *
     * @param[in]       APE_id                  Unique APE identifier
     */
    void runAPE(uint16_t APE_id);

    /**
     * @brief Gets the first processing port related with specific data port
     *
     * @param[in]       dPort_i                 Index of specific data port
     *
     * @retval          size_t                  Index of first processing port or if port don`t exist size of processing ports 
     */
    size_t getFirstRelatedProcessingPort(size_t dPort_i);

    /**
     * @brief Gets the next processing port related with specific data port since of specific processing port
     *
     * @param[in]       dPort_i                 Index of specific data port
     * @param[in]       pPort_i                 Index of specific processing port
     *
     * @retval          size_t                  Index of next processing port or if port don`t exist size of processing ports 
     */
    size_t getNextRelatedProcessingPort(size_t dPort_i, size_t pPort_i);

        /**
     * @brief Gets the first processing port related with specific APE
     *
     * @param[in]       APE_id                  Index of specific APE
     *
     * @retval          size_t                  Index of first processing port or if port don`t exist size of processing ports 
     */
    size_t getFirstProcessingPortRelatedWithAPE(size_t APE_id);

    /**
     * @brief Gets the next processing port related with specific APE since of specific processing port
     *
     * @param[in]       APE_id                  Index of specific APE
     * @param[in]       pPort_i                 Index of specific processing port
     *
     * @retval          size_t                  Index of next processing port or if port don`t exist size of processing ports 
     */
    size_t getNextProcessingPortRelatedWithAPE(size_t APE_id, size_t pPort_i);
};

#endif // ABSTRACT_SWITCH_FABRIC_CLASS
