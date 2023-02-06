/**
 * @file rvm_data_path.cpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Data Path
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include "rvm_data_path.hpp"

#include <iostream>

#include "ASF/abstract_switch_fabric.hpp"

void rvm_DataPathShow(rvm_DataPath &dataPath)
{
    std::cout << "Data Objects" << std::endl;
    for (size_t i = 0; i < dataPath.dataObjs.size(); ++i)
    {
        std::cout << dataPath.dataObjs[i].to_str() << std::endl;
    }
    std::cout << "Astract Processing Elements" << std::endl;
    for (size_t i = 0; i < dataPath.apes.size(); ++i)
    {
        std::cout << dataPath.apes[i].to_str() << std::endl;
    }
    std::cout << "Abstract Switch Fabric" << std::endl;
    std::cout << dataPath.asf->to_str() << std::endl;
}