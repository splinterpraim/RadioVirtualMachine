/**
 * @file fc_help_func.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Help functions for front-end compiler
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

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
#include "ir_data.hpp"
#include "ir_operator.hpp"
#include "ir_link.hpp"
#include "config_code_structure.hpp"

/* ************************** parseSWIR */

/**
 * @brief Shows IR operators
 * 
 * @param[in] operators Vector of IR operators
 */
void showIrOperators(const std::vector<IrOperator> &operators);

/**
 * @brief Shows IR data
 * 
 * @param[in] data Vector of IR data
 */
void showIrData(const std::vector<IrData> &data);

/**
 * @brief Shows IR links
 * 
 * @param[in] links Vector of IR links 
 */
void showIrLinks(const std::vector<IrLink> &links);

/* ************************** convert2rvmIr */

/**
 * @brief Creates the DO Configs from IR objects
 * 
 * @param[in] irObjects IR objects
 * 
 * @retval DO_Config* Pointer to created DO Configs
 */
DO_Config *getDoConfig(IrObjects &irObjects);

/**
 * @brief Gets data size from IR data for the DO Config field
 * 
 * @param[in] irData IR data
 * 
 * @retval uint32_t Data size
 */
uint32_t getDoConfig_size(IrData &irData);

/**
 * @brief Gets flag of external data
 * 
 * @return uint8_t flag of external data
 */
uint8_t getExternal();

/**
 * @brief Gets real data length from IR data for the DO Config field
 * 
 * @param[in] irData IR data
 * @param[in] size Data size
 *  
 * @retval uint8_t Data length
 */
uint8_t getDoConfig_length(IrData &irData, uint32_t size);

/**
 * @brief Gets data from IR data for the DO Config field
 * 
 * @param[in] irData IR data
 * @param[in] len Data length
 * 
 * @retval uint8_t* Pointer to data
 */
uint8_t *getDoConfig_data(IrData &irData, uint8_t len);

/**
 * @brief Creates the ASF Configs from IR objects
 * 
 * @param[in] irObjects IR objects
 *  
 * @retval ASF_Config* Pointer to created ASF Configs
 */
ASF_Config *getAsfConfig(IrObjects &irObjects);

/**
 * @brief Gets amount of IR data connections with IR operators for the AsfConfig field 
 * 
 * @param[in] irData IR data
 * @param[in] irObjects IR objects
 * 
 * @retval uint8_t Amount of IR data connections 
 */
uint8_t getAsfConfig_numApe(IrData &irData, IrObjects &irObjects);

/**
 * @brief Gets IR data connections with IR operators for the AsfConfig field
 * 
 * @param[in] irData    IR data
 * @param[in] N         Amount of IR data connections
 * @param[in] irObjects IR objects
 * 
 * @retval ASF_variable_part* Pointer to IR data connections
 */
ASF_variable_part *getAsfConfig_APE_KP(IrData &irData, uint8_t N, IrObjects &irObjects);

/**
 * @brief Gets operator ID in context of Config Code
 * 
 * @param[in] apeId IR operator ID
 * @param[in] irObjects IR objects
 * 
 * @retval uint8_t Operator ID
 */
uint8_t getApeIdForCfgCode(std::string apeId, IrObjects &irObjects);

/**
 * @brief Gets the amount of input links in operator
 * 
 * @param[in] opId IR operator ID
 * @param[in] links Vector of IR links
 * 
 * @retval int Amount of input links
 */
int getNumInputLink(std::string opId , std::vector<IrLink> &links);

/**
 * @brief Gets the amount of output links in operator
 * 
 * @param[in] opId IR operator ID
 * @param[in] links Vector of IR links
 * 
 * @retval int Amount of output links
 */
int getNumOutputLink(std::string opId, std::vector<IrLink> &links);

/**
 * @brief Creates the APE Configs from IR objects  
 * 
 * @param[in] irObjects IR objects
 * 
 * @retval APE_Config* Pointer to APE Configs
 */
APE_Config *getApeConfig(IrObjects &irObjects);

/**
 * @brief Gets the number of data connections from APE
 * 
 * @param[in] opId IR operator ID
 * @param[in] irObjects IR objects
 * 
 * @retval uint8_t Number of data connections
 */
uint8_t getApeNumPorts(std::string opId, IrObjects &irObjects);

/**
 * @brief Creates the Access Type for ports of operator
 * 
 * @param[in] apeNumPorts   Number of data connections
 * @param[in] opId          IR operator ID
 * @param[in] irObjects     IR objects
 * 
 * @retval uint8_t* Pointer to Access Type for ports
 */
uint8_t *getAccessType(uint8_t apeNumPorts, std::string opId, IrObjects &irObjects);

/**
 * @brief Checks the mismatch between the number of input/output ports of the operator in radiolib
 * 
 * @param[in] irOperator IR operator
 * @param[in] irObjects IR objects
 * 
 * @retval true Input/output ports are matched
 * @retval false Input/output ports don't match
 */
bool checkNumPorts(IrOperator &irOperator, IrObjects &irObjects);

/**
 * @brief Gets the file length
 * 
 * @param[in] fileName Name of file
 * 
 * @retval size_t File length
 */
size_t getFileLen(std::string fileName);

/**
 * @brief Gets the file data
 * 
 * @param[in] fileName Name of file
 * 
 * @retval uint8_t* Pointer to data from file
 */
uint8_t* getFileData(std::string fileName);

/**
 * @brief Gets size of data depending on type
 * 
 * @param[in] dataType Type of data
 * @param[in] dataValSize Number of characters. Additional argument of type string.
 * @retval uint32_t Size of data 
 */
uint32_t detectSize(int dataType, size_t dataValSize);

#endif // FC_HELP_FUNC_HPP