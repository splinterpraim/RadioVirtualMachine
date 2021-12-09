//
// Created by oem on 05.12.2021.
//

#ifndef RADIOVIRTUALMACHINE_RVM_ABSTRACTSWITCHFABRIC_H
#define RADIOVIRTUALMACHINE_RVM_ABSTRACTSWITCHFABRIC_H
#include "RVM_Types.h"
#include "RVM_DataObject.h"
#include "ASF_ContainerPorts.h"

namespace ASF {


    class RVM_AbstractSwitchFabric {
        ASF_ContainerPorts<ASF_PortData> *portsDO;
        ASF_ContainerPorts<ASF_PortAPE> *portsAPE;
       // Connector *connectors;
    };
//
//
//
//
//
//    class PortsAPE {
//        &
//        APE;
//        number;
//        interf; //
//
//        functions
//    };
//
//    class Connector {
//        numPortDO;
//        numPortAPE;
//        direction;
////        interfaceLineDO;
////        interfaceLineAPE;
//    };
}

#endif //RADIOVIRTUALMACHINE_RVM_ABSTRACTSWITCHFABRIC_H
