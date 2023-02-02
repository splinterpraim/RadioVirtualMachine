//
// Created by Елена on 15.05.2022.
//
#include "frontend_compiler.hpp"
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include "fc_help_func.hpp"

#define MASK_LOW_BIT 0x01  /* 0000 0001 */
#define MASK_MS_6_BIT 0xfc /* 1111 1100 */
#define MASK_LS_2_BIT 0x03 /* 0000 0011 */
#define MASK_LS_3_BIT 0x07 /* 0000 0111 */
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

#define CFG_WRITE(v)                                                \
    for (int coefShift = sizeof(v); coefShift > 0; coefShift--)     \
    {                                                               \
        uint8_t new_v = (v >> (8 * (coefShift - 1))) & MASK_1_BYTE; \
        cfgF.write((char *)&(new_v), sizeof(char));                 \
    }

void createRVMcfgcode(ConfigObjects &cfgObj, const std::string &fileNameBin)
{

    uint8_t curbyte = 0;

    std::ofstream cfgF(fileNameBin, std::ios::binary);
    {
        ControlSection &ctrlSec = cfgObj.controlSection;
        DO_Section &doSec = cfgObj.doSection;
        APE_Section &apeSec = cfgObj.apeSection;

        /* Control Section */
        curbyte = (ctrlSec.LCF & MASK_LOW_BIT) << 7;
        curbyte |= (ctrlSec.NAF & MASK_LOW_BIT) << 6;
        CFG_WRITE(curbyte)
        CFG_WRITE(ctrlSec.Task_ID)
        CFG_WRITE(ctrlSec.RPI_version)
        CFG_WRITE(ctrlSec.Reference_ID)
        CFG_WRITE(ctrlSec.Implementation_version)
        CFG_WRITE(ctrlSec.Developer_ID)
        CFG_WRITE(ctrlSec.Creation_Date)

        /* DO Section */
        CFG_WRITE(doSec.N_DO)
        for (uint8_t i = 0; i < doSec.N_DO; i++)
        {
            CFG_WRITE(doSec.DOs[i].DO_ID);
            CFG_WRITE(doSec.DOs[i].size);
            CFG_WRITE(doSec.DOs[i].access_time);
            CFG_WRITE(doSec.DOs[i].length);
            for (uint8_t j = 0; j < doSec.DOs[i].length; j++)
            {
                CFG_WRITE(doSec.DOs[i].data[j]);
            }
            CFG_WRITE(doSec.ASFs[i].DO);
            CFG_WRITE(doSec.ASFs[i].N);
            for (uint8_t j = 0; j < doSec.ASFs[i].N; j++)
            {
                CFG_WRITE(doSec.ASFs[i].APE_KP[j].APE_number);
                CFG_WRITE(doSec.ASFs[i].APE_KP[j].port_number);
            }
        }

        /* APE Section */
        CFG_WRITE(apeSec.N_APE);
        for (uint16_t i = 0; i < apeSec.N_APE; i++)
        {
            CFG_WRITE(apeSec.APEs[i].APE_ID);
            CFG_WRITE(apeSec.APEs[i].op_code);
            curbyte = (apeSec.APEs[i].T & MASK_LOW_BIT) << 7;
            curbyte |= (apeSec.APEs[i].NN & MASK_LS_3_BIT) << 4;
            CFG_WRITE(curbyte);
            CFG_WRITE(apeSec.APEs[i].cost);
            CFG_WRITE(apeSec.APEs[i].time);

            // 2*1=2
            // xx000000
            // 16 ... 8   8  ... 0

            // 2*7=14
            // xxxxxxxx   xxxxxx00
            // 16 ... 8   8  ... 0
            // 6 4 2 0

            curbyte = 0;
            uint16_t cur2byte = 0;

            for (uint8_t j = 0; j < apeSec.APEs[i].NN; j++)
            {
                cur2byte |= (apeSec.APEs[i].access_type[j] & MASK_LS_2_BIT) << (16 - 2 * (j + 1));
            }

            if (apeSec.APEs[i].NN > 4)
            {
                CFG_WRITE(cur2byte);
            }
            else
            {
                curbyte = ((cur2byte >> 8) & MASK_1_BYTE);
                CFG_WRITE(curbyte);
            }
        }
    }
    cfgF.close();
}
