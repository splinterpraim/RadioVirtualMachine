#include "radio_library.hpp"

#define LINK_INPUT 0
#define LINK_OUTPUT 1

#define RL_TYPE_INT 0
#define RL_TYPE_FLOAT 1
#define RL_TYPE_STRING 2
// need different opcodes for typisation
// what needs to do for complex operators (now there is no opcode for them)

RadioLibrary::RadioLibrary()
{
    rl_Operator mult;
    mult.name = "multipication";
    mult.cost = 10;
    mult.time = 10;
    mult.ports.push_back({1, RL_TYPE_INT, LINK_INPUT});
    operators.push_back();
    // opCodeTable[2] = {2,1};
    // opCodeTable[1] = {2,1};
}

int RadioLibrary::getOpCode(std::string operatorId)
{
    // todo: exception hendler
    return 0;
}

IOPortsCnt RadioLibrary::getIOPortsCnt(int opcode)
{
    return opCodeTable[opcode];
}
