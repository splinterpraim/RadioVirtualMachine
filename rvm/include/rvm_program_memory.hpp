/**
 * @file rvm_program_memory.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Program Memory
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_PROGRAM_MEM_CLASS
#define RVM_PROGRAM_MEM_CLASS

#include <string>
#include <cstdint>

/**
 * @brief Program Memory Block implementation
 */
class rvm_ProgramMemory
{
public:

    /**
     * @brief Constructs a new rvm ProgramMemory object
     */
    rvm_ProgramMemory();

    /**
     * @brief Constructs a new rvm ProgramMemory object and initializes memory of a certain size
     *
     * @param[in]       initSize                Memory size to allocate
     */
    rvm_ProgramMemory(uint64_t initSize);

    /**
     * @brief Destroys the rvm ProgramMemory object
     */
    ~rvm_ProgramMemory();

    /**
     * @brief Initializes the program memory. Allocates memory of a certain size.
     *
     * @param[in]       initSize                Memory size to allocate
     */
    void init(uint64_t initSize);

    /**
     * @brief Loads config code file since next free cell
     *
     * @param[in]       fileName                The name of the file that contains the configuration code
     *
     * @retval          uint64_t                Number of bytes downloaded
     */
    uint64_t load(std::string fileName);

    /**
     * @brief Returns the value of byte at the specified address
     *
     * @param[in]       addr                    Address in memory
     *
     * @retval          uint8_t                 Value of byte
     */
    uint8_t get(uint64_t addr);

    /**
     * @brief Gets the size of program memory
     *
     * @retval          uint64_t                Size of program memory
     */
    uint64_t getSize();

private:

    uint64_t size_ = 0;         /* Real memory size */
    uint64_t capacity_ = 0;     /* Allocated memory size */
    uint8_t *mem = nullptr;     /* Pointer to first cell of memory array */

    /**
     * @brief Gets a pointer to a free space in memory of the required size
     *
     * @param[in]       size                    Required memory size
     *
     * @retval          uint8_t*                Pointer to free space in memory 
     */
    uint8_t * getPtrOnFreeSpace(uint64_t size);

    /**
     * @brief Checks if there is free memory of the required size 
     *
     * @param[in]       size                     Required memory size
     *
     * @retval          true                     There is free memory space
     * @retval          false                    No free memory space
     */
    bool hasFreeSpace(uint64_t size);

    /**
     * @brief Reallocates memory by adding the required size
     *
     * @param[in]       size                    Required size to adding
     *
     * @retval          uint8_t*                Pointer to first cell of reallocated memory array
     */
    uint8_t * reallocateMem(uint64_t size);
};

#endif // RVM_PROGRAM_MEM_CLASS