/**
 * @file reference_radio_library.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Function for Reference Radio Library
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "reference_radio_library.hpp"

radioLibrary_el const referenceRadioLibrary[RL_SIZE] = {

/* Arithmetic operators */

    /* Addition */
    { "add_bool", rl_opcode_1, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_bool, rlt_bool},
        { 
            {RL_INPUT_PORT,  rlt_bool, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_bool, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_bool, RL_ENABLE }
        }
    },
    { "add8i", rl_opcode_2, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int8, rlt_int8},
        { 
            {RL_INPUT_PORT,  rlt_int8, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int8, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int8, RL_ENABLE }
        }
    },
    { "add16i", rl_opcode_3, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int16, rlt_int16},
        { 
            {RL_INPUT_PORT,  rlt_int16, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int16, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int16, RL_ENABLE }
        }
    },
    { "add32i", rl_opcode_4, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },
    { "add64i", rl_opcode_5, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int64, rlt_int64},
        { 
            {RL_INPUT_PORT,  rlt_int64, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int64, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int64, RL_ENABLE }
        }
    },
    { "add8u", rl_opcode_6, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_uint8, rlt_uint8},
        { 
            {RL_INPUT_PORT,  rlt_uint8, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_uint8, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_uint8, RL_ENABLE }
        }
    },
    { "add16u", rl_opcode_7, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_uint16, rlt_uint16},
        { 
            {RL_INPUT_PORT,  rlt_uint16, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_uint16, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_uint16, RL_ENABLE }
        }
    },
    { "add32u", rl_opcode_8, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_uint32, rlt_uint32},
        { 
            {RL_INPUT_PORT,  rlt_uint32, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_uint32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_uint32, RL_ENABLE }
        }
    },
    { "add64u", rl_opcode_9, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_uint64, rlt_uint64},
        { 
            {RL_INPUT_PORT,  rlt_uint64, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_uint64, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_uint64, RL_ENABLE }
        }
    },
    { "addf", rl_opcode_10, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_float, rlt_float},
        { 
            {RL_INPUT_PORT,  rlt_float, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_float, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_float, RL_ENABLE }
        }
    },
    { "add_dbl", rl_opcode_11, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_double, rlt_double},
        { 
            {RL_INPUT_PORT,  rlt_double, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_double, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_double, RL_ENABLE }
        }
    },


    /* Multiplication */
    { "mult_bool", rl_opcode_12, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_bool, rlt_bool},
        { 
            {RL_INPUT_PORT,  rlt_bool, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_bool, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_bool, RL_ENABLE }
        }
    },
    { "mult8i", rl_opcode_13, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int8, rlt_int8},
        { 
            {RL_INPUT_PORT,  rlt_int8, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int8, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int8, RL_ENABLE }
        }
    },
    { "mult16i", rl_opcode_14, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int16, rlt_int16},
        { 
            {RL_INPUT_PORT,  rlt_int16, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int16, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int16, RL_ENABLE }
        }
    },
    { "mult32i", rl_opcode_15, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },
    { "mult64i", rl_opcode_16, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int64, rlt_int64},
        { 
            {RL_INPUT_PORT,  rlt_int64, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int64, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int64, RL_ENABLE }
        }
    },
    { "mult8u", rl_opcode_17, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_uint8, rlt_uint8},
        { 
            {RL_INPUT_PORT,  rlt_uint8, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_uint8, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_uint8, RL_ENABLE }
        }
    },
    { "mult16u", rl_opcode_18, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_uint16, rlt_uint16},
        { 
            {RL_INPUT_PORT,  rlt_uint16, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_uint16, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_uint16, RL_ENABLE }
        }
    },
    { "mult32u", rl_opcode_19, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_uint32, rlt_uint32},
        { 
            {RL_INPUT_PORT,  rlt_uint32, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_uint32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_uint32, RL_ENABLE }
        }
    },
    { "mult64u", rl_opcode_20, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_uint64, rlt_uint64},
        { 
            {RL_INPUT_PORT,  rlt_uint64, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_uint64, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_uint64, RL_ENABLE }
        }
    },
    { "multf", rl_opcode_21, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_float, rlt_float},
        { 
            {RL_INPUT_PORT,  rlt_float, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_float, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_float, RL_ENABLE }
        }
    },
    { "mult_dbl", rl_opcode_22, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_double, rlt_double},
        { 
            {RL_INPUT_PORT,  rlt_double, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_double, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_double, RL_ENABLE }
        }
    },


