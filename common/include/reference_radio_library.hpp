/**
 * @file reference_radio_library.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Reference Radio Library
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef REFERENCE_RADIO_LIBRARY_HPP
#define REFERENCE_RADIO_LIBRARY_HPP

#include <cstdint>
#include <cstdarg>

#define RL_MAX_PORT_SIZE 7
#define RL_ENABLE true
#define RL_DISABLE false
#define RL_INPUT_PORT false
#define RL_OUTPUT_PORT true

enum RL_TYPES
{
    rlt_none = 0,
    rlt_bool = 1,
    rlt_int8,
    rlt_int16,
    rlt_int32,
    rlt_int64,
    rlt_uint8,
    rlt_uint16,
    rlt_uint32,
    rlt_uint64,
    rlt_float,
    rlt_double,

    RL_TYPES_SIZE
};

enum RL_OPCODES
{
    rl_opcode_1 = 1,
    rl_opcode_2,
    rl_opcode_3,
    rl_opcode_4,
    rl_opcode_5,
    rl_opcode_6,
    rl_opcode_7,
    rl_opcode_8,
    rl_opcode_9,
    rl_opcode_10,
    rl_opcode_11,
    rl_opcode_12,
    rl_opcode_13,
    rl_opcode_14,
    rl_opcode_15,
    rl_opcode_16,
    rl_opcode_17,
    rl_opcode_18,
    rl_opcode_19,
    rl_opcode_20,
    rl_opcode_21,
    rl_opcode_22,
    rl_opcode_23,
    rl_opcode_24,
    rl_opcode_25,
    rl_opcode_26,
    rl_opcode_27,
    rl_opcode_28,
    rl_opcode_29,
    rl_opcode_30,
    rl_opcode_31,
    rl_opcode_32,
    rl_opcode_33,
    rl_opcode_34,

    RL_OPCODES_SIZE
};
#define RL_SIZE RL_OPCODES_SIZE - 1

/**
 * @brief Description of Input/Output arguments of Radio Library functions
 */
typedef struct
{
    int inNum;              /* Number of input arguments */
    int outNum;             /* Number of output arguments */
    uint8_t ** inPorts;     /* Pointer on input arguments array */
    uint8_t ** outPorts;    /* Pointer on output arguments array */
} rl_ArgArray;

typedef int (*rl_operator_fn)(rl_ArgArray &);

struct radioLibrary_el
{
    const char * name;
    uint32_t opcode;
    uint16_t cost;
    uint16_t time;

     struct {
        bool infinityInPorts;
        bool infinityOutPorts;
        uint8_t typeOfInData;
        uint8_t typeOfOutData;
    } flags;

    rl_operator_fn fn;

    typedef struct {
        bool dir;
        uint8_t typeOfData;
        bool fFilled;
    } port_t;
    port_t ports[RL_MAX_PORT_SIZE];

   

};
using radioLibrary_el = struct radioLibrary_el;

extern radioLibrary_el const referenceRadioLibrary[RL_SIZE];


radioLibrary_el const* rl_getOperator(uint32_t opcode);

uint8_t rl_getInputPortCnt(uint32_t opcode);

uint8_t rl_getOutputPortCnt(uint32_t opcode);



#endif // REFERENCE_RADIO_LIBRARY_HPP