#include "fc_help_func.hpp"
#include "common.hpp"
#include "fc_glob.hpp"
#include "fc_system.hpp"

#include "radio_library.hpp"

#include <fstream>
#include <cstring>
#include <exception>
#include <stdexcept>

#define XML_TYPE_INT "int"
#define XML_TYPE_FLOAT "float"
#define XML_TYPE_STRING "string"

#define DO_CFG_LEN_FOR_FILE 255

extern fc_glob_t fc_glob;
extern RadioLibrary radioLib;

/* ######## Help functions*/
IrOperator convertToIrOperator(pugi::xml_node &op_xml)
{
    IrOperator op;
    op.setId(op_xml.attribute("id").value());
    op.setType(op_xml.attribute("type").value());
    op.setOpcode(op_xml.attribute("opcode").value());
    return op;
}

IrData convertToIrData(pugi::xml_node &data_xml)
{
    IrData data;
    data.setId(data_xml.attribute("id").as_string());
    // data.setType(data_xml.attribute("type").as_string());
    data.setPath(data_xml.attribute("path").as_string());
    data.setAccessTime(data_xml.attribute("access_time").as_string());
    data.setValue(data_xml.attribute("value").as_string());

    return data;
}

void showIrOperators(const std::vector<IrOperator> &operators)
{
    for (auto el : operators)
    {
        std::cout << "id = " << el.getId() << ", "
                  << "type = " << el.getType() << ", "
                  << "opcode = " << el.getOpcode() << std::endl;
    }
}

void showIrData(const std::vector<IrData> &data)
{
    for (auto el : data)
    {
        std::cout << "id = " << el.getId() << ", ";
        // std::cout << "type = " << el.getType() << ", ";
        std::cout << "path = " << el.getPath() << ", ";
        std::cout << "access_time = " << el.getAccessTime() << ", ";
        std::cout << "value = " << el.getValue() << std::endl;
    }
}

void showIrLinks(const std::vector<IrLink> &links)
{
    for (auto el : links)
    {
        std::cout << el.to_str() << std::endl;
    }
}

std::map<int, IrData> takeIrData(pugi::xml_node &op_xml, const std::string &connectType)
{
    //    std::vector<IrData> dataResult;
    std::map<int, IrData> dataResult;

    /* Gets description of operator in Radio lib */
    rl_Operator op_rl = radioLib.findByOpCode(op_xml.attribute("opcode").as_int());
    if (op_rl.name.length() == 0)
        throw std::runtime_error(FC_ERR_STR("Unknown opcode for operator"));

    /* Loop for finding and converting Data from xml to IR */
    for (auto data : op_xml)
    {
        std::string dataConnectType = data.attribute("connect_type").as_string();
        if (dataConnectType.compare(connectType) == 0)
        {
            IrData currData = convertToIrData(data);

            /* Finds data type */
            int order = data.attribute("order").as_int();
            int dataType = -1;
            if (dataConnectType.compare("input") == 0)
            {
                dataType = op_rl.ports.in[order - 1].type;
            }
            else if (dataConnectType.compare("output") == 0)
            {
                dataType = op_rl.ports.out[order - 1].type;
            }
            else
            {
                // err
            }
            currData.setType(dataType);
            dataResult[order] = currData;
        }
    }
    return dataResult;
}

std::vector<IrData> takeOutputIrData(pugi::xml_node &op_xml)
{
    std::vector<IrData> dataResult;
    for (auto data : op_xml)
    {
        std::string connect_type = data.attribute("connect_type").value();
        if (connect_type == "output")
        {
            IrData currData = convertToIrData(data);
            dataResult.push_back(currData);
        }
    }
    return dataResult;
}

void addIrDataToVector(std::vector<IrData> &data, std::map<int, IrData> &newData)
{
    for (auto el : newData)
    {
        /* If not exist */
        if (std::find(data.begin(), data.end(), el.second) == data.end())
        {
            data.push_back(el.second);
        }
    }
}

