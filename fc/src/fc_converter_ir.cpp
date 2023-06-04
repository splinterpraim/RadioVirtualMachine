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
#include <cstdio>
#include <cstdint>
#include <cinttypes>

#include "common.hpp"
#include "system_func.hpp"
#include "fc_glob.hpp"
#include "fc_logger.hpp"
#include "reference_radio_library.hpp"

#define PROGRAM_ID 0
#define APE_ID_START 1


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
    ctrlSec.Creation_Date = 2023;
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
    int type = irData.getType();
    const char* name = irData.getId().c_str();
    switch (type)
    {
        case rlt_bool:
            res = sizeof(bool);
            break;
        case rlt_int8:
            res = sizeof(int8_t);
            break;
        case rlt_int16:
            res = sizeof(int16_t);
            break;
        case rlt_int32:
            res = sizeof(int32_t);
            break;
        case rlt_int64:
            res = sizeof(int64_t);
            break;
        case rlt_uint8:
            res = sizeof(uint8_t);
            break;
        case rlt_uint16:
            res = sizeof(uint16_t);
            break;
        case rlt_uint32:
            res = sizeof(uint32_t);
            break;
        case rlt_uint64:
            res = sizeof(uint64_t);
            break;
        case rlt_float:
            res = sizeof(float);
            break;
        case rlt_double:
            res = sizeof(double);
            break;
        default:
            std::string msg = FC_ERR_STR("Unsupported data type in '%s'", name);
            throw std::runtime_error(msg);
    }

    return res;
}

uint8_t fc_ConverterIR::getDoConfig_length(IrData &irData, uint32_t size)
{
    uint8_t resLen = 0;
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
        std::string dataVal = irData.getValue();
        resLen = detectSize(dataVal, dataType);
    }
    /* Filled path */
    else if (doPath.length() != 0)
    {
        resLen = getFileLen(doPath);
    }

    /* Overflow type check */
    // if (resLen > size)
    // {
    //     std::cout << FC_WARN_STR("Length in file more then size. Data was readed partly.") << std::endl;
    //     int dataType = irData.getType();
    //     std::string dataVal = irData.getValue();

    //     resLen = detectSize(dataVal, dataType);
    // }
    return resLen;
}

