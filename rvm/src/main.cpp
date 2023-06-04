/**
 * @file main.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Program to execute one task on RVM
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <vector>
#include <exception>
#include <stdexcept>

extern "C"
{
#include <dirent.h>
#include <sys/types.h>
}

#include "rvm.hpp"
#include "rvm_glob_define.hpp"
#include "common.hpp"
#include "system_func.hpp"

#define RVM_MAX_STR_SIZE 255

typedef struct {
    const char* name;
    const char* shortName;
    char arg[RVM_MAX_STR_SIZE];
} cmdLineOption_t;

cmdLineOption_t cmdLineOptions[] = {
    {"--taskdir", "-t", {0}},
    {"--loglevel", "-l", {0}}
};

/**
 * @brief Setting variables
 */
typedef struct rvm_setting_s
{
    LogLevels log_levl;     /* level of log */
    std::string taskDir;
} rvm_setting_t;

typedef struct
{
    std::string taskDir;
    typedef struct {
        std::string name;
        uint8_t* cc;
        size_t cc_size;
        std::map<int,std::string> map;
        typedef struct {
            std::string name;
            uint8_t* cc;
            size_t cc_size;
            std::map<int,std::string> map;
        } complex_t;
        std::vector<complex_t> complex;
    }program_t;
    std::vector<program_t> programs;
} rvm_task_view_t;

std::map<int,std::string> getMapFromFile(std::string filePath)
{
    std::map<int,std::string> resMap;
    std::vector<std::string> lines = file2strLine(filePath);
    for(auto& line : lines)
    {
        size_t splitPos = line.find(",");
        std::string opID = line.substr(0, splitPos);
        std::string opName = line.substr(splitPos+1, line.size());
        int opID_i,n;
        int ret = std::sscanf(opID.c_str(), "%d%n",&opID_i,&n);
        if((ret != 1) || (std::strlen(opID.c_str()) != (size_t)n))
        {
            throw std::runtime_error(".map is invalid");
        }
        resMap[opID_i] = opName;
    }
    return resMap;
}

rvm_task_view_t::program_t::complex_t& findOrCreate(std::vector<rvm_task_view_t::program_t::complex_t>& complexes, std::string name)
{
    for(auto& c : complexes)
    {
        if(c.name.compare(name) == 0)
        {
            return c;
        }
    }
    complexes.resize(complexes.size() + 1);
    return complexes[complexes.size()-1];
}


const char* getArgFromOption(const char* optName)
{
    size_t optSize = sizeof(cmdLineOptions)/sizeof(cmdLineOptions[0]);
    for (size_t i = 0; i < optSize; i++)
    {
        cmdLineOption_t *oneOpt = &cmdLineOptions[i];
        if((std::strncmp(oneOpt->name, optName, std::strlen(oneOpt->name)) == 0) ||
            (std::strncmp(oneOpt->shortName, optName, std::strlen(oneOpt->shortName)) == 0))
        {
            return oneOpt->arg;
        }
    }
    return "";
}

/**
 * @brief Parses the command line arguments
 *
 * @param[in]       argc                    Amount of command line arguments
 * @param[in]       argv                    Values of command line arguments
 */
void parseArg(int argc, char* argv[], rvm_setting_t& sets)
{
    size_t optSize = sizeof(cmdLineOptions)/sizeof(cmdLineOptions[0]);
    cmdLineOption_t *setOpt = nullptr;

    /* Default sets */
    sets.taskDir = "./";
    sets.log_levl = LogLevels::ZERO; 

    /* Fills sets from option arguments */
    if(argc > 1)
    {
        for (int i = 0; i < argc-1; i++)
        {
            char * curArg = argv[i+1];
            /* Set argument for option */
            if (setOpt)
            {
                size_t argLen = std::strlen(curArg);
                if ( (argLen > 0) && (curArg[0] == '-') )
                {
                        goto bad_arg;
                }
                std::strncpy(setOpt->arg, curArg, strlen(curArg)+1);

                setOpt = nullptr;
            }
            /* Detect option */
            else
            {
                for (size_t j = 0; j < optSize; j++)
                {
                    cmdLineOption_t *oneOpt = &cmdLineOptions[j];
                    if((std::strncmp(oneOpt->name, curArg, std::strlen(oneOpt->name)) == 0) ||
                        (std::strncmp(oneOpt->shortName, curArg, std::strlen(oneOpt->shortName)) == 0))
                    {
                        setOpt = oneOpt;
                        break;
                    }
                }
                if (!setOpt)
                {
                    goto bad_arg;
                }
            }
            
        }
        /* All options must have arguments */
        if (setOpt)
        {
            goto bad_arg;
        }
        sets.taskDir = getArgFromOption("--taskdir");
        std::string log_levl_tmp = getArgFromOption("--loglevel");
        if (log_levl_tmp.compare("")!=0)
        {
            sets.log_levl = static_cast<LogLevels>( std::stoi(log_levl_tmp));
        }
    }
    return;

bad_arg:
    throw std::runtime_error(RVM_ERR_STR("invalid program argument"));
}


