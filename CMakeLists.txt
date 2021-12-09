cmake_minimum_required(VERSION 3.20)
project(RadioVirtualMachine)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)


add_executable(RadioVirtualMachine main.cpp source/RVM_DataObject.cpp source/RVM_DataObject.h source/RVM_SharedMemory.cpp source/RVM_SharedMemory.h source/trush.h source/RVM_Types.h tests/test_DataObject.cpp tests/test_DataObject.h source/RVM_AbstractSwitchFabric.cpp source/RVM_AbstractSwitchFabric.h source/ASF_ContainerPorts.cpp source/ASF_ContainerPorts.h)
