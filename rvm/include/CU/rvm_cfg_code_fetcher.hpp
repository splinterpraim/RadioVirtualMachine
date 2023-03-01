/**
 * @file rvm_cfg_code_fetcher.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Config Code Fetcher
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_CFG_CODE_FETCHER_CLASS
#define RVM_CFG_CODE_FETCHER_CLASS

#include <cstdint>
#include "config_code_structure.hpp"

#define SET_FLAG 1      /* Flag is set */
#define RESET_FLAG 0    /* Flag is reset */

#define PARSE_STATE_IN_PROC 1   /* Parsing the config code is still in progress */
#define PARSE_STATE_FINISH 0    /* Parsing the config code is finished */

class rvm_ProgramMemory;    /* Forward declaration of rvm_ProgramMemory class */

/**
 * @brief Describes state flags for parsing config code 
 */
struct ParseCfgCodeFlags_s
{
    uint8_t start = RESET_FLAG;     /* Start of config code parsing */
    uint8_t end = RESET_FLAG;       /* End of config code parsing */
    uint8_t stageCnt = RESET_FLAG;  /* Counter of Control Section stages */
    uint8_t ctrlSec = RESET_FLAG;   /* Control Section parsing */

    /**
     * @brief DO Section parsing 
     */
    struct doSec_s
    {
        uint8_t end = RESET_FLAG;   /* End of  DO section parsing */
        uint8_t start = RESET_FLAG; /* Start of DO section parsing */
        uint8_t Ncnt = RESET_FLAG;  /* Current data number in parsing */
        
        /**
         * @brief DO config parsing
         */
        struct doCfg_s
        {
            uint8_t start = RESET_FLAG;         /* Start of DO config parsing */
            uint8_t DO_ID = RESET_FLAG;         /* Parsing the DO config DO_ID field */
            uint8_t size = RESET_FLAG;          /* Parsing the DO config size field */
            uint8_t access_time = RESET_FLAG;   /* Parsing the DO config access_time field */
            uint8_t length = RESET_FLAG;        /* Parsing the DO config length field */
            uint8_t data = RESET_FLAG;          /* Parsing the DO config data field */
            uint8_t byteCnt = RESET_FLAG;       /* Counter of processed bytes */
        } doCfg;

        /**
         * @brief ASF config parsing
         */
        struct asfCfg_s
        {
            uint8_t start = RESET_FLAG;     /* Start of ASF config parsing */
            uint8_t DO = RESET_FLAG;        /* Parsing the ASF config DO field */
            uint8_t N = RESET_FLAG;         /* Parsing the ASF config N field */
            uint8_t APE_KP = RESET_FLAG;    /* Parsing the ASF config APE_KP field */
            uint8_t cntAPE_KP = RESET_FLAG; /* Counter of APE_KP */
            uint8_t byteCnt = RESET_FLAG;   /* Counter of processed bytes */
        } asfCfg;
    } doSec;

    /**
     * @brief APE Section parsing 
     */
    struct apeSec_s
    {
        uint8_t end = RESET_FLAG;       /* End of  APE section parsing */
        uint8_t start = RESET_FLAG;     /* Start of APE Section parsing */
        uint8_t Ncnt = RESET_FLAG;      /* Current APE number in parsing */
        uint8_t byteCnt = RESET_FLAG;   /* Counter of processed bytes */

        /**
         * @brief APE config parsing
         */
         struct apeCfg_s
        {
            uint8_t start = RESET_FLAG;         /* Start of APE config parsing */
            uint8_t APE_ID = RESET_FLAG;        /* Parsing the APE config APE_ID field */
            uint8_t op_code = RESET_FLAG;       /* Parsing the APE config op_code field */
            uint8_t T = RESET_FLAG;             /* Parsing the APE config T field */
            uint8_t NN = RESET_FLAG;            /* Parsing the APE config NN field */
            uint8_t cost = RESET_FLAG;          /* Parsing the APE config cost field */
            uint8_t time = RESET_FLAG;          /* Parsing the APE config time field */
            uint8_t access_type = RESET_FLAG;   /* Parsing the APE config access_type field */
            uint8_t byteCnt = RESET_FLAG;       /* Counter of processed bytes */
        } apeCfg;
    }apeSec;
};
using ParseCfgCodeFlags = struct ParseCfgCodeFlags_s;

/**
 * @brief Config Code Fetcher class implementation
 */
class rvm_cfgCodeFetcher
{
public:

    /**
     * @brief Constructs a new rvm cfgCodeFetcher object
     */
    rvm_cfgCodeFetcher();

    /**
     * @brief Destroys the rvm cfgCodeFetcher object
     * 
     */
    ~rvm_cfgCodeFetcher();

    /**
     * @brief Associates Config Code Fetcher with related Program memory
     *
     * @param[in]       programMemory           Related to related Program memory
     */
    void associate(rvm_ProgramMemory &programMemory);

    /**
     * @brief Fetches config code from program memory by Config Code address
     *
     * @param[in]       cfgAddr                 Config Code address
     *
     * @retval          Config Objects *        Pointer to Config Objects
     */
    ConfigObjects& fetch(uint64_t cfgAddr);

    /**
     * @brief Gets the address in Program memory that was last accessed
     *
     * @return          uint64_t                Last used address  
     */
    uint64_t getLastAddress();

private:

    ConfigObjects cfgCode;                          /* Pointer on temporary config code object */
    ParseCfgCodeFlags parseFlags;                   /* Stores state flags for parsing config code  */
    uint64_t lAddress;                              /* Last used address */
    rvm_ProgramMemory *programMemory = nullptr;     /* Externally related Program memory */

    /**
     * @brief Parses the Config code byte by byte
     *
     * @param[in]       cfgByte                 Current byte of config code
     *
     * @retval          PARSE_STATE_FINISH      Parsing the config code is finished
     * @retval          PARSE_STATE_IN_PROC     Parsing the config code is still in progress
     */
    int parseCfgCode(uint8_t &cfgByte);

    /**
     * @brief Сlears the flags used in parsing
     */
    void clearParseFlags();
};

#endif // RVM_CFG_CODE_FETCHER_CLASS