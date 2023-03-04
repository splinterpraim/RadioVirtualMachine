/**
 * @file rvm_cfg_code_fetcher.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Config Code Fetcher
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "CU/rvm_cfg_code_fetcher.hpp"

#include <cstring>

#include "common.hpp"
#include "config_code_structure.hpp"
#include "rvm_program_memory.hpp"

/**
 * @brief Control section parsing stages
 */
enum CtrlSecParseStages
{
    LCF_NAF = 0,            /* Stage for parsing LCF & NAF fields */
    TASK_ID,                /* Stage for parsing Task_ID fields */
    RPI_VERSION,            /* Stage for parsing RPI_version fields */
    REFERENCE_ID,           /* Stage for parsing Reference_ID fields */
    IMPL_VERSION,           /* Stage for parsing Implementation_version fields */
    DEVELOPER_ID_FIRST,     /* Stage for parsing Developer_ID fields for first byte */
    DEVELOPER_ID_SECOND,    /* Stage for parsing Developer_ID fields for second byte */
    CREATION_DATE_FIRST,    /* Stage for parsing Creation_Date fields for first byte */
    CREATION_DATE_SECOND,   /* Stage for parsing Creation_Date fields for second byte */
};

/* Private */

int rvm_cfgCodeFetcher::parseCfgCode(uint8_t &cfgByte)
{
    int parseState = PARSE_STATE_IN_PROC;

    /* Start Parse */
    if (parseFlags.start == RESET_FLAG)
    {
        // todo: check bad_alloc
        clearConfigObjects(cfgCode);
        parseFlags.start = SET_FLAG;
    }
    /* End Parse */
    else if (parseFlags.end == SET_FLAG)
    {
        clearParseFlags();
        return PARSE_STATE_FINISH;
    }

    /* Control section parse */
    if (parseFlags.ctrlSec != SET_FLAG)
    {
        /* Chose parse stage */
        switch (parseFlags.stageCnt)
        {

        case CtrlSecParseStages::LCF_NAF: /* LCF, NAF */
        {
            cfgCode.controlSection.LCF = (cfgByte >> 7) & (MASK_LOW_BIT);
            cfgCode.controlSection.NAF = (cfgByte >> 6) & (MASK_LOW_BIT);
            break;
        }
        case CtrlSecParseStages::TASK_ID: /* Task_ID */
        {
            cfgCode.controlSection.Task_ID = cfgByte;
            break;
        }
        case CtrlSecParseStages::RPI_VERSION: /* RPI_version */
        {
            cfgCode.controlSection.RPI_version = cfgByte;
            break;
        }
        case CtrlSecParseStages::REFERENCE_ID: /* Reference_ID */
        {
            cfgCode.controlSection.Reference_ID = cfgByte;
            break;
        }
        case CtrlSecParseStages::IMPL_VERSION: /* Implementation_version */
        {
            cfgCode.controlSection.Implementation_version = cfgByte;
            break;
        }
        case CtrlSecParseStages::DEVELOPER_ID_FIRST: /* Developer_ID (first byte) */
        {
            cfgCode.controlSection.Developer_ID = cfgByte << 8;
            break;
        }
        case CtrlSecParseStages::DEVELOPER_ID_SECOND: /* Developer_ID (second byte) */
        {
            cfgCode.controlSection.Developer_ID |= cfgByte;
            break;
        }
        case CtrlSecParseStages::CREATION_DATE_FIRST: /* Creation_Date (first byte) */
        {
            cfgCode.controlSection.Creation_Date = cfgByte << 8;
            break;
        }
        case CtrlSecParseStages::CREATION_DATE_SECOND: /* Creation_Date (second byte) */
        {
            cfgCode.controlSection.Creation_Date |= cfgByte;
            parseFlags.ctrlSec = SET_FLAG;
            break;
        }

        default:
            break;
        }
        parseFlags.stageCnt++;
    }

    /* DO section parse */
    else if (parseFlags.doSec.end != SET_FLAG)
    {
        uint8_t index = parseFlags.doSec.Ncnt;

        /* Start DO section parse */
        if (parseFlags.doSec.start == RESET_FLAG)
        {
            /* N_DO */
            cfgCode.doSection.N_DO = cfgByte;

            /* Create DO_configs & ASF_configs */
            cfgCode.doSection.DOs = new DO_Config[cfgCode.doSection.N_DO];
            cfgCode.doSection.ASFs = new ASF_Config[cfgCode.doSection.N_DO];

            for (int i = 0; i < cfgCode.doSection.N_DO; ++i)
            {
                std::memset(&(cfgCode.doSection.DOs[i]), 0, sizeof(cfgCode.doSection.DOs[i]));
                std::memset(&(cfgCode.doSection.ASFs[i]), 0, sizeof(cfgCode.doSection.ASFs[i]));
            }
            parseFlags.doSec.start = SET_FLAG;
        }

        /* DO_config parse */
        else if (parseFlags.doSec.doCfg.start == RESET_FLAG)
        {
            DO_Config &curDO_cfg = cfgCode.doSection.DOs[index];

            /* DO_config.DO_ID parse */
            if (parseFlags.doSec.doCfg.DO_ID == RESET_FLAG)
            {
                curDO_cfg.DO_ID = cfgByte;
                parseFlags.doSec.doCfg.DO_ID = SET_FLAG;
            }

            /* DO_config.size parse 4 byte */
            else if (parseFlags.doSec.doCfg.size == RESET_FLAG)
            {
                uint8_t shift = 8 * (sizeof(curDO_cfg.size) - (parseFlags.doSec.doCfg.byteCnt + 1));
                curDO_cfg.size |= cfgByte << shift;
                parseFlags.doSec.doCfg.byteCnt++;
                if (shift == 0)
                {
                    parseFlags.doSec.doCfg.byteCnt = RESET_FLAG;
                    parseFlags.doSec.doCfg.size = SET_FLAG;
                }
            }

            /* DO_config.access_time parse 4 byte */
            else if (parseFlags.doSec.doCfg.access_time == RESET_FLAG)
            {
                uint8_t shift = 8 * (sizeof(curDO_cfg.size) - (parseFlags.doSec.doCfg.byteCnt + 1));
                curDO_cfg.access_time |= cfgByte << shift;
                parseFlags.doSec.doCfg.byteCnt++;
                if (shift == 0)
                {
                    parseFlags.doSec.doCfg.byteCnt = RESET_FLAG;
                    parseFlags.doSec.doCfg.access_time = SET_FLAG;
                }
            }

            /* DO_config.length parse 1 byte */
            else if (parseFlags.doSec.doCfg.length == RESET_FLAG)
            {
                curDO_cfg.length = cfgByte;
                parseFlags.doSec.doCfg.length = SET_FLAG;
                parseFlags.doSec.doCfg.byteCnt = RESET_FLAG;

                if (curDO_cfg.length != 0)
                {
                    /* Allocate data */
                    curDO_cfg.data = new uint8_t[curDO_cfg.length];
                    for (size_t i = 0; i < curDO_cfg.length; ++i)
                    {
                        curDO_cfg.data[i] = 0;
                    }
                }
                else
                {
                    parseFlags.doSec.doCfg.data = SET_FLAG;
                    parseFlags.doSec.doCfg.start = SET_FLAG;
                }
            }

            /* DO_config.data parse */
            else if (parseFlags.doSec.doCfg.data == RESET_FLAG)
            {
                curDO_cfg.data[parseFlags.doSec.doCfg.byteCnt] = cfgByte;
                parseFlags.doSec.doCfg.byteCnt++;
                if (parseFlags.doSec.doCfg.byteCnt >= curDO_cfg.length)
                {
                    parseFlags.doSec.doCfg.data = SET_FLAG;
                    parseFlags.doSec.doCfg.start = SET_FLAG;
                }
            }
        }

        /* ASF_config parse */
        else if (parseFlags.doSec.asfCfg.start == RESET_FLAG)
        {
            ASF_Config &curASF_cfg = cfgCode.doSection.ASFs[index];

            /* ASF_config.DO parse */
            if (parseFlags.doSec.asfCfg.DO == RESET_FLAG)
            {
                curASF_cfg.DO = cfgByte;
                parseFlags.doSec.asfCfg.DO = SET_FLAG;
            }

            /* ASF_config.N parse */
            else if (parseFlags.doSec.asfCfg.N == RESET_FLAG)
            {
                curASF_cfg.N = cfgByte;
                parseFlags.doSec.asfCfg.N = SET_FLAG;

                /* Allocate APE_KP */
                curASF_cfg.APE_KP = new ASF_variable_part[curASF_cfg.N];
                for (size_t i = 0; i < curASF_cfg.N; ++i)
                {
                    std::memset(&(curASF_cfg.APE_KP[i]), 0, sizeof(curASF_cfg.APE_KP[i]));
                }
            }

            /* ASF_config.APE_KP parse */
            else if (parseFlags.doSec.asfCfg.APE_KP == RESET_FLAG)
            {
                if (parseFlags.doSec.asfCfg.byteCnt == 0)
                {
                    curASF_cfg.APE_KP[parseFlags.doSec.asfCfg.cntAPE_KP].APE_number = cfgByte;
                    parseFlags.doSec.asfCfg.byteCnt++;
                }
                else if (parseFlags.doSec.asfCfg.byteCnt == 1)
                {
                    curASF_cfg.APE_KP[parseFlags.doSec.asfCfg.cntAPE_KP].port_number = cfgByte;

                    parseFlags.doSec.asfCfg.byteCnt = RESET_FLAG;
                    parseFlags.doSec.asfCfg.cntAPE_KP++;
                    if (parseFlags.doSec.asfCfg.cntAPE_KP >= curASF_cfg.N)
                    {
                        parseFlags.doSec.asfCfg.APE_KP = SET_FLAG;
                        parseFlags.doSec.asfCfg.start = SET_FLAG;
                    }
                }
            }
        }

        /* Check end DO section parse */
        if (parseFlags.doSec.asfCfg.start == SET_FLAG)
        {
            parseFlags.doSec.Ncnt++;
            /* Check End DO section parse */
            if (parseFlags.doSec.Ncnt >= cfgCode.doSection.N_DO)
            {
                parseFlags.doSec.end = SET_FLAG;
            }
            /* Clear flags for parse next DO_Config and ASF_Config */
            else
            {
                parseFlags.doSec.doCfg.start = RESET_FLAG;
                parseFlags.doSec.doCfg.DO_ID = RESET_FLAG;
                parseFlags.doSec.doCfg.size = RESET_FLAG;
                parseFlags.doSec.doCfg.access_time = RESET_FLAG;
                parseFlags.doSec.doCfg.length = RESET_FLAG;
                parseFlags.doSec.doCfg.data = RESET_FLAG;
                parseFlags.doSec.doCfg.byteCnt = RESET_FLAG;

                parseFlags.doSec.asfCfg.start = RESET_FLAG;
                parseFlags.doSec.asfCfg.DO = RESET_FLAG;
                parseFlags.doSec.asfCfg.N = RESET_FLAG;
                parseFlags.doSec.asfCfg.APE_KP = RESET_FLAG;
                parseFlags.doSec.asfCfg.cntAPE_KP = RESET_FLAG;
                parseFlags.doSec.asfCfg.byteCnt = RESET_FLAG;
            }
        }
    }

    /* APE section parse */
    else if (parseFlags.apeSec.end != SET_FLAG)
    {
        uint8_t index = parseFlags.apeSec.Ncnt;

        /* Start APE section parse */
        if (parseFlags.apeSec.start == RESET_FLAG)
        {
            /* N_APE */
            uint8_t shift = 8 * (sizeof(cfgCode.apeSection.N_APE) - (parseFlags.apeSec.byteCnt + 1));
            cfgCode.apeSection.N_APE |= cfgByte << shift;

            parseFlags.apeSec.byteCnt++;
            if (shift == 0)
            {
                /* Create APE_configs */
                cfgCode.apeSection.APEs = new APE_Config[cfgCode.apeSection.N_APE];
                for (int i = 0; i < cfgCode.apeSection.N_APE; ++i)
                {
                    std::memset(&(cfgCode.apeSection.APEs[i]), 0, sizeof(cfgCode.apeSection.APEs[i]));
                }
                parseFlags.apeSec.start = SET_FLAG;
            }
        }

        /* APE_Config parse */
        else if (parseFlags.apeSec.apeCfg.start == RESET_FLAG)
        {
            APE_Config &curAPE_cfg = cfgCode.apeSection.APEs[index];

            /* APE_ID */
            if (parseFlags.apeSec.apeCfg.APE_ID == RESET_FLAG)
            {
                uint8_t shift = 8 * (sizeof(curAPE_cfg.APE_ID) - (parseFlags.apeSec.apeCfg.byteCnt + 1));
                curAPE_cfg.APE_ID |= cfgByte << shift;

                parseFlags.apeSec.apeCfg.byteCnt++;
                if (shift == 0)
                {
                    parseFlags.apeSec.apeCfg.byteCnt = RESET_FLAG;
                    parseFlags.apeSec.apeCfg.APE_ID = SET_FLAG;
                }
            }

            /* op_code */
            else if(parseFlags.apeSec.apeCfg.op_code == RESET_FLAG)
            {
                /* op_code */
                uint8_t shift = 8 * (sizeof(curAPE_cfg.op_code) - (parseFlags.apeSec.apeCfg.byteCnt + 1));
                curAPE_cfg.op_code |= cfgByte << shift;

                parseFlags.apeSec.apeCfg.byteCnt++;
                if (shift == 0)
                {
                    parseFlags.apeSec.apeCfg.byteCnt = RESET_FLAG;
                    parseFlags.apeSec.apeCfg.op_code = SET_FLAG;
                }
            }

            /* T & NN */
            else if(parseFlags.apeSec.apeCfg.T == RESET_FLAG)
            {
                curAPE_cfg.T = (cfgByte >> 7) & MASK_LOW_BIT;
                curAPE_cfg.NN = (cfgByte >> 4) & MASK_LS_3_BIT;

                curAPE_cfg.access_type = new uint8_t[curAPE_cfg.NN]; 
                for (size_t i = 0; i < curAPE_cfg.NN; ++i)
                {
                    curAPE_cfg.access_type[0] = 0;
                }
                
                parseFlags.apeSec.apeCfg.T = SET_FLAG;
            }

            /* cost */
            else if(parseFlags.apeSec.apeCfg.cost == RESET_FLAG)
            {
                /* cost */
                uint8_t shift = 8 * (sizeof(curAPE_cfg.cost) - (parseFlags.apeSec.apeCfg.byteCnt + 1));
                curAPE_cfg.cost |= cfgByte << shift;

                parseFlags.apeSec.apeCfg.byteCnt++;
                if (shift == 0)
                {
                    parseFlags.apeSec.apeCfg.byteCnt = RESET_FLAG;
                    parseFlags.apeSec.apeCfg.cost = SET_FLAG;
                }
            }

            /* time */
            else if(parseFlags.apeSec.apeCfg.time == RESET_FLAG)
            {
                /* cost */
                uint8_t shift = 8 * (sizeof(curAPE_cfg.time) - (parseFlags.apeSec.apeCfg.byteCnt + 1));
                curAPE_cfg.time |= cfgByte << shift;

                parseFlags.apeSec.apeCfg.byteCnt++;
                if (shift == 0)
                {
                    parseFlags.apeSec.apeCfg.byteCnt = RESET_FLAG;
                    parseFlags.apeSec.apeCfg.time = SET_FLAG;
                }
            }

            /* access_type */
            else if(parseFlags.apeSec.apeCfg.access_type == RESET_FLAG)
            {
                for(int shift = 6; shift > 0; shift-=2)
                {
                    curAPE_cfg.access_type[parseFlags.apeSec.apeCfg.byteCnt] = (cfgByte >> shift) & MASK_LS_2_BIT;
                    parseFlags.apeSec.apeCfg.byteCnt++;
                    if (parseFlags.apeSec.apeCfg.byteCnt >= curAPE_cfg.NN)
                    {
                        parseFlags.apeSec.apeCfg.byteCnt = RESET_FLAG;
                        parseFlags.apeSec.apeCfg.access_type = SET_FLAG;
                        parseFlags.apeSec.apeCfg.start = SET_FLAG;
                        break;
                    }
                }


              
            // parseState = PARSE_STATE_FINISH; //! THIS
            }
        }

        /* Check end DO section parse */
        if (parseFlags.apeSec.apeCfg.start == SET_FLAG)
        {
            parseFlags.apeSec.Ncnt++;
            /* Check End DO section parse */
            if (parseFlags.apeSec.Ncnt >= cfgCode.apeSection.N_APE)
            {
                parseFlags.apeSec.end = SET_FLAG;

            }
            /* Clear flags for parse next DO_Config and ASF_Config */
            else
            {
                parseFlags.apeSec.byteCnt = RESET_FLAG;
                parseFlags.apeSec.apeCfg.start = RESET_FLAG;
                parseFlags.apeSec.apeCfg.APE_ID = RESET_FLAG;
                parseFlags.apeSec.apeCfg.op_code = RESET_FLAG;
                parseFlags.apeSec.apeCfg.T = RESET_FLAG;
                parseFlags.apeSec.apeCfg.NN = RESET_FLAG;
                parseFlags.apeSec.apeCfg.cost = RESET_FLAG;
                parseFlags.apeSec.apeCfg.time = RESET_FLAG;
                parseFlags.apeSec.apeCfg.access_type = RESET_FLAG;
                parseFlags.apeSec.apeCfg.byteCnt = RESET_FLAG;
            }
        }
    }

    if (parseFlags.apeSec.end == SET_FLAG)
    {
        parseState = PARSE_STATE_FINISH; //! THIS
    }
    return parseState;
}

