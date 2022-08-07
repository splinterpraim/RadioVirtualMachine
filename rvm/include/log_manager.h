#ifndef LOG_MANAGER_CLASS
#define LOG_MANAGER_CLASS
#include <iostream>
#include <fstream>
#include <string>

class LogManager
{
    std::string filename = "";

public:
    LogManager() = default;
    LogManager(std::string filename) { this->filename = filename; }
    void makeLog(std::string log)
    {
        if (filename == "")
        {
            std::cout << log << std::endl;
        }
        else
        {
            std::ofstream file(filename, std::ios_base::app);
            file << log << std::endl;
            file.close();
        }
    }
    void clear()
    {
        std::ofstream file(filename);
        file.close();
    }
};
#endif // LOG_MANAGER_CLASS
