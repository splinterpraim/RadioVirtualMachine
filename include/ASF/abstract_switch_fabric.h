#ifndef ABSTRACT_SWITCH_FABRIC_CLASS
#define ABSTRACT_SWITCH_FABRIC_CLASS
#include <iostream>
#include "DO/data_object.h"
#include "APE/abstract_processing_element.h"
struct DataPort
{
    rvm::DataObject *relatedDO;
};
struct ProcessingPort
{
    rvm::AbstractProcessingElement *relatedAPE;
    uint8_t number;
};

struct Connector
{
    uint8_t dataPortId;
    uint32_t processingPortId;
    uint8_t dir : 1; /* Direction: 0 - from data port to processing port,
                                   1 - from processing port to data port */
};

namespace rvm
{
    class AbstractSwitchFabric
    {

    public:
        /* Destructor */
        ~AbstractSwitchFabric();

        /* Create ports */
        void createDataPorts(uint8_t numberPorts);
        void createProcessingPorts(uint32_t numberPorts);

        /* Set part */
        void createPortDO(int id_DO, int numAPE);
        void createPortAPE(int id_DO, int APE_info);

        /* Init part */
        associateDataPort(int dataPortId, uint8_t *DO);
        associateProccessingPort(int processingPortId, uint8_t *APE);

        void init(int);

    private:
        struct DataPort *dataPorts;
        struct ProcessingPort *processingPorts;
        struct Connector *connectors;

        int dataPorts_size;
        int processingPorts_size;
        int connectors_size;
    };

};

#endif // ABSTRACT_SWITCH_FABRIC_CLASS