void rvm_cfgCodeFetcher::clearParseFlags()
{
    std::memset((void*)&parseFlags, 0, sizeof(ParseCfgCodeFlags_s));
    parseFlags.start = RESET_FLAG;
    parseFlags.end = RESET_FLAG;
    parseFlags.stageCnt = RESET_FLAG;
    parseFlags.ctrlSec = RESET_FLAG;

    /* DO Section */
    parseFlags.doSec.start = RESET_FLAG;
    parseFlags.doSec.end = RESET_FLAG;
    parseFlags.doSec.Ncnt = RESET_FLAG;

    /* DO config */
    parseFlags.doSec.doCfg.start = RESET_FLAG;
    parseFlags.doSec.doCfg.DO_ID = RESET_FLAG;
    parseFlags.doSec.doCfg.size = RESET_FLAG;
    parseFlags.doSec.doCfg.access_time = RESET_FLAG;
    parseFlags.doSec.doCfg.length = RESET_FLAG;
    parseFlags.doSec.doCfg.data = RESET_FLAG;
    parseFlags.doSec.doCfg.byteCnt = RESET_FLAG;

    /* ASF config */
    parseFlags.doSec.asfCfg.start = RESET_FLAG;
    parseFlags.doSec.asfCfg.DO = RESET_FLAG;
    parseFlags.doSec.asfCfg.N = RESET_FLAG;
    parseFlags.doSec.asfCfg.APE_KP = RESET_FLAG;
    parseFlags.doSec.asfCfg.cntAPE_KP = RESET_FLAG;
    parseFlags.doSec.asfCfg.byteCnt = RESET_FLAG;

    /* APE Section */
    parseFlags.apeSec.start = RESET_FLAG;
    parseFlags.apeSec.end = RESET_FLAG;
    parseFlags.apeSec.Ncnt = RESET_FLAG;
    parseFlags.apeSec.byteCnt = RESET_FLAG;
}

