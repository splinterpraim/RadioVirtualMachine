/**
 * @file fc_parser_swir.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Implementation of FC SWIR Parser.
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "fc_parser_swir.hpp"

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <sstream>

#include "common.hpp"
#include "fc_logger.hpp"
#include "reference_radio_library.hpp"



/* Private */

std::map<int, IrData> fc_ParserSWIR::takeIrDataInput(pugi::xml_node &op_xml)
{
    std::map<int, IrData> dataResult;

    /* Gets description of operator in Radio lib */
    int opcode = op_xml.attribute("opcode").as_int();
    std::string name = op_xml.attribute("id").as_string();
    const radioLibrary_el * op_rl = rl_getOperator(opcode);
    uint8_t inputCnt = rl_getInputPortCnt(opcode);

    /* If opcode doesn't found */
    if (!op_rl)
    {
        throw std::runtime_error(FC_ERR_STR("Unknown opcode '%d' for operator '%s'", opcode, name.c_str()));
    }

    /* Loop for finding and converting Data from xml to IR */
    for (pugi::xml_node data = op_xml.child("data"); data; data = data.next_sibling("data"))
    {
        std::string dataConnectType = data.attribute("connect_type").as_string();
        if (dataConnectType.compare("input") == 0)
        {
            IrData currData = convertToIrData(data);

            /* Finds data type */
            int order = data.attribute("order").as_int();
            int dataType = -1;

            if (op_rl->flags.infinityInPorts == RL_ENABLE)
            {
                dataType = op_rl->flags.typeOfInData;
            }
            else
            {
                if (order > inputCnt)
                {
                    throw std::runtime_error(std::string("Too many inputs for operator '") + name + std::string("'"));
                }
                dataType = op_rl->ports[order - 1].typeOfData;
            }
            currData.setType(dataType);
            dataResult[order] = currData;
        }
    }
    return dataResult;
}

std::map<int, IrData> fc_ParserSWIR::takeIrDataOutput(pugi::xml_node &op_xml)
{
    std::map<int, IrData> dataResult;

    /* Gets description of operator in Radio lib */
    int opcode = op_xml.attribute("opcode").as_int();
    std::string name = op_xml.attribute("id").as_string();
    const radioLibrary_el * op_rl = rl_getOperator(opcode);
    uint8_t inputCnt = rl_getInputPortCnt(opcode);
    uint8_t outputCnt = rl_getOutputPortCnt(opcode);

    /* If opcode doesn't found */
    if (!op_rl)
    {
        throw std::runtime_error(FC_ERR_STR("Unknown opcode '%d' for operator '%s'", opcode, name.c_str()));
    }

    /* Loop for finding and converting Data from xml to IR */
    for (pugi::xml_node data = op_xml.child("data"); data; data = data.next_sibling("data"))
    {
        std::string dataConnectType = data.attribute("connect_type").as_string();
        if (dataConnectType.compare("output") == 0)
        {
            IrData currData = convertToIrData(data);

            /* Finds data type */
            int order = data.attribute("order").as_int();
            int dataType = -1;

            if (op_rl->flags.infinityOutPorts == RL_ENABLE)
            {
                dataType = op_rl->flags.typeOfOutData;
            }
            else
            {
                if (order > outputCnt)
                {
                    throw std::runtime_error(std::string("Too many outputs for operator '") + name + std::string("'"));
                }
                int index = order + inputCnt - 1; 
                dataType = op_rl->ports[index].typeOfData;
            }

            currData.setType(dataType);
            dataResult[order] = currData;
        }
    }
    return dataResult;
}

