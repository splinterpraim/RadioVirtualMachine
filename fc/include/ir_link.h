#ifndef IR_LINK_H
#define IR_LINK_H
#include <iostream>
#include <string>

class IrLink{
public:

	/* Constructors */
	IrLink(){};
	IrLink(std::string dataId, std::string operatorId, int dir, int dataOrder)
			:dataId(dataId), operatorId(operatorId), dir(dir), dataOrder(dataOrder)
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
	int dir;	/* 0 - from data to operator (input)
				   1 - from operator to data (output) */
};
#endif // IR_LINK_H
