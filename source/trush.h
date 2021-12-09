//
// Created by oem on 07.11.2021.
//

#ifndef RADIOVIRTUALMACHINE_TRUSH_H
#define RADIOVIRTUALMACHINE_TRUSH_H



using namespace std;
mutex mutex_forC1;


void doSet(int atrValue, RVM_DataObject *DO_Object);

void doInit(int dataValue, RVM_DataObject *DO_Object);

void APE_FunctionIncrement(RVM_DataObject *DO_ObjectInput, RVM_DataObject *DO_ObjectOutput);

void APE_FunctionMultiple(RVM_DataObject *DO_ObjectInput1, RVM_DataObject *DO_ObjectInput2, RVM_DataObject *DO_ObjectOutput);

void APE_FunctionSum(RVM_DataObject *DO_ObjectInput1, RVM_DataObject *DO_ObjectInput2, RVM_DataObject *DO_ObjectOutput);


void show(thread::id idT, string name, int atr) {
    cout << "ID = " << idT << " " << name << " " << atr << endl;
}

void showDO(RVM_DataObject *DO_Object, string lable) {
    cout << lable << ":";
    cout << "\tdata \t= " << DO_Object->getData() << endl;
    cout << "\tstatus \t= " << DO_Object->getStatus() << endl;
}

void doWork(RVM_DataObject *DO_Object) {
//    DO_Object->setStatus(1);
//    show(this_thread::get_id(), "doWork", sharedMemoryObject->getStatus());
}

void CU_logic(); // logic into Control Unit

void doSet(int atrValue, RVM_DataObject *DO_Object) {
    DO_Object->set(atrValue);
}

void doInit(int dataValue, RVM_DataObject *DO_Object) {
    DO_Object->init(dataValue);
}

void APE_FunctionIncrement(RVM_DataObject *DO_ObjectInput, RVM_DataObject *DO_ObjectOutput) {
    DataEnable inputDataEnable;
    DataEnable outputDataEnable;
    while (true) {
        inputDataEnable = DO_ObjectInput->getDataEnable();
        outputDataEnable = DO_ObjectOutput->getDataEnable();
        if ((inputDataEnable == 1) and (outputDataEnable == 0)) {
            Data inputData = DO_ObjectInput->readAndErase();
            inputData++;
            DO_ObjectOutput->write(inputData);
            break;
        }
    }
}

void APE_FunctionMultiple(RVM_DataObject *DO_ObjectInput1, RVM_DataObject *DO_ObjectInput2,
                          RVM_DataObject *DO_ObjectOutput) {
    DataEnable inputDataEnable1;
    DataEnable inputDataEnable2;
    DataEnable outputDataEnable;
    while (true) {
        inputDataEnable1 = DO_ObjectInput1->getDataEnable();
        inputDataEnable2 = DO_ObjectInput2->getDataEnable();
        outputDataEnable = DO_ObjectOutput->getDataEnable();
        if ((inputDataEnable1 == 1) and (inputDataEnable2 == 1) and (outputDataEnable == 0)) {
            mutex_forC1.lock();
            Data inputData1 = DO_ObjectInput1->readAndErase();
            Data inputData2 = DO_ObjectInput2->readAndErase();
            Data outputData = inputData1 * inputData2;
            DO_ObjectOutput->write(outputData);
            mutex_forC1.unlock();
            break;
        }
    }
}

void APE_FunctionSum(RVM_DataObject *DO_ObjectInput1, RVM_DataObject *DO_ObjectInput2, RVM_DataObject *DO_ObjectOutput) {
    DataEnable inputDataEnable1;
    DataEnable inputDataEnable2;
    DataEnable outputDataEnable;
    while (true) {
        inputDataEnable1 = DO_ObjectInput1->getDataEnable();
        inputDataEnable2 = DO_ObjectInput2->getDataEnable();
        outputDataEnable = DO_ObjectOutput->getDataEnable();
        if ((inputDataEnable1 == 1) and (inputDataEnable2 == 1) and (outputDataEnable == 0)) {
            mutex_forC1.lock();
            Data inputData1 = DO_ObjectInput1->readAndErase();
            Data inputData2 = DO_ObjectInput2->readAndErase();
            Data outputData = inputData1 + inputData2;
            DO_ObjectOutput->write(outputData);
            mutex_forC1.unlock();
            break;
        }
    }
}

void CU_logic() {
    auto *DO_x1 = new RVM_DataObject();
    auto *DO_y1 = new RVM_DataObject();
    auto *DO_x2 = new RVM_DataObject();
    auto *DO_y2 = new RVM_DataObject();
    auto *DO_c1 = new RVM_DataObject();
    auto *DO_c2 = new RVM_DataObject();
    auto *DO_c = new RVM_DataObject();

    doSet(1, DO_x1);
    doSet(1, DO_y1);
    doSet(1, DO_x2);
    doSet(1, DO_y2);
    doSet(0, DO_c1);
    doSet(0, DO_c2);
    doSet(0, DO_c);

    doInit(1, DO_x1);
    doInit(2, DO_y1);
    doInit(3, DO_x2);
    doInit(4, DO_y2);
    doInit(0, DO_c1);
    doInit(0, DO_c2);
    doInit(0, DO_c);

    cout << "START: " << endl;
    showDO(DO_x1, "x1");
    showDO(DO_y1, "y1");
    showDO(DO_x2, "x2");
    showDO(DO_y2, "y2");
    showDO(DO_c1, "c1");
    showDO(DO_c2, "c2");
    showDO(DO_c, "c");


    thread t1(APE_FunctionMultiple, DO_x1, DO_y1, DO_c1);
    thread t2(APE_FunctionMultiple, DO_x2, DO_y2, DO_c2);
    thread t3(APE_FunctionSum, DO_c1, DO_c2, DO_c);

    t1.join();
    t2.join();
    t3.join();

    cout << endl << "FINISH: " << endl;
    showDO(DO_x1, "x1");
    showDO(DO_y1, "y1");
    showDO(DO_x2, "x2");
    showDO(DO_y2, "y2");
    showDO(DO_c1, "c1");
    showDO(DO_c2, "c2");
    showDO(DO_c, "c");


    delete DO_x1;
    delete DO_y1;
    delete DO_x2;
    delete DO_y2;
    delete DO_c1;
    delete DO_c2;
    delete DO_c;
}




impl_ASF(){

    class RVM_AbstractSwitchFabric{
        PortsDO * portsDO; // size_portsDO
        PortsAPE * portsAPE; // size_portsAPE
        Connector * connectors;
    };

    class PortsDO{
        &DO;
        number;
        interf; //

        functions
    };

    class PortsAPE{
        &APE;
        number;
        interf; //

        functions
    };

    class Connector{
        numPortDO;
        numPortAPE;
        direction;
//        interfaceLineDO;
//        interfaceLineAPE;
    };


}
#endif //RADIOVIRTUALMACHINE_TRUSH_H
