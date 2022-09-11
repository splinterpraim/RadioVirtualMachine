#ifndef RVM_CFG_CODE_FETCHER_CLASS
#define RVM_CFG_CODE_FETCHER_CLASS

#include <cstdint>
#include "config_code_structure.hpp"

class rvm_cfgCodeFetcher
{
public:
    rvm_cfgCodeFetcher();
    ~rvm_cfgCodeFetcher();
    int fetch(uint64_t cfgAddr);

private:
    ConfigObjects cfgCode;
    int do_num;
    int ape_num;
    ConfigObjects * parseCfgCode(uint8_t  &cfgBin);
};

#endif // RVM_CFG_CODE_FETCHER_CLASS