#include "fc_parser.hpp"

#include "common.hpp"

#define FC_LOG(s) std::cout << s << std::endl

void fc_Parser::parse(std::string progFileName, std::string ccFileName)
{
    FC_LOG("----- parseSWIR");
    struct IrObjects irObjects = parserSWIR.parse(progFileName);
    showIrObjects(irObjects);

    FC_LOG("----- convert2rvmIr");
    ConfigObjects configObjects = convert2rvmIr(irObjects);
    showConfigObjects(configObjects);

    FC_LOG("----- create RVM configcode");
    createRVMcfgcode(configObjects, ccFileName);

    clearConfigObjects(configObjects);
}
