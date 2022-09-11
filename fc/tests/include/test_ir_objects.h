//
// Created by Елена on 15.05.2022.
//

#ifndef FRONT_END_RVM_COMPILER_TEST_IR_OBJECTS_H
#define FRONT_END_RVM_COMPILER_TEST_IR_OBJECTS_H

#include <iostream>
#include <string>

/* Project headers */
#include "../../include/ir_data.h"
#include "../../include/ir_operator.h"
#include "../../include/ir_link.h"

/* Testing @1: testing IrData */
void testIrData();
void testIrDataSetId(std::string id);
void testIrDataSetType(std::string type);
void testIrDataSetAccessTime(int accessTime);

/* Testing @2: testing IrOperator */
void testIrOperator();
void testIrOperatorSetId(std::string id);
void testIrOperatorSetType(std::string type);

/* Testing @3: testing IrLink */
void testIrLink();
void testIrLinkSetDataId(std::string dataId);
void testIrLinkSetDataOrder(int dataOrder);
void testIrLinkSetOperatorId(std::string operatorId);
void testIrLinkSetDir(int dir);
#endif //FRONT_END_RVM_COMPILER_TEST_IR_OBJECTS_H
