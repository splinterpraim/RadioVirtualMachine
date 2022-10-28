#ifndef RADIO_LIBRARY_HPP
#define RADIO_LIBRARY_HPP
#include <iostream>
#include <string>
#include <map>

struct IOPortsCnt_s
{
    int input;
    int output;
};
using IOPortsCnt = struct IOPortsCnt_s;

class RadioLibrary
{

public:
    RadioLibrary();
    int getOpCode(std::string operatorId);
    IOPortsCnt getIOPortsCnt(int opcode);

private:
    std::map<int, IOPortsCnt> opCodeTable;

};
#endif // RADIO_LIBRARY_HPP