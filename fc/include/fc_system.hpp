
#ifndef FC_SYSTEM_HPP
#define FC_SYSTEM_HPP

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

#endif // FC_SYSTEM_HPP