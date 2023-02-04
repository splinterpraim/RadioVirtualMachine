/**
 * @file ir_data.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Intermediate representation of data
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef IR_DATA_H
#define IR_DATA_H
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;
/**
 * @brief Class for describing of Intermediate representation data
 */
class IrData
{

public:
    IrData() {}
    ~IrData() {}

    void setId(const string &id);
    string getId();

    void setType(const int &type);
    int getType();

    void setPath(const string &path);
    string getPath();

    void setAccessTime(const string &accessTime);
    string getAccessTime();

    void setValue(const string &value);
    string getValue();

    /* Overload */
    bool operator==(const IrData &rData);

private:
    string id = "";
    int type = 0;
    string path = "";
    string accessTime = "";
    string value = "";
};
#endif // IR_DATA_H