void createLinksFromVectorData(std::vector<IrLink> &links, std::map<int, IrData> &data, IrOperator &op, int dir)
{
    for (auto el : data)
    {
        links.push_back(IrLink(el.second.getId(), op.getId(), dir, el.first));
    }
}

/* ######## Help functions*/
/* ************************** convert2rvmIr */
void showControlSection(ControlSection &ctrlSec)
{
    std::string space = "  ";
    std::cout << space << "LCF: " << (int)ctrlSec.LCF << ", NAF: " << (int)ctrlSec.NAF << ", Task_ID: " << (int)ctrlSec.Task_ID << ", RPI_version: " << (int)ctrlSec.RPI_version << ", Reference_ID: " << (int)ctrlSec.Reference_ID << ", Impl_version: " << (int)ctrlSec.Implementation_version << ", Developer_ID: " << (unsigned int)ctrlSec.Developer_ID << ", Creation_Date: " << (unsigned int)ctrlSec.Creation_Date << std::endl;
}

void showDoSection(DO_Section &doSec)
{
    std::string space = "  ";
    std::cout << space << "N_DO: " << (int)doSec.N_DO << std::endl;
    std::cout << space << "DO_Config: " << std::endl;
    showDO_Config(*doSec.DOs, doSec.N_DO);
    std::cout << space << "ASF_Config: " << std::endl;
    showASF_config(*doSec.ASFs, doSec.N_DO);
}

void showDO_Config(DO_Config &doCfg, uint8_t N_DO)
{
    std::string space4 = "    ";
    DO_Config *ptrDoCfg = &doCfg;
    for (uint8_t i = 0; i < N_DO; i++)
    {
        std::cout << space4 << "DO_ID: " << (int)ptrDoCfg[i].DO_ID << ", size: " << (int)ptrDoCfg[i].size << ", access_time: " << (int)ptrDoCfg[i].access_time << ", length: " << (int)ptrDoCfg[i].length << ", data: ";
        for (size_t j = 0; j < ptrDoCfg[i].length; ++j)
            std::cout << std::hex << (int)ptrDoCfg[i].data[j] << " ";
        std::cout << std::dec;
        std::cout << std::endl;
    }
}

void showASF_config(ASF_Config &asfCfg, uint8_t N_DO)
{
    std::string space4 = "    ";
    ASF_Config *ptrAsfCfg = &asfCfg;
    for (uint8_t i = 0; i < N_DO; i++)
    {
        std::cout << space4 << "DO_ID: " << (int)ptrAsfCfg[i].DO << ", Number of APEs connected with DO: " << (int)ptrAsfCfg[i].N << ", APE_KP (APE:PORT) = [ ";
        for (int j = 0; j < ptrAsfCfg[i].N; ++j)
        {
            std::cout << (int)ptrAsfCfg[i].APE_KP[j].APE_number << ":" << (int)ptrAsfCfg[i].APE_KP[j].port_number;
            if ((j + 1) != ptrAsfCfg[i].N)
            {
                std::cout << ", ";
            }
        }
        std::cout << " ]" << std::endl;
    }
}

void showApeSection(APE_Section &apeSec)
{
    std::string space = "  ";
    std::cout << space << "N_APE: " << (int)apeSec.N_APE << std::endl;
    std::cout << space << "APE_Config: " << std::endl;
    showAPE_Config(*apeSec.APEs, apeSec.N_APE);
}

void showAPE_Config(APE_Config &apeCfg, uint16_t N_APE)
{
    std::string space4 = "    ";
    APE_Config *ptrApeCfg = &apeCfg;
    for (uint16_t i = 0; i < N_APE; i++)
    {
        std::cout << space4 << "APE_ID: " << (int)ptrApeCfg[i].APE_ID << ", op code: " << (int)ptrApeCfg[i].op_code << ", T: " << (int)ptrApeCfg[i].T << ", NN: " << (int)ptrApeCfg[i].NN << ", cost: " << (int)ptrApeCfg[i].cost << ", time: " << (int)ptrApeCfg[i].time << ", access type: ";
        for (size_t j = 0; j < ptrApeCfg[i].NN; ++j)
            std::cout << (int)ptrApeCfg[i].access_type[j] << " ";
        std::cout << std::endl;
    }
}

