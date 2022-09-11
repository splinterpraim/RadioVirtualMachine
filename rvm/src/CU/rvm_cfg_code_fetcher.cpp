#include "CU/rvm_cfg_code_fetcher.hpp"
#include "rvm_program_mem.hpp"

extern rvm_ProgramMemory progMem;

rvm_cfgCodeFetcher::rvm_cfgCodeFetcher()
{

}

rvm_cfgCodeFetcher::~rvm_cfgCodeFetcher()
{

}

int rvm_cfgCodeFetcher::fetch(uint64_t cfgAddr)
{
    progMem.get(cfgAddr);
    return 0;
}



/* private */
ConfigObjects * rvm_cfgCodeFetcher::parseCfgCode(uint8_t  &cfgBin)
{
    ConfigObjects *res;
    return res;
}
