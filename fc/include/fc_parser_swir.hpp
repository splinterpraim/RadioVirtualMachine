/**
 * @file fc_parser_swir.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief SWIR parser class
 * @version 0.2
 * @copyright Copyright (c) 2023
 */

#ifndef FC_PARSER_SWIR_CLASS
#define FC_PARSER_SWIR_CLASS

#include <string>
#include <map>
#include <vector>
#include "pugixml/pugixml.hpp"

#include "ir_objects.hpp"
#include "ir_data.hpp"
#include "ir_operator.hpp"
#include "ir_link.hpp"

class fc_Parser_SWIR
{
public:
    /**
     * @brief Parses XML file to Intermediate representation
     *
     * @param[in] fileNameSWIR File name where store xml algorithm
     *
     * @retval IrObjects IR objects
     */
    IrObjects parse(const std::string &fileNameSWIR);

private:
    /**
     * Takes all data connected with specific operator and specific connect type.
     * Converts data to key-value array where the key is order and value is IR data.
     *
     * @param[in] op_xml Operator in XML format
     * @param[in] connectType Type of connection operator with data
     *
     * @retval std::map<int, IrData> Key-value array of IR data
     */
    std::map<int, IrData> takeIrData(pugi::xml_node &op_xml, const std::string &connectType);

    /**
     * @brief Converts data in XML format to IR data format
     *
     * @param[in] data_xml Data in XML format
     *
     * @retval IrData IR data format
     */
    IrData convertToIrData(pugi::xml_node &data_xml);

    /**
     * @brief Adds IR data from key-value array to IR data vector if data is not exist
     *
     * @param[in,out] data Vector of IR data
     * @param[in] newData Key-value array of IR data
     */
    void addIrDataToVector(std::vector<IrData> &data, std::map<int, IrData> &newData);

    /**
     * @brief Converts operator in XML format to IR operator format
     *
     * @param[in] op_xml Operator in XML format
     *
     * @retval IrOperator IR operator format
     */
    IrOperator convertToIrOperator(pugi::xml_node &op_xml);

    /**
     * Creates a links with using key-value array of IR data and IR operator.
     * Adds created links in vector of IR links.
     *
     * @param[in,out] links Vector of IR links
     * @param[in] data Vector of IR data
     * @param[in] op IR operator
     * @param[in] dir Direction of data to operator
     */
    void createLinksFromVectorData(std::vector<IrLink> &links, std::map<int, IrData> &data, IrOperator &op, int dir);
};

#endif // FC_PARSER_SWIR_CLASS