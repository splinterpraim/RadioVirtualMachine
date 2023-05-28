/**
 * @file ir_link.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Intermediate representation of link
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef IR_LINK_H
#define IR_LINK_H

#include <iostream>
#include <string>
#include "reference_radio_library.hpp"

/**
 * @brief Class for describing of Intermediate representation links
 */
class IrLink{
public:

	/**
	 * @brief Constructs a new IR Link object
	 */
	IrLink(){};

	/**
	 * @brief Constructs a new IR Link object with using parameters 
	 * 
	 * @param[in] dataId     IR Data ID
	 * @param[in] operatorId IR Operator ID
	 * @param[in] dir 		 Direction from data to operator
	 * @param[in] dataOrder  The order of the data in relation to the operator 
	 */
	IrLink(std::string dataId, std::string operatorId, int dir, int dataOrder)
			:dataId(dataId), dataOrder(dataOrder), operatorId(operatorId), dir(dir) 
			{};

	/**
	 * @brief Sets the IR Data ID 
	 * 
	 * @param[in] dataId IR Data ID
	 */
	void setDataId(std::string dataId);

	/**
	 * @brief Sets the order of the data in relation to the operator 
	 * 
	 * @param[in] dataOrder The order of the data in relation to the operator
	 */
	void setDataOrder(int dataOrder);

	/**
	 * @brief Sets the IR Operator ID
	 * 
	 * @param[in] operatorId IR Operator ID
	 */
	void setOperatorId(std::string operatorId);

	/**
	 * @brief Sets the direction from data to operator
	 * 
	 * @param[in] dir Direction from data to operator
	 */
	void setDir(int dir);

	/**
	 * @brief Gets the IR Data ID
	 * 
	 * @retval std::string IR Data ID
	 */
    std::string getDataId();

	/**
	 * @brief Gets the order of the data in relation to the operator
	 * 
	 * @retval int The order of the data in relation to the operator
	 */
    int getDataOrder();

	/**
	 * @brief Gets the IR Operator ID
	 * 
	 * @retval std::string IR Operator ID
	 */
	std::string getOperatorId();

	/**
	 * @brief Gets the direction from data to operator
	 * 
	 * @retval int Direction from data to operator
	 */
	int getDir();

	/**
	 * @brief Converts IR Link to string
	 * 
	 * @retval std::string IR Link as string
	 */
	std::string to_str(); 

private:
    std::string dataId; 	/* IR Data ID */
    int dataOrder; 			/* Order of the data in relation to the operator */
	std::string operatorId; /* IR Operator ID */
	int dir;				/* Direction from data to operator.
				   			   RL_INPUT_PORT - from data to operator (input)
				   			   RL_INPUT_PORT - from operator to data (output) */
};
#endif // IR_LINK_H
