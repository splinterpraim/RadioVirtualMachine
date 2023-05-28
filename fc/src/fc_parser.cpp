/**
 * @file fc_parser.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Implementation of FC Parser.
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "fc_parser.hpp"

#include <fstream>
#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>

#include "fc_config.hpp"
#include "common.hpp"
#include "fc_logger.hpp"
#include "system_func.hpp"


#define MASK_1_BYTE 0xff /* 1111 1111 */


#define CFG_WRITE(v)                                                \
    for (int coefShift = sizeof(v); coefShift > 0; coefShift--)     \
    {                                                               \
        uint8_t new_v = (v >> (8 * (coefShift - 1))) & MASK_1_BYTE; \
        cfgF.write((char *)&(new_v), sizeof(char));                 \
    }

/* Private */

void fc_Parser::processComplexOperator(IrObjects &irObj)
{
    bool flagFirstEnter = 0;
    std::string targetComplexDir;
    for (IrOperator &op : irObj.operators)
    {
        if (op.getType().compare("Complex") == 0)
        {
            if (flagFirstEnter == 0)
            {
                if (noChangeTargetDirectory == true)
                {
                    targetComplexDir = targetDir;
                }
                else
                {
                    targetComplexDir = targetDir + "/" + "complex";
                    createDir(targetComplexDir);
                }
                flagFirstEnter = 1;
            }

            fc_Parser parserComplex(targetComplexDir, true);
            parserComplex.setSettingBlock(*settingBlock);
            parserComplex.setProgramName(op.getSubname());
            parserComplex.loadProgramFromStr(op.getSubprogram());
            parserComplex.parse();
        }
    }
}

void fc_Parser::createRVMcfgcode(ConfigObjects &cfgObj, const std::string &fileNameBin)
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
            CFG_WRITE(doSec.DOs[i].external);
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




/* Public */

fc_Parser::fc_Parser()
{

}

fc_Parser::fc_Parser( const std::string &targetDir, bool noChangeTargetDirectory)
    : targetDir(targetDir), noChangeTargetDirectory(noChangeTargetDirectory) {}

fc_Parser::fc_Parser(const fc_Parser& obj)
{
    this->settingBlock = obj.settingBlock;
    this->inputProgramFilePath = obj.inputProgramFilePath;
    this->targetDir = obj.targetDir;
    this->programName = obj.programName; 
    this->IrObj = obj.IrObj;
    this->parserSWIR.setSettingBlock(obj.parserSWIR.getSettingBlock());
    this->converterIR.setIdMapFile(obj.converterIR.getIdMapFile());
    this->noChangeTargetDirectory = obj.noChangeTargetDirectory;
    this->programDoc.reset(obj.programDoc);
}

void fc_Parser::parse()
{
    std::string fullFilePathCC = targetDir + "/" + programName + ".bin";
    std::string mapFilePath = targetDir + "/" + programName + ".map";

    struct IrObjects irObjects = parserSWIR.parse(programDoc);
    processComplexOperator(irObjects);
    converterIR.setIdMapFile(mapFilePath);
    ConfigObjects configObjects = converterIR.convert(irObjects);
    createRVMcfgcode(configObjects, fullFilePathCC);


#ifdef FC_LOG_ENABLE
    FC_LOG("%s>%s Parse program '%s'\n", GN, RT, programName.c_str());
    FC_LOG("----- SWIR file\n");
    showDoc();
    FC_LOG("----- IR objects\n");
    showIrObjects(irObjects);
    FC_LOG("----- CC objects\n");
    showConfigObjects(configObjects);
    FC_LOG("\nCC written in %s\n", fullFilePathCC.c_str());
#endif
    clearConfigObjects(configObjects);
}

void fc_Parser::setSettingBlock(fc_SettingBlock& settingBlock)
{
    this->settingBlock = &settingBlock;
    parserSWIR.setSettingBlock(settingBlock);
}

void fc_Parser::setTargetDir(const std::string& targetDir)
{
    this->targetDir = targetDir;
}

void fc_Parser::setProgramName(const std::string& programName)
{
    this->programName = programName;
}



void fc_Parser::loadProgramFromFile(const std::string& progPath)
{
    parserSWIR.loadProgramFromFile__(progPath, programDoc);
}

void fc_Parser::loadProgramFromNode(const pugi::xml_node &programNode)
{
    parserSWIR.loadProgramFromNode__(programNode, programDoc);
}
void fc_Parser::loadProgramFromStr(const std::string& progStr)
{
    parserSWIR.loadProgramFromStr__(progStr, programDoc);
}

void fc_Parser::showDoc()
{
    programDoc.print(std::cout);
}
