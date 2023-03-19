#include "fc_parser.hpp"

#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>

#include "common.hpp"

#define MASK_1_BYTE 0xff /* 1111 1111 */

#define FC_LOG(s) std::cout << s << std::endl

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
                    // create targetDir + "/" + "complex"
                    if (mkdir(targetComplexDir.c_str(), S_IRWXU | S_IRGRP | S_IXGRP) != 0)
                    {   
                        int e = errno;
                        if (e != EEXIST)
                        {
                            std::string errMsg = std::string("Cann't create directory") + std::string("'") + targetComplexDir + std::string("'");
                            throw std::runtime_error(errMsg.c_str());
                        }
                    }
                }
                flagFirstEnter = 1;
            }
            // create complex dir first

            fc_Parser parserComplex(settingBlock, targetComplexDir, true);
            parserComplex.parse(op.getSubpath());
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
fc_Parser::fc_Parser(fc_SettingBlock &settingBlock, const std::string &targetDir, bool noChangeTargetDirectory)
    : settingBlock(settingBlock), targetDir(targetDir), noChangeTargetDirectory(noChangeTargetDirectory) {}

void fc_Parser::parse(std::string progFileName)
{
    std::string fullProgramFilePath = settingBlock.getDirXML() + "/" + progFileName;
    std::string fullFilePathCC = targetDir + "/" + progFileName + ".bin";
    std::string mapFilePath = targetDir + "/" + progFileName + ".map";

    struct IrObjects irObjects = parserSWIR.parse(fullProgramFilePath);
    processComplexOperator(irObjects);
    converterIR.setIdMapFile(mapFilePath);
    ConfigObjects configObjects = converterIR.convert(irObjects);
    createRVMcfgcode(configObjects, fullFilePathCC);

    FC_LOG(GN << "> " << RT << "Parse '" << fullProgramFilePath << "' in '" << fullFilePathCC << "'");
    FC_LOG("----- IR objects");
    showIrObjects(irObjects);
    FC_LOG("----- CC objects");
    showConfigObjects(configObjects);
    FC_LOG("CC written in " << fullFilePathCC << std::endl);

    clearConfigObjects(configObjects);
}

void fc_Parser::parseComplex(std::string progFileName)
{
    std::string fullProgramFilePath = settingBlock.getDirXML() + "/" + progFileName;
    std::string fullFilePathCC = targetDir + "/" + progFileName + ".bin";
    std::string mapFilePath = targetDir + "/" + progFileName + ".map";

    struct IrObjects irObjects = parserSWIR.parse(fullProgramFilePath);
    processComplexOperator(irObjects);
    converterIR.setIdMapFile(mapFilePath);
    ConfigObjects configObjects = converterIR.convert(irObjects);
    createRVMcfgcode(configObjects, fullFilePathCC);

    FC_LOG(GN << "> " << RT << "Parse '" << fullProgramFilePath << "' in '" << fullFilePathCC << "'");
    FC_LOG("----- IR objects");
    showIrObjects(irObjects);
    FC_LOG("----- CC objects");
    showConfigObjects(configObjects);
    FC_LOG("CC written in " << fullFilePathCC << std::endl);

    clearConfigObjects(configObjects);
}
