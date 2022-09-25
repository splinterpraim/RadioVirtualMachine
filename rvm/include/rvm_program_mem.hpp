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

    /**
     * @brief Returns the value (Byte) at the specified address
     * 
     * @param addr Address in memory
     * @return value  
     */
    uint8_t get(uint64_t addr);

    /**
     * @brief Get the size of program memory
     * 
     * @return size of program memory
     */
    uint64_t getSize();

private:
    uint64_t _size = 0;
    uint64_t _capacity = 0;
    uint8_t *mem = nullptr;


    uint8_t * getPtrOnFreeSpace(uint64_t size);
    bool hasFreeSpace(uint64_t size);
    uint8_t * reallocateMem(uint64_t size);
};

#endif // RVM_PROGRAM_MEM_CLASS