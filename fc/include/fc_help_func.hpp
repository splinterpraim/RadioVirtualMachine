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

#endif // FC_HELP_FUNC_HPP