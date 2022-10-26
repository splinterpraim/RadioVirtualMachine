//
// Created by Елена on 15.05.2022.
//
#include "frontend_compiler.h"
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include "fc_help_func.hpp"

#define MASK_LOW_BIT 0x01  /* 0000 0001 */
#define MASK_MS_6_BIT 0xfc /* 1111 1100 */
#define MASK_LS_2_BIT 0x03 /* 0000 0011 */
#define MASK_1_BYTE 0xff   /* 1111 1111 */

int fillControlSection(ConfigObjects &configObjects, IrObjects &irObjects);
int fillDoSection(ConfigObjects &configObjects, IrObjects &irObjects);
int fillApeSection(ConfigObjects &configObjects, IrObjects &irObjects);

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

int fillDoSection(ConfigObjects &configObjects, IrObjects &irObjects)
{
    DO_Section &doSec = configObjects.doSection;

    doSec.N_DO = irObjects.data.size();
    doSec.DOs = getDoConfig(irObjects);
    doSec.ASFs = getAsfConfig(irObjects);
    return 0;
}

int fillApeSection(ConfigObjects &configObjects, IrObjects &irObjects)
{
    APE_Section &apeSec = configObjects.apeSection;
    apeSec.N_APE = irObjects.operators.size();
    apeSec.APEs = getApeConfig(irObjects);
    return 0;
}

/* Main functions */
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

ConfigObjects convert2rvmIr(IrObjects &irObjects)
{
    ConfigObjects configObjects;
    fillControlSection(configObjects, irObjects);
    fillDoSection(configObjects, irObjects);
    fillApeSection(configObjects, irObjects);
    return configObjects;
}

void showConfigObjects(ConfigObjects &cfgObj)
{
    std::cout << "Control Section: " << std::endl;
    showControlSection(cfgObj.controlSection);
    std::cout << "DO Section: " << std::endl;
    showDoSection(cfgObj.doSection);
    std::cout << "APE Section: " << std::endl;
    showApeSection(cfgObj.apeSection);
}

int clearConfigObjects(ConfigObjects &cfgObj)
{
    delete[] cfgObj.doSection.DOs->data;
    delete[] cfgObj.doSection.DOs;
    delete[] cfgObj.doSection.ASFs->APE_KP;
    delete[] cfgObj.doSection.ASFs;
    return 0;
}

#define CFG_WRITE(v)                                        \
    for (int i = sizeof(v); i > 0; i--)                     \
    {                                                       \
        uint8_t new_v = (v >> (8 * (i - 1))) & MASK_1_BYTE; \
        cfgF.write((char *)&(new_v), sizeof(char));         \
    }

void createRVMcfgcode(ConfigObjects &cfgObj, const std::string &fileNameBin)
{

    uint8_t curbyte = 0;

    std::ofstream cfgF(fileNameBin, std::ios::binary);
    {
        /* Control Section */
        ControlSection &ctrlSec = cfgObj.controlSection;

        // LCF, NAF
        curbyte = (ctrlSec.LCF & MASK_LOW_BIT) << 7;
        curbyte |= (ctrlSec.NAF & MASK_LOW_BIT) << 6;
        CFG_WRITE(curbyte)
        CFG_WRITE(ctrlSec.Creation_Date)
        // cfgF.write((char *)&curbyte, sizeof(curbyte));

        // // Task_ID
        // cfgF.write((char *)&ctrlSec.Task_ID, sizeof(ctrlSec.Task_ID));

        // // RPI_version
        // cfgF.write((char *)&ctrlSec.RPI_version, sizeof(ctrlSec.RPI_version));

        // // Reference_ID
        // cfgF.write((char *)&ctrlSec.Reference_ID, sizeof(ctrlSec.Reference_ID));

        // // Implementation_version
        // cfgF.write((char *)&(ctrlSec.Implementation_version), sizeof(ctrlSec.Implementation_version));

        // // Developer_ID
        // curbyte = (ctrlSec.Developer_ID >> 8) & MASK_1_BYTE;
        // cfgF.write((char *)&curbyte, sizeof(curbyte));
        // curbyte = ctrlSec.Developer_ID & MASK_1_BYTE;
        // cfgF.write((char *)&curbyte, sizeof(curbyte));

        // Creation_Date
        // cfgF.write((char *)&(ctrlSec.Creation_Date), sizeof(ctrlSec.Creation_Date));

        /* DO Section */

        // create byte 10
        //  curbyte = cfgObj.doSection.N_DO;
        //  cfgF.write((char *)&curbyte, sizeof(curbyte));

        // for (uint8_t i = 0; i < cfgObj.doSection.N_DO; i++)
        // {
        //     curbyte = cfgObj.doSection.DOs[i].DO_ID;
        //     cfgF.write((char *)&curbyte, sizeof(curbyte));
        //     curbyte = cfgObj.doSection.DOs[i].size

        // }

        /* APE Section */
    }
    cfgF.close();
}
