#include "fc_parser_swir.hpp"

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <sstream>

#include "radio_library.hpp"
#include "common.hpp"

extern RadioLibrary radioLib;

/* Private */

std::map<int, IrData> fc_ParserSWIR::takeIrDataInput(pugi::xml_node &op_xml)
{
    std::map<int, IrData> dataResult;

    /* Gets description of operator in Radio lib */
    int opcode = op_xml.attribute("opcode").as_int();
    rl_Operator op_rl = radioLib.findByOpCode(opcode);
    /* If opcode doesn't found */
    if (op_rl.name.length() == 0)
    {
        throw std::runtime_error(std::string("Unknown opcode '") + std::to_string(opcode) + std::string("' for operator")); // todo: FC_ERR_STR
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

            if (op_rl.ports.fInfinityInPorts == RL_YES)
            {
                dataType = op_rl.ports.in[0].type; // todo: fix, because not work for undefined num of inputs
            }
            else
            {
                dataType = op_rl.ports.in[order - 1].type; // todo: fix, because not work for undefined num of inputs
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
    rl_Operator op_rl = radioLib.findByOpCode(opcode);
    /* If opcode doesn't found */
    if (op_rl.name.length() == 0)
    {
        throw std::runtime_error(std::string("Unknown opcode '") + std::to_string(opcode) + std::string("' for operator")); // todo: FC_ERR_STR
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

            dataType = op_rl.ports.out[order - 1].type;

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

        op.setSubname(name);
        op.setSubpath(path);
        /* Load program from current document */
        if (subprog_xml.first_child())
        {
            loadProgramFromNode2Str__(subprog_xml, subprog_str);
        }
        /* Load program from child document */
        else if(path.compare("") != 0)
        {
            loadProgramFromFile2Str__(path, subprog_str);
        }
        else
        {
            std::string errMsg = std::string("No program'") + name + ("'found") ;
            throw std::runtime_error(errMsg);
        }
        op.setSubprogram(subprog_str);
    }

    return op;
}

void fc_ParserSWIR::createLinksFromVectorData(std::vector<IrLink> &links, std::map<int, IrData> &data, const std::string &opId, int dir)
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

    createLinksFromVectorData(irObjects.links, inputDataExternal, "", LINK_INPUT);
    createLinksFromVectorData(irObjects.links, outputDataExternal, "", LINK_OUTPUT);

    pugi::xml_node curOperator = program.child("operator");

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
        createLinksFromVectorData(irObjects.links, inputData, currOp.getId(), LINK_INPUT);
        createLinksFromVectorData(irObjects.links, outputData, currOp.getId(), LINK_OUTPUT);

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


void fc_ParserSWIR::loadProgramFromFile__(const std::string& progPath, pugi::xml_document &progDoc)
{
    pugi::xml_parse_result ret = progDoc.load_file(progPath.c_str());
    if(!ret)
    {
        std::string errMsg = std::string("Can't load program file: '") + progPath + std::string("'. ") + ret.description();
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
        std::string errMsg = std::string("Can't load program file: '") + progPath + std::string("'. ") + ret.description();
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