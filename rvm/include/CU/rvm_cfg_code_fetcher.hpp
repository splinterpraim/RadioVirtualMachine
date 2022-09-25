#ifndef RVM_CFG_CODE_FETCHER_CLASS
#define RVM_CFG_CODE_FETCHER_CLASS

#include <cstdint>
#include "config_code_structure.hpp"

#define SET_FLAG 1
#define RESET_FLAG 0

struct ParseCfgCodeFlags_s
{
    uint8_t end = RESET_FLAG;
    struct ControlSectionFlags
    {
        uint8_t LCF = RESET_FLAG;                            // 1 bit
        uint8_t NAF = RESET_FLAG;                            // 1 bit
        uint8_t Task_ID = RESET_FLAG;                        // 8 bit
        uint8_t RPI_version = RESET_FLAG;                    // 8 bit
        uint8_t Reference_ID = RESET_FLAG;                   // 8 bit
        uint8_t Implementation_version = RESET_FLAG;         // 8 bit
        uint8_t Developer_ID[2] = {RESET_FLAG, RESET_FLAG};  // in stand 16 , but 15 bits
        uint8_t Creation_Date[2] = {RESET_FLAG, RESET_FLAG}; // in stand 16 , but 17 bits
    } ctrlSec;
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

private:
    ConfigObjects *cfgCode;
    ParseCfgCodeFlags parseFlags;
    int do_num;
    int ape_num;

    int parseCfgCode(uint8_t &cfgBin);
    void clearParseFlags();
};

#endif // RVM_CFG_CODE_FETCHER_CLASS