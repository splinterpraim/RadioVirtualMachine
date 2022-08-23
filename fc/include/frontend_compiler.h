//
// Created by Елена on 15.05.2022.
//

#ifndef FRONT_END_RVM_COMPILER_FRONTEND_COMPILER_H
#define FRONT_END_RVM_COMPILER_FRONTEND_COMPILER_H

/* C++ headers */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

/* XML lib headers*/
#include "pugixml/pugixml.hpp"

/* Project headers */
#include "ir_data.h"
#include "ir_operator.h"
#include "ir_link.h"

struct IrObjects
{
    std::vector<IrOperator> operators;
    std::vector<IrData> data;
    std::vector<IrLink> links;
};

struct IrObjects parseSWIR(const std::string &fileNameSWIR);
// Convert to RVM IR
// Create RVM Input

/* ######## Help functions*/
/* Convert function */
IrOperator convertToIrOperator(pugi::xml_node &op_xml);
IrData convertToIrData(pugi::xml_node &data_xml);

/* Show functions */
void showIrObjects(const struct IrObjects &irObjects);

void showIrOperators(const std::vector<IrOperator> &operators);

void showIrData(const std::vector<IrData> &data);

void showIrLinks(const std::vector<IrLink> &links);

/* Take data */
std::map<int, IrData> takeIrData(pugi::xml_node &op_xml, const std::string &connectType);

std::vector<IrData> takeOutputIrData(pugi::xml_node &op_xml);

/* Add data to vector */
void addIrDataToVector(std::vector<IrData> &data, std::map<int, IrData> &newData);

/* Create link */
void createLinksFromVectorData(std::vector<IrLink> &links, std::map<int, IrData> &data, IrOperator &op, int dir);

#endif // FRONT_END_RVM_COMPILER_FRONTEND_COMPILER_H
