//
// Created by Елена on 15.05.2022.
//
#include "frontend_compiler.h"
#include <map>
#include <algorithm>

/* ######## Help functions*/
/* Convert function */
IrOperator convertToIrOperator(pugi::xml_node &op_xml);
IrData convertToIrData(pugi::xml_node &data_xml);

/* Show functions */

void showIrOperators(const std::vector<IrOperator> &operators);

void showIrData(const std::vector<IrData> &data);

void showIrLinks(const std::vector<IrLink> &links);

/* Take data */
std::map<int, IrData> takeIrData(pugi::xml_node &op_xml, const std::string &connectType);

std::vector<IrData> takeOutputIrData(pugi::xml_node &op_xml);

/* Add data to vector */
void addIrDataToVector(std::vector<IrData> &data, std::map<int, IrData> &newData);

/* Create link */
void createLinksFromVectorData(std::vector<IrLink> &links, std::map<int, IrData> &data, IrOperator &op, int dir);

IrObjects parseSWIR(const std::string &fileNameSWIR)
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
            /* Take input/output data from operator tag */
            auto inputData = takeIrData(curOperator, "input");
            auto outputData = takeIrData(curOperator, "output");

            /* Add input/output Ir data in Ir objects  */
            addIrDataToVector(irObjects.data, inputData);
            addIrDataToVector(irObjects.data, outputData);

            IrOperator currOp = convertToIrOperator(curOperator);

            /* Add current operator in Ir vector */
            irObjects.operators.push_back(currOp);

            /* Create link objects from input/output IR data and IR operator */
            createLinksFromVectorData(irObjects.links, inputData, currOp, 0);
            createLinksFromVectorData(irObjects.links, outputData, currOp, 1);

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

int fillControlSection(ConfigObjects &configObjects, IrObjects &irObjects);
int fillDoSection(ConfigObjects &configObjects, IrObjects &irObjects);
int fillApeSection(ConfigObjects &configObjects, IrObjects &irObjects);

ConfigObjects convert2rvmIr(IrObjects &irObjects)
{
    ConfigObjects configObjects;
    fillControlSection(configObjects, irObjects);
    fillDoSection(configObjects, irObjects);
    fillApeSection(configObjects, irObjects);
    return configObjects;
}

int fillControlSection(ConfigObjects &configObjects, IrObjects &irObjects)
{
    ControlSection &ctrlSec = configObjects.controlSection;
    ctrlSec.LCF = 1; // means that this is the last Configcode in the task
    ctrlSec.NAF = 0; //
    ctrlSec.Task_ID = 1;
    ctrlSec.RPI_version = 1;  // version number of supported general radio programming interface
    ctrlSec.Reference_ID = 1; // identifier of the reference Radio Library
    ctrlSec.Implementation_version = 1;
    ctrlSec.Developer_ID = 1;
    ctrlSec.Creation_Date = 2022;
    return 0;
}

DO_Config *getDoConfig(IrObjects &irObjects);
ASF_Config *getAsfConfig(IrObjects &irObjects);

int fillDoSection(ConfigObjects &configObjects, IrObjects &irObjects)
{
    DO_Section &doSec = configObjects.doSection;

    doSec.N_DO = irObjects.data.size();
    // doSec.DOs = getDoConfig(irObjects);
    // doSec.ASFs = getAsfConfig(irObjects);
    return 0;
}
int fillApeSection(ConfigObjects &configObjects, IrObjects &irObjects)
{
    return 0;
}
DO_Config *getDoConfig(IrObjects &irObjects)
{
    DO_Config * doConfigRes = new DO_Config[irObjects.data.size()];
    #ifdef xxx
    do_section.DOs = new struct DO_Config[do_section.N_DO];
    int i = 0;
    for (auto &elem : DataHeap)
    {
        do_section.DOs[i].DO_ID = i;
        do_section.DOs[i].access_time = stoi(elem.getAccessTime());
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
        i++;
    }
    #endif 
}
ASF_Config *getAsfConfig(IrObjects &irObjects)
{
}

void filligControlSections(struct ControlSection &controlSection)
{

    controlSection.LCF = 1; // means that this is the last Configcode in the task
    controlSection.NAF = 0; //
    controlSection.Task_ID = 1;
    controlSection.RPI_version = 1;  // version number of supported general radio programming interface
    controlSection.Reference_ID = 1; // identifier of the reference Radio Library
    controlSection.Implementation_version = 1;
    controlSection.Developer_ID = 1;
    controlSection.Creation_Date = 2022;
}

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
    data.setAccessTime(data_xml.attribute("access_time").as_int());
    data.setValue(data_xml.attribute("value").as_string());

    return data;
}

void showIrObjects(const struct IrObjects &irObjects)
{
    /* Show result Ir objects */
    std::cout << "Operators" << std::endl;
    showIrOperators(irObjects.operators);
    std::cout << " - " << std::endl;
    std::cout << "Data" << std::endl;
    showIrData(irObjects.data);
    std::cout << " - " << std::endl;
    std::cout << "link" << std::endl;
    showIrLinks(irObjects.links);
    std::cout << " - " << std::endl;
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
