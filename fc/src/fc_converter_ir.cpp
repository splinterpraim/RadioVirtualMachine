/**
 * @file fc_converter_ir.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Implementation of the FC converter IR.
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "fc_converter_ir.hpp"

#include <fstream>
#include <cstring>

#include "common.hpp"
#include "system_func.hpp"
#include "fc_glob.hpp"
#include "radio_library.hpp"

#define PROGRAM_ID 0
#define APE_ID_START 1

extern RadioLibrary radioLib;

/* Private */
void fc_ConverterIR::fillControlSection(ConfigObjects &configObjects, IrObjects &irObjects)
{
    ControlSection &ctrlSec = configObjects.controlSection;
    ctrlSec.LCF = 1; // means that this is the last Configcode in the task
    ctrlSec.NAF = 0;
    ctrlSec.Task_ID = 1;
    ctrlSec.RPI_version = 1;  // version number of supported general radio programming interface
    ctrlSec.Reference_ID = 1; // identifier of the reference Radio Library
    ctrlSec.Implementation_version = 1;
    ctrlSec.Developer_ID = 1;
    ctrlSec.Creation_Date = 2022;
}

void fc_ConverterIR::fillDoSection(ConfigObjects &configObjects, IrObjects &irObjects)
{
    DO_Section &doSec = configObjects.doSection;

    doSec.N_DO = irObjects.data.size();
    doSec.DOs = getDoConfig(irObjects);
    doSec.ASFs = getAsfConfig(irObjects);
}

DO_Config* fc_ConverterIR::getDoConfig(IrObjects &irObjects)
{
    DO_Config *doConfigRes = new DO_Config[irObjects.data.size()];
    int i = 0;
    for (auto &elem : irObjects.data)
    {
        doConfigRes[i].DO_ID = i;
        doConfigRes[i].size = getDoConfig_size(elem);
        doConfigRes[i].access_time = std::stoul(elem.getAccessTime(), nullptr, 0);
        doConfigRes[i].external = elem.getExternal();
        doConfigRes[i].length = getDoConfig_length(elem, doConfigRes[i].size);
        doConfigRes[i].data = getDoConfig_data(elem, doConfigRes[i].length);

        i++;
    }
    return doConfigRes;
}

uint32_t fc_ConverterIR::getDoConfig_size(IrData &irData)
{
    uint32_t res = 0;
    if (irData.getType() == RL_TYPE_INT)
    {
        res = sizeof(int);
    }
    else if (irData.getType() == RL_TYPE_FLOAT)
    {
        res = sizeof(float);
    }
    else if (irData.getType() == RL_TYPE_STRING)
    {
        res = irData.getValue().size();
    }
    else
    {
        std::cout << FC_ERR_STR("Error: Mismatch of type!") << std::endl;
    }
    return res;
}

uint8_t fc_ConverterIR::getDoConfig_length(IrData &irData, uint32_t size)
{
    uint8_t res = 0;
    std::string doVal = irData.getValue();
    std::string doPath = irData.getPath();

    /* Filled both value and path */
    if ((doVal.length() != 0) && (doPath.length() != 0))
    {
        throw std::runtime_error(FC_ERR_STR("Filled both value and path!"));
    }

    /* Filled value */
    if (doVal.length() != 0)
    {
        int dataType = irData.getType();
        size_t dataValSize = irData.getValue().size();

        //TODO: normal length count 
        res = detectSize(dataType, dataValSize);
    }
    /* Filled path */
    else if (doPath.length() != 0)
    {
        res = getFileLen(doPath);
    }

    /* Overflow type check */
    if (res > size)
    {
        std::cout << FC_WARN_STR("Length in file more then size. Data was readed partly.") << std::endl;
        int dataType = irData.getType();
        size_t dataValSize = irData.getValue().size();

        res = detectSize(dataType, dataValSize);
    }
    return res;
}

uint32_t fc_ConverterIR::detectSize(int dataType, size_t dataValSize)
{
    uint32_t res;

    if (dataType == RL_TYPE_INT)
    {
        res = sizeof(int);
    }
    else if (dataType == RL_TYPE_FLOAT)
    {
        res = sizeof(float);
    }
    else if (dataType == RL_TYPE_STRING)
    {
        res = dataValSize;
    }
    else
    {
        throw std::runtime_error(FC_ERR_STR("Mismatch of type!"));
    }
    return res;
}

size_t fc_ConverterIR::getFileLen(std::string fileName)
{
    size_t res = 0;
    std::ifstream dataFile;
    dataFile.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);
    if (!dataFile.is_open())
    {
        throw std::runtime_error(FC_ERR_STR("File " + fileName + " does not open"));
    }
    res = dataFile.tellg();

    return res;
}