/* Others operators */
    /* Complex Addition */
    { "addMultiIn_32i", rl_opcode_23, 10, 10, {RL_ENABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },
    /* Copy */
    { "copy_32i", rl_opcode_24, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },

    /* Copy on sig*/
    { "copyOnSig_32i", rl_opcode_30, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_bool,  RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },

    /* Delay */
    { "z_32i", rl_opcode_25, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },
    /* Move */
    { "move_32i", rl_opcode_26, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },

    { "moveGenSig_32i", rl_opcode_27, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },

    { "moveOnSig_32i", rl_opcode_28, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },

    { "FIR_order_2_32i", rl_opcode_29, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },

    { "cmp_32i", rl_opcode_31, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_bool, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_bool, RL_ENABLE }
        }
    },

    { "iterator_32i", rl_opcode_32, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_bool, RL_ENABLE },
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_bool, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_bool, RL_ENABLE }
        }
    },

    { "sendSignal_32i", rl_opcode_33, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_int32, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_bool, RL_ENABLE }
        }
    },

    { "generatorRandom_32i", rl_opcode_34, 10, 10, {RL_DISABLE, RL_DISABLE, rlt_int32, rlt_int32},
        { 
            {RL_INPUT_PORT,  rlt_bool, RL_ENABLE },
            {RL_OUTPUT_PORT, rlt_int32, RL_ENABLE }
        }
    },
};

radioLibrary_el const* rl_getOperator(uint32_t opcode)
{
    uint32_t radioLib_size = sizeof(referenceRadioLibrary)/sizeof(referenceRadioLibrary[0]);
    for(uint32_t i =0 ; i < radioLib_size; i++)
    {
        const radioLibrary_el *el = &referenceRadioLibrary[i];
        if(el->opcode == opcode)
        {
            return el;
        }
    }
    return nullptr;
}

uint8_t rl_getInputPortCnt(uint32_t opcode)
{
    uint8_t cnt = 0;
    uint32_t radioLib_size = sizeof(referenceRadioLibrary)/sizeof(referenceRadioLibrary[0]);
    for(uint32_t i =0 ; i < radioLib_size; i++)
    {
        const radioLibrary_el *el = &referenceRadioLibrary[i];
        if(el->opcode == opcode)
        {
            uint32_t ports_size =  sizeof(el->ports)/sizeof(el->ports[0]);
            for(uint32_t j = 0; j < ports_size; j++)
            {
                if((el->ports[j].fFilled) && (el->ports[j].dir == RL_INPUT_PORT))
                {
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

uint8_t rl_getOutputPortCnt(uint32_t opcode)
{
    uint8_t cnt = 0;
    uint32_t radioLib_size = sizeof(referenceRadioLibrary)/sizeof(referenceRadioLibrary[0]);
    for(uint32_t i =0 ; i < radioLib_size; i++)
    {
        const radioLibrary_el *el = &referenceRadioLibrary[i];
        if(el->opcode == opcode)
        {
            uint32_t ports_size =  sizeof(el->ports)/sizeof(el->ports[0]);
            for(uint32_t j = 0; j < ports_size; j++)
            {
                if((el->ports[j].fFilled) && (el->ports[j].dir == RL_OUTPUT_PORT))
                {
                    cnt++;
                }
            }
        }
    }
    return cnt;
}