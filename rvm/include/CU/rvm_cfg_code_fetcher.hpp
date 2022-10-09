#ifndef RVM_CFG_CODE_FETCHER_CLASS
#define RVM_CFG_CODE_FETCHER_CLASS

#include <cstdint>
#include "config_code_structure.hpp"

#define SET_FLAG 1
#define RESET_FLAG 0

struct ParseCfgCodeFlags_s
{
    uint8_t start = RESET_FLAG;
    uint8_t end = RESET_FLAG;
    uint8_t stageCnt = RESET_FLAG;
    uint8_t ctrlSec = RESET_FLAG;
    struct doSec_s
    {   
        uint8_t end = RESET_FLAG;
        uint8_t start = RESET_FLAG;
        uint8_t Ncnt = RESET_FLAG;
        struct doCfg_s
        {
            uint8_t start = RESET_FLAG;
            uint8_t DO_ID = RESET_FLAG;
            uint8_t size = RESET_FLAG;
            uint8_t access_time = RESET_FLAG;
            uint8_t length = RESET_FLAG;
            uint8_t data = RESET_FLAG;
            uint8_t stageCnt = RESET_FLAG;
        } doCfg;
        
        uint8_t asfCfg = RESET_FLAG;

    }doSec;
  
};
using ParseCfgCodeFlags = struct ParseCfgCodeFlags_s;

class rvm_cfgCodeFetcher
{
public:
    rvm_cfgCodeFetcher();
    ~rvm_cfgCodeFetcher();

    /**
     * @brief Fetch config code from program memory
     *
     * @param cfgAddr Start address
     * @return Configcode
     */
    int fetch(uint64_t cfgAddr);

    /**
     * @brief Show config code
     * 
     */
    void showCfgCode();

private:
    ConfigObjects *cfgCode = nullptr;
    ParseCfgCodeFlags parseFlags;
    int do_num;
    int ape_num;

    int parseCfgCode(uint8_t &cfgBin);
    void clearParseFlags();
};

#endif // RVM_CFG_CODE_FETCHER_CLASS