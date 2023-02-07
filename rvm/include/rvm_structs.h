/**
 * @file rvm_structs.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Status structs and enums
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_STRUCTS_HPP
#define RVM_STRUCTS_HPP

#include <cstdint>
#include <string>

/**
 * @brief Data Object states
 */
enum stDO
{
    empty = 0,  /* No data in Data Object */
    full        /* Data Object filled with data */
};

/**
 * @brief Data Object Exceptions enum
 */
enum exDO
{
    NOEXCEPT = 0,       /* No exceptions */
    OP_WITH_BIGSIZE,    /* Operation with a size greater than the size of the Data object */
    WRITE_CONFL,        /* Conflicting writes */
    READ_ERASE_CONFL    /* Conflicting read-erase operation */
};

/**
 * @brief Abstract Processing Element states
 */
enum stAPE
{
    inactive,   /* Doesn't perform an operation */
    active      /* Performs an operation */
};

/**
 * @brief Access type for Data Object
 */
namespace at
{
    /**
     * @brief Access type for Data Object enum
     */
    enum
    {
        read,       /* Read data from Data Object */
        write,      /* Written data in Data Object */
        readErase   /* Read and Erase data from Data Object */
    };
}

/**
 * @brief Status of Data Object
 */
struct StatusFromDataObject
{
    uint8_t id : 8;         /* Unique Data Object identifier */
    uint8_t state : 1;      /* State of Data Object -> stDO::empty, stDO::full */
    uint8_t accessType : 2; /* Access type of Data Object -> at::read, at::write, at::readErase */
    uint8_t exception : 2;  /* Exeption of Data Object */

    /**
     * @brief Converts StatusFromDataObject to string
     *
     * @retval          std::string             StatusFromDataObject as string
     */
    std::string to_str() const
    {
        std::string result_str = "id " + std::to_string(id) + ", " +
                                 "state " + std::to_string(state) + ", " +
                                 "accessType " + std::to_string(accessType) + ", " +
                                 "exception " + std::to_string(exception);
        return result_str;
    }
};

/**
 * @brief Status of Abstract Processing Element
 */
struct StatusFromAbstractProcessingElement
{
    uint16_t id : 16;       /* Unique Abstract Processing Element identifier */
    uint8_t state : 1;      /* State of Abstract Processing Element -> stAPE::inactive, stAPE::active */
    uint8_t exception : 2;  /* Exeption of Abstract Processing Element */

    /**
     * @brief Converts StatusFromAbstractProcessingElement to string
     *
     * @retval          std::string             StatusFromAbstractProcessingElement as string
     */
    std::string to_str() const
    {
        std::string result_str = "id " + std::to_string(id) + ", " +
                                 "state " + std::to_string(state) + ", " +
                                 "exception " + std::to_string(exception);
        return result_str;
    }
};

#endif // RVM_STRUCTS_HPP
