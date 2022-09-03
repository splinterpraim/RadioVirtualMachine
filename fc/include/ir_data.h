#ifndef IR_DATA_H
#define IR_DATA_H
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

class IrData {

public:
	IrData(){}
	~IrData(){}
	void setId(const string &id);
	string getId();

    void setType(const string &type);
    string getType();

    void setPath(const string &path);
    string getPath();

    void setAccessTime(const string &accessTime);
    string getAccessTime();

    void setValue(const string &value);
    string getValue();

//    ----


	/* Overload */
	bool operator==(const IrData & rData);
private:
	string id = "";
	string type = "";
	string path = "";
    string accessTime = "";
    string value = "";


};
#endif // IR_DATA_H

