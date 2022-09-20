cmake_minimum_required(VERSION 3.24)

project(Communication_Component)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

aux_source_directory(. src_list)

add_library(Communication_Component SHARED ${src_list})

target_link_libraries(Communication_Component event)

target_link_libraries(Communication_Component pthread)

set(CMAKE_INSTALL_PREFIX "../")

install(TARGETS Communication_Component
        LIBRARY DESTINATION lib)

install(FILES task.h thread_pool.h thread.h server_task.h
        DESTINATION include)