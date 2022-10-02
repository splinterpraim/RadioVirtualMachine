#include "radio_library.hpp"

RadioLibrary::RadioLibrary()
{
    opCodeTable["mult1"] = 1;
    opCodeTable["mult2"] = 2;
    opCodeTable["add"] = 3;
}

int RadioLibrary::getOpCode(std::string operatorId)
{
    // todo: exception hendler
    return opCodeTable[operatorId];
}