/* Public */

rvm_cfgCodeFetcher::rvm_cfgCodeFetcher()
{
    initConfigObjects(cfgCode);
}

rvm_cfgCodeFetcher::~rvm_cfgCodeFetcher()
{
    clearConfigObjects(cfgCode);
}

void rvm_cfgCodeFetcher::associate(rvm_ProgramMemory &programMemory)
{
    this->programMemory = &programMemory;
}

ConfigObjects& rvm_cfgCodeFetcher::fetch(uint64_t cfgAddr)
{
    uint64_t progMemSize = programMemory->getSize();

    /* Check on out of memory */
    if (cfgAddr >= progMemSize)
    {
        throw std::runtime_error(RVM_ERR_STR("Fetch is failed, because the address is out of memory"));
    }

    uint64_t addr = cfgAddr;
    uint8_t byte = 0;

    /* Loop for parsing config code */
    byte = programMemory->get(addr);
    lAddress = addr;
    while (parseCfgCode(byte) != PARSE_STATE_FINISH)
    {
        addr++;
        if (addr >= progMemSize)
        {
            break;
        }
        byte = programMemory->get(addr);
        lAddress = addr;
        
    }
    clearParseFlags();

    return cfgCode;
}

uint64_t rvm_cfgCodeFetcher::getLastAddress()
{
    return lAddress;
}

