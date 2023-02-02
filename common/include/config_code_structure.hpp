//
// Created by Елена on 09.03.2022.
//

#ifndef FC_CONFIG_CODE_STRUCTURE_HPP
#define FC_CONFIG_CODE_STRUCTURE_HPP
#include <iostream>

#define APE_T_STATIC 0
#define APE_T_DYNAMIC 1

#define APE_ACCESS_TYPE_R 0
#define APE_ACCESS_TYPE_W 1

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
using ControlSection = struct ControlSection;

struct DO_Config{
    uint8_t DO_ID;          //* Identificator of data
    uint32_t size;          //* Maximum data size in bytes
    uint32_t access_time;   //* Access time in ns
    uint8_t length;         //* Current size of data (max 256 bytes of data)
    uint8_t *data;          //* Pointer to data
};
using DO_Config = struct DO_Config;

struct ASF_variable_part{
    uint8_t APE_number; //* ID of APE
    uint8_t port_number;
};
using ASF_variable_part = struct ASF_variable_part;

struct ASF_Config{
    uint8_t DO;
    uint8_t N; //* 6 bit (but in cfgbin 8 bit)
    ASF_variable_part *APE_KP ;
};
using ASF_Config = struct ASF_Config;

struct DO_Section {
    uint8_t N_DO; //* Number of DO
    DO_Config *DOs;
    ASF_Config *ASFs;
};
using DO_Section = struct DO_Section;

struct APE_Config{
    uint16_t APE_ID;
    uint32_t  op_code; //* 20 bits (but 32 bits)
    uint8_t T; //* flag for static (=0) or dynamic (=1) operations
    uint8_t NN; //* number of ports (3 bits)
    uint16_t cost; //* execution cost value (2 bytes)
    uint16_t time; //* constraint value (2 bytes)
    uint8_t  *access_type;
};
using APE_Config = struct APE_Config;

struct APE_Section{
    uint16_t N_APE; //* Number of APE
    APE_Config *APEs;
};
using APE_Section = struct APE_Section;

struct ConfigObjects{
    ControlSection controlSection;
    DO_Section doSection;
    APE_Section apeSection;
};
using ConfigObjects = struct ConfigObjects;


void initConfigObjects(ConfigObjects & cfgObj);
/**
 * @brief Shows Config objects in standart output
 * 
 * @param cfgObj Config objects for output
 */ 
void showConfigObjects(ConfigObjects & cfgObj);

/**
 * @brief Clear Config Objects
 * 
 * @param cfgObj Reference to Config Objects
 */ 
void clearConfigObjects(ConfigObjects & cfgObj); 


#endif //FC_CONFIG_CODE_STRUCTURE_HPP

