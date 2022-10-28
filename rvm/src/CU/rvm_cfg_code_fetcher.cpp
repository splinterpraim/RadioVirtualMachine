#include "CU/rvm_cfg_code_fetcher.hpp"
#include "rvm_program_mem.hpp"
#include "common.hpp"

/* PARSE STATES */
#define PARSE_STATE_IN_PROC 1
#define PARSE_STATE_FINISH 0

/* PARSE STAGES */
enum parseStage
{
    ctrlSec0 = 0,
    ctrlSec1,
    ctrlSec2,
    ctrlSec3,
    ctrlSec4,
    ctrlSec5,
    ctrlSec6,
    ctrlSec7,
    ctrlSec8,
    doSec0,
    doSec1
};

enum parseStageDoSec
{
    s0 = 0,
    s1,
    s2,
    s3,
    s4,
    s5,
    s6,
    s7,
    s8,
    s9,
    s10
};

/* Masks */
#define MASK_ONE 0x01        /* 0000 0001 */
#define MASK_SIX_BITS_R 0x3f /* 0011 1111 */
#define MASK_TWO_BITS_R 0x03 /* 0000 0011 */

#define MASK_TWO_BITS_L 0xc0 /* 1100 0000 */

extern rvm_ProgramMemory progMem;




uint8_t binGetFirstBit(uint8_t byte)
{
    return (byte >> 7) & (MASK_ONE);
}

uint8_t binGetSecondBit(uint8_t byte)
{
    return (byte >> 6) & (MASK_ONE);
}

rvm_cfgCodeFetcher::rvm_cfgCodeFetcher()
{
}

rvm_cfgCodeFetcher::~rvm_cfgCodeFetcher()
{
}

void rvm_cfgCodeFetcher::associate(rvm_ProgramMemory &programMemory)
{
    this->programMemory = &programMemory;
}

// todo: rename progMem on programMemory

ConfigObjects * rvm_cfgCodeFetcher::fetch(uint64_t cfgAddr)
{
    uint64_t progMemSize = progMem.getSize();

    /* Check on out of memory */
    if (cfgAddr >= progMemSize)
    {
        throw std::runtime_error(RVM_ERR_STR("Fetch is failed, because the address is out of memory"));
    }

    uint64_t addr = cfgAddr;
    uint8_t byte = 0;

    /* Loop for parsing config code */
    byte = progMem.get(addr++);
    while (parseCfgCode(byte) != PARSE_STATE_FINISH)
    {
        byte = progMem.get(addr++);
        if (addr >= progMemSize)
        {
            break;
        }
    }

    
    return cfgCode;
}

void rvm_cfgCodeFetcher::showCfgCode()
{
    if (cfgCode != nullptr)
    {
        std::string space2 = "  ";
        std::string space4 = "    ";
        /* Show controlSection */

        std::cout << "Control Section:" << std::endl;
        std::cout << space2 << "LCF = " << (unsigned int)cfgCode->controlSection.LCF << std::endl;
        std::cout << space2 << "NAF = " << (unsigned int)cfgCode->controlSection.NAF << std::endl;
        std::cout << space2 << "Task_ID = " << (unsigned int)cfgCode->controlSection.Task_ID << std::endl;
        std::cout << space2 << "RPI_version = " << (unsigned int)cfgCode->controlSection.RPI_version << std::endl;
        std::cout << space2 << "Referenc_ID = " << (unsigned int)cfgCode->controlSection.Reference_ID << std::endl;
        std::cout << space2 << "Implementation_version = " << (unsigned int)cfgCode->controlSection.Implementation_version << std::endl;
        std::cout << space2 << "Developer_ID = " << (unsigned int)cfgCode->controlSection.Developer_ID << std::endl;
        std::cout << space2 << "Creation_Date = " << (unsigned int)cfgCode->controlSection.Creation_Date << std::endl;
        std::cout << std::endl;

        std::cout << "DO Section:" << std::endl;
        std::cout << space2 << "N_DO = " << (unsigned int)cfgCode->doSection.N_DO << std::endl;
        std::cout << space2 << "DO_config:" << std::endl;
        for (int i = 0; i < cfgCode->doSection.N_DO; ++i)
        {
            std::cout << space4 << "DO_ID = " << (unsigned int) cfgCode->doSection.DOs[i].DO_ID << ", ";
            std::cout << space4 << "size = " << cfgCode->doSection.DOs[i].size << ", ";
            std::cout << std::endl;
        }
        // showDoSection(cfgCode->doSection);
    }
}

