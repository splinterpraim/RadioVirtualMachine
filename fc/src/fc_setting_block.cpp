#include "fc_setting_block.hpp"

void fc_SettingBlock::setDirXML(const std::string &dirXML)
{
    this->dirXML = dirXML;
}

std::string fc_SettingBlock::getDirXML()
{
    return dirXML;
}

void fc_SettingBlock::setDirCC(const std::string &dirCC)
{
    this->dirCC = dirCC;
}

std::string fc_SettingBlock::getDirCC()
{
    return dirCC;
}