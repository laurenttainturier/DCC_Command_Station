cmake_minimum_required(VERSION 3.21)
project(DCC_Command_Station)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_library(packetmanager STATIC libpacketmanager/packet_manager.cpp)
add_executable(DCC_Command_Station
        main.cpp
        libpacketmanager/packet_manager.cpp
        libpacketmanager/packet_manager.hpp libpacketmanager/details/packet_builder.cpp libpacketmanager/details/packet_builder.hpp)
