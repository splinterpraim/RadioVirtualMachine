#include "CU/rvm_cfg_code_fetcher.hpp"
#include "rvm_program_mem.hpp"
#include "common.hpp"

#define PARSE_STATE 1


extern rvm_ProgramMemory progMem;

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
    if (cfgAddr >=  progMemSize)
    {
        throw std::runtime_error(RVM_ERR_STR("Fetch is failed, because the address is out of memory"));
    }

    uint64_t addr = cfgAddr;
    uint8_t byte = 0;
    ConfigObjects * resCfg = new ConfigObjects[1];

    /* Loop for parsing config code */
    byte = progMem.get(addr++);
    while (parseCfgCode(byte) == PARSE_STATE)
    {
        byte = progMem.get(addr++);
        if (addr >= progMemSize)
        {
            break;
        }
        // if addr  > size mem
    }
    return 0;
}



/* private */
int rvm_cfgCodeFetcher::parseCfgCode(uint8_t  &cfgBin)
{

    // if new fetch
    if (parseFlags.end == SET_FLAG)
    {
        clearParseFlags();
    }

    return PARSE_STATE;
}

void rvm_cfgCodeFetcher::clearParseFlags()
{
    parseFlags.end = RESET_FLAG;

    /* Reset control section */
    parseFlags.ctrlSec.LCF = RESET_FLAG;
    parseFlags.ctrlSec.NAF = RESET_FLAG;
    parseFlags.ctrlSec.Task_ID = RESET_FLAG;
    parseFlags.ctrlSec.RPI_version = RESET_FLAG;
    parseFlags.ctrlSec.Reference_ID = RESET_FLAG;
    parseFlags.ctrlSec.Implementation_version = RESET_FLAG;
    parseFlags.ctrlSec.Developer_ID[0] = RESET_FLAG;
    parseFlags.ctrlSec.Developer_ID[1] = RESET_FLAG;
    parseFlags.ctrlSec.Creation_Date[0] = RESET_FLAG;
    parseFlags.ctrlSec.Creation_Date[1] = RESET_FLAG;
}
