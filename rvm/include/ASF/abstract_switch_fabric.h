#ifndef ABSTRACT_SWITCH_FABRIC_CLASS
#define ABSTRACT_SWITCH_FABRIC_CLASS
#include <iostream>
#include <vector>
#include "DO/data_object.h"
#include "APE/abstract_processing_element.h"
typedef struct DataPort_s
{
    DataObject *relatedDO = nullptr;
} DataPort;
typedef struct ProcessingPort_s
{
    AbstractProcessingElement *relatedAPE = nullptr;
    uint8_t port_number = 0;
} ProcessingPort;

typedef struct Connector_s
{
    uint8_t dataPortId = 0;
    uint32_t processingPortId = 0;
    uint8_t dir : 1; /* Direction: LINK_INPUT - from data port to processing port,
                                   LINK_OUTPUT - from processing port to data port */
    uint8_t set = 0;

} Connector;

class AbstractSwitchFabric
{

public:
    /* Destructor */
    ~AbstractSwitchFabric();

    /* Set  number of DataPorts and ProcessingPort  and creat them */
    void set(int numPortsDO, int numPortsAPE);

    /* Create ports */
    void createDataPorts(uint8_t numberPorts);
    void createProcessingPorts(uint32_t numberPorts);

    /* Create connectors */
    void allocConnectors(int numConnectors);

    void createConnector(int DataPortsId, int ProcessingPortsId, int dir);

    /* Set part */
    void createPortDO(int id_DO, int numAPE);
    void createPortAPE(int id_DO, int APE_info);

    /* Init part */
    void associateDataPort(int dataPortId, DataObject &DO);
    void associateProccessingPort(int processingPortId, AbstractProcessingElement &APE, uint8_t portAPE);

    void init(int);

    std::string to_str();

private:
    std::vector<DataPort> dataPorts;
    std::vector<ProcessingPort> processingPorts;
    std::vector<Connector> connectors;
};

#endif // ABSTRACT_SWITCH_FABRIC_CLASS
