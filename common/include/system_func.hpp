#ifndef SYSTEM_FUNC_HPP
#define SYSTEM_FUNC_HPP

/**
 * @brief Checks whether the endian in the system is little
 * 
 * @retval true - Little endian
 * @retval false - Big endian
 */
bool endianIsLittle();

/**
 * @brief Reverses byte order
 * 
 * @param val Input value
 * @return Reversed value
 */
int reverseEndian(int val);

#endif // SYSTEM_FUNC_HPP