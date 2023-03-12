/**
 * @file radio_library.cpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Reference Radio Library
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "radio_library.hpp"
#include <exception>
#include <stdexcept>

#include "common.hpp"

#define LINK_INPUT 0
#define LINK_OUTPUT 1

// #define RL_TYPE_INT 0
// #define RL_TYPE_FLOAT 1
// #define RL_TYPE_STRING 2
// need different opcodes for typisation (Int32, int16 and etc)
// what needs to do for complex operators (now there is no opcode for them)

RadioLibrary::RadioLibrary()
{
    rl_Operator addInt;
    {
        addInt.name = "additionInt";
        addInt.opcode = 1;
        addInt.cost = 10;
        addInt.time = 10;
        addInt.ports.in.push_back({1, RL_TYPE_INT});
        addInt.ports.in.push_back({2, RL_TYPE_INT});
        addInt.ports.out.push_back({3, RL_TYPE_INT});
    }
    operators.push_back(addInt);

    rl_Operator addFloat;
    {
        addFloat.name = "additionFloat";
        addFloat.opcode = 2;
        addFloat.cost = 10;
        addFloat.time = 10;
        addFloat.ports.in.push_back({1, RL_TYPE_FLOAT});
        addFloat.ports.in.push_back({2, RL_TYPE_FLOAT});
        addFloat.ports.out.push_back({3, RL_TYPE_FLOAT});
    }
    operators.push_back(addFloat);

    rl_Operator multInt;
    {
        multInt.name = "multipicationInt";
        multInt.opcode = 3;
        multInt.cost = 10;
        multInt.time = 10;
        multInt.ports.in.push_back({1, RL_TYPE_INT});
        multInt.ports.in.push_back({2, RL_TYPE_INT});
        multInt.ports.out.push_back({3, RL_TYPE_INT});
    }
    operators.push_back(multInt);

    rl_Operator multFloat;
    {
        multFloat.name = "multipicationFloat";
        multFloat.opcode = 4;
        multFloat.cost = 10;
        multFloat.time = 10;
        multFloat.ports.in.push_back({1, RL_TYPE_FLOAT});
        multFloat.ports.in.push_back({2, RL_TYPE_FLOAT});
        multFloat.ports.out.push_back({3, RL_TYPE_FLOAT});
    }
    operators.push_back(multFloat);

    rl_Operator AdderInt;
    {
        AdderInt.name = "AdderInt";
        AdderInt.opcode = 5;
        AdderInt.cost = 10;
        AdderInt.time = 10;
        AdderInt.ports.fInfinityInPorts = RL_YES;
        AdderInt.ports.in.push_back({0, RL_TYPE_INT}); // todo: fix, because not work for undefined num of inputs
        AdderInt.ports.out.push_back({3, RL_TYPE_INT});
    }
    operators.push_back(AdderInt);
}

rl_Operator RadioLibrary::findByOpCode(int opcode)
{
    for (auto &oneOp : operators)
    {
        if (oneOp.opcode == opcode)
        {
            return oneOp;
        }
    }

    rl_Operator nullOp;
    return nullOp;
}

IOPortsCnt RadioLibrary::getIOPortsCnt(int opcode)
{
    for (auto &oneOp : operators)
    {
        if (oneOp.opcode == opcode)
        {
            IOPortsCnt cntPorts;
            if (oneOp.ports.fInfinityInPorts == RL_YES)
            {
                cntPorts.input = RL_PORTS_INF;
                cntPorts.output = (int)oneOp.ports.out.size();
            }
            else
            {
                cntPorts.input = (int)oneOp.ports.in.size();
                cntPorts.output = (int)oneOp.ports.out.size();
            }
            return cntPorts;
        }
    }

    throw std::runtime_error(FC_ERR_STR("Operator not found!"));
}
