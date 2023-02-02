#ifndef IR_OPERATOR_H
#define IR_OPERATOR_H

#include <iostream>
#include <string>

/**
 * @brief Class for describing of Intermediate representation operator
 *
 */
class IrOperator
{

public:
	IrOperator() {}

	~IrOperator() {}

	void setId(const std::string &id);

	std::string getId();

	void setType(const std::string &type);

	std::string getType();

	void setOpcode(const std::string &opcode);
	
	std::string getOpcode();

private:
	std::string id = "";
	std::string type = "";
	std::string opcode = "";
};

#endif //  IR_OPERATOR_H
