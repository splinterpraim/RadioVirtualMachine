#include "radio_library.hpp"

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
