/**
 * @file abstract_processing_element.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Abstract Processing Element
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS
#define RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS

#include <iostream>
#include <string>
#include <vector>

#include "CU/rvm_threadsafe_queue.hpp"
#include "rvm_structs.h"

class rvm_dataPathConfigurationBlock;   /* Forward declaration of rvm_dataPathConfigurationBlock class */

/**
 * @brief Abstract Processing Element port description
 */
struct PortAPE_s
{
    uint8_t num = 0;            /* Port number */
    uint8_t accessTypes = 0;    /* Port type */
};
typedef struct PortAPE_s PortAPE;

/**
 * @brief Manager for ports of Abstract Processing Element
 */
class APEportManager
{
public:

    /**
     * @brief Constructs a new APEportManager object
     */
    APEportManager();

    /**
     * @brief Destroy the APEportManager object
     */
    ~APEportManager();

    /**
     * @brief Initializes manager of ports of APE
     *
     * @param[in]       numPorts                Number of ports APE
     */
    void init(uint8_t numPorts);

    /**
     * @brief Associates Manager of ports APE with related ports in APE
     *
     * @param[in]       portsAPE                Related ports of APE
     */
    void associate(std::vector<PortAPE> &portsAPE);

    /**
     * Commits changes of data enables for specific ports APE and changes port state if necessary.
     * @param[in]       portNumber              Port number
     * @param[in]       dEnable                 Availability of data
     */
    void commitDataEnable(uint8_t portNumber, uint8_t dEnable);

    /**
     * @brief Indicates ports ready for data transfer
     * 
     * @retval          true                    ready
     * @retval          false                   not ready
     */
    bool portsReady();

    /**
     * @brief Stores data for a specific port
     *
     * @param[in]       portNumber              Port number
     * @param[in]       ptrTmpData              Reference to data for port
     */
    void storeData(uint8_t portNumber, uint8_t &ptrTmpData);

    /**
     * @brief Loads data from a specific port
     *
     * @param[in]       portNumber              Port number
     *
     * @retval          uint8_t&                Reference to data from port
     */
    uint8_t & loadData(uint8_t portNumber);

private:
    std::vector<PortAPE> *portsAPE;         /* Related ports of APE */
    std::vector<uint8_t> portsEnables;      /* Ports enables */
    std::vector<uint8_t*> portsDataBuffer;  /* Data of ports */
    uint8_t numPorts = 0;                   /* Number of ports */
};

/**
 * @brief Abstract Processing Element class implementation
 */
class AbstractProcessingElement
{
public:

    /**
     * @brief Constructs a new Abstract Processing Element object
     */
    AbstractProcessingElement();

    /**
     * @brief Destroys the Abstract Processing Element object
     */
    ~AbstractProcessingElement();

    /**
     * @brief Sets Abstract Processing Element attributes
     *
     * @param[in]       id                      Unique APE identifier
     * @param[in]       cost                    The execution cost
     * @param[in]       time                    The execution time
     * @param[in]       T                       Flag dynamic operations
     * @param[in]       portsAccessTypes        Array of ports access types
     * 
     * @retval          0                       Success
     * @retval          -1                      Failute
     */
    int set(uint16_t id, uint16_t cost, uint16_t time, uint16_t T, const std::vector<uint8_t> &portsAccessTypes);

    /**
     * @brief Initializes Abstract Processing Element of a specific operation
     *
     * @param[in]       opcode                  The specific operation code
     * @param[in]       operation               The specific operation from Radio Library
     * 
     * @retval          0                       Success
     * @retval          -1                      Failute
     */
    int init(const uint32_t &opcode, int (*operation)(uint8_t argc, ...));

    /**
     * @brief Executes APE, performs the specified operation on the data.
     */
    void run();

    /**
     * @brief Associates Abstract Processing Element with related Data path configuration block
     * 
     * @param[in]       cfgnBlock               Reference to related Data path configuration block
     */
    void associate(rvm_dataPathConfigurationBlock &cfgnBlock, rvm_ThreadsafeQueue<StatusFromAbstractProcessingElement>& qAPE);

    /**
     * @brief Informs about the availability of data for a specific port of APE
     *
     * @param[in]       portNumber              Port number of APE
     * @param[in]       dEnable                 Availability of data
     */
    void dataEnable(uint8_t portNumber, uint8_t dEnable);

    /**
     * @brief Returns access type for specific port of APE
     *
     * @param[in]       portNumber              Port number of APE
     */
    uint8_t accessType(uint8_t portNumber);

    /**
     * @brief Returns ports readiness
     *
     * @retval          true                    if ports of APE ready to transfer data
     * @retval          false                   if ports of APE not ready to transfer data
     */
    bool portsReadyToTransfer();

    /**
     * @brief Reads data on specific ports of APE
     * 
     * @param[in]       portNumber              Port number of APE
     * @param[in]       ptrTmpData              Reference to input data
     */
    void read(uint8_t portNumber, uint8_t &ptrTmpData);

    /**
     * @brief Writes data from specific ports of APE
     * 
     * @param[in]       portNumber              Port number of APE
     * 
     * @retval          uint8_t&                Reference to output data
     */
    uint8_t & write(uint8_t portNumber);

    /**
     * @brief Gets unique APE identifier
     * 
     * @retval          uint16_t                Unique APE identifier
     */
    uint16_t getId();

    /**
     * @brief Converts APE to string
     *
     * @retval          std::string             APE as string
     */
    std::string to_str();

private:

    uint16_t id = 0;        /* Unique APE identifier */
    uint16_t cost = 0;      /* The execution cost of operation */
    uint16_t time = 0;      /* The execution time of operation */
    uint8_t T = 0;          /* Flag dynamic operations. 1 - dynamic, 0 -not dynamic */
    uint32_t opcode = 0;    /* Opcode of APE */
    int (*operation)(uint8_t argc, ...);                    /* Specific operation */
    rvm_dataPathConfigurationBlock *cfgnBlock = nullptr;    /* Externally related Data path configuration block */
    rvm_ThreadsafeQueue<StatusFromAbstractProcessingElement>* qAPE = nullptr;
    StatusFromAbstractProcessingElement status;             /* Current status of APE */
    APEportManager portsMngr;                               /* Manager for port of APE */
    std::vector<PortAPE> ports;                             /* Ports of APE */
    uint8_t numPorts = 0;                                   /* Number of ports */
};

#endif // RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS
