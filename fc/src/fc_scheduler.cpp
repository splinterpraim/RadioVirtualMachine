#include "fc_scheduler.hpp"

#include "pugixml/pugixml.hpp"

#include "system_func.hpp"


// fc_Scheduler::fc_Scheduler(fc_SettingBlock& settingBlock): settingBlock(settingBlock)
// {

// }
/* Private */
bool fc_Scheduler::loadProgram2Parser(pugi::xml_node programNode,std::vector<fc_Parser>& parsers)
{
    std::cout << programNode.attribute("name").as_string() << std::endl;
    std::string name = programNode.attribute("name").as_string();
    std::string path = programNode.attribute("path").as_string();

    /* Load program from current document */
    if (programNode.first_child())
    {
        auto position = parsers.size();
        parsers.resize(position+1);
        parsers[position].setSettingBlock(*settingBlock);
        std::string targetDir = settingBlock->getDirCC() + std::string("/") +name;
        createDir(targetDir);
        parsers[position].setTargetDir(targetDir);
        parsers[position].loadProgramFromNode(programNode);
    }
    /* Load program from child document */
    else if(path.compare("") != 0)
    {
        auto position = parsers.size();
        parsers.resize(position+1);
        parsers[position].setSettingBlock(*settingBlock);
        std::string targetDir = settingBlock->getDirCC() + std::string("/") +name;
        createDir(targetDir);
        parsers[position].setTargetDir(targetDir);
        std::string progPath = settingBlock->getDirXML() + std::string("/") + path;
        parsers[position].loadProgramFromFile(progPath);
    }
    else
    {
        return false;
    }
    return true;
}

void fc_Scheduler::schedule(std::string inputTaskFilePath, std::vector<fc_Parser>& parsers)
{
    /* Load xml file */
    pugi::xml_document doc;
    pugi::xml_parse_result ret = doc.load_file(inputTaskFilePath.c_str());
    if(!ret)
    {
        throw std::runtime_error(ret.description());
    }
    doc.print(cout);

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
        if (!loadProgram2Parser(program, parsers))
        {
            std::string err = std::string("body for program '") + program.attribute("name").as_string() + 
                              std::string("' not found in file: ") + inputTaskFilePath;
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

void fc_Scheduler::setSettingBlock(fc_SettingBlock& settingBlock)
{
    this->settingBlock = &settingBlock;
}
