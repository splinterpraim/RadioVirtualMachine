#include "APE/abstract_processing_element.h"

#include <algorithm>
/* Exception Headers */
#include <exception>
#include <stdexcept>

#include "common.hpp"
#include "radiolib/functions.h"

#define APE_PORT_BLOCKED 1
#define APE_PORT_ALLOWED 0
APEportManager::APEportManager()
{
}
void APEportManager::init(uint8_t numPorts)
{
    this->numPorts = numPorts;
    portsEnables.resize(numPorts);
    portsDataBuffer.resize(numPorts);
    std::fill(portsEnables.begin(), portsEnables.end(), APE_PORT_BLOCKED);
    std::fill(portsDataBuffer.begin(), portsDataBuffer.end(), nullptr);
}

void APEportManager::associate(std::vector<PortAPE> &portsAPE)
{
    this->portsAPE = &portsAPE;
}

void APEportManager::commitDataEnable(uint8_t portNumber, uint8_t dEnable)
{
    if (portNumber >= numPorts)
    {
        throw std::invalid_argument(RVM_ERR_STR("invalid port number, out of range port number"));
    }

    auto &curPort = (*portsAPE)[portNumber];

    /* Set port enable */
    if ((dEnable == stDO::empty) && (curPort.accessTypes == APE_ACCESS_TYPE_W))
    {
        portsEnables[portNumber] = APE_PORT_ALLOWED;
    }
    else if ((dEnable == stDO::full) && (curPort.accessTypes == APE_ACCESS_TYPE_R))
    {
        portsEnables[portNumber] = APE_PORT_ALLOWED;
    }
    else
    {
        portsEnables[portNumber] = APE_PORT_BLOCKED;
    }
}

bool APEportManager::portsReady()
{
    for (auto &port_ready : portsEnables)
    {
        if (port_ready == APE_PORT_BLOCKED)
        {
            return false;
        }
    }
    return true;
}

void APEportManager::storeData(uint8_t portNumber, uint8_t &ptrTmpData)
{
    if (portNumber >= numPorts)
    {
        throw std::invalid_argument(RVM_ERR_STR("invalid port number, out of range port number"));
    }

    if (portsDataBuffer[portNumber])
        delete[] portsDataBuffer[portNumber];

    portsDataBuffer[portNumber] = &ptrTmpData;
}

uint8_t &APEportManager::loadData(uint8_t portNumber)
{
    if (portNumber >= numPorts)
    {
        throw std::invalid_argument(RVM_ERR_STR("invalid port number, out of range port number"));
    }

    if (!portsDataBuffer[portNumber])
        throw std::runtime_error(RVM_ERR_STR("nullptr on port data"));

    return *portsDataBuffer[portNumber];
}

AbstractProcessingElement::AbstractProcessingElement()
{
    portsMngr.associate(ports);
}
AbstractProcessingElement::~AbstractProcessingElement()
{
    // delete[] ports;
}

int AbstractProcessingElement::set(uint16_t id, uint16_t cost, uint16_t time, uint16_t T, const std::vector<uint8_t> &portsAccessTypes)
{
    /* Throw exceptions */
    {
        /* Invalid argument T */
        if (T > 1)
        {
            throw std::invalid_argument("Setting AbstractProcessingElement failed, argument T > 1!");
        }

        /* Invalid argument portsAccessTypes */
        if (portsAccessTypes.size() == 0)
        {
            throw std::runtime_error("Setting AbstractProcessingElement failed, portsAccessTypes.size() == 0!");
        }

        /* Double function call */
        if (ports.size() != 0)
        {
            throw std::runtime_error("Setting AbstractProcessingElement failed, Double set function call!");
        }
    }

    /* Exception Handle */
    {

        /* Allocate mem */
        try
        {
            this->id = id;
            this->cost = cost;
            this->time = time;
            this->T = T;
            this->numPorts = portsAccessTypes.size();
            ports.resize(this->numPorts);
            int i = 0;
            for (auto el : portsAccessTypes)
            {
                ports[i].num = 0;
                ports[i].accessTypes = el;
                i++;
            }
            portsMngr.init(this->numPorts);
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Bad_alloc: Setting DataObject failed, Memory allocation error " << std::endl;
            return -1;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception: Setting DataObject failed, error during function execution!" << std::endl;
            return -1;
        }
    }

    return 0;
}