uint8_t* fc_ConverterIR::getDoConfig_data(IrData &irData, uint8_t len)
{
    uint8_t *res = nullptr;
    std::string doVal = irData.getValue();
    std::string doPath = irData.getPath();
    int dataType = irData.getType();

    /* Filled both value and path */
    if ((doVal.length() != 0) && (doPath.length() != 0))
    {
        throw std::runtime_error(FC_ERR_STR("Filled both value and path!"));
    }

    //! segf
    /* Filled value */
    if (doVal.length() != 0)
    {
        if (dataType == RL_TYPE_INT)
        {
            size_t procSymbCnt = 0;
            for (auto sym : doVal)
            {
                if (sym == ' ')
                {
                    throw std::runtime_error(FC_ERR_STR("Incorrect value!"));
                }
            }
            int intVal = std::stoi(doVal, &procSymbCnt);
            if (procSymbCnt != doVal.size())
            {
                throw std::runtime_error(FC_ERR_STR("Incorrect value!"));
            }
            if (endianIsLittle() == CMN_LITTLE_ENDIAN)
            {
                intVal = reverseEndian(intVal);
            }

            res = new uint8_t[len];
            std::memcpy((void *)res, (const void *)&intVal, len);
        }
        else if (dataType == RL_TYPE_FLOAT)
        {
            size_t procSymbCnt = 0;
            for (auto sym : doVal)
            {
                if (sym == ' ')
                {
                    throw std::runtime_error(FC_ERR_STR("Incorrect value!"));
                }
            }

            float fltVal = std::stof(doVal, &procSymbCnt);
            if (procSymbCnt != doVal.size())
            {
                throw std::runtime_error(FC_ERR_STR("Incorrect value!"));
            }
            if (endianIsLittle() == CMN_LITTLE_ENDIAN)
            {
                fltVal = reverseEndian(fltVal);
            }

            res = new uint8_t[len];
            std::memcpy((void *)res, (const void *)&fltVal, len);
        }
        else if (dataType == RL_TYPE_STRING)
        {
            // todo: get data for string
            // res = irData.getValue().size();
        }
        else
        {
            throw std::runtime_error(FC_ERR_STR("Mismatch of type!"));
        }
    }
    /* Filled path */
    else if (doPath.length() != 0)
    {
        res = getFileData(doPath);
    }

    return res;
}

uint8_t* fc_ConverterIR::getFileData(std::string fileName)
{
    uint8_t *res = nullptr;
    size_t fSize = 0;

    std::ifstream dataFile;
    dataFile.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);
    if (!dataFile.is_open())
    {
        throw std::runtime_error(FC_ERR_STR("File " + fileName + " does not open"));
    }

    fSize = dataFile.tellg();
    if (fSize != 0)
    {
        res = new uint8_t[fSize];
        dataFile.seekg(0, std::ios::beg);
        dataFile.read((char *)res, fSize);
        dataFile.close();
    }

    return res;
}

ASF_Config* fc_ConverterIR::getAsfConfig(IrObjects &irObjects)
{
    ASF_Config *asfConfigRes = new ASF_Config[irObjects.data.size()];
    int i = 0;
    for (auto &elem : irObjects.data)
    {
        asfConfigRes[i].DO = i;
        asfConfigRes[i].N = getAsfConfig_numApe(elem, irObjects); //! cannot be more than 63
        asfConfigRes[i].APE_KP = getAsfConfig_APE_KP(elem, asfConfigRes[i].N, irObjects);

        i++;
    }
    return asfConfigRes;
}

uint8_t fc_ConverterIR::getAsfConfig_numApe(IrData &irData, IrObjects &irObjects)
{
    uint8_t res = 0;
    std::string dataId = irData.getId();

    for (auto &elem : irObjects.links)
    {
        if (dataId.compare(elem.getDataId()) == 0)
            res++;
    }

    return res;
}

ASF_variable_part* fc_ConverterIR::getAsfConfig_APE_KP(IrData &irData, uint8_t N, IrObjects &irObjects)
{
    ASF_variable_part *res = nullptr;
    std::string dataId = irData.getId();

    res = new ASF_variable_part[N];
    int i = 0;

    /* Iterations on links */
    for (auto &link : irObjects.links)
    {
        /* Finds a link with a dataId field equal to IR dataId */
        if (dataId.compare(link.getDataId()) == 0)
        {
            res[i].APE_number = getApeIdForCfgCode(link.getOperatorId(), irObjects.operators);

            /* input */
            if (link.getDir() == 0)
            {
                res[i].port_number = link.getDataOrder();
            }
            /* output */
            else
            {
                res[i].port_number = link.getDataOrder() + getNumInputLink(link.getOperatorId(), irObjects.links);
            }
            i++;
        }
    }

    return res;
}

uint8_t fc_ConverterIR::getApeIdForCfgCode(std::string apeId, std::vector<IrOperator> &operators)
{
    /* "" in apeId means Program ID */
    if (apeId == "")
    {
        return PROGRAM_ID;
    }
    uint8_t apeOrderNum = APE_ID_START;

    /* Iterations on operators */
    for (auto &op : operators)
    {
        /* Finds a operator */
        if (apeId.compare(op.getId()) == 0)
        {
            break;
        }
        apeOrderNum++;

    }
    return apeOrderNum;
}

