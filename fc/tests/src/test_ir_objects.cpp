//
// Created by Елена on 15.05.2022.
//
#include "../include/test_ir_objects.h"



/* Testing @1 */
void testIrData() {
    testIrDataSetId("x1");
    testIrDataSetId(""); // <- BAD
    testIrDataSetType("float");
    testIrDataSetType(""); // <- BAD
    testIrDataSetAccessTime(10);
    testIrDataSetAccessTime(-1); // <- BAD
}

void testIrDataSetId(std::string id) {
    IrData irData;
    try {
        irData.setId(id);
        std::cout << "->testIrDataSetId GOOD" << std::endl;
    }
    catch (std::invalid_argument &e) {
        std::cout << "->testIrDataSetId BAD" << std::endl;
        cout << "... "<<e.what() << endl;
    }

}

void testIrDataSetType(std::string type) {
    IrData irData;
    try{
        irData.setType(type);
        std::cout << "->testIrDataSetType GOOD" << std::endl;

    }
    catch (std::invalid_argument &e){
        std::cout << "->testIrDataSetType BAD" << std::endl;
        cout << "... "<<e.what() << endl;
    }
}

void testIrDataSetAccessTime(int accessTime){
    IrData irData;
    try{
        irData.setAccessTime(accessTime);
        std::cout << "->testIrDataSetAccessTime GOOD" << std::endl;

    }
    catch (std::invalid_argument &e){
        std::cout << "->testIrDataSetAccessTime BAD" << std::endl;
        cout << "... "<<e.what() << endl;
    }
}

void testIrOperator(){
    testIrOperatorSetId("mult1");
    testIrOperatorSetId(""); // <- BAD
    testIrOperatorSetType("Terminal");
    testIrOperatorSetType(""); // <- BAD
}

void testIrOperatorSetId(std::string id) {
    IrOperator irOperator;
    try {
        irOperator.setId(id);
        std::cout << "->testIrOperatorSetId GOOD" << std::endl;
    }
    catch (std::invalid_argument &e) {
        std::cout << "->testIrOperatorSetId BAD" << std::endl;
        cout << "... "<<e.what() << endl;
    }

}

void testIrOperatorSetType(std::string type) {
    IrOperator irOperator;
    try{
        irOperator.setType(type);
        std::cout << "->testIrOperatorSetType GOOD" << std::endl;

    }
    catch (std::invalid_argument &e){
        std::cout << "->testIrOperatorSetType BAD" << std::endl;
        cout << "... "<<e.what() << endl;
    }
}

void testIrLink(){
    testIrLinkSetDataId("x1");
    testIrLinkSetDataId(""); // <- BAD
    testIrLinkSetDataOrder(1);
    testIrLinkSetDataOrder(-1); // <- BAD
    testIrLinkSetOperatorId("mult1");
    testIrLinkSetOperatorId(""); // <- BAD
    testIrLinkSetDir(0);
    testIrLinkSetDir(-2); // <- BAD
}

void testIrLinkSetDataId(std::string dataId) {
    IrLink irLink;
    try {
        irLink.setDataId(dataId);
        std::cout << "->testIrLinkSetDataId GOOD" << std::endl;
    }
    catch (std::invalid_argument &e) {
        std::cout << "->testIrLinkSetDataId BAD" << std::endl;
        cout << "... " << e.what() << endl;
    }
}

void testIrLinkSetDataOrder(int dataOrder) {
    IrLink irLink;
    try {
        irLink.setDataOrder(dataOrder);
        std::cout << "->testIrLinkSetDataOrder GOOD" << std::endl;
    }
    catch (std::invalid_argument &e) {
        std::cout << "->testIrLinkSetDataOrder BAD" << std::endl;
        cout << "... " << e.what() << endl;
    }
}

void testIrLinkSetOperatorId(std::string operatorId) {
    IrLink irLink;
    try {
        irLink.setOperatorId(operatorId);
        std::cout << "->testIrLinkSetOperatorId GOOD" << std::endl;
    }
    catch (std::invalid_argument &e) {
        std::cout << "->testIrLinkSetOperatorId BAD" << std::endl;
        cout << "... " << e.what() << endl;
    }
}

void testIrLinkSetDir(int dir) {
    IrLink irLink;
    try {
        irLink.setDir(dir);
        std::cout << "->testIrLinkSetDir GOOD" << std::endl;
    }
    catch (std::invalid_argument &e) {
        std::cout << "->testIrLinkSetDir BAD" << std::endl;
        cout << "... " << e.what() << endl;
    }
}