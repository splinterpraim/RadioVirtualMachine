#ifndef RADIO_LIBRARY_HPP
#define RADIO_LIBRARY_HPP
#include <iostream>
#include <string>
#include <map>

class RadioLibrary
{

public:
    RadioLibrary();
    int getOpCode(std::string operatorId);

private:
    std::map<std::string, int> opCodeTable;

};
#endif // RADIO_LIBRARY_HPP