#include <iostream>
#include <string>
#include "CU/control_unit.h"
#include "DO/data_object.h"

using namespace std;

int main()
{
    try
    {

        // struct StatusFromDataObject s;
        rvm::ControlUnit mainCU, slaveCU;
        // mainCU.configuringDataObjects();
        mainCU.configuringAbstractProcessingElements();

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
    catch (const char *ex)
    {
        cout << ex << endl;
    }
    catch (string ex)
    {
        cout << ex << endl;
    }
    return 0;
}