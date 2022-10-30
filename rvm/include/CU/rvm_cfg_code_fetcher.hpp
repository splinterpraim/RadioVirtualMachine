#ifndef RVM_CFG_CODE_FETCHER_CLASS
#define RVM_CFG_CODE_FETCHER_CLASS

#include <cstdint>
#include "config_code_structure.hpp"
#include "rvm_program_mem.hpp"

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

        struct asfCfg_s
        {
            uint8_t start = RESET_FLAG;
            uint8_t DO = RESET_FLAG;
            uint8_t N = RESET_FLAG;
            uint8_t APE_KP = RESET_FLAG;
            uint8_t cntAPE_KP = RESET_FLAG;
            uint8_t stageCnt = RESET_FLAG;
        } asfCfg;


    } doSec;


    struct apeSec_s
    {
        uint8_t end = RESET_FLAG;
        uint8_t start = RESET_FLAG;
        uint8_t Ncnt = RESET_FLAG;
        uint8_t stageCnt = RESET_FLAG;

         struct apeCfg_s
        {
            uint8_t start = RESET_FLAG;
            uint8_t APE_ID = RESET_FLAG;
            uint8_t op_code = RESET_FLAG;
            uint8_t T = RESET_FLAG;
            uint8_t NN = RESET_FLAG;
            uint8_t cost = RESET_FLAG;
            uint8_t time = RESET_FLAG;
            uint8_t access_type = RESET_FLAG;
            uint8_t stageCnt = RESET_FLAG;
        } apeCfg;

    }apeSec;

};
using ParseCfgCodeFlags = struct ParseCfgCodeFlags_s;

class rvm_cfgCodeFetcher
{
public:
    rvm_cfgCodeFetcher();
    ~rvm_cfgCodeFetcher();

    void associate(rvm_ProgramMemory &programMemory);

    /**
     * @brief Fetch config code from program memory
     *
     * @param[in] cfgAddr Start address
     * @return Config Objects
     */
    ConfigObjects *fetch(uint64_t cfgAddr);

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

    /* Associated objects */
    rvm_ProgramMemory *programMemory;

    int parseCfgCode(uint8_t &cfgBin);
    void clearParseFlags();
};

#endif // RVM_CFG_CODE_FETCHER_CLASS