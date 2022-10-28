#define FC_LOG(s) std::cout << s << std::endl

/* C++ headers */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

/* XML lib headers*/
#include "pugixml/pugixml.hpp"

/* Project headers */
#include "ir_data.h"
#include "ir_operator.h"
#include "ir_link.h"
#include "frontend_compiler.h"
#include "radio_library.hpp"

#include "fc_glob.hpp"
#include "fc_glob_func.hpp"

// #include "../tests/include/test_ir_objects.h"
fc_glob_t fc_glob;
RadioLibrary radioLib;


void create_xml_file(std::string file_name = "output.xml");

///******************************
int main(int argc, char *argv[])
{

    try
    {

        /* Set global var */
        fc_glob_set();


        std::string file_nameSWIR = "./XML_files/AlgScalar2.xml";
        std::string file_nameBin = "./config_codes/cfgcode1.bin";

        if (argc == 2)
        {
            file_nameSWIR = argv[1];
        }

        FC_LOG("----- parseSWIR");
        struct IrObjects irObjects = parseSWIR(file_nameSWIR);
        showIrObjects(irObjects);

        FC_LOG("----- convert2rvmIr");
        ConfigObjects configObjects = convert2rvmIr(irObjects);
        showConfigObjects(configObjects);

        FC_LOG("----- create RVM configcode");
        createRVMcfgcode(configObjects, file_nameBin);

        clearConfigObjects(configObjects);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

void create_xml_file(std::string file_name)
{

    pugi::xml_document doc;
    pugi::xml_node program = doc.append_child("program");

    /* Create operator nodes */
    pugi::xml_node op1 = program.append_child("operator");
    pugi::xml_node op2 = program.append_child("operator");
    pugi::xml_node op3 = program.append_child("operator");

    /* Create data nodes */
    pugi::xml_node op1_data[3];
    pugi::xml_node op2_data[3];
    pugi::xml_node op3_data[3];
    for (int i = 0; i < 3; ++i)
    {
        op1_data[i] = op1.append_child("data");
    }

    for (int i = 0; i < 3; ++i)
    {
        op2_data[i] = op2.append_child("data");
    }

    for (int i = 0; i < 3; ++i)
    {
        op3_data[i] = op3.append_child("data");
    }

    /* Filling attribute operators */
    op1.append_attribute("id") = "mult1";
    op2.append_attribute("id") = "mult2";
    op3.append_attribute("id") = "sum";

    /* Filling attribute data */
    op1_data[0].append_attribute("id") = "1";
    op1_data[1].append_attribute("id") = "2";
    op1_data[2].append_attribute("id") = "3";
    op2_data[0].append_attribute("id") = "4";
    op2_data[1].append_attribute("id") = "5";
    op2_data[2].append_attribute("id") = "6";
    op3_data[0].append_attribute("id") = "3";
    op3_data[1].append_attribute("id") = "6";
    op3_data[2].append_attribute("id") = "7";

    op1_data[0].append_attribute("dir") = "input";
    op1_data[1].append_attribute("dir") = "input";
    op1_data[2].append_attribute("dir") = "output";
    op2_data[0].append_attribute("dir") = "input";
    op2_data[1].append_attribute("dir") = "input";
    op2_data[2].append_attribute("dir") = "output";
    op3_data[0].append_attribute("dir") = "input";
    op3_data[1].append_attribute("dir") = "input";
    op3_data[2].append_attribute("dir") = "output";

    doc.save_file(file_name.c_str());
}

// testIrData();
// testIrOperator();
// testIrLink();