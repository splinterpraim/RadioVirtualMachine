/**
 * @file ir_data.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Intermediate representation of data
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef IR_DATA_H
#define IR_DATA_H

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

/**
 * @brief Class for describing of Intermediate representation data
 */
class IrData
{

public:
    /**
     * @brief Construct a new IR Data object
     */
    IrData() {}

    /**
     * @brief Destroys the IR Data object
     */
    ~IrData() {}

    /**
     * @brief Sets the ID of IR Data object
     *
     * @param[in] id ID of IR Data object
     */
    void setId(const string &id);

    /**
     * @brief Gets the ID of IR Data object
     *
     * @retval string ID of IR Data object
     */
    string getId();

    /**
     * @brief Sets the type of IR Data object
     *
     * @param[in] type Type of IR Data object
     */
    void setType(int type);

    /**
     * @brief Gets the type of IR Data object
     *
     * @retval int Type of IR Data object
     */
    int getType();

    /**
     * @brief Sets the path of IR Data object
     *
     * @param[in] path Path of IR Data object
     */
    void setPath(const string &path);

    /**
     * @brief Gets the path of IR Data object
     *
     * @retval string Path of IR Data object
     */
    string getPath();

    /**
     * @brief Sets the access time of IR Data object
     *
     * @param[in] accessTime Access time of IR Data object
     */
    void setAccessTime(const string &accessTime);

    /**
     * @brief Gets the access time of IR Data object
     *
     * @retval string Access time of IR Data object
     */
    string getAccessTime();

    /**
     * @brief Sets the value of IR Data object
     *
     * @param[in] value Value of IR Data object
     */
    void setValue(const string &value);

    /**
     * @brief Gets the value of IR Data object
     *
     * @retval string Value of IR Data object
     */
    string getValue();

    /**
     * @brief Sets the external data flag of IR Data object
     *
     * @param[in] value Value of IR Data object
     */
    void setExternal(bool external);

    /**
     * @brief Gets the external data flag of IR Data object
     *
     * @retval string Value of IR Data object
     */
    bool getExternal();

    /**
     * @brief Overload operator == for comparing IR Data objects
     *
     * @param[in] rData The right operand of the IR Data type
     *
     * @retval true IR Data is equal
     * @retval false IR Data is not equal
     */
    bool operator==(const IrData &rData);

private:
    string id = "";         /* Unique IR Data identifier */
    int type = 0;           /* Type of IR Data value */
    string path = "";       /* Path to file with IR Data value */
    string accessTime = ""; /* IR Data access time  */
    string value = "";      /* IR Data value */
    bool external = 0;      /* External data flag */
};

#endif // IR_DATA_H
