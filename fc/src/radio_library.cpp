#include "radio_library.hpp"
#include "common.hpp"

#define LINK_INPUT 0
#define LINK_OUTPUT 1

// #define RL_TYPE_INT 0
// #define RL_TYPE_FLOAT 1
// #define RL_TYPE_STRING 2
// need different opcodes for typisation
// what needs to do for complex operators (now there is no opcode for them)

RadioLibrary::RadioLibrary()
{
    rl_Operator addInt;
    {
        addInt.name = "additionInt";
        addInt.opcode.opClass = 1;
        addInt.opcode.opSubClass = 1;
        addInt.cost = 10;
        addInt.time = 10;
        addInt.ports.push_back({1, RL_TYPE_INT, LINK_INPUT});
        addInt.ports.push_back({2, RL_TYPE_INT, LINK_INPUT});
        addInt.ports.push_back({3, RL_TYPE_INT, LINK_OUTPUT});
    }
    operators.push_back(addInt);

    rl_Operator addFloat;
    {
        addFloat.name = "additionFloat";
        addFloat.opcode.opClass = 1;
        addFloat.opcode.opSubClass = 2;
        addFloat.cost = 10;
        addFloat.time = 10;
        addFloat.ports.push_back({1, RL_TYPE_FLOAT, LINK_INPUT});
        addFloat.ports.push_back({2, RL_TYPE_FLOAT, LINK_INPUT});
        addFloat.ports.push_back({3, RL_TYPE_FLOAT, LINK_OUTPUT});
    }
    operators.push_back(addFloat);

    rl_Operator multInt;
    {
        multInt.name = "multipicationInt";
        multInt.opcode.opClass = 2;
        multInt.opcode.opSubClass = 1;
        multInt.cost = 10;
        multInt.time = 10;
        multInt.ports.push_back({1, RL_TYPE_INT, LINK_INPUT});
        multInt.ports.push_back({2, RL_TYPE_INT, LINK_INPUT});
        multInt.ports.push_back({3, RL_TYPE_INT, LINK_OUTPUT});
    }
    operators.push_back(multInt);

    rl_Operator multFloat;
    {
        multFloat.name = "multipicationFloat";
        multFloat.opcode.opClass = 2;
        multFloat.opcode.opSubClass = 2;
        multFloat.cost = 10;
        multFloat.time = 10;
        multFloat.ports.push_back({1, RL_TYPE_FLOAT, LINK_INPUT});
        multFloat.ports.push_back({2, RL_TYPE_FLOAT, LINK_INPUT});
        multFloat.ports.push_back({3, RL_TYPE_FLOAT, LINK_OUTPUT});
    }
    operators.push_back(multFloat);

    // opCodeTable[2] = {2,1};
    // opCodeTable[1] = {2,1};
}

rl_Operator RadioLibrary::findByOpCode(int opcode)
{
    for(auto &oneOp : operators)
    {
        if(concatOpCode(oneOp.opcode.opClass, oneOp.opcode.opSubClass) == opcode) //concat
        {
            return oneOp;
        }
    }

    rl_Operator nullOp;
    return nullOp;
}


int RadioLibrary::getOpCode(std::string operatorId)
{
    // todo: exception hendler
    return 0;
}

IOPortsCnt RadioLibrary::getIOPortsCnt(int opcode)
{
    // return opCodeTable[opcode];
}


/* Private */
uint32_t RadioLibrary::concatOpCode(int opClass, int opSubClass)
{
    int res = opSubClass & 0x03ff; /* 0000 0011 1111 1111 */  
    res |= (opClass & 0x03ff) << 10;
    return res;
}
