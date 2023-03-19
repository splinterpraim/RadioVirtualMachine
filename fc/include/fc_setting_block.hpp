/**
 * @file fc_setting_block.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Setting block for setting variables in front-end compiler
 * @version 0.2
 * @copyright Copyright (c) 2023
 */

#ifndef FC_SETTING_BLOCK_CLASS
#define FC_SETTING_BLOCK_CLASS

#include <string>

/**
 * @brief Class Setting block for setting variables in front-end compiler
 */
class fc_SettingBlock
{
public:
    /**
     * @brief Sets the directory where storages XML files
     *
     * @param[in] dirXML directory of XML files
     */
    void setDirXML(const std::string &dirXML);

     /**
     * @brief Gets the directory where storages XML files
     *
     * @retval directory of XML files
     */
    std::string getDirXML();

    /**
     * @brief Sets the directory where storages configcode files
     *
     * @param[in] dirXML directory of configcode files
     */
    void setDirCC(const std::string &dirCC);

    /**
     * @brief Gets the directory where storages configcode files
     *
     * @retval directory of configcode files
     */
    std::string getDirCC();

private:
    /* Directory of configcode files */
    std::string dirXML;
    /* Directory of configcode files*/
    std::string dirCC;
};

#endif // FC_SETTING_BLOCK_CLASS