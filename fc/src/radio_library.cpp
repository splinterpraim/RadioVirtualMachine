#include "radio_library.hpp"


// need different opcodes for typisation
// what needs to do for complex operators (now there is no opcode for them)

RadioLibrary::RadioLibrary()
{
    opCodeTable[2] = {2,1}; 
    opCodeTable[1] = {2,1};
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
