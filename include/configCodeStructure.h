
#ifndef FRONT_END_RVM_COMPILER_CONFIGCODESTRUCTURE_H
#define FRONT_END_RVM_COMPILER_CONFIGCODESTRUCTURE_H
#include <iostream>

struct ControlSection {
    uint8_t LCF;
    uint8_t NAF;
    uint8_t Task_ID;
    uint8_t RPI_version;
    uint8_t Reference_ID;
    uint8_t Implementation_version;
    uint16_t Developer_ID; //15 bits
    uint16_t Creation_Date; //17 bits
};
struct DO_Config{
    uint8_t DO_ID;
    uint32_t size;
    uint32_t access_time;
    uint8_t length;
    uint8_t *data;
};
struct ASF_variable_part{
    uint8_t APE_number;
    uint8_t port_number;
};
struct ASF_Config{
    uint8_t DO;
    uint8_t N;
    struct ASF_variable_part *APE_KP ;
};

struct DO_Section {
    uint8_t N_DO; //number of DO
    struct DO_Config *DOs;
    struct ASF_Config *ASFs;
};

struct APE_Config{
    uint16_t APE_ID;
    uint32_t  op_code;
    uint8_t T;
    uint8_t NN;
    uint16_t cost;
    uint16_t time;
    uint8_t  *access_type;
};
struct APE_Section{
    uint16_t N_APE;
    struct APE_Config *APEs;
};
#endif //FRONT_END_RVM_COMPILER_CONFIGCODESTRUCTURE_H