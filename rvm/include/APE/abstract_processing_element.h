#ifndef RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS
#define RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "class_definition.h"
#include "rvm_structs.h"
#include "CU/control_unit.h"
#include "CU/rvm_data_path_configuration_block.hpp"

// struct PortsAccessTypes{
//     int size;
//     std::vector<int> accessTypes;
// };
struct PortAPE_s //? map using?
{
    uint8_t num = 0;
    uint8_t accessTypes = 0; /*  Port type  */
};
typedef struct PortAPE_s PortAPE;

class APEportManager
{
public:
    APEportManager();
    void init(uint8_t numPorts);
    void associate(std::vector<PortAPE> &portsAPE);

    void commitDataEnable(uint8_t portNumber, uint8_t dEnable);

    /**
     * @brief Indicates ports ready for data transfer
     * 
     * @retval true - ready
     * @retval false - not ready
     */
    bool portsReady();

    void storeData(uint8_t portNumber, uint8_t &ptrTmpData);
    uint8_t & loadData(uint8_t portNumber);


private:
    std::vector<PortAPE> *portsAPE;
    std::vector<uint8_t> portsEnables;
    std::vector<uint8_t*> portsDataBuffer;
    uint8_t numPorts = 0;

};

class AbstractProcessingElement
{
public:
    /* Constructor */
    AbstractProcessingElement();

    /* Destructor */
    ~AbstractProcessingElement();

    /**
     * @brief Sets Abstract Processing Element attributes
     *
     * @param id[in] Identifier to Abstract Processing Element
     * @param cost[in] The execution cost
     * @param time[in] The execution time
     * @param T[in] Flag dynamic operations
     * @param portsAccessTypes[in] Map of
     * @return int: 0 - if the function worked without errors, -1 - if the function worked with errors
     */
    int set(uint16_t id, uint16_t cost, uint16_t time, uint16_t T, const std::vector<uint8_t> &portsAccessTypes);

    /* Initializes APE of a specific operation */
    /**
     * @brief Initializes bstract Processing Element of a specific operation
     *
     * @param opcode[in] The specific operation code
     * @param operation[in] The specific operation from Radio Library
     * @return int: 0 - if the function worked without errors, -1 - if the function worked with errors
     */
    int init(const uint32_t &opcode, int (*operation)(uint8_t argc, ...));

    /**
     * @brief Starts an operation on the data
     * 
     */
    void run();

    /* Sets a pointer to the associated Control Unit */
    void setSendControlUnit(ControlUnit &cu);

    void associate(rvm_dataPathConfigurationBlock &cfgnBlock);

    void dataEnable(uint8_t portNumber, uint8_t dEnable);

    /**
     * @brief Returns access type for specific ports of APE and ports readiness
     * 
     * @param[in] portNumber Port number
     * @param[out] acType  Access type
     * @retval true - if ports of APE ready to transfer data
     * @retval false - if not ready
     */
    bool accessType(uint8_t portNumber, uint8_t &acType);

    void read(uint8_t portNumber, uint8_t &ptrTmpData);
    uint8_t & write(uint8_t portNumber);

    uint16_t getId();
    /* other */
    int checkCallBack();
    void doOperation();
    std::string to_str();

private:
    uint16_t id = 0;
    uint16_t cost = 0;
    uint16_t time = 0;
    uint8_t T = 0;

    uint32_t opcode = 0;
    int (*operation)(uint8_t argc, ...);

    ControlUnit *cu = nullptr;
    rvm_dataPathConfigurationBlock *cfgnBlock = nullptr;

    StatusFromAbstractProcessingElement status;

    APEportManager portsMngr; /* Port manager */
    std::vector<PortAPE> ports; //todo: vector 
    uint8_t numPorts = 0;

    /* for dynamic operations */
};

#endif // RVM_ABSTRACT_PROCESSING_ELEMENT_CLASS
