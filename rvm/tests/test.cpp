

#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>

#include "rvm_program_memory.hpp"
#include "DO/data_object.hpp"
#include "APE/abstract_processing_element.hpp"
#include "rvm_glob_define.hpp"
#include "common.hpp"

#define TEST_GOOD std::cout << __func__ << " is " << SET_GREEN("GOOD") << std::endl;
#define TEST_BAD std::cout << __func__ << " is " << SET_RED("BAD") << std::endl;

void TEST_rvm_ProgramMemory_init0()
{
    rvm_ProgramMemory pMem;

    try
    {
        pMem.init(0);
        TEST_BAD
    }
    catch (const std::exception &e)
    {
        TEST_GOOD
        return;
    }
    // bad test
    throw std::runtime_error("B");
}

void TEST_rvm_ProgramMemory_initPos()
{
    rvm_ProgramMemory pMem;

    try
    {
        pMem.init(10);
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cout << e.what() << std::endl;
        // bad test
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_loadNorm()
{
    rvm_ProgramMemory pMem;

    try
    {
        pMem.init(100);
        pMem.load("/home/xivvxx/buff/cfgfile");
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cerr << e.what() << '\n';
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_loadMoreSize()
{
    rvm_ProgramMemory pMem;

    try
    {
        pMem.init(1);
        pMem.load("/home/xivvxx/buff/cfgfile");
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cerr << e.what() << '\n';
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_loadNoData()
{
    rvm_ProgramMemory pMem;
    try
    {
        pMem.init(1);
        pMem.load("/home/xivvxx/buff/cfgfile3");
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cerr << e.what() << '\n';
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_loadMultData()
{
    rvm_ProgramMemory pMem;
    try
    {
        pMem.init(1);
        pMem.load("/home/xivvxx/buff/cfgfile");
        pMem.load("/home/xivvxx/buff/cfgfile2");
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cerr << e.what() << '\n';
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_getNorm()
{
    rvm_ProgramMemory pMem;
    try
    {
        pMem.init(1);
        pMem.load("/home/xivvxx/buff/cfgfile");
        pMem.get(0);
        TEST_GOOD
    }
    catch (const std::exception &e)
    {
        TEST_BAD
        std::cerr << e.what() << '\n';
        throw std::runtime_error("B");
    }
    return;
}

void TEST_rvm_ProgramMemory_getOutOfRange()
{
    rvm_ProgramMemory pMem;
    try
    {
        pMem.init(1);
        pMem.load("/home/xivvxx/buff/cfgfile");
        pMem.get(100);
        TEST_BAD
    }
    catch (const std::exception &e)
    {
        TEST_GOOD

        return;
    }
    throw std::runtime_error("B");
}

int EmptyPlug(uint8_t argc, ...) { return 0;}

typedef struct
{
    std::vector<int> dp; // number, related DO id
    std::vector<std::pair<int,int>> pp; // number, related APE id, APE port num
    std::vector<std::pair<int,std::pair<int,int>>> con; // dp num, pp num, dir

    std::string to_str()
    {
        std::string res;
        int rowSize = 8;
        int dpRowSize = 12;

        res = "data ports [ num : ID_of_related_DO ]:\n";
        res += "count = " + std::to_string(dp.size()) + "\n\t";
        int i = 0;
        for(auto& el : dp)
        {
            res += "[" + std::to_string(i) + ":" + std::to_string(el) + "] ";
            i++;
            if (i%dpRowSize == 0)
                res += "\n\t";
        }

        res += "\n";
        res += "processing ports [ num : ID_of_related_APE : APE_port ]:\n";
        res += "count = " + std::to_string(pp.size()) + "\n\t";
        i = 0;
        for(auto& el : pp)
        {
            res += "[" + std::to_string(i) + ":" 
                       + std::to_string(el.first) + ":"
                       + std::to_string(el.second) +"] ";
            i++;
            if (i%rowSize == 0)
                res += "\n\t";
        }

        res += "\n";
        res += "connectors [ data_port_ID : processing_port_ID : direction ]:\n";
        res += "count = " + std::to_string(pp.size()) + "\n\t";
        i = 0;
        for(auto& el : con)
        {
            res += "[" + std::to_string(el.first) + ":" 
                       + std::to_string(el.second.first) + ":"
                       + std::to_string(el.second.second) +"] ";
            i++;
            if (i%rowSize == 0)
                res += "\n\t";
        }
        
        return res;
    }
} asf_t;
/* RVM Test */
void TEST_rvm_Program()
{
    /* Data prepare */
    uint8_t do0[1] = {1};
    uint8_t do1[1] = {6};
#define PROGRAM_DO_SIZE 6
#define PROGRAM_APE_SIZE 4
    size_t do_size = PROGRAM_DO_SIZE;
    size_t ape_size = PROGRAM_APE_SIZE;
    DataObject dos[PROGRAM_DO_SIZE];
    int id = 0;
    dos[id].set(id, 1, 11); dos[id].init(do0[0], 1); id++;
    dos[id].set(id, 4, 11); dos[id].init(do1[0], 1); id++;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 4, 11); id++;
    dos[id].set(id, 4, 11); id++;

    AbstractProcessingElement apes[PROGRAM_APE_SIZE];
    id = 0;
    apes[id].set(id+1, 10, 10, 0, {0,0,1,1}); apes[id].init(32,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(34,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(29,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(33,EmptyPlug); id++;

    asf_t asf;
    id = 0;
    for (size_t i = 0; i < do_size; i++) { asf.dp.push_back(i); }
    asf.pp.push_back({1,1}); asf.pp.push_back({1,2}); asf.pp.push_back({1,3}); asf.pp.push_back({1,4});
    asf.pp.push_back({2,1}); asf.pp.push_back({2,2});
    asf.pp.push_back({3,1}); asf.pp.push_back({3,2});
    asf.pp.push_back({4,1}); asf.pp.push_back({4,2});
    asf.con.push_back({0,{0,0}}); asf.con.push_back({0,{9,1}});
    asf.con.push_back({1,{1,0}});
    asf.con.push_back({2,{2,1}}); asf.con.push_back({2,{4,0}});
    asf.con.push_back({3,{3,1}});
    asf.con.push_back({4,{5,1}}); asf.con.push_back({4,{6,0}});
    asf.con.push_back({5,{7,1}}); asf.con.push_back({5,{8,0}});

    /* Output */
    std::cout << "Data Objects" << std::endl;
    for (size_t i = 0; i < do_size; i++)
    {
        std::cout << dos[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Processing Elements" << std::endl;
    for (size_t i = 0; i < ape_size; i++)
    {
        std::cout << apes[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Switch Fabric" << std::endl;
    std::cout << asf.to_str() << std::endl;

}

void TEST_rvm_Program_it_before(int iter)
{
    /* Data prepare */

#define PROGRAM_DO_SIZE 6
#define PROGRAM_APE_SIZE 4
    size_t do_size = PROGRAM_DO_SIZE;
    size_t ape_size = PROGRAM_APE_SIZE;
    DataObject dos[PROGRAM_DO_SIZE];
    uint8_t startVal[1];
    typedef union {int32_t val;uint8_t bytes[4];} val32_t;
    val32_t x;

    switch(iter)
    {
        case 1:
        {
            startVal[0] = 5;
            x.val = 3;
            break;
        }
        case 2:
        {
            startVal[0] = 4;
            x.val = 1;
            break;
        }
        case 3:
        {
            startVal[0] = 3;
            x.val = 20;
            break;
        }
        case 4:
        {
            startVal[0] = 2;
            x.val = 7;
            break;
        }
        case 5:
        {
            startVal[0] = 1;
            x.val = 32;
            break;
        }
        case 6:
        {
            startVal[0] = 0;
            x.val = 18;
            break;
        }
    }
    uint8_t doX[4] = {x.bytes[0], x.bytes[1], x.bytes[2], x.bytes[3] };


    int id = 0;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 4, 11); dos[id].init(startVal[0], 1); id++;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 4, 11); dos[id].init(doX[0], 4); id++;
    dos[id].set(id, 4, 11); id++;

    AbstractProcessingElement apes[PROGRAM_APE_SIZE];
    id = 0;
    apes[id].set(id+1, 10, 10, 0, {0,0,1,1}); apes[id].init(32,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(34,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(29,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(33,EmptyPlug); id++;

    asf_t asf;
    id = 0;
    for (size_t i = 0; i < do_size; i++) { asf.dp.push_back(i); }
    asf.pp.push_back({1,1}); asf.pp.push_back({1,2}); asf.pp.push_back({1,3}); asf.pp.push_back({1,4});
    asf.pp.push_back({2,1}); asf.pp.push_back({2,2});
    asf.pp.push_back({3,1}); asf.pp.push_back({3,2});
    asf.pp.push_back({4,1}); asf.pp.push_back({4,2});
    asf.con.push_back({0,{0,0}}); asf.con.push_back({0,{9,1}});
    asf.con.push_back({1,{1,0}});
    asf.con.push_back({2,{2,1}}); asf.con.push_back({2,{4,0}});
    asf.con.push_back({3,{3,1}});
    asf.con.push_back({4,{5,1}}); asf.con.push_back({4,{6,0}});
    asf.con.push_back({5,{7,1}}); asf.con.push_back({5,{8,0}});

    /* Output */
    std::cout << "Data Objects" << std::endl;
    for (size_t i = 0; i < do_size; i++)
    {
        std::cout << dos[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Processing Elements" << std::endl;
    for (size_t i = 0; i < ape_size; i++)
    {
        std::cout << apes[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Switch Fabric" << std::endl;
    std::cout << asf.to_str() << std::endl;

}

void TEST_rvm_Program_it_after(int iter)
{
    /* Data prepare */

#define PROGRAM_DO_SIZE 6
#define PROGRAM_APE_SIZE 4
    size_t do_size = PROGRAM_DO_SIZE;
    size_t ape_size = PROGRAM_APE_SIZE;
    DataObject dos[PROGRAM_DO_SIZE];
    uint8_t startVal[1];
    typedef union {int32_t val;uint8_t bytes[4];} val32_t;
    val32_t y;

    switch(iter)
    {
        case 1:
        {
            startVal[0] = 5;
            y.val = 60;
            break;
        }
        case 2:
        {
            startVal[0] = 4;
            y.val = 110;
            break;
        }
        case 3:
        {
            startVal[0] = 3;
            y.val = 550;
            break;
        }
        case 4:
        {
            startVal[0] = 2;
            y.val = 780;
            break;
        }
        case 5:
        {
            startVal[0] = 1;
            y.val = 1650;
            break;
        }
        case 6:
        {
            startVal[0] = 0;
            y.val = 1600;
            break;
        }
    }
    uint8_t doY[4] = {y.bytes[0], y.bytes[1], y.bytes[2], y.bytes[3] };

    int id = 0;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 4, 11); dos[id].init(startVal[0], 1); id++;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 4, 11); id++;
    dos[id].set(id, 4, 11); dos[id].init(doY[0], 4); id++;

    AbstractProcessingElement apes[PROGRAM_APE_SIZE];
    id = 0;
    apes[id].set(id+1, 10, 10, 0, {0,0,1,1}); apes[id].init(32,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(34,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(29,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(33,EmptyPlug); id++;

    asf_t asf;
    id = 0;
    for (size_t i = 0; i < do_size; i++) { asf.dp.push_back(i); }
    asf.pp.push_back({1,1}); asf.pp.push_back({1,2}); asf.pp.push_back({1,3}); asf.pp.push_back({1,4});
    asf.pp.push_back({2,1}); asf.pp.push_back({2,2});
    asf.pp.push_back({3,1}); asf.pp.push_back({3,2});
    asf.pp.push_back({4,1}); asf.pp.push_back({4,2});
    asf.con.push_back({0,{0,0}}); asf.con.push_back({0,{9,1}});
    asf.con.push_back({1,{1,0}});
    asf.con.push_back({2,{2,1}}); asf.con.push_back({2,{4,0}});
    asf.con.push_back({3,{3,1}});
    asf.con.push_back({4,{5,1}}); asf.con.push_back({4,{6,0}});
    asf.con.push_back({5,{7,1}}); asf.con.push_back({5,{8,0}});

    /* Output */
    std::cout << "Data Objects" << std::endl;
    for (size_t i = 0; i < do_size; i++)
    {
        std::cout << dos[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Processing Elements" << std::endl;
    for (size_t i = 0; i < ape_size; i++)
    {
        std::cout << apes[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Switch Fabric" << std::endl;
    std::cout << asf.to_str() << std::endl;

}


void TEST_rvm_FIR()
{
    /* Data prepare */
    uint8_t do4[1] = {0x14};
    uint8_t do9[1] = {0x1e};
    uint8_t do12[1] = {0x28};
#define FIR_DO_SIZE 14
#define FIR_APE_SIZE 8
    size_t do_size = FIR_DO_SIZE;
    size_t ape_size = FIR_APE_SIZE;
    DataObject dos[FIR_DO_SIZE];
    int id = 0;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 1, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); dos[id].init(do4[0], 1); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); dos[id].init(do9[0], 1); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); dos[id].init(do12[0], 1); id++;

    AbstractProcessingElement apes[FIR_APE_SIZE];
    id = 0;
    apes[id].set(id+1, 10, 10, 0, {0,1,1}); apes[id].init(24,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,0,1}); apes[id].init(15,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(25,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1,1}); apes[id].init(24,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,0,1}); apes[id].init(15,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(25,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,0,1}); apes[id].init(15,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,0,0,1}); apes[id].init(23,EmptyPlug); id++;

    asf_t asf;
    id = 0;
    for (size_t i = 0; i < do_size; i++) { asf.dp.push_back(i); }
    asf.pp.push_back({0,1});/* 0 */  asf.pp.push_back({0,2});/* 1 */
    asf.pp.push_back({1,1});/* 2 */  asf.pp.push_back({1,2});/* 3 */  asf.pp.push_back({1,3});/* 4 */
    asf.pp.push_back({2,1});/* 5 */  asf.pp.push_back({2,2});/* 6 */  asf.pp.push_back({2,3});/* 7 */
    asf.pp.push_back({3,1});/* 8 */  asf.pp.push_back({3,2});/* 9 */
    asf.pp.push_back({4,1});/* 10 */ asf.pp.push_back({4,2});/* 11 */ asf.pp.push_back({4,3});/* 12 */
    asf.pp.push_back({5,1});/* 13 */ asf.pp.push_back({5,2});/* 14 */ asf.pp.push_back({5,3});/* 15 */
    asf.pp.push_back({6,1});/* 16 */ asf.pp.push_back({6,2});/* 17 */
    asf.pp.push_back({7,1});/* 18 */ asf.pp.push_back({7,2});/* 19 */ asf.pp.push_back({5,3});/* 20 */
    asf.pp.push_back({8,1});/* 21 */ asf.pp.push_back({8,2});/* 22 */ asf.pp.push_back({8,3});/* 23 */ asf.pp.push_back({8,4});/* 24 */
    asf.con.push_back({0,{0,0}}); asf.con.push_back({0,{2,0}});
    asf.con.push_back({1,{1,1}}); asf.con.push_back({1,{24,1}});
    asf.con.push_back({2,{3,1}}); asf.con.push_back({2,{5,0}});
    asf.con.push_back({3,{4,1}}); asf.con.push_back({3,{8,0}});
    asf.con.push_back({4,{6,0}});
    asf.con.push_back({5,{7,1}}); asf.con.push_back({5,{21,0}});
    asf.con.push_back({6,{9,1}}); asf.con.push_back({6,{10,0}});
    asf.con.push_back({7,{11,1}}); asf.con.push_back({7,{13,0}});
    asf.con.push_back({8,{12,1}}); asf.con.push_back({8,{16,0}});
    asf.con.push_back({9,{14,0}});
    asf.con.push_back({10,{15,1}}); asf.con.push_back({10,{22,0}});
    asf.con.push_back({11,{17,1}}); asf.con.push_back({11,{18,0}});
    asf.con.push_back({12,{19,0}});
    asf.con.push_back({13,{20,1}}); asf.con.push_back({13,{23,0}});

    /* Output */
    std::cout << "Data Objects" << std::endl;
    for (size_t i = 0; i < do_size; i++)
    {
        std::cout << dos[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Processing Elements" << std::endl;
    for (size_t i = 0; i < ape_size; i++)
    {
        std::cout << apes[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Switch Fabric" << std::endl;
    std::cout << asf.to_str() << std::endl;
}

void TEST_rvm_Delay()
{
    /* Data prepare */
    uint8_t do4[1] = {0};
#define DELAY_DO_SIZE 5
#define DELAY_APE_SIZE 3
    size_t do_size = DELAY_DO_SIZE;
    size_t ape_size = DELAY_APE_SIZE;
    DataObject dos[FIR_DO_SIZE];
    int id = 0;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 1, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); dos[id].init(do4[0], 1); id++;

    AbstractProcessingElement apes[DELAY_APE_SIZE];
    id = 0;
    apes[id].set(id+1, 10, 10, 0, {0,1,1}); apes[id].init(27,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,1}); apes[id].init(26,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,0,1}); apes[id].init(28,EmptyPlug); id++;

    asf_t asf;
    id = 0;
    for (size_t i = 0; i < do_size; i++) { asf.dp.push_back(i); }
    asf.pp.push_back({0,1});/* 0 */  asf.pp.push_back({0,2});/* 1 */
    asf.pp.push_back({1,1});/* 2 */  asf.pp.push_back({1,2});/* 3 */  asf.pp.push_back({1,3});/* 4 */
    asf.pp.push_back({2,1});/* 5 */  asf.pp.push_back({2,2});/* 6 */
    asf.pp.push_back({3,1});/* 7 */  asf.pp.push_back({3,2});/* 8 */  asf.pp.push_back({3,3});/* 9 */
    asf.con.push_back({0,{0,0}}); asf.con.push_back({0,{2,0}});
    asf.con.push_back({1,{1,1}}); asf.con.push_back({1,{9,1}});
    asf.con.push_back({2,{3,1}}); asf.con.push_back({2,{7,0}});
    asf.con.push_back({3,{4,1}}); asf.con.push_back({3,{5,0}});
    asf.con.push_back({4,{6,1}}); asf.con.push_back({4,{8,0}});

    /* Output */
    std::cout << "Data Objects" << std::endl;
    for (size_t i = 0; i < do_size; i++)
    {
        std::cout << dos[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Processing Elements" << std::endl;
    for (size_t i = 0; i < ape_size; i++)
    {
        std::cout << apes[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Switch Fabric" << std::endl;
    std::cout << asf.to_str() << std::endl;
}

void TEST_rvm_Adder()
{
    /* Data prepare */
#define ADDER_DO_SIZE 5
#define ADDER_APE_SIZE 2
    size_t do_size = ADDER_DO_SIZE;
    size_t ape_size = ADDER_APE_SIZE;
    DataObject dos[ADDER_DO_SIZE];
    int id = 0;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); id++;
    dos[id].set(id, 4, 10); id++;

    AbstractProcessingElement apes[ADDER_APE_SIZE];
    id = 0;
    apes[id].set(id+1, 10, 10, 0, {0,0,1}); apes[id].init(4,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,0,1}); apes[id].init(4,EmptyPlug); id++;

    asf_t asf;
    id = 0;
    for (size_t i = 0; i < do_size; i++) { asf.dp.push_back(i); }
    asf.pp.push_back({0,1});/* 0 */  asf.pp.push_back({0,2});/* 1 */  asf.pp.push_back({0,3});/* 2 */ asf.pp.push_back({0,4});/* 3 */
    asf.pp.push_back({1,1});/* 4 */  asf.pp.push_back({1,2});/* 5 */  asf.pp.push_back({1,3});/* 6 */
    asf.pp.push_back({2,1});/* 7 */  asf.pp.push_back({2,2});/* 8 */  asf.pp.push_back({2,3});/* 9 */
    asf.con.push_back({0,{0,0}}); asf.con.push_back({0,{4,0}});
    asf.con.push_back({1,{1,0}}); asf.con.push_back({1,{5,0}});
    asf.con.push_back({2,{2,0}}); asf.con.push_back({2,{8,0}});
    asf.con.push_back({3,{3,1}}); asf.con.push_back({3,{9,1}});
    asf.con.push_back({4,{6,1}}); asf.con.push_back({4,{7,0}});

    /* Output */
    std::cout << "Data Objects" << std::endl;
    for (size_t i = 0; i < do_size; i++)
    {
        std::cout << dos[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Processing Elements" << std::endl;
    for (size_t i = 0; i < ape_size; i++)
    {
        std::cout << apes[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Switch Fabric" << std::endl;
    std::cout << asf.to_str() << std::endl;
}

void TEST_rvm_Iterator()
{
    /* Data prepare */
    typedef union {int32_t val;uint8_t bytes[4];}val32_t;
    val32_t v;
    v.val = -1;  
    uint8_t do6[4] = {v.bytes[0], v.bytes[1], v.bytes[2], v.bytes[3] };
    uint8_t do7[1] = {0};
#define ITERATOR_DO_SIZE 8
#define ITERATOR_APE_SIZE 3
    size_t do_size = ITERATOR_DO_SIZE;
    size_t ape_size = ITERATOR_APE_SIZE;
    DataObject dos[ITERATOR_DO_SIZE];
    int id = 0;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 4, 11); id++;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 1, 11); id++;
    dos[id].set(id, 4, 11); id++;
    dos[id].set(id, 4, 11); id++;
    dos[id].set(id, 4, 11); dos[id].init(do6[0], 4); id++;
    dos[id].set(id, 4, 11); dos[id].init(do7[0], 1); id++;

    AbstractProcessingElement apes[ITERATOR_APE_SIZE];
    id = 0;
    apes[id].set(id+1, 10, 10, 0, {0,0,1,1}); apes[id].init(30,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,0,1}); apes[id].init(4,EmptyPlug); id++;
    apes[id].set(id+1, 10, 10, 0, {0,0,0,1}); apes[id].init(41,EmptyPlug); id++;

    asf_t asf;
    id = 0;
    for (size_t i = 0; i < do_size; i++) { asf.dp.push_back(i); }
    asf.pp.push_back({0,1});/* 0 */  asf.pp.push_back({0,2});/* 1 */  asf.pp.push_back({0,3});/* 2 */  asf.pp.push_back({0,4});/* 3 */
    asf.pp.push_back({1,1});/* 4 */  asf.pp.push_back({1,2});/* 5 */  asf.pp.push_back({1,3});/* 6 */  asf.pp.push_back({1,4});/* 7 */
    asf.pp.push_back({2,1});/* 8 */  asf.pp.push_back({2,2});/* 9 */  asf.pp.push_back({2,3});/* 10 */
    asf.pp.push_back({3,1});/* 11 */  asf.pp.push_back({3,2});/* 12 */  asf.pp.push_back({3,3});/* 13 */  asf.pp.push_back({3,4});/* 14 */
    asf.con.push_back({0,{0,0}}); asf.con.push_back({0,{4,0}});
    asf.con.push_back({1,{1,0}}); asf.con.push_back({1,{5,0}}); asf.con.push_back({1,{10,1}});
    asf.con.push_back({2,{2,1}}); asf.con.push_back({2,{13,1}});
    asf.con.push_back({3,{3,1}}); asf.con.push_back({3,{14,1}});
    asf.con.push_back({4,{6,1}}); asf.con.push_back({4,{11,0}});
    asf.con.push_back({5,{7,1}}); asf.con.push_back({5,{8,0}});
    asf.con.push_back({6,{9,0}});
    asf.con.push_back({7,{12,0}});

    /* Output */
    std::cout << "Data Objects" << std::endl;
    for (size_t i = 0; i < do_size; i++)
    {
        std::cout << dos[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Processing Elements" << std::endl;
    for (size_t i = 0; i < ape_size; i++)
    {
        std::cout << apes[i].to_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Abstract Switch Fabric" << std::endl;
    std::cout << asf.to_str() << std::endl;
}

/* RUNS */
void RUN_TESTS_rvm_ProgramMemory()
{
    try
    {
        TEST_rvm_ProgramMemory_init0();
        TEST_rvm_ProgramMemory_initPos();
        TEST_rvm_ProgramMemory_loadNorm();
        TEST_rvm_ProgramMemory_loadMoreSize();
        TEST_rvm_ProgramMemory_loadMultData();
        TEST_rvm_ProgramMemory_getNorm();
        TEST_rvm_ProgramMemory_getOutOfRange();
    }
    catch (const std::exception &e)
    {
    }
}

void RUN_TESTS_rvm()
{
    try
    {
        // TEST_rvm_Program();
        // TEST_rvm_FIR();
        // TEST_rvm_Delay();
        // TEST_rvm_Adder();
        // TEST_rvm_Iterator();

        // TEST_rvm_Program_it_before(6);
        TEST_rvm_Program_it_after(6);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    try
    {
        // RUN_TESTS_rvm_ProgramMemory();
        RUN_TESTS_rvm();

    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}