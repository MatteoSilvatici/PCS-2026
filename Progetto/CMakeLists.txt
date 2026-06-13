cmake_minimum_required(VERSION 3.20)

project(Progetto) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow  -Werror=vla")

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES main.cpp)
add_executable(main ${SOURCES})

find_package(Eigen3 REQUIRED)
target_link_libraries(main Eigen3::Eigen)





