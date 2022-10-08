
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
void showASF_config(ASF_Config &asfCfg, uint8_t N_DO);



/* Get config */
DO_Config *getDoConfig(IrObjects &irObjects);
uint32_t getDoConfig_size(IrData &irData);
uint8_t getDoConfig_length(IrData &irData);
uint8_t *getDoConfig_data(IrData &irData, uint8_t len);
ASF_Config *getAsfConfig(IrObjects &irObjects);
uint8_t getAsfConfig_numApe(IrData &irData, IrObjects &irObjects);
ASF_variable_part *getAsfConfig_APE_KP(IrData &irData, uint8_t N, IrObjects &irObjects);
uint8_t getApeOrderNum(std::string apeId, IrObjects &irObjects);
int getNumInputLink(std::string opId , std::vector<IrLink> &links);
int getNumOutputLink(std::string opId, std::vector<IrLink> &links);
APE_Config *getApeConfig(IrObjects &irObjects);
uint8_t getApeNumPorts(std::string opId, IrObjects &irObjects);
uint8_t *getAccessType(uint8_t apeNumPorts, std::string opId, IrObjects &irObjects);

/*  */
size_t getFileLen(std::string fileName);
uint8_t* getFileData(std::string fileName);


#endif // FC_HELP_FUNC_HPP