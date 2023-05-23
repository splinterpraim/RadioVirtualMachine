#include "fc_scheduler.hpp"

#include "pugixml/pugixml.hpp"

// fc_Scheduler::fc_Scheduler(fc_SettingBlock& settingBlock): settingBlock(settingBlock)
// {

// }


void fc_Scheduler::schedule(std::string inputTaskFilePath, std::vector<fc_Parser>& parsers)
{
    /* Load xml file */
    pugi::xml_document doc;
    pugi::xml_parse_result ret = doc.load_file(inputTaskFilePath.c_str());
    if(!ret)
    {
        throw std::runtime_error(ret.description());
    }

    /* Take task tag */
    pugi::xml_node task = doc.child("task"); 
    if (!task)
    {
        std::string err = std::string("not found <task> tag in file: ") + inputTaskFilePath;
        throw std::runtime_error(err);
    }

    /* Iterate over program tag */
    for(pugi::xml_node program : task.children("program"))
    {
        std::cout << program.attribute("name").as_string() << std::endl;
        std::string name = program.attribute("name").as_string();
        std::string path = program.attribute("path").as_string();

        /* Load program from current document */
        if (program.first_child())
        {

        }
        /* Load program from child document */
        else if(path.compare("") != 0)
        {

        }
        /* Program body not found */
        else
        {
            std::string err = std::string("body for program '") + name + std::string("' not found in file: ") + inputTaskFilePath;
            throw std::runtime_error(err);
        }
        

        // fc_Parser p(name, path, );
    }
    // auto inputDataExternal = takeIrDataInputExternal(program);
    // auto outputDataExternal = takeIrDataOutputExternal(program);

    // addIrDataToVector(irObjects.data, inputDataExternal);
    // addIrDataToVector(irObjects.data, outputDataExternal);

    // createLinksFromVectorData(irObjects.links, inputDataExternal, "", LINK_INPUT);
    // createLinksFromVectorData(irObjects.links, outputDataExternal, "", LINK_OUTPUT);

    // pugi::xml_node curOperator = program.child("operator");

    // /* Parse tag inside */
    // while (true)
    // {
    //     IrOperator currOp = convertToIrOperator(curOperator);

    //     /* Take input/output data from operator tag */
    //     auto inputData = takeIrDataInput(curOperator);
    //     auto outputData = takeIrDataOutput(curOperator);

    //     /* Add input/output Ir data in Ir objects  */
    //     addIrDataToVector(irObjects.data, inputData);
    //     addIrDataToVector(irObjects.data, outputData);

    //     /* Add current operator in Ir vector */
    //     irObjects.operators.push_back(currOp);

    //     /* Create link objects from input/output IR data and IR operator */
    //     createLinksFromVectorData(irObjects.links, inputData, currOp.getId(), LINK_INPUT);
    //     createLinksFromVectorData(irObjects.links, outputData, currOp.getId(), LINK_OUTPUT);

    //     auto xmlNodeType = curOperator.next_sibling("operator").type();

    //     /* Check end of sibling operator list */
    //     if (xmlNodeType == pugi::node_null)
    //     {
    //         curOperator = curOperator.parent();
    //         std::string xmlNodeName = curOperator.name();

    //         /* Check end of xml operator list */
    //         if (xmlNodeName.compare("program") == 0)
    //         {
    //             break;
    //         }
    //         else
    //         {
    //             throw std::runtime_error(FC_ERR_STR("unknown tag during XML parsing"));
    //         }
    //     }
    //     curOperator = curOperator.next_sibling("operator");
    // }
    // return irObjects;
}
