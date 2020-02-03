cmake_minimum_required(VERSION 3.10)

project(network_socket)

if(WIN32)
	add_compile_options("/std:c++latest")
endif(WIN32)

set(CMAKE_CXX_STANDARD 17)

add_executable(server
${CMAKE_CURRENT_SOURCE_DIR}/server/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/server/player.h
)

add_executable(client
${CMAKE_CURRENT_SOURCE_DIR}/client/main.cpp
)

 