uint8_t fc_ConverterIR::detectSize(std::string dataVal, int dataType)
{

#define str2digit_withCheck(str,dvar,dtype,dspec,dcast)  \
{                                    \
    int n;                                  \
    int ret;                                \
    ret = std::sscanf(str, dspec "%n", (dcast*)&dvar, &n);  \
    if((ret != 1) || (std::strlen(str)!= (size_t)n))    \
    {                                                       \
        throw std::runtime_error(FC_ERR_STR("Can't convert value '%s' to type '%s'",str, #dtype));      \
    }   \
    char buffer[FC_STR_VALUE_MAX_SIZE]; \
    std::snprintf(buffer, sizeof(buffer),dspec,dvar);   \
    if (! ((std::strncmp(#dtype,"float",sizeof(#dtype)) == 0) ||  \
           (std::strncmp(#dtype,"double",sizeof(#dtype)) == 0)) )  \
    {                                                    \
        if (std::strncmp(buffer, str, sizeof(buffer))!= 0)  \
        {                                                    \
            throw std::runtime_error(FC_ERR_STR("Type '%s' overflow for value '%s'", #dtype, str));      \
                                            \
        }                                   \
    }   \
}
#define findHighBitNumber(dvar,dtype,bytes)   \
{                                               \
    uint64_t bitMask = UINT64_MAX;           \
    uint8_t type = sizeof(dtype);           \
    bytes = 0;                                   \
    for( size_t i = 0; i < sizeof(uint64_t); i++ ) \
    {                                           \
        bytes++;                              \
        bitMask = bitMask << 8; \
        if(!(dvar & bitMask))    {break;}               \
        if (bytes >= type) {break;} \
    }                           \
}

    uint8_t res = 0;
    const char* str = dataVal.c_str();
    switch (dataType)
    {
        case rlt_bool:
            res = sizeof(bool);
            break;
        case rlt_int8:
        {
            int8_t num;
            str2digit_withCheck(str, num, int8_t, "%" PRId8, int)
            findHighBitNumber(num,int8_t,res);
            break;
        }
        case rlt_int16:
        {
            int16_t num;
            str2digit_withCheck(str, num, int16_t, "%" PRId16, int)
            findHighBitNumber(num,int16_t,res);
            break;
        }
        case rlt_int32:
        {
            int32_t num;
            str2digit_withCheck(str, num, int32_t, "%" PRId32, int)
            findHighBitNumber(num,int32_t,res);
            break;
        }
        case rlt_int64:
        {
            int64_t num;
            str2digit_withCheck(str, num, int64_t, "%" PRId64, long)
            findHighBitNumber(num,int64_t,res);
            break;
        }
        case rlt_uint8:
        {
            uint8_t num;
            str2digit_withCheck(str, num, uint8_t, "%" PRIu8, unsigned int)
            findHighBitNumber(num,uint8_t,res);
            break;
        }
        case rlt_uint16:
        {
            uint16_t num;
            str2digit_withCheck(str, num, uint16_t, "%" PRIu16, unsigned int)
            findHighBitNumber(num,uint16_t,res);
            break;
        }
        case rlt_uint32:
        {
            uint32_t num;
            str2digit_withCheck(str, num, uint32_t, "%" PRIu32, unsigned int)
            findHighBitNumber(num,uint32_t,res);
            break;
        }
        case rlt_uint64:
        {
            uint64_t num;
            str2digit_withCheck(str, num, uint64_t, "%" PRIu64, unsigned long)
            findHighBitNumber(num,uint64_t,res);
            break;
        }
        case rlt_float:
        {
            float num;
            str2digit_withCheck(str, num, float, "%f" , float)
            res = sizeof(float);
            break;
        }
        case rlt_double:
        {
            double num;
            str2digit_withCheck(str, num, double, "%lf" , double)
            res = sizeof(double);
            break;
        }
        default:
        {
            std::string msg = FC_ERR_STR("Unsupported data type '%d'", dataType);
            throw std::runtime_error(msg);
        }
    }

    return res;
#undef str2digit_withCheck
#undef findHighBitNumber
}

size_t fc_ConverterIR::getFileLen(std::string fileName)
{
    size_t res = 0;
    std::ifstream dataFile;
    dataFile.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);
    if (!dataFile.is_open())
    {
        throw std::runtime_error(FC_ERR_STR("File '%s' does not open", fileName.c_str()));
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

#define str2digit_withCheck(str,dvar,dtype,dspec,dcast,destruct)  \
{                                    \
    int n;                                  \
    int ret;                                \
    ret = std::sscanf(str, dspec "%n", (dcast*)&dvar, &n);  \
    if((ret != 1) || (std::strlen(str)!= (size_t)n))    \
    {                                                       \
        destruct;                          \
        throw std::runtime_error(FC_ERR_STR("Can't convert value '%s' to type '%s'",str, #dtype));      \
    }   \
    char buffer[FC_STR_VALUE_MAX_SIZE]; \
    std::snprintf(buffer, sizeof(buffer),dspec,dvar);   \
    if (! ((std::strncmp(#dtype,"float",sizeof(#dtype)) == 0) ||  \
           (std::strncmp(#dtype,"double",sizeof(#dtype)) == 0)) )  \
    {                                                    \
        if (std::strncmp(buffer, str, sizeof(buffer))!= 0)  \
        {                                                    \
            destruct;                    \
            throw std::runtime_error(FC_ERR_STR("Type '%s' overflow for value '%s'", #dtype, str));      \
                                            \
        }                                   \
    }   \
}

    /* Filled value */
    const char* str = doVal.c_str();
    res = new uint8_t[len];
    if (doVal.length() != 0)
    {
            switch (dataType)
        {
            case rlt_bool:
            {
                if(doVal.compare("true") == 0)
                {
                    *res = 1;
                }
                else if(doVal.compare("false") == 0)
                {
                    *res = 0;
                }
                else
                {
                    delete[] res;
                    throw std::runtime_error(FC_ERR_STR("Can't convert value '%s' to type '%s'",str, "bool"));
                }
                break;
            }
            case rlt_int8:
            {
                int8_t num;
                str2digit_withCheck(str, num, int8_t, "%" PRId8, int, delete[] res)
                *res = num;
                break;
            }
            case rlt_int16:
            {
                int16_t num;
                str2digit_withCheck(str, num, int16_t, "%" PRId16, int, delete[] res)
                if (endianIsLittle())
                {
                    num = reverseEndian(num, len);
                }
                std::memcpy((void *)res, (const void *)&num, len);
                break;
            }
            case rlt_int32:
            {
                int32_t num;
                str2digit_withCheck(str, num, int32_t, "%" PRId32, int, delete[] res)
                if (endianIsLittle())
                {
                    num = reverseEndian(num, len);
                }
                std::memcpy((void *)res, (const void *)&num, len);
                break;
            }
            case rlt_int64:
            {
                int64_t num;
                str2digit_withCheck(str, num, int64_t, "%" PRId64, long, delete[] res)
                if (endianIsLittle())
                {
                    num = reverseEndian(num, len);
                }
                std::memcpy((void *)res, (const void *)&num, len);
                break;
            }
            case rlt_uint8:
            {
                uint8_t num;
                str2digit_withCheck(str, num, uint8_t, "%" PRIu8, unsigned int, delete[] res)
                if (endianIsLittle())
                {
                    num = reverseEndian(num, len);
                }
                std::memcpy((void *)res, (const void *)&num, len);
                break;
            }
            case rlt_uint16:
            {
                uint16_t num;
                str2digit_withCheck(str, num, uint16_t, "%" PRIu16, unsigned int, delete[] res)
                if (endianIsLittle())
                {
                    num = reverseEndian(num, len);
                }
                std::memcpy((void *)res, (const void *)&num, len);
                break;
            }
            case rlt_uint32:
            {
                uint32_t num;
                str2digit_withCheck(str, num, uint32_t, "%" PRIu32, unsigned int, delete[] res)
                if (endianIsLittle())
                {
                    num = reverseEndian(num, len);
                }
                std::memcpy((void *)res, (const void *)&num, len);
                break;
            }
            case rlt_uint64:
            {
                uint64_t num;
                str2digit_withCheck(str, num, uint64_t, "%" PRIu64, unsigned long, delete[] res)
                if (endianIsLittle())
                {
                    num = reverseEndian(num, len);
                }
                std::memcpy((void *)res, (const void *)&num, len);
                break;
            }
            case rlt_float:
            {
                float num;
                str2digit_withCheck(str, num, float, "%f" , float, delete[] res)
                if (endianIsLittle())
                {
                    num = reverseEndianFloat(num, len);
                }
                std::memcpy((void *)res, (const void *)&num, len);
                break;
            }
            case rlt_double:
            {
                double num;
                str2digit_withCheck(str, num, double, "%lf" , double, delete[] res)
                if (endianIsLittle())
                {
                    num = reverseEndianDouble(num, len);
                    num = reverseEndianDouble(num, len);
                }
                std::memcpy((void *)res, (const void *)&num, len);
                break;
            }
            default:
            {
                delete[] res;
                std::string msg = FC_ERR_STR("Unsupported data type '%d'", dataType);
                throw std::runtime_error(msg);
            }
        }
    }
    /* Filled path (!no type specified) */
    else if (doPath.length() != 0)
    {
        res = getFileData(doPath);
    }

    return res;
#undef str2digit_withCheck
}

uint8_t* fc_ConverterIR::getFileData(std::string fileName)
{
    uint8_t *res = nullptr;
    size_t fSize = 0;

    std::ifstream dataFile;
    dataFile.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);
    if (!dataFile.is_open())
    {
        throw std::runtime_error(FC_ERR_STR("File '%s' does not open", fileName));
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

uint8_t fc_ConverterIR::getNumInputLink(std::string opId, std::vector<IrLink> &links)
{
    uint8_t res = 0;

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
        if (!checkNumPortsInRadioLib(op, irObjects))
        {
            throw std::runtime_error(FC_ERR_STR("Mismatch number of in/out ports in IR operator %s and radiolib!", op.getId().c_str()));
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

bool fc_ConverterIR::checkNumPortsInRadioLib(IrOperator &irOperator, IrObjects &irObjects)
{
    uint8_t numInputLink = getNumInputLink(irOperator.getId(), irObjects.links);
    uint8_t numOutputLink = getNumOutputLink(irOperator.getId(), irObjects.links);
    uint32_t opcode = std::stoul(irOperator.getOpcode());
    const radioLibrary_el * op = rl_getOperator(opcode);
    uint8_t inputCnt = rl_getInputPortCnt(opcode);
    uint8_t outputCnt = rl_getOutputPortCnt(opcode);
    uint8_t iDiff = inputCnt - numInputLink;
    uint8_t oDiff = outputCnt - numOutputLink;

    if ((op->flags.infinityInPorts == RL_ENABLE) && (op->flags.infinityOutPorts == RL_ENABLE))
    {
        return true;
    }
    else if (op->flags.infinityInPorts == RL_ENABLE)
    {
        return !oDiff;
    }
    else if (op->flags.infinityOutPorts == RL_ENABLE)
    {
        return !iDiff;
    }

    return !(iDiff || oDiff);
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

uint8_t fc_ConverterIR::getNumOutputLink(std::string opId, std::vector<IrLink> &links)
{
    uint8_t res = 0;

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
        std::string row;
        if (!el.getType().compare("Complex"))
        {
            row = std::to_string(getApeIdForCfgCode(el.getId(),operators)) + "," + el.getSubname();
        }
        else
        {
            row = std::to_string(getApeIdForCfgCode(el.getId(),operators)) + "," + el.getId();
        }
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