std::map<int, IrData> fc_ParserSWIR::takeIrDataInputExternal(pugi::xml_node &op_xml)
{
    std::map<int, IrData> dataResult;

    /* Loop for finding and converting Data from xml to IR */
    for (pugi::xml_node data = op_xml.child("data"); data; data = data.next_sibling("data"))
    {
        std::string dataConnectType = data.attribute("connect_type").as_string();
        if (dataConnectType.compare("input") == 0)
        {
            IrData currData = convertToIrData(data);
            currData.setType(RL_TYPE_NOT_SET);
            currData.setExternal(1);
            int order = data.attribute("order").as_int();
            dataResult[order] = currData;
        }
    }

    return dataResult;
}
std::map<int, IrData> fc_ParserSWIR::takeIrDataOutputExternal(pugi::xml_node &op_xml)
{
    std::map<int, IrData> dataResult;

    /* Loop for finding and converting Data from xml to IR */
    for (pugi::xml_node data = op_xml.child("data"); data; data = data.next_sibling("data"))
    {
        std::string dataConnectType = data.attribute("connect_type").as_string();
        if (dataConnectType.compare("output") == 0)
        {
            IrData currData = convertToIrData(data);
            currData.setType(RL_TYPE_NOT_SET);
            currData.setExternal(1);
            int order = data.attribute("order").as_int();
            dataResult[order] = currData;
        }
    }
    return dataResult;
}

IrData fc_ParserSWIR::convertToIrData(pugi::xml_node &data_xml)
{
    IrData data;
    data.setId(data_xml.attribute("id").as_string());
    // data.setType(data_xml.attribute("type").as_string());
    data.setPath(data_xml.attribute("path").as_string());
    data.setAccessTime(data_xml.attribute("access_time").as_string());
    data.setValue(data_xml.attribute("value").as_string());

    return data;
}

void fc_ParserSWIR::addIrDataToVector(std::vector<IrData> &data, std::map<int, IrData> &newData)
{
    for (auto el : newData)
    {
        /* If not exist */
        std::vector<IrData>::iterator it= std::find(data.begin(), data.end(), el.second);
        if (it == data.end())
        {
            data.push_back(el.second);
        }
        else if (it->getType() == RL_TYPE_NOT_SET)
        {
            it->setType(el.second.getType());
        }
    }
}

IrOperator fc_ParserSWIR::convertToIrOperator(pugi::xml_node &op_xml)
{
    IrOperator op;
    op.setId(op_xml.attribute("id").value());
    op.setType(op_xml.attribute("type").value());
    op.setOpcode(op_xml.attribute("opcode").value());
    if (op.getType().compare("Complex") == 0)
    {
        pugi::xml_node subprog_xml = op_xml.child("program");
        std::string subprog_str;
        std::string name = subprog_xml.attribute("name").value();
        std::string path = subprog_xml.attribute("path").value();
        std::string progPath = settingBlock->getDirXML() + std::string("/") + path;
        op.setSubname(name);
        op.setSubpath(progPath);
        /* Load program from current document */
        if (subprog_xml.first_child())
        {
            loadProgramFromNode2Str__(subprog_xml, subprog_str);
        }
        /* Load program from child document */
        else if(path.compare("") != 0)
        {
            loadProgramFromFile2Str__(progPath, subprog_str);
        }
        else
        {
            std::string errMsg = std::string("No program '") + name + ("' found") ;
            throw std::runtime_error(errMsg);
        }
        op.setSubprogram(subprog_str);
    }

    return op;
}

void fc_ParserSWIR::createLinksFromVectorData(std::vector<IrLink> &links, std::map<int, IrData> &data, const std::string &opId, bool dir)
{
    for (auto el : data)
    {
        links.push_back(IrLink(el.second.getId(), opId, dir, el.first));
    }
}

/* Public */

