/**
 * @file ir_operator.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Intermediate representation of operator
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef IR_OPERATOR_H
#define IR_OPERATOR_H

#include <iostream>
#include <string>

/**
 * @brief Class for describing of Intermediate representation operator
 */
class IrOperator
{

public:
	/**
	 * @brief Constructs a new IR Operator object
	 */
	IrOperator() {}

	/**
	 * @brief Destroys the IR Operator object
	 */
	~IrOperator() {}

	/**
	 * @brief Sets the IR Operator ID
	 *
	 * @param[in] id IR Operator ID
	 */
	void setId(const std::string &id);

	/**
	 * @brief Gets the IR Operator ID
	 *
	 * @retval std::string IR Operator ID
	 */
	std::string getId();

	/**
	 * @brief Sets the type of IR Operator object
	 *
	 * @param[in] type Type of IR Operator object
	 */
	void setType(const std::string &type);

	/**
	 * @brief Gets the type of IR Operator object
	 *
	 * @retval std::string Type of IR Operator object
	 */
	std::string getType();

	/**
	 * @brief Sets the opcode of IR Operator object
	 *
	 * @param[in] opcode Opcode of IR Operator object
	 */
	void setOpcode(const std::string &opcode);

	/**
	 * @brief Gets the opcode of IR Operator object
	 *
	 * @retval std::string Opcode of IR Operator object
	 */
	std::string getOpcode();

	/**
	 * @brief Sets the subname of IR Operator object
	 *
	 * @param[in] subname Subname of IR Operator object
	 */
	void setSubname(const std::string &subname);

	/**
	 * @brief Gets the subname of IR Operator object
	 *
	 * @retval std::string subname of IR Operator object
	 */
	std::string getSubname();

	/**
	 * @brief Sets the subpath of IR Operator object
	 *
	 * @param[in] subpath Subpath of IR Operator object
	 */
	void setSubpath(const std::string &subpath);

	/**
	 * @brief Gets the subpath of IR Operator object
	 *
	 * @retval std::string subpath of IR Operator object
	 */
	std::string getSubpath();
private:
	std::string id = "";	  /* Unique IR Operator identifier */
	std::string type = "";	  /* Complex or Terminal type of IR Operator */
	std::string opcode = "";  /* Opcode of IR Operator object */
	std::string subname = ""; /* Name of subprogram for complex operator */
	std::string subpath = ""; /* Path of subprogram for complex operator*/
};

#endif //  IR_OPERATOR_H
