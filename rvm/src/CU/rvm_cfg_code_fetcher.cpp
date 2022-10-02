#include "CU/rvm_cfg_code_fetcher.hpp"
#include "rvm_program_mem.hpp"
#include "common.hpp"

/* PARSE STATES */
#define PARSE_STATE_IN_PROC 1
#define PARSE_STATE_FINISH 0

/* PARSE STAGES */
#define PARSE_STAGE_ZERO 0
#define PARSE_STAGE_ONE 1
#define PARSE_STAGE_TWO 2
#define PARSE_STAGE_THREE 3
#define PARSE_STAGE_FOUR 4

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

int rvm_cfgCodeFetcher::fetch(uint64_t cfgAddr)
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
    return 0;
}

void rvm_cfgCodeFetcher::showCfgCode()
{
    if (cfgCode != nullptr)
    {
        std::string space2 = "  ";
        /* Show controlSection */

        std::cout << "Control Section:" << std::endl;
        std::cout << space2 << "LCF = " << (int) cfgCode->controlSection.LCF << std::endl;
        std::cout << space2 << "NAF = " << (int) cfgCode->controlSection.NAF << std::endl;
        std::cout << space2 << "Task_ID = " << (int) cfgCode->controlSection.Task_ID << std::endl;
        std::cout << space2 << "RPI_version = " << (int) cfgCode->controlSection.RPI_version << std::endl;
        std::cout << space2 << "Implementation_version = " << (int) cfgCode->controlSection.Implementation_version << std::endl;
    }
}


/* private */
int rvm_cfgCodeFetcher::parseCfgCode(uint8_t &cfgBin)
{
    int parseState = PARSE_STATE_IN_PROC;
    /* Start Parse */
    if (parseFlags.start == RESET_FLAG)
    {
        cfgCode = new ConfigObjects[1];
        // clear cfgCode
        parseFlags.start = SET_FLAG;
    }
    /* End Parse */
    else if (parseFlags.end == SET_FLAG)
    {
        clearParseFlags();
        return 0;
    }


    /* Parse */
    switch (parseFlags.stageCnt)
    {

    case PARSE_STAGE_ZERO:
    {
        /* Fill Control Section
            full -> LCF (1 bit), NAF (1 bit)
            partially -> Task_ID (6 bits) */
        cfgCode->controlSection.LCF = binGetFirstBit(cfgBin);
        cfgCode->controlSection.NAF = binGetSecondBit(cfgBin);
        cfgCode->controlSection.Task_ID = (cfgBin & MASK_SIX_BITS_R) << 2; /* Get six bits from the right and shift on start left position */
        break;
    }

    case PARSE_STAGE_ONE:
    {
        /* Fill Control Section
            full -> Task_ID (2 bits)
            partially -> RPI_version (6 bits) */
        cfgCode->controlSection.Task_ID &= ((cfgBin >> 6) & MASK_TWO_BITS_R);
        cfgCode->controlSection.RPI_version = (cfgBin & MASK_SIX_BITS_R) << 2;
        break;
    }
    case PARSE_STAGE_TWO:
    {
        /* Fill Control Section
            full -> RPI_version (2 bits)
            partially -> Reference_ID (6 bits) */
        cfgCode->controlSection.RPI_version &= ((cfgBin >> 6) & MASK_TWO_BITS_R);
        cfgCode->controlSection.Reference_ID = (cfgBin & MASK_SIX_BITS_R) << 2;
        break;
    }
    case PARSE_STAGE_THREE:
    {
        /* Fill Control Section
            full -> Reference_ID (2 bits)
            partially -> Implementation_version (6 bits) */
        cfgCode->controlSection.Reference_ID &= ((cfgBin >> 6) & MASK_TWO_BITS_R);
        cfgCode->controlSection.Implementation_version = (cfgBin & MASK_SIX_BITS_R) << 2;
        break;
    }
    case PARSE_STAGE_FOUR:
    {
        /* Fill Control Section
            full -> Implementation_version (2 bits)
            partially -> Developer_ID (6 bits) */
        cfgCode->controlSection.Implementation_version &= ((cfgBin >> 6) & MASK_TWO_BITS_R);
        cfgCode->controlSection.Developer_ID = (cfgBin & MASK_SIX_BITS_R) << 2;
        parseState = PARSE_STATE_FINISH; //! THIS
        break;
    }

    default:
        break;
    }
    parseFlags.stageCnt++;

    return parseState;
}

void rvm_cfgCodeFetcher::clearParseFlags()
{
    parseFlags.start = RESET_FLAG;
    parseFlags.end = RESET_FLAG;
    parseFlags.stageCnt = RESET_FLAG;

    /* Reset control section */
    parseFlags.ctrlSec.LCF = RESET_FLAG;
    parseFlags.ctrlSec.NAF = RESET_FLAG;
    // parseFlags.ctrlSec.Task_ID = RESET_FLAG;
    parseFlags.ctrlSec.RPI_version = RESET_FLAG;
    parseFlags.ctrlSec.Reference_ID = RESET_FLAG;
    parseFlags.ctrlSec.Implementation_version = RESET_FLAG;
    parseFlags.ctrlSec.Developer_ID[0] = RESET_FLAG;
    parseFlags.ctrlSec.Developer_ID[1] = RESET_FLAG;
    parseFlags.ctrlSec.Creation_Date[0] = RESET_FLAG;
    parseFlags.ctrlSec.Creation_Date[1] = RESET_FLAG;
}