IrObjects fc_ParserSWIR::parse(const pugi::xml_document &doc)
{
    /* Declaration IrObjects */
    IrObjects irObjects;

    /* Take top tag */
    pugi::xml_node program = doc.child("program");
    auto inputDataExternal = takeIrDataInputExternal(program);
    auto outputDataExternal = takeIrDataOutputExternal(program);

    addIrDataToVector(irObjects.data, inputDataExternal);
    addIrDataToVector(irObjects.data, outputDataExternal);

    createLinksFromVectorData(irObjects.links, inputDataExternal, "", RL_INPUT_PORT);
    createLinksFromVectorData(irObjects.links, outputDataExternal, "", RL_OUTPUT_PORT);

    pugi::xml_node curOperator = program.child("operator");
    if(!curOperator)
    {
        throw std::runtime_error(std::string("No operators found, program is empty"));
    }

    /* Parse tag inside */
    while (true)
    {
        IrOperator currOp = convertToIrOperator(curOperator);

        /* Take input/output data from operator tag */
        auto inputData = takeIrDataInput(curOperator);
        auto outputData = takeIrDataOutput(curOperator);

        /* Add input/output Ir data in Ir objects  */
        addIrDataToVector(irObjects.data, inputData);
        addIrDataToVector(irObjects.data, outputData);

        /* Add current operator in Ir vector */
        irObjects.operators.push_back(currOp);

        /* Create link objects from input/output IR data and IR operator */
        createLinksFromVectorData(irObjects.links, inputData, currOp.getId(), RL_INPUT_PORT);
        createLinksFromVectorData(irObjects.links, outputData, currOp.getId(), RL_OUTPUT_PORT);

        auto xmlNodeType = curOperator.next_sibling("operator").type();

        /* Check end of sibling operator list */
        if (xmlNodeType == pugi::node_null)
        {
            curOperator = curOperator.parent();
            std::string xmlNodeName = curOperator.name();

            /* Check end of xml operator list */
            if (xmlNodeName.compare("program") == 0)
            {
                break;
            }
            else
            {
                throw std::runtime_error(FC_ERR_STR("unknown tag during XML parsing"));
            }
        }
        curOperator = curOperator.next_sibling("operator");
    }
    return irObjects;
}

void fc_ParserSWIR::setSettingBlock(fc_SettingBlock& settingBlock)
{
    this->settingBlock = &settingBlock;
}

fc_SettingBlock& fc_ParserSWIR::getSettingBlock() const
{
    return *settingBlock;
}

void fc_ParserSWIR::loadProgramFromFile__(const std::string& progPath, pugi::xml_document &progDoc)
{
    pugi::xml_parse_result ret = progDoc.load_file(progPath.c_str());
    if(!ret)
    {
        std::string errMsg = std::string("Failed to load xml file: ") + progPath + std::string(" (description: ") + ret.description() + std::string(")");
        throw std::runtime_error(errMsg);
    }
}
void fc_ParserSWIR::loadProgramFromNode__(const pugi::xml_node &programNode, pugi::xml_document &progDoc)
{
    std::stringstream ss;
    std::string xmlDoc;
    programNode.print(ss);
    xmlDoc = ss.str();
    pugi::xml_parse_result ret = progDoc.load_string(xmlDoc.c_str());
    if(!ret)
    {
        std::cout << ret.description() << std::endl;
        throw std::runtime_error(ret.description());
    }
}

void fc_ParserSWIR::loadProgramFromStr__(const std::string& progStr, pugi::xml_document &programDoc)
{
    pugi::xml_parse_result ret = programDoc.load_string(progStr.c_str());
    if(!ret)
    {
        std::cout << ret.description() << std::endl;
        throw std::runtime_error(ret.description());
    }
}

void fc_ParserSWIR::loadProgramFromFile2Str__(const std::string& progPath, std::string &progStr)
{
    pugi::xml_document doc;
    pugi::xml_parse_result ret = doc.load_file(progPath.c_str());
    if(!ret)
    {
        std::string errMsg = std::string("Failed to load xml file: ") + progPath + std::string(" (description: ") + ret.description() + std::string(")");
        throw std::runtime_error(errMsg);
    }
    loadProgramFromNode2Str__(doc, progStr);
}

void fc_ParserSWIR::loadProgramFromNode2Str__(const pugi::xml_node &programNode, std::string &progStr)
{
    std::stringstream ss;
    std::string xmlDoc;
    programNode.print(ss);
    progStr = ss.str();
}