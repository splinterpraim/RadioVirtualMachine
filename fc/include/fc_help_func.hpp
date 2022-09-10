
#ifndef FC_HELP_FUNC_HPP
#define FC_HELP_FUNC_HPP
/* C++ headers */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

/* XML lib headers*/
#include "pugixml/pugixml.hpp"

/* Project headers */
#include "ir_objects.hpp"
#include "ir_data.h"
#include "ir_operator.h"
#include "ir_link.h"
#include "config_code_structure.hpp"

/* ######## Help functions*/
/* ************************** parseSWIR */
/* Convert function */
IrOperator convertToIrOperator(pugi::xml_node &op_xml);
IrData convertToIrData(pugi::xml_node &data_xml);

/* Show functions */
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


/* ######## Help functions*/
/* ************************** convert2rvmIr */
void showControlSection(ControlSection &ctrlSec);
void showDoSection(DO_Section &doSec);
void showDO_Config(DO_Config &doCfg, uint8_t N_DO);



/* Get config */
DO_Config *getDoConfig(IrObjects &irObjects);
uint32_t getDoConfig_size(IrData &irData);
uint8_t *getDoConfig_sizeLenData(class IrData &irData, uint32_t &doCfgSize, uint8_t &doCfgLen);
ASF_Config *getAsfConfig(IrObjects &irObjects);



#endif // FC_HELP_FUNC_HPP