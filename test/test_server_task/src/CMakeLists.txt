cmake_minimum_required(VERSION 3.24)

project(Communication_Component_Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../../../include)

link_directories(../../../lib)

aux_source_directory(. src_list)

add_executable(Test_Server_Task ${src_list})

target_link_libraries(Test_Server_Task libCommunication_Component.so)