/* private */
int rvm_cfgCodeFetcher::parseCfgCode(uint8_t &cfgByte)
{
    int parseState = PARSE_STATE_IN_PROC;
    /* Start Parse */
    if (parseFlags.start == RESET_FLAG)
    {
        cfgCode = new ConfigObjects[1];
        // todo: check bad_alloc
        initConfigObjects(*cfgCode);
        parseFlags.start = SET_FLAG;
    }
    /* End Parse */
    else if (parseFlags.end == SET_FLAG)
    {
        clearParseFlags();
        return 0;
    }

    /* Control section parse */
    if (parseFlags.ctrlSec != SET_FLAG)
    {
        /* Parse */
        switch (parseFlags.stageCnt)
        {

        case parseStage::ctrlSec0:
        {
            /* Fill Control Section
                full -> LCF (+1 bit [1/1]), NAF (+1 bit [1/1])
                partially -> Task_ID (+6 bits [6/8]) */
            cfgCode->controlSection.LCF = (cfgByte >> 7) & (MASK_LOW_BIT);
            cfgCode->controlSection.NAF = (cfgByte >> 6) & (MASK_LOW_BIT); 
            break;
        }
        case parseStage::ctrlSec1:
        {
            /* Fill Control Section
                full -> Task_ID (+2 bits [8/8])
                partially -> RPI_version (+6 bits [6/8]) */
            cfgCode->controlSection.Task_ID = cfgByte;
            break;
        }
        case parseStage::ctrlSec2:
        {
            /* Fill Control Section
                full -> RPI_version (+2 bits [8/8])
                partially -> Reference_ID (+6 bits [6/8]) */
            cfgCode->controlSection.RPI_version = cfgByte;
            break;
        }
        case parseStage::ctrlSec3:
        {
            /* Fill Control Section
                full -> Reference_ID (+2 bits [8/8])
                partially -> Implementation_version (+6 bits [6/8]) */
            cfgCode->controlSection.Reference_ID = cfgByte;
            break;
        }
        case parseStage::ctrlSec4:
        {
            /* Fill Control Section
                full -> Implementation_version (+2 bits [8/8])
                partially -> Developer_ID (+6 bits [6/16]) */
            cfgCode->controlSection.Implementation_version = cfgByte;
            break;
        }
        case parseStage::ctrlSec5: /* THIS */
        {
            /* Fill Control Section
                partially -> Developer_ID (+8 bits [14/16]) */
            cfgCode->controlSection.Developer_ID |= cfgByte << 2;
            break;
        }
        case parseStage::ctrlSec6:
        {
            /* Fill Control Section
                full -> Developer_ID (+2 bits [16/16])
                partially -> Creation_date (+6 bits [6/16]) */

            cfgCode->controlSection.Developer_ID |= ((cfgByte >> 6) & MASK_TWO_BITS_R);
            cfgCode->controlSection.Creation_Date = (cfgByte & MASK_SIX_BITS_R) << 10;
            break;
        }
        case parseStage::ctrlSec7:
        {
            /* Fill Control Section
                partially -> Creation_date (+8 bits [14/16]) */
            cfgCode->controlSection.Creation_Date |= cfgByte << 2;
            break;
        }
        case parseStage::ctrlSec8:
        {
            /* Fill Control Section
                full -> Creation_date (+2 bits [16/16])
                partially -> doSection.N_DO (+6 bits [6/8]) */
            cfgCode->controlSection.Creation_Date |= ((cfgByte >> 6) & MASK_TWO_BITS_R);
            cfgCode->doSection.N_DO = (cfgByte & MASK_SIX_BITS_R) << 2;
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
        
            /* Start DO section parse */
            if (parseFlags.doSec.start == RESET_FLAG)
            {
                /* Fill DO Section
                    full -> N_DO (+2 bits [8/8]) */
                cfgCode->doSection.N_DO |= ((cfgByte >> 6) & MASK_TWO_BITS_R);

                /* Create DO_configs & ASF_configs */
                cfgCode->doSection.DOs = new DO_Config[cfgCode->doSection.N_DO];
                cfgCode->doSection.ASFs = new ASF_Config[cfgCode->doSection.N_DO];
                parseFlags.doSec.start = SET_FLAG;
            }


            /* DO_config parse */
            if (parseFlags.doSec.doCfg.start == RESET_FLAG)
            {
                uint8_t index = parseFlags.doSec.Ncnt;

                /* DO_config.DO_ID parse 1 byte */
                if(parseFlags.doSec.doCfg.DO_ID == RESET_FLAG)
                {
                    if ( parseFlags.doSec.doCfg.stageCnt ==  parseStageDoSec::s0 )
                    {
                        cfgCode->doSection.DOs[index].DO_ID = (cfgByte & MASK_SIX_BITS_R) << 2; /* -> DO_ID (+6 bits [6/8]) */
                        parseFlags.doSec.doCfg.stageCnt++;
                    }
                    else 
                    {
                        cfgCode->doSection.DOs[index].DO_ID |= ((cfgByte >> 6) & MASK_TWO_BITS_R); /* -> DO_ID (+2 bits [8/8]) */
                        cfgCode->doSection.DOs[index].size = (cfgByte & MASK_SIX_BITS_R) << (32 - 6); /* -> size (+6 bits [6/32]) */
                        
                        parseFlags.doSec.doCfg.DO_ID = SET_FLAG;
                        parseFlags.doSec.doCfg.stageCnt = RESET_FLAG;
                    }
                }

                /* DO_config.size parse 4 byte */
                else if (parseFlags.doSec.doCfg.size == RESET_FLAG)
                {
                    /* Add first/second bytes to doSection.DOs[index].size  */
                    if ( parseFlags.doSec.doCfg.stageCnt ==  parseStageDoSec::s0 )
                    {
                        cfgCode->doSection.DOs[index].size |= cfgByte << (26 - 8); /* -> size (+8 bits [14/32]) */
                        parseFlags.doSec.doCfg.stageCnt++;
                    }
                    /* Add third bytes to doSection.DOs[index].size  */
                    else if ( parseFlags.doSec.doCfg.stageCnt ==  parseStageDoSec::s1 )
                    {
                        cfgCode->doSection.DOs[index].size |= cfgByte << (18 - 8);  /* -> size (+8 bits [22/32]) */
                        parseFlags.doSec.doCfg.stageCnt++;
                    }
                    /* Add fourth bytes to doSection.DOs[index].size  */
                    else if ( parseFlags.doSec.doCfg.stageCnt ==  parseStageDoSec::s2 )
                    {
                        cfgCode->doSection.DOs[index].size |= cfgByte << (10 - 8); /* -> size (+8 bits [30/32]) */
                        parseFlags.doSec.doCfg.stageCnt++;
                    }
                    /* Add 5 bytes to doSection.DOs[index].size  */
                    else if ( parseFlags.doSec.doCfg.stageCnt ==  parseStageDoSec::s3 )
                    {
                        cfgCode->doSection.DOs[index].size |= ((cfgByte >> 6) & MASK_TWO_BITS_R); /* -> size (+2 bits [32/32]) */
                        cfgCode->doSection.DOs[index].access_time = (cfgByte & MASK_SIX_BITS_R) << (32 - 6); /* -> size (+6 bits [6/32]) */
                        

                        parseFlags.doSec.doCfg.stageCnt = RESET_FLAG;
                        parseFlags.doSec.doCfg.size  = SET_FLAG;
                        
                    }


                }

                /* DO_config.access_time parse 4 byte */
                else if (parseFlags.doSec.doCfg.access_time == RESET_FLAG)
                {
                    /* Add first/second bytes to doSection.DOs[index].access_time  */
                    if ( parseFlags.doSec.doCfg.stageCnt ==  parseStageDoSec::s0 )
                    {
                        cfgCode->doSection.DOs[index].size |= cfgByte << (26 - 8); /* -> size (+8 bits [14/32]) */
                        parseFlags.doSec.doCfg.stageCnt++;
                    }
                    parseFlags.doSec.doCfg.start = SET_FLAG;
                }
                // size 4 byte
                // access time 4 byte
                // len 1 byte
                // data % byte

                /* 
                uint8_t DO_ID;          //* Identificator of data
                uint32_t size;          //* Maximum data size in bytes
                uint32_t access_time;   //* Access time in ns
                uint8_t length;         //* Current size of data (max 256 bytes of data)
                uint8_t *data;          //* Pointer to data
                 */
            }

            /* ASF_config parse */
            // else if(parseFlags.doSec.asfCfg == RESET_FLAG)
            // {
            //     parseFlags.doSec.Ncnt++;
            //     /* Check End DO section parse */
            //     if (parseFlags.doSec.Ncnt >= cfgCode->doSection.N_DO)
            //     {
            //         //end doSec parse
            //         parseFlags.doSec.end = SET_FLAG;
            //         parseState = PARSE_STATE_FINISH; //! THIS

            //     }
            // }
                
            

            

            
            

    }

    return parseState;
}

void rvm_cfgCodeFetcher::clearParseFlags()
{
    parseFlags.start = RESET_FLAG;
    parseFlags.end = RESET_FLAG;
    parseFlags.stageCnt = RESET_FLAG;
    parseFlags.ctrlSec = RESET_FLAG;
    parseFlags.doSec.start = RESET_FLAG;
    parseFlags.doSec.end = RESET_FLAG;
    parseFlags.doSec.Ncnt = RESET_FLAG;

    parseFlags.doSec.doCfg.start = RESET_FLAG;
    parseFlags.doSec.doCfg.DO_ID = RESET_FLAG;
    parseFlags.doSec.doCfg.size = RESET_FLAG;
    parseFlags.doSec.doCfg.access_time = RESET_FLAG;
    parseFlags.doSec.doCfg.length = RESET_FLAG;
    parseFlags.doSec.doCfg.data = RESET_FLAG;

    parseFlags.doSec.asfCfg = RESET_FLAG;
}