int AbstractProcessingElement::init(const uint32_t &opcode, int (*operation)(uint8_t argc, ...))
{
    /* Throw exceptions */
    {
        /* Invalid argument operation */
        if (operation == nullptr)
        {
            throw std::invalid_argument("Setting AbstractProcessingElement failed, operation ==  nullptr!");
        }
    }
    this->opcode = opcode;
    this->operation = operation;
    return 0;
}

void AbstractProcessingElement::run()
{
    rl_ArgArray argArray;
    argArray.inNum = 0;
    argArray.outNum = 0;

    // todo: replace in sets or gets in radio library
    /* Count in out ports */
    for (int i = 0; i < numPorts; i++)
    {
        if (ports[i].accessTypes == APE_ACCESS_TYPE_R)
        {
            argArray.inNum++;
        }
        else if (ports[i].accessTypes == APE_ACCESS_TYPE_W)
        {
            argArray.outNum++;
        }
    }
    argArray.inPorts = new uint8_t *[argArray.inNum];
    argArray.outPorts = new uint8_t *[argArray.outNum];

    /* Prepare input data */
    for (int i = 0; i < numPorts; i++)
    {
        if (ports[i].accessTypes == APE_ACCESS_TYPE_R)
        {
            argArray.inPorts[i] = &(portsMngr.loadData(i));
        }
    }

    /* run operation */
    operation(numPorts, &argArray);

    /* Processing result output data */
    /* Clear after run */
    int outCnt = 0;
    for (int i = 0; i < numPorts; i++)
    {
        if (ports[i].accessTypes == APE_ACCESS_TYPE_W)
        {
            portsMngr.storeData(i, *argArray.outPorts[outCnt]);
            outCnt++;
        }
    }
}

void AbstractProcessingElement::setSendControlUnit(ControlUnit &cu)
{
    this->cu = &cu;
}

void AbstractProcessingElement::associate(rvm_dataPathConfigurationBlock &cfgnBlock)
{
    this->cfgnBlock = &cfgnBlock;
}

void AbstractProcessingElement::dataEnable(uint8_t portNumber, uint8_t dEnable)
{
    if (portNumber >= numPorts)
        throw std::runtime_error(RVM_ERR_STR("Out of range ports of operator"));

    portsMngr.commitDataEnable(portNumber, dEnable);
}

bool AbstractProcessingElement::accessType(uint8_t portNumber, uint8_t &acType)
{
    if (portNumber >= numPorts)
        throw std::invalid_argument(RVM_ERR_STR("Out of range ports of operator"));

    bool ret = portsMngr.portsReady();
    if (ret)
    {
        acType = ports[portNumber].accessTypes;
    }
    return ret;
}

void AbstractProcessingElement::read(uint8_t portNumber, uint8_t &ptrTmpData)
{
    if (portNumber >= numPorts)
        throw std::invalid_argument(RVM_ERR_STR("Out of range ports of operator"));
    portsMngr.storeData(portNumber, ptrTmpData);
}

uint8_t &AbstractProcessingElement::write(uint8_t portNumber)
{
    if (portNumber >= numPorts)
        throw std::invalid_argument(RVM_ERR_STR("Out of range ports of operator"));
    return portsMngr.loadData(portNumber);
}

uint16_t AbstractProcessingElement::getId()
{
    return id;
}

int AbstractProcessingElement::checkCallBack()
{
    std::cout << "d" << std::endl;
    // status.id = id;
    // status.state = inactive;
    // status.exception = 0;
    // cu->sendStatusFromAbstractProcessingElement(status);
    int result = 0;
    operation(3, 1, 2, result);
    return 0;
}

void AbstractProcessingElement::doOperation()
{
    int rez = 0;
    operation(3, 2, 2, 1, &rez);
    LogManager().makeLog(std::to_string(rez));
}
std::string AbstractProcessingElement::to_str()
{
    std::string result_str = "id " + std::to_string(id) + ", cost " + std::to_string(cost) +
                             ", time " + std::to_string(time) + ", opcode " + std::to_string(opcode) + "\n";
    for (size_t i = 0; i < numPorts; i++)
    {
        result_str += "  " + std::to_string(i) + " port: " + std::to_string(ports[i].accessTypes) + "\n";
    }

    return result_str;
}