void processTaskDir(std::string taskDir, rvm_task_view_t& task)
{
    DIR *dir;
    DIR *dirProg;
    DIR *dirComplex;
    struct dirent *ent;
    struct dirent *entProg;
    struct dirent *entComplex;
    const char* rootDir = taskDir.c_str();
    char path[1024];
    char pathComplex[1024];
    char filePath[1024];

    task.taskDir = rootDir;
    if ((dir = opendir (rootDir)) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            /* Process program dir */
            if (ent->d_type == DT_DIR)
            {
                /* Skip dirs */
                if (!strcmp (ent->d_name, "."))
                    continue;
                if (!strcmp (ent->d_name, ".."))
                    continue;
                
                /* Process program directory inside */
                snprintf(path, sizeof(path), "%s/%s", rootDir, ent->d_name);
                if ((dirProg = opendir (path)) != NULL)
                {
                    size_t progNum = task.programs.size();
                    task.programs.resize(progNum + 1);
                    rvm_task_view_t::program_t* curProg = &task.programs[progNum];

                    while ((entProg = readdir (dirProg)) != NULL)
                    {
                        /* Skip dirs */
                        if (!strcmp (entProg->d_name, "."))
                            continue;
                        if (!strcmp (entProg->d_name, ".."))
                            continue;

                        /* Process complex dir */
                        if((entProg->d_type == DT_DIR) && 
                            (!strncmp(entProg->d_name,"complex",strlen(entProg->d_name))))
                        {
                            snprintf(pathComplex, sizeof(pathComplex), "%s/%s", path, entProg->d_name);
                            if ((dirComplex = opendir (pathComplex)) != NULL)
                            {
                                while ((entComplex = readdir (dirComplex)) != NULL)
                                {
                                    /* Process complex files */
                                    if(entComplex->d_type == DT_REG)
                                    {
                                        snprintf(filePath, sizeof(filePath), "%s/%s", pathComplex, entComplex->d_name);
                                        std::string ext, name;
                                        getName(std::string(entComplex->d_name), name);
                                        getExt(std::string(entComplex->d_name), ext);
                                        rvm_task_view_t::program_t::complex_t& cplx = findOrCreate(curProg->complex, name);
                                        if(cplx.name.compare("") == 0)
                                        {
                                            cplx.name = name;
                                        }

                                        if(ext.compare("bin") == 0)
                                        {
                                            file2array(filePath, &cplx.cc, cplx.cc_size);
                                        }
                                        else if (ext.compare("map") == 0)
                                        {
                                            cplx.map = getMapFromFile(filePath);
                                        }
                                    }
                                }
                                closedir (dirComplex);
                            }
                        }

                        /* Process program files */
                        else if(entProg->d_type == DT_REG)
                        {
                            snprintf(filePath, sizeof(filePath), "%s/%s", path, entProg->d_name);
                            std::string ext, name;
                            getName(std::string(entProg->d_name), name);
                            getExt(std::string(entProg->d_name), ext);
                            curProg->name = name;
                            if(ext.compare("bin") == 0)
                            {
                                file2array(filePath, &curProg->cc, curProg->cc_size);
                            }
                            else if (ext.compare("map") == 0)
                            {
                                curProg->map = getMapFromFile(filePath);
                            }
                        }
                    }
                closedir (dirProg);
                
                }
            }
            
        }
        closedir (dir);
    }

    /* Could not open directory */
    else 
    {
        throw std::runtime_error(RVM_ERR_STR("Could not open directory"));
    }

}

void showTaskDir(rvm_task_view_t& task)
{
    std::printf("TASK [%s]\n",task.taskDir.c_str());
    for(auto& p : task.programs)
    {
        std::printf("program: %s\n", p.name.c_str());
        std::printf("map ->\n");
        for(auto& progM : p.map)
        {
            std::printf("\t%d : %s\n", progM.first, progM.second.c_str());
        }
        std::printf("config code (len %lu bytes) ->\n",p.cc_size);
        size_t i = 0;
        while( i < p.cc_size)
        {
            std::printf("\t");
            for(size_t j = 0; j < BIN_INPUT_ROW_SIZE; j++)
            {
                if( i < p.cc_size)
                {
                    std::printf("%.2x ", p.cc[i]);
                }
                i++;
            }
            std::printf("\n");
        }
        std::printf("complex ->\n");

        for(auto& cplx : p.complex)
        {
            std::printf("\tname: %s\n", cplx.name.c_str());
            std::printf("\tmap ->\n");
            for(auto& cplxM : cplx.map)
            {
                std::printf("\t\t%d : %s\n", cplxM.first, cplxM.second.c_str());
            }
            std::printf("\tconfig code (len %lu bytes) ->\n",cplx.cc_size);
            size_t i = 0;
            while( i < cplx.cc_size)
            {
                std::printf("\t\t");
                for(size_t j = 0; j < BIN_INPUT_ROW_SIZE; j++)
                {
                    if( i < cplx.cc_size)
                    {
                        std::printf("%.2x ", cplx.cc[i]);
                    }
                    i++;
                }
                std::printf("\n");
            }

            
        }
    }
    
}

/**
 * @brief Main function
 *
 * @param[in]       argc                    Amount of command line arguments
 * @param[in]       argv                    Values of command line arguments
 *
 * @retval          int                     Return code
 */
int main(int argc, char *argv[])
{
    try
    {
        rvm_setting_t rvmSets;
        parseArg(argc, argv,rvmSets);
        rvm_task_view_t task;
        processTaskDir(rvmSets.taskDir, task);
        showTaskDir(task);
        Rvm rvm1;

        /* Add radio lib operators to RVM */
        uint32_t radioLib_size = sizeof(referenceRadioLibrary)/sizeof(referenceRadioLibrary[0]);
        for(uint32_t i =0 ; i < radioLib_size; i++)
        {
            const radioLibrary_el *el = &referenceRadioLibrary[i];
            rvm1.addRLOperator(el->opcode, el->fn);
        }
        for(auto& p : task.programs)
        {
            /* Add Complex operators to RVM */
            for(auto& cplx : p.complex)
            {
               rvm1.addRVMOperator(cplx.name, cplx.cc, cplx.cc_size, cplx.map );
            }
            /* Add program config code */
            rvm1.addProgram(p.cc, p.cc_size);
        }
        rvm1.show();

        return 0;
        rvm1.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}