#include "fc_help_func.hpp"

#define XML_TYPE_INT "int"
#define XML_TYPE_FLOAT "float"
#define XML_TYPE_STRING "string"


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



/* ######## Help functions*/
/* ************************** convert2rvmIr */

DO_Config *getDoConfig(IrObjects &irObjects)
{
    DO_Config *doConfigRes = new DO_Config[irObjects.data.size()];
    int i = 0;
    for (auto &elem : irObjects.data)
    {
        doConfigRes[i].DO_ID = i;
        doConfigRes[i].access_time = std::stoul(elem.getAccessTime(), nullptr, 0);
        doConfigRes[i].data = getDoConfig_sizeLenData(elem, doConfigRes[i].size, doConfigRes[i].length);

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
uint8_t *getDoConfig_sizeLenData(class IrData &irData, uint32_t &doCfgSize, uint8_t &doCfgLen)
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
ASF_Config *getAsfConfig(IrObjects &irObjects)
{
    return NULL;
}
