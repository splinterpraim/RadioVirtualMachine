#ifndef IR_OPERATOR_H
#define IR_OPERATOR_H

#include <iostream>
#include <string>

class IrOperator{

public:
	IrOperator(){}
	~IrOperator(){}
	void setId(const std::string &id);
	std::string getId();
    void setType (const std::string &type);
    std::string getType();
private:
	std::string id = "";
	std::string type = "";
};

#endif //  IR_OPERATOR_H
