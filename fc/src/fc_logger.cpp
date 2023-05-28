
#include "fc_logger.hpp"

std::string fcLoggerStr(const char* format, ...)
{
    std::string str;
    va_list args;
    char buffer[FC_LOGGER_MAX_STRING] = {0};
    va_start(args, format);
    if(vsnprintf(buffer, sizeof(buffer), format, args) > 0)
    {
        str = buffer;
    }
    va_end(args);
    return str;
}
