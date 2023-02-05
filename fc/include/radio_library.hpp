/**
 * @file radio_library.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Reference Radio Library
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

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
    int opcode;

    struct OpPort
    {
        int num;    /* Number of port */
        int type;   /* Type of data */
    };
    using OpPort = struct OpPort;
    
    struct Ports_s
    {
        std::vector<OpPort> in;
        std::vector<OpPort> out;

    }ports;

    uint16_t cost;
    uint16_t time;
};
using rl_Operator = struct rl_Operator_s;

/**
 * @brief Class for describing of Reference Radio Library
 */
class RadioLibrary
{

public:
    /**
     * @brief Constructs a new Radio Library object
     */
    RadioLibrary();

    /**
     * @brief Finds by opcode corresponding description of the operator in Radio Library
     * 
     * @param[in] opcode Opcode of operator
     * 
     * @retval rl_Operator Description of the operator in Radio Library
     */
    rl_Operator findByOpCode(int opcode);

    /**
     * @brief Gets the amount of input and output ports of operator 
     * 
     * @param[in] opcode Opcode of operator
     * 
     * @retval IOPortsCnt Amount of input and output ports of operator
     */
    IOPortsCnt getIOPortsCnt(int opcode);

private:
    std::vector<rl_Operator> operators; /* Vector of operators from Radio Library */
};

#endif // RADIO_LIBRARY_HPP