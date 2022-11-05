#ifndef RADIO_LIBRARY_HPP
#define RADIO_LIBRARY_HPP
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct IOPortsCnt_s
{
    int input;
    int output;
};
using IOPortsCnt = struct IOPortsCnt_s;

struct rl_Operator_s
{
    std::string name;
    struct Opcode_s
    {
        int opClass; /* Code of operation */
        int opSubClass; /* Code of data type for operator processing */
    } opcode;

    struct OpPort
    {
        int num; /* Number of port */
        int type; /* Type of data */
        int direct; /* Data input or output */
    };  
    using OpPort = struct OpPort;
    std::vector<OpPort> ports;

    uint16_t cost;
    uint16_t time;
};
using rl_Operator = struct rl_Operator_s;



class RadioLibrary
{

public:
    RadioLibrary();

    rl_Operator findByOpCode(int opcode);

    int getOpCode(std::string operatorId);
    IOPortsCnt getIOPortsCnt(int opcode);

private:
    std::vector<rl_Operator> operators;

    uint32_t concatOpCode(int opClass, int opSubClass);
    // std::map<int, IOPortsCnt> opCodeTable;
};
#endif // RADIO_LIBRARY_HPP