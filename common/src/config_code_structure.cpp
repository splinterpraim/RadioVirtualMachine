#include "config_code_structure.hpp"
#include <cstring>
/* Private */

void showAPE_Config(APE_Config &apeCfg, uint16_t N_APE)
{
    std::string space4 = "    ";
    APE_Config *ptrApeCfg = &apeCfg;
    for (uint16_t i = 0; i < N_APE; i++)
    {
        std::cout << space4 << "APE_ID: " << (int)ptrApeCfg[i].APE_ID << ", op code: " << (int)ptrApeCfg[i].op_code << ", T: " << (int)ptrApeCfg[i].T << ", NN: " << (int)ptrApeCfg[i].NN << ", cost: " << (int)ptrApeCfg[i].cost << ", time: " << (int)ptrApeCfg[i].time << ", access type: ";
        for (size_t j = 0; j < ptrApeCfg[i].NN; ++j)
            std::cout << (int)ptrApeCfg[i].access_type[j] << " ";
        std::cout << std::endl;
    }
}

void showASF_config(ASF_Config &asfCfg, uint8_t N_DO)
{
    std::string space4 = "    ";
    ASF_Config *ptrAsfCfg = &asfCfg;
    for (uint8_t i = 0; i < N_DO; i++)
    {
        std::cout << space4 << "DO_ID: " << (int)ptrAsfCfg[i].DO << ", Number of APEs connected with DO: " << (int)ptrAsfCfg[i].N << ", APE_KP (APE:PORT) = [ ";
        for (int j = 0; j < ptrAsfCfg[i].N; ++j)
        {
            std::cout << (int)ptrAsfCfg[i].APE_KP[j].APE_number << ":" << (int)ptrAsfCfg[i].APE_KP[j].port_number; 
            if ((j + 1) != ptrAsfCfg[i].N)
            {
                std::cout<< ", ";
            }
        }
        std::cout << " ]" << std::endl;
    }
}

void showDO_Config(DO_Config &doCfg, uint8_t N_DO)
{
    std::string space4 = "    ";
    DO_Config *ptrDoCfg = &doCfg;
    for (uint8_t i = 0; i < N_DO; i++)
    {
        std::cout << space4 << "DO_ID: " << (int)ptrDoCfg[i].DO_ID << ", size: " << (int)ptrDoCfg[i].size << 
                            ", access_time: " << (int)ptrDoCfg[i].access_time << ", length: " << (int)ptrDoCfg[i].length << 
                            ", external: " << (int)ptrDoCfg[i].external << ", data: ";
        for (size_t j = 0; j < ptrDoCfg[i].length; ++j)
            std::cout << std::hex << (int)ptrDoCfg[i].data[j] << " ";
        std::cout << std::dec;
        std::cout << std::endl;
    }
}

void showApeSection(APE_Section &apeSec)
{
    std::string space = "  ";
    std::cout << space << "N_APE: " << (int)apeSec.N_APE << std::endl;
    std::cout << space << "APE_Config: " << std::endl;
    showAPE_Config(*apeSec.APEs, apeSec.N_APE);
}

void showDoSection(DO_Section &doSec)
{
    std::string space = "  ";
    std::cout << space << "N_DO: " << (int)doSec.N_DO << std::endl;
    std::cout << space << "DO_Config: " << std::endl;
    showDO_Config(*doSec.DOs, doSec.N_DO);
    std::cout << space << "ASF_Config: " << std::endl;
    showASF_config(*doSec.ASFs, doSec.N_DO);
}

void showControlSection(ControlSection &ctrlSec)
{
    std::string space = "  ";
    std::cout << space << "LCF: " << (int)ctrlSec.LCF << ", NAF: " << (int)ctrlSec.NAF << ",\n"
    << space << "Task_ID: " << (int)ctrlSec.Task_ID << ", RPI_version: " << (int)ctrlSec.RPI_version << ",\n"
    << space << "Reference_ID: " << (int)ctrlSec.Reference_ID << ", Impl_version: " << (int)ctrlSec.Implementation_version << ",\n"
    << space << "Developer_ID: " << (unsigned int)ctrlSec.Developer_ID << ", Creation_Date: " << (unsigned int)ctrlSec.Creation_Date << std::endl;
}


/* Public */
void initConfigObjects(ConfigObjects & cfgObj)
{
    std::memset(&(cfgObj), 0, sizeof(ConfigObjects));
}

void showConfigObjects(ConfigObjects &cfgObj)
{
    std::cout << "Control Section: " << std::endl;
    showControlSection(cfgObj.controlSection);
    std::cout << "DO Section: " << std::endl;
    showDoSection(cfgObj.doSection);
    std::cout << "APE Section: " << std::endl;
    showApeSection(cfgObj.apeSection);
}

void clearConfigObjects(ConfigObjects & cfgObj)
{
    std::memset(&(cfgObj.controlSection), 0, sizeof(ControlSection));

    /* Clear DO_Section */
    /* Clear DO_Config */
    if ( cfgObj.doSection.DOs != nullptr )
    {
        for (uint8_t i = 0; i < cfgObj.doSection.N_DO; ++i)
        {
            if ( cfgObj.doSection.DOs[i].data != nullptr )
            {
                delete[] cfgObj.doSection.DOs[i].data;
            }
        }
        delete[] cfgObj.doSection.DOs;
    }
    /* Clear ASF_Config */
    if ( cfgObj.doSection.ASFs != nullptr )
    {
        for (uint8_t i = 0; i < cfgObj.doSection.N_DO; ++i)
        {
            if ( cfgObj.doSection.ASFs[i].APE_KP != nullptr )
            {
                delete[] cfgObj.doSection.ASFs[i].APE_KP;
            }
        }
        delete[] cfgObj.doSection.ASFs;
    }

    /* Clear APE_Section */
    /* Clear APE_Config */
    if ( cfgObj.apeSection.APEs != nullptr )
    {
        for (uint8_t i = 0; i < cfgObj.apeSection.N_APE; ++i)
        {
            if ( cfgObj.apeSection.APEs[i].access_type != nullptr )
            {
                delete[] cfgObj.apeSection.APEs[i].access_type;
            }
        }
        delete[] cfgObj.apeSection.APEs;
    }

    std::memset(&(cfgObj), 0, sizeof(ConfigObjects));
}




