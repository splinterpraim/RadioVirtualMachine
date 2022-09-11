#include <iostream>
#include <string>
#include "rvm_program_mem.hpp"
#include "CU/control_unit.h"
#include "DO/data_object.h"
#include "log_manager.h"

// #include "config_code_structure.hpp"
rvm_ProgramMemory progMem;

using namespace std;

int test();

int main()
{
    progMem.init(10);
	// test();
}


int test()
{
    try
    {

        rvm::DataObject do1;
        do1.set(1, 10, 1);
        // do1.set(1, 10, 1);
        std::cout << do1.to_str() << std::endl;

        // struct StatusFromDataObject s;
        // rvm::ControlUnit mainCU, slaveCU;
        // mainCU.configuringDataObjects();
        // mainCU.configuringAbstractProcessingElements();
        // mainCU.configuringAbstractSwitchFabric();

        /// -->>>>>>>>>>>>>>>>>

        // mainCU.setStatus(s);
        // slaveCU.setStatus(s);

        // mainCU.showStatus();
        // slaveCU.showStatus();

        // rvm::DataObject mainDO;
        // mainDO.set(1, 0, 3);
        // mainDO.setSendControlUnit(mainCU);
        // // mainDO.setSendStatusFunction(rvm::sendStatusDO);
        // mainDO.checkCallBack();
        // s.id = 2;
        // rvm::sendStatusDO(slaveCU, s);
        // mainCU.showStatus();
        // slaveCU.showStatus();

        // mainCU.configuringDataObjects();
    }
    catch (const std::invalid_argument &e)
    {
        cout << "Invalid_argument: " << e.what() << endl;
    }
    catch (const std::runtime_error &e)
    {
        cout << "Runtime_error: " << e.what() << endl;
    }
    catch (std::exception &e)
    {
        cout << "Exception: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Exception" << endl;
    }
    return 0;
}
