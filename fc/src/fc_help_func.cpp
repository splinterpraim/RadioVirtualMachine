#include "fc_help_func.hpp"
#include "common.hpp"
#include "fc_glob.hpp"
#include "fc_system.hpp"

#include <fstream>
#include <cstring>
#include <exception>
#include <stdexcept>

#define XML_TYPE_INT "int"
#define XML_TYPE_FLOAT "float"
#define XML_TYPE_STRING "string"

#define DO_CFG_LEN_FOR_FILE 255

extern fc_glob_t fc_glob;

/* ######## Help functions*/
IrOperator convertToIrOperator(pugi::xml_node &op_xml)
{
    IrOperator op;
    op.setId(op_xml.attribute("id").value());
    op.setType(op_xml.attribute("type").value());

    return op;
}

IrData convertToIrData(pugi::xml_node &data_xml)
{
    IrData data;
    data.setId(data_xml.attribute("id").as_string());
    data.setType(data_xml.attribute("type").as_string());
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
                  << "type = " << el.getType() << std::endl;
    }
}

void showIrData(const std::vector<IrData> &data)
{
    for (auto el : data)
    {
        std::cout << "id = " << el.getId() << ", ";
        std::cout << "type = " << el.getType() << ", ";
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
    for (auto data : op_xml)
    {
        std::string dataConnectType = data.attribute("connect_type").as_string();
        if (dataConnectType == connectType)
        {
            IrData currData = convertToIrData(data);
            int order = data.attribute("order").as_int();
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
}

void showDO_Config(DO_Config &doCfg, uint8_t N_DO)
{
    std::string space4 = "    ";
    DO_Config *ptrDoCfg = &doCfg;
    for (uint8_t i = 0; i < N_DO; i++)
    {
        std::cout << space4 << "DO_ID: " << (int)ptrDoCfg[i].DO_ID << ", size: " << (int)ptrDoCfg[i].size << ", access_time: " << (int)ptrDoCfg[i].access_time << ", length: " << (int)ptrDoCfg[i].length <<
            //  ", data: "<< (int) ptrDoCfg[i].data <<
            std::endl;
    }
}

DO_Config *getDoConfig(IrObjects &irObjects)
{
    //+todo: 1. type of file is not txt - it's binary.
    //+todo: 2. error - if there are full value and path
    //+todo: 3. mb get data from file immediately

    DO_Config *doConfigRes = new DO_Config[irObjects.data.size()];
    int i = 0;
    for (auto &elem : irObjects.data)
    {
        doConfigRes[i].DO_ID = i;
        doConfigRes[i].access_time = std::stoul(elem.getAccessTime(), nullptr, 0);
        doConfigRes[i].size = getDoConfig_size(elem);
        doConfigRes[i].length = getDoConfig_length(elem);
        doConfigRes[i].data = getDoConfig_data(elem, doConfigRes[i].length);

#ifdef xxx

        if (elem.getType() == "float")
        {
            do_section.DOs[i].size = sizeof(float);
        }
        if (elem.getPath() == "")
        {
            if (elem.getValue() != "")
            {
                if (elem.getType() == "float")
                {
                    do_section.DOs[i].length = sizeof(float);
                    //***********************
                    // convert float to bin (union)
                    do_section.DOs[i].data = new uint8_t[sizeof(float)];
                    auto bufData = stof(elem.getValue());
                    memcpy(do_section.DOs[i].data, &bufData, sizeof(float));
                }
            }
        }
        else
        {
            do_section.DOs[i].length = elem.getPath().size();
            do_section.DOs[i].data = new uint8_t[elem.getPath().size()];
            auto bufData = elem.getPath().c_str();
            memcpy(do_section.DOs[i].data, &bufData, elem.getPath().size());
        }
#endif
        i++;
    }
    return doConfigRes;
}

uint32_t getDoConfig_size(IrData &irData)
{
    uint32_t res = 0;
    if (irData.getType() == XML_TYPE_INT)
    {
        res = sizeof(int);
    }
    else if (irData.getType() == XML_TYPE_FLOAT)
    {
        res = sizeof(float);
    }
    else if (irData.getType() == XML_TYPE_STRING)
    {
        res = irData.getValue().size();
    }
    else
    {
        std::cout << "Error: Mismatch of type!" << std::endl;
    }
    return res;
}

uint8_t getDoConfig_length(IrData &irData)
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
        if (irData.getType() == XML_TYPE_INT)
        {
            res = sizeof(int);
        }
        else if (irData.getType() == XML_TYPE_FLOAT)
        {
            res = sizeof(float);
        }
        else if (irData.getType() == XML_TYPE_STRING)
        {
            res = irData.getValue().size();
        }
        else
        {
            throw std::runtime_error(FC_ERR_STR("Mismatch of type!"));
        }
    }
    /* Filled path */
    else if (doPath.length() != 0)
    {
        res = getFileLen(doPath);
    }
    return res;
}

uint8_t *getDoConfig_sizeLenData(IrData &irData, uint32_t &doCfgSize, uint8_t &doCfgLen)
{
    if (irData.getType() == XML_TYPE_INT)
    {
        doCfgSize = sizeof(int);
        // len / data (file/value)
    }
    else if (irData.getType() == XML_TYPE_FLOAT)
    {
        doCfgSize = sizeof(float);
    }
    else if (irData.getType() == XML_TYPE_STRING)
    {
        doCfgSize = irData.getValue().size();
    }
    else
    {
        // error
    }
    return 0;
}

uint8_t *getDoConfig_data(IrData &irData, uint8_t len)
{
    uint8_t *res = nullptr;
    std::string doVal = irData.getValue();
    std::string doPath = irData.getPath();

    /* Filled both value and path */
    if ((doVal.length() != 0) && (doPath.length() != 0))
    {
        throw std::runtime_error(FC_ERR_STR("Filled both value and path!"));
    }

    //! seqf
    /* Filled value */
    if (doVal.length() != 0)
    {
        std::cout << "d1" << std::endl;
        if (irData.getType() == XML_TYPE_INT)
        {
            int intVal = std::stoi(doVal);
            if (fc_glob.endian == CMN_BIG_ENDIAN)
            {
                intVal = convertToLittleEndian(intVal);
            }
            size_t intValLen = sizeof(intVal);

            res = new uint8_t[len];
            std::memcpy((void *)res, (const void *)&intVal, len);
        }
        else if (irData.getType() == XML_TYPE_FLOAT)
        {
            int fltVal = std::stof(doVal);
            //! need convert to endians
            // if (fc_glob.endian == CMN_BIG_ENDIAN)
            // {
            //     fltVal = convertToLittleEndian(fltVal);
            // }
            size_t intValLen = sizeof(fltVal);

            res = new uint8_t[len];
            std::memcpy((void *)res, (const void *)&fltVal, len);
        }
        else if (irData.getType() == XML_TYPE_STRING)
        {
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
        // open file
        // read info
        // check size
        std::cout << "p1" << std::endl;
        res = getFileData(doPath);
    }

    // todo: show data
    // todo: delete data mem
    std::cout << "d0: " << doVal << ")" << " len = " << (int)len << std::endl;

    for (size_t i = 0; i < len; ++i)
        std::cout << (int)res[i] << " ";
    std::cout << std::endl;
    std::cout << "d_end: " << doVal << ")" << std::endl;

    return res;
}

ASF_Config *getAsfConfig(IrObjects &irObjects)
{
    return NULL;
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

uint8_t* getFileData(std::string fileName)
{
    uint8_t * res = nullptr;
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
