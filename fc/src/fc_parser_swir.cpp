#include "fc_parser_swir.hpp"


#include "radio_library.hpp"
#include "common.hpp"

extern RadioLibrary radioLib;

/* Private */
std::map<int, IrData> fc_Parser_SWIR::takeIrData(pugi::xml_node &op_xml, const std::string &connectType)
{
    //    std::vector<IrData> dataResult;
    std::map<int, IrData> dataResult;

    /* Gets description of operator in Radio lib */
    rl_Operator op_rl = radioLib.findByOpCode(op_xml.attribute("opcode").as_int());
    if (op_rl.name.length() == 0)
    {
        throw std::runtime_error(FC_ERR_STR("Unknown opcode for operator"));
    }

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
                dataType = op_rl.ports.in[order - 1].type; // todo: fix, because not work for undefined num of inputs
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

IrData fc_Parser_SWIR::convertToIrData(pugi::xml_node &data_xml)
{
    IrData data;
    data.setId(data_xml.attribute("id").as_string());
    // data.setType(data_xml.attribute("type").as_string());
    data.setPath(data_xml.attribute("path").as_string());
    data.setAccessTime(data_xml.attribute("access_time").as_string());
    data.setValue(data_xml.attribute("value").as_string());

    return data;
}

void fc_Parser_SWIR::addIrDataToVector(std::vector<IrData> &data, std::map<int, IrData> &newData)
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

IrOperator fc_Parser_SWIR::convertToIrOperator(pugi::xml_node &op_xml)
{
    IrOperator op;
    op.setId(op_xml.attribute("id").value());
    op.setType(op_xml.attribute("type").value());
    op.setOpcode(op_xml.attribute("opcode").value());
    return op;
}

void fc_Parser_SWIR::createLinksFromVectorData(std::vector<IrLink> &links, std::map<int, IrData> &data, IrOperator &op, int dir)
{
    for (auto el : data)
    {
        links.push_back(IrLink(el.second.getId(), op.getId(), dir, el.first));
    }
}

/* Public */

IrObjects fc_Parser_SWIR::parse(const std::string &fileNameSWIR)
{
    /* Declaration IrObjects */
    IrObjects irObjects;

    /* Load xml file */
    pugi::xml_document doc;
    doc.load_file(fileNameSWIR.c_str());

    /* Take top tag */
    pugi::xml_node program = doc.child("program");
    pugi::xml_node curOperator = program.first_child();

    /* Parse tag inside */
    while (true)
    {
        std::string operatorType = curOperator.attribute("type").as_string();
        /* If Complex */
        if (operatorType.compare("Complex") == 0)
        {
            curOperator = curOperator.child("operator");
        }
        /* If terminal */
        else
        {
            std::string input_s = "input";
            std::string output_s = "output";
            /* Take input/output data from operator tag */
            auto inputData = takeIrData(curOperator, input_s);
            auto outputData = takeIrData(curOperator, output_s);
    

            /* Add input/output Ir data in Ir objects  */
            addIrDataToVector(irObjects.data, inputData);
            addIrDataToVector(irObjects.data, outputData);

            IrOperator currOp = convertToIrOperator(curOperator);

            /* Add current operator in Ir vector */
            irObjects.operators.push_back(currOp);

            /* Create link objects from input/output IR data and IR operator */
            createLinksFromVectorData(irObjects.links, inputData, currOp, LINK_INPUT);
            createLinksFromVectorData(irObjects.links, outputData, currOp, LINK_OUTPUT);

            auto xmlNodeType = curOperator.next_sibling().type();

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
            }
            curOperator = curOperator.next_sibling();
        }
    }
    return irObjects;
}