int fc_ConverterIR::getNumInputLink(std::string opId, std::vector<IrLink> &links)
{
    int res = 0;

    for (auto &elem : links)
    {
        if ((opId.compare(elem.getOperatorId()) == 0) && (elem.getDir() == 0))
            res++;
    }
    return res;
}

void fc_ConverterIR::fillApeSection(ConfigObjects &configObjects, IrObjects &irObjects)
{
    APE_Section &apeSec = configObjects.apeSection;
    apeSec.N_APE = irObjects.operators.size();
    apeSec.APEs = getApeConfig(irObjects);
}

APE_Config* fc_ConverterIR::getApeConfig(IrObjects &irObjects)
{
    APE_Config *apeConfigRes = new APE_Config[irObjects.operators.size()];
    int i = 0;
    for (auto &op : irObjects.operators)
    {
        if (!checkNumPorts(op, irObjects))
        {
            throw std::runtime_error(FC_ERR_STR("Mismatch number of in/out ports in XML and radiolib!"));
        }
        apeConfigRes[i].APE_ID = getApeIdForCfgCode(op.getId(), irObjects.operators);
        apeConfigRes[i].op_code = std::stoul(op.getOpcode());
        apeConfigRes[i].T = APE_T_STATIC;
        apeConfigRes[i].NN = getApeNumPorts(op.getId(), irObjects);
        apeConfigRes[i].cost = 10;
        apeConfigRes[i].time = 10;
        apeConfigRes[i].access_type = getAccessType(apeConfigRes[i].NN, op.getId(), irObjects);
        i++;
    }
    return apeConfigRes;
}

bool fc_ConverterIR::checkNumPorts(IrOperator &irOperator, IrObjects &irObjects)
{
    int numInputLink = getNumInputLink(irOperator.getId(), irObjects.links);
    int numOutputLink = getNumOutputLink(irOperator.getId(), irObjects.links);

    IOPortsCnt numIOPortsLib = radioLib.getIOPortsCnt(std::stoul(irOperator.getOpcode()));

    if ((numIOPortsLib.input == RL_PORTS_INF) && (numOutputLink == numIOPortsLib.output))
    {
        return true;
    }
    else if ((numInputLink == numIOPortsLib.input) && (numOutputLink == numIOPortsLib.output))
    {
        return true;
    }

    return false;
}

uint8_t fc_ConverterIR::getApeNumPorts(std::string opId, IrObjects &irObjects)
{
    // todo: check max size (3 bits available)
    // todo: get result from refference radiolibrary (example: operator "multiple" => number of ports = 3 )
    uint8_t apeNumPorts = 0;

    /* Iterations on links */
    for (auto &link : irObjects.links)
    {
        /* Finds a link with a operatorId field equal to IR operatorId */
        if (opId.compare(link.getOperatorId()) == 0)
        {
            apeNumPorts++;
        }
    }
    return apeNumPorts;
}

int fc_ConverterIR::getNumOutputLink(std::string opId, std::vector<IrLink> &links)
{
    int res = 0;

    for (auto &elem : links)
    {
        if ((opId.compare(elem.getOperatorId()) == 0) && (elem.getDir() == 1))
            res++;
    }
    return res;
}

uint8_t* fc_ConverterIR::getAccessType(uint8_t apeNumPorts, std::string opId, IrObjects &irObjects)
{
    uint8_t *accessType = new uint8_t[apeNumPorts];

    int numInputLink = getNumInputLink(opId, irObjects.links);
    int numOutputLink = getNumOutputLink(opId, irObjects.links);

    for (int i = 0; i < numInputLink; i++)
    {
        accessType[i] = APE_ACCESS_TYPE_R;
    }

    for (int i = 0; i < numOutputLink; i++)
    {
        accessType[i + numInputLink] = APE_ACCESS_TYPE_W;
    }

    return accessType;
}

void fc_ConverterIR::generateIdMapFile(std::vector<IrOperator> &operators)
{
    ofstream fin;
    fin.open(idMapFile,std::ios::out);
    for(auto & el : operators)
    {
        std::string row = std::to_string(getApeIdForCfgCode(el.getId(),operators)) + "," + el.getId();
        fin << row << std::endl;
    }
    fin.close();
}


/* Public */
ConfigObjects fc_ConverterIR::convert(IrObjects &irObjects)
{
    ConfigObjects configObjects;
    fillControlSection(configObjects, irObjects);
    fillDoSection(configObjects, irObjects);
    fillApeSection(configObjects, irObjects);
    generateIdMapFile(irObjects.operators);
    return configObjects;
}

void fc_ConverterIR::setIdMapFile(const std::string &fileName)
{
    idMapFile = fileName;
}

std::string fc_ConverterIR::getIdMapFile() const
{
    return idMapFile;
}
