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

#define LINK_INPUT 0 
#define LINK_OUTPUT 1

/**
 * @brief Class for describing of Intermediate representation links
 * 
 */
class IrLink{
public:

	/* Constructors */
	IrLink(){};
	IrLink(std::string dataId, std::string operatorId, int dir, int dataOrder)
			:dataId(dataId), dataOrder(dataOrder), operatorId(operatorId), dir(dir) 
			{};

	/* Setters */
	void setDataId(std::string dataId);
	void setDataOrder(int dataOrder);
	void setOperatorId(std::string operatorId);
	void setDir(int dir);

	/* Getters */
    std::string getDataId();
    int getDataOrder();
	std::string getOperatorId();
	int getDir();

	/* To string */
	std::string to_str();
private:
    std::string dataId;
    int dataOrder;
	std::string operatorId;
	int dir;	/* LINK_INPUT - from data to operator (input)
				   LINK_OUTPUT - from operator to data (output) */
};
#endif // IR_LINK_H
