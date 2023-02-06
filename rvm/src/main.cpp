#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <exception>
#include <stdexcept>

#include "rvm.hpp"

#include "rvm_program_mem.hpp"
#include "CU/rvm_control_unit.hpp"
#include "CU/rvm_cfg_code_fetcher.hpp"
#include "DO/data_object.hpp"

#include "rvm_glob_define.hpp"
#include "common.hpp"
#include "config_code_structure.hpp"

// #include "config_code_structure.hpp"
// rvm_ProgramMemory progMem;

int test();
void parseArg(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    try
    {
        rvm_globDefaultFill();
        parseArg(argc, argv);

        // todo: replace progMem cfgFe code in Rvm run
        std::vector<std::string> cfgFileNames;
        cfgFileNames.push_back("./config_codes/cfgcode1.bin");
        Rvm rvm1(cfgFileNames);
        rvm1.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    // test();
}

int test()
{
    try
    {

        DataObject do1;
        do1.set(1, 10, 1);
        // do1.set(1, 10, 1);
        std::cout << do1.to_str() << std::endl;

        // struct StatusFromDataObject s;
        // ControlUnit mainCU, slaveCU;

        /// -->>>>>>>>>>>>>>>>>

        // mainCU.setStatus(s);
        // slaveCU.setStatus(s);


        // DataObject mainDO;
        // mainDO.set(1, 0, 3);
        // mainDO.checkCallBack();
        // s.id = 2;
        // sendStatusDO(slaveCU, s);

    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Invalid_argument: " << e.what() << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Runtime_error: " << e.what() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Exception" << std::endl;
    }
    return 0;
}


void parseArg(int argc, char *argv[])
{
    if (argc > 2)
    {
        throw std::runtime_error(RVM_ERR_STR("invalid program argument"));
    }

    

    if (argc == 2)
    {
        rvm_glob_t newGlob;
        int logLevel = -1;
        std::sscanf(argv[1], "%d", &logLevel);
        if (logLevel > static_cast<int>(LogLevels::SECOND) || logLevel == -1)
        {
            throw std::runtime_error(RVM_ERR_STR("invalid program argument - logLevel"));
        }
        newGlob.log_levl = static_cast<LogLevels>(logLevel);
        rvm_globFill(newGlob);
    }
    
    

}