DO_Config *getDoConfig(IrObjects &irObjects)
{
    DO_Config *doConfigRes = new DO_Config[irObjects.data.size()];
    int i = 0;
    for (auto &elem : irObjects.data)
    {
        doConfigRes[i].DO_ID = i;
        doConfigRes[i].access_time = std::stoul(elem.getAccessTime(), nullptr, 0);
        doConfigRes[i].size = getDoConfig_size(elem);
        doConfigRes[i].length = getDoConfig_length(elem, doConfigRes[i].size);
        doConfigRes[i].data = getDoConfig_data(elem, doConfigRes[i].length);

        i++;
    }
    return doConfigRes;
}

uint32_t getDoConfig_size(IrData &irData)
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
        std::cout << "Error: Mismatch of type!" << std::endl;
    }
    return res;
}

uint8_t getDoConfig_length(IrData &irData, uint32_t size)
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

uint8_t *getDoConfig_data(IrData &irData, uint8_t len)
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
            if (fc_glob.endian == CMN_LITTLE_ENDIAN)
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
            if (fc_glob.endian == CMN_LITTLE_ENDIAN)
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

ASF_Config *getAsfConfig(IrObjects &irObjects)
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

uint8_t getAsfConfig_numApe(IrData &irData, IrObjects &irObjects)
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

ASF_variable_part *getAsfConfig_APE_KP(IrData &irData, uint8_t N, IrObjects &irObjects)
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
            res[i].APE_number = getApeOrderNum(link.getOperatorId(), irObjects);

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
uint8_t getApeOrderNum(std::string apeId, IrObjects &irObjects)
{
    uint8_t apeOrderNum = 0;

    /* Iterations on operators */
    for (auto &op : irObjects.operators)
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

int getNumInputLink(std::string opId, std::vector<IrLink> &links)
{
    int res = 0;

    for (auto &elem : links)
    {
        if ((opId.compare(elem.getOperatorId()) == 0) && (elem.getDir() == 0))
            res++;
    }
    return res;
}

int getNumOutputLink(std::string opId, std::vector<IrLink> &links)
{
    int res = 0;

    for (auto &elem : links)
    {
        if ((opId.compare(elem.getOperatorId()) == 0) && (elem.getDir() == 1))
            res++;
    }
    return res;
}

APE_Config *getApeConfig(IrObjects &irObjects)
{
    APE_Config *apeConfigRes = new APE_Config[irObjects.operators.size()];
    int i = 0;
    for (auto &op : irObjects.operators)
    {
        if (!checkNumPorts(op, irObjects))
        {
            throw std::runtime_error(FC_ERR_STR("Mismatch number of in/out ports in XML and radiolib!"));
        }
        apeConfigRes[i].APE_ID = i;
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

uint8_t getApeNumPorts(std::string opId, IrObjects &irObjects)
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

uint8_t *getAccessType(uint8_t apeNumPorts, std::string opId, IrObjects &irObjects)
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

bool checkNumPorts(IrOperator &irOperator, IrObjects &irObjects)
{
    int numInputLink = getNumInputLink(irOperator.getId(), irObjects.links);
    int numOutputLink = getNumOutputLink(irOperator.getId(), irObjects.links);

    IOPortsCnt numIOPortsLib = radioLib.getIOPortsCnt(std::stoul(irOperator.getOpcode()));

    if ((numInputLink == numIOPortsLib.input) && (numOutputLink == numIOPortsLib.output))
    {
        return true;
    }

    return false;
}

size_t getFileLen(std::string fileName)
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

uint8_t *getFileData(std::string fileName)
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

uint32_t detectSize(int dataType, size_t dataValSize)
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
