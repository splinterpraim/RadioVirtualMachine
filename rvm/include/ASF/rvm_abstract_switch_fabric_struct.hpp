/**
 * @file rvm_abstract_switch_fabric_struct.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Data Transfer Thread
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_ABSTRACT_SWITCH_FABRIC_STRUCT
#define RVM_ABSTRACT_SWITCH_FABRIC_STRUCT

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
    uint8_t dataPortId = 0;                     /* Data port ID */
    uint32_t processingPortId = 0;              /* Processing port ID */
    DataPort * dataPort = nullptr;              /* Data port pointer */
    ProcessingPort * processingPort = nullptr;  /* Data port pointer */
    uint8_t dir : 1;                            /* Direction of data port to processing port: LINK_INPUT - from data port to processing port, LINK_OUTPUT - from processing port to data port */
    uint8_t set = 0;                            /* Flag set or not set connector */
} Connector;


#endif // RVM_ABSTRACT_SWITCH_FABRIC_STRUCT
