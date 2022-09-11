#ifndef RVM_PROGRAM_MEM_CLASS
#define RVM_PROGRAM_MEM_CLASS

#include <string>
#include <cstdint>
#include "config_code_structure.hpp"

class rvm_ProgramMemory
{
public:
    rvm_ProgramMemory();
    rvm_ProgramMemory(uint64_t initSize);
    ~rvm_ProgramMemory();

    /**
     * @brief Initializes the program memory. Allocates memory of a certain size.
     *
     * @param initSize Allocated memory size
     */
    void init(uint64_t initSize);

    /**
     * @brief Loads config code file since next free cell
     * 
     * @param fileName The name of the file that contains the configuration code
     * @return Number of bytes downloaded
     */
    uint64_t load(std::string fileName);

    uint8_t get(uint64_t addr);

private:
    uint64_t _size;
    uint8_t *mem;
};

#endif // RVM_PROGRAM_MEM_CLASS